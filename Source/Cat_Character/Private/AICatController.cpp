// Fill out your copyright notice in the Description page of Project Settings.


#include "AICatController.h"
#include "Curves/CurveFloat.h"
#include "Kismet/GameplayStatics.h"
#include "CatNeedInterface.h"
#include "Engine/World.h"

AAICatController::AAICatController(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
    InitNeedsDecreaseRate();
    InitNeedsStats();
    InitPredefinedNeedsCurves();
}

void AAICatController::BeginPlay()
{
    Super::BeginPlay();
}

void AAICatController::GoToNeed_Implementation(ECatNeed need)
{

}

bool AAICatController::FindClosestNeed(ECatNeed need, FVector &location) const
{
    TArray<AActor *> NeedActors;
    UGameplayStatics::GetAllActorsWithInterface(this,UCatNeedInterface::StaticClass(), NeedActors);
    const FVector ThisLocation = GetPawn() ? GetPawn()->GetActorLocation() : FVector();
    const bool NeedSight = RequiereSight.Find(need) != nullptr ? *RequiereSight.Find(need) : false;
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
                   return true;
                }
            }
        }
        // there's no valid solution
        location = ThisLocation;
        return false;
    }
    location = NeedActors.IsValidIndex(0) ? NeedActors[0]->GetActorLocation() : ThisLocation ;
    return NeedActors.IsValidIndex(0);
}

void  AAICatController::InitNeedsStats()
{
    for (uint8 it = 1; it < static_cast<uint8>(ECatNeed::ECN_Max); it ++ )
    {
        NeedsStats.Add(static_cast<ECatNeed>(it), 1.f);
    }
}

void  AAICatController::InitNeedsDecreaseRate()
{
    for (uint8 it = 1; it < static_cast<uint8>(ECatNeed::ECN_Max); it ++ )
    {
        NeedsDecreaseRate.Add(static_cast<ECatNeed>(it), 0.1f);
    }
}

void AAICatController::InitPredefinedNeedsCurves()
{
     for (uint8 it = 1; it < static_cast<uint8>(ECatNeed::ECN_Max); it ++ )
    {
        PredefinedNeedsCurves.Add(static_cast<ECatNeed>(it),NewObject<UCurveFloat>(this,UCurveFloat::StaticClass()));
    }

}

void AAICatController::InitRequiereSight()
{
     for (uint8 it = 1; it < static_cast<uint8>(ECatNeed::ECN_Max); it ++ )
    {
        RequiereSight.Add(static_cast<ECatNeed>(it),false);
    }

}