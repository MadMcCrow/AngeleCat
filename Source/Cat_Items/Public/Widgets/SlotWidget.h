// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemData.h"
#include "SlotWidgetComponent.generated.h"

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

public:

    virtual void SetVisibility(ESlateVisibility inVisibility) override;


protected:

    UPROPERTY(meta = (BindWidget), EditDefaultsOnly, BlueprintReadOnly, Category= "Widget")
    UCatContextWidget * WMainSlotWindow;

    UPROPERTY(meta = (BindWidget), EditDefaultsOnly, BlueprintReadOnly, Category= "Widget")
    UCatContextWidget * WItemListWindow;

    UFUNCTION(BlueprintCallable, Category = "ItemList")
    void ShowItemList(bool Visible);

    UFUNCTION(BlueprintCallable, Category = "Init")
    void SetFromSlot(AItem *SlotItem = nullptr);

    UFUNCTION(BlueprintCallable, Category = "Init")
    void SetFromData(const FItemStaticData &data);

private:

    UPROPERTY()
    bool bItemListVisible;

};


