// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved


#include "CatPlayerController.h"
#include "Components/Widget.h"
#include "CatPlayerStatics.h"
#include "CatPlayerCameraPawn.h"
//#include "Engine/World.h"
//#include "GameFramework/Character.h"
//#include "Kismet/GameplayStatics.h"


ACatPlayerController::ACatPlayerController(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
}

void ACatPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void ACatPlayerController::Tick(float deltaTime)
{
    Super::Tick(deltaTime);
}

void ACatPlayerController::BeginPlay()
{
    Super::BeginPlay();
    if(IsUsingMouse())
        EnableMouse(nullptr);
}

bool ACatPlayerController::IsUsingMouse() const
{
    return true;
}

void ACatPlayerController::EnableMouse(UWidget * inWidgetToFocus)
{
    UCatPlayerStatics::SetPlayerInputMode(this,EUIInputMode::UI_Game, inWidgetToFocus, false);
}
