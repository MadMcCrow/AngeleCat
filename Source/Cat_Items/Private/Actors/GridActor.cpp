// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "GridActor.h"
#include "Cat_ItemsPCH.h"
#include "Runtime/Core/Public/Async/ParallelFor.h"
#include "GridMeshComponent.h"
#include "GameFramework/PlayerController.h"
#include "Components/BoxComponent.h"
#include "SlotWidgetComponent.h"
#if WITH_EDITOR
#include "Kismet/KismetSystemLibrary.h"
#endif // WITH_EDITOR


 AGridActor::AGridActor(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
	// default values
	GridSize= FIntPoint(25,25);
	ElementSize = FVector2D(200.f,200.f);
	PrimaryActorTick.bCanEverTick = false;
	
	// Create Components
	GlobalGridCollision = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("CollisionBox"));
	RootComponent = GlobalGridCollision;
	SlotMeshes = ObjectInitializer.CreateDefaultSubobject<UGridMeshComponent>(this, TEXT("SlotMeshes"));
	SlotMeshes->SetupAttachment(RootComponent);
	SlotMeshes->SetHiddenInGame(true); // it should be invisible and only used for collisions
	
	// Slots
	SelectedSlotMesh	= ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("SelectedSlotMesh"));
	HoveredSlotMesh		= ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("HoveredSlotMesh"));
	SelectedSlotMesh->SetupAttachment(RootComponent);
	HoveredSlotMesh->SetupAttachment(RootComponent);

	// SlotWidget
	ActiveSlotWidget = ObjectInitializer.CreateDefaultSubobject <USlotWidgetComponent> (this, TEXT("SelectedSlotWidget"));
	ActiveSlotWidget->SetupAttachment(RootComponent);

 	InitSlotArray();

}

void AGridActor::OnConstruction(const FTransform& transform)
{
    Super::OnConstruction(transform);

	SelectedSlot = -1;
	HoveredSlot = -1;
	// init slots
	InitSlotArray();
    SetBoundingBox();
	//DrawSlots();
}

void AGridActor::InitSlotArray()
{
    Slots.Empty();
	Slots.Init(FGridItemSlot(), GridSize.X * GridSize.Y);
    ParallelFor(Slots.Num(), [&](int32 Idx) {
    	Slots[Idx].SetCoordinate(Idx,GridSize.X , GridSize.Y );
    });

}


void AGridActor::BeginPlay()
{
	Super::BeginPlay();
}

FVector2D AGridActor::GetLocalGridPosition(const FIntPoint &pos) const
{
	const float X = (pos.X * ElementSize.X) +(ElementSize.X * 0.5);
	const float Y = (pos.Y * ElementSize.Y) +(ElementSize.Y * 0.5);
    return FVector2D( X, Y);
}

bool AGridActor::FindLookedAtPositionFromScreen(const FVector2D &screenPosition, const APlayerController* player, FIntPoint &outSlot)
{
	if(!player)
	return false;

	FVector position, direction;
	bool valid = false;
	valid = player->DeprojectScreenPositionToWorld(screenPosition.X, screenPosition.Y, position, direction );
	
	
	FVector CamLoc; FRotator CamRot;
	player->PlayerCameraManager->GetCameraViewPoint(CamLoc,CamRot);

	if(!valid)
		return false;
	
	FHitResult OutHit;
	const FVector Start = CamLoc;
	const FVector End = ((direction * 10000.f) + position);
	FCollisionQueryParams CollisionParams;
	FCollisionObjectQueryParams ObjectCollisionParams;
	ObjectCollisionParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
	ObjectCollisionParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);
	ObjectCollisionParams.AddObjectTypesToQuery(ECollisionChannel::ECC_PhysicsBody);
	valid = GetWorld()->LineTraceSingleByObjectType(OutHit, Start, End, ObjectCollisionParams, CollisionParams);

#if WITH_EDITOR
	if(bDebug)
		UKismetSystemLibrary::DrawDebugLine(this, Start,End, valid ? FColor::Blue : FColor::Red, 1.f, 0.5f);
