#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance_Combat.generated.h"

/**
 * 
 */
UCLASS()
class COMBAT_API UMyAnimInstance_Combat : public UAnimInstance
{
	GENERATED_BODY()
public:
	
	virtual void NativeInitializeAnimation() override;

	UFUNCTION(BlueprintCallable, Category = Animation)
	void UpdateAnimationAxis();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Chara)
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Chara)
	class APawn* myPawn;

	UFUNCTION(BlueprintCallable, Category = Animation)
		void CallJump();

};
