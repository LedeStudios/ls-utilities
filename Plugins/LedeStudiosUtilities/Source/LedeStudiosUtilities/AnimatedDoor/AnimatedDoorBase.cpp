// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimatedDoorBase.h"


AAnimatedDoorBase::AAnimatedDoorBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Door = CreateDefaultSubobject<USkeletalMeshComponent>("Door");
	SetRootComponent(Door);
}

void AAnimatedDoorBase::BeginPlay()
{
	Super::BeginPlay();

	UAnimInstance* Anim = Door->GetAnimInstance();
	checkf(Anim, TEXT("AAnimatedDoorBase::BeginPlay: The Animation Instance for the Door actor must be registered."));

	Anim->OnMontageStarted.AddDynamic(this, &AAnimatedDoorBase::OnAnimationStarted);
	Anim->OnMontageEnded.AddDynamic(this, &AAnimatedDoorBase::OnAnimationEnded);
	
	// Set Door is Opened
	if (bIsOpened)
	{
		Door->SetAnimation(OpenAnimation);
		Door->SetPosition(1.f, false);
	}
}

void AAnimatedDoorBase::OpenDoor() const
{
	if (bIsWorking)
	{
		return;
	}
	
	// Play animation when door is closed
	if (!bIsOpened)
	{
		if (OpenAnimation)
		{
			Door->Stop();
			Door->PlayAnimation(OpenAnimation, false);
		}
	}
}

void AAnimatedDoorBase::CloseDoor() const
{
	if (bIsWorking)
	{
		return;
	}
	
	// Play animation when door is opened
	if (bIsOpened)
	{
		if (CloseAnimation)
		{
			Door->Stop();
			Door->PlayAnimation(CloseAnimation, false);
		}
	}
}

bool AAnimatedDoorBase::IsOpened() const
{
	return bIsOpened;
}

bool AAnimatedDoorBase::IsWorking() const
{
	return bIsWorking;
}

void AAnimatedDoorBase::SetProgress(float InProgress) const
{
	InProgress = FMath::Clamp(InProgress, 0.f, 1.f);
	Door->SetPosition(InProgress);
}

void AAnimatedDoorBase::OnAnimationStarted(UAnimMontage* Montage)
{
	bIsWorking = true;
}

void AAnimatedDoorBase::OnAnimationEnded(UAnimMontage* Montage, bool bInterrupted)
{
	bIsWorking = false;

	// Close Door
	if (bIsOpened)
	{
		bIsOpened = false;
		if (OnDoorClosed.IsBound())
		{
			OnDoorClosed.Broadcast();
		}
		return;
	}

	// Open Door
	bIsOpened = true;
	if (OnDoorOpened.IsBound())
	{
		OnDoorClosed.Broadcast();
	}
}
