// Fill out your copyright notice in the Description page of Project Settings.


#include "TestActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATestActor::ATestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	Sphere->SetupAttachment(Root); // setting up hierarchy: root will be parent of sphere
	Sphere->SetSphereRadius(100.f);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ATestActor::HandleOverlap);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Sphere);
}

void ATestActor::TestFunction()
{
	AddActorWorldOffset(FVector::UpVector * 500.f);
}

// Multiple outputs
float ATestActor::JumpADistance(float Distance, FVector Direction, FVector& OutMoveDelta)
{
	OutMoveDelta = Direction * Distance;
	AddActorWorldOffset(OutMoveDelta);
	return 5.f;
}

void ATestActor::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<APawn>())
	{
		ChaseTarget = Cast<APawn>(OtherActor);
		IsOverlapping = true;
		OnOverlap();
	}
}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ChaseTarget != nullptr)
	{
		FVector Direction = ChaseTarget->GetActorLocation() - GetActorLocation();
		Direction.Normalize();
		// Note:
		// Direction = Direction.GetSafeNormal() for copy of normal
		AddActorWorldOffset(Direction * Speed * DeltaTime);

		// Rotate to face player
		FRotator Rotation = UKismetMathLibrary::MakeRotFromX(Direction);
		SetActorRotation(Rotation);
	}
}

// Unreal naming:
// AActor: Actors have "A" prefix; Ex. ATestActor
// UOBject: Base object type
//		Anything else that inherites from UObject: "U" prefix; Ex. USceneComponent, USphereComponent, etc.
// Anything else that is not UObject: "F" prefix; Ex. FVector, FRotator, etc.
//		Unless if it's template class: "T" prefix; Ex. TArray