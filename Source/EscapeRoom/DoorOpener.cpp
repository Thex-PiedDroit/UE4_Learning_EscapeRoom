
#include "DoorOpener.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"


UDoorOpener::UDoorOpener()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDoorOpener::BeginPlay()
{
	Super::BeginPlay();

	m_pOwner = GetOwner();
	m_tInitialRotation = m_pOwner->GetActorRotation();

	if (m_pPressurePlate != nullptr)
	{
		m_pPressurePlate->OnActorBeginOverlap.AddDynamic(this, &UDoorOpener::AddOverlappingObject);
		m_pPressurePlate->OnActorEndOverlap.AddDynamic(this, &UDoorOpener::RemoveOverlappingObject);
	}
}

void UDoorOpener::AddOverlappingObject(AActor* pMe, AActor* pOther)
{
	++m_ucOverlappingObjectsCount;
	if (m_ucOverlappingObjectsCount == 1)
		OnDoorOpenRequest.Broadcast();
}

void UDoorOpener::RemoveOverlappingObject(AActor* pMe, AActor* pOther)
{
	--m_ucOverlappingObjectsCount;
	if (m_ucOverlappingObjectsCount == 0)
		OnDoorCloseRequest.Broadcast();
}

void UDoorOpener::TickComponent(float fDeltaTime, ELevelTick eTickType, FActorComponentTickFunction* pThisTickFunction)
{
	Super::TickComponent(fDeltaTime, eTickType, pThisTickFunction);
}
