// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "CatUserWidget.h"
#include "Components/WidgetComponent.h"


UCatUserWidget * UCatUserWidget::NewWidget(UActorComponent * owner, TSubclassOf< UCatUserWidget > userWidgetClass)
{
    return NewWidget<UCatUserWidget, UWorld>(owner->GetWorld(), userWidgetClass);
}

template<typename WidgetCompT>
static WidgetCompT * UCatUserWidget::CreateWidgetComponent(AActor * owner, TSubclassOf< UCatUserWidget > userWidgetClass, TSubclassOf< WidgetCompT > componentClass, FName socketName,  bool worldSpace)
 {
     static_assert(TIsDerivedFrom<WidgetCompT, UWidgetComponent>::IsDerived, "The given WidgetCompT type is not a widget component class");
     
     if(!userWidgetClass.Get() || !owner)
         return nullptr;
     
    const FName newwidgetcompname = MakeUniqueObjectName(owner, componentClass, userWidgetClass->GetDefaultObjectName());
    WidgetCompT* newcomp = NewObject<WidgetCompT>(owner, componentClass, newwidgetcompname);

    if(!newcomp)
         return nullptr;

    auto widgetcomp = static_cast<UWidgetComponent*>(newcomp);

    widgetcomp->RegisterComponent();        //You must ConstructObject with a valid Outer that has world, see above	 
    widgetcomp->SetWorldLocation(owner->GetActorLocation()); 
    widgetcomp->SetWorldRotation(owner->GetActorRotation()); 
    widgetcomp->AttachToComponent(owner->GetRootComponent(),FAttachmentTransformRules::SnapToTargetNotIncludingScale, socketName); 
    SetWidgetComponent(widgetcomp,userWidgetClass);
     return newcomp;     
 }

template UWidgetComponent * UCatUserWidget::CreateWidgetComponent<UWidgetComponent>(AActor *, TSubclassOf<UCatUserWidget> , TSubclassOf<UWidgetComponent> ,FName, bool);


void UCatUserWidget::SetWidgetComponent(UWidgetComponent * comp, TSubclassOf<UCatUserWidget> userWidgetClass,  bool worldSpace)
{
   if(!comp)
       return;
   auto widget = NewWidget(comp,userWidgetClass);
   comp->SetWidget(widget);
   comp->SetWidgetSpace(worldSpace ? EWidgetSpace::World : EWidgetSpace::Screen);
}
