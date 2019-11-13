// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "CatContextWidget.h"
#include "Cat_UIPCH.h"

template<typename WidgetT>
WidgetT * UCatContextWidget::CreateChild( OwnerT * OwningObject,TSubclassOf< UUserWidget > UserWidgetClass, FName WidgetName)
{
    if(!WSubWidgetContainer)
        return nullptr;

    auto widget = CreateWidget<WidgetT, UCatContextWidget>(this, UserWidgetClass, WidgetName);
    if(widget)
    {
        WSubWidgetContainer->AddChild(widget);
    }

    return widget;
}