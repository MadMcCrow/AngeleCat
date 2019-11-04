#include "Item.h"

AItem::AItem(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
    
}

ECatNeed AItem::GetNeedType()
{
    return Info.NeedType;
}


void AItem::GetCatNeedEffect(ECatNeed &Type, float &Value)
{
    Type = GetNeedType();
    Value = GetNeedEfficiency();
}

float AItem::GetNeedEfficiency_Implementation()
{
    return Info.MaxEfficiency;
}

void AItem::Use_Implementation(float Amount, AAICatController * Cat)
{
    
}
