#pragma once

#include <vector>

#define TOP_BAR_X	{40, 15, 10, 5, 5, 3, 2, 1, 0, 0}		// 그래프 막대 위 음영 x축(10개까지 좌표 나열)

#define GRAPH_BAR_TOTAL_LEN	150		// 그래프 막대 총 넓이 150 ( 10개 그래프로 하나에 15씩)
#define GRAPH_BAR_HIGH_MAX	110		// 그래프 막대 총 높이

namespace {
	constexpr int MAX_POLYGON_NUM = 5; // 5방면을 처리하기 위함 . 육면체에서 밑면을 제거함

	enum ColorType {
		RED = 1,
		ORANGE = 2,
		YELLOW = 3,
		GREEN = 4,
		CYAN = 5,
		BLUE = 6,
		PURPLE = 7,
		NAVY = 8,
		BROWN = 9,
		GRAY = 10
	};
}

typedef struct GRAPH_INFO_
{
	COLORREF	front_color;
	COLORREF	top_color;
	COLORREF	side_color;

	RECT		bar_rect;
	POINT		vertical[MAX_POLYGON_NUM];
	POINT		horizontal[MAX_POLYGON_NUM];

}GRAPH_INFO, *PGRAPH_INFO;

class GraphImpl
{
public:
	GraphImpl();
	~GraphImpl();

	void CreateGraph(HWND hwnd);
	void SetSize(const int item_count);
	void AddItem(const int index, const int value);

	void TestDrawHorizon();
private :
	void SetGraphPosition();
	void Bar(PGRAPH_INFO pGraph_Info);	// Statistics_Bar
	void BarColor(int index, int colorCode);
	void Background(int iXL, int iYU, int iXR, int iYD);
	void HorizontalGuideLine(PGRAPH_INFO pGraph_Info, int iXL, int iYU, int iXR, int iYD, int bar_count);

	GRAPH_INFO graph_info_[10] = { 0, }; // FIXME : 테스트용 향후 동적으로 객체 크기를 정해야함.

	std::vector<int> items;

	RECT rt_;
	HWND graph_hwnd_;
	int item_total_count_;
};

