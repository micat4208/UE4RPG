#include "EnemySpawnRegion.h"

#include "Component/EnemySpawner/EnemySpawnerComponent.h"

AEnemySpawnRegion::AEnemySpawnRegion()
{
	PrimaryActorTick.bCanEverTick = true;

	EnemySpawner = CreateDefaultSubobject<UEnemySpawnerComponent>(TEXT("ENEMY_SPAWNER_COMPONENT"));

	SetRootComponent(EnemySpawner);

}

void AEnemySpawnRegion::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemySpawnRegion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

