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
    static WidgetT * CreateWidget(OwnerT * Owner, TSubclassOf< UCatUserWidget > UserWidgetClass);


    template<typename WidgetCompT>
    static WidgetCompT * CreateWidgetComponent(AActor * Owner, TSubclassOf< UCatUserWidget > UserWidgetClass, TSubclassOf< WidgetCompT > ComponentClass, bool worldSpace = false);



};
