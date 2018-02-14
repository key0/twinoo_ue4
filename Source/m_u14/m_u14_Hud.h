
#pragma once

#include "GameFramework/HUD.h"
#include "m_u14_Hud.generated.h"

//DECLARE_DELEGATE( FButtonPressEvent )
DECLARE_DELEGATE_OneParam( FButtonPressEvent, uint8 )

UCLASS()
class M_U14_API Am_u14_Hud : public AHUD {

     GENERATED_BODY()

public :

    FButtonPressEvent on_buttonPress ;

    enum e_type_button {

        startButton
       ,stopButton
       ,button_types

    };

private :

    struct Button {


        e_type_button myType;

        #define START_0 "/Game/myHud/Start_button_0.Start_button_0"
        #define START_1 "/Game/myHud/Start_button_1.Start_button_1"
        #define STOP_0  "/Game/myHud/Stop_button_0.Stop_button_0"
        #define STOP_1  "/Game/myHud/Stop_button_1.Stop_button_1"


       Button() :  X ( 0 )
                    , Y ( 0 )
                    , W ( 0 )
                    , H ( 0 )
       {}

       float X, W ;
       float Y, H ;
      // FString name ;

       UTexture2D* bodyTex2D = nullptr ;

       bool create( float newX , float newY , e_type_button newType, const TCHAR* ue4Path ) {

            bodyTex2D = LoadObject<UTexture2D>( 0 , ue4Path ) ;//GetOuter()
            //LoadObject<UTexture2D>( this , TEXT("/Game/Stop_button_0.Stop_button_0") ) ;

            if ( nullptr == bodyTex2D ) return false;
            X = newX ;
            Y = newY ;
            W = bodyTex2D ->Resource ->GetSizeX();
            H = bodyTex2D ->Resource ->GetSizeY();
            myType = newType ;

            return true;
       }

       void setPressed ( const TCHAR* ue4Path ) {

            bodyTex2D = LoadObject<UTexture2D>( 0 , ue4Path ) ;//GetOuter()
            //state = pressed ;
           //if ( nullptr == bodyTex2D ) return ;
       }

       bool isPressed( float posX , float posY ) {

            return (
                       posX >=   X
                    && posX <= ( X + W )
                    && posY >=   Y
                    && posY <= ( Y + H )
                                          ) ;

       }

    };// ButtonHUD

    Am_u14_Hud();

    Button btnStart;
    Button btnStop;
    void drawButtons();

//public :

//    ButtonHUD* hudButton;

protected:

    virtual void DrawHUD() override;
	
};

