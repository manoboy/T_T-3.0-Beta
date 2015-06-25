#include "MyMenu.h"
#include "Visuals.h"
#include "AimBot.h"
#include "RecoilControl.h"
#include "TriggerBot.h"
#include"Engine.h"
#include "Radar.h"
/*

	TextLables

*/


template <> void CChangeValueBox<int>::Draw()
{
	Drawings->GuiBox(Position, FillColor, BorderColor);
	Drawings->GuiBox(AddPosition, AddColor, FillColor);
	Drawings->GuiBox(SubPosition, SubColor, FillColor);

	Drawings->Text("+", AddPosition.left + 4, TextPosition.top, FillColor);
	Drawings->Text("-", SubPosition.left + 4, TextPosition.top, FillColor);

	char Buf[124];
	sprintf(Buf, "%s: %i", Text, *Value);
	Drawings->Text(Buf, TextPosition.left, TextPosition.top, TextColor);
};


void CMenuCore::InitTextLables(int amount)
{
	MaxTextLabels = amount;
	if (amount == 0)
		return;

	TextLabel = new CTextLabel[amount];
}

void CMenuCore::AddTextLabel(char* Text, RECT Position, Color FillColor, Color BorderColor, Color TextColor)
{
	if (TextLabels == MaxTextLabels)
		return;

	TextLabel[TextLabels] = CTextLabel(Text, Position, FillColor, BorderColor, TextColor);
	LastTextLabelPos = Position;
	TextLabels++;
}

void CMenuCore::AddTextLabelToList(char* Text, Color FillColor, Color BorderColor, Color TextColor)
{
	if (TextLabels == MaxTextLabels)
		return;

	RECT Position;
	if (TextLabels == 0)
	{
		Position = TextLabelListFirstPosition;
	}
	else
	{
		Position.left = LastTextLabelPos.left + TextLabelListNextPosition.left;
		Position.top = LastTextLabelPos.bottom + TextLabelListNextPosition.top;
		Position.right = LastTextLabelPos.right + TextLabelListNextPosition.right;
		Position.bottom = LastTextLabelPos.bottom + TextLabelListNextPosition.top + TextLabelListNextPosition.bottom;
	}
	TextLabel[TextLabels] = CTextLabel(Text, Position, FillColor, BorderColor, TextColor);
	LastTextLabelPos = Position;
	TextLabels++;

}


/*

Buttons

*/


void CMenuCore::InitButtons(int amount)
{
	MaxButtons = amount;
	if (amount == 0)
		return;

	Button = new CButton[amount];
}

void CMenuCore::AddButton(char* Text, bool *Variable, RECT Position, Color FillColor, Color BorderColor, Color PressedColor, Color TextColor)
{
	if (Buttons == MaxButtons)
		return;
	Button[Buttons] = CButton(Text, Variable, Position, FillColor, BorderColor, PressedColor, TextColor);
	LastButtonPos = Position;
	Buttons++;
}

void CMenuCore::AddButtonToList(char* Text, bool *Variable, Color FillColor, Color BorderColor, Color PressedColor, Color TextColor)
{
	if (Buttons == MaxButtons)
		return;

	RECT Position;
	if (CheckBoxes == 0)
	{
		Position = ButtonListFirstPosition;
	}
	else
	{
		Position.left = LastButtonPos.left + ButtonListNextPosition.left;
		Position.top = LastButtonPos.bottom + ButtonListNextPosition.top;
		Position.right = LastButtonPos.right + ButtonListNextPosition.right;
		Position.bottom = LastButtonPos.bottom + ButtonListNextPosition.top + ButtonListNextPosition.bottom;
	}
	Button[Buttons] = CButton(Text, Variable, Position, FillColor, BorderColor, PressedColor, TextColor);
	LastButtonPos = Position;
	Buttons++;
}

void CMenuCore::UpdateButtons()
{
	for (int i = 0; i < Buttons; i++)
	{
		if (*Button[i].Pressed && clock() > Button[i].PressdedTime + 50)
			*Button[i].Pressed = false;

		if (CMyWindow::MousePos.x >= Button[i].Position.left &&  CMyWindow::MousePos.x <= Button[i].Position.right)
		{
			if (CMyWindow::MousePos.y >= Button[i].Position.top && CMyWindow::MousePos.y <= Button[i].Position.bottom)
			{
				if (GetAsyncKeyState(VK_LBUTTON) && *Button[i].Pressed == false)
				{
					if (*Button[i].Pressed)
						*Button[i].Pressed = false;
					else
						*Button[i].Pressed = true;

					Button[i].PressdedTime = clock();
				}
			}
		}
	}
}



/*

CheckBoxes

*/


void CMenuCore::InitCheckBoxes(int amount)
{
	MaxCheckBoxes = amount;
	if (amount == 0)
		return;

	CheckBox = new CCheckBox[amount];
}

void CMenuCore::AddCheckBox(char* Text, bool *Variable, RECT Position, Color BorderColor, Color FillColor, Color CheckColor, Color TextColor)
{
	if (CheckBoxes == MaxCheckBoxes)
		return;

	CheckBox[CheckBoxes] = CCheckBox(Text, Variable, Position, BorderColor, FillColor, CheckColor, TextColor);
	LastCheckBoxPos = Position;
	CheckBoxes++;
}

void CMenuCore::AddCheckBoxToList(char* Text, bool *Variable, Color BorderColor, Color FillColor, Color CheckColor, Color TextColor)
{
	if (CheckBoxes == MaxCheckBoxes)
		return;

	RECT Position;
	if (CheckBoxes == 0)
	{
		Position = CheckBoxListFirstPosition;
	}
	else
	{
		Position.left = LastCheckBoxPos.left + CheckBoxListNextPosition.left;
		Position.top = LastCheckBoxPos.bottom + CheckBoxListNextPosition.top;
		Position.right = LastCheckBoxPos.right + CheckBoxListNextPosition.right;
		Position.bottom = LastCheckBoxPos.bottom + CheckBoxListNextPosition.top + CheckBoxListNextPosition.bottom;
	}
	CheckBox[CheckBoxes] = CCheckBox(Text, Variable, Position, BorderColor, FillColor, CheckColor, TextColor);
	LastCheckBoxPos = Position;
	CheckBoxes++;
}

void CMenuCore::UpdateCheckBoxes()
{
	for (int i = 0; i < CheckBoxes; i++)
	{
		if (CMyWindow::MousePos.x >= CheckBox[i].CheckPosition.left &&  CMyWindow::MousePos.x <= CheckBox[i].CheckPosition.right)
		{
			if (CMyWindow::MousePos.y >= CheckBox[i].CheckPosition.top && CMyWindow::MousePos.y <= CheckBox[i].CheckPosition.bottom)
			{
				if (GetAsyncKeyState(VK_LBUTTON) && clock() > CheckBox[i].PressdedTime + 150)
				{
					if (*CheckBox[i].Checked)
						*CheckBox[i].Checked = false;
					else
						*CheckBox[i].Checked = true;
					CheckBox[i].PressdedTime = clock();
				}
			}
		}
	}
}


