#include "stdafx.h"
#include "GraphImpl.h"

#include <algorithm>

GraphImpl::GraphImpl()
{
}


GraphImpl::~GraphImpl()
{
}

void GraphImpl::Background(int left_pos, int top_pos, int right_pos, int bottom_pos)
{
	HDC hDC = GetDC(graph_hwnd_);

	HBRUSH hBrush_Bar = NULL;
	HBRUSH hBrush_BarOld = NULL;
	HPEN hPen_Bar = NULL;
	HPEN hPen_BarOld = NULL;

	char bar_shadow_xpos[10] = TOP_BAR_X; // FIXME : 하드코드 되있음.
	int bar_hor_size = GRAPH_BAR_TOTAL_LEN;

	bar_hor_size = bar_hor_size / item_total_count_;

	// 그래프 음영처리 사이드 아래 
	POINT pGraph_top_3d[] = { { left_pos + 30, top_pos + 15 },
	{ left_pos + 30 + (bar_hor_size / 3) - bar_shadow_xpos[item_total_count_ - 1] ,top_pos + 10 },
	{ left_pos + 30 + (bar_hor_size / 3) - bar_shadow_xpos[item_total_count_ - 1], bottom_pos - 16 },
	{ left_pos + 30, bottom_pos - 11 },
	{ left_pos + 30, top_pos + 15 } };


	POINT pGraph_bot_3d[] = { { left_pos + 30 + (bar_hor_size / 3) - bar_shadow_xpos[item_total_count_ - 1], bottom_pos - 16 },
	{ right_pos - 10 , bottom_pos - 16 },
	{ right_pos - 15, bottom_pos - 11 },
	{ left_pos + 30, bottom_pos - 11 },
	{ left_pos + 30 + (bar_hor_size / 3) - bar_shadow_xpos[item_total_count_ - 1], bottom_pos - 16 } };


	RECT rect_A_line = { left_pos - 11, top_pos, right_pos, bottom_pos };	//음영처리

	FillRect(hDC, &rect_A_line, (HBRUSH)GetStockObject(GRAY_BRUSH));
	Rectangle(hDC, (left_pos - 10), (top_pos + 1), right_pos, bottom_pos);

	hBrush_Bar = CreateSolidBrush(RGB(169, 169, 169));
	hBrush_BarOld = (HBRUSH)SelectObject(hDC, hBrush_Bar);

	Polygon(hDC, pGraph_top_3d, MAX_POLYGON_NUM); // 폴리곤은 좌표 순서대로 그린다. 
	Polygon(hDC, pGraph_bot_3d, MAX_POLYGON_NUM);

	(HPEN)SelectObject(hDC, hPen_BarOld);
	(HBRUSH)SelectObject(hDC, hBrush_BarOld);

	MoveToEx(hDC, left_pos + 30 + (bar_hor_size / 3) - bar_shadow_xpos[item_total_count_ - 1], (top_pos + 10), NULL);	// 맨위에 X축 막대기 
	LineTo(hDC, (right_pos - 10), (top_pos + 10));

	MoveToEx(hDC, (right_pos - 10), (top_pos + 10), NULL);	// 오른쪽 Y축 막대기 
	LineTo(hDC, right_pos - 10, (bottom_pos - 16));

	MoveToEx(hDC, (left_pos + 30), (top_pos + 15), NULL);	// X축
	LineTo(hDC, (left_pos + 30), (bottom_pos - 2));

	MoveToEx(hDC, (left_pos + 10), (bottom_pos - 11), NULL);	// Y축
	LineTo(hDC, (right_pos - 15), (bottom_pos - 11));

	// TODO : 이쯤에다가 X 축 Y 축이 무엇인지 Text로 출력.
}


void GraphImpl::Bar(PGRAPH_INFO pGraph_Info)
{
	HDC hDC = GetDC(graph_hwnd_);

	HBRUSH hBrush_Bar = NULL;
	HBRUSH hBrush_BarOld = NULL;

	HPEN hPen_Bar = NULL;
	HPEN hPen_BarOld = NULL;

	hBrush_Bar = CreateSolidBrush(pGraph_Info->front_color);
	hBrush_BarOld = (HBRUSH)SelectObject(hDC, hBrush_Bar);

	hPen_Bar = CreatePen(PS_SOLID, 1, pGraph_Info->front_color);
	hPen_BarOld = (HPEN)SelectObject(hDC, hPen_Bar);

	Rectangle(hDC,
		pGraph_Info->bar_rect.left,
		pGraph_Info->bar_rect.top,
		pGraph_Info->bar_rect.right,
		pGraph_Info->bar_rect.bottom
	);

	hPen_Bar = CreatePen(PS_SOLID, 1, pGraph_Info->top_color);
	(HPEN)SelectObject(hDC, hPen_Bar);

	hBrush_Bar = CreateSolidBrush(pGraph_Info->top_color);
	(HBRUSH)SelectObject(hDC, hBrush_Bar);

	Polygon(hDC, pGraph_Info->vertical, MAX_POLYGON_NUM);

	hPen_Bar = CreatePen(PS_SOLID, 1, pGraph_Info->side_color);
	(HPEN)SelectObject(hDC, hPen_Bar);

	hBrush_Bar = CreateSolidBrush(pGraph_Info->side_color);
	(HBRUSH)SelectObject(hDC, hBrush_Bar);

	Polygon(hDC, pGraph_Info->horizontal, MAX_POLYGON_NUM);

	(HBRUSH)SelectObject(hDC, hBrush_BarOld);
	(HPEN)SelectObject(hDC, hPen_BarOld);


	DeleteObject(hBrush_Bar);
	DeleteObject(hPen_Bar);
}

