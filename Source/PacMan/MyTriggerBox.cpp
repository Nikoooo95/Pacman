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

}
// Called every frame
void AMyTriggerBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FVector AMyTriggerBox::Get_Direction(){

	AActor * player = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn();

	offset_X = player->GetActorLocation().X - this->GetActorLocation().X;
	offset_Y = player->GetActorLocation().Y - this->GetActorLocation().Y;

	if (abs(offset_X) > abs(offset_Y)) {
		if (offset_X >= 0 && gate_Right) {
			return Right();
		} else if (offset_X < 0 && gate_Left) {
			return Left();
		} else {
			if (offset_Y >= 0 && gate_Down) {
				return Down();
			} else if (offset_Y < 0 && gate_Up) {
				return Up();
			}
		}
	} else {
		if (offset_Y >= 0 && gate_Down) {
			return Down();
		} else if (offset_Y < 0 && gate_Up) {
			return Up();
		} else {
			if (offset_X >= 0 && gate_Right) {
				return Right();
			} else if (offset_X < 0 && gate_Left) {
				return Left();
			}
		}
	}
	return FVector(0, 0, 0);
}

//Devuelve el vector arriba
FVector AMyTriggerBox::Up() {
	
	return FVector(0, -1, 0);
}

//Devuelve el vector abajo
FVector AMyTriggerBox::Down() {
	
	
	return FVector(0, 1, 0);
}

//Devuelve el vector derecha
FVector AMyTriggerBox::Right() {

	return FVector(1, 0, 0);
}

//Devuelve el vector izquierda
FVector AMyTriggerBox::Left() {
	
	return FVector(-1, 0, 0);
}