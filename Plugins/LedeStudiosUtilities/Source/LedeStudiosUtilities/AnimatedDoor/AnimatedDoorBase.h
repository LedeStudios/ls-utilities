// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AnimatedDoorBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDoorDelegate);

UCLASS()
class LEDESTUDIOSUTILITIES_API AAnimatedDoorBase : public AActor
{
	GENERATED_BODY()

public:
	AAnimatedDoorBase();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AnimatedDoor")
	TObjectPtr<USkeletalMeshComponent> Door;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AnimatedDoor")
	TObjectPtr<UAnimSequence> OpenAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AnimatedDoor")
	TObjectPtr<UAnimSequence> CloseAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AnimatedDoor")
	bool bIsOpened = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AnimatedDoor")
	bool bIsWorking = false;
	
public:
	UFUNCTION(BlueprintCallable, Category="AnimatedDoor")
	void OpenDoor() const;

	UFUNCTION(BlueprintCallable, Category="AnimatedDoor")
	void CloseDoor() const;

	UFUNCTION(BlueprintCallable, Category="AnimatedDoor")
	bool IsOpened() const;

	UFUNCTION(BlueprintCallable, Category="AnimatedDoor")
	bool IsWorking() const;
	
	UFUNCTION(BlueprintCallable, Category="AnimatedDoor")
	void SetProgress(float InProgress) const;

public:
	UPROPERTY(BlueprintAssignable, Category="AnimatedDoor")
	FOnDoorDelegate OnDoorOpened;

	UPROPERTY(BlueprintAssignable, Category="AnimatedDoor")
	FOnDoorDelegate OnDoorClosed;

private:
	UFUNCTION()
	void OnAnimationStarted(UAnimMontage* Montage);
	
	UFUNCTION()
	void OnAnimationEnded(UAnimMontage* Montage, bool bInterrupted);
	
};
