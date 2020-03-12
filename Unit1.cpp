//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "math.h"
#include "time.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
TStringList *matrix=new TStringList();
AnsiString crypto_key;
//int crypto_shift;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
   srand(time(NULL));
   GroupBox2->Left=9;GroupBox3->Left=9;
   //OpenTextFileDialog1->InitialDir = ExtractFileDir(Application->ExeName);//+"\\Шифры";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
  if(Key=='1' && Shift.Contains(ssAlt))RadioButton1->Checked=true;
  if(Key=='2' && Shift.Contains(ssAlt))RadioButton2->Checked=true;
  if(Key=='1' && Shift.Contains(ssCtrl)){ComboBox1->ItemIndex=0;ComboBox1Change(Sender);}
  if(Key=='2' && Shift.Contains(ssCtrl)){ComboBox1->ItemIndex=1;ComboBox1Change(Sender);}
  if(Key=='3' && Shift.Contains(ssCtrl)){ComboBox1->ItemIndex=2;ComboBox1Change(Sender);}
  if(Key=='4' && Shift.Contains(ssCtrl)){ComboBox1->ItemIndex=3;ComboBox1Change(Sender);}
  if(Key=='5' && Shift.Contains(ssCtrl)){ComboBox1->ItemIndex=4;ComboBox1Change(Sender);}
  if(Key=='6' && Shift.Contains(ssCtrl)){ComboBox1->ItemIndex=5;ComboBox1Change(Sender);}
  if(Key=='7' && Shift.Contains(ssCtrl)){ComboBox1->ItemIndex=6;ComboBox1Change(Sender);}
  if(Key=='8' && Shift.Contains(ssCtrl)){ComboBox1->ItemIndex=7;ComboBox1Change(Sender);}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
  Edit1->OnKeyPress=EditPress;Edit2->OnKeyPress=EditPress;Edit3->OnKeyPress=EditPress;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
  delete matrix;matrix=NULL;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Memo1ContextPopup(TObject *Sender, TPoint &MousePos, bool &Handled)

