// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "Grid.h"
#include "Cat_ItemsPCH.h"
#include "Runtime/Core/Public/Async/ParallelFor.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"


 AGrid::AGrid(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{

	SlotMeshes = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("SlotMeshes"));
	GridSize= FIntPoint(25,25);
	ElementSize = FVector2D(200.f,200.f);
	PrimaryActorTick.bCanEverTick = false;

    Slots.Init(FGridItemSlot(), GridSize.X * GridSize.Y);
    ParallelFor(Slots.Num(), [&](int32 Idx) {
    	Slots[Idx].SetCoordinate(Idx,GridSize.X , GridSize.Y );
    });

}

void AGrid::BeginPlay()
{
	Super::BeginPlay();
	DrawSlots();
}

FVector2D AGrid::GetLocalGridPosition(FIntPoint pos)
{
	const float X = (pos.X * ElementSize.X) +(ElementSize.X * 0.5);
	const float Y = (pos.Y * ElementSize.Y) +(ElementSize.Y * 0.5);
    return FVector2D( X, Y);
}

void AGrid::DrawSlots()
{
	FTransform ActorT = GetActorTransform();

	SlotMeshes->ClearInstances();
	ParallelFor(Slots.Num(), [this, &ActorT](int32 Idx) {
		const FVector LocalPosition = FVector(GetLocalGridPosition(FGridItemSlot::CoordFromIdx(Idx, GridSize.X , GridSize.Y)), 0.f) + GridOffset;
		const FVector WorldLocation = ActorT.TransformPosition(LocalPosition);
		const FTransform InstanceTransform = FTransform(ActorT.Rotator(), WorldLocation , ActorT.GetScale3D());
		// Add instance mesh
		SlotMeshes->AddInstanceWorldSpace(InstanceTransform);
    });
}

void AGrid::UpdateSlots()
{

}

void AGrid::SelectSlot(int32 idx)
{
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
	const auto ClosestPoint = FVector::PointPlaneProject(WorldPosition, GetActorLocation() + GridOffset, GetActorUpVector());
	FTransform ActorT = GetActorTransform();
	ActorT.AddToTranslation(GridOffset);
	const auto Local = ActorT.InverseTransformPosition(ClosestPoint);
	// we should now only consider X and Y for position on the grid.
	SelectSlot(FIntPoint(ClosestPoint.X / ElementSize.X,ClosestPoint.Y / ElementSize.Y));
}

void AGrid::DeselectSlot()
{
	SelectedSlot = -1;
	bSlotIsSelected = false;
}
