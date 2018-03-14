// Copyright Shawn Kim 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"

#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:

	// Distance from the center of the pawn
	UPROPERTY(EditAnywhere)
	float Reach = 100.0f;
	
	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UInputComponent* InputComponent = nullptr;

	// Look for attached Physics Handle
	void FindPhysicsHandleComponent();

	// Look for attached Input Component only in runtime
	void SetupInputComponent();

	// Ray-cast and grab what's in reach
	void Grab();

	// Release what's in reach and grabbed
	void Release();

	// Returns 
	const FHitResult GetFirstPhysicisBodyInReach();

	// Returns Start of Current ReachLine  
	FVector GetReachLineEnd() const;

	// Returns End of Current ReachLine
	FVector GetReachLineStart() const;
};