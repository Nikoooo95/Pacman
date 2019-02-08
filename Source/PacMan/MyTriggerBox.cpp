// Fill out your copyright notice in the Description page of Project Settings.

#include "MyTriggerBox.h"
#include <Engine.h>

// Sets default values
AMyTriggerBox::AMyTriggerBox()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyTriggerBox::BeginPlay()
{
	Super::BeginPlay();
	direction = get_Direction();

}
// Called every frame
void AMyTriggerBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	readyToBeUpdated = true;

}

FVector AMyTriggerBox::get_Direction()
{
	FVector new_direction;
	AActor * player = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn();
	offset_X = player->GetActorLocation().X - this->GetActorLocation().X;
	offset_Y = player->GetActorLocation().Y - this->GetActorLocation().Y;
	if (abs(offset_X) > abs(offset_Y)) {
		if (offset_X >= 0 && gate_Right) {
			//UE_LOG(LogTemp, Warning, TEXT("1 Right"));
			return right();
		} else if (offset_X < 0 && gate_Left) {
			//UE_LOG(LogTemp, Warning, TEXT("1 Left"));
			return left();
		} else {
			if (offset_Y >= 0 && gate_Down) {
				//UE_LOG(LogTemp, Warning, TEXT("1 Down"));
				return down();
			} else if (offset_Y < 0 && gate_Up) {
				//UE_LOG(LogTemp, Warning, TEXT("1 Up"));
				return up();
			}
		}
	} else {
		if (offset_Y >= 0 && gate_Down) {
			//UE_LOG(LogTemp, Warning, TEXT("2 Down"));
			return down();
		} else if (offset_Y < 0 && gate_Up) {
			//UE_LOG(LogTemp, Warning, TEXT("2 Up"));
			return up();
		} else {
			if (offset_X >= 0 && gate_Right) {
				//UE_LOG(LogTemp, Warning, TEXT("2 Right"));
				return right();
			} else if (offset_X < 0 && gate_Left) {
				//UE_LOG(LogTemp, Warning, TEXT("2 Left"));
				return left();
			}
		}
	}
	return new_direction;
}

FVector AMyTriggerBox::up() {
	
	return FVector(0, -1, 0);
}


FVector AMyTriggerBox::down() {
	
	
	return FVector(0, 1, 0);
}

FVector AMyTriggerBox::left() {
	
	return FVector(-1, 0, 0);
}


FVector AMyTriggerBox::right() {
	
	return FVector(1, 0, 0);
}