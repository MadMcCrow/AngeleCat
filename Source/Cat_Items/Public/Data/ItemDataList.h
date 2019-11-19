// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "ItemData.h"
#include "ItemDataList.generated.h"

/**
 * 
 */
UCLASS(blueprintType, Category= "Item|Asset")
class CAT_ITEMS_API UItemDataList : public UPrimaryDataAsset
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (AssetBundles = "Items"), AssetRegistrySearchable)
		TArray<TSoftObjectPtr<UItemData>> Data;

public:

	UFUNCTION(BlueprintPure, Category = "Data")
	TArray<TSoftObjectPtr<UItemData>> GetData() const { return Data; }


	

	UFUNCTION(BlueprintCallable, Category= "statics")
	static UItemData * LoadItemFromSoftPtr_Blocking(TSoftObjectPtr<UItemDataList> list, int32 idx);

	UFUNCTION(BlueprintCallable, Category= "statics")
	static TArray<UItemData *> LoadAllItemsFromSoftPtr_Blocking(TSoftObjectPtr<UItemDataList> list);

	UFUNCTION(BlueprintCallable, Category= "load")
	UItemData * LoadItem_Blocking(int32 idx);

	UFUNCTION(BlueprintCallable, Category= "load")
	TArray<UItemData *> LoadAllItems_Blocking();

	


};