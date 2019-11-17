// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "ItemData.h"
#include "GridActor.h"
#include "SlotWidgetComponent.generated.h"

class UCatContextWidget;


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
	UCatContextWidget * GetContextWidget() const;

	UFUNCTION(BlueprintCallable, Category = "Widget")
	void InitFromSlot(const FGridItemSlot &Slot);

	UFUNCTION(BlueprintCallable, Category = "Widget")
	virtual void Collapse();

	UFUNCTION(BlueprintCallable, Category = "Widget")
	virtual void Reveal();


	UFUNCTION(BlueprintPure, Category = "Grid")
	virtual AGridActor * GetGrid() const;


protected:

	UFUNCTION(BlueprintCallable, Category = "Buy")
	void BuyAsset(UItemData * Data);

	UFUNCTION(BlueprintCallable, Category = "Buy")
	void BuyData(const FItemStaticData &Data);


	virtual void InitFromEmptySlot();

	virtual void InitFromFilledSlot();

	UFUNCTION(BlueprintCallable, Category = "Grid")
	virtual void SetGrid(AGridActor * grid);


private:

	UPROPERTY()
	UCatContextWidget * ContextWidget;

	UPROPERTY()
	FIntPoint SlotCoordinate;

	UPROPERTY()
	AGridActor * Grid;

};


