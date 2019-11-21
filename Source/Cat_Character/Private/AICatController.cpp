// Fill out your copyright notice in the Description page of Project Settings.


#include "AICatController.h"
#include "Cat_CharacterPCH.h"
#include "CatNeedInterface.h"
#include "Runtime/Core/Public/Async/ParallelFor.h"
#include "TimerManager.h"


#define  FUNCLOGTEXT(x) *(FString("[") + FString(__FUNCTION__) + FString(" - ") + GetName() + FString("] ") + FString(  x ))
#define  EMPTYIMPLEMENTATION() UE_LOG(LogCat_Character, Display,TEXT("%s"), FUNCLOGTEXT("Empty implementation"))


AAICatController::AAICatController(const FObjectInitializer &ObjectInitializer) 
: Super(ObjectInitializer)
, UpdateNeedDelay(0.1f)
{
	InitNeedsStats();
	InitNeedsDecreaseRate();
	InitPredefinedNeedsCurves();
	InitNeedsRequiereSight();

	// do the next task :
	ReadyToDoTask.AddDynamic(this, &AAICatController::StartNeedAI);
	GoToNeedDone.AddDynamic(this, &AAICatController::UseNeed);
	UseNeedDone.AddDynamic(this, &AAICatController::FinishNeedAI);
	NeedChanged.AddDynamic(this, &AAICatController::ResetTask);

}

void AAICatController::BeginPlay()
{
    Super::BeginPlay();

	ReadyToDoTask.Broadcast();

	GetWorldTimerManager().SetTimer(UpdateNeedTimerHandle, this, &AAICatController::UpdateNeed, UpdateNeedDelay, true);
	
}

void AAICatController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{	
	if(GetWorld() != nullptr)
		if(GetWorldTimerManager().IsTimerActive(UpdateNeedTimerHandle))
			GetWorldTimerManager().ClearTimer(UpdateNeedTimerHandle);
	
	Super::EndPlay(EndPlayReason);
}
 
 


ECatNeed AAICatController::GetMostWantedNeed(float &outValue) const
{
    float MinNeed = BIG_NUMBER;
    ECatNeed retval = ECatNeed::ECN_None;
    for (auto it : NeedsStats)
    {
        if(it.Value < MinNeed)
        {
            MinNeed = it.Value;
            retval = it.Key;
        }
    }
    outValue = MinNeed;
    return retval;
}

TArray<ECatNeed> AAICatController::GetSortedNeeds() const
{
    TArray<ECatNeed> retval;
    auto NeedCopy = NeedsStats;
    NeedCopy.ValueSort([](float A, float B) {
        return A < B; // From  smaller to bigger
    });
    NeedCopy.GetKeys(retval);
    return retval;
}

TArray<ECatNeed> AAICatController::GetCriticalNeeds() const
{
    TArray<ECatNeed> retval;
    auto NeedCopy = NeedsStats;
    for (uint8 it = 1; it < static_cast<uint8>(ECatNeed::ECN_Max); it ++ )
    {
        auto need     = static_cast<ECatNeed>(it);
        auto value    = NeedsStats.Find(need);
        auto critical = NeedsCriticalLevels.Find(need);
        if(value > critical)
            NeedCopy.Remove(need);
    }
    NeedCopy.ValueSort([](float A, float B) { return A < B;});
    NeedCopy.GetKeys(retval);
    return retval;
}

void AAICatController::StartNeedAI_Implementation()
{
	EMPTYIMPLEMENTATION();
}

void AAICatController::GoToNeed_Implementation()
{
	FAIMoveRequest MoveRequest;
	
	MoveRequest.SetGoalLocation(GetNeedActorLocation());
	MoveRequest.SetCanStrafe(false); // cats are weird when they strafe
	MoveRequest.SetAcceptanceRadius(GetNeedActorAcceptanceRadius());
	MoveRequest.SetAllowPartialPath(true); // at least try to go there
	MoveRequest.SetReachTestIncludesAgentRadius(true); // might wanna try with false

	const auto moveorder = MoveTo(MoveRequest, nullptr);
}

void AAICatController::UseNeed_Implementation()
{
	EMPTYIMPLEMENTATION();
}

void AAICatController::FinishNeedAI_Implementation()
{
	EMPTYIMPLEMENTATION();
}

void AAICatController::DoNothing_Implementation()
{
	EMPTYIMPLEMENTATION();
}

void AAICatController::ResetTask_Implementation()
{
	EMPTYIMPLEMENTATION();
	StopMovement();
}


bool AAICatController::FindClosestNeed(ECatNeed need, FVector &location,  AActor * &needActor) const
{
    TArray<AActor *> NeedActors;
    UGameplayStatics::GetAllActorsWithInterface(this,UCatNeedInterface::StaticClass(), NeedActors);
    const FVector ThisLocation = GetPawn() ? GetPawn()->GetActorLocation() : FVector();
    const bool NeedSight = NeedsRequiereSight.Find(need) != nullptr ? *NeedsRequiereSight.Find(need) : false;
    const auto World = GetWorld();

    NeedActors.Sort([&ThisLocation, &World](const AActor& Lhs, const AActor& Rhs) -> bool
    {
        const float DistanceLhs = FVector::DistSquared(Lhs.GetActorLocation(), ThisLocation);
        const float DistanceRhs = FVector::DistSquared(Rhs.GetActorLocation(), ThisLocation);
        const bool SortByDistance = DistanceLhs < DistanceRhs;
        return SortByDistance;
    });

    if(NeedSight)
    {
        for(auto itr :NeedActors)
        {
            if(itr)
            {
                FHitResult OutHit;
                World->LineTraceSingleByChannel(OutHit, ThisLocation, itr->GetActorLocation(), ECC_Visibility);
                if(!OutHit.IsValidBlockingHit())
                {
                   location = itr->GetActorLocation();
                   needActor = itr;
                   return true;
                }
            }
        }
        // there's no valid solution
        location = ThisLocation;
        needActor = nullptr;
        return false;
    }
    
    needActor = NeedActors.IsValidIndex(0) ? NeedActors[0] : nullptr;
    location = NeedActors.IsValidIndex(0) ? NeedActors[0]->GetActorLocation() : ThisLocation ;
    return NeedActors.IsValidIndex(0);  
}

