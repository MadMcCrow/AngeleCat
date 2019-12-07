// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved


#include "CatHUD.h"
#include "UserWidget.h"


void ACatHUD::SpawnHUDWidget()
{
    if(MainwidgetClass.Get())
    {
            MainHUDWidget = CreateWidget<UUserWidget>( GetOwningPlayerController(), MainwidgetClass);
    }

}