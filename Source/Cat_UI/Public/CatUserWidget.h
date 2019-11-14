// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "Blueprint/UserWidget.h"
#include "CatUserWidget.generated.h"

class AActor;
class UWidgetComponent;
class APlayerController;

/// @brief UCatUserWidget		base class for user widget
UCLASS(ClassGroup=(UI))
class CAT_UI_API UCatUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:

    template<typename WidgetT, typename OwnerT>
    static WidgetT * NewWidget(OwnerT * owner, TSubclassOf< UCatUserWidget > userWidgetClass)
    {
        FName newwidgetname = MakeUniqueObjectName(owner, userWidgetClass, userWidgetClass->GetDefaultObjectName());
        return CreateWidget<WidgetT,OwnerT>(owner, userWidgetClass, newwidgetname);
    }

    UFUNCTION(BlueprintCallable, Category = "WidgetStatics")
    static UCatUserWidget * NewWidget(UActorComponent * owner, TSubclassOf< UCatUserWidget > userWidgetClass);

    
    template<typename WidgetCompT>
    static WidgetCompT * CreateWidgetComponent(AActor * owner, TSubclassOf< UCatUserWidget > userWidgetClass, TSubclassOf< WidgetCompT > componentClass, FName socketName = NAME_None, bool worldSpace = false);

    UFUNCTION(BlueprintCallable, Category = "WidgetStatics")
    static UWidgetComponent* CreateWidgetComponent(AActor * owner, TSubclassOf< UCatUserWidget > userWidgetClass, TSubclassOf< UWidgetComponent > componentClass, FName socketName = NAME_None, bool worldSpace = false)
    {return CreateWidgetComponent<UWidgetComponent>(owner, userWidgetClass, componentClass,socketName, worldSpace);}
   

    UFUNCTION(BlueprintCallable, Category = "WidgetStatics")
    static void SetWidgetComponent(UWidgetComponent * comp, TSubclassOf< UCatUserWidget > userWidgetClass,  bool worldSpace = false);
   

};
