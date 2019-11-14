// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "CatTextDisplayWidget.h"
#include "Components/Button.h"
#include "CatButtonWidget.generated.h"

class UTextBlock;

/// @brief UCatUserWidget		base class for user widget
UCLASS(ClassGroup=(UI))
class CAT_UI_API UCatButtonWidget : public UCatTextDisplayWidget
{
	GENERATED_BODY()

public:

    virtual void OnWidgetRebuilt() override;
protected:

    UPROPERTY(meta = (BindWidget),VisibleAnywhere, BlueprintReadOnly, Category= "Widget")
    UButton * WButton;

public:

    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events|Button")
    FOnButtonClickedEvent   OnClicked;
    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events|Button")
    FOnButtonPressedEvent   OnPressed;
    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events|Button")
    FOnButtonReleasedEvent  OnReleased;
    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events|Button")
    FOnButtonHoverEvent     OnHovered;

protected:

    UFUNCTION(BlueprintImplementableEvent, Category = "Events|Button")
    void OnClickedEvent();

    UFUNCTION(BlueprintImplementableEvent, Category = "Events|Button")
    void OnPressedEvent();

    UFUNCTION(BlueprintImplementableEvent, Category = "Events|Button")
    void OnReleasedEvent();

    UFUNCTION(BlueprintImplementableEvent, Category = "Events|Button")
    void OnHoveredEvent();

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
