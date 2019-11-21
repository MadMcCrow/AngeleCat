// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "SlotWidgetComponent.h"
#include "Widgets/SlotWidget.h"
#include "CatPlayerState.h"
#include "Kismet/GameplayStatics.h"

#define LOCTEXT_NAMESPACE "SlotWidgetComponent"

USlotWidgetComponent::USlotWidgetComponent() : Super()
{
	Space = EWidgetSpace::Screen;
}


void USlotWidgetComponent::InitWidget()
{
	Super::InitWidget();
	ContextWidget = Cast<USlotWidget>(GetUserWidgetObject());
    ContextWidget->SetSlotWidgetComponent(this);
}

USlotWidget* USlotWidgetComponent::GetContextWidget() const
{
	return ContextWidget;
}

void USlotWidgetComponent::InitFromSlot(const FGridItemSlot& Slot)
{
	SlotCoordinate = Slot.GetCoordinate();


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
	return Cast<AGridActor>(GetOwner());
}

bool USlotWidgetComponent::BuyAsset(UItemData* data, APlayerController * player)
{
    if(data)
        return BuyData(data->GetData(), player);
    return false;
}

bool USlotWidgetComponent::BuyData(const FItemStaticData& data, APlayerController * player)
{
	ACatPlayerState *PS = nullptr;
	if(player)
	{
		PS = Cast<ACatPlayerState>(player->PlayerState);
	}
	else
	{
		if(GetContextWidget())
		{
			PS = GetContextWidget()->GetOwningPlayerState<ACatPlayerState>(true);
		}
		else
		{
			auto PC = UGameplayStatics::GetPlayerController(this, 0);
			if(!PC)
				return false;
			PS = Cast<ACatPlayerState>(PC->PlayerState);
		}
	}
   
    if(PS && PS->CanSpend(data.GetCost()))
    {
        if(GetGrid())
        {
			AActor * worldcontext = player ? static_cast<AActor * >(player) :  static_cast<AActor *>(GetGrid());
            auto item = AItem::CreateItem(worldcontext, GetGrid(), GetGrid()->GetItemBaseClass(),data);
            if(item)
            {
                if(!PS->TrySpend(data.GetCost()))
                {
                    item->BeginDestroy(); // we could not pay.
                    return false;
                }
                GetGrid()->SetActorInSlot(item, GetCoordinate());
                return true;
            }
        }
    }
    return false;
}

void USlotWidgetComponent::InitFromFilledSlot()
{
	if(!GetContextWidget())
		return;
		
	GetContextWidget()->Collapse();
	if(Grid)
	{
		AActor *  target = Grid->GetItemAtCoordinate(SlotCoordinate);
		if(!target)
			return;
		AItem * item = Cast<AItem>(target);
		if(!item)
			return;
	
		const auto Data = item->GetStaticData();
		const FText Source = FText::Format(LOCTEXT("TitleText", " {0} ({1},{2})"),Data.GetTextName(), SlotCoordinate.X, SlotCoordinate.Y);
		GetContextWidget()->SetFromData(item->GetStaticData());
		
	}
	GetContextWidget()->Reveal();
}

void USlotWidgetComponent::InitFromEmptySlot()
{
	GetContextWidget()->Collapse();
	const FText Source = FText::Format(LOCTEXT("TitleText", " Empty slot ({0},{1})"), SlotCoordinate.X, SlotCoordinate.Y);
	GetContextWidget()->SetTitle(Source);
	GetContextWidget()->SetFromEmptySlot();
	GetContextWidget()->Reveal();
}

#undef LOCTEXT_NAMESPACE