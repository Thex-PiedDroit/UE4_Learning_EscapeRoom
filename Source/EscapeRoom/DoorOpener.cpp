
#include "DoorOpener.h"
#include "GameFramework/Actor.h"


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
}

void UDoorOpener::TickComponent(float fDeltaTime, ELevelTick eTickType, FActorComponentTickFunction* pThisTickFunction)
{
	Super::TickComponent(fDeltaTime, eTickType, pThisTickFunction);

	FRotator tRotator = m_pOwner->GetActorRotation();

	float fFrameRotation = m_fRotationPerSecond * fDeltaTime;

	if (!m_bOpened)
	{
		m_fCurrentLocalRotation += fFrameRotation;
		if (m_fCurrentLocalRotation >= 90.0f)
		{
			m_fCurrentLocalRotation = 90.0f;
			m_bOpened = true;
		}
	}
	else
	{
		m_fCurrentLocalRotation -= fFrameRotation;
		if (m_fCurrentLocalRotation <= 0.0f)
		{
			m_fCurrentLocalRotation = 0.0f;
			m_bOpened = false;
		}
	}

	tRotator.Yaw = m_fInitialYaw - m_fCurrentLocalRotation;

	m_pOwner->SetActorRotation(tRotator.Quaternion());
}
