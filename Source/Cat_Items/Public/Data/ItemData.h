// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "Engine/DataAsset.h"
#include "Item.h"
#include "ItemData.generated.h"

//forward declaration
class UStaticMeshComponent;

/**
 * 
 */
UCLASS(blueprintType, Category= "Item|Asset")
class CAT_ITEMS_API UItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()
protected:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (ShowOnlyInnerProperties, AssetBundles = "Items"),  AssetRegistrySearchable)
    FItemStaticData Data;

public:

    UFUNCTION(BlueprintPure,Category = "Data")
    FItemStaticData GetData() const {return Data;}

    UFUNCTION(BlueprintPure, Category = "Statics")
    static FText GetName(const FItemStaticData &in) {return in.GetTextName();}

    UFUNCTION(BlueprintPure, Category = "Statics")
    static int32 GetCost(const FItemStaticData &in) {return in.GetCost();}

    UFUNCTION(BlueprintPure, Category = "Statics")
    static UStaticMesh * GetMesh(const FItemStaticData &in) {return in.GetMesh();}

    UFUNCTION(BlueprintPure, Category = "Statics")
    static FText GetDescription(const FItemStaticData &in) {return in.GetDescription();}

    UFUNCTION(BlueprintCallable, Category = "Statics|Assets")
    static bool GetAllItemAssetsByClass(TArray<UItemData *> &Assets, UItemData* Asset);

    UFUNCTION(BlueprintCallable, Category = "Statics|Assets")
    static bool GetAllItemAssets(TArray<UItemData *> &Assets);


};