// Fill out your copyright notice in the Description page of Project Settings.

#include "PositionReport.h"
#include "Runtime/Engine/Classes/Gameframework/Actor.h"

// **IWYU Reference

// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();

	FString ObjectName = GetOwner()->GetName();
	FString ObjectPos = GetOwner()->GetTransform().GetLocation().ToString();
	FString ObjectPosX = FString::SanitizeFloat(GetOwner()->GetTransform().GetLocation().X);
	FString ObjectPosY = FString::SanitizeFloat(GetOwner()->GetTransform().GetLocation().Y);

	UE_LOG(LogTemp, Warning, TEXT("%s is at %s (%s, %s)"), *ObjectName, *ObjectPos, *ObjectPosX, *ObjectPosY);
}


// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

