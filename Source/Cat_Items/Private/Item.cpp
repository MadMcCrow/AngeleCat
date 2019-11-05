#include "Item.h"
#include "Components/StaticMeshComponent.h"

FName AItem::MeshName = TEXT("ItemMesh");

AItem::AItem(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
    StaticMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this,MeshName);
    RootComponent = StaticMesh;
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

void AItem::Use_Implementation(float Amount, AAICatController * Cat)
{
    
}
