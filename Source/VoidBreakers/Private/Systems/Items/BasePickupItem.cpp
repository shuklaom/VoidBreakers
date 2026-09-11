// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Items/BasePickupItem.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Systems/Items/PickupComponent.h"
#include "Systems/Items/ItemDataAsset.h"

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
}