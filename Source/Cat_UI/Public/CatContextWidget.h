// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "CatUserWidget.h"
#include "UCatContextWidget.generated.h"

/// @brief UCatUserWidget		base class for user widget
UCLASS()
class CAT_UI_API UCatContextWidget : public UCatUserWidget
{
	GENERATED_BODY()
protected:

    UPROPERTY(meta = (BindWidget), BlueprintReadWrite, Category= "widget")
    UTextBlock WTitle;

    UPROPERTY(meta = (BindWidget), BlueprintReadWrite, Category= "widget")
    UPanelWidget * WSubWidgetContainer;

public:

    template<typename WidgetT>
    WidgetT * CreateChild(TSubclassOf< UUserWidget > UserWidgetClass, FName WidgetName);

    UFUNCTION(BlueprintCallable, Category = "Context", DisplayName = "CreateChild")
    UUserWidget * CreateChild_BP(TSubclassOf< UUserWidget > UserWidgetClass, FName WidgetName)
    {
        return CreateChild<UUserWidget>(UserWidgetClass,WidgetName);
    }

};
