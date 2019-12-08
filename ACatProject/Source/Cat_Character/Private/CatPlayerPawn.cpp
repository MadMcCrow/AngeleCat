// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "CatPlayerPawn.h"
#include "Cat_CharacterPCH.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "CatInputComponent.h"
#include "GameFramework/PlayerController.h"


FName ACatPlayerPawn::SpringArmName = TEXT("CameraBoom");
FName ACatPlayerPawn::CameraCompName = TEXT("FollowCamera");

ACatPlayerPawn::ACatPlayerPawn() : Super()
{
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(SpringArmName);
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 100.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(CameraCompName);
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

UInputComponent * ACatPlayerPawn::CreatePlayerInputComponent()
{
	// Super does this :
	//	static const FName InputComponentName(TEXT("PawnInputComponent0"));
	//	return NewObject<UInputComponent>(this, InputComponentName);

	// We could try to do something like this :
	// auto PC = Cast<APlayerController>(GetOwner());
	// if(PC)
	// {
	//	return PC->GetInputComponent();
	// }
	static const FName InputComponentName(TEXT("PawnInputComponent0"));
	return NewObject<UCatInputComponent>(this, InputComponentName);
}

// Called to bind functionality to input
void ACatPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	auto catinput = Cast<UCatInputComponent>(PlayerInputComponent);
	if(catinput)
		catinput->BindInputsToCharacter(this);
}

void ACatPlayerPawn::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ACatPlayerPawn::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

