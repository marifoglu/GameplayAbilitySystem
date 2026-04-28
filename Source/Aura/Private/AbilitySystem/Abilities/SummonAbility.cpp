// Copyright ApesFiction


#include "AbilitySystem/Abilities/SummonAbility.h"
#include "Kismet/KismetSystemLibrary.h"


TArray<FVector> USummonAbility::GetSpawnLocations()
{
	const AActor* AvatarActor = GetAvatarActorFromActorInfo();
	if (!AvatarActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("SummonAbility: AvatarActor is null — cannot get spawn locations."));
		return TArray<FVector>();
	}
	
	const FVector Forward = AvatarActor->GetActorForwardVector();
	const FVector Location = AvatarActor->GetActorLocation();
	const float DeltaSpread = SpawnSpread / NumMinions;

	const FVector LeftOfSpread = Forward.RotateAngleAxis(-SpawnSpread / 2.f, FVector::UpVector);
	TArray<FVector> SpawnLocations;
	for (int32 i = 0; i < NumMinions; i++)
	{
		const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
		FVector ChosenSpawnLocation = Location + Direction * FMath::FRandRange(MinSpawnDistance, MaxSpawnDistance);

		FHitResult HitResult;
		GetWorld()->LineTraceSingleByChannel(
			HitResult,
			ChosenSpawnLocation + FVector(0.f, 0.f, 400.f),
			ChosenSpawnLocation - FVector(0.f, 0.f, 400.f),
			ECC_Visibility
		);
		if (HitResult.bBlockingHit)
		{
			ChosenSpawnLocation = HitResult.ImpactPoint;
		}
		SpawnLocations.Add(ChosenSpawnLocation);
		
	}
	
	return SpawnLocations;
}

TSubclassOf<APawn> USummonAbility::GetRandomMinionClass()
{
	int32 Selection = FMath::RandRange(0, MinionClasses.Num() - 1);
	return MinionClasses[Selection];
}
