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
    BindInputComponent->BindAction(ClickActionName, EInputEvent::IE_Pressed, this, &ACatPlayerController::OnClick);
}

void ACatPlayerController::Onclick()
{
    if(GridInteractComp)
    {
        GridInteractComp->TrySelect();
    }
}