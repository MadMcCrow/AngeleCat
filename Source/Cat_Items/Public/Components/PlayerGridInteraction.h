// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerGridInteraction.generated.h"


class AGridActor;
class APlayerController;

UCLASS( ClassGroup=(PlayerController), meta=(BlueprintSpawnableComponent) )
class CAT_ITEMS_API UPlayerGridInteraction : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerGridInteraction();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Screen Position")
	virtual void SetCursorScreenPosition(const FVector2D &in);
	
	UFUNCTION()
	virtual void TrySelect();

	UFUNCTION(BlueprintPure, Category = "Selection")
	virtual bool GetSelected(AGridActor * &outGrid, FIntPoint &outCoord);

protected:

	virtual void UpdateGrids();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	FVector2D ScreenLookPosition;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	APlayerController * OwningPC;

private:

	UPROPERTY()
	TArray<AGridActor *> GridActors;

	UPROPERTY(transient)
	TMap<AGridActor *, FIntPoint> GridActorsPosition;
	
	UPROPERTY(transient)
	AGridActor * SelectedGrid;

	UPROPERTY(transient)
	FIntPoint SelectedGridPosition;

	void InitGrids();

};
