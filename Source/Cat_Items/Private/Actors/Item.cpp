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

AItem * AItem::CreateItem(const UObject * worldContextObject, AActor * newOwner, const TSubclassOf<AItem> inItemClass,const FItemStaticData &inDataAsset)
{
    if(!newOwner)
        return nullptr;

    UWorld * world = newOwner->GetWorld() ? newOwner->GetWorld() : worldContextObject->GetWorld();
    if(!world)
        return nullptr;
        
    const auto itemclass = inItemClass.Get() ? inItemClass : AItem::StaticClass();
    FActorSpawnParameters params;
    params.Name = MakeUniqueObjectName(newOwner, itemclass ,inDataAsset.GetName());
    params.bNoFail = false;
    params.Owner = newOwner;
    params.bAllowDuringConstructionScript = true;

    // Template nullptr,
    // bNoCollisionFail false,
    // bRemoteOwned false
    //  APawn* Instigator nullptr
    // bNoFail */ false,
    // OverrideLevel*/ nullptr
    // bDeferConstruction*/ false

    AActor * actor = newOwner->GetWorld()->SpawnActorAbsolute( itemclass, FTransform(), params);
    
    if(actor)
    {
        AItem * item = Cast<AItem>(actor);
        if(item)
        {
             item->SetFromData(inDataAsset);
             return item;
        } 
    }
    return nullptr;
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
