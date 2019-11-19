// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "SlotWidget.h"
#include "CatContextWidget.h"
#include "SlotWidgetComponent.h"


#define LOCTEXT_NAMESPACE "SlotWidget"
#define RESETDYNAMIC(x,y,z) y.RemoveDynamic( x, z); y.AddDynamic(x, z);

void USlotWidget::OnWidgetRebuilt()
{
    Super::OnWidgetRebuilt();
    
}

void USlotWidget::SetSlotWidgetComponent(USlotWidgetComponent * widgetComponent)
{
    if(widgetComponent)
    {
            OwningWidgetComponent = widgetComponent;
    }
    else
    {
        if(GetOuter() && Cast<USlotWidgetComponent>(GetOuter()))
            OwningWidgetComponent = Cast<USlotWidgetComponent>(GetOuter());
    }

}

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
        break;
        case ESlateVisibility::Visible:
        default:
        break;
    }
}

void USlotWidget::ShowItemList(bool Visible)
{
    if(bCanShowItemList && bItemListVisible != Visible)
    {
        bItemListVisible = true;
        WItemListWindow->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
    }
}

void USlotWidget::SetFromSlot(AItem *slotItem)
{
    if(!slotItem)
    {
        bCanShowItemList = true;
        return;
    }
    bCanShowItemList = false;
}

void USlotWidget::SetFromData(const FItemStaticData &data)
{

}

void USlotWidget::SetFromEmptySlot()
{
    
}

void USlotWidget::SetTitle(const FText &title)
{
    WMainSlotWindow->SetTitle(title);
}


void USlotWidget::Collapse()
{
    SetVisibility(ESlateVisibility::Collapsed);
}

void USlotWidget::Reveal()
{
    SetVisibility(ESlateVisibility::Visible);
}

#undef LOCTEXT_NAMESPACE