void  AAICatController::InitNeedsStats()
{
    for (uint8 it = 1; it < static_cast<uint8>(ECatNeed::ECN_Max); it ++ )
    {
        if(!NeedsStats.Find(static_cast<ECatNeed>(it)))
        {
            NeedsStats.Add(static_cast<ECatNeed>(it), 1.f);
        }
    }
}

void  AAICatController::InitNeedsDecreaseRate()
{
    for (uint8 it = 1; it < static_cast<uint8>(ECatNeed::ECN_Max); it ++ )
    {
        if(!NeedsDecreaseRate.Find(static_cast<ECatNeed>(it)))
        {
            NeedsDecreaseRate.Add(static_cast<ECatNeed>(it), 0.1f);
        }
    }
}

void AAICatController::InitPredefinedNeedsCurves()
{
     for (uint8 it = 1; it < static_cast<uint8>(ECatNeed::ECN_Max); it ++ )
    {
        if(!PredefinedNeedsCurves.Find(static_cast<ECatNeed>(it)))
        {
        // you need to set property to nullptr, as it is shown as asset in the UE4
        PredefinedNeedsCurves.Add(static_cast<ECatNeed>(it), nullptr/*NewObject<UCurveFloat>(this,UCurveFloat::StaticClass())*/);
        }

    }

}

void AAICatController::InitNeedsCriticalLevels()
{
    for (uint8 it = 1; it < static_cast<uint8>(ECatNeed::ECN_Max); it ++ )
    {
        if(!NeedsCriticalLevels.Find(static_cast<ECatNeed>(it)))
        {
            NeedsCriticalLevels.Add(static_cast<ECatNeed>(it),0.25f);
        }
    }
}

void AAICatController::InitNeedsRequiereSight()
{
    for (uint8 it = 1; it < static_cast<uint8>(ECatNeed::ECN_Max); it ++ )
    {
        if(!NeedsRequiereSight.Find(static_cast<ECatNeed>(it)))
        {
            NeedsRequiereSight.Add(static_cast<ECatNeed>(it),false);
        }
    }

}

#if WITH_EDITOR
void AAICatController::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	InitNeedsStats();
	InitNeedsDecreaseRate();
	InitPredefinedNeedsCurves();
    InitNeedsCriticalLevels();
	InitNeedsRequiereSight();
}
#endif // WITH_EDITOR

void AAICatController::SetCurrentNeed(const ECatNeed newNeed)
{
	if (NeedChosen == newNeed)
		return;

    NeedChosen = newNeed;
    NeedChanged.Broadcast();
}

void AAICatController::SetCurrentNeedActor( AActor* newActor)
{
	if (UseActor == newActor)
		return;

    UseActor = newActor;
    NeedChanged.Broadcast();
}

FVector AAICatController::GetNeedActorLocation() const
{
    const auto interface = Cast<ICatNeedInterface>(UseActor);
    if(interface)
    {
        return UseActor->GetActorLocation() + interface->GetCatNeedLocation();
    }
    return FVector();
}

float AAICatController::GetNeedActorAcceptanceRadius() const
{
	const auto interface = Cast<ICatNeedInterface>(UseActor);
	if (interface)
	{
		return interface->GetCatNeedRadius();
	}
	return 200.f;
}


bool AAICatController::GetNeedIsCritical() const
{
    const auto critlevelptr = NeedsCriticalLevels.Find(NeedChosen);
    const auto needstatptr  = NeedsStats.Find(NeedChosen);
    if(critlevelptr && needstatptr)
    {
        if(*needstatptr < *critlevelptr)
            return true;
        else
            return false;
    }
    return false;
}

void AAICatController::UpdateNeed()
{
    ECatNeed newneed = ECatNeed::ECN_None;
	AActor* needactor = nullptr;
    const auto importantneeds = GetCriticalNeeds();
    if(importantneeds.IsValidIndex(0))
    {
        // Let's use that need:
        newneed = importantneeds[0];
    }
    else    // nothing really urgent to do, will do
    {
        const auto sortedneeds = GetSortedNeeds();
        if(sortedneeds.IsValidIndex(0))
        {
            newneed = sortedneeds[0];
        }
    }
    SetCurrentNeed(newneed);
    if(newneed != ECatNeed::ECN_None)
    {
       
        FVector needlocation;
        if(FindClosestNeed(newneed, needlocation , needactor))
			needactor = nullptr;
        else
            DoNothing();
    }
   
    
	if (needactor == nullptr || newneed == ECatNeed::ECN_None)
	{
		DoNothing();
		return;
	}
   
	SetCurrentNeedActor(needactor);
	SetCurrentNeed(newneed);
}