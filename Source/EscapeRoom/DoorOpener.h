
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DoorOpener.generated.h"


class AActor;
class ATriggerVolume;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDoorOpenRequest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDoorCloseRequest);

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

	UFUNCTION()
	void AddOverlappingObject(AActor* pMe, AActor* pOther);
	UFUNCTION()
	void RemoveOverlappingObject(AActor* pMe, AActor* pOther);

	AActor* m_pOwner = nullptr;

	UPROPERTY(BlueprintAssignable)
	FOnDoorOpenRequest OnDoorOpenRequest;
	UPROPERTY(BlueprintAssignable)
	FOnDoorCloseRequest OnDoorCloseRequest;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* m_pPressurePlate = nullptr;

	FRotator m_tInitialRotation = FRotator();
	UFUNCTION(BlueprintPure)
	FRotator GetInitialRotation() const { return m_tInitialRotation; };

	unsigned char m_ucOverlappingObjectsCount = 0;
};
