// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "Item.h"
#include "ItemData.h"
#include "Components/StaticMeshComponent.h"

FName AItem::MeshName = TEXT("ItemMesh");

AItem::AItem(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
    StaticMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this,MeshName);
    RootComponent = StaticMesh;
}

AItem * AItem::CreateItem(AActor * Owner, const TSubclassOf<AItem> inItemClass,const FItemData &inDataAsset)
{
    const FName name = MakeUniqueObjectName(Owner,inItemClass,inDataAsset.GetName();
    const AActor * spawned = Owner->GetWorld()->SpawnActor( inItemClass,name ,
    FVector(), FRotator(), /*Template*/ nullptr, /*bNoCollisionFail*/ false,
    /*bRemoteOwned*/ false, Owner,/*  APawn* Instigator*/ nullptr, 
    /* bNoFail */ false, /*OverrideLevel*/ nullptr, /* bDeferConstruction*/ false);
    auto item = Cast<AItem>(spawned);
    return item;
}

void AItem::SetFromData(const FItemStaticData &in)
{
    Info = in;
    if(StaticMesh)
    {
        StaticMesh->SetStaticMesh(Info.GetMesh());
    }
}

void AItem::SetFromDataAsset(const UItemData * in)
{
    SetFromData(in->GetData());
}

ECatNeed AItem::GetNeedType() const
{
    return Info.NeedType;
}


void AItem::GetCatNeedEffect(ECatNeed &Type, float &Value) const
{
    Type = GetNeedType();
    Value = GetNeedEfficiency();
}

float AItem::GetNeedEfficiency_Implementation() const
{
    return Info.MaxEfficiency;
}

void AItem::Use(float Amount, AAICatController * Cat)
{
    Use_BP(Amount,Cat);
}
