// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CatNeedInterface.h"
#include "AICatController.generated.h"


class UCurveFloat;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdateCatTask);

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

public:

    UPROPERTY(BlueprintAssignable, Category = "Task|Event")
    FUpdateCatTask ReadyToDoTask;

    UPROPERTY(BlueprintAssignable, Category = "Task|Event")
    FUpdateCatTask FindNeedDone;

    UPROPERTY(BlueprintAssignable, Category = "Task|Event")
    FUpdateCatTask GoToNeedDone;

    UPROPERTY(BlueprintAssignable, Category = "Task|Event")
    FUpdateCatTask UseNeedDone;

    UPROPERTY(BlueprintAssignable, Category = "Task|Event")
    FUpdateCatTask NeedChanged;

protected:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Task")
	void FindNeed();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Task")
	void GoToNeed();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Task")
	void UseNeed();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Task")
	void DoNothing();

protected:

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, BlueprintSetter=SetCurrentNeed, Category = "Task|Data", transient)
    ECatNeed NeedChosen;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, BlueprintSetter=SetCurrentNeedActor,  Category = "Task|Data", DisplayName = "NeedActor", transient)
    AActor* UseActor;

    UFUNCTION(BlueprintCallable, BlueprintSetter, Category = "Task|Data")
    void SetCurrentNeed(const ECatNeed newNeed);

    UFUNCTION(BlueprintCallable, BlueprintSetter, Category = "Task|Data")
    void SetCurrentNeedActor(const AActor* newActor);

    UFUNCTION(BlueprintPure, Category = "Task|Data")
    FVector GetNeedActorLocation() const;

    UFUNCTION(BlueprintPure, Category = "Task|Data")
    bool GetNeedIsCritical() const;

private:
    virtual void UpdateNeed();

};
