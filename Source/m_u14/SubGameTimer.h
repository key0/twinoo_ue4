
#pragma once

#include "GameFramework/Actor.h"
#include "SubGameTimer.generated.h"

UCLASS()
class M_U14_API ASubGameTimer : public AActor { 

	GENERATED_BODY()

	ASubGameTimer();
    //virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
    virtual void EndPlay( const EEndPlayReason::Type EEndPlayReason ) override;
	virtual void Tick( float DeltaSeconds ) override;

    UStaticMeshComponent* rootComp ;
    UParticleSystemComponent* psComp;
    TWeakObjectPtr<UMaterialInstanceDynamic> dynMaterial ;
    UParticleSystem* fire;
    USoundCue* soundBoom;

//=================================

    UPROPERTY()
    float speed = 0.1 ;

    FVector scale , startScale ;
    FLinearColor color ;
    bool isEndPlay ;

public:

    bool isNewRaund ;

};

