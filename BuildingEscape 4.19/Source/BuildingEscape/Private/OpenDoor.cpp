// Copyright Shawn Kim 2018

#include "OpenDoor.h"
#include "Runtime/Engine/Classes/Gameframework/Actor.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"

#define OUT

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

}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Trigger Volume
	// old code
	// when the specified actor is on the plate(volume)
	if (GetTotalMassOfActorsOnPlate() > TriggerMass) // TODO make into a parameter
	{
		OnOpenDoor.Broadcast();
		UE_LOG(LogTemp, Warning, TEXT("door open"));
	}
	else
	{
		OnCloseDoor.Broadcast();
	}
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.0f;

	TArray<AActor*> OverlappingActors;
	
	if (!PressurePlate) { return TotalMass; }
	
	// find all the overlapping actors
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	for (const auto& Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();

		UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate %d"), *Actor->GetName(), TotalMass);
	}
	
	return TotalMass;
}