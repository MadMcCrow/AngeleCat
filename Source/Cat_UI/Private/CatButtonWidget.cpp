// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "CatButtonWidget.h"

void UCatButtonWidget::OnWidgetRebuilt()
{
    Super::OnWidgetRebuilt();
    if(WButtonText)
    {
        WButtonText->OnClicked.BindDynamic(this, UCatButtonWidget::OnClicked_impl);
        WButtonText->OnPressed.BindDynamic(this, UCatButtonWidget::OnPressed_impl);
        WButtonText->OnReleased.BindDynamic(this,UCatButtonWidget::OnRelease_impl);
        WButtonText->OnHovered.BindDynamic(this, UCatButtonWidget::OnHovered_impl);
    }
}

void UCatButtonWidget::OnClicked_impl()
{
    OnClicked.BroadCast();
    OnClickedEvent();
}
void UCatButtonWidget::OnPressed_impl()
{
    OnPressed.BroadCast();
    OnPressedEvent();
}
void UCatButtonWidget::OnReleased_impl()
{
    OnReleased.BroadCast();
    OnReleasedEvent();
}
void UCatButtonWidget::OnHovered_impl()
{
    OnHovered.BroadCast();
    OnHoveredEvent();
}