// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "CatPawn.h"
#include "AICatController.h"

// Sets default values
ACatPawn::ACatPawn()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    AIControllerClass = AAICatController::StaticClass();
}

// Called when the game starts or when spawned
void ACatPawn::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void ACatPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACatPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

AAICatController * ACatPawn::GetCatController() const
{
    return Cast<AAICatController>(GetController);
}