/*

ChangeValueBoxes

*/

void CMenuCore::InitChangeValueBoxesI(int amount)
{
	MaxChangeValueBoxesI = amount;
	if (amount == 0)
		return;

	ChangeValueBoxI = new CChangeValueBox<int>[amount];
}

void CMenuCore::InitChangeValueBoxesF(int amount)
{
	MaxChangeValueBoxesF = amount;
	if (amount == 0)
		return;

	ChangeValueBoxF = new CChangeValueBox<float>[amount];
}

void CMenuCore::InitChangeValueBoxesT(int amount)
{
	MaxChangeValueBoxesT = amount;
	if (amount == 0)
		return;

	ChangeValueBoxT = new CChangeValueBoxText[amount];
}


void CMenuCore::AddChangeValueBox(char *Text, int *Value, int ChangeValue, int MaxValue, int MinValue, RECT Position, Color FillColor, Color BorderColor, Color AddColor, Color SubColor, Color TextColor)
{
	if (ChangeValueBoxesI == MaxChangeValueBoxesI)
		return;

	ChangeValueBoxI[ChangeValueBoxesI] = CChangeValueBox<int>(Text, Value, ChangeValue, MaxValue, MinValue, Position, FillColor, BorderColor, AddColor, SubColor, TextColor);
	ChangeValueBoxesI++;
	LastChangeValueBoxPos = Position;
}

void CMenuCore::AddChangeValueBox(char *Text, float *Value, float ChangeValue, float MaxValue, float MinValue, RECT Position, Color FillColor, Color BorderColor, Color AddColor, Color SubColor, Color TextColor)
{
	if (ChangeValueBoxesF == MaxChangeValueBoxesF)
		return;

	ChangeValueBoxF[ChangeValueBoxesF] = CChangeValueBox<float>(Text, Value, ChangeValue, MaxValue, MinValue, Position, FillColor, BorderColor, AddColor, SubColor, TextColor);
	ChangeValueBoxesF++;
	LastChangeValueBoxPos = Position;
}

void CMenuCore::AddChangeValueBox(char *Text, char **ValueText, int *Value, int MaxValue, int MinValue, RECT Position, Color FillColor, Color BorderColor, Color AddColor, Color SubColor, Color TextColor)
{
	if (ChangeValueBoxesT == MaxChangeValueBoxesT)
		return;

	ChangeValueBoxT[ChangeValueBoxesT] = CChangeValueBoxText(Text, ValueText, Value, MaxValue, MinValue, Position, FillColor, BorderColor, AddColor, SubColor, TextColor);
	ChangeValueBoxesT++;
	LastChangeValueBoxPos = Position;
}

void CMenuCore::AddChangeValueBoxToList(char *Text, int *Value, int ChangeValue, int MaxValue, int MinValue, Color FillColor, Color BorderColor, Color AddColor, Color SubColor, Color TextColor)
{
	if (ChangeValueBoxesI == MaxChangeValueBoxesI)
		return;

	RECT Position;
	if (ChangeValueBoxesI == 0 && ChangeValueBoxesF == 0 && ChangeValueBoxesT == 0)
	{
		Position = ChangeValueBoxListFirstPosition;
	}
	else
	{
		Position.left = LastChangeValueBoxPos.left + ChangeValueBoxListNextPosition.left;
		Position.top = LastChangeValueBoxPos.bottom + ChangeValueBoxListNextPosition.top;
		Position.right = LastChangeValueBoxPos.right + ChangeValueBoxListNextPosition.right;
		Position.bottom = LastChangeValueBoxPos.bottom + ChangeValueBoxListNextPosition.top + ChangeValueBoxListNextPosition.bottom;
	}
	ChangeValueBoxI[ChangeValueBoxesI] = CChangeValueBox<int>(Text, Value, ChangeValue, MaxValue, MinValue, Position, FillColor, BorderColor, AddColor, SubColor, TextColor);
	ChangeValueBoxesI++;
	LastChangeValueBoxPos = Position;
}


void CMenuCore::AddChangeValueBoxToList(char *Text, float *Value, float ChangeValue, float MaxValue, float MinValue, Color FillColor, Color BorderColor, Color AddColor, Color SubColor, Color TextColor)
{
	if (ChangeValueBoxesF == MaxChangeValueBoxesF)
		return;

	RECT Position;
	if (ChangeValueBoxesI == 0 && ChangeValueBoxesF == 0 && ChangeValueBoxesT == 0)
	{
		Position = ChangeValueBoxListFirstPosition;
	}
	else
	{
		Position.left = LastChangeValueBoxPos.left + ChangeValueBoxListNextPosition.left;
		Position.top = LastChangeValueBoxPos.bottom + ChangeValueBoxListNextPosition.top;
		Position.right = LastChangeValueBoxPos.right + ChangeValueBoxListNextPosition.right;
		Position.bottom = LastChangeValueBoxPos.bottom + ChangeValueBoxListNextPosition.top + ChangeValueBoxListNextPosition.bottom;
	}
	ChangeValueBoxF[ChangeValueBoxesF] = CChangeValueBox<float>(Text, Value, ChangeValue, MaxValue, MinValue, Position, FillColor, BorderColor, AddColor, SubColor, TextColor);
	ChangeValueBoxesF++;
	LastChangeValueBoxPos = Position;
}


void CMenuCore::AddChangeValueBoxToList(char *Text, char **ValueText, int *Value, int MaxValue, int MinValue, Color FillColor, Color BorderColor, Color AddColor, Color SubColor, Color TextColor)
{
	RECT Position;
	if (ChangeValueBoxesI == 0 && ChangeValueBoxesF == 0 && ChangeValueBoxesT == 0)
	{
		Position = ChangeValueBoxListFirstPosition;
	}
	else
	{
		Position.left = LastChangeValueBoxPos.left + ChangeValueBoxListNextPosition.left;
		Position.top = LastChangeValueBoxPos.bottom + ChangeValueBoxListNextPosition.top;
		Position.right = LastChangeValueBoxPos.right + ChangeValueBoxListNextPosition.right;
		Position.bottom = LastChangeValueBoxPos.bottom + ChangeValueBoxListNextPosition.top + ChangeValueBoxListNextPosition.bottom;
	}
	ChangeValueBoxT[ChangeValueBoxesT] = CChangeValueBoxText(Text, ValueText, Value, MaxValue, MinValue, Position, FillColor, BorderColor, AddColor, SubColor, TextColor);
	ChangeValueBoxesT++;
	LastChangeValueBoxPos = Position;
}

