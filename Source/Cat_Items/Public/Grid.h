// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grid.generated.h"

// forward declaration
class UHierarchicalInstancedStaticMeshComponent;
class UStaticMeshComponent;
class UBoxComponent;

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

    virtual void OnConstruction(const FTransform& transform) override;
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
    FIntPoint GridSize;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
    FVector2D ElementSize;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid")
    FVector GridOffset;

protected:

    UFUNCTION(BlueprintCallable, Category = "Grid")
    FVector2D GetLocalGridPosition(int32 X, int32 Y) const {return GetLocalGridPosition(FIntPoint(X,Y));}

    FVector2D GetLocalGridPosition(const FIntPoint &pos) const;

private:
    ///	@brief SlotMeshes		The meshes drawn to represent the Grid in real world
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = true))
	    UHierarchicalInstancedStaticMeshComponent * SlotMeshes;

    ///	@brief SelectedSlotMesh The meshes drawn to represent the selected grid slot in real world
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = true))
	    UStaticMeshComponent * SelectedSlotMesh;

    ///	@brief HoveredSlotMesh	The meshes drawn to represent the hovered grid slot in real world
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = true))
	    UStaticMeshComponent * HoveredSlotMesh;

    ///	@brief HoveredSlotMesh	The meshes drawn to represent the hovered grid slot in real world
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = true))
	    UBoxComponent * GlobalGridCollision;


public:

    UFUNCTION(BlueprintCallable, Category = "Interaction")
    bool FindLookedAtPositionFromScreen(const FVector2D &screenPosition, const APlayerController* player, FIntPoint &outSlot);

    UFUNCTION(BlueprintPure, Category = "Navigation" )
    FORCEINLINE int32 IdxFromCoordinate(const FIntPoint &coord) { return FGridItemSlot::IndexFromCoord(coord, GridSize.X, GridSize.Y);}

    UFUNCTION(BlueprintCallable, Category = "Rendering")
    void DrawSlots();

    UFUNCTION(BlueprintCallable, Category = "Rendering")
    void UpdateSlots();


    UFUNCTION(BlueprintCallable, Category = "Geometry")
    void SetBoundingBox();

    FTransform GetSlotIdxWorldSpace(int32 idx) const;

    UFUNCTION(BlueprintCallable, Category = "Navigation|Selection", DisplayName ="SelectSlotFromIdx")
    void SelectSlot(int32 idx);

    void SelectSlot(int32 X, int32 Y);
    UFUNCTION(BlueprintCallable, Category = "Navigation|Selection", DisplayName ="SelectSlotFromXY" )
    void SelectSlotInt32(int32 X, int32 Y) { SelectSlot(X,Y);}

    void SelectSlot(FIntPoint coord);
    UFUNCTION(BlueprintCallable, Category = "Navigation|Selection", DisplayName ="SelectSlotFromCoord")
    void SelectSlotIntPoint(FIntPoint coord) {SelectSlot(coord);}

    void SelectSlot(FVector WorldPosition);
    UFUNCTION(BlueprintCallable, Category = "Navigation|Selection", DisplayName ="SelectSlotFromWorld")
    void SelectSlotFVector(FVector WorldPosition) {SelectSlot(WorldPosition);}

    UFUNCTION(BlueprintCallable, Category = "Navigation|Selection")
    void DeselectSlot();


    UFUNCTION(BlueprintCallable, Category = "Navigation|Hover", DisplayName ="HoverSlotFromIdx")
    void HoverSlot(int32 idx);

    void HoverSlot(int32 X, int32 Y);
    UFUNCTION(BlueprintCallable, Category = "Navigation|Hover", DisplayName ="HoverSlotFromXY" )
    void HoverSlotInt32(int32 X, int32 Y) { HoverSlot(X,Y);}

    void HoverSlot(FIntPoint coord);
    UFUNCTION(BlueprintCallable, Category = "Navigation|Hover", DisplayName ="HoverSlotFromCoord")
    void HoverSlotIntPoint(FIntPoint coord) {HoverSlot(coord);}

    void HoverSlot(FVector WorldPosition);
    UFUNCTION(BlueprintCallable, Category = "Navigation|Hover", DisplayName ="HoverSlotFromWorld")
    void HoverSlotFVector(FVector WorldPosition) {HoverSlot(WorldPosition);}

    UFUNCTION(BlueprintCallable, Category = "Navigation" )
    FIntPoint CoordFromWorldSpace(const FVector &WorldPosition);

    UFUNCTION(BlueprintPure, Category = "Navigation")
    FORCEINLINE FIntPoint Left(const FIntPoint &coord)  {return FIntPoint((coord.X -1)% GridSize.X, coord.Y);}
    UFUNCTION(BlueprintPure, Category = "Navigation")
    FORCEINLINE FIntPoint Right(const FIntPoint &coord) {return FIntPoint((coord.X +1)% GridSize.X, coord.Y);}
    UFUNCTION(BlueprintPure, Category = "Navigation")
    FORCEINLINE FIntPoint Up(const FIntPoint &coord)    {return FIntPoint(coord.X, (coord.Y -1)% GridSize.Y);}
    UFUNCTION(BlueprintPure, Category = "Navigation")
    FORCEINLINE FIntPoint Down(const FIntPoint &coord)  {return FIntPoint(coord.X, (coord.Y +1)% GridSize.Y);}


private :

    UPROPERTY()
    int32 SelectedSlot;

    UPROPERTY(transient)
    int32 PreviousSelectedSlot;

    UPROPERTY()
    int32 HoveredSlot;

    UPROPERTY(transient)
    int32 PreviousHoveredSlot;

    bool bSlotIsSelected;

    TArray<FGridItemSlot> Slots;

    void HideSlotInstanceMesh(int32 idx, bool hide = true);

};
