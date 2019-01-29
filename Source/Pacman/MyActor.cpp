// Fill out your copyright notice in the Description page of Project Settings.

#include "MyActor.h"

#include "Components/StaticMeshComponent.h"


// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	//RootComponent = mesh;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachTo(Root);
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	//collider->OnComponentBeginOverlap.AddDynamic(this, &AMyActor::OnTriggerEnter);
	//collider->OnComponentEndOverlap.AddDynamic(this, &AMyActor::OnTriggerExit);
	//collider->OnComponentBeginOverlap.AddDynamic(this, &ACar::OnTriggerEnter);
	//collider->OnComponentEndOverlap.AddDynamic(this, &ACar::OnTriggerExit);
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyActor::OnTriggerEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

}

//Si sale del campo de acción de un semáforo, le pide que le borre de la lista y libere el permiso
void AMyActor::OnTriggerExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {


}