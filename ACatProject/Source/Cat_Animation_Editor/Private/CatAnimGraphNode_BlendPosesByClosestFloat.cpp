// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "CatAnimGraphNode_BlendPosesByClosestFloat.h"
#include "Kismet2/BlueprintEditorUtils.h"

#define LOCTEXT_NAMESPACE "A3Nodes"

UAnimGraphNode_BlendPosesByClosestFloat::UAnimGraphNode_BlendPosesByClosestFloat(FObjectInitializer const &ObjectInitializer) : Super(ObjectInitializer)
{
	
}


//Title Color!
FLinearColor UAnimGraphNode_BlendPosesByClosestFloat::GetNodeTitleColor() const
{ 
	return FLinearColor(25,1,1,1);
}

//Node Category
FString UAnimGraphNode_BlendPosesByClosestFloat::GetNodeCategory() const
{
	return FString("Blend");
}
FString UAnimGraphNode_BlendPosesByClosestFloat::GetControllerDescription() const
{
	return TEXT("Pose By Closest Float");
}

FText UAnimGraphNode_BlendPosesByClosestFloat::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return LOCTEXT("UAnimGraphNode_BlendPosesByClosestFloat_Title", "Blend Poses by Closest float");
}


FText UAnimGraphNode_BlendPosesByClosestFloat::GetTooltipText() const
{
	return LOCTEXT("UAnimGraphNode_BlendPosesByClosestFloat_Tooltip", "Blend Poses (finding the one closer to float)");
}