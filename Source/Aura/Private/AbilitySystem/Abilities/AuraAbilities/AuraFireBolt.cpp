// Copyright ApesFiction


#include "AbilitySystem/Abilities/AuraAbilities/AuraFireBolt.h"

#include "AbilitySystem/AuraGameplayTags.h"

FString UAuraFireBolt::GetDescription(int32 Level)
{
	const int32 Damage = DamageTypes[FAuraGameplayTags::Get().Damage_Fire].GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	if (Level == 1)
	{
		return FString::Printf(TEXT(
			// Title
			"<Title>FIRE BOLT</>\n\n"

			// Level
			"<Small>Level: </><Level>%d</>\n"
			// Mana
			"<Small>Mana Cost: </><ManaCost>%.1f</>\n"
			// Cooldown
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			// Description
			"<Default>Launches a bolt of fire, exploding on impact and dealing: </>"
			"<Damage>%d</>"
			"<Default> fire damage with chance the burn.</>"
			
			// Values
			), Level, ManaCost, Cooldown, Damage);
	}
	else
	{
		return FString::Printf(TEXT(
			// Title
			"<Title>FIRE BOLT</>\n\n"

			// Level
			"<Small>Level: </><Level>%d</>\n"
			// Mana
			"<Small>Mana Cost: </><ManaCost>%.1f</>\n"
			// Cooldown
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			// Number of Projectiles
			"<Default>Launches %d bolts of fire, exploding on impact and dealing: </>"
			
			// Description
			"<Damage>%d</>"
			"<Default> fire damage with chance the burn.</>"
			
			// Values
			), Level, ManaCost, Cooldown, FMath::Min(Level, NumProjectiles), Damage);
	}
}

FString UAuraFireBolt::GetNextLevelDescription(int32 Level)
{
	const int32 Damage = GetDamageByDamageTypes(Level, FAuraGameplayTags::Get().Damage_Fire);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	
	return FString::Printf(TEXT(
		// Title
		"<Title>NEXT LEVEL</>\n\n"

		// Level
		"<Small>Level: </><Level>%d</>\n"
		// Mana
		"<Small>Mana Cost: </><ManaCost>%.1f</>\n"
		// Cooldown
		"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

		// Number of Projectiles
		"<Default>Launches %d bolts of fire, exploding on impact and dealing: </>"
			
		// Description
		"<Damage>%d</>"
		"<Default> fire damage with chance the burn.</>"
			
		// Values
		), Level, ManaCost, Cooldown, FMath::Min(Level, NumProjectiles), Damage);
}