void GraphImpl::HorizontalGuideLine(PGRAPH_INFO pGraph_Info, int left_pos, int top_pos, int right_pos, int bottom_pos, int bar_count)
{
	char bar_shadow_xpos[10] = TOP_BAR_X; //FIXME: 하드코드 되있음.
	int bar_length = GRAPH_BAR_TOTAL_LEN;

	HFONT hCntFont = NULL;
	HFONT hCntFontOld = NULL;

	bar_length = bar_length / bar_count;

	HDC hDC = GetDC(graph_hwnd_);
	hCntFont = CreateFont(12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("돋움"));
	hCntFontOld = (HFONT)SelectObject(hDC, hCntFont);
	
	RECT line_pos = { rt_.left - 15, top_pos + 35, rt_.left + 27, top_pos + 70 };
	RECT line2_pos = { rt_.left - 15, top_pos + 75, rt_.left + 25, top_pos + 110 };

	CString buffer = _T( "대각선");
	DrawText(hDC, buffer, buffer.GetLength(), &line_pos, DT_RIGHT);
	
	CString buffer2 = _T("직선");
	DrawText(hDC, buffer2, buffer2.GetLength(), &line2_pos, DT_RIGHT);

	(HFONT)SelectObject(hDC, hCntFontOld);

	MoveToEx(hDC, left_pos + 30 + (bar_length / 3) - bar_shadow_xpos[bar_count - 1], top_pos + 60, NULL);	// Y축  +21 = 기본 15
	LineTo(hDC, (right_pos - 10), top_pos + 40);	//  190 = x축 길이

	MoveToEx(hDC, left_pos + 30 + (bar_length / 3) - bar_shadow_xpos[bar_count - 1], top_pos + 85, NULL);	// Y축  +18 = 기본 15
	LineTo(hDC, (right_pos - 10), top_pos + 85);	//  190 = x축 길이
}

void GraphImpl::BarColor(int index, int colorCode)
{
	switch (colorCode)
	{
	case ColorType::RED:	//  빨강
		graph_info_[index].front_color = RGB(222, 76, 99);
		graph_info_[index].top_color = RGB(212, 66, 89);
		graph_info_[index].side_color = RGB(192, 46, 69);
		break;

	case ColorType::ORANGE:	// 주황
		graph_info_[index].front_color = RGB(255, 156, 114);
		graph_info_[index].top_color = RGB(245, 146, 104);
		graph_info_[index].side_color = RGB(212, 126, 84);
		break;

	case ColorType::YELLOW:		// 노랑
		graph_info_[index].front_color = RGB(242, 236, 126);
		graph_info_[index].top_color = RGB(232, 226, 116);
		graph_info_[index].side_color = RGB(212, 206, 96);
		break;

	case ColorType::GREEN:	// 풀
		graph_info_[index].front_color = RGB(113, 195, 123);
		graph_info_[index].top_color = RGB(103, 185, 113);
		graph_info_[index].side_color = RGB(83, 165, 93);
		break;

	case ColorType::CYAN: // 청록
		graph_info_[index].front_color = RGB(63, 204, 213);
		graph_info_[index].top_color = RGB(53, 194, 203);
		graph_info_[index].side_color = RGB(33, 174, 183);
		break;

	case ColorType::BLUE:	// 파랑
		graph_info_[index].front_color = RGB(105, 164, 254);
		graph_info_[index].top_color = RGB(95, 154, 244);
		graph_info_[index].side_color = RGB(75, 134, 224);
		break;

	case ColorType::PURPLE:	// 보라
		graph_info_[index].front_color = RGB(194, 126, 237);
		graph_info_[index].top_color = RGB(184, 116, 227);
		graph_info_[index].side_color = RGB(164, 96, 207);
		break;

	case ColorType::NAVY:	// 남색
		graph_info_[index].front_color = RGB(139, 136, 213);
		graph_info_[index].top_color = RGB(129, 126, 203);
		graph_info_[index].side_color = RGB(109, 106, 183);
		break;

	case ColorType::BROWN:	// 갈색
		graph_info_[index].front_color = RGB(189, 181, 132);
		graph_info_[index].top_color = RGB(179, 171, 122);
		graph_info_[index].side_color = RGB(159, 151, 102);
		break;

	case ColorType::GRAY:	// 회색
		graph_info_[index].front_color = RGB(187, 187, 187);
		graph_info_[index].top_color = RGB(177, 177, 177);
		graph_info_[index].side_color = RGB(157, 157, 157);
		break;

	}
}

