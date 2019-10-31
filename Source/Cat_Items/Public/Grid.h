// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grid.generated.h"

// forward declaration
class UHierarchicalInstancedStaticMeshComponent;

USTRUCT()
struct FGridItemSlot
{
    GENERATED_BODY()
protected:
    
    UPROPERTY()
    FIntPoint coordinate;
    
    UPROPERTY()
    bool bIsEmpty;
    
    UPROPERTY()
    AActor * Item;
    
public:
    
    FGridItemSlot(FIntPoint coord = FIntPoint(0,0), bool empty = true, AActor * obj = nullptr) : coordinate(coord), bIsEmpty(empty), Item(obj)
    {}

	void SetCoordinate(int32 idx, int32 XDim, int32 YDim)	{coordinate = CoordFromIdx(idx, XDim, YDim);}

    static FIntPoint CoordFromIdx(int32 idx, int32 XDim, int32 YDim)
    {
		const int Y = idx / XDim;
		const int X = idx - ( XDim * Y);
        return FIntPoint(X,Y);
    }

	static int32 IndexFromCoord(FIntPoint coord, int32 XDim, int32 YDim)
    {
        return (coord.Y % YDim) * XDim + (coord.X % XDim);
    }
};




UCLASS()
class CAT_ITEMS_API AGrid : public AActor
{
	GENERATED_BODY()

public:

    AGrid(const FObjectInitializer &ObjectInitializer = FObjectInitializer::Get());

    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
    FIntPoint GridSize;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
    FVector2D ElementSize;
    
    UPROPERTY()
    FVector GridOffset;

protected:

    UFUNCTION(BlueprintCallable, Category = "Grid")
    FVector2D GetLocalGridPosition(int32 X, int32 Y) {return GetLocalGridPosition(FIntPoint(X,Y));}

    FVector2D GetLocalGridPosition(FIntPoint pos);

    ///	@brief SlotMeshes					The meshes drawn to represent the path in real world
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	    UHierarchicalInstancedStaticMeshComponent * SlotMeshes;
    
public:

    UFUNCTION(BlueprintCallable, Category = "Rendering") 
    void DrawSlots();

    UFUNCTION(BlueprintCallable, Category = "Selection", DisplayName ="SelectSlotFromIdx")
    void SelectSlot(int32 idx);

    void SelectSlot(int32 X, int32 Y);
    UFUNCTION(BlueprintCallable, Category = "Selection", DisplayName ="SelectSlotFromXY" )
    void SelectSlotInt32(int32 X, int32 Y) { SelectSlot(X,Y);}
    
    void SelectSlot(FIntPoint coord);
    UFUNCTION(BlueprintCallable, Category = "Selection", DisplayName ="SelectSlotFromCoord")
    void SelectSlotIntPoint(FIntPoint coord) {SelectSlot(coord);}
    
    void SelectSlot(FVector WorldPosition);
    UFUNCTION(BlueprintCallable, Category = "Selection", DisplayName ="SelectSlotFromWorld")
    void SelectSlotFVector(FVector WorldPosition) {SelectSlot(WorldPosition);}
    
    UFUNCTION(BlueprintCallable, Category = "Selection")
    void DeselectSlot();

    
private :

    int32 SelectedSlot;
    bool bSlotIsSelected;
    
    TArray<FGridItemSlot> Slots;


};
