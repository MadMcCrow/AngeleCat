// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved


#include "CatPlayerController.h"
#include "PlayerGridInteraction.h"
//#include "Engine/World.h"
//#include "GameFramework/Character.h"
//#include "Kismet/GameplayStatics.h"


ACatPlayerController::ACatPlayerController(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
    GridInteractComp = ObjectInitializer.CreateDefaultSubobject<UPlayerGridInteraction>(this, TEXT("GridInteractionComponent"));
}

void ACatPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
    InputComponent->BindAction(ClickActionName, EInputEvent::IE_Pressed, this, &ACatPlayerController::OnClick);
}

void ACatPlayerController::Tick(float deltaTime)
{
    Super::Tick(deltaTime);
    UpdateGridInteractionCursorPosition();
}

bool ACatPlayerController::IsUsingMouse() const
{
    return true;
}

void ACatPlayerController::OnClick()
{
    if(GridInteractComp)
    {
        GridInteractComp->TrySelect();
    }
}

void ACatPlayerController::UpdateGridInteractionCursorPosition()
{

}