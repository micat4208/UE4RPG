#pragma once

#include "UE4RPG.h"
#include "GameFramework/Actor.h"
#include "EnemySpawnRegion.generated.h"

UCLASS()
class UE4RPG_API AEnemySpawnRegion : public AActor
{
	GENERATED_BODY()

private :
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UEnemySpawnerComponent* EnemySpawner;
	
public:	
	AEnemySpawnRegion();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
