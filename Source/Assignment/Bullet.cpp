// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "PC_PlayerController.h"

/*
* ABullet constructor
* Sets default values
*/
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Mesh"));
	BulletMesh->SetupAttachment(RootComponent);
	CollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision Capsule"));
	CollisionCapsule->SetupAttachment(BulletMesh);
	CollisionCapsule->SetCollisionProfileName("Trigger");
}

/*
* BeginPlay function
* Called when the game starts or when spawned. Sets triggers for overlap.
*/
void ABullet::BeginPlay()
{
	Super::BeginPlay();

	CollisionCapsule->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlapBegin);
	CollisionCapsule->OnComponentEndOverlap.AddDynamic(this, &ABullet::OnOverlapEnd);
}

/*
* OnOverlapBegin function
* Gives 5 bullets to player.
*/
void ABullet::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap Begin"));
	if (OtherActor) {
		APawn* OtherPawn = Cast<APawn>(OtherActor);
		if (OtherPawn) {
			AController* Controller = OtherPawn->GetController();
			if (Controller->IsA(APC_PlayerController::StaticClass())) {
				APC_PlayerController* PlayerController = Cast<APC_PlayerController>(Controller);
				int bullets = PlayerController->GetBullets();
				PlayerController->SetBullets(bullets + 5);
			}
		}
	}
}

/*
* OnOverlapEnd function
* Destroys bullet if the player interacts with it.
*/
void ABullet::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap End"));
	if (OtherActor) {
		APawn* OtherPawn = Cast<APawn>(OtherActor);
		if (OtherPawn) {
			AController* Controller = OtherPawn->GetController();
			if (Controller->IsA(APC_PlayerController::StaticClass())) {
				this->Destroy();
			}
		}
	}
}

