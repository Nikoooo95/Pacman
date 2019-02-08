// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ghost.generated.h"

UCLASS()
class PACMAN_API AGhost : public AActor
{
	GENERATED_BODY()

public:

	//Tiempo de espera hasta el arranque
	UPROPERTY(EditAnywhere)
		float start_Time;

	//Valor de velocidad
	UPROPERTY(EditAnywhere)
		float init_Speed;

	//Collider
	UPROPERTY(EditAnywhere)
		class UBoxComponent* collider;

	//Velocidad actual en cada Tick
	FVector speed;

	//Dirección inicial
	FVector starting_Speed;

	//Posicion inicial del fantasma
	FVector init_Pos;

	//False: Power Up desactivado. True: Power Up activado.
	bool power_Up;

	//Handler de tiempo para los delay
	FTimerHandle UnusedHandle;
	
	//Nueva direccion que debe tomar
	FVector direction_Temp;

	

public:	
	// Sets default values for this actor's properties
	AGhost();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Establece la velocidad y direccion inicial
	void Set_Starting_Speed();
	
	//Cambio de direccion al llegar a un trigger
	void Change_Speed_Event();

	//Activa temporalmente el Power Up
	void Power_Up();

	//Invierte el efecto del Power Up
	void Reverse_Power_Up();

	//Cambia el material del fantasma con el Power Up
	UFUNCTION(BlueprintNativeEvent, Category = "Material")
		void Change_Color();

	//Evento de colision con otro Collider
	UFUNCTION()
		void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
