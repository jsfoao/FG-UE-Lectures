#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ThirdPersonCharacter.generated.h"

class USceneComponent;
class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class AThirdPersonCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AThirdPersonCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* Sphere;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Range = 200.f;
};
