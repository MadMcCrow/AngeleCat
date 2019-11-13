// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "CatUserWidget.h"
#include "Components/Button.h"
#include "UCatContextWidget.generated.h"

class UTextBlock;


/// @brief UCatUserWidget		base class for user widget
UCLASS(ClassGroup=(UI))
class CAT_UI_API UCatButtonWidget : public UCatUserWidget
{
	GENERATED_BODY()

public:

    virtual void OnWidgetRebuilt() override;
protected:

    UPROPERTY(meta = (BindWidget), BlueprintReadWrite, Category= "widget")
    UTextBlock * WButtonText;

    UPROPERTY(meta = (BindWidget), BlueprintReadWrite, Category= "widget")
    UButton * WButtonText;

public:

    UPROPERTY()
    FOnButtonClickedEvent   OnClicked;

    UPROPERTY()
    FOnButtonPressedEvent   OnPressed;

    UPROPERTY()
    FOnButtonReleasedEvent  OnReleased;

    UPROPERTY()
    FOnButtonHoverEvent     OnHovered;

private:
    UFUNCTION()
    void OnClicked_impl();

    UFUNCTION()
    void OnPressed_impl();

    UFUNCTION()
    void OnReleased_impl();

    UFUNCTION()
    void OnHovered_impl();

};
