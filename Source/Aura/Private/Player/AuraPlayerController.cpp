// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"


AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(AuraContext, 0);
	}
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);

	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	VirtualCursorPosition = FVector2D(ViewportSizeX * 0.5f, ViewportSizeY * 0.5f);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Look);
}

void AAuraPlayerController::Move(const struct FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AAuraPlayerController::Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();
    
	if (LookAxisVector.SizeSquared() > 0.1f)  // Deadzone
	{
		// Move virtual cursor
		VirtualCursorPosition.X += LookAxisVector.X * CursorSpeed * GetWorld()->GetDeltaSeconds();
		VirtualCursorPosition.Y += LookAxisVector.Y * CursorSpeed * GetWorld()->GetDeltaSeconds();
        
		// Clamp to viewport
		int32 ViewportSizeX, ViewportSizeY;
		GetViewportSize(ViewportSizeX, ViewportSizeY);
		VirtualCursorPosition.X = FMath::Clamp(VirtualCursorPosition.X, 0.f, (float)ViewportSizeX);
		VirtualCursorPosition.Y = FMath::Clamp(VirtualCursorPosition.Y, 0.f, (float)ViewportSizeY);
        
		// Update mouse cursor position
		SetMouseLocation(VirtualCursorPosition.X, VirtualCursorPosition.Y);
	}
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = nullptr; // reset ...
	
	AActor* HitActor = CursorHit.GetActor();
	if (HitActor && HitActor->GetClass()->ImplementsInterface(UEnemyInterface::StaticClass()))
	{
		ThisActor.SetObject(HitActor);
		ThisActor.SetInterface(Cast<IEnemyInterface>(HitActor));
	}
	else
	{
		ThisActor = nullptr;
	}

	/** Line trace from cursor, there are several scenarios
	 *	A. LastActor is null && ThisActor is null
	 *		- Do Nothing
	 *	B. LastActor is null && ThisActor is valid
	 *		- Highlight ThisActor
	 *	C. LastActor is valid && ThisActor is null
	 *		- UnHighlight LastActor
	 *	D. Both actors are valid, but LastActor != ThisActor
	 *		- UnHighlight LastActor, and Highlight ThisActor
	 *	E. Both actors are valid, and are the same actor
	 *		- Do nothing!
	 */

	if (LastActor.GetInterface() == nullptr)
	{
		if (ThisActor.GetInterface() != nullptr)
		{
			// Case B
			ThisActor->HighlightActor();
		}
		else
		{
			// Case A - both are null, do nothing
		}
	}else
	{
		if (ThisActor.GetInterface() == nullptr)
		{
			// Case C
			LastActor->UnHighlightActor();
		}
		else
		{
			// both actors are valid
			if (LastActor != ThisActor)
			{
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}else
			{
				// Case E
			}
		}
	}
}






















