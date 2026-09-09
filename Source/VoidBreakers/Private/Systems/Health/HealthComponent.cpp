// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Health/HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	CurrentHealth = MaxHealth;
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UHealthComponent::TakeDamage(float DamageAmount)
{
	if (DamageAmount <= 0.0f || IsDead())
	{
		return;
	}

	const float OldHealth = CurrentHealth;

	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.0f, MaxHealth);

	const float HealthChange = CurrentHealth - OldHealth;

	OnHealthChanged.Broadcast(CurrentHealth, MaxHealth, HealthChange);

	if (IsDead())
	{
		OnDeath.Broadcast();
	}
}

void UHealthComponent::Heal(float HealAmount)
{
	if (!bCanHeal || HealAmount <= 0.0f || IsDead())
	{
		return;
	}

	const float OldHealth = CurrentHealth;

	CurrentHealth = FMath::Clamp(CurrentHealth + HealAmount, 0.0f, MaxHealth);

	const float HealthChange = CurrentHealth - OldHealth;

	OnHealthChanged.Broadcast(CurrentHealth, MaxHealth, HealthChange);
}

void UHealthComponent::SetHealth(float NewHealth)
{
	const float OldHealth = CurrentHealth;

	CurrentHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);

	const float HealthChange = CurrentHealth - OldHealth;

	OnHealthChanged.Broadcast(CurrentHealth, MaxHealth, HealthChange);

	if (IsDead())
	{
		OnDeath.Broadcast();
	}
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
}