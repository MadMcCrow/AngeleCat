// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CatPlayerStatics.generated.h"


/**
 *	@brief UCatPlayerStatics		Static class to add more functions related to Player interactions
 */
UCLASS(Category = "Player")
class CAT_PLAYER_API UCatPlayerStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static FVector2D MouseScreenBorderMove(UObject * WorldContextObject, float xThreshold,float yThreshold, bool invertXY = false, bool allowOutsideMovement = true);
	
};
