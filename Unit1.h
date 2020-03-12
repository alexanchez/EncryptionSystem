//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include <Menus.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TMemo *Memo1;
	TMemo *Memo2;
	TOpenTextFileDialog *OpenTextFileDialog1;
	TGroupBox *GroupBox1;
	TEdit *Edit1;
	TSaveTextFileDialog *SaveTextFileDialog1;
	TPopupMenu *PopupMenu1;
	TMenuItem *POpenFile;
	TMenuItem *PSaveFile;
	TRadioButton *RadioButton1;
	TRadioButton *RadioButton2;
	TBitBtn *Action;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton2;
	TSpeedButton *SpeedButton3;
	TComboBox *ComboBox1;
	TListBox *ListBox1;
	TMenuItem *PClearMemo;
	TBitBtn *Exchange;
	TGroupBox *GroupBox2;
	TEdit *Edit2;
	TLabel *Label1;
	TLabel *Label2;
	TEdit *Edit3;
	TButton *Button1;
	TGroupBox *GroupBox3;
	TLabel *Label3;
	TLabel *Label4;
	TEdit *Edit4;
	TEdit *Edit5;
	void __fastcall Memo1ContextPopup(TObject *Sender, TPoint &MousePos, bool &Handled);
	void __fastcall Memo2ContextPopup(TObject *Sender, TPoint &MousePos, bool &Handled);
	void __fastcall POpenFileClick(TObject *Sender);
	void __fastcall PSaveFileClick(TObject *Sender);
	void __fastcall ActionClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall RadioButton1Click(TObject *Sender);
	void __fastcall RadioButton2Click(TObject *Sender);
	void __fastcall ComboBox1Change(TObject *Sender);
	void __fastcall ComboBox1CloseUp(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall PClearMemoClick(TObject *Sender);
	void __fastcall ExchangeClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);


private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	void __fastcall TForm1::EditPress(TObject *Sender, wchar_t &Key)
          {
			TEdit *Current=static_cast<TEdit *>(Sender);
			if((Key!=VK_BACK)&&(Key<'0'||Key>'9')&&(Key!='-'))Key=0;
			if(Key=='-')
			{if(Current->Text.Pos("-"))Key=0;
			else if(Current->SelStart!=0)Key=0;
			}
			Current=NULL;delete Current;
		  }
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
