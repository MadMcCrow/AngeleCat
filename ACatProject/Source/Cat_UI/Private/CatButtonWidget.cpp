// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "CatButtonWidget.h"

#define RESETDYNAMIC(x,y,z) y.RemoveDynamic( x, z); y.AddDynamic(x, z);

void UCatButtonWidget::OnWidgetRebuilt()
{
    Super::OnWidgetRebuilt();
    if(WButton)
    {
        RESETDYNAMIC( this, WButton->OnClicked,  &UCatButtonWidget::OnClicked_impl);
        RESETDYNAMIC( this, WButton->OnPressed,  &UCatButtonWidget::OnPressed_impl);
        RESETDYNAMIC( this, WButton->OnReleased, &UCatButtonWidget::OnReleased_impl);
        RESETDYNAMIC( this, WButton->OnHovered,  &UCatButtonWidget::OnHovered_impl);
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