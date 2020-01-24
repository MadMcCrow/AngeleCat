// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "Animation/AnimNodeBase.h"
#include "CatAnimNode_PoseByClosestFloat.generated.h"

USTRUCT(BlueprintType)
struct FPoseFloatValue : public FPoseLink
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links, meta=(PinShownByDefault))
	float Value;

};

USTRUCT(BlueprintType)
struct CAT_ANIMATION_API FAnimNode_PoseByClosestFloat : public FAnimNode_Base
{
	GENERATED_BODY()

public:

	FAnimNode_PoseByClosestFloat();

	//  FPoseLink - this can be any combination 
    //  of other nodes, not just animation sequences
	//	so you could have an blend space leading into 
    //  a layer blend per bone to just use the arm
	//	and then pass that into the PoseLink
	
	/** Base Pose - This Can Be Entire Anim Graph Up To This Point, or Any Combination of Other Nodes*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links, meta = (PinShownByDefault))
	TArray<FPoseFloatValue> Poses;
	
	/** Sample Property That Will Show Up as a Pin */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links, meta=(PinShownByDefault))
	float SampleFloat;
	
// FAnimNode_Base interface
public:
	
	// FAnimNode_Base interface
 virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;
 virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext & Context) override;
 virtual void Update_AnyThread(const FAnimationUpdateContext & Context) override;
 virtual void Evaluate_AnyThread(FPoseContext& Output) override;
	// End of FAnimNode_Base interface



protected:
	virtual FString GetNodeName(FNodeDebugData& DebugData) { return DebugData.GetNodeName(this); }


};