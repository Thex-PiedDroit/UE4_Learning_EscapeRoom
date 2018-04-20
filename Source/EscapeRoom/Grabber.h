
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


class APlayerController;
class UInputComponent;
class UPhysicsHandleComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ESCAPEROOM_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:

	UGrabber();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	virtual void BeginPlay() override;

private:

	void GrabWhatsInFrontOfMe();
	void UpdateGrabbedObject();
	void ReleaseWhateverImHolding();

	void UpdateEyesData();

	APlayerController * m_pPlayerController = nullptr;

	UInputComponent* m_pInputComponent = nullptr;
	UPhysicsHandleComponent* m_pPhysicsHandle = nullptr;

	FVector m_tEyesPos = FVector();
	FRotator m_tEyesRotation = FRotator();

	UPROPERTY(EditAnywhere)
	float m_fReach = 100.0f;
};