{
  POpenFile->Visible=true;PSaveFile->Visible=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Memo2ContextPopup(TObject *Sender, TPoint &MousePos, bool &Handled)

{
  POpenFile->Visible=false;PSaveFile->Visible=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton1Click(TObject *Sender)
{
  GroupBox1->Enabled=true;GroupBox1->Color=clWhite;Edit1->Color=clWhite;
  GroupBox2->Enabled=true;GroupBox2->Color=clWhite;Edit2->Color=clWhite;Edit3->Color=clWhite;
  GroupBox3->Enabled=true;GroupBox3->Color=clWhite;Edit4->Color=clWhite;Edit5->Color=clWhite;
  ListBox1->Items->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton2Click(TObject *Sender)
{
  GroupBox1->Enabled=false;GroupBox1->Color=(TColor)RGB(245,245,245);Edit1->Color=(TColor)RGB(245,245,245);
  GroupBox2->Enabled=false;GroupBox2->Color=(TColor)RGB(245,245,245);Edit2->Color=(TColor)RGB(245,245,245);Edit3->Color=(TColor)RGB(245,245,245);
  GroupBox3->Enabled=false;GroupBox3->Color=(TColor)RGB(245,245,245);Edit4->Color=(TColor)RGB(245,245,245);Edit5->Color=(TColor)RGB(245,245,245);
  ListBox1->Items->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::POpenFileClick(TObject *Sender)
{
  if(OpenTextFileDialog1->Execute())
  {
	 if(ComboBox1->ItemIndex==0||ComboBox1->ItemIndex==3||ComboBox1->ItemIndex==4||ComboBox1->ItemIndex==5||
		ComboBox1->ItemIndex==6||ComboBox1->ItemIndex==7||(ComboBox1->ItemIndex==1&&RadioButton1->Checked)||
		(ComboBox1->ItemIndex==2&&RadioButton1->Checked))
		Memo1->Lines->LoadFromFile(OpenTextFileDialog1->FileName);
	 if(ComboBox1->ItemIndex==1&&RadioButton2->Checked)
	 {
	   if(OpenTextFileDialog1->FileName.Pos("_matrix"))ListBox1->Items->LoadFromFile(OpenTextFileDialog1->FileName);
	   else
	   {
       Memo1->Lines->LoadFromFile(OpenTextFileDialog1->FileName);
	   OpenTextFileDialog1->FileName=OpenTextFileDialog1->FileName.Delete(OpenTextFileDialog1->FileName.Length()-3,4);
	   try{ListBox1->Items->LoadFromFile(OpenTextFileDialog1->FileName+"_matrix.txt");}catch(...){ShowMessage("Для даного методу необхідно матрицю!");POpenFileClick(Sender);}
	   }
	 }
	 if(ComboBox1->ItemIndex==2&&RadioButton2->Checked)
	 {
	   if(OpenTextFileDialog1->FileName.Pos("_(a,b)"))ListBox1->Items->LoadFromFile(OpenTextFileDialog1->FileName);
	   else
	   {
	   Memo1->Lines->LoadFromFile(OpenTextFileDialog1->FileName);
	   OpenTextFileDialog1->FileName=OpenTextFileDialog1->FileName.Delete(OpenTextFileDialog1->FileName.Length()-3,4);
	   try{ListBox1->Items->LoadFromFile(OpenTextFileDialog1->FileName+"_(a,b).txt");}catch(...){ShowMessage("Для даного методу необхідно завантажити ключі(a,b)!");POpenFileClick(Sender);}
	   }
	 }
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PSaveFileClick(TObject *Sender)
{
  if(SaveTextFileDialog1->Execute())
  {
	if(ComboBox1->ItemIndex==1&&RadioButton1->Checked)
	{
	  if(ExtractFileExt(SaveTextFileDialog1->FileName) != ".txt")
		matrix->SaveToFile(ExtractFileDir(SaveTextFileDialog1->FileName)+"\\"+ExtractFileName(SaveTextFileDialog1->FileName)+"_matrix.txt");
	  else
	  {
		SaveTextFileDialog1->FileName=SaveTextFileDialog1->FileName.Delete(SaveTextFileDialog1->FileName.Length()-3,4);
		matrix->SaveToFile(SaveTextFileDialog1->FileName+"_matrix.txt");
	  }
	}
	if(ComboBox1->ItemIndex==2&&RadioButton1->Checked)
	{
	  if(ExtractFileExt(SaveTextFileDialog1->FileName) != ".txt")
		matrix->SaveToFile(ExtractFileDir(SaveTextFileDialog1->FileName)+"\\"+ExtractFileName(SaveTextFileDialog1->FileName)+"_(a,b).txt");
	  else
	  {
		SaveTextFileDialog1->FileName=SaveTextFileDialog1->FileName.Delete(SaveTextFileDialog1->FileName.Length()-3,4);
		matrix->SaveToFile(SaveTextFileDialog1->FileName+"_(a,b).txt");
	  }
	}
	if(SaveTextFileDialog1->FileName.Pos(".txt"))
	 Memo2->Lines->SaveToFile(SaveTextFileDialog1->FileName);
	else
	 Memo2->Lines->SaveToFile(SaveTextFileDialog1->FileName+".txt");
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PClearMemoClick(TObject *Sender)
{
  if(Memo1->Focused())Memo1->Clear();
  if(Memo2->Focused())Memo2->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ExchangeClick(TObject *Sender)
{
  Memo1->Text=Memo2->Text;Memo2->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBox1Change(TObject *Sender)
{
  if(ComboBox1->ItemIndex!=1)ListBox1->Items->Clear();
  if(ComboBox1->ItemIndex!=2){GroupBox1->Visible=true;GroupBox2->Visible=false;GroupBox3->Visible=false;}
  if(ComboBox1->ItemIndex==2){GroupBox1->Visible=false;GroupBox2->Visible=true;GroupBox3->Visible=false;}
  if(ComboBox1->ItemIndex==4){GroupBox1->Visible=false;GroupBox2->Visible=false;GroupBox3->Visible=true;}
  if(ComboBox1->ItemIndex==3)Button1->Visible=true;
  else {Button1->Visible=false;if(Form2->Visible)Form2->Close();}
  if(ComboBox1->ItemIndex==3||ComboBox1->ItemIndex==6){Edit1->OnKeyPress=NULL;GroupBox1->Caption="Ключ(текст)";}
  else {Edit1->OnKeyPress=EditPress;GroupBox1->Caption="Величина зсуву";}
  if(ComboBox1->ItemIndex==5){GroupBox1->Visible=false;}
  Edit2->Height=20;Edit3->Height=20;Edit4->Height=20;Edit5->Height=20;
  if(ComboBox1->ItemIndex==7){GroupBox1->Visible=false;GroupBox2->Visible=false;GroupBox3->Visible=false;}
  Action->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBox1CloseUp(TObject *Sender)
{
  Action->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
  Form2->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ActionClick(TObject *Sender)
{
  if(Memo1->Text.Length()==0){ShowMessage("Текст не введений!");return;}
  TStringList *list=new TStringList();
  TStringList *voc=new TStringList();
  Action->Tag=0;//0 - словник;1 - перебір
  int count;//Кількість знайдених слів з тексту у словнику
  int QuantLetters;
  AnsiString alphabet,freqtable;
  int frequencies[33]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  if(SpeedButton1->Down)
  {
	alphabet="абвгґдеєжзиіїйклмнопрстуфхцчшщьюя";
	freqtable="онаитверіскмдлупязьгчбхцюжйїєфшщґ";
	QuantLetters=33;
	voc->LoadFromFile(ExtractFileDir(Application->ExeName)+"\\Vocabulary(ua).txt");
  }
  if(SpeedButton2->Down)
  {
	alphabet="абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
	freqtable="аеёкпфщюбжлрхъявзмсцыгинтчьдйоушэ";
	QuantLetters=33;
	voc->LoadFromFile(ExtractFileDir(Application->ExeName)+"\\Vocabulary(ru).txt");
  }
  if(SpeedButton3->Down)
  {
	alphabet="abcdefghijklmnopqrstuvwxyz";
	freqtable="etiaonsrhcldpyumfbgwvkxqzj";
	QuantLetters=26;
	voc->LoadFromFile(ExtractFileDir(Application->ExeName)+"\\Vocabulary(en).txt");
  }
  AnsiString text=Memo1->Text;
  int shift,index,pos=0;
  //Таблиця Віженера
  //if(ComboBox1->ItemIndex==3){QuantLetters++;alphabet=alphabet+" ";}//С пробелом
  Form2->StringGrid1->ColCount=QuantLetters+1;Form2->StringGrid1->RowCount=QuantLetters+1;
  for(int i=1;i<Form2->StringGrid1->ColCount;i++)for(int j=1;j<Form2->StringGrid1->RowCount;j++)Form2->StringGrid1->Cells[i][j]="";
  for(int i=1;i<Form2->StringGrid1->ColCount;i++)Form2->StringGrid1->Cells[i][0]=AnsiString(alphabet.UpperCase().c_str()[i-1]);
  for(int i=1;i<Form2->StringGrid1->RowCount;i++)Form2->StringGrid1->Cells[0][i]=AnsiString(alphabet.UpperCase().c_str()[i-1]);
  //if(ComboBox1->ItemIndex==3)alphabet.c_str()[QuantLetters-1]='*';//С пробелом
  for(int i=1;i<Form2->StringGrid1->RowCount;i++)
  {
	for(int j=1;j<Form2->StringGrid1->ColCount;j++)
	{
	  index=pos+j-1;//pos-зсув
	  if(index>=QuantLetters)index-=QuantLetters;
	  Form2->StringGrid1->Cells[j][i]=AnsiString(alphabet.UpperCase().c_str()[index]);
	}
	pos++;
  }
  //*************************************Шифрування**********************************
  if(RadioButton1->Checked)
  {
	  if(ComboBox1->ItemIndex==0 || ComboBox1->ItemIndex==1)//Цезарь-Проста заміна
	  {
		if(Edit1->Text==""){ShowMessage("Величина зсуву не введена!");return;}
		shift=Edit1->Text.ToInt();
		for(int i=0;i<text.Length();i++)
		 if(alphabet.Pos(text.LowerCase().c_str()[i]))
		 {
			index=alphabet.Pos(text.LowerCase().c_str()[i]);
			pos=index+shift;
			if(pos>QuantLetters)while(pos>QuantLetters)pos-=QuantLetters;
			else if(pos<=0)while(pos<=0)pos=QuantLetters-abs(pos);
			if(text.c_str()[i]==text.UpperCase().c_str()[i])
			   text.c_str()[i]=alphabet.UpperCase().c_str()[pos-1];
			else text.c_str()[i]=alphabet.c_str()[pos-1];
		 }
	  }
	  if(ComboBox1->ItemIndex==0)//Звичайний Цезарь
		 Memo2->Text=text;
	  if(ComboBox1->ItemIndex==1)//Проста заміна
	  {
		  AnsiString text_numbers;
		  matrix->Clear();
		  for(int i=0;i<QuantLetters*2+1;i++)//Убрать *2 для "без регистра";      +1 - пробел
		  {
			for(;;)
			{
			 int number=rand()%90+10;
			 if(matrix->IndexOf(IntToStr(number))==-1)
				{matrix->Add(number);break;}
			}
		  }
		  for(int i=0;i<text.Length();i++)
		  {
		   if(alphabet.Pos(text.LowerCase().c_str()[i]))
		   {
			  index=alphabet.Pos(text.LowerCase().c_str()[i]);
			  if(text.c_str()[i]==text.LowerCase().c_str()[i])text_numbers+=matrix->Strings[index-1];//r
			  else text_numbers+=matrix->Strings[index-1+QuantLetters];//r
			  //text_numbers+=matrix->Strings[index-1];//Оставить это для "без регистра"
		   }
		   else
			 {if(text.c_str()[i]==' ')text_numbers+=matrix->Strings[matrix->Count-1];//Пробел
			  else text_numbers+=text.c_str()[i];}
		  }
		  Memo2->Text=text_numbers;
		  ListBox1->Items->Clear();
		  for(int i=0;i<(matrix->Count-1)/2;i++)//Убрать /2 для "без регистра";    -1 - пробел
			ListBox1->Items->Add(AnsiString(alphabet.c_str()[i])+AnsiString("–")+AnsiString(matrix->Strings[i]));
		  for(int i=(matrix->Count-1)/2;i<matrix->Count-1;i++)//Полностью убрать   -1 - пробел
			ListBox1->Items->Add(AnsiString(alphabet.UpperCase().c_str()[i-QuantLetters])+AnsiString("–")+AnsiString(matrix->Strings[i]));
		  ListBox1->Items->Add(AnsiString(" -")+AnsiString(matrix->Strings[matrix->Count-1]));//Пробел
		  //Збереження ключа---
		  if(shift>=0)matrix->Add(shift);
		  else
		   {
			 shift=abs(shift);
			 if(shift>QuantLetters)while(shift>QuantLetters)shift-=QuantLetters;
			 matrix->Add(QuantLetters-shift);
		   }
		  }
	  if(ComboBox1->ItemIndex==2)//Афінна система підстановок Цезаря
	  {
		  if(Edit2->Text==""||Edit3->Text==""){ShowMessage("Параметри шифрування не введені!");return;}
		  int a=Edit2->Text.ToInt(),b=Edit3->Text.ToInt();
		  for(int i=1;i<=abs(a);i++)//від 1,т.к. може a=1
			if(i!=1 && abs(a)%i==0 && QuantLetters%i==0)
			  {ShowMessage("НСД("+AnsiString(a)+","+AnsiString(QuantLetters)+")!=1"+" ("+AnsiString(i)+")");return;}
		  for(int i=0;i<text.Length();i++)
			if(alphabet.Pos(text.LowerCase().c_str()[i]))
			{
			  index=alphabet.Pos(text.LowerCase().c_str()[i]);
			  shift=a*(index-1)+b;//E=at+b
			  if(shift>=QuantLetters)while(shift>=QuantLetters)shift-=QuantLetters;
			  else if(shift<0)while(shift<0)shift=QuantLetters-abs(shift);
			  if(text.c_str()[i]==text.UpperCase().c_str()[i])
			     text.c_str()[i]=alphabet.UpperCase().c_str()[shift];
			  else text.c_str()[i]=alphabet.c_str()[shift];
			}
		  Memo2->Text=text;
		  matrix->Clear();matrix->Add(a);matrix->Add(b);//Збереження ключа (a,b)
	  }
	  if(ComboBox1->ItemIndex==3)//Віженера
	  {
		  if(Edit1->Text.Length()==0){ShowMessage("Ключ не введений!");return;}
		  pos=0;
		  for(int i=0;i<text.Length();i++)
		   if(alphabet.Pos(text.LowerCase().c_str()[i]))
			{
			  AnsiString letter=Form2->StringGrid1->Cells[alphabet.Pos(text.LowerCase().c_str()[i])][alphabet.Pos(Edit1->Text.LowerCase().c_str()[pos])];//[char_index][key_index]
			  text.c_str()[i]=letter.LowerCase().c_str()[0];
			  pos++;
			  if(pos==Edit1->Text.Length())pos=0;
			}
		  Memo2->Text=text;
	  }
	  if(ComboBox1->ItemIndex==4)//Модернізований код Цезаря
	  {
		  if(Edit4->Text.Length()==0){ShowMessage("Зсув k не введений!");return;}
		  if(Edit5->Text.Length()==0){ShowMessage("Ключ не введений!");return;}
		  if(Edit5->Text.Length()>QuantLetters){ShowMessage("Довжина ключа>кількості букв алфавіта!");return;}
		  if(Edit4->Text.ToInt()>QuantLetters){ShowMessage("Зсув k має бути в діапазоні 1-"+AnsiString(QuantLetters));return;}
		  AnsiString key,new_alphabet=alphabet;
		  int k=Edit4->Text.ToInt(),key_length;
		  for(int i=0;i<Edit5->Text.Length();i++)
		   if(!key.Pos(Edit5->Text.c_str()[i]))
			   {key=key+Edit5->Text.c_str()[i];
				new_alphabet=new_alphabet.Delete(new_alphabet.Pos(Edit5->Text.c_str()[i]),1);
			   }
		  key_length=key.Length();
		  for(int i=0;i<new_alphabet.Length();i++)                        //справа
		   if(key.Length()<QuantLetters-k)
			  key=key+AnsiString(new_alphabet.c_str()[i]);
		  pos=1;
		  for(int i=QuantLetters-key_length-k;i<new_alphabet.Length();i++)//зліва
			  {key=key.Insert(AnsiString(new_alphabet.c_str()[i]),pos);pos++;}
		  for(int i=0;i<text.Length();i++)
		   if(alphabet.Pos(text.LowerCase().c_str()[i]))
			{
				text.c_str()[i]=key.c_str()[alphabet.Pos(text.LowerCase().c_str()[i])-1];
			}
		  crypto_key=key;
		  Memo2->Text=text;
	  }
	  if(ComboBox1->ItemIndex==5)//Полібія
	  {
		  int n;
		  if(SpeedButton1->Down||SpeedButton2->Down){alphabet=alphabet+".!?";n=6;QuantLetters=36;}
		  else {alphabet="abcdefghiklmnopqrstuvwxyz";n=5;QuantLetters=25;}//без j
		  for(int i=0;i<text.Length();i++)
		   if(alphabet.Pos(text.LowerCase().c_str()[i]))
			{
				index=alphabet.Pos(text.LowerCase().c_str()[i])-n;
				if(index<=0)index=QuantLetters-abs(index);
				text.c_str()[i]=alphabet.c_str()[index-1];
			}
		  Memo2->Text=text;
	  }
	  if(ComboBox1->ItemIndex==6)//Перестановочний з ключовим словом(матричний шифр з ключем)
	  {
		  if(Edit1->Text.Length()==0){ShowMessage("Ключ не введений!");return;}
		  if(Edit1->Text.Length()<4||Edit1->Text.Length()>8){ShowMessage("Довжина ключа має бути в межах 4-8");return;}
		  if(Edit1->Text.Length()>text.Length()){ShowMessage("Довжина ключа>довжини текста!");return;}
		  AnsiString index_sorted,word=Edit1->Text,text_encrypted;
		  char temp;
		  for(int i=0;i<word.Length();i++)
		   for(int j=i+1;j<word.Length();j++)
			if(word.c_str()[i]>word.c_str()[j])
			 {temp=word.c_str()[i];
			  word.c_str()[i]=word.c_str()[j];
			  word.c_str()[j]=temp;
			 }
		  for(int i=0;i<word.Length();i++)
			 index_sorted=index_sorted+AnsiString(Edit1->Text.Pos(AnsiString(word.c_str()[i]))-1);
		  int n=word.Length();
		  pos=0;
		  for(int i=0;i<n;i++)
		  {
		   index=StrToInt(index_sorted.c_str()[i]);
		   for(int j=index;j<text.Length();j=j+n)
			 if(alphabet.Pos(text.LowerCase().c_str()[j]))
				text_encrypted=text_encrypted+AnsiString(text.c_str()[j]);
		  }
		  crypto_key=index_sorted;
		  Memo2->Text=text_encrypted;
		  //Memo2->Lines->Add(index_sorted);
	  }
	  if(ComboBox1->ItemIndex==7)//Потокове шифрування з гаммою
	  {
		  alphabet=alphabet+" ";QuantLetters++;
		  //QuantLetters=32;alphabet="абвгдежзийклмнопрсту хцчшщъыьэюя";//проверка значений задания
		  AnsiString new_text;int k=0;
		  TStringList *indexes=new TStringList();
		  for(int i=0;i<text.Length();i++)
		   if(alphabet.Pos(text.LowerCase().c_str()[i]))
			  indexes->Add(alphabet.Pos(text.LowerCase().c_str()[i])-1);
		  //ShowMessage(indexes->Text);//відкрите повідомлення
		  matrix->Clear();
		  //matrix->Add("4");matrix->Add("31");matrix->Add("15");//проверка значений задания
		  //Ключ шифрування
		  for(int i=0;i<3;i++)//K=(Y1,Y2,Y3)
		  {
			for(;;)
			{
			 int number=rand()%QuantLetters+0;
			 if(matrix->IndexOf(IntToStr(number))==-1)
				{matrix->Add(number);break;}
			}
		  }
		  for(int i=3;i<indexes->Count;i++)//Y_t=(Y_(t-1)+Y_(t-3))mod n
			  matrix->Add((matrix->Strings[i-1].ToInt()+matrix->Strings[i-3].ToInt())%QuantLetters);
		  matrix->Add((matrix->Strings[matrix->Count-1].ToInt()+matrix->Strings[matrix->Count-3].ToInt())%QuantLetters);
		  //ShowMessage(matrix->Text);//послідовність Y
		  for(int i=0;i<matrix->Count-1;i++)//Z_t=(Y_t+Y_(t+1))mod n
			matrix->Strings[i]=IntToStr((matrix->Strings[i].ToInt()+matrix->Strings[i+1].ToInt())%QuantLetters);
		  matrix->Delete(matrix->Count-1);//після злиття - видаляємо останній
		  //ShowMessage(matrix->Text);//шифро гамма Z
		  for(int i=0;i<text.Length();i++)
		  {
		   if(alphabet.Pos(text.LowerCase().c_str()[i]))//Si=(C(ti)+Ki)mod n
			{
				index=(indexes->Strings[k].ToInt()+matrix->Strings[k].ToInt())%QuantLetters;
				new_text+=alphabet.c_str()[index];
				k++;
			}
		   else new_text+=text.c_str()[i];
		  }
		  Memo2->Text=new_text;
		  delete indexes;indexes=NULL;
	  }
   //*************
   if(MessageDlg("Зберегти отриманий шифр?",mtConfirmation,TMsgDlgButtons()<<mbYes<<mbNo,0)==mrYes)
	  PSaveFileClick(Sender);
  }
  //*************************************Дешифрування**********************************
  if(RadioButton2->Checked)
  {
	  AnsiString text_chars;
	  if(ComboBox1->ItemIndex==1)//Проста заміна
	  {
		  if(ListBox1->Items->Count==0){ShowMessage("Завантажте матрицю до шифру!");return;}
		  matrix->Assign(ListBox1->Items);
		  shift=matrix->Strings[matrix->Count-1].ToInt();//Зчитування ключа (останнє число матриці)
		  matrix->Delete(matrix->Count-1);//Видалення ключа з матриці
		  AnsiString number;
		  for(int i=0;i<text.Length();i++)
		  {
		   if(isdigit(text.c_str()[i]))
		   {
			if(i+1<text.Length()&&isdigit(text.c_str()[i+1]))//if(isdigit(text.c_str()[i+1]))
			 {
			  number=AnsiString(text.c_str()[i])+AnsiString(text.c_str()[i+1]);//ShowMessage(number);
			  if(matrix->IndexOf(number)>=0)
			  {
			   if(matrix->IndexOf(number)<QuantLetters)text_chars+=AnsiString(alphabet.c_str()[matrix->IndexOf(number)]);//Нижній регістр
			   else
				{if(number==matrix->Strings[matrix->Count-1])text_chars+=AnsiString(" ");//Пробел
				 else text_chars+=AnsiString(alphabet.UpperCase().c_str()[matrix->IndexOf(number)-QuantLetters]);//Верхній регістр
				}
			   //text_chars+=AnsiString(alphabet.c_str()[matrix->IndexOf(number)]);//Оставить это для "без регистра"
			   i++;
			  }
			  else text_chars+=AnsiString(text.c_str()[i]);//Утворене число немає у матриці
			 }
			else text_chars+=AnsiString(text.c_str()[i]);//Останній елемент
		   }
		   else text_chars+=AnsiString(text.c_str()[i]);//Якщо не цифра
		  }
		  text=text_chars;
		  //Дешифр за існуючим ключем
		  for(int i=0;i<text.Length();i++)
		   if(alphabet.Pos(text.LowerCase().c_str()[i]))
		   {
			 index=alphabet.Pos(text.LowerCase().c_str()[i]);
			 pos=index-shift;
			 if(pos>QuantLetters)while(pos>QuantLetters)pos-=QuantLetters;
			 else if(pos<=0)while(pos<=0)pos=QuantLetters-abs(pos);
			 if(text.c_str()[i]==text.UpperCase().c_str()[i])
			   text.c_str()[i]=alphabet.UpperCase().c_str()[pos-1];
			 else text.c_str()[i]=alphabet.c_str()[pos-1];
		   }
		  Memo2->Text=text;
	  }
	  if(ComboBox1->ItemIndex==0)//Цезаря
	  {
		  int max=-1,pos_max,pos_letter,letter_table;
		  AnsiString sign;//Знак: 1-"+" 0-"-"
		  for(int i=0;i<text.Length();i++)
		   if(alphabet.Pos(text.LowerCase().c_str()[i]))
		   {
			 index=alphabet.Pos(text.LowerCase().c_str()[i]);
			 frequencies[index-1]++;
			 if(frequencies[index-1]>max)
			   {max=frequencies[index-1];pos_max=index;}
		   }
		  letter_table=0;
		  for(int i=0;i<QuantLetters;i++)
		  {
			pos_letter=alphabet.Pos(freqtable.c_str()[letter_table]);
			shift=abs(pos_max-pos_letter);//abs - Якщо позиція букви з макс.частотою знаходиться лівіше букви з таблиці
			if(pos_max-pos_letter>0)sign="-";//-
			else sign="+";//+
			//Дешифрування тексту
			text=Memo1->Text;
			for(int i=0;i<text.Length();i++)
			 if(alphabet.Pos(text.LowerCase().c_str()[i]))
			  {
			   index=alphabet.Pos(text.LowerCase().c_str()[i]);
			   if(sign=="+")pos=index+shift;
			   if(sign=="-")pos=index-shift;
			   if(pos>QuantLetters)pos-=QuantLetters;
			   else if(pos<=0)pos=QuantLetters-abs(pos);
			   if(text.c_str()[i]==text.UpperCase().c_str()[i])
				  text.c_str()[i]=alphabet.UpperCase().c_str()[pos-1];
			   else text.c_str()[i]=alphabet.c_str()[pos-1];
			  }
			Memo2->Text=text;
			//---
			count=0;list->Clear();
			list->StrictDelimiter=true;
			list->Delimiter=' ';
			list->DelimitedText = text;
			for(int i=0;i<list->Count;i++)
			  if(voc->IndexOf(list->Strings[i].LowerCase())>=0)
				 count++;
			//ShowMessage("Зміщення: "+AnsiString(sign)+AnsiString(shift)+AnsiString(". Співпадіння зі словником: ")+AnsiString(FormatFloat("0.00",float(count)/float(list->Count)*100))+AnsiString("%(")+
			//				AnsiString(count)+AnsiString("-")+AnsiString(list->Count)+AnsiString(")"));
			if(Action->Tag==0)
			{
			 if(float(count)/float(list->Count)>=0.25)
			  {ShowMessage("Зміщення: "+AnsiString(sign)+AnsiString(shift)+AnsiString(". Співпадіння зі словником: ")+AnsiString(FormatFloat("0.00",float(count)/float(list->Count)*100))+AnsiString("%(")+
						   AnsiString(count)+AnsiString("-")+AnsiString(list->Count)+AnsiString(")"));
			   break;}
			 else
			   letter_table++;
			 if(i==QuantLetters-1)
			  if(MessageDlg("Пошук у словнику не дав результатів!Перейти у ручний режим?",mtConfirmation,TMsgDlgButtons()<<mbYes<<mbNo,0)==mrYes)
				{letter_table=0;i=-1;Action->Tag=1;}//ручний режим
			}
			else
			if(Action->Tag==1)
			{
			 if(MessageDlg("Зміщення: "+AnsiString(sign)+AnsiString(shift)+AnsiString(". Отриманий текст зрозумілий?"),mtConfirmation,TMsgDlgButtons()<<mbYes<<mbNo,0)==mrYes)
			   break;
			 else
			   letter_table++;
			}
		  }
	  }
	  if(ComboBox1->ItemIndex==2)//Афінна система підстановок Цезаря
	  {
			if(ListBox1->Items->Count==0){ShowMessage("Завантажте ключі до шифру(a,b)!");return;}
			matrix->Assign(ListBox1->Items);
			int a=matrix->Strings[0].ToInt(),b=matrix->Strings[1].ToInt();
			for(int i=0;i<text.Length();i++)
			 if(alphabet.Pos(text.LowerCase().c_str()[i]))
			  {
			   index=alphabet.Pos(text.LowerCase().c_str()[i]);
			   int exp=0;
			   while((exp*QuantLetters+index-1-b)%a!=0)exp++;//t=(n*26+E-b)/a
			   shift=(exp*QuantLetters+index-1-b)/a;
			   if(shift<0)while(shift<0)shift=QuantLetters-abs(shift);
			   if(text.c_str()[i]==text.UpperCase().c_str()[i])
				  text.c_str()[i]=alphabet.UpperCase().c_str()[shift];
			   else text.c_str()[i]=alphabet.c_str()[shift];
			  }
			Memo2->Text=text;
	  }
	  if(ComboBox1->ItemIndex==3)//Віженера
	  {
			if(Edit1->Text.Length()==0){ShowMessage("Ключ не введений!");return;}
			pos=0;
			for(int i=0;i<text.Length();i++)
			 if(alphabet.Pos(text.LowerCase().c_str()[i]))
			  {
			   AnsiString row;
			   int key_index=alphabet.Pos(Edit1->Text.LowerCase().c_str()[pos]);
			   for(int j=1;j<Form2->StringGrid1->ColCount;j++)row=row+AnsiString(Form2->StringGrid1->Cells[j][key_index].LowerCase());
			   int char_index=row.Pos(text.LowerCase().c_str()[i]);
			   AnsiString letter=Form2->StringGrid1->Cells[char_index][0];
			   text.c_str()[i]=letter.LowerCase().c_str()[0];
			   pos++;
			   if(pos==Edit1->Text.Length())pos=0;
			  }
			Memo2->Text=text;
	  }
	  if(ComboBox1->ItemIndex==4)//Модернізований код Цезаря
	  {
			for(int i=0;i<text.Length();i++)
			 if(crypto_key.Pos(text.LowerCase().c_str()[i]))
			  {
				  text.c_str()[i]=alphabet.c_str()[crypto_key.Pos(text.LowerCase().c_str()[i])-1];
			  }
			Memo2->Text=text;
	  }
	  if(ComboBox1->ItemIndex==5)//Полібія
	  {
			int n;
			if(SpeedButton1->Down||SpeedButton2->Down){alphabet=alphabet+".!?";n=6;QuantLetters=36;}
			else {alphabet="abcdefghiklmnopqrstuvwxyz";n=5;QuantLetters=25;}//без j
			for(int i=0;i<text.Length();i++)
			if(alphabet.Pos(text.LowerCase().c_str()[i]))
			{
				index=alphabet.Pos(text.LowerCase().c_str()[i])+n;
				if(index>QuantLetters)index-=QuantLetters;
				text.c_str()[i]=alphabet.c_str()[index-1];
			}
			Memo2->Text=text;
	  }
	  if(ComboBox1->ItemIndex==6)//Матричний шифр
	  {
			AnsiString word=crypto_key,text_decrypted;
			int n=word.Length(),m; //n-ключ,m-блоків текста
			if(text.Length()%n==0)m=text.Length()/n;
			else m=text.Length()/n+1;
			pos=0;
			for(int i=m;i>0;i--)
			{
			 for(int j=0;j<n;j++)
			 {
				  int shiftindex=n-StrToInt(word.c_str()[j])-1;//рядок
				  index=text.Length()-i-shiftindex*i-pos*shiftindex;//i-смещение вправо,shiftindex*i-смещение вверх,pos*shiftindex-зсув
				  if(text.Length()%n!=0&&shiftindex!=0)index++;
				  if(index>=0&&index<text.Length())
					 text_decrypted=text_decrypted+AnsiString(text.c_str()[index]);//оставить это
			 }
			 pos++;
			}
			Memo2->Text=text_decrypted;
	  }
	  if(ComboBox1->ItemIndex==7)//Потокове шифрування з гаммою
	  {
			AnsiString new_text;int k=0;
			alphabet=alphabet+" ";QuantLetters++;
			//QuantLetters=32;alphabet="абвгдежзийклмнопрсту хцчшщъыьэюя";//удалить
			for(int i=0;i<text.Length();i++)
			{
			 if(alphabet.Pos(text.LowerCase().c_str()[i]))//ti=C(si+(32-Ki))mod n
			 {
				int pos=alphabet.Pos(text.LowerCase().c_str()[i])-1;
				index=(pos+QuantLetters-matrix->Strings[k].ToInt())%QuantLetters;
				new_text+=alphabet.c_str()[index];
				k++;
			 }
			 else new_text+=text.c_str()[i];
			}
			Memo2->Text=new_text;
      }
	  if(MessageDlg("Зберегти отриманий текст?",mtConfirmation,TMsgDlgButtons()<<mbYes<<mbNo,0)==mrYes)
		 PSaveFileClick(Sender);
  }
  delete list,voc;list=NULL;voc=NULL;
}
//---------------------------------------------------------------------------
/*
			   if((index-1-b)%a==0)shift=(index-1-b)/a; //t=(E-b)/a
			   else                                     //t=(26*exp+E-b)/a
			   {
				int exp=1;
				while((exp*QuantLetters+index-1-b)%a!=0)exp++;
				shift=(exp*QuantLetters+index-1-b)/a;
			   }
*/
/*//Полибия через char
		  char **array=new char*[n];
		  for (int i=0; i<n;i++)
			 array[i]=new char[n];
		  pos=0;//ShowMessage(AnsiString(array[i][j]));
		  for(int i=0;i<5;i++)
			for(int j=0;j<5;j++)
			  {array[i][j]=alphabet.c_str()[pos];pos++;
			   StringGrid1->Cells[j][i]=AnsiString(array[i][j]);}
*/
//---------------------------------------------------------------------------
/*
		  for(int i=0;i<text.Length();i++)//Y_t=(Y_(t-1)+Y_(t-3))mod n
		  {
		   if(alphabet.Pos(text.LowerCase().c_str()[i])&&k>=3)
			  matrix->Add((matrix->Strings[k-1].ToInt()+matrix->Strings[k-3].ToInt())%QuantLetters);
		   k++;
		  }
		  matrix->Add((matrix->Strings[k-1].ToInt()+matrix->Strings[k-3].ToInt())%QuantLetters);
*/