#endif

	if(!valid)
		return false;
	

	if(OutHit.IsValidBlockingHit())
	{
		outSlot = CoordFromWorldSpace(OutHit.ImpactPoint);
		if(OutHit.Actor == this)
		{
			valid = true;	
		}
	}
	return valid;
}

AActor * AGridActor::GetItemAtCoordinate(const FIntPoint &coord)
{
	const FGridItemSlot * griditemslot = Slots.FindByPredicate([&coord](const FGridItemSlot &itr){
		return itr.GetCoordinate() == coord;
	});
	if(griditemslot)
		return griditemslot->GetItem();
	return nullptr;
}


void AGridActor::SetActorInSlot(AActor * actor, const FIntPoint &coord)
{
    if(!actor)
        return;

    
    FGridItemSlot * griditemslot = Slots.FindByPredicate([&coord](const FGridItemSlot &itr){
		return itr.GetCoordinate() == coord;
	});    
    if(griditemslot)
    {
        actor->SetActorTransform(GetSlotIdxWorldSpace(FGridItemSlot::IndexFromCoord(coord, GridSize.X , GridSize.Y )));
        griditemslot->Item = actor;
    }
}


void AGridActor::DrawSlots()
{
	if(SlotMeshes)
	{
		SlotMeshes->ClearInstances();
		for(int32 Idx = 0; Idx < Slots.Num(); Idx++)
		{
			const FTransform InstanceTransform = GetSlotIdxWorldSpace(Idx);
			SlotMeshes->AddInstanceWorldSpace(InstanceTransform);
		}
	}
}

void AGridActor::UpdateSlots()
{
    // we always remove selected and hovered slot.
    // if Selected == hovered. we only do selected.
	if(SelectedSlot != PreviousSelectedSlot)
	{
		PreviousSelectedSlot = SelectedSlot; // avoid doing this twice
		if(SelectedSlot != -1)
		{
			SelectedSlotMesh->SetHiddenInGame(false /*hidden*/, true/*Propagate to children*/);
			SelectedSlotMesh->SetWorldTransform(GetSlotIdxWorldSpace(SelectedSlot));

			// widget
			ActiveSlotWidget->SetHiddenInGame(false);
			ActiveSlotWidget->Reveal();
			ActiveSlotWidget->InitFromSlot(Slots[SelectedSlot]);
			ActiveSlotWidget->SetWorldTransform(GetSlotIdxWorldSpace(SelectedSlot));
		}
		else
		{
			ActiveSlotWidget->SetHiddenInGame(true);
			ActiveSlotWidget->Collapse();
			SelectedSlotMesh->SetHiddenInGame(true /*hidden*/, true/*Propagate to children*/);
		}
	}
	if(HoveredSlot != PreviousHoveredSlot)
	{
		if(HoveredSlot != -1 && HoveredSlot != SelectedSlot)
		{
			HoveredSlotMesh->SetHiddenInGame(false /*hidden*/, true/*Propagate to children*/);
			HoveredSlotMesh->SetWorldTransform(GetSlotIdxWorldSpace(HoveredSlot));
		}
		else
		{
			HoveredSlotMesh->SetHiddenInGame(true /*hidden*/, true/*Propagate to children*/);
		}
	}
}

void AGridActor::SetBoundingBox()
{
    // Get real actor dimensions :
    const FVector2D size2d = FVector2D(GridSize.X * ElementSize.X, GridSize.Y * ElementSize.Y);
    const FVector  size = FVector(size2d, 10);

    // set bounding box dimension :
    GlobalGridCollision->SetBoxExtent(size/2, false);

    // set grid offset
    // TODO: CHECK THAT :
    GridOffset = -1 * size/2;

}

FTransform AGridActor::GetSlotIdxWorldSpace(int32 idx) const
{
    const FTransform ActorT = GetActorTransform();
	const FVector2D Local2D = GetLocalGridPosition(FGridItemSlot::CoordFromIdx(idx, GridSize.X , GridSize.Y));
    const FVector LocalPosition = FVector(Local2D, 0.f) + GridOffset;
	const FVector WorldLocation = ActorT.TransformPosition(LocalPosition);
	return FTransform(ActorT.Rotator(), WorldLocation , ActorT.GetScale3D());
}

