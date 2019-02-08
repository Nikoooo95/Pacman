// Fill out your copyright notice in the Description page of Project Settings.

#include "Ghost.h"
#include <Engine.h>
#include "MyTriggerBox.h"
#include "Components/BoxComponent.h"
#include "MyPawn.h"

// Sets default values
AGhost::AGhost()
{
	PrimaryActorTick.bCanEverTick = true;
	collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	collider->OnComponentBeginOverlap.AddDynamic(this, &AGhost::OnBoxBeginOverlap);
}

// Called when the game starts or when spawned
void AGhost::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(UnusedHandle, this, &AGhost::Set_Starting_Speed, 1.0f, true, start_Time);
	starting_Speed = FVector(init_Speed, 0, 0);
	init_Speed = abs(init_Speed);
	init_Pos = this->GetActorLocation();
	power_Up = false;
}

// Called every frame
void AGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorWorldOffset(speed * DeltaTime, true);
}

//Establece la velocidad y direccion inicial
void AGhost::Set_Starting_Speed() {
	speed = starting_Speed;
}

//Cambio de direccion al llegar a un trigger
void AGhost::Change_Speed_Event() {
	speed = init_Speed * direction_Temp;
}

//Evento de colision con otro Collider
void AGhost::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	AMyTriggerBox * trigger_Box = Cast<AMyTriggerBox>(OtherActor);
	if (trigger_Box != nullptr) {
		//Si encuentra un trigger, pide un cambio de direccion
		direction_Temp = trigger_Box->Get_Direction();
		GetWorld()->GetTimerManager().SetTimer(UnusedHandle, this, &AGhost::Change_Speed_Event, 1.0f, false, 1.0f);
	}
		
	AMyPawn * main_Player = Cast<AMyPawn>(OtherActor);
	if (main_Player != nullptr) {
		if (!power_Up) {
			//Si no hay Power Up, se come al Pawn
			GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
		} else {
			//Si hay Power Up, se reinicia su posicion y aumenta su puntuacion
			this->SetActorLocation(init_Pos);
			Set_Starting_Speed();
			main_Player->score += 200;
			Change_To_Normal();
		}
	}

}

//void AGhost::Change_Color_Implementation(){}
void AGhost::Change_To_Normal_Implementation(){}

void AGhost::Change_To_Power_Up_Implementation(){}
