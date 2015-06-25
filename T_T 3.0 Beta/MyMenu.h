#pragma once
#include "Globals.h"
#include "MyWindow.h"
#include "MyButtons.h"
#include "Drawings.h"

class CMenuCore
{
public:
	char *MenuName;
	RECT MenuPostion;
	RECT MenuTitleBarPostion;
	float MenuWidth;
	float MenuHeight;

	bool MenuActive;
	clock_t MenuActiveStateChangeTime = 0;

	Color MenuCursorColor;
	Color MenuColor;
	Color MenuBorderColor;
	Color MenuNameColor;
	Color TitleBarColor;
	Color ActiveTitleBarColor;
	Color TitleBarBorderColor;

	int TextLabels = 0;
	int MaxTextLabels;
	CTextLabel* TextLabel;
	RECT LastTextLabelPos;
	RECT TextLabelListFirstPosition;
	RECT TextLabelListNextPosition;
	void InitTextLables(int amount);
	void AddTextLabel(char* Text, RECT Position, Color FillColor, Color BorderColor, Color TextColor);
	void AddTextLabelToList(char* Text, Color FillColor, Color BorderColor, Color TextColor);

	int Buttons = 0;
	int MaxButtons;
	CButton *Button;
	RECT LastButtonPos;
	RECT ButtonListFirstPosition;
	RECT ButtonListNextPosition;
	void InitButtons(int amount);
	void AddButton(char* Text, bool *Variable, RECT Position, Color FillColor, Color BorderColor, Color PressedColor, Color TextColor);
	void AddButtonToList(char* Text, bool *Variable, Color FillColor, Color BorderColor, Color PressedColor, Color TextColor);
	void UpdateButtons();


	int CheckBoxes = 0;
	int MaxCheckBoxes;
	CCheckBox *CheckBox;
	RECT LastCheckBoxPos;
	RECT CheckBoxListFirstPosition;
	RECT CheckBoxListNextPosition;
	void InitCheckBoxes(int amount);
	void AddCheckBox(char* Text, bool *Variable, RECT Position, Color BorderColor, Color FillColor, Color CheckColor, Color TextColor);
	void AddCheckBoxToList(char* Text, bool *Variable, Color BorderColor, Color FillColor, Color CheckColor, Color TextColor);
	void UpdateCheckBoxes();


	int ChangeValueBoxesI = 0;
	int MaxChangeValueBoxesI;
	CChangeValueBox<int> *ChangeValueBoxI;
	int ChangeValueBoxesF = 0;
	int MaxChangeValueBoxesF;
	CChangeValueBox<float> *ChangeValueBoxF;
	int ChangeValueBoxesT = 0;
	int MaxChangeValueBoxesT;
	CChangeValueBoxText *ChangeValueBoxT;

	RECT LastChangeValueBoxPos;
	RECT ChangeValueBoxListFirstPosition;
	RECT ChangeValueBoxListNextPosition;

	void InitChangeValueBoxesI(int amount);
	void InitChangeValueBoxesF(int amount);
	void InitChangeValueBoxesT(int amount);

	void AddChangeValueBox(char *Text, int *Value, int ChangeValue, int MaxValue, int MinValue, RECT Position, Color FillColor, Color BorderColor, Color AddColor, Color SubColor, Color TextColor);
	void AddChangeValueBoxToList(char *Text, int *Value, int ChangeValue, int MaxValue, int MinValue, Color FillColor, Color BorderColor, Color AddColor, Color SubColor, Color TextColor);

	void AddChangeValueBox(char *Text, float *Value, float ChangeValue, float MaxValue, float MinValue, RECT Position, Color FillColor, Color BorderColor, Color AddColor, Color SubColor, Color TextColor);
	void AddChangeValueBoxToList(char *Text, float *Value, float ChangeValue, float MaxValue, float MinValue, Color FillColor, Color BorderColor, Color AddColor, Color SubColor, Color TextColor);

	void AddChangeValueBox(char *Text, char **ValueText, int *Value, int MaxValue, int MinValue, RECT Position, Color FillColor, Color BorderColor, Color AddColor, Color SubColor, Color TextColor);
	void AddChangeValueBoxToList(char *Text, char **ValueText, int *Value, int MaxValue, int MinValue, Color FillColor, Color BorderColor, Color AddColor, Color SubColor, Color TextColor);

	void UpdateChangeValueBoxes();


};

class CSubMenu : public CMenuCore
{
public:
	void MenuUpdate();
	void Draw();
	CSubMenu(){};
	virtual ~CSubMenu(){};
};

class CMyMenu : public CMenuCore
{
public:
	CMyMenu(){};
	~CMyMenu(){};

	int SubMenus;
	int MaxSubMenus;
	CSubMenu *ActiveSubMenu;
	CSubMenu *SubMenu;
	RECT LastSubMenuPosition;
	RECT LastSubMenuTitleBarPosition;
	CSubMenu* AddSubMenu(char* Name, RECT MenuTitleBarPostion, RECT Position, Color TitleBarColor, Color TitleBarBorderColor, Color MenuColor, Color MenuBorderColor, Color MenuNameColor);
	void UpdateSubMenus();

	void Init();

	void InitSubMenus(int amount);
	CSubMenu *MenuMain;
	CSubMenu *MenuVisuals;
	CSubMenu *MenuRadar;
	CSubMenu *MenuRCS;
	CSubMenu *MenuTriggerBot;
	CSubMenu *MenuAimBot;
	CSubMenu *MenuMisc;
	CSubMenu *MenuColors;
	CSubMenu *MenuOverClock;


	void Draw();
	void MenuUpdate();
	void MenuSave();
	void MenuLoad();

};

