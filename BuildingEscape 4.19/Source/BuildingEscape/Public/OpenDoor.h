// Copyright Shawn Kim 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenRequest);

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

	// Opens the door
	void OpenDoor();

	// Closes door
	void CloseDoor();

	UPROPERTY(BlueprintAssignable)
		FOnOpenRequest OnOpenRequest;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	float OpenAngle = -90.0f;	//Angle for the door
	
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr; // Trigger area

	UPROPERTY(EditAnywhere)
	float DoorClosingDelay = 1.0f;

	float DoorLastOpenTime;
	
	float GetTotalMassOfActorsOnPlate();

	AActor * Owner;
};
