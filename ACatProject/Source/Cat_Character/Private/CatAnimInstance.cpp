// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved


#include "CatAnimInstance.h"
#include "Cat_CharacterPCH.h"
#include "CatMovementComponent.h"
#include "CatPawn.h"


void UCatAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);
    auto cat = TryGetOwningCat();
    if(cat && cat->GetCatMovementComponent())
    {
        Velocity = cat->GetVelocity();
        bIsJumping = cat->GetCatMovementComponent()->IsFalling();
        bIsCrouching = cat->GetCatMovementComponent()->IsCrouching();
        bIsSitting =  cat->GetCatMovementComponent()->IsSitting();
    }
    else
    {
        Velocity = FVector::ZeroVector;
        bIsSitting = true;
        bIsJumping = false;
        bIsCrouching = true;
    }
}

ACatPawn *  UCatAnimInstance::TryGetOwningCat(bool &isValid) const
{
    auto cat = TryGetOwningCat();
    isValid = cat != nullptr;
    return cat;
}

ACatPawn *  UCatAnimInstance::TryGetOwningCat() const
{
    auto cat = Cast<ACatPawn>(TryGetPawnOwner());
    return cat;
}