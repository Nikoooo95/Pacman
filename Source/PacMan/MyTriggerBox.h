// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "MyTriggerBox.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_API AMyTriggerBox : public ATriggerBox
{
	GENERATED_BODY()


public:
	int distance;
	FVector direction;
	bool readyToBeUpdated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float offset_X;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float offset_Y;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool gate_Up;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool gate_Down;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool gate_Right;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool gate_Left;

public:
	// Sets default values for this actor's properties
	AMyTriggerBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	FVector get_Direction();
	
	FVector up();
	FVector down();
	FVector right();
	FVector left();

};
