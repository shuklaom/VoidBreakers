// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/BasePlayerCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Blueprint/UserWidget.h"

ABasePlayerCharacter::ABasePlayerCharacter()
{
	bUseControllerRotationYaw = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetRelativeLocation(FVector(1.197563f, 40.689219f, 75.684804f));
	CameraBoom->SetRelativeRotation(FRotator(-10.0f, 0.0f, 0.0f));
	CameraBoom->TargetArmLength = 250.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	InventoryWidget = nullptr;
	bIsInventoryOpen = false;
}

void ABasePlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABasePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABasePlayerCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABasePlayerCharacter::Look);

		EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Started, this, &ABasePlayerCharacter::ToggleInventory);
	}
}

void ABasePlayerCharacter::DoMove(float Right, float Forward)
{
	if (GetController())
	{
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void ABasePlayerCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController())
	{
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void ABasePlayerCharacter::DoJumpStart()
{
	if (CanJump())
	{
		Jump();
	}
}

void ABasePlayerCharacter::DoJumpEnd()
{
	if (CanJump())
	{
		StopJumping();
	}
}

void ABasePlayerCharacter::ToggleInventory()
{
	if (bIsInventoryOpen)
	{
		CloseInventory();
	}
	else
	{
		OpenInventory();
	}
}

void ABasePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (auto PlayerController = Cast<APlayerController>(GetController()))
	{
		if (auto LocalPlayer = PlayerController->GetLocalPlayer())
		{
			if (auto Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				Subsystem->AddMappingContext(PlayerInputMappingContext, 0);
			}
		}
	}
}

void ABasePlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	DoMove(MovementVector.X, MovementVector.Y);
}

void ABasePlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	float LookAxisVectorX = InvertMovement(LookAxisVector.X, bInvertCameraX);
	float LookAxisVectorY = InvertMovement(LookAxisVector.Y, bInvertCameraY);

	DoLook(LookAxisVectorX, LookAxisVectorY);
}

void ABasePlayerCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void ABasePlayerCharacter::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

float ABasePlayerCharacter::InvertMovement(float Value, bool bIsInverted)
{
	return bIsInverted ? -Value : Value;
}

void ABasePlayerCharacter::OpenInventory()
{
	if (bIsInventoryOpen || !InventoryWidgetClass) return;

	InventoryWidget = CreateWidget<UUserWidget>(GetWorld(), InventoryWidgetClass);

	if (!InventoryWidget) return;

	InventoryWidget->AddToViewport();

	bIsInventoryOpen = true;
}

void ABasePlayerCharacter::CloseInventory()
{
	if (!bIsInventoryOpen || !InventoryWidget) return;

	InventoryWidget->RemoveFromParent();
	
	InventoryWidget = nullptr;
	
	bIsInventoryOpen = false;
}
