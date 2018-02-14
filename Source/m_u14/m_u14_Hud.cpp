
#include "m_u14.h"
#include "m_u14_Hud.h"

Am_u14_Hud::Am_u14_Hud() {

	UE_LOG(LogTemp, Warning, TEXT("=== CTOR::Am_u14_Hud "));

    if ( btnStart.create( 10 , 10 , startButton , TEXT( START_0 ) ) ) UE_LOG(LogTemp, Warning, TEXT("=== BTN START LOADED!! "));
    if ( btnStop. create( 10 , 60 , stopButton  , TEXT( STOP_0  ) ) ) UE_LOG(LogTemp, Warning, TEXT("=== BTN STOP  LOADED!! "));

}

void Am_u14_Hud::drawButtons() {

    auto
    item = FCanvasTileItem(  FVector2D (btnStart.X ,btnStart.Y)
                           , btnStart.bodyTex2D ->Resource//
                           , FLinearColor::White          );

    item.BlendMode = SE_BLEND_Translucent;
    Canvas ->DrawItem( item );

    item = FCanvasTileItem(  FVector2D (btnStop.X ,btnStop.Y)
                           , btnStop.bodyTex2D ->Resource//
                           , FLinearColor::White          );

    item.BlendMode = SE_BLEND_Translucent;
    Canvas ->DrawItem( item );

}

void Am_u14_Hud::DrawHUD() {
	
	Super::DrawHUD();
    
	if ( Canvas == nullptr ) return ;
	auto pc = GetOwningPlayerController() ;
	if ( pc == nullptr ) return ;


    //_____UNPAUSE
    if ( pc ->WasInputKeyJustPressed(EKeys::SpaceBar) ) {

         pc ->SetPause( false ) ;
    }

    drawButtons();

    static float mouseX;
    static float mouseY;

    pc ->GetMousePosition(mouseX, mouseY);

    if ( pc ->WasInputKeyJustPressed( EKeys::LeftMouseButton ) ) {

        if ( btnStart.isPressed( mouseX,mouseY ) ) {

            UE_LOG(LogTemp, Warning, TEXT("=== BTN START PRESSED :mouseX=%f,mouseY=%f , btn.X=%f ,btn.W=%f "),mouseX,mouseY,btnStart.X,btnStart.W );

            btnStart.setPressed( TEXT( START_1 ) );

            on_buttonPress.ExecuteIfBound( startButton );

        }

        if ( btnStop .isPressed( mouseX,mouseY ) ) {

            UE_LOG(LogTemp, Warning, TEXT("=== BTN STOP PRESSED :mouseX=%f,mouseY=%f , btn.X=%f ,btn.W=%f "),mouseX,mouseY,btnStop.X,btnStop.W );

            btnStop.setPressed( TEXT( STOP_1 ) );

            on_buttonPress.ExecuteIfBound( stopButton );
        }

    }


}

//Canvas->DrawText(  GEngine->GetLargeFont()//GetSmallFont()
//                 , TEXT("___MENU___")
//                 , 100
//                 , 100						);
