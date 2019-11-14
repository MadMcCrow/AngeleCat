// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved


#include "CatPlayerController.h"
#include "PlayerGridInteraction.h"
#include "Components/Widget.h"
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
    FInputModeGameAndUI inputmode;
	inputmode.SetLockMouseToViewportBehavior(EMouseLockMode::LockOnCapture);
	inputmode.SetHideCursorDuringCapture(false);
	if (inWidgetToFocus != nullptr)
	{
		inputmode.SetWidgetToFocus(inWidgetToFocus->TakeWidget());
	}
	SetInputMode(inputmode);
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
    if(!GridInteractComp)
        return;

    FVector2D pos = FVector2D(0.5,0.5);
    if(IsUsingMouse())
    {
        GetMousePosition(pos.X, pos.Y);
    }

    GridInteractComp->SetCursorScreenPosition(pos);
}