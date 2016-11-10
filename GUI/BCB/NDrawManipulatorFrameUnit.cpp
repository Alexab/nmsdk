//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "NDrawManipulatorFrameUnit.h"
#include "TUBitmap.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TNDrawManipulatorFrame *NDrawManipulatorFrame;
//---------------------------------------------------------------------------
__fastcall TNDrawManipulatorFrame::TNDrawManipulatorFrame(TComponent* Owner)
	: TUVisualControllerFrame(Owner)
{
 BmpGraphics.SetCanvas(&BmpCanvas);
 CanvasWidth=400;
 CanvasHeight=400;
 Length=100;
 X1=CanvasWidth/2;
 Y1=50;//CanvasHeight/2;
 X2=0;
 Y2=0;
 Angle1=0;
 Angle2=0;
 BmpGraphics.SetPenWidth(2);
 //UpdateInterval = 100;
 // Константное смещение на постоянный угол при отображении
 ZeroAngle=3.1415/2;
 NumElem = 5;
 MaxAng = 3.1415/180*90;

 ZeroMovement=0;

 Movement=0;
 TempBmp=new TBitmap;
}
//---------------------------------------------------------------------------
void TNDrawManipulatorFrame::AUpdateInterface()
{
 int z=0;
 //link1+
 double deltaAngEdge = MaxAng/NumElem;
 for(int i=0;i<NumElem;i++)
 {

  Angle1=(i+1)*deltaAngEdge-deltaAngEdge/2;
  //link2+
  for(int j=0;j<NumElem;j++)
  {
   Angle2=(j+1)*deltaAngEdge-deltaAngEdge/2;
   X2=X1+Length*cos(ZeroAngle+Angle1);
   Y2=Y1+Length*sin(ZeroAngle+Angle1);
   BmpGraphics.SetCanvas(&BmpCanvas);
   BmpCanvas.SetRes(CanvasWidth,CanvasHeight,RDK::ubmRGB24);
   BmpCanvas.Fill(RDK::UColorT(255,255,255));
   BmpGraphics.SetPenColor(0x00FF0000);
   BmpGraphics.SetPenWidth(2);
   BmpGraphics.Line(0,Y1,CanvasWidth,Y1);
   BmpGraphics.Line(X1,0,X1,CanvasHeight);
   //edge
   BmpGraphics.SetPenWidth(1);
   BmpGraphics.SetPenColor(0x00000000);
   BmpGraphics.Line(X1,Y1,X2,Y2);
   BmpGraphics.Line(X2,Y2,X2+Length*cos(ZeroAngle+Angle1),Y2+Length*sin(ZeroAngle+Angle1));
   for(int k=0;k<NumElem;k++)
   {
	BmpGraphics.Line(X1,Y1,X1+Length*cos(ZeroAngle+(k+1)*deltaAngEdge),Y1+Length*sin(ZeroAngle+(k+1)*deltaAngEdge));
	BmpGraphics.Line(X1,Y1,X1+Length*cos(ZeroAngle-(k+1)*deltaAngEdge),Y1+Length*sin(ZeroAngle-(k+1)*deltaAngEdge));
	BmpGraphics.Line(X2,Y2,X2+Length*cos(ZeroAngle+(k+1)*deltaAngEdge+Angle1),Y2+Length*sin(ZeroAngle+(k+1)*deltaAngEdge+Angle1));
	BmpGraphics.Line(X2,Y2,X2+Length*cos(ZeroAngle-(k+1)*deltaAngEdge+Angle1),Y2+Length*sin(ZeroAngle-(k+1)*deltaAngEdge+Angle1));
   }
   BmpGraphics.SetPenColor(0x000000FF);
   BmpGraphics.SetPenWidth(4);
   BmpGraphics.Line(X1,Y1,X2,Y2);
   BmpGraphics.Circle(X1,Y1,10,true);
   BmpGraphics.Line(X2,Y2,X2+Length*cos(ZeroAngle+Angle1+Angle2),Y2+Length*sin(ZeroAngle+Angle1+Angle2));
   BmpGraphics.Circle(X2,Y2,10,true);
   BmpCanvas>>TempBmp;
   Image->Picture->Bitmap = TempBmp;
   Image->Repaint();
//   std::string fname = "D:/Bmp/"+RDK::sntoa(NumElem)+"/"+RDK::sntoa(z+1)+".bmp";
   z++;
   try
   {
//   Image->Picture->SaveToFile(fname.c_str());
   Image->CleanupInstance();
   }
   catch(Exception &ex)
   {

   }
  }
  //link2-
  for(int j=0;j<NumElem;j++)
  {
   Angle2=-(j+1)*deltaAngEdge+deltaAngEdge/2;
   X2=X1+Length*cos(ZeroAngle+Angle1);
   Y2=Y1+Length*sin(ZeroAngle+Angle1);
   BmpGraphics.SetCanvas(&BmpCanvas);
   BmpCanvas.SetRes(CanvasWidth,CanvasHeight,RDK::ubmRGB24);
   BmpCanvas.Fill(RDK::UColorT(255,255,255));
   BmpGraphics.SetPenColor(0x00FF0000);
   BmpGraphics.SetPenWidth(2);
   BmpGraphics.Line(0,Y1,CanvasWidth,Y1);
   BmpGraphics.Line(X1,0,X1,CanvasHeight);
   //edge
   BmpGraphics.SetPenWidth(1);
   BmpGraphics.SetPenColor(0x00000000);
   BmpGraphics.Line(X1,Y1,X2,Y2);
   BmpGraphics.Line(X2,Y2,X2+Length*cos(ZeroAngle+Angle1),Y2+Length*sin(ZeroAngle+Angle1));
   for(int k=0;k<NumElem;k++)
   {
	BmpGraphics.Line(X1,Y1,X1+Length*cos(ZeroAngle+(k+1)*deltaAngEdge),Y1+Length*sin(ZeroAngle+(k+1)*deltaAngEdge));
	BmpGraphics.Line(X1,Y1,X1+Length*cos(ZeroAngle-(k+1)*deltaAngEdge),Y1+Length*sin(ZeroAngle-(k+1)*deltaAngEdge));
	BmpGraphics.Line(X2,Y2,X2+Length*cos(ZeroAngle+(k+1)*deltaAngEdge+Angle1),Y2+Length*sin(ZeroAngle+(k+1)*deltaAngEdge+Angle1));
	BmpGraphics.Line(X2,Y2,X2+Length*cos(ZeroAngle-(k+1)*deltaAngEdge+Angle1),Y2+Length*sin(ZeroAngle-(k+1)*deltaAngEdge+Angle1));
   }
   BmpGraphics.SetPenColor(0x000000FF);
   BmpGraphics.SetPenWidth(4);
   BmpGraphics.Line(X1,Y1,X2,Y2);
   BmpGraphics.Circle(X1,Y1,10,true);
   BmpGraphics.Line(X2,Y2,X2+Length*cos(ZeroAngle+Angle1+Angle2),Y2+Length*sin(ZeroAngle+Angle1+Angle2));
   BmpGraphics.Circle(X2,Y2,10,true);
   BmpCanvas>>TempBmp;
   Image->Picture->Bitmap = TempBmp;
   Image->Repaint();
//   std::string fname = "D:/Bmp/"+RDK::sntoa(NumElem)+"/"+RDK::sntoa(z+1)+".bmp";
   z++;
   try
   {
//   Image->Picture->SaveToFile(fname.c_str());
   Image->CleanupInstance();
   }
   catch(Exception &ex)
   {

   }
  }
 }
 //link1-
 for(int i=0;i<NumElem;i++)
 {

  Angle1=-(i+1)*deltaAngEdge+deltaAngEdge/2;
  //link2+
  for(int j=0;j<NumElem;j++)
  {
   Angle2=(j+1)*deltaAngEdge-deltaAngEdge/2;
   X2=X1+Length*cos(ZeroAngle+Angle1);
   Y2=Y1+Length*sin(ZeroAngle+Angle1);
   BmpGraphics.SetCanvas(&BmpCanvas);
   BmpCanvas.SetRes(CanvasWidth,CanvasHeight,RDK::ubmRGB24);
   BmpCanvas.Fill(RDK::UColorT(255,255,255));
   BmpGraphics.SetPenColor(0x00FF0000);
   BmpGraphics.SetPenWidth(2);
   BmpGraphics.Line(0,Y1,CanvasWidth,Y1);
   BmpGraphics.Line(X1,0,X1,CanvasHeight);
   //edge
   BmpGraphics.SetPenWidth(1);
   BmpGraphics.SetPenColor(0x00000000);
   BmpGraphics.Line(X1,Y1,X2,Y2);
   BmpGraphics.Line(X2,Y2,X2+Length*cos(ZeroAngle+Angle1),Y2+Length*sin(ZeroAngle+Angle1));
   for(int k=0;k<NumElem;k++)
   {
	BmpGraphics.Line(X1,Y1,X1+Length*cos(ZeroAngle+(k+1)*deltaAngEdge),Y1+Length*sin(ZeroAngle+(k+1)*deltaAngEdge));
	BmpGraphics.Line(X1,Y1,X1+Length*cos(ZeroAngle-(k+1)*deltaAngEdge),Y1+Length*sin(ZeroAngle-(k+1)*deltaAngEdge));
	BmpGraphics.Line(X2,Y2,X2+Length*cos(ZeroAngle+(k+1)*deltaAngEdge+Angle1),Y2+Length*sin(ZeroAngle+(k+1)*deltaAngEdge+Angle1));
	BmpGraphics.Line(X2,Y2,X2+Length*cos(ZeroAngle-(k+1)*deltaAngEdge+Angle1),Y2+Length*sin(ZeroAngle-(k+1)*deltaAngEdge+Angle1));
   }
   BmpGraphics.SetPenColor(0x000000FF);
   BmpGraphics.SetPenWidth(4);
   BmpGraphics.Line(X1,Y1,X2,Y2);
   BmpGraphics.Circle(X1,Y1,10,true);
   BmpGraphics.Line(X2,Y2,X2+Length*cos(ZeroAngle+Angle1+Angle2),Y2+Length*sin(ZeroAngle+Angle1+Angle2));
   BmpGraphics.Circle(X2,Y2,10,true);
   BmpCanvas>>TempBmp;
   Image->Picture->Bitmap = TempBmp;
   Image->Repaint();
//   std::string fname = "D:/Bmp/"+RDK::sntoa(NumElem)+"/"+RDK::sntoa(z+1)+".bmp";
   z++;
   try
   {
//   Image->Picture->SaveToFile(fname.c_str());
   Image->CleanupInstance();
   }
   catch(Exception &ex)
   {

   }
  }
  //link2-
  for(int j=0;j<NumElem;j++)
  {
   Angle2=-(j+1)*deltaAngEdge+deltaAngEdge/2;
   X2=X1+Length*cos(ZeroAngle+Angle1);
   Y2=Y1+Length*sin(ZeroAngle+Angle1);
   BmpGraphics.SetCanvas(&BmpCanvas);
   BmpCanvas.SetRes(CanvasWidth,CanvasHeight,RDK::ubmRGB24);
   BmpCanvas.Fill(RDK::UColorT(255,255,255));
   BmpGraphics.SetPenColor(0x00FF0000);
   BmpGraphics.SetPenWidth(2);
   BmpGraphics.Line(0,Y1,CanvasWidth,Y1);
   BmpGraphics.Line(X1,0,X1,CanvasHeight);
   //edge
   BmpGraphics.SetPenWidth(1);
   BmpGraphics.SetPenColor(0x00000000);
   BmpGraphics.Line(X1,Y1,X2,Y2);
   BmpGraphics.Line(X2,Y2,X2+Length*cos(ZeroAngle+Angle1),Y2+Length*sin(ZeroAngle+Angle1));
   for(int k=0;k<NumElem;k++)
   {
	BmpGraphics.Line(X1,Y1,X1+Length*cos(ZeroAngle+(k+1)*deltaAngEdge),Y1+Length*sin(ZeroAngle+(k+1)*deltaAngEdge));
	BmpGraphics.Line(X1,Y1,X1+Length*cos(ZeroAngle-(k+1)*deltaAngEdge),Y1+Length*sin(ZeroAngle-(k+1)*deltaAngEdge));
	BmpGraphics.Line(X2,Y2,X2+Length*cos(ZeroAngle+(k+1)*deltaAngEdge+Angle1),Y2+Length*sin(ZeroAngle+(k+1)*deltaAngEdge+Angle1));
	BmpGraphics.Line(X2,Y2,X2+Length*cos(ZeroAngle-(k+1)*deltaAngEdge+Angle1),Y2+Length*sin(ZeroAngle-(k+1)*deltaAngEdge+Angle1));
   }
   BmpGraphics.SetPenColor(0x000000FF);
   BmpGraphics.SetPenWidth(4);
   BmpGraphics.Line(X1,Y1,X2,Y2);
   BmpGraphics.Circle(X1,Y1,10,true);
   BmpGraphics.Line(X2,Y2,X2+Length*cos(ZeroAngle+Angle1+Angle2),Y2+Length*sin(ZeroAngle+Angle1+Angle2));
   BmpGraphics.Circle(X2,Y2,10,true);
   BmpCanvas>>TempBmp;
   Image->Picture->Bitmap = TempBmp;
   Image->Repaint();
//   std::string fname = "D:/Bmp/"+RDK::sntoa(NumElem)+"/"+RDK::sntoa(z+1)+".bmp";
   z++;
   try
   {
//   Image->Picture->SaveToFile(fname.c_str());
   Image->CleanupInstance();
   }
   catch(Exception &ex)
   {

   }
  }
 }
}
void TNDrawManipulatorFrame::DrawEngine(double x,double y,double angle)
{

}
void __fastcall TNDrawManipulatorFrame::Button1Click(TObject *Sender)
{
 UpdateInterface();
}
//---------------------------------------------------------------------------

