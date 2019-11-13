// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "CatButtonWidget.h"

void UCatButtonWidget::OnWidgetRebuilt()
{
    Super::OnWidgetRebuilt();
    if(WButtonText)
    {
        WButtonText->OnClicked.BindDynamic(this, UCatButtonWidget::OnClicked_impl);
    }
}

void UCatButtonWidget::OnClicked_impl()
{
    OnClicked.BroadCast();
}
void UCatButtonWidget::OnPressed_impl()
{
    OnPressed.BroadCast();
}
void UCatButtonWidget::OnReleased_impl()
{
    OnReleased.BroadCast();
}
void UCatButtonWidget::OnHovered_impl()
{
    OnHovered..BroadCast();
}