// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CatNeedInterface.h"
#include "AICatController.generated.h"


class UCurveFloat;

/**
 *
 */
UCLASS()
class CAT_CHARACTER_API AAICatController : public AAIController
{
	GENERATED_BODY()

public:

	AAICatController(const FObjectInitializer &ObjectInitializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Needs")
	virtual void GoToNeed(ECatNeed need);

	UFUNCTION(BlueprintCallable, Category = "Needs")
	virtual bool FindClosestNeed(ECatNeed need, FVector &location) const;


protected:
	UPROPERTY(EditDefaultsOnly, Category = "Needs")
	TMap<ECatNeed,UCurveFloat *> PredefinedNeedsCurves;

	UPROPERTY(VisibleAnywhere, Category = "Needs")
	TMap<ECatNeed,float> NeedsStats;

	UPROPERTY(EditDefaultsOnly, Category = "Needs")
	TMap<ECatNeed,float> NeedsDecreaseRate;

	UPROPERTY(EditDefaultsOnly, Category = "Needs")
	TMap<ECatNeed,bool> RequiereSight;


	UFUNCTION()
	virtual void InitNeedsStats();

	UFUNCTION()
	virtual void InitNeedsDecreaseRate();

	UFUNCTION()
	virtual void InitPredefinedNeedsCurves();

	
	UFUNCTION()
	virtual void InitRequiereSight();




};
