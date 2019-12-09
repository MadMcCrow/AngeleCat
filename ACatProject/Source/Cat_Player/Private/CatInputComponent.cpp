// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved


#include "CatInputComponent.h"
#include "Cat_PlayerPCH.h"
#include "GameFramework/Character.h"
#include "CatPlayerPawn.h"

UCatInputComponent::UCatInputComponent(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
    JumpAction       = TEXT("Jump");
    RunAction        = TEXT("Run");
    MoveForwardAxis  = TEXT("MoveForward");
    MoveRightAxis    = TEXT("MoveRight");
    TurnAxis         = TEXT("Turn");
    TurnRateAxis     = TEXT("TurnRate");
    LookUpAxis       = TEXT("LookUp");
    LookUpRateAxis   = TEXT("LookUpRate");
}


void UCatInputComponent::BindInputsToCharacter(ACharacter * characterTarget)
{
    if(!characterTarget)
        return;

	BindAction(JumpAction, IE_Pressed, characterTarget, &ACharacter::Jump);
	BindAction(JumpAction, IE_Released, characterTarget, &ACharacter::StopJumping);

    
	BindAxis(TurnAxis,        characterTarget, &APawn::AddControllerYawInput);
	BindAxis(LookUpAxis,      characterTarget, &APawn::AddControllerPitchInput);

    auto cat = Cast<ACatPlayerPawn>(characterTarget);
    if(cat != nullptr)
    {
	    BindAxis(MoveForwardAxis,   cat, &ACatPlayerPawn::MoveForward);
	    BindAxis(MoveRightAxis,     cat, &ACatPlayerPawn::MoveRight);
        // // We have 2 versions of the rotation bindings to handle different kinds of devices differently
	    // // "turn" handles devices that provide an absolute delta, such as a mouse.
	    // // "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
        BindAxis(TurnRateAxis,    cat, &ACatPlayerPawn::TurnAtRate);
        BindAxis(LookUpRateAxis,  cat, &ACatPlayerPawn::LookUpAtRate);

        // Running
        BindAction(RunAction, IE_Pressed, cat, &ACatPlayerPawn::Run);
        BindAction(RunAction, IE_Pressed, cat, &ACatPlayerPawn::StopRunning);
    }
}

void UCatInputComponent::BindInputsToController(APlayerController * controller)
{

}