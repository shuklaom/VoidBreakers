// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickupItem.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UBoxComponent;
class UPickupComponent;
class UWidgetComponent;

UCLASS()
class VOIDBREAKERS_API ABasePickupItem : public AActor
{
	GENERATED_BODY()
	
public:
	ABasePickupItem();

	UFUNCTION(BlueprintPure, Category = "Pickup")
	UPickupComponent* GetPickup() const { return Pickup; }

	UFUNCTION(BlueprintCallable, Category = "Pickup|UI")
	void ShowInteractionPrompt();
	
	UFUNCTION(BlueprintCallable, Category = "Pickup|UI")
	void HideInteractionPrompt();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UBoxComponent> InteractionBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UWidgetComponent> InteractionWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UPickupComponent> Pickup;
};
