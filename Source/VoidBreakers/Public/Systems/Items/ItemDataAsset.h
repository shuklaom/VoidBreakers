// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemType.h"
#include "ItemDataAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class VOIDBREAKERS_API UItemDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

	public: 

		/**
		* The unique identifier for this item.
		*/
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
		FName ItemID;

		/**
		* The display name of this item.
		*/
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
		FText ItemName;

		/**
		* A brief description of this item.
		*/
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
		FText Description;

		/**
		* The icon representing this item in the UI.
		*/
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Visual")
		TObjectPtr<UTexture2D> Icon;

		/**
		* The mesh representing this item in the world.
		*/
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Visual")
		TObjectPtr<UStaticMesh> WorldMesh;

		/**
		* The maximum number of this item that can be stacked together.
		*/
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Stacking")
		int32 MaxStackSize = 1;

		/**
		* The type of this item.
		*/
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
		EItemType ItemType = EItemType::Misc;
	
};
