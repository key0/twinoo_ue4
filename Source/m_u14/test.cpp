
#include "m_u14.h"
#include "test.h"

Atest::Atest() {

	PrimaryActorTick.bCanEverTick = true;

}

void Atest::BeginPlay() {

	UE_LOG(LogTemp, Warning, TEXT( "=== test::BeginPlay") ) ;
	Super::BeginPlay();

//     Create a new Task and pass as a parameter
//     Then, tell that Task to execute in the background.
//     The FAutoDeleteAsyncTask will make sure to delete the task when it's finished.

//     Multithreading requires cautious handle of the available threads, in order to avoid
//     race conditions and strange bugs that are not easy to solve

//     Fortunately, UE4 contains a class (FAutoDeleteAsyncTask) which handles everything by itself
//     and the programmer is able to perform async operations without any real effort.

    ( new FAutoDeleteAsyncTask< myAsyncTask >( 42 ) ) ->StartBackgroundTask();

}


