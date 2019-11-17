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

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (ShowOnlyInnerProperties) )
    FItemStaticData Data;

public:

    UFUNCTION(BlueprintPure)
    FItemStaticData GetData() const {return Data;}


};