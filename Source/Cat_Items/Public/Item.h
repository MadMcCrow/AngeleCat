// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AICatController.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

//forward declaration
class UStaticMeshComponent;


USTRUCT(BlueprintType, Category = "Item")
struct FItemStaticData
{
    GENERATED_BODY()
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

};


UCLASS()
class AItem : public AActor, public ICatNeedInterface
{
    GENERATED_BODY()

public:
    AItem(const FObjectInitializer &ObjectInitializer = FObjectInitializer::Get());

    UFUNCTION(BlueprintPure, Category = "Needs")
    ECatNeed GetNeedType() const override;

    UFUNCTION(BlueprintPure, Category = "Needs")
    void GetCatNeedEffect(ECatNeed &Type, float &Value) const override;

    UFUNCTION(BlueprintNativeEvent, Category = "Needs")
    float GetNeedEfficiency() const;

    UFUNCTION(BlueprintNativeEvent, Category = "Needs")
    void Use(float Amount, AAICatController * Cat);

protected:
    UPROPERTY(EditDefaultsOnly)
    FItemStaticData Info;

    UPROPERTY(EditDefaultsOnly, Category = "Rendering")
    UStaticMeshComponent * ItemMesh;
};