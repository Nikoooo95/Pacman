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

	//Distancia del jugador a dicho trigger
	float offset_X;
	float offset_Y;

	//Permite ir hacia arriba
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool gate_Up;

	//Permite ir hacia abajo
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool gate_Down;

	//Permite ir hacia derecha
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool gate_Right;

	//Permite ir hacia izquierda
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
	
	//Devuelve la direccion a la que tiene que ir el fantasma
	FVector Get_Direction();
	
	//Devuelve el vector arriba
	FVector Up();

	//Devuelve el vector abajo
	FVector Down();

	//Devuelve el vector derecha
	FVector Right();

	//Devuelve el vector izquierda
	FVector Left();

};
