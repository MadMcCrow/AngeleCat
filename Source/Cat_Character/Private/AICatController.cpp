// Fill out your copyright notice in the Description page of Project Settings.


#include "AICatController.h"
#include "Curves/CurveFloat.h"

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

void AAICatController::GoToNeed(ECatNeed need)
{

}

FVector AAICatController::FindClosestNeed(ECatNeed need)
{
    return FVector();
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