
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DoorOpener.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ESCAPEROOM_API UDoorOpener : public UActorComponent
{
	GENERATED_BODY()

public:

	UDoorOpener();

	virtual void TickComponent(float fDeltaTime, ELevelTick eTickType, FActorComponentTickFunction* pThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_fRotationPerSecond = 90.0f;

protected:

	virtual void BeginPlay() override;

private:

	AActor* m_pOwner = nullptr;

	float m_fInitialYaw = 0.0f;
	float m_fCurrentLocalRotation = 0.0f;
	bool m_bOpened = false;
};
