// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved


#include "CatPlayerStatics.h"
#include "WidgetLayoutLibrary.h"
#include "Widget.h"
#include "GameFramework/PlayerController.h"

FVector2D UCatPlayerStatics::GetMouseBorderOverlap(UObject * WorldContextObject, float xThreshold,float yThreshold, bool invertXY, bool allowOutsideMovement)
{
	auto MousePos = UWidgetLayoutLibrary::GetMousePositionOnViewport(WorldContextObject);
	MousePos *= UWidgetLayoutLibrary::GetViewportScale(WorldContextObject);
	MousePos /= UWidgetLayoutLibrary::GetViewportSize(WorldContextObject);

	if(allowOutsideMovement)
	{
		MousePos = MousePos.ClampAxes(0.f,1.f);
	}
	else
	{
		// ignore out-of screen Mouse position
		if(MousePos.X > 1.f || MousePos.X < 0.f || MousePos.Y > 1.f || MousePos.Y < 0.f)
			return FVector2D(0.f,0.f);
	}

	float xMovement = 0.f;
	float yMovement = 0.f;

	if(MousePos.X > 1.f - xThreshold)
	{
		xMovement = -1.f *  (MousePos.X - xThreshold) / (1.f - xThreshold); // inverted because the origin is top right
	} else if( MousePos.X < xThreshold)
	{
		xMovement = (xThreshold - MousePos.X) / (xThreshold );
	}
	if(MousePos.Y > 1.f - yThreshold)
	{
		yMovement = (MousePos.Y - yThreshold) / (1.f - yThreshold);
	} else if( MousePos.Y < yThreshold)
	{
		yMovement = -1.f * (yThreshold - MousePos.Y) / (yThreshold );
	}

	return invertXY?  FVector2D(yMovement, xMovement) : FVector2D(xMovement, yMovement);

}

void UCatPlayerStatics::SetPlayerInputMode(APlayerController * player, EUIInputMode inputMode,UWidget * inWidgetToFocus, bool bHideCursorDuringCapture)
{
	if (player == nullptr)	
		return;

	EMouseLockMode inMouseLockMode = EMouseLockMode::LockInFullscreen;
		
	switch(inputMode)
	{
	case EUIInputMode::UI_Only :
		{
			FInputModeUIOnly mode;
			mode.SetLockMouseToViewportBehavior(inMouseLockMode);

			if (inWidgetToFocus != nullptr)
			{
				mode.SetWidgetToFocus(inWidgetToFocus->TakeWidget());
			}
			player->SetInputMode(mode);
		}
		player->bShowMouseCursor = true;
	break;
	case EUIInputMode::UI_Game :
		{
			FInputModeGameAndUI mode;
			mode.SetLockMouseToViewportBehavior(inMouseLockMode);
			mode.SetHideCursorDuringCapture(bHideCursorDuringCapture);
			if (inWidgetToFocus != nullptr)
			{
				mode.SetWidgetToFocus(inWidgetToFocus->TakeWidget());
			}
			player->SetInputMode(mode);
		}
		player->bShowMouseCursor = true;
	break;
	case EUIInputMode::Game_Only :
		{
			FInputModeGameOnly mode;
			player->SetInputMode(mode);
		}
		player->bShowMouseCursor = false;
	break;
	default:
	return;
	};
}