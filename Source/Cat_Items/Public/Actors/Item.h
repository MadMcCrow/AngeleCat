// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "GameFramework/Actor.h"
#include "CatNeedInterface.h"
#include "Item.generated.h"

class AAICatController;
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

    FORCEINLINE UStaticMesh * GetMesh() const   {return VisibleMesh;}
    FORCEINLINE FName GetName() const           {return StaticName;}
    FORCEINLINE FText GetTextName() const       {return LocalizedName;}
    FORCEINLINE FText GetDescription() const    {return Description;}
    FORCEINLINE int32 GetCost() const           {return Cost;}
    FORCEINLINE ECatNeed GetType() const        {return NeedType;}
    FORCEINLINE float GetEfficiency() const     {return MaxEfficiency;}
};

UCLASS()
class AItem : public AActor, public ICatNeedInterface
{
    GENERATED_BODY()

public:
    AItem(const FObjectInitializer &ObjectInitializer = FObjectInitializer::Get());

    UFUNCTION(BlueprintCallable, Category = "Create", meta = (WorldContext="worldContextObject"))
    static AItem * CreateItem(const UObject * worldContextObject, AActor * newOwner, const TSubclassOf<AItem> inItemClass,const FItemStaticData &inDataAsset);

    UFUNCTION(BlueprintCallable, Category = "Setup")
    void SetFromData(const FItemStaticData &in);

    UFUNCTION(BlueprintCallable, Category = "Setup")
    void SetFromDataAsset(const UItemData * in);

    virtual ECatNeed GetNeedType() const override;
    virtual void GetCatNeedEffect(ECatNeed &Type, float &Value) const override;

    UFUNCTION(BlueprintNativeEvent, Category = "Needs")
    float GetNeedEfficiency() const;

    UFUNCTION(BlueprintImplementableEvent, Category = "Needs")
    void Use_BP(float Amount, AAICatController * Cat);

	virtual FVector GetCatNeedLocation() const override { return UseLocation; }
    virtual void Use(float Amount, AAICatController * Controller) override;

    UFUNCTION(BlueprintCallable, Category = "Setup")
    FORCEINLINE FItemStaticData GetStaticData() const {return Info;}


protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Need")
    UItemData * ItemAsset;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Need")
    FItemStaticData Info;

    UPROPERTY(EditAnywhere, BlueprintReadOnly,meta = (MakeEditWidget), Category = "Need")
    FVector UseLocation;

public:
    static FName MeshName;
private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
    UStaticMeshComponent * StaticMesh;



};
