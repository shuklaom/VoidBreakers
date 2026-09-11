// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickupItem.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class UPickupComponent;

UCLASS()
class VOIDBREAKERS_API ABasePickupItem : public AActor
{
	GENERATED_BODY()
	
public:
	ABasePickupItem();

	UFUNCTION(BlueprintPure, Category = "Pickup")
	UPickupComponent* GetPickup() const { return Pickup; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UBoxComponent> InteractionBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UPickupComponent> Pickup;
};
