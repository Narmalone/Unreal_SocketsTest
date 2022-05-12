// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data_Cpp.generated.h"

UCLASS()
class SOCKETTEST_API AData_Cpp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AData_Cpp();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Items | RotateObject")
	float PitchValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Items | RotateObject")
	float YawValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Items | RotateObject")
	float RollValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items | RotateObject")
	bool isTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items | Vector")
	FVector CurrentLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Items | Vector")
    FVector newLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Items | Vector")
	float SpeedToGo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items | RotateObject")
		float deltaSeconds;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items | Collision")
	class USphereComponent* CollideSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items | Particles")
	class UParticleSystemComponent* IdleParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items | Particles")
	class UParticleSystem* OverlapParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items | Sounds")
	class USoundCue* OverlapSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void onOverlapBeggin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void onOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void MoveTo();
};
