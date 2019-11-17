// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "SlotWidgetComponent.h"
#include "CatContextWidget.h"

#define LOCTEXT_NAMESPACE "SlotWidget"

void USlotWidget::SetVisibility(ESlateVisibility inVisibility)
{
    Super::SetVisibility(inVisibility);
    switch(inVisibility)
    {
        case ESlateVisibility::Collapsed:
        case ESlateVisibility::Hidden:
        {
            bItemListVisible = false;
            if(WItemListWindow)
                WItemListWindow->SetVisibility(inVisibility);
        }
        break:
        case ESlateVisibility::Visible:
        default:
    }
}


void USlotWidget::SetFromSlot(bool empty, AItem *slotItem)
{
    if(empty || !slotItem)
}


#undef LOCTEXT_NAMESPACE