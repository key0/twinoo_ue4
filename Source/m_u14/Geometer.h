
#pragma once

#include "m_u14.h"
#include "GameFramework/Actor.h"
#include "SubGameTimer.h"
//#include "M_Hud.h"
#include "Geometer.generated.h"

UCLASS()
class M_U14_API AGeometer : public AActor {

	GENERATED_BODY()

    enum e_form {
         sphere
        ,cube
        ,tetrahUp
        ,tetrahDown
        ,octah
        ,dodecah
        ,icosah
        //,sphere_cube
        //,sphere_tetrah
        //,sphere_octah
        ,cube_octah
        ,tetrahUp_tetrahDown
        ,operAdd
        ,forms_count
    };

    struct AddAbleForms_t {
       e_form A;
       e_form B;
       e_form AB;
    };

    const FString formToString(int f) const {

          switch (f) {

                 case sphere:               return "SM_Sphere";
                 case cube:                 return "SM_Cube";
                 case tetrahUp:             return "SM_TetrahUp";
                 case tetrahDown:           return "SM_TetrahDown";
                 case octah:                return "SM_Octah";
                 case dodecah:              return "SM_Dodecah";
                 case icosah:               return "SM_Icosah";
                 case cube_octah:           return "SM_Cube_Octah";
                 case tetrahUp_tetrahDown:  return "SM_TetrahUp_TetrahDown";
                 case operAdd:              return "SM_OperAdd";

          };

          return "unknown_form";
    }

    const AddAbleForms_t randAddAbleForms () const {

       static const AddAbleForms_t addAbleForms[]= {

            { sphere    ,sphere     ,sphere                 }
           ,{ cube      ,cube       ,cube                   }
           ,{ tetrahUp  ,tetrahDown ,tetrahUp_tetrahDown    }
           ,{ tetrahDown,tetrahUp   ,tetrahUp_tetrahDown    }
           ,{ cube      ,octah      ,cube_octah             }
           ,{ octah     ,cube       ,cube_octah             }
           ,{ octah     ,octah      ,octah                  }
           ,{ dodecah   ,dodecah    ,dodecah                }
           ,{ icosah    ,icosah     ,icosah                 }


       };

       return addAbleForms [ FMath::RandHelper( arraySize( addAbleForms ) ) ];
    }

    uint16 addAbleFormsSize;

    enum e_geometer_comp {
         arg1 = 0
        ,oper
        ,arg2
        ,res1 // true answer
        ,res2
        ,res3
        ,geometer_comps
    };

    const FName compToName(int n) const {

          switch (n) {

                case arg1:          return FName("arg1");
                case oper:          return FName("oper");
                case arg2:          return FName("arg2");
                case res1:          return FName("res1");
                case res2:			return FName("res2");
                case res3:			return FName("res3");

          }
          return FName("unknown_comp");
    }

    AGeometer() ;
    //virtual void OnConstruction( const FTransform& Transform ) override;
	virtual void BeginPlay() override;
    virtual void EndPlay( const EEndPlayReason::Type EEndPlayReason ) override;
    //virtual void Tick( float DeltaSeconds ) override;

    UStaticMesh* formMesh [ forms_count ] ;
    UStaticMeshComponent* meshComp[ geometer_comps ];
    FVector location [ geometer_comps ] ;

    ASubGameTimer* gameTimer = nullptr ;

    //UPROPERTY(EditAnywhere)
    //USoundBase* soundBoom;
    USoundBase* sound_14Bitz = nullptr ; // true answer sound


//_________ main subGame geometer funcs :
    bool isNewRaund ;
    void raund();
    UFUNCTION()
    void raundUpdate();

    FTimerHandle timerID;
    float timerRate = 0.02f;

     //void gameOver();

    UFUNCTION()
    void on_CompClicked( UPrimitiveComponent* ClickedComp , FKey ButtonClicked );//, FKey ButtonClicked );

};
