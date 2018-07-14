// Copyright Shawn Kim 2018

#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber Instanciated!"));

	FindPhysicsHandleComponent();
	SetupInputComponent();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PhysicsHandle) { return; }

	/// if the physics handle is attached
	if (PhysicsHandle->GrabbedComponent) {
		/// move the object to where the holder is
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
	}
}


void UGrabber::Grab() {
	// UE_LOG(LogTemp, Warning, TEXT("UGrabber::Grab() Called"));

	/// Try and reach any actors with physics body collision channel set
	auto HitResult = GetFirstPhysicisBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

	/// If hit something then attach a physics handle
	if (ActorHit) {

		if (!PhysicsHandle) { return; }
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			ComponentToGrab,
			EName::NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			ComponentToGrab->GetOwner()->GetActorRotation()
		);
	}
}


void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("UGrabber::Release() Called"));

	if (!PhysicsHandle) { return; }
	PhysicsHandle->ReleaseComponent();
}


void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s -> Missing physics handle component"), *GetOwner()->GetName());
	}

}


void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent)
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s -> Found Input Component"), *GetOwner()->GetName());

		/// bind the input axis
		InputComponent->BindAction("Grab", EInputEvent::IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", EInputEvent::IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s -> Missing Input Component"), *GetOwner()->GetName());
	}

}


const FHitResult UGrabber::GetFirstPhysicisBodyInReach()
{
	/// Line-trace
	FHitResult Hit;

	/// QueryParams for LineTraceSingleByObjectType
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		GetReachLineStart(),
		GetReachLineEnd(), 
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	/// for debugging
	AActor* HitActor = Hit.GetActor();
	if (HitActor) {
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *(HitActor->GetName()));
	}

	return Hit;
}


FVector UGrabber::GetReachLineStart() const {

	/// Get FirstPlayer ViewPoint Location, Rotation
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	/// View Point (Guide line by DrawDebugLine)
	return PlayerViewPointLocation;
}

FVector UGrabber::GetReachLineEnd() const {

	/// Get FirstPlayer ViewPoint Location, Rotation
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	/// View Point (Guide line by DrawDebugLine)
	return PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);
}