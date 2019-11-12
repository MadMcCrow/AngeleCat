// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CatNeedInterface.h"
#include "Item.generated.h"

//forward declaration
class UStaticMeshComponent;


USTRUCT(BlueprintType, Category = "Item")
struct FItemStaticData
{
    GENERATED_BODY()
    friend class AItem;
protected:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName StaticName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText LocalizedName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buy")
    int32  Cost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Needs")
    ECatNeed NeedType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Needs")
    float MaxEfficiency;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering")
    UStaticMesh * VisibleMesh;

public:

    UStaticMesh * GetMesh() const {return VisibleMesh;}
};


/**
 * 
 */
UCLASS()
class FItemStaticData UItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()
protected:

    UPROPERTY(BlueprintReadWrite)
    FItemStaticData Data;

public:

    UFUNCTION(BlueprintPure)
    FItemStaticData GetData() const {return Data;}


}