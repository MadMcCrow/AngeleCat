// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "Grid.h"
#include "Cat_ItemsPCH.h"
#include "Runtime/Core/Public/Async/ParallelFor.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "GameFramework/PlayerController.h"
#include "Components/BoxComponent.h"

 AGrid::AGrid(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
	// default values
	GridSize= FIntPoint(25,25);
	ElementSize = FVector2D(200.f,200.f);
	PrimaryActorTick.bCanEverTick = false;
	
	// Create Components
	GlobalGridCollision = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("CollisionBox"));
	RootComponent = GlobalGridCollision;
	SlotMeshes = ObjectInitializer.CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(this, TEXT("SlotMeshes"));
	SlotMeshes->SetupAttachment(RootComponent);
	
	// Slots
	SelectedSlotMesh	= ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("SelectedSlotMesh"));
	HoveredSlotMesh		= ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("HoveredSlotMesh"));
	SelectedSlotMesh->SetupAttachment(RootComponent);
	HoveredSlotMesh->SetupAttachment(RootComponent);


	// Init slots
    Slots.Init(FGridItemSlot(), GridSize.X * GridSize.Y);
    ParallelFor(Slots.Num(), [&](int32 Idx) {
    	Slots[Idx].SetCoordinate(Idx,GridSize.X , GridSize.Y );
    });

}

void AGrid::OnConstruction(const FTransform& transform)
{
    Super::OnConstruction(transform);
    
    SetBoundingBox();

}


void AGrid::BeginPlay()
{
	Super::BeginPlay();
	DrawSlots();
}

FVector2D AGrid::GetLocalGridPosition(const FIntPoint &pos) const
{
	const float X = (pos.X * ElementSize.X) +(ElementSize.X * 0.5);
	const float Y = (pos.Y * ElementSize.Y) +(ElementSize.Y * 0.5);
    return FVector2D( X, Y);
}

