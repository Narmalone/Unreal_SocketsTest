// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance_Combat.h"

void UMyAnimInstance_Combat::NativeInitializeAnimation()
{
	if (myPawn == nullptr) {
		myPawn = TryGetPawnOwner();
	}
}

void UMyAnimInstance_Combat::UpdateAnimationAxis()
{
	if (myPawn) {
		FVector SpeedVec = myPawn->GetVelocity();
		FVector HorizontalSpeed = FVector(SpeedVec.X, SpeedVec.Z, 0.f);

		Speed = HorizontalSpeed.Size();
	}
}

void UMyAnimInstance_Combat::CallJump()
{
	
}
