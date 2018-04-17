
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DoorOpener.generated.h"


class ATriggerVolume;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ESCAPEROOM_API UDoorOpener : public UActorComponent
{
	GENERATED_BODY()

public:

	UDoorOpener();

	virtual void TickComponent(float fDeltaTime, ELevelTick eTickType, FActorComponentTickFunction* pThisTickFunction) override;

protected:

	virtual void BeginPlay() override;

private:

	void OpenDoor(float fDeltaTime);
	void CloseDoor(float fDeltaTime);
	void ApplyNewRotation();

	AActor* m_pOwner = nullptr;
	AActor* m_pActorAbleToOpenDoor = nullptr;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* m_pPressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
	float m_fRotationPerSecond = 90.0f;

	float m_fInitialYaw = 0.0f;
	float m_fCurrentLocalRotation = 0.0f;
};