bool AGrid::FindLookedAtPositionFromScreen(const FVector2D &screenPosition, const APlayerController* player, FIntPoint &outSlot)
{
	FVector position, direction;
	bool valid = true;
	valid = player->DeprojectScreenPositionToWorld(screenPosition.X, screenPosition.Y, position, direction );
	
	if(!valid)
		return false;
	
	FHitResult OutHit;
	const FVector Start = position;
	const FVector End = ((direction * 1000.f) + position);
	FCollisionQueryParams CollisionParams;
	FCollisionObjectQueryParams ObjectCollisionParams;
	ObjectCollisionParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
	if(!GetWorld()->LineTraceTestByObjectType(OutHit, Start, End, ECC_Visibility, CollisionParams)) 
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

void AGrid::DrawSlots()
{
	if(SlotMeshes)
	{
		SlotMeshes->ClearInstances();
		for(int32 Idx = 0; Idx < Slots.Num(); Idx++)
		{
			const FTransform InstanceTransform = GetSlotIdxWorldSpace(Idx);
			SlotMeshes->AddInstanceWorldSpace(InstanceTransform);
		}
		// this crashes
		/*
		FCriticalSection Mutex;
		ParallelFor(Slots.Num(), [this, &Mutex](int32 Idx) {
			const FTransform InstanceTransform = GetSlotIdxWorldSpace(Idx);
			// Add instance mesh
			Mutex.Lock();
			SlotMeshes->AddInstanceWorldSpace(InstanceTransform);
			Mutex.Unlock();
		});
		*/
	}
}

void AGrid::UpdateSlots()
{
    // we always remove selected and hovered slot.
    // if Selected == hovered. we only do selected.
    if(SelectedSlot != -1)
    {
        SelectedSlotMesh->SetHiddenInGame(false /*hidden*/, true/*Propagate to children*/);
        SelectedSlotMesh->SetWorldTransform(GetSlotIdxWorldSpace(SelectedSlot));
        HideSlotInstanceMesh(SelectedSlot, true);
        if(PreviousSelectedSlot != -1)
            HideSlotInstanceMesh(PreviousSelectedSlot, false);
    }else
    {
        SelectedSlotMesh->SetHiddenInGame(true /*hidden*/, true/*Propagate to children*/);
    }
    if(HoveredSlot != -1 && HoveredSlot != SelectedSlot)
    {
        HoveredSlotMesh->SetHiddenInGame(false /*hidden*/, true/*Propagate to children*/);
        HoveredSlotMesh->SetWorldTransform(GetSlotIdxWorldSpace(HoveredSlot));
        HideSlotInstanceMesh(HoveredSlot, true);
        if(PreviousHoveredSlot != -1)
            HideSlotInstanceMesh(PreviousHoveredSlot, false);
    }
    else
    {
        HoveredSlotMesh->SetHiddenInGame(true /*hidden*/, true/*Propagate to children*/);
    }
}

void AGrid::SetBoundingBox()
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

FTransform AGrid::GetSlotIdxWorldSpace(int32 idx) const
{
    const FTransform ActorT = GetActorTransform();
	const FVector2D Local2D = GetLocalGridPosition(FGridItemSlot::CoordFromIdx(idx, GridSize.X , GridSize.Y));
    const FVector LocalPosition = FVector(Local2D, 0.f) + GridOffset;
	const FVector WorldLocation = ActorT.TransformPosition(LocalPosition);
	return FTransform(ActorT.Rotator(), WorldLocation , ActorT.GetScale3D());
}

void AGrid::SelectSlot(int32 idx)
{
    // ignore no change
    if(SelectedSlot == idx)
        return;

    PreviousSelectedSlot = Slots.IsValidIndex(SelectedSlot) ? SelectedSlot : -1;
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

void AGrid::SelectSlot(int32 X, int32 Y)
{
	SelectSlot(FGridItemSlot::IndexFromCoord(FIntPoint(X,Y), GridSize.X , GridSize.Y ));
}

void AGrid::SelectSlot(FIntPoint coord)
{
	SelectSlot(FGridItemSlot::IndexFromCoord(coord, GridSize.X , GridSize.Y ));
}

void AGrid::SelectSlot(FVector WorldPosition)
{
	SelectSlot(CoordFromWorldSpace(WorldPosition));
}

void AGrid::DeselectSlot()
{
    PreviousSelectedSlot = SelectedSlot;
	SelectedSlot = -1;
	bSlotIsSelected = false;
}

void AGrid::HoverSlot(int32 idx)
{
    // ignore no change
    if(HoveredSlot == idx)
        return;
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

void AGrid::HoverSlot(int32 X, int32 Y)
{
	HoverSlot(FGridItemSlot::IndexFromCoord(FIntPoint(X,Y), GridSize.X , GridSize.Y ));
}

void AGrid::HoverSlot(FIntPoint coord)
{
	HoverSlot(FGridItemSlot::IndexFromCoord(coord, GridSize.X , GridSize.Y ));
}

void AGrid::HoverSlot(FVector WorldPosition)
{
	HoverSlot(CoordFromWorldSpace(WorldPosition));
}

 FIntPoint AGrid::CoordFromWorldSpace(const FVector &WorldPosition)
 {
     /*
	const auto ClosestPoint = FVector::PointPlaneProject(WorldPosition, GetActorLocation() + GridOffset, GetActorUpVector());
	FTransform ActorT = GetActorTransform();
	ActorT.AddToTranslation(GridOffset);
	const auto Local = ActorT.InverseTransformPosition(ClosestPoint);
    return FIntPoint(ClosestPoint.X / ElementSize.X,ClosestPoint.Y / ElementSize.Y);
	*/
    // let's use instanced mesh to do that:
    FBox NewBox = FBox::BuildAABB (WorldPosition, FVector(ElementSize, ElementSize.X));
    const auto Idxs = SlotMeshes->GetInstancesOverlappingBox(const FBox& Box, true);
    Idxs.Sort([&WorldPosition](const int32 &idxA, const int32 &idxB){
        FTransform instanceA;
        FTransform instanceB;
        SlotMeshes->GetInstanceTransform(idxA, instanceA, true);
        SlotMeshes->GetInstanceTransform(idxA, instanceB, true);
        return FVector::Dist(instanceA.GetTranslation(), WorldPosition) < FVector::Dist(instanceB.GetTranslation(), WorldPosition);
    });
    if(!Idxs.IsValidIndex(0))
        return FIntPoint(0,0);
    
    
    return FGridItemSlot::CoordFromIdx(Idxs[]);
	// we should now only consider X and Y for position on the grid.

 }

void AGrid::HideSlotInstanceMesh(int32 idx, bool hide)
{
    // Set to actual transform of the idx
    FTransform insttransform;
    SlotMeshes->GetInstanceTransform(idx, insttransform, true);
    insttransform.SetScale3D(hide ? FVector::ZeroVector: FVector::OneVector);
    // apply it
    SlotMeshes->UpdateInstanceTransform( idx, insttransform, true /*bWorldSpace*/, true/*bMarkRenderStateDirty*/,false /*bTeleport*/);
    // enjoy
}