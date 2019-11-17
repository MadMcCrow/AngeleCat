// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "CatPlayerState.h"

float ACatPlayerState::GetMoney() const
{
	return MoneyScore;
}
bool ACatPlayerState::CanSpend(float amount) const
{
	return (amount <= GetMoney());
}

bool ACatPlayerState::TrySpend(float amount)
{
	if(CanSpend(amount))
	{
		MoneyScore -= amount;
			OnDecreasedEvent.Broadcast();
		return true;
	}
	return false;
}

void ACatPlayerState::Earn(float amount)
{
	MoneyScore += amount;
	OnIncreasedEvent.Broadcast();
}
