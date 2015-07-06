//---------------------------------------------------------------------------

#ifndef TNAstaticGyroUnitH
#define TNAstaticGyroUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TUVisualControllerFormUnit.h"
#include <Vcl.ExtCtrls.hpp>

#include "nmsdk_cpp_initdll.h"
//#include "nmsdk.bcb.h"
//---------------------------------------------------------------------------
class TNAstaticGyro : public TUVisualControllerForm
{
__published:	// IDE-managed Components
	TImage *Image1;
	void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TNAstaticGyro(TComponent* Owner);

	RDK::UEPtr<NMSDK::NAstaticGyro> Gyro;

// Сохраняет параметры интерфейса в xml
virtual void ASaveParameters(RDK::USerStorageXML &xml);

// Загружает параметры интерфейса из xml
virtual void ALoadParameters(RDK::USerStorageXML &xml);


void AUpdateInterface(void);


// Возврат интерфейса в исходное состояние
void AClearInterface(void);


// Создание копии этого компонента
virtual TUVisualControllerForm* New(TComponent *owner=0);
};
//---------------------------------------------------------------------------
extern PACKAGE TNAstaticGyro *NAstaticGyro;
//---------------------------------------------------------------------------
#endif
