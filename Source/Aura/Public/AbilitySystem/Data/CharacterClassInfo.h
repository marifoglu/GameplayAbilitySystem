// Copyright ApesFiction

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Engine/DataAsset.h"
#include "CharacterClassInfo.generated.h"

class UGameplayEffect;
class UGameplayAbility;

UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
    // CIRCLE 1 - LIMBO
    Limbo_Shade,            // Fodder
    Limbo_Whisper,          // Sinner
    Limbo_Phantom,          // Fiend
    Limbo_Charon,           // Warden
    Limbo_Minos,            // Archfiend

    // CIRCLE 2 - LUST
    Lust_Succubus,          // Fodder
    Lust_Tempest,           // Sinner
    Lust_Siren,             // Fiend
    Lust_Incubus,           // Warden
    Lust_Semiramis,         // Archfiend

    // CIRCLE 3 - GLUTTONY
    Gluttony_Bloater,       // Fodder
    Gluttony_Gorger,        // Sinner
    Gluttony_Gulper,        // Fiend
    Gluttony_Devourer,      // Warden
    Gluttony_Cerberus,      // Archfiend

    // CIRCLE 4 - GREED
    Greed_Hoarder,          // Fodder
    Greed_Miser,            // Sinner
    Greed_Collector,        // Fiend
    Greed_Plutus,           // Warden
    Greed_Mammon,           // Archfiend

    // CIRCLE 5 - WRATH
    Wrath_Fury,             // Fodder
    Wrath_Berserker,        // Sinner
    Wrath_Ravager,          // Fiend
    Wrath_Phlegyas,         // Warden
    Wrath_Erinyes,          // Archfiend

    // CIRCLE 6 - HERESY
    Heresy_Heretic,         // Fodder
    Heresy_Apostate,        // Sinner
    Heresy_Blasphemer,      // Fiend
    Heresy_FallenAngel,     // Warden
    Heresy_Farinata,        // Archfiend

    // CIRCLE 7 - VIOLENCE
    Violence_Butcher,       // Fodder
    Violence_Harpy,         // Sinner
    Violence_Slayer,        // Fiend
    Violence_Centaur,       // Warden
    Violence_Nessus,        // Archfiend

    // CIRCLE 8 - FRAUD
    Fraud_Deceiver,         // Fodder
    Fraud_Serpent,          // Sinner
    Fraud_Schemer,          // Fiend
    Fraud_Malebranche,      // Warden
    Fraud_Geryon,           // Archfiend

    // CIRCLE 9 - TREACHERY
    Treachery_Frozen,       // Fodder
    Treachery_Traitor,      // Sinner
    Treachery_Betrayer,     // Fiend
    Treachery_Giant,        // Warden
    Treachery_Lucifer       // Archfiend
};

USTRUCT(BlueprintType)
struct FCharacterClassDefaultInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Category="Class Defaults")
	TSubclassOf<UGameplayEffect> PrimaryAttributes;
};

UCLASS()
class AURA_API UCharacterClassInfo : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category="Character Class Defaults")
	TMap<ECharacterClass, FCharacterClassDefaultInfo> CharacterClassInformation;
	
	UPROPERTY(EditDefaultsOnly, Category="Common Class Defaults")
	TSubclassOf<UGameplayEffect> SecondaryAttributes;

	UPROPERTY(EditDefaultsOnly, Category="Common Class Defaults")
	TSubclassOf<UGameplayEffect> VitalAttributes;

	UPROPERTY(EditDefaultsOnly, Category="Common Class Defaults")
	TArray<TSubclassOf<UGameplayAbility>> CommonAbilities;


	UPROPERTY(EditDefaultsOnly, Category="Common Class Defaults|Damage")
	TObjectPtr<UCurveTable> DamageCalculationCoefficients;

	FCharacterClassDefaultInfo GetClassDefaultInfo(ECharacterClass CharacterClass) const;
	
};
