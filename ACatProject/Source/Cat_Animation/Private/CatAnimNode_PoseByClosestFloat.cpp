#include "CatAnimNode_PoseByClosestFloat.h"


FAnimNode_PoseByClosestFloat::FAnimNode_PoseByClosestFloat()
	: FAnimNode_Base(), SampleFloat(0.f)
{
}

void FAnimNode_PoseByClosestFloat::Initialize_AnyThread(const FAnimationInitializeContext & Context)
{
	//Init the Inputs
	for(FPoseFloatValue it : Poses)
		it.Initialize(Context);
	
}

void FAnimNode_PoseByClosestFloat::CacheBones_AnyThread(const FAnimationCacheBonesContext & Context)
{
	for(FPoseFloatValue it : Poses)
		it.CacheBones(Context);
}

void FAnimNode_PoseByClosestFloat::Update_AnyThread(const FAnimationUpdateContext & Context)
{
    //***************************************
	// Evaluate Graph, see AnimNode_Base, AnimNodeBase.h
	//***************************************
	GetEvaluateGraphExposedInputs().Execute(Context);
	
	// Do Updates 

	//Try To Update As Few of the Inputs As You Can
	
	//************************************************
	// FPoseLinkBase::Update Active Pose - this is what makes 
    //the glowing line thing happen and animations loop
	//***********************************************
	Poses.Sort([&](const FPoseFloatValue &A, const FPoseFloatValue &B){
		return FMath::Abs(A.Value - SampleFloat) < FMath::Abs(B.Value - SampleFloat);
	});

	if(Poses.IsValidIndex(0))
		Poses[0].Update(Context);
}

void FAnimNode_PoseByClosestFloat::Evaluate_AnyThread(FPoseContext & Output)
{
	// Return Base Pose, Un Modified 

	Poses.Sort([&](const FPoseFloatValue &A, const FPoseFloatValue &B){
		return FMath::Abs(A.Value - SampleFloat) < FMath::Abs(B.Value - SampleFloat);
	});

	if(Poses.IsValidIndex(0))
		Poses[0].Evaluate(Output);
	//Evaluate is returning the Output to this function,
	//which is returning the Output to the rest of the Anim Graph
	
	//In this case, we are passing the Output out variable into the BasePose
	
	//Basically saying, give us back the unmodified Base Pose
	
	//i.e, the bulk of your anim tree.
}