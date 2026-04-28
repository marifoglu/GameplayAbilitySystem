// Copyright ApesFiction


#include "AbilitySystem/AuraAbilitySystemGlobals.h"

#include "Aura/Public/AbilitySystem/AuraAbilityTypes.h"

FGameplayEffectContext* UAuraAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FAuraGameplayEffectContext();
}