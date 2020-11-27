#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "InteractableComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractableDelegate, UObject*, Context);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MOTHERSHIPMAYHEM_API UInteractableComponent : public USceneComponent {
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
		FInteractableDelegate OnInteract;

	UFUNCTION(BlueprintCallable)
		void Trigger(UObject* Context);
};
