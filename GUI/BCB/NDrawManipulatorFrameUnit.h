//---------------------------------------------------------------------------

#ifndef NDrawManipulatorFrameUnitH
#define NDrawManipulatorFrameUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TUVisualControllerFrameUnit.h"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include "nmsdk_cpp_initdll.h"
//#include "nmsdk.bcb.h"
//---------------------------------------------------------------------------
class TNDrawManipulatorFrame : public TUVisualControllerFrame
{
__published:	// IDE-managed Components
	TPanel *Panel3;
	TButton *Button1;
	TImage *Image;
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TNDrawManipulatorFrame(TComponent* Owner);
	// Отображаемое изображение
RDK::UBitmap BmpCanvas;
RDK::UGraphics BmpGraphics;

// Разрешение изображения
int CanvasWidth,CanvasHeight;

// Координаты узла звена
double X1,X2,Y1,Y2;

// Угол поворота звена
double Angle1,Angle2;

// Смещение по перемещению при отображении
double Movement;

// Длина звена (пикс)
double Length;

// Константное смещение на постоянный угол при отображении
double ZeroAngle;

// Константное смещение по перемещению при отображении
double ZeroMovement;

int NumElem;

double MaxAng;

TBitmap *TempBmp;

void DrawEngine(double x,double y,double angle);
void AUpdateInterface();
};
//---------------------------------------------------------------------------
extern PACKAGE TNDrawManipulatorFrame *NDrawManipulatorFrame;
//---------------------------------------------------------------------------
#endif
