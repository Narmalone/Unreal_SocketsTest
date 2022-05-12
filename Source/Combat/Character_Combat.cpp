// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_Combat.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Math/Rotator.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACharacter_Combat::ACharacter_Combat()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera_Arm"));
	CameraArm->SetupAttachment(GetRootComponent());
	CameraArm->TargetArmLength = 150.f;

	myCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Ma_Camera"));
	myCamera->SetupAttachment(CameraArm);

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 525.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->AirControl = 500.f;
	
}

// Called when the game starts or when spawned
void ACharacter_Combat::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacter_Combat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bPressedJump == true) {

	}
}

// Called to bind functionality to input
void ACharacter_Combat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//check si le player input component est pas null
	check(PlayerInputComponent);

	//Players Binding
	
	//jump
	PlayerInputComponent->BindAction("Jump",IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump",IE_Released, this, &ACharacter::StopJumping);

	//Translate
	PlayerInputComponent->BindAxis("MoveForward", this, &ACharacter_Combat::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACharacter_Combat::MoveRight);


	//rotate
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ACharacter_Combat::Turn);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ACharacter_Combat::LookUp);
}

void ACharacter_Combat::MoveForward(float value) {
	if (Controller!= nullptr && value != .0f) {

		//Création des rotators
		const FRotator rot = Controller->GetControlRotation();
		const FRotator yawRot(0.f, rot.Yaw, 0.f);

		const FVector direction = FRotationMatrix(yawRot).GetUnitAxis(EAxis::X);
		AddMovementInput(direction, value);
	}
}
void ACharacter_Combat::MoveRight(float value) {
	if (Controller != nullptr && value != .0f) {

		//Création des rotators
		const FRotator rot = Controller->GetControlRotation();
		const FRotator yawRot(0.f, rot.Yaw, 0.f);

		const FVector direction = FRotationMatrix(yawRot).GetUnitAxis(EAxis::Y);
		AddMovementInput(direction, value);
	}
}
void ACharacter_Combat::Turn(float value) {
	AddControllerYawInput(value * turnRate * GetWorld()->GetDeltaSeconds());
}

void ACharacter_Combat::LookUp(float value) {
	AddControllerPitchInput(value * lookRate * GetWorld()->GetDeltaSeconds());
}

