// Fill out your copyright notice in the Description page of Project Settings.


#include "myData.h"

// Sets default values for this component's properties
UmyData::UmyData()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	PV = 10;
}


// Called when the game starts
void UmyData::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UmyData::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


int UmyData::GetPV() {
	return PV;
}

void UmyData::ApplyDammage(int Value) {
	PV -= Value;
}