void AGridActor::SelectSlot(int32 idx)
{
	PreviousSelectedSlot = SelectedSlot;
    // ignore no change
    if(SelectedSlot == idx)
        return;

	if(Slots.IsValidIndex(idx))
	{
		SelectedSlot = idx;
		bSlotIsSelected = true;
	}
	else
	{
		SelectedSlot = -1;
		bSlotIsSelected = false;
	}
    UpdateSlots();
}

void AGridActor::SelectSlot(int32 X, int32 Y)
{
	SelectSlot(FGridItemSlot::IndexFromCoord(FIntPoint(X,Y), GridSize.X , GridSize.Y ));
}

void AGridActor::SelectSlot(FIntPoint coord)
{
	SelectSlot(FGridItemSlot::IndexFromCoord(coord, GridSize.X , GridSize.Y ));
}

void AGridActor::SelectSlot(FVector WorldPosition)
{
	SelectSlot(CoordFromWorldSpace(WorldPosition));
}

void AGridActor::DeselectSlot()
{
	SelectedSlot = -1;
	bSlotIsSelected = false;
}

void AGridActor::HoverSlot(int32 idx)
{
    // ignore no change
    if(HoveredSlot == idx)
        return;

	PreviousHoveredSlot = HoveredSlot;
	if(Slots.IsValidIndex(idx))
	{
		HoveredSlot = idx;
	}
	else
	{
		HoveredSlot = -1;
	}
    UpdateSlots();
}

void AGridActor::HoverSlot(int32 X, int32 Y)
{
	HoverSlot(FGridItemSlot::IndexFromCoord(FIntPoint(X,Y), GridSize.X , GridSize.Y ));
}

void AGridActor::HoverSlot(FIntPoint coord)
{
	HoverSlot(FGridItemSlot::IndexFromCoord(coord, GridSize.X , GridSize.Y ));
}

void AGridActor::HoverSlot(FVector WorldPosition)
{
	HoverSlot(CoordFromWorldSpace(WorldPosition));
}

 FIntPoint AGridActor::CoordFromWorldSpace(const FVector &WorldPosition)
 {
	 
	int32 Coord = -1;
	
	if(!SlotMeshes)
		return FIntPoint();

    // let's use instanced mesh to do that:
    FBox NewBox = FBox::BuildAABB (WorldPosition, FVector(ElementSize, ElementSize.X));




    TArray<int32> Idxs = SlotMeshes->GetInstancesOverlappingBox(NewBox, true);
    Idxs.Sort([&WorldPosition, this](const int32 &idxA, const int32 &idxB){
        FTransform instanceA;
        FTransform instanceB;
        SlotMeshes->GetInstanceTransform(idxA, instanceA, true);
        SlotMeshes->GetInstanceTransform(idxA, instanceB, true);
        return FVector::Dist(instanceA.GetTranslation(), WorldPosition) < FVector::Dist(instanceB.GetTranslation(), WorldPosition);
    });
    if(Idxs.IsValidIndex(0))
        Coord = Idxs[0];

	#if WITH_EDITOR
	if(bDebug)
		UKismetSystemLibrary::DrawDebugBox(this,NewBox.GetCenter(), NewBox.GetExtent(), Idxs.IsValidIndex(0) ? FLinearColor::Green : FLinearColor::Red, FRotator(), 0.2f, 1.f );
	#endif

    return FGridItemSlot::CoordFromIdx(Coord, GridSize.X , GridSize.Y);
 }

void AGridActor::HideSlotInstanceMesh(int32 idx, bool hide)
{
    // Set to actual transform of the idx
    FTransform insttransform;
	if(hide)
    	SlotMeshes->HideInstance(idx);
	else
		SlotMeshes->ShowInstance(idx);
    // enjoy
}