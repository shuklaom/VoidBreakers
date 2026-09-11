// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "BasePlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class UUserWidget;
struct FInputActionValue;

UCLASS()
class VOIDBREAKERS_API ABasePlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ABasePlayerCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void DoMove(float Right, float Forward);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void DoLook(float Yaw, float Pitch);

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoJumpStart();

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoJumpEnd();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void ToggleInventory();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void Interact();

protected:
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

private:
	float InvertMovement(float Value, bool bIsInverted);

	void OpenInventory();

	void CloseInventory();

public:

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:
	UPROPERTY(EditAnywhere, Category = "InputAction|Locomotion")
	UInputMappingContext* PlayerInputMappingContext;

	UPROPERTY(EditAnywhere, Category="InputAction|Locomotion")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = "InputAction|Locomotion")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "InputAction|Locomotion")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "InputAction|Inventory")
	UInputAction* InventoryAction;

	UPROPERTY(EditAnywhere, Category = "InputAction|Interact")
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, Category = "Interaction")
	float InteractRange = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InvertMovement")
	bool bInvertCameraX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InvertMovement")
	bool bInvertCameraY;

	UPROPERTY(EditDefaultsOnly, Category = "UI|Inventory")
	TSubclassOf<UUserWidget> InventoryWidgetClass;

	UPROPERTY()
	UUserWidget* InventoryWidget;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	bool bIsInventoryOpen;
};
