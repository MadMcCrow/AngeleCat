// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "CatPlayerState.h"
#include "CatUserWidget.h"
#include "Widgets/PlayerWidget.h"

#define MONEYMAX 2147483648

void ACatPlayerState::BeginPlay()
{
    Super::BeginPlay();
}


int32 ACatPlayerState::GetMoney() const
{
	return MoneyScore;
}
bool ACatPlayerState::CanSpend(int32 amount) const
{
	return (amount <= GetMoney());
}

bool ACatPlayerState::TrySpend(int32 amount)
{
	if(CanSpend(amount))
	{
		MoneyScore -= amount;
			OnDecreasedEvent.Broadcast();
		return true;
	}
	return false;
}

void ACatPlayerState::Earn(int32 amount)
{
	if(MoneyScore + amount <=MONEYMAX)
		MoneyScore += amount;
	OnIncreasedEvent.Broadcast();
}
