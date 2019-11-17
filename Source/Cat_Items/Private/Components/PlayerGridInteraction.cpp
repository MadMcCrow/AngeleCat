// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved


#include "PlayerGridInteraction.h"
#include "EngineUtils.h"
#include "GridActor.h"

// Sets default values for this component's properties
UPlayerGridInteraction::UPlayerGridInteraction()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts
void UPlayerGridInteraction::BeginPlay()
{
	Super::BeginPlay();
	OwningPC = Cast<APlayerController>(GetOwner());
	InitGrids();

}

void UPlayerGridInteraction::TrySelect()
{
	for(auto pairvalue : GridActorsPosition)
	{
		if(pairvalue.Key)
		{
			pairvalue.Key->SelectSlot(pairvalue.Value);
			SelectedGrid = pairvalue.Key;
			SelectedGridPosition = pairvalue.Value;
		}
		else
		{
			SelectedGrid = nullptr;
			SelectedGridPosition = FIntPoint(-1,-1);
		}
		
	}
}

bool UPlayerGridInteraction::GetSelected(AGridActor * &outGrid, FIntPoint &outCoord)
{
	if(SelectedGrid)
	{
			outGrid		= SelectedGrid;
			outCoord	= SelectedGridPosition;
	return true;
	}
	// else
	outGrid	 = nullptr;
	outCoord = FIntPoint(-1,-1);
	return false;
}

void UPlayerGridInteraction::SetCursorScreenPosition(const FVector2D &in)
{
	ScreenLookPosition = in;
}

// Called every frame
void UPlayerGridInteraction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdateGrids();

}

void UPlayerGridInteraction::UpdateGrids()
{
	if(OwningPC)
	{
		GridActorsPosition.Empty();
		for(auto itr : GridActors)
		{
			if(!itr)
				continue;
			
			FIntPoint Position;
			bool valid = itr->FindLookedAtPositionFromScreen(ScreenLookPosition, OwningPC, Position );
			if(valid)
			{
				itr->HoverSlotIntPoint(Position);
				GridActorsPosition.Add(itr,Position);
			}
		}
	}
}

void UPlayerGridInteraction::InitGrids()
{
	const auto World = GetWorld(); 
	for(TActorIterator<AGridActor> It(World, AGridActor::StaticClass()); It; ++It)
	{
		AGridActor* Actor = *It;
		GridActors.Add(Actor);
	}
}

