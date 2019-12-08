// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved


#include "CatAnimInstance.h"
#include "Cat_CharacterPCH.h"
#include "CatPawn.h"


void UCatAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    auto cat = TryGetOwningCat();
    Velocity = cat->GetVelocity();
    bIsJumping = cat->GetMovementComponent()->IsFalling();
    bIsCrouching = cat->GetMovementComponent()->IsCrouching();

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