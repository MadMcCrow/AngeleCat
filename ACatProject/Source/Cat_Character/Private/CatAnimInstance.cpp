// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved


#include "CatAnimInstance.h"
#include "Cat_CharacterPCH.h"
#include "CatMovementComponent.h"
#include "CatPawn.h"

float UCatAnimInstance::MinWalkSpeed = KINDA_SMALL_NUMBER;

void UCatAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);
    const auto cat = TryGetOwningCat();
    if(cat && cat->GetCatMovementComponent())
    {
        Velocity		 = cat->GetVelocity();
		Direction		 = cat->GetActorForwardVector();
        bIsJumping		 = cat->GetCatMovementComponent()->IsFalling();
        bIsCrouching	 = cat->GetCatMovementComponent()->IsCrouching();
        bIsSitting		 = cat->GetCatMovementComponent()->IsSitting();
		bIsInTurnInPlace = cat->GetCatMovementComponent()->CanPlayTurnInPlace();
		TurnInPlaceAngle = cat->GetCatMovementComponent()->GetTurnInPlaceRotation().Yaw;


		cat->GetCatMovementComponent()->SetIsInTurnInPlaceAnim(bIsInTurnInPlace);
    }
    else
    {
        Velocity	 = FVector::ZeroVector;
        bIsSitting	 = true;
        bIsJumping	 = false;
        bIsCrouching = true;
		bIsInTurnInPlace = false;
    }
	
}

ACatPawn *  UCatAnimInstance::TryGetOwningCat(bool &isValid) const
{
    const auto cat = TryGetOwningCat();
    isValid = cat != nullptr;
    return cat;
}

ACatPawn *  UCatAnimInstance::TryGetOwningCat() const
{
    const auto cat = Cast<ACatPawn>(TryGetPawnOwner());
    return cat;
}