// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved


#include "CatInputComponent.h"
#include "Cat_PlayerPCH.h"
#include "GameFramework/Character.h"
#include "CatPlayerPawn.h"

UCatInputComponent::UCatInputComponent(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
    JumpAction = TEXT("Jump");
    MoveForwardAxis = TEXT("MoveForward");
    MoveRightAxis  = TEXT("MoveRight");
    TurnAction = TEXT("Turn");
    TurnRateAction = TEXT("TurnRate");
    LookUpAction = TEXT("LookUp");
    LookUpRateAction = TEXT("LookUpRate");

}


void UCatInputComponent::BindInputsToCharacter(ACharacter * characterTarget)
{
    if(!characterTarget)
        return;

	BindAction(JumpAction, IE_Pressed, characterTarget, &ACharacter::Jump);
	BindAction(JumpAction, IE_Released, characterTarget, &ACharacter::StopJumping);

    
	BindAxis(TurnAction,        characterTarget, &APawn::AddControllerYawInput);
	BindAxis(LookUpAction,      characterTarget, &APawn::AddControllerPitchInput);

    auto cat = Cast<ACatPlayerPawn>(characterTarget);
    if(cat != nullptr)
    {
	    BindAxis(MoveForwardAxis,   cat, &ACatPlayerPawn::MoveForward);
	    BindAxis(MoveRightAxis,     cat, &ACatPlayerPawn::MoveRight);
        // // We have 2 versions of the rotation bindings to handle different kinds of devices differently
	    // // "turn" handles devices that provide an absolute delta, such as a mouse.
	    // // "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
        BindAxis(TurnRateAction,    cat, &ACatPlayerPawn::TurnAtRate);
        BindAxis(LookUpRateAction,  cat, &ACatPlayerPawn::LookUpAtRate);
    }
}

void UCatInputComponent::BindInputsToController(APlayerController * controller)
{

}