// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyTriggerBox.h"
#include "MyPawn.generated.h"


UCLASS()
class PACMAN_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:

	//Direcciones posibles
	enum DIRECTIONS {
		UP, DOWN, LEFT, RIGHT, NONE
	}direction_State;

	//Puntuacion del jugador
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int score;

	//Velocidad del direccion
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float speed;

	//Direccion del Pawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector direction;

	//False: no se ha pulsado un boton. True: se ha pulsado un boton
	bool button_Pressed;

	//Collider del Pawn
	class USphereComponent * collider;

	//False: no está en Trigger. True: está en Trigger
	bool in_Trigger;

	//False: no está activa el Power Up. True: está activado el Power Up
	bool power_Up;

	//Handler del Timer para los delay
	FTimerHandle UnusedHandle;

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Envia al Pawn hacia arriba
	void Up();

	//Envia al Pawn hacia abajo
	void Down();

	//Envia al Pawn hacia derecha
	void Right();

	//Envia al Pawn hacia izquierda
	void Left();

	//Reinica los valores de control de direccion
	void Reset_Direction();

	//Selecciona la direccion a la que enviar al Pawn
	void Send_Direction();

	//Pone a false la variable in_Trigger
	void Reset_Trigger();

	//Pone a false la variable de Power_Up
	void Reset_Power_Up();

	//Evento de entrada de Colision con el Pawn
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	//Evento de salida de Colision con el Pawn
	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
