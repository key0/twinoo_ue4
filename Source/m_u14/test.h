
#pragma once

#include "GameFramework/Actor.h"
#include "test.generated.h"

UCLASS()
class M_U14_API Atest : public AActor { 

	GENERATED_BODY()

	Atest();
	virtual void BeginPlay() override;

    struct myAsyncTask : public FNonAbandonableTask {

        // This function is needed from the API of the engine.
        // My (orfeasel) guess is that it provides necessary information
        // about the thread that we occupy and the progress of our task
        //
         FORCEINLINE
         TStatId GetStatId() const {

             RETURN_QUICK_DECLARE_CYCLE_STAT(  PrimeCalculationAsyncTask
                                             , STATGROUP_ThreadPoolAsyncTasks );
         }

        int32 _myParam;
        myAsyncTask( int32 param ) {

            _myParam = param ;

        }


        //This function is executed when we tell our task to execute
        void DoWork() {

            UE_LOG(LogTemp, Warning, TEXT( "=== Hi from background thread! f (param = %d)"), _myParam += 1 ) ;

        }
    };
};

