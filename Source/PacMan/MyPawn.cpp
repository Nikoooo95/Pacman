// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Components/InputComponent.h"
#include <Engine.h>
#include "MyTriggerBox.h"
#include "Point.h"
#include "Ghost.h"

// Sets default values
AMyPawn::AMyPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	speed = 100;
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	APlayerController * player_Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	collider = dynamic_cast<USphereComponent*>(GetComponentByClass(USphereComponent::StaticClass()));
	if (collider) {
		collider->OnComponentBeginOverlap.AddDynamic(this, &AMyPawn::OnOverlapBegin);
		collider->OnComponentEndOverlap.AddDynamic(this, &AMyPawn::OnOverlapEnd);
	}
	EnableInput(player_Controller);

	in_Trigger = false;
	direction_State = LEFT;
	score = 0;
	button_Pressed = false;
	power_Up = false;	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorWorldOffset(direction * DeltaTime, true);
	if (button_Pressed) {
		button_Pressed = false;
		Send_Direction();
	}
	
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("Up", IE_Pressed, this, &AMyPawn::Up);
	InputComponent->BindAction("Down", IE_Pressed, this, &AMyPawn::Down);
	InputComponent->BindAction("Right", IE_Pressed, this, &AMyPawn::Right);
	InputComponent->BindAction("Left", IE_Pressed, this, &AMyPawn::Left);
}

//Envia al Pawn hacia arriba
void AMyPawn::Up() {
	direction_State = UP;
	button_Pressed = true;
	GetWorld()->GetTimerManager().SetTimer(UnusedHandle, this, &AMyPawn::Reset_Direction, 1.0f, false, 0.5f);
}

//Envia al Pawn hacia abajo
void AMyPawn::Down() {
	direction_State = DOWN;
	button_Pressed = true;
	GetWorld()->GetTimerManager().SetTimer(UnusedHandle, this, &AMyPawn::Reset_Direction, 1.0f, false, 0.5f);

}

//Envia al Pawn hacia derecha
void AMyPawn::Right() {
	direction_State = RIGHT;
	button_Pressed = true;
	GetWorld()->GetTimerManager().SetTimer(UnusedHandle, this, &AMyPawn::Reset_Direction, 1.0f, false, 0.5f);
}

//Envia al Pawn hacia izquierda
void AMyPawn::Left() {
	direction_State = LEFT;
	button_Pressed = true;
	GetWorld()->GetTimerManager().SetTimer(UnusedHandle, this, &AMyPawn::Reset_Direction, 1.0f, false, 0.5f);
}

//Reinica los valores de control de direccion
void AMyPawn::Reset_Direction() {
	direction_State = NONE;
	button_Pressed = false;
}

//Selecciona la direccion a la que enviar al Pawn
void AMyPawn::Send_Direction() {
	switch (direction_State) {
	case UP:
		direction = FVector(0, -speed, 0);
		break;
	case DOWN:
		direction = FVector(0, speed, 0);
		break;
	case RIGHT:
		direction = FVector(speed, 0, 0);
		break;
	case LEFT:
		direction = FVector(-speed, 0, 0);
		break;
	case NONE:
		break;
	}

	Reset_Direction();
}

//Pone a false la variable in_Trigger
void AMyPawn::Reset_Trigger() {
	in_Trigger = false;
}

//Pone a false la variable de Power_Up
void AMyPawn::Reset_Power_Up() {
	power_Up = false;
	/*for (TActorIterator<AGhost> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		ActorItr->Reverse_Power_Up();
	}*/
}

//Evento de entrada de Colision con el Pawn
void AMyPawn::OnOverlapBegin(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	AMyTriggerBox * trigger_Box = Cast<AMyTriggerBox>(OtherActor);
	if (trigger_Box != nullptr && !in_Trigger) {
		//Si entra en un trigger
		in_Trigger = true;
	}
}

//Evento de salida de Colision con el Pawn
void AMyPawn::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	AMyTriggerBox * trigger_Box = Cast<AMyTriggerBox>(OtherActor);
	if (trigger_Box != nullptr && in_Trigger) {
		//Si sale del trigger
		Reset_Direction();
		Reset_Trigger();
	} else {
		APoint * point = Cast<APoint>(OtherActor);
		//Si sale de encontrarse con un punto, aumenta la puntuacion
		if (point != nullptr) {
			score += point->Get_Value();
			if (point->Get_Value() == 10) {
				power_Up = true;
				for (TActorIterator<AGhost> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
					ActorItr->Change_To_Power_Up();
				}
				//GetWorld()->GetTimerManager().SetTimer(UnusedHandle, this, &AMyPawn::Reset_Power_Up, 1.0f, false, 2.0f);
			}
			point->Destroy();
		}
	}
}


