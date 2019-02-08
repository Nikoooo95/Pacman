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
	in_Path_Point = false;
	direccion = LEFT;
	stado = left_right;
	holded = false;
	power_Up = false;
	Send_Direction();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorWorldOffset(direction * DeltaTime, true);
	if (holded) {
		holded = false;

		if (stado == trigger) {
			GetWorld()->GetTimerManager().SetTimer(UnusedHandle, this, &AMyPawn::Send_Direction, 1.0f, false, time_To_Change);
		} else {
			Send_Direction();
		}
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

void AMyPawn::Up() {

	//if (stado == up_down || in_Path_Point) {
		direccion = UP;
		holded = true;
		GetWorld()->GetTimerManager().SetTimer(UnusedHandle, this, &AMyPawn::Reset_Direction, 1.0f, false, 0.5f);
	//}
}

void AMyPawn::Down() {
	//if (stado == up_down || in_Path_Point) {
		direccion = DOWN;
		holded = true;
		GetWorld()->GetTimerManager().SetTimer(UnusedHandle, this, &AMyPawn::Reset_Direction, 1.0f, false, 0.5f);
	//}
}

void AMyPawn::Right() {
	//if (stado == left_right || in_Path_Point) {
		direccion = RIGHT;
		holded = true;
		GetWorld()->GetTimerManager().SetTimer(UnusedHandle, this, &AMyPawn::Reset_Direction, 1.0f, false, 0.5f);
	//};
}

void AMyPawn::Left() {
	//if (stado == left_right || in_Path_Point) {
		direccion = LEFT;
		holded = true;
		GetWorld()->GetTimerManager().SetTimer(UnusedHandle, this, &AMyPawn::Reset_Direction, 1.0f, false, 0.5f);
	//}
}


void AMyPawn::Reset_Direction() {
	UE_LOG(LogTemp, Warning, TEXT("Cleaning"));
	direccion = NONE;
	holded = false;
}

void AMyPawn::Send_Direction() {
	switch (direccion) {
	case UP:
		stado = up_down;
		direction = FVector(0, -speed, 0);
		break;
	case DOWN:
		stado = up_down;
		direction = FVector(0, speed, 0);
		break;
	case RIGHT:
		stado = left_right;
		direction = FVector(speed, 0, 0);
		break;
	case LEFT:
		stado = left_right;
		direction = FVector(-speed, 0, 0);
		break;
	case NONE:
		break;
	}

	Reset_Direction();
}

void AMyPawn::OnOverlapBegin(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	AMyTriggerBox * trigger_Box = Cast<AMyTriggerBox>(OtherActor);
	if (trigger_Box != nullptr && !in_Path_Point) {
		in_Path_Point = true;
	}
}

void AMyPawn::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	AMyTriggerBox * trigger_Box = Cast<AMyTriggerBox>(OtherActor);
	if (trigger_Box != nullptr && in_Path_Point) {
		Reset_Direction();
		reset_Path_Point();

		UE_LOG(LogTemp, Warning, TEXT("Out"));
	} else {
		APoint * point = Cast<APoint>(OtherActor);
		if (point != nullptr) {
			score += point->get_Value();
			if (point->get_Value() == 10) {
				power_Up = true;
				for (TActorIterator<AGhost> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
					ActorItr->Power_Up();
					//GetWorld()->GetTimerManager().SetTimer(UnusedHandle, this, *ActorItr::change, 1.0f, false, 5.f);
				}
				GetWorld()->GetTimerManager().SetTimer(UnusedHandle, this, &AMyPawn::reset_Mecanica, 1.0f, false, 5.f);
			}
			point->Destroy();
		}
		
	}


}


void AMyPawn::reset_Path_Point() {
	in_Path_Point = false;
}

void AMyPawn::reset_Mecanica() {
	power_Up = false;
}



