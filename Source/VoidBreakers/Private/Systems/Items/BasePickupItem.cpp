// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Items/BasePickupItem.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Systems/Items/PickupComponent.h"
#include "Systems/Items/ItemDataAsset.h"
#include  "Components/WidgetComponent.h"
#include "UI/InteractionPromptWidget.h"

ABasePickupItem::ABasePickupItem()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetupAttachment(RootComponent);
	InteractionBox->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	InteractionBox->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	InteractionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	InteractionBox->SetCollisionResponseToChannel(ECC_Visibility, ECollisionResponse::ECR_Block);

	Pickup = CreateDefaultSubobject<UPickupComponent>(TEXT("Pickup"));

	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
	InteractionWidget->SetupAttachment(RootComponent);
	InteractionWidget->SetWidgetSpace(EWidgetSpace::Screen);
	InteractionWidget->SetDrawAtDesiredSize(true);
	InteractionWidget->SetVisibility(false);

}

void ABasePickupItem::ShowInteractionPrompt()
{
	if (!InteractionWidget)
	{
		return;
	}

	const UPickupComponent* PickupComponent = GetPickup();
	const FText ItemName = PickupComponent && PickupComponent->Item ? PickupComponent->Item->ItemName : FText::GetEmpty();

	const FText PromptText = ItemName.IsEmpty() 
		? NSLOCTEXT("Pickup", "PickupPromptWithoutItem", "Press E to pick up") 
		: FText::Format(NSLOCTEXT("Pickup", "PickupPromptWithItem", "Press F to pick up {0}"), ItemName);

	if (UInteractionPromptWidget* PormptWidget = Cast<UInteractionPromptWidget>(InteractionWidget->GetUserWidgetObject()))
	{
		PormptWidget->SetPromptText(PromptText);
	}

	InteractionWidget->SetVisibility(true);
}

void ABasePickupItem::HideInteractionPrompt()
{
	InteractionWidget->SetVisibility(false);
}
