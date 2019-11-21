// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "ItemData.h"
#include "GridActor.h"
#include "SlotWidgetComponent.generated.h"

class USlotWidget;
class APlayerController;

/**
 * 
 */
UCLASS()
class CAT_ITEMS_API USlotWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
	friend AGridActor;
	
	USlotWidgetComponent();

public:

	virtual void InitWidget() override;

	UFUNCTION(BlueprintPure, Category = "Widget")
	USlotWidget * GetContextWidget() const;

	UFUNCTION(BlueprintCallable, Category = "Widget")
	void InitFromSlot(const FGridItemSlot &Slot);

	UFUNCTION(BlueprintCallable, Category = "Widget")
	virtual void Collapse();

	UFUNCTION(BlueprintCallable, Category = "Widget")
	virtual void Reveal();


	UFUNCTION(BlueprintPure, Category = "Grid")
	virtual AGridActor * GetGrid() const;

    UFUNCTION(BlueprintPure, Category = "Grid")
	FIntPoint GetCoordinate() const {return SlotCoordinate;}


protected:

	UFUNCTION(BlueprintCallable, Category = "Buy")
	bool BuyAsset(UItemData * data, APlayerController * player = nullptr);

	UFUNCTION(BlueprintCallable, Category = "Buy")
	bool BuyData(const FItemStaticData &data, APlayerController *  player = nullptr);


	virtual void InitFromEmptySlot();

	virtual void InitFromFilledSlot();



private:

	UPROPERTY()
	mutable USlotWidget * ContextWidget;

	UPROPERTY()
	FIntPoint SlotCoordinate;

	UPROPERTY()
	AGridActor * Grid;

};