void CMenuCore::UpdateChangeValueBoxes()
{
	for (int i = 0; i < ChangeValueBoxesI; i++)
	{
		if (CMyWindow::MousePos.x >= ChangeValueBoxI[i].AddPosition.left &&  CMyWindow::MousePos.x <= ChangeValueBoxI[i].AddPosition.right)
		{

			if (CMyWindow::MousePos.y >= ChangeValueBoxI[i].AddPosition.top && CMyWindow::MousePos.y <= ChangeValueBoxI[i].AddPosition.bottom)
			{
				if (GetAsyncKeyState(VK_LBUTTON) && clock() > ChangeValueBoxI[i].PressdedTime + 50)
				{
					if (*ChangeValueBoxI[i].Value + ChangeValueBoxI[i].ChangeValue <= ChangeValueBoxI[i].MaxValue)
						*ChangeValueBoxI[i].Value = *ChangeValueBoxI[i].Value + ChangeValueBoxI[i].ChangeValue;

					else
						*ChangeValueBoxI[i].Value = ChangeValueBoxI[i].MaxValue;

					ChangeValueBoxI[i].PressdedTime = clock();
				}
			}
		}
		else if (CMyWindow::MousePos.x >= ChangeValueBoxI[i].SubPosition.left &&  CMyWindow::MousePos.x <= ChangeValueBoxI[i].SubPosition.right)
		{
			if (CMyWindow::MousePos.y >= ChangeValueBoxI[i].SubPosition.top && CMyWindow::MousePos.y <= ChangeValueBoxI[i].SubPosition.bottom)
			{
				if (GetAsyncKeyState(VK_LBUTTON) && clock() > ChangeValueBoxI[i].PressdedTime + 50)
				{
					if (*ChangeValueBoxI[i].Value - ChangeValueBoxI[i].ChangeValue >= ChangeValueBoxI[i].MinValue)
						*ChangeValueBoxI[i].Value = *ChangeValueBoxI[i].Value - ChangeValueBoxI[i].ChangeValue;
					else
						*ChangeValueBoxI[i].Value = ChangeValueBoxI[i].MinValue;
					ChangeValueBoxI[i].PressdedTime = clock();
				}
			}
		}
	}

	for (int i = 0; i < ChangeValueBoxesF; i++)
	{
		if (CMyWindow::MousePos.x >= ChangeValueBoxF[i].AddPosition.left &&  CMyWindow::MousePos.x <= ChangeValueBoxF[i].AddPosition.right)
		{

			if (CMyWindow::MousePos.y >= ChangeValueBoxF[i].AddPosition.top && CMyWindow::MousePos.y <= ChangeValueBoxF[i].AddPosition.bottom)
			{
				if (GetAsyncKeyState(VK_LBUTTON) && clock() > ChangeValueBoxF[i].PressdedTime + 50)
				{
					if (*ChangeValueBoxF[i].Value + ChangeValueBoxF[i].ChangeValue <= ChangeValueBoxF[i].MaxValue)
						*ChangeValueBoxF[i].Value += ChangeValueBoxF[i].ChangeValue;
					else
						*ChangeValueBoxF[i].Value = ChangeValueBoxF[i].MaxValue;

					ChangeValueBoxF[i].PressdedTime = clock();
				}
			}
		}
		else if (CMyWindow::MousePos.x >= ChangeValueBoxF[i].SubPosition.left &&  CMyWindow::MousePos.x <= ChangeValueBoxF[i].SubPosition.right)
		{
			if (CMyWindow::MousePos.y >= ChangeValueBoxF[i].SubPosition.top && CMyWindow::MousePos.y <= ChangeValueBoxF[i].SubPosition.bottom)
			{
				if (GetAsyncKeyState(VK_LBUTTON) && clock() > ChangeValueBoxF[i].PressdedTime + 50)
				{
					if (*ChangeValueBoxF[i].Value - ChangeValueBoxF[i].ChangeValue >= ChangeValueBoxF[i].MinValue)
						*ChangeValueBoxF[i].Value -= ChangeValueBoxF[i].ChangeValue;
					else
						*ChangeValueBoxF[i].Value = ChangeValueBoxF[i].MinValue;

					ChangeValueBoxF[i].PressdedTime = clock();
				}
			}
		}
	}


	for (int i = 0; i < ChangeValueBoxesT; i++)
	{
		if (CMyWindow::MousePos.x >= ChangeValueBoxT[i].AddPosition.left &&  CMyWindow::MousePos.x <= ChangeValueBoxT[i].AddPosition.right)
		{

			if (CMyWindow::MousePos.y >= ChangeValueBoxT[i].AddPosition.top && CMyWindow::MousePos.y <= ChangeValueBoxT[i].AddPosition.bottom)
			{
				if (GetAsyncKeyState(VK_LBUTTON) && clock() > ChangeValueBoxT[i].PressdedTime + 100)
				{
					if (*ChangeValueBoxT[i].Value + 1 <= ChangeValueBoxT[i].MaxValue)
						*ChangeValueBoxT[i].Value += 1;
					else
						*ChangeValueBoxT[i].Value = ChangeValueBoxT[i].MaxValue;

					ChangeValueBoxT[i].PressdedTime = clock();
				}
			}
		}
		else if (CMyWindow::MousePos.x >= ChangeValueBoxT[i].SubPosition.left &&  CMyWindow::MousePos.x <= ChangeValueBoxT[i].SubPosition.right)
		{
			if (CMyWindow::MousePos.y >= ChangeValueBoxT[i].SubPosition.top && CMyWindow::MousePos.y <= ChangeValueBoxT[i].SubPosition.bottom)
			{
				if (GetAsyncKeyState(VK_LBUTTON) && clock() > ChangeValueBoxT[i].PressdedTime + 100)
				{
					if (*ChangeValueBoxT[i].Value - 1 >= ChangeValueBoxT[i].MinValue)
						*ChangeValueBoxT[i].Value -= 1;
					else
						*ChangeValueBoxT[i].Value = ChangeValueBoxT[i].MinValue;

					ChangeValueBoxT[i].PressdedTime = clock();
				}
			}
		}
	}

}



/*

SubMenu

*/
void CSubMenu::MenuUpdate()
{
	UpdateButtons();
	UpdateCheckBoxes();
	UpdateChangeValueBoxes();
}

void CSubMenu::Draw()
{
	for (int i = 0; i < TextLabels; i++)
		TextLabel[i].Draw();

	for (int i = 0; i < Buttons; i++)
		Button[i].Draw();

	for (int i = 0; i < CheckBoxes; i++)
		CheckBox[i].Draw();

	for (int i = 0; i < ChangeValueBoxesI; i++)
		ChangeValueBoxI[i].Draw();

	for (int i = 0; i < ChangeValueBoxesF; i++)
		ChangeValueBoxF[i].Draw();

	for (int i = 0; i < ChangeValueBoxesT; i++)
		ChangeValueBoxT[i].Draw();
}

/*
Menu
*/

void CMyMenu::InitSubMenus(int amount)
{
	MaxSubMenus = amount;
	if (amount == 0)
		return;

	SubMenu = new CSubMenu[amount];
}

