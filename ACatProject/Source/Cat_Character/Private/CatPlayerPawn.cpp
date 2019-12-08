// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "CatPlayerPawn.h"
#include "Cat_CharacterPCH.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


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

// Called to bind functionality to input
void ACatPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up gameplay key bindings
	// check(PlayerInputComponent);
	// PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	// PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// PlayerInputComponent->BindAxis("MoveForward", this, &ACatPlayerPawn::MoveForward);
	// PlayerInputComponent->BindAxis("MoveRight", this, &ACatPlayerPawn::MoveRight);
 
	// // We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// // "turn" handles devices that provide an absolute delta, such as a mouse.
	// // "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	// PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	// PlayerInputComponent->BindAxis("TurnRate", this, &ACatPlayerPawn::TurnAtRate);
	// PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	// PlayerInputComponent->BindAxis("LookUpRate", this, &ACatPlayerPawn::LookUpAtRate);

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

