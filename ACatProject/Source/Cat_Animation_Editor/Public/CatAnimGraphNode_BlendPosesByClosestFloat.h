// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
//#include "AnimGraphNode_Base.h"
#include "CatAnimNode_PoseByClosestFloat.h"
#include "AnimGraph/Classes/AnimGraphNode_Base.h"
#include "CatAnimGraphNode_BlendPosesByClosestFloat.generated.h"

UCLASS(MinimalAPI)
class UAnimGraphNode_BlendPosesByClosestFloat : public UAnimGraphNode_Base
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, Category=Settings)
	FAnimNode_PoseByClosestFloat Node;

public:
	// UEdGraphNode interface
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual FString GetNodeCategory() const override;
	virtual FText GetTooltipText() const override;
	// End of UEdGraphNode interface

protected:
	virtual FString GetControllerDescription() const;
	
};

