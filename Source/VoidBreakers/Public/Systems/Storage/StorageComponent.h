// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemStack.h"
#include "StorageComponent.generated.h"

/**
 * A component that provides storage functionality for items.
 */
struct FItemStack;

/**
 * Delegate that is broadcast when the storage changes (items added or removed).
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStorageChanged);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VOIDBREAKERS_API UStorageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStorageComponent();

protected:
	virtual void BeginPlay() override;

public:

	/**
	 * Initializes the storage with a specified capacity.
	 */
	void InitializeStorage(int32 NewCapacity);

	/**
	 * Checks if the specified item and quantity are valid for storage.
	 */
    UFUNCTION(BlueprintPure, Category = "Storage")
    bool ValidItem(UItemDataAsset* Item, int32 Quantity) const;

	/// ADD ITEMS

	/**
	 * Adds the specified item and quantity to the storage.
	 */
	UFUNCTION(BlueprintCallable, Category = "Storage")
	bool AddItem(UItemDataAsset* Item, int32 Quantity, int32& AddedQuantity, int32& RemainingQuantity);

	/**
	 * Adds the specified item and quantity to existing stacks in the storage.
	 */
    UFUNCTION(BlueprintCallable, Category = "Storage")
    int32 AddToExistingStacks(UItemDataAsset* Item, int32 QuantityToAdd);

	/**
	 * Adds the specified item and quantity to empty slots in the storage.
	 */
    UFUNCTION(BlueprintCallable, Category = "Storage")
	int32 AddToEmptySlots(UItemDataAsset* Item, int32 QuantityToAdd);

	/// REMOVE ITEMS

	/**
	 * Removes the specified item and quantity from the storage.
	 */
	UFUNCTION(BlueprintCallable, Category = "Storage")
	bool RemoveItem(UItemDataAsset* Item, int32 Quantity, int32& RemovedQuantity, int32& RemainingQuantity);

	///API FUNCTIONS

	/**
	 * Returns the maximum capacity of the storage.
	 */
	UFUNCTION(BlueprintPure, Category = "Storage")
	int32 GetCapacity() const;

	/**
	 * Returns the number of item stacks currently in the storage.
	 */
	UFUNCTION(BlueprintPure, Category = "Storage")
	int32 GetItemCount() const;

	/**
	 * Returns the item and quantity at the specified slot index.
	 */
	UFUNCTION(BlueprintPure, Category = "Storage")
	bool GetItemAtSlot(int32 SlotIndex, UItemDataAsset*& Item, int32& Quantity) const;

	/**
	 * Checks if the specified slot index is empty.
	 */
	UFUNCTION(BlueprintPure, Category = "Storage")
	bool IsSlotEmpty(int32 SlotIndex) const;

	UFUNCTION(BlueprintPure, Category = "Storage")
	int32 GetTotalQuantity(UItemDataAsset* Item) const;
	
public:

	/**
	 * The array of item stacks in the storage.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Storage")
	TArray<FItemStack> Items;

	/**
	 * The maximum capacity of the storage.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Storage")
	int32 Capacity = 20;

	/**
	 * Delegate that is broadcast when the storage changes (items added or removed).
	 */
	UPROPERTY(BlueprintAssignable, Category = "Storage")
	FOnStorageChanged OnStorageChanged;
};