CSubMenu* CMyMenu::AddSubMenu(char* Name, RECT MenuTitleBarPostion, RECT Position, Color TitleBarColor, Color TitleBarBorderColor, Color MenuColor, Color MenuBorderColor, Color MenuNameColor)
{
	if (SubMenus == MaxSubMenus)
		return nullptr;

	SubMenu[SubMenus].MenuName = new char[strlen(Name) + 1];
	memcpy(SubMenu[SubMenus].MenuName, Name, strlen(Name) + 1);
	SubMenu[SubMenus].MenuName[strlen(Name)] = 0;

	SubMenu[SubMenus].MenuPostion = Position;
	SubMenu[SubMenus].MenuTitleBarPostion = MenuTitleBarPostion;

	LastSubMenuPosition = SubMenu[SubMenus].MenuPostion;
	LastSubMenuTitleBarPosition = SubMenu[SubMenus].MenuTitleBarPostion;

	MenuWidth = SubMenu[SubMenus].MenuPostion.right - SubMenu[SubMenus].MenuPostion.left;
	MenuWidth = SubMenu[SubMenus].MenuPostion.bottom - SubMenu[SubMenus].MenuPostion.top;

	SubMenu[SubMenus].MenuNameColor = MenuNameColor;
	SubMenu[SubMenus].MenuColor = MenuColor;
	SubMenu[SubMenus].MenuBorderColor = MenuBorderColor;
	SubMenu[SubMenus].TitleBarColor = TitleBarColor;
	SubMenu[SubMenus].TitleBarBorderColor = TitleBarBorderColor;

	SubMenus++;

	return &SubMenu[SubMenus - 1];
}

void CMyMenu::UpdateSubMenus()
{
	for (int i = 0; i < SubMenus; i++)
	{
		if (SubMenu[i].MenuActive)
			continue;
		if (CMyWindow::MousePos.x >= SubMenu[i].MenuTitleBarPostion.left &&  CMyWindow::MousePos.x <= SubMenu[i].MenuTitleBarPostion.right)
		{
			if (CMyWindow::MousePos.y >= SubMenu[i].MenuTitleBarPostion.top && CMyWindow::MousePos.y <= SubMenu[i].MenuTitleBarPostion.bottom)
			{
				if (GetAsyncKeyState(VK_LBUTTON) && clock() > SubMenu[i].MenuActiveStateChangeTime + 150)
				{
					if (ActiveSubMenu->MenuActive)
						ActiveSubMenu->MenuActive = false;

					SubMenu[i].MenuActive = true;

					ActiveSubMenu = &SubMenu[i];

					SubMenu[i].MenuActiveStateChangeTime = clock();
				}
			}
		}
	}

}

void CMyMenu::Draw()
{



	Drawings->GuiBox(MenuTitleBarPostion, MenuColor, MenuBorderColor);
	Drawings->Text(MenuName, MenuTitleBarPostion.left + 10, MenuTitleBarPostion.top + 16, MenuNameColor);

	for (int i = 0; i < TextLabels; i++)
		TextLabel[i].Draw();

	for (int i = 0; i < Buttons; i++)
		Button[i].Draw();

	for (int i = 0; i < CheckBoxes; i++)
		CheckBox[i].Draw();

	for (int i = 0; i < ChangeValueBoxesI; i++)
		ChangeValueBoxI[i].Draw();

	for (int i = 0; i < ChangeValueBoxesF; i++)
		ChangeValueBoxF[i].Draw();

	for (int i = 0; i < ChangeValueBoxesT; i++)
		ChangeValueBoxT[i].Draw();

	for (int i = 0; i < SubMenus; i++)
	{
		if (SubMenu[i].MenuActive)
		{
			SubMenu[i].Draw();
			Drawings->GuiBox(SubMenu[i].MenuTitleBarPostion.left, SubMenu[i].MenuTitleBarPostion.top, SubMenu[i].MenuTitleBarPostion.right - SubMenu[i].MenuTitleBarPostion.left, SubMenu[i].MenuTitleBarPostion.bottom - SubMenu[i].MenuTitleBarPostion.top, SubMenu[i].TitleBarColor, SubMenu[i].TitleBarBorderColor);
			Drawings->Text(SubMenu[i].MenuName, SubMenu[i].MenuTitleBarPostion.left + 5, SubMenu[i].MenuTitleBarPostion.top + 20, SubMenu[i].MenuNameColor);
		}
		else
		{
			Drawings->GuiBox(SubMenu[i].MenuTitleBarPostion.left, SubMenu[i].MenuTitleBarPostion.top, SubMenu[i].MenuTitleBarPostion.right - SubMenu[i].MenuTitleBarPostion.left, SubMenu[i].MenuTitleBarPostion.bottom - SubMenu[i].MenuTitleBarPostion.top, SubMenu[i].TitleBarColor, SubMenu[i].TitleBarBorderColor);
			Drawings->Text(SubMenu[i].MenuName, SubMenu[i].MenuTitleBarPostion.left + 5, SubMenu[i].MenuTitleBarPostion.top + 20, SubMenu[i].MenuNameColor);
		}
	}

	GetCursorPos(&CMyWindow::MousePos);
	CMyWindow::MousePos.x -= CMyWindow::WindowRect.left;
	CMyWindow::MousePos.y -= CMyWindow::WindowRect.top;
	Drawings->FilledBox(CMyWindow::MousePos.x - 6, CMyWindow::MousePos.y, 14, 2, MenuCursorColor);
	Drawings->FilledBox(CMyWindow::MousePos.x, CMyWindow::MousePos.y - 6, 2, 14, MenuCursorColor);


}

void CMyMenu::MenuSave()
{
	fstream File;
	File.open(_TempXOR("Config.cfg"), fstream::in | fstream::out | fstream::trunc);
	if (File.is_open())
	{
		for (int i = 0; i < SubMenus; i++)
		{
			for (int j = 0; j < SubMenu[i].CheckBoxes; j++)
			{
				File << *SubMenu[i].CheckBox[j].Checked << endl;
			}
			for (int j = 0; j < SubMenu[i].ChangeValueBoxesI; j++)
			{
				File << *SubMenu[i].ChangeValueBoxI[j].Value << endl;
			}
			for (int j = 0; j < SubMenu[i].ChangeValueBoxesF; j++)
			{
				File << *SubMenu[i].ChangeValueBoxF[j].Value << endl;
			}
			for (int j = 0; j < SubMenu[i].ChangeValueBoxesT; j++)
			{
				File << *SubMenu[i].ChangeValueBoxT[j].Value << endl;
			}
		}
		File << CRadar::x << endl;
		File << CRadar::y << endl;
	}
	File.close();
}
void CMyMenu::MenuLoad()
{
	fstream File;
	File.open(_TempXOR("Config.cfg"), fstream::in | fstream::out);
	if (File.is_open())
	{
		for (int i = 0; i < SubMenus; i++)
		{
			for (int j = 0; j < SubMenu[i].CheckBoxes; j++)
			{
				File >> *SubMenu[i].CheckBox[j].Checked;
			}
			for (int j = 0; j < SubMenu[i].ChangeValueBoxesI; j++)
			{
				File >> *SubMenu[i].ChangeValueBoxI[j].Value;
			}
			for (int j = 0; j < SubMenu[i].ChangeValueBoxesF; j++)
			{
				File >> *SubMenu[i].ChangeValueBoxF[j].Value;
			}
			for (int j = 0; j < SubMenu[i].ChangeValueBoxesT; j++)
			{
				File >> *SubMenu[i].ChangeValueBoxT[j].Value;
			}
		}
		File >> CRadar::x;
		File >> CRadar::y;
	}
	File.close();
}

