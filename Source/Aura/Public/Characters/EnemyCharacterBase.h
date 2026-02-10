// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/CharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "EnemyCharacterBase.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AEnemyCharacterBase : public ACharacterBase, public IEnemyInterface	
{
	GENERATED_BODY()

public:
	AEnemyCharacterBase();

	UPROPERTY(BlueprintReadOnly)
	bool bIsHighlighted = false;
	
	/** Enemy Interface **/
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	/** End Enemy Interface **/

protected:
	virtual void BeginPlay() override;

};
