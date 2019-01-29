// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class PACMAN_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	


	UPROPERTY(EditAnywhere, Category = "Direction")
		int32 direction;


	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* mesh;


	/*UPROPERTY(EditAnywhere)
		class UBoxComponent* collider;*/

	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
		USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	//OnTriggerEnter -> Cuando entre en zona de acci�n de un sem�foro
	UFUNCTION()
		void OnTriggerEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//OnTriggerExit -> Cuando salga de zona de acci�n de un sem�foro
	UFUNCTION()
		void OnTriggerExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	
};
