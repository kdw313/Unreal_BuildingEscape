// Copyright Shawn Kim 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnOpenDoor;
	
	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnCloseDoor;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:	
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr; // Trigger area
	
	UPROPERTY(EditAnywhere)
	float TriggerMass = 30.0f;

	// returns total mass
	float GetTotalMassOfActorsOnPlate();

	AActor * Owner;
};
