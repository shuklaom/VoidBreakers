// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Storage/StorageComponent.h"

UStorageComponent::UStorageComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UStorageComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeStorage(Capacity);

}

void UStorageComponent::InitializeStorage(int32 NewCapacity)
{
	Items.Empty();
	Items.Reserve(NewCapacity);

	for(int32 Index = 0; Index < NewCapacity; ++Index)
	{
		FItemStack EmptyStack;

		EmptyStack.Item = nullptr;
		EmptyStack.Quantity = 0;

		Items.Add(EmptyStack);
	}
}

bool UStorageComponent::ValidItem(UItemDataAsset* Item, int32 Quantity) const
{
	if (Item == nullptr || Quantity <= 0)
	{
		return false;
	}
	return true;
}

bool UStorageComponent::AddItem(UItemDataAsset* Item, int32 Quantity, int32& AddedQuantity, int32& RemainingQuantity)
{
	AddedQuantity = 0;
	RemainingQuantity = Quantity;

	if (!ValidItem(Item, Quantity))
	{
		return false;
	}

	RemainingQuantity = AddToExistingStacks(Item, RemainingQuantity);

	RemainingQuantity = AddToEmptySlots(Item, RemainingQuantity);

	AddedQuantity = Quantity - RemainingQuantity;

	if (AddedQuantity > 0)
	{
		OnStorageChanged.Broadcast();
	}

	return RemainingQuantity == 0;
}

int32 UStorageComponent::AddToExistingStacks(UItemDataAsset* Item, int32 QuantityToAdd)
{
	if (!ValidItem(Item, QuantityToAdd))
	{
		return QuantityToAdd;
	}

	const int32 MaxStackSize = Item->MaxStackSize;

	if (MaxStackSize <= 0)
	{
		return QuantityToAdd;
	}

	for (FItemStack& Stack : Items)
	{
		if (QuantityToAdd <= 0)
		{
			break;
		}

		if (Stack.Item != Item || Stack.Quantity <= 0)
		{
			continue;
		}

		const int32 AvailableSpace = MaxStackSize - Stack.Quantity;
		const int32 AmountToAdd = FMath::Min(QuantityToAdd, AvailableSpace);

		Stack.Quantity += AmountToAdd;
		QuantityToAdd -= AmountToAdd;
	}

	return QuantityToAdd;
}

int32 UStorageComponent::AddToEmptySlots(UItemDataAsset* Item, int32 QuantityToAdd)
{
	if (!ValidItem(Item, QuantityToAdd))
	{
		return QuantityToAdd;
	}

	const int32 MaxStackSize = Item->MaxStackSize;

	if (MaxStackSize <= 0)
	{
		return QuantityToAdd;
	}

	for (FItemStack& Stack : Items)
	{
		if (QuantityToAdd <= 0)
		{
			break;
		}

		if (Stack.Item != nullptr)
		{
			continue;
		}

		const int32 AmountToAdd = FMath::Min(QuantityToAdd, MaxStackSize);
		
		Stack.Item = Item;
		Stack.Quantity = AmountToAdd;
		
		QuantityToAdd -= AmountToAdd;
	}

	return QuantityToAdd;
}

bool UStorageComponent::RemoveItem(UItemDataAsset* Item, int32 Quantity, int32& RemovedQuantity, int32& RemainingQuantity)
{
	RemovedQuantity = 0;
	RemainingQuantity = Quantity;

	if (!ValidItem(Item, Quantity))
	{
		return false;
	}

	for (FItemStack& Stack : Items)
	{
		if (RemainingQuantity <= 0)
		{
			break;
		}

		if (Stack.Item != Item || Stack.Quantity <= 0)
		{
			continue;
		}
		
		const int32 AmountToRemove = FMath::Min(RemainingQuantity, Stack.Quantity);

		Stack.Quantity -= AmountToRemove;

		RemovedQuantity += AmountToRemove;

		RemainingQuantity -= AmountToRemove;

		if (Stack.Quantity == 0)
		{
			Stack.Item = nullptr;
		}
	}

	if (RemovedQuantity > 0)
	{
		OnStorageChanged.Broadcast();
	}

	return RemainingQuantity == 0;
}

int32 UStorageComponent::GetCapacity() const
{
	return Items.Num();
}

int32 UStorageComponent::GetItemCount() const
{
	int32 ItemCount = 0;

	for (const FItemStack& Stack : Items)
	{
		if (Stack.Item != nullptr && Stack.Quantity > 0)
		{
			++ItemCount;
		}
	}
	return ItemCount;
}

bool UStorageComponent::GetItemAtSlot(int32 SlotIndex, UItemDataAsset*& Item, int32& Quantity) const
{
	Item = nullptr;
	Quantity = 0;

	if (!Items.IsValidIndex(SlotIndex))
	{
		return false;
	}

	const FItemStack& Stack = Items[SlotIndex];

	if (Stack.Item == nullptr || Stack.Quantity <= 0)
	{
		return false;
	}

	Item = Stack.Item;
	Quantity = Stack.Quantity;

	return true;
}

bool UStorageComponent::IsSlotEmpty(int32 SlotIndex) const
{
	if (!Items.IsValidIndex(SlotIndex))
	{
		return true;
	}

	const FItemStack& Stack = Items[SlotIndex];

	return Stack.Item == nullptr || Stack.Quantity <= 0;
}

int32 UStorageComponent::GetTotalQuantity(UItemDataAsset* Item) const
{
	if (Item == nullptr)
	{
		return 0;
	}

	int32 TotalQuantity = 0;

	for (const FItemStack& Stack : Items)
	{
		if (Stack.Item != Item || Stack.Quantity <= 0)
		{
			continue;
		}

		TotalQuantity += Stack.Quantity;
	}

	return TotalQuantity;
}
