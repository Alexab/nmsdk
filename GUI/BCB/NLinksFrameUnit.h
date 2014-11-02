//---------------------------------------------------------------------------

#ifndef NLinksFrameUnitH
#define NLinksFrameUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "NANetFrameUnit.h"
//---------------------------------------------------------------------------
class TNLinksFrame : public TFrame
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TNANetFrame *NANetFrameInputs;
	TGroupBox *GroupBox2;
	TNANetFrame *NANetFrameOutputs;
	TGroupBox *GroupBox3;
	TNANetFrame *NANetFrameLinks;
	TPanel *Panel1;
	TButton *CreateLinkButton;
	TButton *BreakLinkButton;
	TSplitter *Splitter1;
	void __fastcall CreateLinkButtonClick(TObject *Sender);
	void __fastcall BreakLinkButtonClick(TObject *Sender);
	void __fastcall FrameResize(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TNLinksFrame(TComponent* Owner);

public:		// User declarations
	// Указатель на рабочую сеть
	NNet *Network;

	// Инициализация интерфейса перед первым отображением
	void __fastcall Init(NNet *net);
};
//---------------------------------------------------------------------------
extern PACKAGE TNLinksFrame *NLinksFrame;
//---------------------------------------------------------------------------
#endif
