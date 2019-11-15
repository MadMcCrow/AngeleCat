// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "GridMeshComponent.generated.h"

/**
 * 
 */
UCLASS()
class CAT_ITEMS_API UGridMeshComponent : public UInstancedStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	
	virtual bool HideInstance(int32 InstanceIndex);
	virtual bool ShowInstance(int32 InstanceIndex);

	virtual int32 AddInstance(const FTransform& InstanceTransform) override;
	virtual void ClearInstances() override;
	
protected:
	virtual int32 AddInstanceNum(const FTransform& InstanceTransform, int32 Num);
	virtual int32 AddInstanceNumWorldSpace(const FTransform& WorldTransform, int32 Num);

	UPROPERTY()
	TMap<int32, FTransform>	HiddenInstances;

	UPROPERTY()
	TMap<int32, FTransform>	VisibleInstances;

};
