// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved


#include "CatPlayerCameraPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "CatPlayerStatics.h"


// Sets default values
ACatPlayerCameraPawn::ACatPlayerCameraPawn() : Super()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FixedRoot = CreateDefaultSubobject<USceneComponent>(TEXT("PawnRoot"));
	RootComponent = FixedRoot;
	MovementComp = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("CustomMovementComponent"));
	MovementComp->UpdatedComponent = RootComponent;
	
	
	CamBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	Cam = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	CamBoom->SetupAttachment(FixedRoot);
	Cam->SetupAttachment(CamBoom, CamBoom->SocketName);

	CamBoom->SetRelativeRotation(FRotator(-90, 180.f, 0.f));
	CamBoom->TargetArmLength = 900.f;
	CamBoom->bDoCollisionTest = false;
	CamBoom->bEnableCameraLag = true;
	CamBoom->CameraLagSpeed = 5.0f;

	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw	= true;

	// Local Player only
	AutoPossessAI			= EAutoPossessAI::Disabled;
	AutoPossessPlayer		= EAutoReceiveInput::Player0;
	AIControllerClass		= nullptr;
	bOnlyRelevantToOwner	= true;
	bReplicateMovement		= false;
	bReplicates				= false;
	bNetLoadOnClient		= false;

	// Disable Gameplay capabilities
	bCanBeDamaged = false;
}

// Called when the game starts or when spawned
void ACatPlayerCameraPawn::BeginPlay()
{
	Super::BeginPlay();
	ZoomDistance = CamBoom->TargetArmLength;
	bRotateMode = false;
}

// Called every frame
void ACatPlayerCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bRotateMode)
		return;

	const auto BorderMove = FVector(UCatPlayerStatics::MouseScreenBorderMove(this, 0.1f, 0.1f, true /* Camera is always rotated*/, false), 0.f); // 0.1 is arbitrary
	MoveCamera(BorderMove, (ZoomDistance* ZoomDistance) / 1500000.f); // 1500000 is arbitrary

	if (ActorToFollow)
		ZoomOnActor(ActorToFollow);
}

// Called to bind functionality to input
void ACatPlayerCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UPawnMovementComponent* ACatPlayerCameraPawn::GetMovementComponent() const
{
	return MovementComp;
}

void ACatPlayerCameraPawn::MoveCamera(const FVector& Input, float Scale)
{
	MovementComp->AddInputVector(Input * Scale, false);
}

void ACatPlayerCameraPawn::RotateCameraUp(float Input, float Scale)
{
	if (!bRotateMode)
		return;
	const auto Rot = GetControlRotation();
	const auto newRot = Rot.Pitch + (Input * Scale);
	if (newRot < 180.f && newRot > 80.f)
		AddControllerPitchInput(Input * Scale);

}

void ACatPlayerCameraPawn::RotateCameraRight(float Input, float Scale)
{
	if (!bRotateMode)
		return;

	AddControllerYawInput(Input * Scale);
}

void ACatPlayerCameraPawn::Zoom(float Delta, float Scale)
{
	ZoomDistance = FMath::Clamp<float>((Scale * -1.f * Delta) + ZoomDistance, 200.f, 5000.f);
	CamBoom->TargetArmLength = FMath::FInterpTo(CamBoom->TargetArmLength, ZoomDistance, GetWorld()->GetDeltaSeconds(), 5.0f);
}

void ACatPlayerCameraPawn::ZoomOnActor(const AActor* Target)
{
	if (!Target)
		return;
	FVector Origin, Span;
	Target->GetActorBounds(false, Origin, Span);
	ZoomDistance = Span.Size2D() * 2;
	SetActorLocation(Origin, false, nullptr, ETeleportType::TeleportPhysics);
}

void ACatPlayerCameraPawn::SetActorToFollow(AActor* Target)
{
	if (!Target)
		return;
	ActorToFollow = Target;
	ZoomOnActor(ActorToFollow);
}

