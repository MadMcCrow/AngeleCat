// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "CatNeedInterface.generated.h"


UENUM(BlueprintType)
enum class ECatNeed	 : uint8
{
    ECN_None	UMETA(Hidden),
	ECN_Food	UMETA(DisplayName = "Food"),
	ECN_Water	UMETA(DisplayName = "Water"),
	ECN_Sleep	UMETA(DisplayName = "Sleep"),
	ECN_Play	UMETA(DisplayName = "Play"),
	ECN_Max		UMETA(Hidden)
};


UINTERFACE(Category = "Needs")
class CAT_CHARACTER_API UCatNeedInterface : public UInterface
{
	//GENERATED_UINTERFACE_BODY()
    GENERATED_BODY()
};

class CAT_CHARACTER_API ICatNeedInterface
{
	//GENERATED_IINTERFACE_BODY()
	GENERATED_BODY()
public:


    UFUNCTION(BlueprintPure, Category = "Needs")
    ECatNeed GetNeedType() const PURE_VIRTUAL(ICatNeedInterface::GetCatNeedEffect, return ECatNeed::ECN_None;);

    UFUNCTION(BlueprintPure)
    void GetCatNeedEffect(ECatNeed &Type, float &Value) const PURE_VIRTUAL(ICatNeedInterface::GetCatNeedEffect,;);

};