void GraphImpl::CreateGraph(HWND hwnd)
{
	graph_hwnd_ = hwnd;
	GetClientRect(hwnd, &rt_);
	
	Background(rt_.left, rt_.top, rt_.right, rt_.bottom);
	SetGraphPosition();
	
	for (int i = 0; i < item_total_count_; ++i)
	{
		Bar(&graph_info_[i]);  // NOTE : Bar를 하나씩 그린다. 나중에 객체 하나씩 값이 변경될때를 위함.
	}
}

void GraphImpl::SetGraphPosition()
{
	int hor_bar_size = GRAPH_BAR_TOTAL_LEN / item_total_count_;

	int left_start_pos_buffer = rt_.left + 45; // 좌측 시작 지점 45 최초의 시작 지점
	char bar_shadow_xpos[10] = TOP_BAR_X; // FIXME: 하드코드 되있음

	for (int i = 0; i < item_total_count_; i++)
	{
		BarColor(i, i + 1);

		int top_size_buffer = (GRAPH_BAR_HIGH_MAX * items[i]) / item_total_count_; // 차트 높이 비율

		graph_info_[i].bar_rect.left = left_start_pos_buffer;
		graph_info_[i].bar_rect.top = rt_.bottom - 11;	// top = 아래 y축
		graph_info_[i].bar_rect.right = graph_info_[i].bar_rect.left + hor_bar_size;
		graph_info_[i].bar_rect.bottom = rt_.bottom - 11 - top_size_buffer;

		// 작대기 세로측
		graph_info_[i].vertical[0].x = left_start_pos_buffer;
		graph_info_[i].vertical[0].y = rt_.bottom - 11 - top_size_buffer;
		graph_info_[i].vertical[1].x = left_start_pos_buffer + (hor_bar_size / 3) - bar_shadow_xpos[item_total_count_ - 1];	// 위 껍데기 x좌표 ( 막대기 갯수에따라 변화)
		graph_info_[i].vertical[1].y = rt_.bottom - 11 - top_size_buffer - 5;
		graph_info_[i].vertical[2].x = graph_info_[i].bar_rect.left + hor_bar_size + 5;		// 120
		graph_info_[i].vertical[2].y = rt_.bottom - 11 - top_size_buffer - 5;			  	    // 170
		graph_info_[i].vertical[3].x = graph_info_[i].bar_rect.left + hor_bar_size;			// 115
		graph_info_[i].vertical[3].y = rt_.bottom - 11 - top_size_buffer;
		graph_info_[i].vertical[4].x = left_start_pos_buffer;
		graph_info_[i].vertical[4].y = rt_.bottom - 11 - top_size_buffer;

		// 작대기 가로 
		graph_info_[i].horizontal[0].x = graph_info_[i].bar_rect.left + hor_bar_size;
		graph_info_[i].horizontal[0].y = rt_.bottom - 11 - top_size_buffer;
		graph_info_[i].horizontal[1].x = graph_info_[i].bar_rect.left + hor_bar_size;
		graph_info_[i].horizontal[1].y = rt_.bottom - 11;
		graph_info_[i].horizontal[2].x = graph_info_[i].bar_rect.left + hor_bar_size + 5;
		graph_info_[i].horizontal[2].y = rt_.bottom - 16;
		graph_info_[i].horizontal[3].x = graph_info_[i].bar_rect.left + hor_bar_size + 5;
		graph_info_[i].horizontal[3].y = rt_.bottom - 11 - top_size_buffer - 5;
		graph_info_[i].horizontal[4].x = graph_info_[i].bar_rect.left + hor_bar_size;
		graph_info_[i].horizontal[4].y = rt_.bottom - 11 - top_size_buffer;

		left_start_pos_buffer = left_start_pos_buffer + hor_bar_size;
	}
}
void GraphImpl::SetSize(const int count)
{
	item_total_count_ = count;
	items.assign(item_total_count_, 0);

}
void GraphImpl::AddItem(const int index, const int value)
{
	if (0 <= index && item_total_count_ > index)
		items[index] = value;
}

void GraphImpl::TestDrawHorizon() 
{
	HorizontalGuideLine(&graph_info_[0], rt_.left, rt_.top, rt_.right, rt_.bottom, 5);
}