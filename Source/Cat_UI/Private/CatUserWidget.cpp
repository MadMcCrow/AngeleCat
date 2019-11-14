// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "CatUserWidget.h"



template<typename WidgetT, typename OwnerT>
WidgetT * UCatUserWidget::CreateWidget(OwnerT * owner, TSubclassOf< UCatUserWidget > userWidgetClass)
{
    //  UserWidgetClass.GetName() 
    FName newwidgetname = MakeUniqueObjectName(owner, UserWidgetClass, UserWidgetClass.GetDefaultObjectName());
    return CreateWidget<WidgetT,OwnerT>(owner, UCatUserWidget, newwidgetname);
}

template<typename WidgetCompT>
WidgetCompT * UCatUserWidget::CreateWidgetComponent(AActor * owner, TSubclassOf< UCatUserWidget > userWidgetClass, TSubclassOf< WidgetCompT > componentClass, bool worldSpace)
{
    if(!userWidgetClass.Get() || !owner || !WidgetCompT->IsChildOf<UWidgetComponent>())
        return nullptr;
    
    FName newwidgetname = MakeUniqueObjectName(owner, componentClass, userWidgetClass.GetDefaultObjectName());
    WidgetCompT* newcomp = NewObject<WidgetCompT>( ComponentClass, this, YourObjectName);

    if(!newcomp)
        return nullptr;

    auto widgetcomp = static_cast<UWidgetComponent*>(newcomp);
    widgetcomp->RegisterComponent();        //You must ConstructObject with a valid Outer that has world, see above	 
    widgetcomp->SetWorldLocation(Location); 
    widgetcomp->SetWorldRotation(Rotation); 
    widgetcomp->AttachTo(GetRootComponent(),SocketName,EAttachLocation::KeepWorldPosition); 
    SetWidgetComponent(widgetcomp,userWidgetClass);

    return newcomp;     
}

 void UCatUserWidget::SetWidgetComponent(UWidgetComponent * comp, TSubclassOf< UCatUserWidget > userWidgetClass,  bool worldSpace = false)
 {
    if(!comp)
        return;
    auto widget = CreateWidget(comp,UserWidgetClass);
    widgetcomp->SetWidget(widget);
    widgetcomp->SetWidgetSpace(worldSpace ? EWidgetSpace::World : EWidgetSpace::Screen);
 }
    