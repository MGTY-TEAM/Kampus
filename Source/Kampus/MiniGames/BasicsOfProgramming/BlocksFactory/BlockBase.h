// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TimerManager.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "BlockBase.generated.h"


UCLASS(Abstract)
class KAMPUS_API ABlockBase : public AActor
{
	GENERATED_BODY()

public:
	ABlockBase();

	bool bIsDragged{false};
	
	virtual void OnDrag(FVector UnderCursorImpactPointLocation);
	virtual void OnDrop(FVector UnderCursorImpactPointLastLocation);
private:
	UPROPERTY(Category = Components, VisibleAnywhere)
	UStaticMeshComponent* MeshComponent{nullptr};
	
	UPROPERTY(Category = Sequence, VisibleAnywhere)
	ABlockBase* NextBlock{nullptr};
	UPROPERTY(Category = Sequence, VisibleAnywhere)
	ABlockBase* PrevBlock{nullptr};
	UPROPERTY(Category = DragDrop, VisibleAnywhere)
	
	float DragInterpolationSpeed;
	UPROPERTY(Category = DragDrop, VisibleAnywhere)
	float DropInterpolationSpeed;

	FTimerHandle DropInterpolationTimerHandle;

};

inline ABlockBase::ABlockBase()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	DragInterpolationSpeed = 0.5;
	DropInterpolationSpeed = 0.1;
}

inline void ABlockBase::OnDrag(FVector UnderCursorImpactPointLocation)
{
	bIsDragged = true;
	if (DropInterpolationTimerHandle.IsValid())
		GetWorldTimerManager().ClearTimer(DropInterpolationTimerHandle);

	FVector NewLocation = GetActorLocation();
	
	NewLocation.Y = FMath::FInterpTo(GetActorLocation().Y, UnderCursorImpactPointLocation.Y, GetWorld()->GetDeltaSeconds(),
	                 DragInterpolationSpeed);
	NewLocation.Z = FMath::FInterpTo(GetActorLocation().Z, UnderCursorImpactPointLocation.Y, GetWorld()->GetDeltaSeconds(),
	                 DragInterpolationSpeed);
	SetActorLocation(NewLocation);
}

inline void ABlockBase::OnDrop(FVector UnderCursorImpactPointLastLocation)
{
	bIsDragged = false;
	GetWorldTimerManager().SetTimer(DropInterpolationTimerHandle, FTimerDelegate::CreateLambda(
		                                [this, UnderCursorImpactPointLastLocation]
		                                {
		                                	FVector NewLocation = GetActorLocation();
			                                NewLocation.Y = FMath::FInterpTo(GetActorLocation().Y, UnderCursorImpactPointLastLocation.Y,
			                                                 GetWorld()->GetDeltaSeconds(), DropInterpolationSpeed);
			                                NewLocation.Z = FMath::FInterpTo(GetActorLocation().Z, UnderCursorImpactPointLastLocation.Y,
			                                                 GetWorld()->GetDeltaSeconds(), DropInterpolationSpeed);
		                                	SetActorLocation(NewLocation);
		                                }), 0.016, true);
}
