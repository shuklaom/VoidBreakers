// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemType.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Resource        UMETA(DisplayName = "Resource"), // Raw materials or crafting components
	Consumable      UMETA(DisplayName = "Consumable"), // Items that can be consumed for effects (e.g., Medkits)
    Weapon          UMETA(DisplayName = "Weapon"), // Items used to deal damage to enemies
    Tool            UMETA(DisplayName = "Tool"), // Items used to perform specific actions (e.g., keys)
    Equipment       UMETA(DisplayName = "Equipment"), // Wearable items that provide bonuses or abilities
    Quest           UMETA(DisplayName = "Quest"), // Items related to quests or objectives
    Misc            UMETA(DisplayName = "Misc") // Miscellaneous items that don't fit into other categories
};