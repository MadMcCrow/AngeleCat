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
    const auto playerstate = Cast<ACatPlayerState>(GetOwningPlayer()->PlayerState);
    if(playerstate)
    {
        OwningPlayerState = playerstate;
        UpdateFunds();
        RESETDYNAMIC(this, OwningPlayerState->OnIncreasedEvent, &UPlayerWidget::UpdateFunds);
        RESETDYNAMIC(this, OwningPlayerState->OnDecreasedEvent, &UPlayerWidget::UpdateFunds);
    }
}

void UPlayerWidget::UpdateFunds()
{
    if(OwningPlayerState)
        FundsWidget->SetValueAsCurrency(OwningPlayerState->GetMoney());
}

#undef LOCTEXT_NAMESPACE