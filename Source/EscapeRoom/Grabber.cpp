
#include "Grabber.h"

#include "Components/InputComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"


UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	m_pPlayerController = GetWorld()->GetFirstPlayerController();

	m_pInputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	checkf(m_pInputComponent != nullptr, TEXT("No input component on %s"), *(GetOwner()->GetName()));
	m_pInputComponent->BindAction("Interact", IE_Pressed, this, &UGrabber::GrabWhatsInFrontOfMe);
	m_pInputComponent->BindAction("Interact", IE_Released, this, &UGrabber::ReleaseWhateverImHolding);

	m_pPhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	checkf(m_pPhysicsHandle != nullptr, TEXT("No physics handle on %s"), *(GetOwner()->GetName()));
}

void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_pPhysicsHandle->GrabbedComponent != nullptr)
		UpdateGrabbedObject();
}

void UGrabber::GrabWhatsInFrontOfMe()
{
	UpdateEyesData();

	FHitResult tHit;
	if (GetWorld()->LineTraceSingleByObjectType(OUT tHit, m_tEyesPos, m_tEyesPos + (m_tEyesRotation.Vector() * m_fReach), FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), FCollisionQueryParams(FName(TEXT("Nothing")), false, GetOwner())))
		m_pPhysicsHandle->GrabComponentAtLocationWithRotation(tHit.GetComponent(), tHit.BoneName, tHit.ImpactPoint, tHit.Actor->GetActorRotation());
	else
		ReleaseWhateverImHolding();
}

void UGrabber::UpdateGrabbedObject()
{
	UpdateEyesData();
	m_pPhysicsHandle->SetTargetLocation(m_tEyesPos + (m_tEyesRotation.Vector() * m_fReach));
}

void UGrabber::ReleaseWhateverImHolding()
{
	m_pPhysicsHandle->ReleaseComponent();
}

void UGrabber::UpdateEyesData()
{
	m_pPlayerController->GetPlayerViewPoint(OUT m_tEyesPos, OUT m_tEyesRotation);
}
