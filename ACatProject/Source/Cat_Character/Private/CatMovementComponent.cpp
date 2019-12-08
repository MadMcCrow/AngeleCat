// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved


#include "CatMovementComponent.h"

UCatMovementComponent::UCatMovementComponent() : Super()
{
	BaseRotationRate = 450.f;
    // base configuration : 
	bOrientRotationToMovement = true; // Character moves in the direction of input...	
	RotationRate = FRotator(0.0f, BaseRotationRate, 0.0f); // ...at this rotation rate
	JumpZVelocity = 600.f; // cats are known to jump high
	AirControl = 0.5f; // cats are very agile
}