// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "CatPlayerState.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFundChange);

//struct CAT_PLAYER_API FPlayerPurchaseInfo

/**
 * 
 */
UCLASS()
class CAT_PLAYER_API ACatPlayerState : public APlayerState
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Funds")
	float MoneyScore;

public:

	UFUNCTION(BlueprintPure, Category = "Funds")
	float GetMoney() const;

	UFUNCTION(BlueprintPure, Category = "Funds|Purchase")
	bool CanSpend(float amount) const;

	UFUNCTION(BlueprintCallable, Category = "Funds|Purchase")
	bool TrySpend(float amount);

	UFUNCTION(BlueprintCallable, Category = "Funds|Earn")
	void Earn(float amount);

	UPROPERTY(BlueprintAssignable, Category = "Funds|Events")
	FFundChange OnIncreasedEvent;

	UPROPERTY(BlueprintAssignable, Category = "Funds|Events")
	FFundChange OnDecreasedEvent;
	
};
