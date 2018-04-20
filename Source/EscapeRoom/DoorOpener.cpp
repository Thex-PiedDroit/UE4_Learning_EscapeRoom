
#include "DoorOpener.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"


UDoorOpener::UDoorOpener()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UDoorOpener::BeginPlay()
{
	Super::BeginPlay();

	m_pOwner = GetOwner();
	m_fInitialYaw = m_pOwner->GetActorRotation().Yaw;

	m_pPressurePlate->OnActorBeginOverlap.AddDynamic(this, &UDoorOpener::AddOverlappingObject);
	m_pPressurePlate->OnActorEndOverlap.AddDynamic(this, &UDoorOpener::RemoveOverlappingObject);
}

void UDoorOpener::TickComponent(float fDeltaTime, ELevelTick eTickType, FActorComponentTickFunction* pThisTickFunction)
{
	Super::TickComponent(fDeltaTime, eTickType, pThisTickFunction);

	if (m_ucOverlappingObjectsCount > 0)
		OpenDoor(fDeltaTime);
	else
		CloseDoor(fDeltaTime);
}

void UDoorOpener::OpenDoor(float fDeltaTime)
{
	if (m_fCurrentLocalRotation >= 90.0f)
	{
		m_fCurrentLocalRotation = 90.0f;
		return;
	}

	m_fCurrentLocalRotation += m_fRotationPerSecond * fDeltaTime;
	ApplyNewRotation();
}

void UDoorOpener::CloseDoor(float fDeltaTime)
{
	if (m_fCurrentLocalRotation <= 0.0f)
	{
		m_fCurrentLocalRotation = 0.0f;
		return;
	}

	m_fCurrentLocalRotation -= m_fRotationPerSecond * fDeltaTime;
	ApplyNewRotation();
}

void UDoorOpener::ApplyNewRotation()
{
	FRotator tRotator = m_pOwner->GetActorRotation();
	tRotator.Yaw = m_fInitialYaw - m_fCurrentLocalRotation;
	m_pOwner->SetActorRotation(tRotator.Quaternion());
}
