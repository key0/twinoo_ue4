
#pragma once

#include "m_u14.h"
#include "GameFramework/Actor.h"
#include "Colorz.generated.h"

UCLASS()
class M_U14_API AColorz : public AActor { 

	GENERATED_BODY()

    enum Color { // -  named iteration for material
         Gray = -1// special for like violet + green
        ,Red
        ,Red_Violet
        ,Violet
        ,Violet_Blue
        ,Blue
        ,Blue_Cyan
        ,Cyan
        ,Cyan_Green
        ,Green
        ,Green_Yellow
        ,Yellow
        ,Yellow_Red
        ,colors_count
    };

    uint8 randBase3Color() const {

        Color base3Color[] = {

             Red
            ,Blue
            ,Green

        };

        auto r = FMath::RandHelper( arraySize ( base3Color ) );

        return static_cast< uint8 >( base3Color[ r ] )  ;
    }

    uint8 randBase6Color() const {

        Color base6Color[] = {

             Red
            ,Violet
            ,Blue
            ,Cyan
            ,Green
            ,Yellow

        };

        auto r = FMath::RandHelper( arraySize ( base6Color ) );

        return static_cast< uint8 >( base6Color[ r ] )  ;
    }

    Color addColor( const Color c1 , const Color c2 ) const {

        if ( c1 == c2 ) return c1;

        Color colorAddTable[] = {  Red      , Violet     , Red_Violet
                                 , Red      , Blue       , Violet
                                 , Red      , Cyan       , Gray
                                 , Red      , Green      , Yellow
                                 , Red      , Yellow     , Yellow_Red
                                 //, Red      , Red        , Red
                                 , Violet   , Blue       , Violet_Blue
                                 , Violet   , Cyan       , Blue
                                 , Violet   , Green      , Gray
                                 , Violet   , Yellow     , Red
                                 , Violet   , Red        , Red_Violet
                                 //, Violet   , Violet     , Violet
                                 , Blue	    , Cyan	     , Blue_Cyan
                                 , Blue     , Green	     , Cyan
                                 , Blue     , Yellow	 , Gray//
                                 , Blue     , Red		 , Violet
                                 , Blue     , Violet	 , Violet_Blue
                                 //, Blue     , Blue       , Blue
                                 , Cyan     , Green      , Cyan_Green
                                 , Cyan     , Yellow     , Green
                                 , Cyan     , Red        , Gray//
                                 , Cyan     , Violet	 , Blue
                                 , Cyan     , Blue		 , Blue_Cyan
                                 //, Cyan    , Cyan		  , Cyan
                                 , Green    , Yellow     , Green_Yellow
                                 , Green    , Red        , Yellow
                                 , Green    , Violet     , Gray//
                                 , Green    , Blue       , Cyan
                                 , Green    , Cyan       , Cyan_Green
                                 //, Green    , Green      , Green
                                 , Yellow   , Red        , Yellow_Red
                                 , Yellow   , Violet     , Red
                                 , Yellow   , Blue       , Gray//
                                 , Yellow   , Cyan       , Green
                                 , Yellow   , Green      , Green_Yellow
                                 //, Yellow   , Yellow     , Yellow
        };

        uint8 i = 0 ;

        while ( colorAddTable[ i ] != c1 ) i+= 3 * 5 ;
        while ( colorAddTable[ i ] != c2 ) i++       ;
        i++;

        return colorAddTable[ i % arraySize( colorAddTable ) ] ;
    }

    const FString colorToString( int8 c ) const {

       switch (c) {

            case Gray:			return "MI_Gray";
            case Red:			return "MI_Red";
            case Red_Violet:	return "MI_Red_Violet";
            case Violet:		return "MI_Violet";
            case Violet_Blue:	return "MI_Violet_Blue";
            case Blue:			return "MI_Blue";
            case Blue_Cyan:		return "MI_Blue_Cyan";
            case Cyan:			return "MI_Cyan";
            case Cyan_Green:	return "MI_Cyan_Green";
            case Green:			return "MI_Green";
            case Green_Yellow:	return "MI_Green_Yellow";
            case Yellow:		return "MI_Yellow";
            case Yellow_Red:	return "MI_Yellow_Red";

       };
       return "unknown_color";
    }
    enum e_colors_comps {

         arg1 = 0
        ,oper
        ,arg2
        ,res1 // true answer
        ,res2
        ,res3
        ,colors_comps
    };
    const FName compToName( int8 n ) const {

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

    AColorz();
    virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EEndPlayReason) override;
    //virtual void Tick( float DeltaSeconds ) override;

    UMaterialInstance* materialColor[ colors_count ];
    UStaticMeshComponent* meshComp[ colors_comps ];

    USoundBase* sound_33Bitz = nullptr ;
    //_________ main game func :
    void raund();

    UFUNCTION()
    void raundUpdate();

    FTimerHandle timerID;
    float timerRate = 0.02f;

    void gameOver();

    UFUNCTION()
    void on_CompClicked( UPrimitiveComponent* ClickedComp, FKey ButtonClicked );

};

 // ================== ADD COLOR ALTERNATE
 //   Color addColor( const Color c1 , const Color c2 ) const {

//         struct twoColors {

//            Color _c1;
//            Color _c2;

//            twoColors( Color c1 ,Color c2 ) : _c1(c1) , _c2(c2) {}

//         };

//         TMap< Color  , twoColors >  colorSumMap;
//         colorSumMap.Add( Red , twoColors ( Green , Blue ) );

