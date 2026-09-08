// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Systems/Items/ItemDataAsset.h"
#include "ItemStack.generated.h"

class UItemDataAsset;

USTRUCT(BlueprintType)
struct VOIDBREAKERS_API FItemStack
{
	GENERATED_BODY()

public:

	/**
	* The item contained in this stack.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Stack")
	TObjectPtr<UItemDataAsset> Item = nullptr;

	/**
	* The quantity of the item in this stack.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Stack", meta = (ClampMin = "0"))
	int32 Quantity = 0;
};
