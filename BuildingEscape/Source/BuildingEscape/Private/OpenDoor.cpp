// Copyright Shawn Kim 2018

#include "OpenDoor.h"
#include "Runtime/Engine/Classes/Gameframework/Actor.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// when the specified actor is on the plate(volume)
	if (PressurePlate->IsOverlappingActor(ActorThatOpens)) 
	{
		OpenDoor();
	}
}


void UOpenDoor::OpenDoor()
{
	// don't forget to set the object that's gonna be moved from static -> Movable
	// Referencing owner
	AActor* MyOwner = GetOwner();

	// Pitch(Y), Yaw(Z), Roll(X)
	FRotator NewRotator = FRotator(0.0f, OpenAngle, 0.0f);

	// Set Actor's rotation
	MyOwner->SetActorRotation(NewRotator);
}
