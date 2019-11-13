// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved


#include "CatPlayerStatics.h"
#include "WidgetLayoutLibrary.h"

FVector2D UCatPlayerStatics::MouseScreenBorderMove(UObject * WorldContextObject, float xThreshold,float yThreshold, bool invertXY, bool allowOutsideMovement)
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

