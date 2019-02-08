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

	enum direction {
		UP, DOWN, LEFT, RIGHT, NONE
	}direccion;

	enum state {
		left_right, up_down, trigger
	}stado;

	bool holded;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int score;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float time_To_Change;
	class USphereComponent * collider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector direction;

	bool in_Path_Point;

	bool power_Up;

	FTimerHandle UnusedHandle;
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

	void Up();
	void Down();
	void Right();
	void Left();

	void Reset_Direction();

	void Send_Direction();

	void reset_Path_Point();

	void reset_Mecanica();

	bool check_Power_Up();

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
