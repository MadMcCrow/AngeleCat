// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "CatUserWidget.h"
#include "CatContextWidget.generated.h"

class UTextBlock;

/// @brief UCatUserWidget		base class for user widget
UCLASS()
class CAT_UI_API UCatContextWidget : public UCatUserWidget
{
	GENERATED_BODY()
protected:

    UPROPERTY(meta = (BindWidget), EditDefaultsOnly, BlueprintReadOnly, Category= "Widget")
    UTextBlock * WTitle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text", meta = (BlueprintSetter = "SetTitle"))
	FText TitleText;
    
    UPROPERTY(meta = (BindWidget), EditDefaultsOnly, BlueprintReadOnly, Category= "Widget")
    UPanelWidget * WSubWidgetContainer;

public:

    template<typename WidgetT>
    WidgetT * CreateChild(TSubclassOf< UUserWidget > UserWidgetClass, FName WidgetName);

    UFUNCTION(BlueprintCallable, Category = "Context", DisplayName = "CreateChild")
    UUserWidget * CreateChild_BP(TSubclassOf< UUserWidget > UserWidgetClass, FName WidgetName)
    {
        return CreateChild<UUserWidget>(UserWidgetClass,WidgetName);
    }

	UFUNCTION(BlueprintCallable, BlueprintSetter, Category = "Widget")
	void SetTitle(const FText &in);


};
