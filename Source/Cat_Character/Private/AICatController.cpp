// Fill out your copyright notice in the Description page of Project Settings.


#include "AICatController.h"
#include "Curves/CurveFloat.h"
#include "Kismet/GameplayStatics.h"
#include "CatNeedInterface.h"
#include "Engine/World.h"
#include "Runtime/Core/Public/Async/ParallelFor.h"

AAICatController::AAICatController(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
	InitNeedsStats();
	InitNeedsDecreaseRate();
	InitPredefinedNeedsCurves();
	InitNeedsRequiereSight();
}

void AAICatController::BeginPlay()
{
    Super::BeginPlay();
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


void AAICatController::GoToNeed_Implementation(ECatNeed need)
{

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

    needActor = NeedActors[0];
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