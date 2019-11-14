// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "Blueprint/UserWidget.h"
#include "CatUserWidget.generated.h"

class AActor;
class UWidgetComponent;

/// @brief UCatUserWidget		base class for user widget
UCLASS(ClassGroup=(UI))
class CAT_UI_API UCatUserWidget : public UUserWidet
{
	GENERATED_BODY()
public:

    template<typename WidgetT, typename OwnerT>
    static WidgetT * CreateWidget(OwnerT * owner, TSubclassOf< UCatUserWidget > userWidgetClass);
    UFUNCTION(BlueprintCallable, Category = "WidgetStatics")
    static UCatUserWidget * CreateWidget(UObject * owner, TSubclassOf< UCatUserWidget > userWidgetClass)
    {return CreateWidget<UCatUserWidget, UObject>(owner, userWidgetClass);}

    
    template<typename WidgetCompT>
    static WidgetCompT * CreateWidgetComponent(AActor * owner, TSubclassOf< UCatUserWidget > userWidgetClass, TSubclassOf< WidgetCompT > componentClass, bool worldSpace = false);
    UFUNCTION(BlueprintCallable, Category = "WidgetStatics")
    static UWidgetComponent* CreateWidgetComponent(AActor * owner, TSubclassOf< UCatUserWidget > userWidgetClass, TSubclassOf< WidgetCompT > componentClass, bool worldSpace = false)
    {return CreateWidgetComponent<UWidgetComponent>(owner, userWidgetClass, componentClass, worldSpace);}
   

    UFUNCTION(BlueprintCallable, Category = "WidgetStatics")
    static void SetWidgetComponent(UWidgetComponent * comp, TSubclassOf< UCatUserWidget > userWidgetClass,  bool worldSpace = false);

    

};
