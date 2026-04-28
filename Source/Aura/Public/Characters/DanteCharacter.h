// Copyright ApesFiction

#pragma once

#include "CoreMinimal.h"
#include "Characters/CharacterBase.h"
#include "Interface/PlayerInterface.h"
#include "DanteCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UNiagaraComponent;

UCLASS()
class AURA_API ADanteCharacter : public ACharacterBase, public IPlayerInterface
{
	GENERATED_BODY()

public:
	ADanteCharacter();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

protected:
	/** Player Interface **/
	virtual void AddToXP_Implementation(int32 InXP) override;
	virtual void LevelUp_Implementation() override;
	virtual int32 GetXP_Implementation() const override;
	virtual int32 FindLevelForXP_Implementation(int32 InXP) const override;
	virtual int32 GetAttributePointsReward_Implementation(int32 Level) const override;
	virtual int32 GetSpellPointsReward_Implementation(int32 Level) const override;
	virtual void AddToPlayerLevel_Implementation(int32 InPlayerLevels) override;
	virtual void AddToAttributePoints_Implementation(int32 InAttributePoints) override;
	virtual void AddToSpellPoints_Implementation(int32 InSpellPoints) override;
	virtual int32 GetAttributePoints_Implementation() const override;
	virtual int32 GetSpellPoints_Implementation() const override;
	/** End Player Interface **/
	
	/** Combat Interface **/
	virtual int32 GetPlayerLevel_Implementation() override; 
	/** End Combat Interface **/

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Effects")
	TObjectPtr<UNiagaraComponent> LevelUpNiagaraComponent;

private:
	virtual void InitAbilityActorInfo() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> TopDownCameraComponent;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	UFUNCTION(NetMulticast, Reliable)
	void MulticastLevelUpParticles() const;
};
