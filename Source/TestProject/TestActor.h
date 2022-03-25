// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestActor.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class TESTPROJECT_API ATestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Function callable from BP
	UFUNCTION(BlueprintCallable)
	void FunctionCallableFromBp();

	UFUNCTION(BlueprintImplementableEvent)
	void OnOverlap();

	UFUNCTION(BlueprintCallable)
	void TestFunction();

	UFUNCTION(BlueprintCallable, Meta = (AdvancedDisplay = "Distance"))
	float JumpADistance(float Distance, FVector Direction, FVector& OutMoveDelta);

	void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	// similar to [SerializeField] in C# (with VisibleAnywhere)
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* Sphere;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 200.f;

	APawn* ChaseTarget = nullptr;
	bool IsOverlapping;

	// Note: Use UP:: to see all options
};