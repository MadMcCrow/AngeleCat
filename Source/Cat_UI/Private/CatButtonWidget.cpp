// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "CatButtonWidget.h"

void UCatButtonWidget::OnWidgetRebuilt()
{
    Super::OnWidgetRebuilt();
    if(WButton)
    {
        WButton->OnClicked.AddDynamic(this,  &UCatButtonWidget::OnClicked_impl);
        WButton->OnPressed.AddDynamic(this,  &UCatButtonWidget::OnPressed_impl);
        WButton->OnReleased.AddDynamic(this, &UCatButtonWidget::OnReleased_impl);
        WButton->OnHovered.AddDynamic(this,  &UCatButtonWidget::OnHovered_impl);
    }
}

void UCatButtonWidget::OnClicked_impl()
{
    OnClicked.Broadcast();
    OnClickedEvent();
}
void UCatButtonWidget::OnPressed_impl()
{
    OnPressed.Broadcast();
    OnPressedEvent();
}
void UCatButtonWidget::OnReleased_impl()
{
    OnReleased.Broadcast();
    OnReleasedEvent();
}
void UCatButtonWidget::OnHovered_impl()
{
    OnHovered.Broadcast();
    OnHoveredEvent();
}