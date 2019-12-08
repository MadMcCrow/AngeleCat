// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "CatContextWidget.h"
#include "Cat_UIPCH.h"

template<typename WidgetT>
WidgetT * UCatContextWidget::CreateChild(TSubclassOf< UUserWidget > UserWidgetClass, FName WidgetName)
{
    if(!WSubWidgetContainer)
        return nullptr;

    auto widget = CreateWidget<WidgetT, UCatContextWidget>(this, UserWidgetClass, WidgetName);
    AddChild(widget);
    return widget;
}

template UUserWidget * UCatContextWidget::CreateChild<UUserWidget>(TSubclassOf<UUserWidget> UserWidgetClass, FName WidgetName);

void UCatContextWidget::AddChild( UWidget * widget)
{
    if(widget && WSubWidgetContainer)
    {
        WSubWidgetContainer->AddChild(static_cast<UWidget *>(widget));
    }
}

