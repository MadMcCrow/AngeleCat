// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridActor.generated.h"

// forward declaration
class AGridActor;
class UGridMeshComponent;
class UStaticMeshComponent;
class UBoxComponent;
class USlotWidgetComponent;

USTRUCT(BlueprintType)
struct FGridItemSlot
{
    GENERATED_BODY()
    friend AGridActor;
    
protected:

    UPROPERTY()
    FIntPoint Coordinate;

    UPROPERTY()
    bool bIsEmpty;

    UPROPERTY()
    AActor * Item;

public:

    FGridItemSlot(FIntPoint coord = FIntPoint(0,0), bool empty = true, AActor * obj = nullptr) : Coordinate(coord), bIsEmpty(empty), Item(obj)
    {}

	void SetCoordinate(int32 idx, int32 XDim, int32 YDim)	{ Coordinate = CoordFromIdx(idx, XDim, YDim);}

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

	bool IsEmpty() const { return bIsEmpty; }
	AActor * GetItem() const { return Item; }
	FIntPoint GetCoordinate() const { return Coordinate; }
};


UCLASS()
class CAT_ITEMS_API AGridActor : public AActor
{
	GENERATED_BODY()

public:

    AGridActor(const FObjectInitializer &ObjectInitializer = FObjectInitializer::Get());

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

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
    TSubclassOf<AItem> BaseItemClass;

private:
    ///	@brief SlotMeshes		The meshes drawn to represent the Grid in real world
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = true))
	    UGridMeshComponent * SlotMeshes;

    ///	@brief SelectedSlotMesh The meshes drawn to represent the selected grid slot in real world
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = true))
	    UStaticMeshComponent * SelectedSlotMesh;

    ///	@brief HoveredSlotMesh	The meshes drawn to represent the hovered grid slot in real world
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = true))
	    UStaticMeshComponent * HoveredSlotMesh;

    ///	@brief HoveredSlotMesh	The meshes drawn to represent the hovered grid slot in real world
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = true))
	    UBoxComponent * GlobalGridCollision;

	///	@brief HoveredSlotMesh	The meshes drawn to represent the hovered grid slot in real world
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = true))
		USlotWidgetComponent * ActiveSlotWidget;


public:

#if WITH_EDITORONLY_DATA 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
    bool bDebug;
#endif // WITH_EDITORONLY_DATA 

    UFUNCTION(BlueprintCallable, Category = "Interaction")
    bool FindLookedAtPositionFromScreen(const FVector2D &screenPosition, const APlayerController* player, FIntPoint &outSlot);

    UFUNCTION(BlueprintPure, Category = "Navigation" )
    FORCEINLINE int32 IdxFromCoordinate(const FIntPoint &coord) { return FGridItemSlot::IndexFromCoord(coord, GridSize.X, GridSize.Y);}

    UFUNCTION(BlueprintPure, Category = "Get")
    AActor * GetItemAtCoordinate(const FIntPoint &coord);

    UFUNCTION(BlueprintPure, Category = "Get")
    TSubclassOf<AItem>  GetItemBaseClass();

    UFUNCTION(BlueprintCallable, Category = "Item")
    void SetActorInSlot(AActor * actor, const FIntPoint &coord);

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

    UPROPERTY()
    TArray<FGridItemSlot> Slots;
    void InitSlotArray();

    void HideSlotInstanceMesh(int32 idx, bool hide = true);
};
