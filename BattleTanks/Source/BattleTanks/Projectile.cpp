// Copyright Nameless Studio


#include "Projectile.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);	// Set simulation hit events as default for projectiles
	CollisionMesh->SetVisibility(false); 	// Projectile won't be visible, only its' vfx of smoke

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch VFX"));
	LaunchBlast->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepRelativeTransform);

	ImpactExplosion = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact VFX"));
	ImpactExplosion->AttachTo(RootComponent);
	ImpactExplosion->bAutoActivate = false;

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	ExplosionForce->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepRelativeTransform);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovement->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	// OnHit even of collision mesh of the sphere
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::Launch(float Speed)
{
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovement->Activate();
}

void AProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	LaunchBlast->Deactivate();
	ImpactExplosion->Activate();
	ExplosionForce->FireImpulse();

	SetRootComponent(ImpactExplosion);
	CollisionMesh->DestroyComponent();

	UGameplayStatics::ApplyRadialDamage(
		this,
		ProjectileDamage,
		GetActorLocation(),
		ExplosionForce->Radius,
		UDamageType::StaticClass(),
		TArray<AActor*>()
	);

	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(Timer, this,&AProjectile::InTimerMethod,DestroyDelay,false,-1);
}

void AProjectile::InTimerMethod()
{
	this->Destroy();
}