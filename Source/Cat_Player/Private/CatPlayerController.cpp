// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved


#include "CatPlayerController.h"
#include "PlayerGridInteraction.h"
#include "Components/Widget.h"
#include "CatPlayerStatics.h"
#include "CatPlayerCameraPawn.h"
//#include "Engine/World.h"
//#include "GameFramework/Character.h"
//#include "Kismet/GameplayStatics.h"


ACatPlayerController::ACatPlayerController(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer), MouseWheelSpeed(1.f)
{
    GridInteractComp = ObjectInitializer.CreateDefaultSubobject<UPlayerGridInteraction>(this, TEXT("GridInteractionComponent"));
	ClickActionName = TEXT("Select");
	MouseWheelAxisName = TEXT("Zoom");
}

void ACatPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
    InputComponent->BindAction(ClickActionName, EInputEvent::IE_Pressed, this, &ACatPlayerController::OnClick);
    InputComponent->BindAxis(MouseWheelAxisName, this, &ACatPlayerController::OnMouseWheel);
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
    UCatPlayerStatics::SetPlayerInputMode(this,EUIInputMode::UI_Game, inWidgetToFocus, false);
}

ACatPlayerCameraPawn * ACatPlayerController::GetCameraPawn() const
{
    return Cast<ACatPlayerCameraPawn>(GetPawn());
}


void ACatPlayerController::OnClick()
{
    if(GridInteractComp)
    {
        GridInteractComp->TrySelect();
    }
}

void ACatPlayerController::OnMouseWheel(float value)
{
    if(GetCameraPawn())
        GetCameraPawn()->Zoom(value, MouseWheelSpeed);
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

