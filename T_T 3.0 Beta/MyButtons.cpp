#include "MyButtons.h"
#include "MyWindow.h"


CTextLabel::CTextLabel(const char *Text, RECT Position, Color FillColor, Color BorderColor, Color TextColor)
{

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

	this->TextPosition = RECT{ Position.left + 3, Position.top + Height/2 + CMyWindow::FontHeight/2 + 3, Position.right, Position.bottom };
	
	this->FillColor = FillColor;
	this->BorderColor = BorderColor;
	this->TextColor = TextColor;
}

void CTextLabel::Draw()
{
	Drawings->GuiBox(Position, FillColor, BorderColor);
	Drawings->Text(Text, TextPosition.left, TextPosition.top, TextColor);
}










CButton::CButton(char* Text, bool *Variable, RECT Position, Color FillColor, Color BorderColor, Color PressedColor, Color TextColor)
{

	if (Variable != nullptr)
		Pressed = Variable;
	else
		Pressed = new bool;

	this->Position = Position;

	this->Width = Position.right - Position.left;
	this->Height = Position.bottom - Position.top;

	this->TextPosition = RECT{ Position.left + 3, Position.top + Height / 2 + CMyWindow::FontHeight / 2 + 3, Position.right, Position.bottom };

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

	this->BorderColor = BorderColor;
	this->FillColor = FillColor;
	this->PressedColor = PressedColor;
	this->TextColor = TextColor;

	this->PressdedTime = clock();
}

void CButton::Draw()
{
	if (*Pressed == true)
	{
		Drawings->GuiBox(Position, PressedColor, BorderColor);
	}
	else
	{
		Drawings->GuiBox(Position, FillColor, BorderColor);
	}
	Drawings->Text(Text, TextPosition.left, TextPosition.top, TextColor);
}








CCheckBox::CCheckBox(char* Text, bool *Variable, RECT Position, Color FillColor, Color BorderColor, Color CheckColor, Color TextColor)
{

	if (Variable != nullptr)
		this->Checked = Variable;
	else
		this->Checked = new bool;

	this->Position = Position;
	this->CheckPosition = RECT{ Position.right - (((Position.bottom - 5) - (Position.top + 5) + 5)), Position.top + 5, Position.right - 5, Position.bottom - 5 };
	this->Width = Position.right - Position.left;
	this->Height = Position.bottom - Position.top;

	this->TextPosition = RECT{ Position.left + 3, Position.top + Height / 2 + CMyWindow::FontHeight / 2 + 3, Position.right, Position.bottom };


	this->CheckWidth = this->CheckPosition.right - this->CheckPosition.left;
	this->CheckHeight = this->CheckPosition.bottom - this->CheckPosition.top;

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

	this->BorderColor = BorderColor;
	this->FillColor = FillColor;
	this->CheckColor = CheckColor;
	this->TextColor = TextColor;

	this->PressdedTime = clock();

}

void CCheckBox::Draw()
{

	Drawings->GuiBox(Position, FillColor, BorderColor);
	
	Drawings->GuiBox(CheckPosition, CheckColor, BorderColor);

	if (*Checked == true)
	{
		Drawings->Text("x", CheckPosition.left + 4, TextPosition.top, FillColor);
	}

	Drawings->Text(Text, TextPosition.left, TextPosition.top, TextColor);
}






char *Trash[5] = { "a", "b", "c", "d", "e" };
CChangeValueBoxText::CChangeValueBoxText(char *Text, char **ValueText, int *Value, int MaxValue, int MinValue, RECT Position, Color FillColor, Color BorderColor, Color AddColor, Color SubColor, Color TextColor)
{

	if (ValueText)
	{
		this->ValueText = ValueText;
		this->Value = Value;
		this->MaxValue = MaxValue;
		this->MinValue = MinValue;
	}
	else
	{
		this->ValueText = Trash;
		this->Value = 0;
		this->MaxValue = 5;
		this->MinValue = 0;
	}


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


void CChangeValueBoxText::Draw()
{
	Drawings->GuiBox(Position, FillColor, BorderColor);
	Drawings->GuiBox(AddPosition, AddColor, FillColor);
	Drawings->GuiBox(SubPosition, SubColor, FillColor);

	Drawings->Text(">", AddPosition.left + 4, TextPosition.top, FillColor);
	Drawings->Text("<", SubPosition.left + 4, TextPosition.top, FillColor);

	char Buf[124];
	sprintf(Buf, "%s: %s", Text, ValueText[*Value]);
	Drawings->Text(Buf, TextPosition.left, TextPosition.top, TextColor);
}