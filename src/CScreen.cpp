#include "CScreen.h"
#include "Global.h"
#include <sstream>

#include "Resource.h"

using namespace std;
using namespace Gdiplus;


// I'm horrible with animation


CScreen::CScreen() :
	m_Lines(),
	m_Title(),
	m_TimerRandom(this->DELAY_RANDOM_CHAR),
	m_TimerNext(this->DELAY_NEXT_CHAR),
	m_Viewport(85, 396, 213, 168),
	m_AnimateText(FALSE),
	m_AnimateTitle(FALSE),
	m_BackBuffer(nullptr),
	m_Font(nullptr),
	m_Screen(nullptr),
	m_Background(Color(0x5d, 0x82, 0x36))
{
	this->m_BackBuffer = new Gdiplus::Bitmap(this->m_Viewport.Width, this->m_Viewport.Height);
	this->m_Font = Gdiplus::Bitmap::FromResource(AfxGetInstanceHandle(), MAKEINTRESOURCEW(IDB_FONT));
	this->m_Screen = new Gdiplus::Graphics(this->m_BackBuffer);

	this->m_TextViewport = {
		0,
		CScreen::CHAR_HEIGHT + CScreen::CHAR_SPACING,
		this->m_Viewport.Width,
		this->m_Viewport.Height
	};

	this->m_TitleViewport = { 0, 0, this->m_Viewport.Width, this->m_Viewport.Height };
	srand(time(nullptr));
}

CScreen::~CScreen()
{
	SAFE_DELETE(this->m_Screen);
	SAFE_DELETE(this->m_Font);
	SAFE_DELETE(this->m_BackBuffer);
}

void CScreen::SetText(const string& text)
{
    stringstream check(text);

    string word;
	int size = 0;
	int pos = 0;
	int line = 0;
	int lastX = this->m_TextViewport.Width - CScreen::CHAR_WIDTH;

	for (int i = 0; i < CScreen::LINE_COUNT; i++)
	{
		this->m_Lines[i].Words.clear();
		this->m_Lines[i].Index = 0;
		this->m_Lines[i].X = 0;
	}

    while (getline(check, word, ' '))
    {
		int textLength = word.length();
		int size = (textLength * CScreen::CHAR_WIDTH) + (textLength * CScreen::CHAR_SPACING);

		if ((pos + size) > this->m_TextViewport.Width)
		{
			pos = 0;
			if (++line >= CScreen::LINE_COUNT)
				break;
		}

		this->m_Lines[line].Words.append(word).append(1, ' ');
		pos += size + CScreen::WORD_SPACING;
    }
	
	this->m_Screen->FillRectangle(&this->m_Background, this->m_TextViewport);
	
	this->ResetTicks();
	this->m_AnimateText = TRUE;
}

void CScreen::SetTitle(const string& title)
{
	this->m_Title.Words = title;
	this->m_Title.Index = 0;
	this->m_Title.X = 0;

	this->m_Screen->FillRectangle(&this->m_Background, this->m_TitleViewport);

	this->ResetTicks();
	this->m_AnimateTitle = TRUE;
}

void CScreen::Clear(CWnd* const owner)
{
	this->ClearTitle(owner);
	this->ClearText(owner);
}

void CScreen::ClearTitle(CWnd* const owner)
{
	this->m_Title.Words.clear();
	this->m_Screen->FillRectangle(&this->m_Background, this->m_TitleViewport);

	RECT rect = {
		this->m_TitleViewport.X + this->m_Viewport.X,
		this->m_TitleViewport.Y + this->m_Viewport.Y,
		this->m_TitleViewport.Width,
		this->m_TitleViewport.Height
	};

	owner->InvalidateRect(&rect, FALSE);
}

