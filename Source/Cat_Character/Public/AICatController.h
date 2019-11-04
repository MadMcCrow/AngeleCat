// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AICatController.generated.h"


class UCurveFloat;

UENUM(BlueprintType)
enum class ECatNeed	 : uint8
{
	ECN_Food	UMETA(DisplayName = "Food"),
	ECN_Water	UMETA(DisplayName = "Water"),
	ECN_Sleep	UMETA(DisplayName = "Sleep"),
	ECN_Play	UMETA(DisplayName = "Play"),
	ECN_Max		UMETA(Hidden)
};


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

	UFUNCTION(BlueprintCallable, Category = "Needs")
	virtual void GoToNeed(ECatNeed need);

	UFUNCTION(BlueprintCallable, Category = "Needs")
	virtual FVector FindClosestNeed(ECatNeed need);



protected:
	UPROPERTY(EditDefaultsOnly, Category = "Needs")
	TMap<ECatNeed,UCurveFloat *> PredefinedNeedsCurves;

	UPROPERTY(VisibleAnywhere, Category = "Needs")
	TMap<ECatNeed,float> NeedsStats;

	UPROPERTY(EditDefaultsOnly, Category = "Needs")
	TMap<ECatNeed,float> NeedsDecreaseRate;


	UFUNCTION()
	virtual void InitNeedsStats();

	UFUNCTION()
	virtual void InitNeedsDecreaseRate();

	UFUNCTION()
	virtual void InitPredefinedNeedsCurves();



	
};
