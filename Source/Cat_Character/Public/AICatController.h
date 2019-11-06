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

	UFUNCTION(BlueprintCallable, Category = "Needs")
	virtual ECatNeed GetMostWantedNeed(float &outValue) const;

	UFUNCTION(BlueprintCallable, Category = "Needs")
	virtual TArray<ECatNeed> GetSortedNeeds() const;

	UFUNCTION(BlueprintCallable, Category = "Needs")
	virtual TArray<ECatNeed> GetCriticalNeeds() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Needs")
	void GoToNeed(ECatNeed need);

	UFUNCTION(BlueprintCallable, Category = "Needs")
	virtual bool FindClosestNeed(ECatNeed need, FVector &location, AActor * &needActor) const;




protected:
	UPROPERTY(EditDefaultsOnly, Category = "Needs")
	TMap<ECatNeed,UCurveFloat *> PredefinedNeedsCurves;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Needs")
	TMap<ECatNeed,float> NeedsStats;

	UPROPERTY(EditDefaultsOnly, Category = "Needs")
	TMap<ECatNeed,float> NeedsDecreaseRate;

	UPROPERTY(EditDefaultsOnly, Category = "Needs")
	TMap<ECatNeed,float> NeedsCriticalLevels;

	UPROPERTY(EditDefaultsOnly, Category = "Needs")
	TMap<ECatNeed,bool> NeedsRequiereSight;

	virtual void InitNeedsStats();
	virtual void InitNeedsDecreaseRate();
	virtual void InitPredefinedNeedsCurves();
	virtual void InitNeedsCriticalLevels();
	virtual void InitNeedsRequiereSight();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif //WITH_EDITOR


};
