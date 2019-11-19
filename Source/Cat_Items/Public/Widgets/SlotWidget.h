// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemData.h"
#include "SlotWidget.generated.h"

class UCatContextWidget;
class USlotWidgetComponent;

/**
 * 
 */
UCLASS()
class CAT_ITEMS_API USlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
	friend USlotWidgetComponent;

    virtual void OnWidgetRebuilt() override;

public:

    virtual void SetVisibility(ESlateVisibility inVisibility) override;

    virtual void SetSlotWidgetComponent(USlotWidgetComponent * widgetComponent);

    UFUNCTION(BlueprintCallable, Category = "ItemList")
    void ShowItemList(bool Visible);

    UFUNCTION(BlueprintCallable, Category = "Init")
    void SetFromSlot(AItem *SlotItem = nullptr);

    UFUNCTION(BlueprintCallable, Category = "Init")
    void SetFromData(const FItemStaticData &data);

    UFUNCTION(BlueprintCallable, Category = "Init")
    void SetFromEmptySlot();

    UFUNCTION(BlueprintCallable, Category = "Init")
    void SetTitle(const FText &title);

    UFUNCTION(BlueprintCallable, Category = "Widget")
	virtual void Collapse();

	UFUNCTION(BlueprintCallable, Category = "Widget")
	virtual void Reveal();


protected:

    UPROPERTY(meta = (BindWidget), BlueprintReadOnly, Category= "Widget")
    UCatContextWidget * WMainSlotWindow;

    UPROPERTY(meta = (BindWidget), BlueprintReadOnly, Category= "Widget")
    UCatContextWidget * WItemListWindow;

    UPROPERTY(BlueprintReadWrite, Category = "Item")
    bool bCanShowItemList;

private:

    UPROPERTY()
    bool bItemListVisible;

    UPROPERTY()
    USlotWidgetComponent * OwningWidgetComponent;

};