void CScreen::ClearText(CWnd* const owner)
{
	for (int i = 0; i < CScreen::LINE_COUNT; i++)
		this->m_Lines[i].Words.clear();

	this->m_Screen->FillRectangle(&this->m_Background, this->m_TextViewport);

	RECT rect = {
		this->m_TextViewport.X + this->m_Viewport.X,
		this->m_TextViewport.Y + this->m_Viewport.Y,
		this->m_TextViewport.Width,
		this->m_TextViewport.Height
	};

	owner->InvalidateRect(&rect, FALSE);
}

BOOL CScreen::AnimateTitle()
{
	//char ch = this->NextChar(this->m_Title);
	//if (ch == 0)
	//{
	//	this->m_AnimateTitle = FALSE;
	//	return FALSE;
	//}

	//int charIndex = (ch - 65) * CScreen::CHAR_WIDTH;

	//this->m_Screen->DrawImage(
	//	this->m_Font,
	//	this->m_Title.X, this->m_Title.Y, 
	//	charIndex, 0, CScreen::CHAR_WIDTH, CScreen::CHAR_HEIGHT,
	//	Unit::UnitPixel
	//);

	return TRUE;
}

BOOL CScreen::AnimateText(CScreen::LineInfo& line, int lineNo)
{
	if (line.Index >= line.Words.length())
		return FALSE;

	char ch = line.Words[line.Index];
	if (ch == ' ')
	{
		line.Index++;
		line.X += CScreen::WORD_SPACING;
		return TRUE;
	}

	int charIndex = 0;
	if (ch < 'A')
		charIndex = ((ch - '0') + 26) * CScreen::CHAR_WIDTH;
	else
		charIndex = (ch - 'A') * CScreen::CHAR_WIDTH;

	if (this->m_TimerRandom > 0)
		charIndex = (rand() % CScreen::CHAR_COUNT) * CScreen::CHAR_WIDTH;

	int y = (lineNo * CScreen::CHAR_HEIGHT) + (lineNo * CScreen::CHAR_SPACING);

	this->m_Screen->DrawImage(
		this->m_Font,
		line.X, y,
		charIndex, 0, CScreen::CHAR_WIDTH, CScreen::CHAR_HEIGHT,
		Unit::UnitPixel
	);

	if (this->m_TimerRandom <= 0)
	{
		this->m_TimerRandom = this->DELAY_RANDOM_CHAR;
		line.X += CScreen::CHAR_SPACING + CScreen::CHAR_WIDTH;
		line.Index++;
	}

	return TRUE;
}

BOOL CScreen::OnFrame()
{
	BOOL needsUpdate = FALSE;
	
	this->Tick();

	if (this->m_AnimateTitle)
	{
		this->m_AnimateTitle = this->AnimateText(this->m_Title);
		needsUpdate = TRUE;
	}

	if (this->m_AnimateText)
	{
		DWORD done = 0;
		for (int i = 0; i < CScreen::LINE_COUNT; i++)
		{
			if (!this->AnimateText(this->m_Lines[i], i+1))
				done++;
		}

		if (done >= CScreen::LINE_COUNT)
			this->m_AnimateText = FALSE;

		needsUpdate = TRUE;
	}

	return needsUpdate;
}

void CScreen::OnRender(HDC hdc)
{
	Gdiplus::Graphics gx(hdc);
	gx.DrawImage(this->m_BackBuffer, this->m_Viewport);
}

const Gdiplus::Rect& CScreen::Viewport() const
{
	return this->m_Viewport;
}

void CScreen::ResetTicks()
{
	this->m_TimerRandom = this->DELAY_RANDOM_CHAR;
	this->m_TimerNext = this->DELAY_NEXT_CHAR;
}

void CScreen::Tick()
{
	this->m_TimerRandom--;
	if (this->m_TimerRandom < 0)
		this->m_TimerRandom = 0;

	if (this->m_TimerRandom <= 0)
	{
		this->m_TimerNext--;
		if (this->m_TimerNext < 0)
			this->m_TimerNext = 0;
	}
}