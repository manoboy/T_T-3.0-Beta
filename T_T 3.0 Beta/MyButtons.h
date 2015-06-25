#pragma once
#include "Globals.h"
#include "Drawings.h"

class CTextLabel{
public:
	char *Text;
	RECT Position;
	RECT TextPosition;

	float Width;
	float Height;

	Color FillColor;
	Color BorderColor;
	Color TextColor;
	
	CTextLabel(){};
	CTextLabel(const char *Text, RECT Position, Color FillColor, Color BorderColor, Color TextColor);
	
	void Draw();
};



class CButton{
public:	
	RECT Position;
	RECT TextPosition;
	char* Text;

	Color BorderColor;
	Color PressedColor;
	Color FillColor;
	Color TextColor;
	bool *Pressed;
	clock_t PressdedTime;
	clock_t UnpressTime;

	float Width;
	float Height;

	CButton(){};

	CButton(char* Text, bool *Variable, RECT Position, Color FillColor, Color BorderColor, Color PressedColor, Color TextColor);
	void Draw();
};


class CCheckBox{
public:	
	RECT Position;
	RECT CheckPosition;
	RECT TextPosition;
	char* Text;

	Color BorderColor;
	Color FillColor;
	Color CheckColor;
	Color TextColor;
	clock_t PressdedTime;
	bool *Checked;

	float Width;
	float Height;

	float CheckWidth;
	float CheckHeight;

	CCheckBox(){};
	CCheckBox(char* Text, bool *Variable, RECT Position, Color FillColor, Color BorderColor, Color CheckColor, Color TextColor);

	void Draw();
};







template <class ValueType> 
class CChangeValueBox
{
public:
	RECT Position;
	RECT AddPosition;
	RECT SubPosition;
	RECT TextPosition;
	char* Text;

	Color BorderColor;
	Color FillColor;
	Color AddColor;
	Color SubColor;
	Color TextColor;
	clock_t PressdedTime = 0;

	ValueType *Value;
	ValueType MaxValue;
	ValueType MinValue;
	ValueType ChangeValue;

	float Width;
	float Height;
	float AddWidth;
	float AddHeight;
	float SubWidth;
	float SubHeight;


	CChangeValueBox(){};
	CChangeValueBox(char *Text, ValueType *Value, ValueType ChangeValue, ValueType MaxValue, ValueType MinValue, RECT Position, Color FillColor, Color BorderColor, Color AddColor, Color SubColor, Color TextColor);

	void Draw();
};

template <class ValueType> CChangeValueBox<ValueType>::CChangeValueBox(char *Text, ValueType *Value, ValueType ChangeValue, ValueType MaxValue, ValueType MinValue, RECT Position, Color FillColor, Color BorderColor, Color AddColor, Color SubColor, Color TextColor)
{

	if (Value != nullptr)
		this->Value = Value;
	else
		this->Value = new ValueType;

	this->ChangeValue = ChangeValue;
	this->MaxValue = MaxValue;
	this->MinValue = MinValue;

	if (!Text)
	{
		this->Text = new char;
		*(this->Text) = '\n';
	}
	else
	{
		int Length = strlen(Text);
		this->Text = new char[Length + 1];
		strcpy(this->Text, Text);
		this->Text[Length] = 0;
	}

	this->Position = Position;
	this->Width = Position.right - Position.left;
	this->Height = Position.bottom - Position.top;

	this->TextPosition = RECT{ Position.left + 3, Position.top + Height / 2 + CMyWindow::FontHeight / 2 + 3, Position.right, Position.bottom };


	this->AddWidth = (this->Position.bottom - 5) - (this->Position.top + 5);
	this->AddHeight = (this->Position.bottom - 5) - (this->Position.top + 5);
	this->SubWidth = (this->Position.bottom - 5) - (this->Position.top + 5);
	this->SubHeight = (this->Position.bottom - 5) - (this->Position.top + 5);

	this->AddPosition = RECT{ this->Position.right - (AddWidth + 5), this->Position.top + 5, this->Position.right - 5, this->Position.bottom - 5 };
	this->SubPosition = RECT{ this->AddPosition.right - (SubWidth + 12), this->Position.top + 5, this->AddPosition.right - 12, this->Position.bottom - 5 };


	this->FillColor = FillColor;
	this->BorderColor = BorderColor;
	this->AddColor = AddColor;
	this->SubColor = SubColor;
	this->TextColor = TextColor;

	this->PressdedTime = clock();
};


template <class ValueType> void CChangeValueBox<ValueType>::Draw()
{
	Drawings->GuiBox(Position, FillColor, BorderColor);
	Drawings->GuiBox(AddPosition, AddColor, FillColor);
	Drawings->GuiBox(SubPosition, SubColor, FillColor);

	Drawings->Text("+", AddPosition.left + 4, TextPosition.top, FillColor);
	Drawings->Text("-", SubPosition.left + 4, TextPosition.top, FillColor);

	char Buf[124];
	sprintf(Buf, "%s: %.2f", Text, *Value);
	Drawings->Text(Buf, TextPosition.left, TextPosition.top, TextColor);
};







class CChangeValueBoxText
{
public:
	RECT Position;
	RECT AddPosition;
	RECT SubPosition;
	RECT TextPosition;
	char* Text;

	Color BorderColor;
	Color FillColor;
	Color AddColor;
	Color SubColor;
	Color TextColor;
	clock_t PressdedTime = 0;

	int *Value;
	int MaxValue;
	int MinValue;

	float Width;
	float Height;
	float AddWidth;
	float AddHeight;
	float SubWidth;
	float SubHeight;

	char **ValueText;

	CChangeValueBoxText(){};
	CChangeValueBoxText(char *Text, char **ValueText, int *Value, int MaxValue, int MinValue, RECT Position, Color FillColor, Color BorderColor, Color AddColor, Color SubColor, Color TextColor);

	void Draw();

};
