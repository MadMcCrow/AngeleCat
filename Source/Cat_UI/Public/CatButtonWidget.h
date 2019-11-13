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
