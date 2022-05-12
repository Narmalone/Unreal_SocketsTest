// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "other.generated.h"

UCLASS()
class SOCKETTEST_API Aother : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Aother();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
