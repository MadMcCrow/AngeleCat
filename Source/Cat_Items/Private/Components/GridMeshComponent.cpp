// Fill out your copyright notice in the Description page of Project Settings.


#include "GridMeshComponent.h"


bool UGridMeshComponent::HideInstance(int32 InstanceIndex)
{
    const FTransform * InstT =  VisibleInstances.Find(InstanceIndex);
    if(InstT)
    {
        HiddenInstances.Add(InstanceIndex, *InstT);
        VisibleInstances.Remove(InstanceIndex);
        RemoveInstance(InstanceIndex);
        return true;
    }
    return false;
}

bool UGridMeshComponent::ShowInstance(int32 InstanceIndex)
{
    const FTransform * InstT = HiddenInstances.Find(InstanceIndex);
    if(InstT)
    {
        AddInstanceNum(*InstT, InstanceIndex);
        return true;
    }
    return false;
}

int32 UGridMeshComponent::AddInstance(const FTransform& InstanceTransform)
{
    int32 idx = UInstancedStaticMeshComponent::AddInstance(InstanceTransform);
    VisibleInstances.Add(idx,InstanceTransform);

    const FTransform * InstT = HiddenInstances.Find(idx);
    if(InstT)    { HiddenInstances.Remove(idx); }

    return idx;
}

void UGridMeshComponent::ClearInstances()
{
    UInstancedStaticMeshComponent::ClearInstances();
    // Clear stored data
    HiddenInstances.Empty();
    VisibleInstances.Empty();
}

int32 UGridMeshComponent::AddInstanceNum(const FTransform& InstanceTransform, int32 Num)
{
    if(Num <= PerInstanceSMData.Num())
    {
        VisibleInstances.Add(Num,InstanceTransform);
        const FTransform * InstT = HiddenInstances.Find(Num);
        if(InstT) { HiddenInstances.Remove(Num); }

        return AddInstanceInternal(Num, nullptr, InstanceTransform);
    }
    return -1;
}

int32 UGridMeshComponent::AddInstanceNumWorldSpace(const FTransform& WorldTransform, int32 Num)
 {
	// Transform from world space to local space
     if(Num <= PerInstanceSMData.Num())
     {
        FTransform RelativeTM = WorldTransform.GetRelativeTransform(GetComponentTransform());
	    return AddInstanceNum(RelativeTM, Num);
     }
     return -1;
}