// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PickupComponent.generated.h"

class UBoxComponent;
class UItemDataAsset;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VOIDBREAKERS_API UPickupComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPickupComponent();

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	bool TryPickup(AActor* Picker);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup")
	TObjectPtr<UItemDataAsset> Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1"))
	int32 Quantity = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	bool bDestroyOwnerOnPickup = true;
};
