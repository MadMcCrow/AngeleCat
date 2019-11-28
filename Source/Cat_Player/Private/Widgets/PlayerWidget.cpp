// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "PlayerWidget.h"
#include "GameFramework/PlayerController.h"
#include "CatPlayerState.h"
#include "CatValueWidget.h"


#define LOCTEXT_NAMESPACE "PlayerWidget"
#define RESETDYNAMIC(x,y,z) y.RemoveDynamic( x, z); y.AddDynamic(x, z);

void UPlayerWidget::OnWidgetRebuilt()
{
    Super::OnWidgetRebuilt();
}

#undef LOCTEXT_NAMESPACE