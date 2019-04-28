// Copyright Nameless Studio

#include "SprungWheel.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	SpringConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("SpringConstraint"));
	SetRootComponent(SpringConstraint);

	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->SetupAttachment(SpringConstraint);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Axle);

	WheelAxleConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("WheelAxleConstraint"));
	WheelAxleConstraint->SetupAttachment(Axle);

}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);

	if (GetAttachParentActor())
	{
		UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
		if (!BodyRoot) return;
		SpringConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Axle, NAME_None);
		WheelAxleConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
	}
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Resetting force each frame to not over accumulate
	if (GetWorld()->TickGroup == TG_PostPhysics)
		TotalForceMagnitudeThisFrame = 0;
}

void ASprungWheel::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	ApplyForce();
}

void ASprungWheel::ApplyForce()
{
	Wheel->AddForce(Axle->GetForwardVector() * TotalForceMagnitudeThisFrame);
}

void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	TotalForceMagnitudeThisFrame += ForceMagnitude;
}

