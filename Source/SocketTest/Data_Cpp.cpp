// Fill out your copyright notice in the Description page of Project Settings.


#include "Data_Cpp.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Sound/SoundCue.h"
#include "Engine/SkeletalMeshSocket.h"
#include "CharacterWeapon.h"
#include "myData.h"
// Sets default values
AData_Cpp::AData_Cpp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//collide setup
	CollideSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollideSphere"));
	RootComponent = CollideSphere;

	//Mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal"));
	Weapon->SetupAttachment(GetRootComponent());	

	//Particle
	IdleParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Idle_Particule"));
	IdleParticle->SetupAttachment(GetRootComponent());

	//Set value of rotation object
	PitchValue = .0f;
	YawValue = .0f;
	RollValue = .0f;
	isTrigger = false;

	CurrentLocation = this->GetActorLocation();
	SpeedToGo = 150.f;

	//Get Data
	DataToEnter = CreateDefaultSubobject<UmyData>(TEXT("Database"));
	
}

// Called when the game starts or when spawned
void AData_Cpp::BeginPlay()
{
	Super::BeginPlay();
	CollideSphere->OnComponentBeginOverlap.AddDynamic(this, &AData_Cpp::onOverlapBeggin);
	CollideSphere->OnComponentEndOverlap.AddDynamic(this, &AData_Cpp::onOverlapEnd);
}

// Called every frame
void AData_Cpp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	deltaSeconds = DeltaTime;
	if (isTrigger == true) {
		FQuat rotateObject = FQuat(FRotator(PitchValue, YawValue, RollValue));
		AddActorLocalRotation(rotateObject * DeltaTime, false, 0, ETeleportType::None);
		MoveTo();
	}
	
}

void AData_Cpp::onOverlapBeggin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Enter Collision"));
	isTrigger = true;
	DataToEnter->ApplyDammage(1);
	if (DataToEnter->PV <= 0) {
		DataToEnter->PV = 0;
		Destroy();
	}
	if (OverlapParticle) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OverlapParticle, GetActorLocation(), FRotator(.0f), true);
	}
	//Comme le son et l'autre particle sont pas attach à l'obj etc quand on destroy la particle continue car elle est pas dans l'obj
	if (OverlapSound) {
		UGameplayStatics::PlaySound2D(this, OverlapSound, 2.75f);
	}	
	if (OtherActor) {

		ACharacterWeapon* curChar = Cast<ACharacterWeapon>(OtherActor);
		if (curChar) {
			EquipWeapon(curChar);
		}
	}
}

void AData_Cpp::onOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	isTrigger = false;
	UE_LOG(LogTemp, Warning, TEXT("Exit Collision"));
}

void AData_Cpp::MoveTo()
{

	if (CurrentLocation.Z < newLocation.Z) {
		GetRootComponent()->AddRelativeLocation(CurrentLocation);
		CurrentLocation.Z += SpeedToGo * deltaSeconds;
		UE_LOG(LogTemp, Warning, TEXT("en train de monter"));
	}
	else if (CurrentLocation.Z >= newLocation.Z) {
		CurrentLocation = newLocation;
		UE_LOG(LogTemp, Warning, TEXT("stop"));
	}
}

void AData_Cpp::EquipWeapon(class ACharacterWeapon* myChar) {

	//Ignore collision de la cam
	Weapon->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	Weapon->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	Weapon->SetSimulatePhysics(false);

	const USkeletalMeshSocket* weaponSocket = myChar->GetMesh()->GetSocketByName("WeaponSocket");

	if (Weapon) {
		if (weaponSocket) {
			weaponSocket->AttachActor(this, myChar->GetMesh());
		}
	}
}
