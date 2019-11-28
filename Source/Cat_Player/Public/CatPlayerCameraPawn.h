// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "GameFramework/Pawn.h"
#include "CatPlayerCameraPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UFloatingPawnMovement;

UCLASS(ClassGroup = "Cat_Player", Category = "Pawn")
class CAT_PLAYER_API ACatPlayerCameraPawn : public APawn
{
	GENERATED_BODY()
public:
	// Sets default values for this pawn's properties
	ACatPlayerCameraPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:

	///	@brief Cam					Player's default cam
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
		UCameraComponent * Cam;

	///	@brief CamBoom				arm to distance @see cam
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		USpringArmComponent * CamBoom;

	///	@brief FixedRoot			Origin of the player camera pawn
	UPROPERTY()
		USceneComponent * FixedRoot;


	///	@brief MovementComp			Component handling the movement
	UPROPERTY(EditDefaultsOnly, Category = "Movement" )
		UFloatingPawnMovement * MovementComp;

	///	@brief ZoomDistance			How much are we zoomed in
	UPROPERTY(BlueprintReadWrite)
		float ZoomDistance;

	///	@brief bRotateMode			Are we supposed to rotate or move
	UPROPERTY(BlueprintReadWrite)
		bool bRotateMode;

public:
	/// Override of Pawn function
	virtual UPawnMovementComponent* GetMovementComponent() const override;

	///	@brief MoveCamera			Use Movement component to move the pawn
	UFUNCTION(BlueprintCallable, Category = "Movement")
		virtual void MoveCamera(const FVector &Input, float Scale = 1.f);

	///	@brief RotateCameraUp		Rotate Camera Up and Down
	UFUNCTION(BlueprintCallable, Category = "Movement")
		virtual void RotateCameraUp(float Input, float Scale = 1.f);

	///	@brief RotateCameraRight	Rotate Camera Right and Left
	UFUNCTION(BlueprintCallable, Category = "Movement")
		virtual void RotateCameraRight(float Input, float Scale = 1.f);

	///	@brief MoveCamera			Use Movement component to move the pawn
	UFUNCTION(BlueprintCallable, Category = "Movement")
		virtual void SetInRotateMode(bool InRotateMode = true) { bRotateMode = InRotateMode; }

	///	@brief Zoom					Dolly In, getting closer to the look point
	UFUNCTION(BlueprintCallable, Category = "Camera")
		virtual void Zoom(float Delta, float Scale = 1.f);

	///	@brief ActorToFollow		Actor to follow and zoom on
	UPROPERTY(BlueprintReadWrite, Category = "Follow")
		AActor * ActorToFollow;


	///	@brief ZoomOnActor			Do the necessary adjustment to see clearly the Actor
	UFUNCTION()
		void ZoomOnActor(const AActor * Target);


	///	@brief SetActorToFollow		Set Who the camera is supposed to follow
	UFUNCTION(BlueprintCallable, Category = "Follow")
		void SetActorToFollow( AActor * Target);

	UFUNCTION(BlueprintCallable, Category = "Follow")
		void StopFollowing() { ActorToFollow = nullptr; }

	UFUNCTION(BlueprintPure, Category = "Follow")
		FORCEINLINE bool IsFollowing() const { return ActorToFollow != nullptr; }




};
