// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "myData.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOCKETTEST_API UmyData : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UmyData();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player's Variable | life")
	int PV;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	

	int GetPV();
	void ApplyDammage(int Value);
};
