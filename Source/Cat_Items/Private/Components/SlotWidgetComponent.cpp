// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "SlotWidgetComponent.h"
#include "CatContextWidget.h"

#define LOCTEXT_NAMESPACE "SlotWidget"

USlotWidgetComponent::USlotWidgetComponent() : Super()
{
	Space = EWidgetSpace::Screen;
}


void USlotWidgetComponent::InitWidget()
{
	Super::InitWidget();
	ContextWidget = Cast<UCatContextWidget>(GetUserWidgetObject());
}

UCatContextWidget* USlotWidgetComponent::GetContextWidget() const
{
	return ContextWidget;
}

void USlotWidgetComponent::InitFromSlot(const FGridItemSlot& Slot)
{
	SlotCoordinate = Slot.GetCoordinate();
	if (GetContextWidget())
	{
		const FText Source = FText::Format(LOCTEXT("TitleText	", " Item At {0} {1}"), SlotCoordinate.X, SlotCoordinate.Y);
		GetContextWidget()->SetTitle(Source);
	}


	if(Slot.IsEmpty())
	{
		InitFromEmptySlot();
	}
	else
	{
		InitFromFilledSlot();
	}
}

void USlotWidgetComponent::Collapse()
{
	if (GetContextWidget())
		GetContextWidget()->SetVisibility(ESlateVisibility::Collapsed);
}

void USlotWidgetComponent::Reveal()
{
	if(GetContextWidget())
		GetContextWidget()->SetVisibility(ESlateVisibility::Visible);
}

AGridActor* USlotWidgetComponent::GetGrid() const
{
	return Grid;
}

void USlotWidgetComponent::SetGrid(AGridActor* grid)
{
	Grid = grid;
}

void USlotWidgetComponent::BuyAsset(UItemData* Data)
{
	
}

void USlotWidgetComponent::BuyData(const FItemStaticData& Data)
{

}



void USlotWidgetComponent::InitFromFilledSlot()
{
}

void USlotWidgetComponent::InitFromEmptySlot()
{
}

#undef LOCTEXT_NAMESPACE