void CMyMenu::Init()
{

	MenuName = _OnceXOR("Menu - T_T Phoenix 3.0 Beta");
	MenuPostion = RECT{ 10, 10, 700, 200 };
	MenuTitleBarPostion = RECT{ MenuPostion.left, MenuPostion.top, MenuPostion.right, MenuPostion.top + 30 };
	MenuWidth = MenuPostion.right - MenuPostion.left;
	MenuHeight = MenuPostion.bottom - MenuPostion.top;
	MenuNameColor = Color(255, 255, 0, 255);
	MenuBorderColor = Color(255, 255, 255, 255);
	MenuColor = Color(255, 0, 0, 0);
	MenuCursorColor = Color(255, 0, 255, 255);
	MenuActive = false;

	RECT SubMenuCheckBoxPos;

	int CheckBoxWidth = 300;
	int CheckBoxHeight = 22;
	int ChangeValueBoxWidth = 300;
	int ChangeValueBoxHeight = 22;
	
	InitSubMenus(7);

	LastSubMenuTitleBarPosition = RECT{ MenuPostion.left, MenuTitleBarPostion.top, MenuPostion.right, MenuTitleBarPostion.bottom + 15 };

	
	MenuMain = AddSubMenu(_TempXOR("Main"), RECT{ LastSubMenuTitleBarPosition.left, LastSubMenuTitleBarPosition.bottom + 5, LastSubMenuTitleBarPosition.left + 100, LastSubMenuTitleBarPosition.bottom + 40 }, RECT{ LastSubMenuTitleBarPosition.left, LastSubMenuTitleBarPosition.bottom + 5, LastSubMenuTitleBarPosition.right, MenuPostion.bottom }, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuMain->MenuActive = false;
	MenuMain->InitTextLables(4);
	MenuMain->InitButtons(2);
	MenuMain->CheckBoxListFirstPosition = RECT{ SubMenu[0].MenuTitleBarPostion.right + 10, SubMenu[0].MenuTitleBarPostion.top, SubMenu[0].MenuTitleBarPostion.right + CheckBoxWidth, SubMenu[0].MenuTitleBarPostion.top + CheckBoxHeight };
	MenuMain->CheckBoxListNextPosition = RECT{ 0, 5, 0, CheckBoxHeight };
	MenuMain->ChangeValueBoxListFirstPosition = RECT{ SubMenu[0].CheckBoxListFirstPosition.right + 10, SubMenu[0].CheckBoxListFirstPosition.top, SubMenu[0].CheckBoxListFirstPosition.right + ChangeValueBoxWidth, SubMenu[0].CheckBoxListFirstPosition.top + ChangeValueBoxHeight };
	MenuMain->ChangeValueBoxListNextPosition = RECT{ 0, 5, 0, ChangeValueBoxHeight };
	
	MenuMain->AddButton(_TempXOR("Save"), &CEngine::save, RECT{ SubMenu[0].MenuTitleBarPostion.right + 10, SubMenu[0].MenuTitleBarPostion.top, SubMenu[0].MenuTitleBarPostion.right + 300, SubMenu[0].MenuTitleBarPostion.top + 40 }, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color((float)255 / (float)255, (float)125 / (float)255, (float)125 / (float)255, (float)125 / (float)255), Color(255, 255, 255, 255));
	MenuMain->AddButton(_TempXOR("Load"), &CEngine::load, RECT{ SubMenu[0].MenuTitleBarPostion.right + 310, SubMenu[0].MenuTitleBarPostion.top, SubMenu[0].MenuTitleBarPostion.right + 600, SubMenu[0].MenuTitleBarPostion.top + 40 }, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color((float)255 / (float)255, (float)125 / (float)255, (float)125 / (float)255, (float)125 / (float)255), Color(255, 255, 255, 255));



	MenuMain->TextLabelListFirstPosition = RECT{ SubMenu[0].MenuTitleBarPostion.right + 10, SubMenu[0].Button[0].Position.bottom + 10, MenuPostion.right + 10, SubMenu[0].Button[0].Position.bottom + 10 + CheckBoxHeight };
	MenuMain->TextLabelListNextPosition = RECT{ 0, 5, 0, CheckBoxHeight };
	MenuMain->AddTextLabelToList(_TempXOR("Creedits: Koelion"), Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 0, 255, 0));
	MenuMain->AddTextLabelToList(_TempXOR("Its free cheat. If you bought it u were scammed!"), Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 0, 255, 0));
	MenuMain->AddTextLabelToList(_TempXOR("You are not allowed to sell this cheat!"), Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 0, 255, 0));
	MenuMain->AddTextLabelToList(_TempXOR("=3 GL HF"), Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 0, 255, 0));



	MenuVisuals = AddSubMenu(_TempXOR("Visuals"), RECT{ LastSubMenuTitleBarPosition.left, LastSubMenuTitleBarPosition.bottom + 5, LastSubMenuTitleBarPosition.left + 100, LastSubMenuTitleBarPosition.bottom + 40 }, RECT{ LastSubMenuTitleBarPosition.left, LastSubMenuTitleBarPosition.bottom + 5, LastSubMenuTitleBarPosition.right, MenuPostion.bottom }, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuVisuals->MenuActive = false;
	MenuVisuals->InitCheckBoxes(14);
	MenuVisuals->InitChangeValueBoxesF(1);
	MenuVisuals->InitChangeValueBoxesT(1);
	MenuVisuals->CheckBoxListFirstPosition = RECT{ SubMenu[0].MenuTitleBarPostion.right + 10, SubMenu[0].MenuTitleBarPostion.top, SubMenu[0].MenuTitleBarPostion.right + CheckBoxWidth, SubMenu[0].MenuTitleBarPostion.top + CheckBoxHeight };
	MenuVisuals->CheckBoxListNextPosition = RECT{ 0, 5, 0, CheckBoxHeight };
	MenuVisuals->ChangeValueBoxListFirstPosition = RECT{ SubMenu[0].CheckBoxListFirstPosition.right + 10, SubMenu[0].CheckBoxListFirstPosition.top, SubMenu[0].CheckBoxListFirstPosition.right + ChangeValueBoxWidth, SubMenu[0].CheckBoxListFirstPosition.top + ChangeValueBoxHeight };
	MenuVisuals->ChangeValueBoxListNextPosition = RECT{ 0, 5, 0, ChangeValueBoxHeight };
	MenuVisuals->TextLabelListFirstPosition = RECT{ SubMenu[0].MenuTitleBarPostion.right + 10, SubMenu[0].MenuTitleBarPostion.top, MenuPostion.right + 10, SubMenu[0].MenuTitleBarPostion.top + CheckBoxHeight };
	MenuVisuals->TextLabelListNextPosition = RECT{ 0, 5, 0, CheckBoxHeight };

	MenuVisuals->AddCheckBoxToList(_TempXOR("Crosshair"), &Visuals->bDrawCrosshair, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuVisuals->AddCheckBoxToList(_TempXOR("Team mates"), &Visuals->bDrawAlly, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuVisuals->AddCheckBoxToList(_TempXOR("ESP boxes"), &Visuals->bDrawESP, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuVisuals->AddCheckBoxToList(_TempXOR("Draw head"), &Visuals->bDrawHead, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuVisuals->AddCheckBoxToList(_TempXOR("Bones"), &Visuals->bDrawBones, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuVisuals->AddCheckBoxToList(_TempXOR("Snap lines"), &Visuals->bDrawSnapLine, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuVisuals->AddCheckBoxToList(_TempXOR("Health"), &Visuals->bDrawHealth, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuVisuals->AddCheckBoxToList(_TempXOR("Distance"), &Visuals->bDrawDistance, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuVisuals->AddCheckBoxToList(_TempXOR("Weapon"), &Visuals->bDrawWeapon, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuVisuals->AddCheckBoxToList(_TempXOR("Name"), &Visuals->bDrawName, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuVisuals->AddCheckBoxToList(_TempXOR("Bomb position"), &Visuals->bDrawBomb, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuVisuals->AddCheckBoxToList(_TempXOR("Granades position"), &Visuals->bDrawGranades, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuVisuals->AddCheckBoxToList(_TempXOR("Droped weapons position"), &Visuals->bDrawDropedWeapons, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuVisuals->AddCheckBoxToList(_TempXOR("Draw Recoil Crosshair"), &Visuals->bDrawRecoilCrosshair, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));

	MenuVisuals->AddChangeValueBoxToList(_TempXOR("Recoil Crosshair type"), RecoilDrawTypes, &Visuals->RecoilDrawType, 1, 0, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuVisuals->AddChangeValueBoxToList(_TempXOR("Recoil circle resolution"), &Visuals->RecoilDrawResolution, 0.1f, 100.0f, 0.1f, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));



	MenuRadar = AddSubMenu(_TempXOR("Radar"), RECT{ LastSubMenuTitleBarPosition.left, LastSubMenuTitleBarPosition.bottom + 5, LastSubMenuTitleBarPosition.left + 100, LastSubMenuTitleBarPosition.bottom + 40 }, RECT{ LastSubMenuTitleBarPosition.left, LastSubMenuTitleBarPosition.bottom + 5, LastSubMenuTitleBarPosition.right, MenuPostion.bottom }, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuRadar->MenuActive = false;
	MenuRadar->InitCheckBoxes(1);
	MenuRadar->InitChangeValueBoxesF(2);
	MenuRadar->CheckBoxListFirstPosition = RECT{ SubMenu[0].MenuTitleBarPostion.right + 10, SubMenu[0].MenuTitleBarPostion.top, SubMenu[0].MenuTitleBarPostion.right + CheckBoxWidth, SubMenu[0].MenuTitleBarPostion.top + CheckBoxHeight };
	MenuRadar->CheckBoxListNextPosition = RECT{ 0, 5, 0, CheckBoxHeight };
	MenuRadar->ChangeValueBoxListFirstPosition = RECT{ SubMenu[0].CheckBoxListFirstPosition.right + 10, SubMenu[0].CheckBoxListFirstPosition.top, SubMenu[0].CheckBoxListFirstPosition.right + ChangeValueBoxWidth, SubMenu[0].CheckBoxListFirstPosition.top + ChangeValueBoxHeight };
	MenuRadar->ChangeValueBoxListNextPosition = RECT{ 0, 5, 0, ChangeValueBoxHeight };
	MenuRadar->TextLabelListFirstPosition = RECT{ SubMenu[0].MenuTitleBarPostion.right + 10, SubMenu[0].MenuTitleBarPostion.top, MenuPostion.right + 10, SubMenu[0].MenuTitleBarPostion.top + CheckBoxHeight };
	MenuRadar->TextLabelListNextPosition = RECT{ 0, 5, 0, CheckBoxHeight };

	MenuRadar->AddCheckBoxToList(_TempXOR("Active"), &CRadar::Active, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuRadar->AddChangeValueBoxToList(_TempXOR("Size"), &CRadar::Size, 0.5f, 1000.0f, 0.0f, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuRadar->AddChangeValueBoxToList(_TempXOR("Range"), &CRadar::Range, 0.5f, 100.0f, 0.0f, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));



	MenuRCS = AddSubMenu(_TempXOR("Recoil Control"), RECT{ LastSubMenuTitleBarPosition.left, LastSubMenuTitleBarPosition.bottom + 5, LastSubMenuTitleBarPosition.left + 100, LastSubMenuTitleBarPosition.bottom + 40 }, RECT{ LastSubMenuTitleBarPosition.left, LastSubMenuTitleBarPosition.bottom + 5, LastSubMenuTitleBarPosition.right, MenuPostion.bottom }, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuRCS->MenuActive = false;
	MenuRCS->InitCheckBoxes(1);
	MenuRCS->InitChangeValueBoxesI(1);
	MenuRCS->InitChangeValueBoxesF(2);
	MenuRCS->InitChangeValueBoxesT(1);
	MenuRCS->CheckBoxListFirstPosition = RECT{ SubMenu[0].MenuTitleBarPostion.right + 10, SubMenu[0].MenuTitleBarPostion.top, SubMenu[0].MenuTitleBarPostion.right + CheckBoxWidth, SubMenu[0].MenuTitleBarPostion.top + CheckBoxHeight };
	MenuRCS->CheckBoxListNextPosition = RECT{ 0, 5, 0, CheckBoxHeight };
	MenuRCS->ChangeValueBoxListFirstPosition = RECT{ SubMenu[0].CheckBoxListFirstPosition.right + 10, SubMenu[0].CheckBoxListFirstPosition.top, SubMenu[0].CheckBoxListFirstPosition.right + ChangeValueBoxWidth, SubMenu[0].CheckBoxListFirstPosition.top + ChangeValueBoxHeight };
	MenuRCS->ChangeValueBoxListNextPosition = RECT{ 0, 5, 0, ChangeValueBoxHeight };
	MenuRCS->TextLabelListFirstPosition = RECT{ SubMenu[0].MenuTitleBarPostion.right + 10, SubMenu[0].MenuTitleBarPostion.top, MenuPostion.right + 10, SubMenu[0].MenuTitleBarPostion.top + CheckBoxHeight };
	MenuRCS->TextLabelListNextPosition = RECT{ 0, 5, 0, CheckBoxHeight };
	
	MenuRCS->AddCheckBoxToList(_TempXOR("Active"), &RecoilControl->Active, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuRCS->AddChangeValueBoxToList(_TempXOR("Sleep Time(MS)"), &CRecoilControl::SleepTime, 1, 1000, 0, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuRCS->AddChangeValueBoxToList(_TempXOR("Recoil counter X multiplayer"), &CRecoilControl::m_XMultiplayer, 0.02f, 10.0f, 0.1f, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuRCS->AddChangeValueBoxToList(_TempXOR("Recoil counter Y multiplayer"), &CRecoilControl::m_YMultiplayer, 0.02f, 10.0f, 0.1f, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuRCS->AddChangeValueBoxToList(_TempXOR("Toggle HotKey"), KeyNames, &CRecoilControl::HotKey, 255, 0, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));


	MenuTriggerBot = AddSubMenu(_TempXOR("TriggerBot"), RECT{ LastSubMenuTitleBarPosition.left, LastSubMenuTitleBarPosition.bottom + 5, LastSubMenuTitleBarPosition.left + 100, LastSubMenuTitleBarPosition.bottom + 40 }, RECT{ LastSubMenuTitleBarPosition.left, LastSubMenuTitleBarPosition.bottom + 5, LastSubMenuTitleBarPosition.right, MenuPostion.bottom }, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuTriggerBot->MenuActive = false;
	MenuTriggerBot->InitCheckBoxes(4);
	MenuTriggerBot->InitChangeValueBoxesI(5);
	MenuTriggerBot->InitChangeValueBoxesF(1);
	MenuTriggerBot->InitChangeValueBoxesT(1);
	MenuTriggerBot->CheckBoxListFirstPosition = RECT{ SubMenu[0].MenuTitleBarPostion.right + 10, SubMenu[0].MenuTitleBarPostion.top, SubMenu[0].MenuTitleBarPostion.right + CheckBoxWidth, SubMenu[0].MenuTitleBarPostion.top + CheckBoxHeight };
	MenuTriggerBot->CheckBoxListNextPosition = RECT{ 0, 5, 0, CheckBoxHeight };
	MenuTriggerBot->ChangeValueBoxListFirstPosition = RECT{ SubMenu[0].CheckBoxListFirstPosition.right + 10, SubMenu[0].CheckBoxListFirstPosition.top, SubMenu[0].CheckBoxListFirstPosition.right + ChangeValueBoxWidth, SubMenu[0].CheckBoxListFirstPosition.top + ChangeValueBoxHeight };
	MenuTriggerBot->ChangeValueBoxListNextPosition = RECT{ 0, 5, 0, ChangeValueBoxHeight };
	MenuTriggerBot->TextLabelListFirstPosition = RECT{ SubMenu[0].MenuTitleBarPostion.right + 10, SubMenu[0].MenuTitleBarPostion.top, MenuPostion.right + 10, SubMenu[0].MenuTitleBarPostion.top + CheckBoxHeight };
	MenuTriggerBot->TextLabelListNextPosition = RECT{ 0, 5, 0, CheckBoxHeight };

	MenuTriggerBot->AddCheckBoxToList(_TempXOR("Active"), &CTriggerBot::Active, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuTriggerBot->AddCheckBoxToList(_TempXOR("On Hotkey press"), &CTriggerBot::OnHotKey, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuTriggerBot->AddCheckBoxToList(_TempXOR("Shoot Only On Head"), &CTriggerBot::ShootOnHitBox, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuTriggerBot->AddCheckBoxToList(_TempXOR("Sniper Mode"), &CTriggerBot::SniperMode, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuTriggerBot->AddChangeValueBoxToList(_TempXOR("Sleep Time(MS)"), &CTriggerBot::SleepTime, 1, 1000, 0, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuTriggerBot->AddChangeValueBoxToList(_TempXOR("HotKey"), KeyNames, &CTriggerBot::HotKey, 255, 0, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuTriggerBot->AddChangeValueBoxToList(_TempXOR("Delay Time(MS)"), &CTriggerBot::DelayTime, 1, 1000, 0, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuTriggerBot->AddChangeValueBoxToList(_TempXOR("Shooting Time(MS)"), &CTriggerBot::ShootingTime, 1, 1000, 0, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuTriggerBot->AddChangeValueBoxToList(_TempXOR("Break Time(MS)"), &CTriggerBot::BreakTime, 1, 1000, 0, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuTriggerBot->AddChangeValueBoxToList(_TempXOR("On Lose Target Shooting Time(MS)"), &TriggerBot.ExtraShootingTime, 1, 1000, 0, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuTriggerBot->AddChangeValueBoxToList(_TempXOR("Max punch"), &CTriggerBot::MaxPunch, 0.02f, 10.0f, 0.1f, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	


	MenuAimBot = AddSubMenu(_TempXOR("AimBot"), RECT{ LastSubMenuTitleBarPosition.left, LastSubMenuTitleBarPosition.bottom + 5, LastSubMenuTitleBarPosition.left + 100, LastSubMenuTitleBarPosition.bottom + 40 }, RECT{ LastSubMenuTitleBarPosition.left, LastSubMenuTitleBarPosition.bottom + 5, LastSubMenuTitleBarPosition.right, MenuPostion.bottom }, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuAimBot->MenuActive = false;
	MenuAimBot->InitCheckBoxes(9);
	MenuAimBot->InitChangeValueBoxesI(4);
	MenuAimBot->InitChangeValueBoxesF(10);
	MenuAimBot->InitChangeValueBoxesT(2);
	MenuAimBot->CheckBoxListFirstPosition = RECT{ SubMenu[0].MenuTitleBarPostion.right + 10, SubMenu[0].MenuTitleBarPostion.top, SubMenu[0].MenuTitleBarPostion.right + CheckBoxWidth, SubMenu[0].MenuTitleBarPostion.top + CheckBoxHeight };
	MenuAimBot->CheckBoxListNextPosition = RECT{ 0, 5, 0, CheckBoxHeight };
	MenuAimBot->ChangeValueBoxListFirstPosition = RECT{ SubMenu[0].CheckBoxListFirstPosition.right + 10, SubMenu[0].CheckBoxListFirstPosition.top, SubMenu[0].CheckBoxListFirstPosition.right + ChangeValueBoxWidth, SubMenu[0].CheckBoxListFirstPosition.top + ChangeValueBoxHeight };
	MenuAimBot->ChangeValueBoxListNextPosition = RECT{ 0, 5, 0, ChangeValueBoxHeight };
	MenuAimBot->TextLabelListFirstPosition = RECT{ SubMenu[0].MenuTitleBarPostion.right + 10, SubMenu[0].MenuTitleBarPostion.top, MenuPostion.right + 10, SubMenu[0].MenuTitleBarPostion.top + CheckBoxHeight };
	MenuAimBot->TextLabelListNextPosition = RECT{ 0, 5, 0, CheckBoxHeight };

	MenuAimBot->AddCheckBoxToList(_TempXOR("Active"), &CAimBot::Active, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuAimBot->AddCheckBoxToList(_TempXOR("Draw FOV"), &CAimBot::DrawFOV, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuAimBot->AddCheckBoxToList(_TempXOR("Focus closest to crosshair"), &CAimBot::AimOnClosestToCrosshair, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuAimBot->AddCheckBoxToList(_TempXOR("Focus closest to player"), &CAimBot::AimOnClosestToPlayer, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuAimBot->AddCheckBoxToList(_TempXOR("Dont lock next target"), &CAimBot::DontLockNext, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuAimBot->AddCheckBoxToList(_TempXOR("Focus Only Spotted"), &CAimBot::FocusOnlySpotted, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuAimBot->AddCheckBoxToList(_TempXOR("Use \"Rage\" Aim System (Set Sleep to 1)"), &CAimBot::bRage, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuAimBot->AddCheckBoxToList(_TempXOR("Random Moves UNSTABLE"), &CAimBot::bRandomMoves, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuAimBot->AddCheckBoxToList(_TempXOR("Stop Random Moves When Shooting"), &CAimBot::StopRandomMovesWhenShooting, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuAimBot->AddChangeValueBoxToList(_TempXOR("Sleep Time(MS)"), &CAimBot::SleepTime, 1, 1000, 0, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuAimBot->AddChangeValueBoxToList(_TempXOR("HotKey"), KeyNames, &CAimBot::HotKey, 255, 0, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuAimBot->AddChangeValueBoxToList(_TempXOR("Aim Bone"), AimBonesNames, &CAimBot::AimBoneIndex, 3, 0, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuAimBot->AddChangeValueBoxToList(_TempXOR("FOV"), &CAimBot::FOV, 1, 1000, 0, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuAimBot->AddChangeValueBoxToList(_TempXOR("Predict Movment"), &CAimBot::PredictMovment, 1, 1000, 0, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuAimBot->AddChangeValueBoxToList(_TempXOR("Recoil counter X multiplayer"), &CAimBot::m_XMultiplayer, 0.02f, 10.0f, 0.1f, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuAimBot->AddChangeValueBoxToList(_TempXOR("Recoil counter Y multiplayer"), &CAimBot::m_YMultiplayer, 0.02f, 10.0f, 0.1f, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuAimBot->AddChangeValueBoxToList(_TempXOR("Boost speed"), &CAimBot::BustSpeed, 0.02f, 100.0f, 0.1f, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuAimBot->AddChangeValueBoxToList(_TempXOR("Smooth"), &CAimBot::Smooth, 0.1f, 100.0f, 0.1f, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuAimBot->AddChangeValueBoxToList(_TempXOR("Stop aimbot after X (ms)"), &CAimBot::StopAimbotAfterXMS, 1, 10000, 0, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuAimBot->AddChangeValueBoxToList(_TempXOR("Stop Aiming At Distance(px)"), &CAimBot::StopAimingAtDistance, 0.1f, 100.0f, 0.1f, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuAimBot->AddChangeValueBoxToList(_TempXOR("Random Moves Rand Time"), &CAimBot::MaxRandTime, 0.02f, 100.0f, 0.00f, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuAimBot->AddChangeValueBoxToList(_TempXOR("Random Moves Time"), &CAimBot::AdditionalTime, 0.02f, 100.0f, 0.00f, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuAimBot->AddChangeValueBoxToList(_TempXOR("Random Moves Multiplier"), &CAimBot::RandomMultiplier, 0.02f, 100.0f, 0.00f, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuAimBot->AddChangeValueBoxToList(_TempXOR("Random Moves Max Random X"), &CAimBot::RandomX, 0.02f, 100.0f, 0.00f, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuAimBot->AddChangeValueBoxToList(_TempXOR("Random Moves Max Random Y"), &CAimBot::RandomY, 0.02f, 100.0f, 0.00f, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));


	MenuMisc = AddSubMenu(_TempXOR("Misc"), RECT{ LastSubMenuTitleBarPosition.left, LastSubMenuTitleBarPosition.bottom + 5, LastSubMenuTitleBarPosition.left + 100, LastSubMenuTitleBarPosition.bottom + 40 }, RECT{ LastSubMenuTitleBarPosition.left, LastSubMenuTitleBarPosition.bottom + 5, LastSubMenuTitleBarPosition.right, MenuPostion.bottom }, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuMisc->MenuActive = false;
	MenuMisc->InitCheckBoxes(1);
	MenuMisc->InitChangeValueBoxesI(3);
	MenuMisc->InitChangeValueBoxesT(1);
	MenuMisc->CheckBoxListFirstPosition = RECT{ SubMenu[0].MenuTitleBarPostion.right + 10, SubMenu[0].MenuTitleBarPostion.top, SubMenu[0].MenuTitleBarPostion.right + CheckBoxWidth, SubMenu[0].MenuTitleBarPostion.top + CheckBoxHeight };
	MenuMisc->CheckBoxListNextPosition = RECT{ 0, 5, 0, CheckBoxHeight };
	MenuMisc->ChangeValueBoxListFirstPosition = RECT{ SubMenu[0].CheckBoxListFirstPosition.right + 10, SubMenu[0].CheckBoxListFirstPosition.top, SubMenu[0].CheckBoxListFirstPosition.right + ChangeValueBoxWidth, SubMenu[0].CheckBoxListFirstPosition.top + ChangeValueBoxHeight };
	MenuMisc->ChangeValueBoxListNextPosition = RECT{ 0, 5, 0, ChangeValueBoxHeight };
	MenuMisc->TextLabelListFirstPosition = RECT{ SubMenu[0].MenuTitleBarPostion.right + 10, SubMenu[0].MenuTitleBarPostion.top, MenuPostion.right + 10, SubMenu[0].MenuTitleBarPostion.top + CheckBoxHeight };
	MenuMisc->TextLabelListNextPosition = RECT{ 0, 5, 0, CheckBoxHeight };
	MenuMisc->AddCheckBoxToList(_TempXOR("Bunny Hop"), &CEngine::bBunnyHop, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuMisc->AddChangeValueBoxToList(_TempXOR("Panic HotKey"), KeyNames, &CEngine::PANICK_KEY, 255, 0, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));
	MenuMisc->AddChangeValueBoxToList(_TempXOR("Players refresh(MS)"), &CEngine::ReadPlayersSleep, 1, 1000, 0, Color(255, 0, 0, 0), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255));


	MenuMain->MenuActive = true;
	ActiveSubMenu = MenuMain;
}