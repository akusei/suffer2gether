#pragma once
#ifndef CSCREEN_H
#define CSCREEN_H

#include "framework.h"
#include <gdiplus.h>
#include <string>
#include <vector>


class CScreen
{
public:
	CScreen();
	virtual ~CScreen();

	BOOL OnFrame();
	void OnRender(HDC hdc);

	void SetText(const std::string& text);
	void SetTitle(const std::string& title);
	void Clear(CWnd* const owner);
	void ClearTitle(CWnd* const owner);
	void ClearText(CWnd* const owner);

	const Gdiplus::Rect& Viewport() const;

protected:
	static const DWORD LINE_COUNT = 4;
	static const DWORD CHAR_WIDTH = 19;
	static const DWORD CHAR_HEIGHT = 32;
	static const DWORD CHAR_SPACING = 2;
	static const DWORD WORD_SPACING = 15;
	static const DWORD CHAR_COUNT = 36;

	const float DELAY_RANDOM_CHAR = 3.0;
	const float DELAY_NEXT_CHAR = 3.0;

	typedef struct LineInfo
	{
		LineInfo() : Words(), Index(0), X(0) {}
		std::string Words;
		DWORD Index;
		DWORD X;
	} LineInfo;

	Gdiplus::Rect m_Viewport;
	Gdiplus::Rect m_TitleViewport;
	Gdiplus::Rect m_TextViewport;
	Gdiplus::Bitmap* m_Font;
	Gdiplus::Bitmap* m_BackBuffer;
	Gdiplus::Graphics* m_Screen;
	Gdiplus::SolidBrush m_Background;

	BOOL m_AnimateText;
	BOOL m_AnimateTitle;
	float m_TimerRandom;
	float m_TimerNext;

	CScreen::LineInfo m_Title;
	CScreen::LineInfo m_Lines[CScreen::LINE_COUNT];

	BOOL AnimateTitle();
	BOOL AnimateText(CScreen::LineInfo& line, int lineNo = 0);
	void Tick();
	void ResetTicks();
};

#endif
