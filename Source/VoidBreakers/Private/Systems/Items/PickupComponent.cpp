// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Items/PickupComponent.h"
#include "Components/BoxComponent.h"
#include "Systems/Items/ItemDataAsset.h"
#include "Character/BaseCharacter.h"
#include "Systems/Storage/StorageComponent.h"

UPickupComponent::UPickupComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UPickupComponent::TryPickup(AActor* Picker)
{
	if (!Item || !Picker)
	{
		return false;
	}

	ABaseCharacter* Character = Cast<ABaseCharacter>(Picker);

	if (!Character)
	{
		return false;
	}

	UStorageComponent* Storage = Character->GetStorage();

	if (!Storage)
	{
		return false;
	}

	int32 AddedQuantity = 0;
	int32 RemainingQuantity = 0;

	const bool bFullyPickedUp = Storage->AddItem(Item, Quantity, AddedQuantity, RemainingQuantity);

	if (bFullyPickedUp && bDestroyOwnerOnPickup)
	{
		if (AActor* Owner = GetOwner())
		{
			Owner->Destroy();
		}
	}
	else if (AddedQuantity > 0)
	{
		Quantity = RemainingQuantity;
	}

	return bFullyPickedUp;
}