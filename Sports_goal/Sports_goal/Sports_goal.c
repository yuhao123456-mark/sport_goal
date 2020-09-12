// Sports_goal.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "Sports_goal_resources.h"
#include "Sports_goal_specifications.h"
#include "gx_api.h"
#include <stdio.h>

GX_WINDOW_ROOT* root;

#define FRONT_WIDTH  18
#define FRONT_HEIGHT 44

#define SCREEN_WIDTH 320


void switch_interface(GX_WIDGET* widget, int current_interface,
	int change_interface);
void distance_length(GX_WIDGET* widget, int m);
void distance_timing(GX_WIDGET* widget, int hour, int mintue);
void change_front(GX_WIDGET* widget, int front, GX_WIDGET* sport_goal, int distance_num, GX_POINT point);
extern UINT win32_graphics_driver_setup_565rgb(GX_DISPLAY* display);



int hour = 0;
int mintue = 0;
int distance_m = 0;
GX_BOOL first_clicked = GX_TRUE;
UINT SET_EVENT_HANDLER(GX_WINDOW* widget, GX_EVENT* event_ptr) {
	switch (event_ptr->gx_event_type) {
	case GX_SIGNAL(IDC_SET_AIMS, GX_EVENT_CLICKED): {
		switch_interface(widget, IDC_MAIN_SET, IDC_CHILD_AIMS);
	} break;
	case GX_SIGNAL(IDC_SET_AIMS_DISTANCE, GX_EVENT_CLICKED): {
		switch_interface(widget, IDC_MAIN_SET, IDC_CHILD_DISTANCE);
	} break;
	case GX_SIGNAL(IDC_SET_AIMS_TIME, GX_EVENT_CLICKED): {
		switch_interface(widget, IDC_MAIN_SET, IDC_CHILD_TIME);
	} break;
	case GX_SIGNAL(IDC_SET_AIMS_CALORIES, GX_EVENT_CLICKED): {
		switch_interface(widget, IDC_MAIN_SET, IDC_CHILD_CALORIES);
	} break;
	case GX_SIGNAL(IDC_SET_SWITCH, GX_EVENT_CLICKED): {
		if (first_clicked == GX_TRUE) {
			GX_WIDGET* sport_goal[1];
			gx_widget_find(widget, IDC_SET_SWITCH, IDC_SET_SWITCH, sport_goal);
			gx_icon_button_pixelmap_set(sport_goal[0],
				GX_PIXELMAP_ID_TARGET_CLOSE_ICON);
			first_clicked = GX_FALSE;
		}
		else if (first_clicked == GX_FALSE) {
			GX_WIDGET* sport_goal[1];
			gx_widget_find(widget, IDC_SET_SWITCH, IDC_SET_SWITCH, sport_goal);
			gx_icon_button_pixelmap_set(sport_goal[0],
				GX_PIXELMAP_ID_TARGET_OPEN_ICON);
			first_clicked = GX_TRUE;
		}
	} break;
	case GX_SIGNAL(IDC_TIME_EXIT, GX_EVENT_CLICKED): {
		switch_interface(widget, IDC_CHILD_TIME, IDC_MAIN_SET);
	} break;
	case GX_SIGNAL(IDC_TIME_EXIT1, GX_EVENT_CLICKED): {
		switch_interface(widget, IDC_CHILD_TIME, IDC_MAIN_SET);
	} break;
	case GX_SIGNAL(IDC_TIME_LESS, GX_EVENT_CLICKED): {
		mintue--;
		if (mintue <= 0)
		{
			if (hour <= 0 && mintue <= 0) {
				hour = 0;
				mintue = 0;
			}
			else {
				hour--;
				mintue = 59;
			}
		}

		distance_timing(widget, hour, mintue);
	} break;
	case GX_SIGNAL(IDC_TIME_PLUS, GX_EVENT_CLICKED): {
		mintue++;
		if (mintue >= 59 && hour >= 99)
		{
			mintue = 59;
			hour = 99;
		}
		if (mintue == 60)
		{
			hour++;
			mintue = 0;
		}
		distance_timing(widget, hour, mintue);
	} break;
	case GX_SIGNAL(IDC_TIME_FINISH_WIDGET, GX_EVENT_CLICKED):
	{
		switch_interface(widget, IDC_CHILD_TIME, IDC_MAIN_SET);
	}
	break;
	case GX_SIGNAL(IDC_DISTANCE_EXIT, GX_EVENT_CLICKED):
	{
		switch_interface(widget, IDC_CHILD_DISTANCE, IDC_MAIN_SET);
	}
	break;
	case GX_SIGNAL(IDC_DISTANCE_EXIT1, GX_EVENT_CLICKED):
	{
		switch_interface(widget, IDC_CHILD_DISTANCE, IDC_MAIN_SET);
	}
	break;
	case GX_SIGNAL(IDC_DISTANCE_LESS, GX_EVENT_CLICKED):
	{
		distance_m--;
		if (distance_m <= 0)
		{
			distance_m = 0;
		}
		distance_length(widget, distance_m);
	}
	break;
	case GX_SIGNAL(IDC_DISTANCE_PLUS, GX_EVENT_CLICKED):
	{
		distance_m++;
		if (distance_m >= 40000)
		{
			distance_m = 40000;
		}
		distance_length(widget, distance_m);
	}
	default:
		gx_window_event_process(widget, event_ptr);
	}
}

void distance_timing(GX_WIDGET* widget, int hour, int mintue) {
	GX_WIDGET* sport_goal[1];

	GX_RESOURCE_ID distance_time_TAB[] = {
	GX_PIXELMAP_ID_SPORTS1_NUM0, GX_PIXELMAP_ID_SPORTS1_NUM1,
	GX_PIXELMAP_ID_SPORTS1_NUM2, GX_PIXELMAP_ID_SPORTS1_NUM3,
	GX_PIXELMAP_ID_SPORTS1_NUM4, GX_PIXELMAP_ID_SPORTS1_NUM5,
	GX_PIXELMAP_ID_SPORTS1_NUM6, GX_PIXELMAP_ID_SPORTS1_NUM7,
	GX_PIXELMAP_ID_SPORTS1_NUM8, GX_PIXELMAP_ID_SPORTS1_NUM9,
	};

	gx_widget_find(widget, IDC_TIME_HOUR1, IDC_TIME_HOUR1, sport_goal);
	gx_icon_pixelmap_set((GX_ICON*)sport_goal[0], distance_time_TAB[hour / 10], 0);
	gx_widget_find(widget, IDC_TIME_HOUR2, IDC_TIME_HOUR2, sport_goal);
	gx_icon_pixelmap_set((GX_ICON*)sport_goal[0], distance_time_TAB[hour % 10], 0);
	gx_widget_find(widget, IDC_TIME_MINTUE1, IDC_TIME_MINTUE1, sport_goal);
	gx_icon_pixelmap_set((GX_ICON*)sport_goal[0], distance_time_TAB[mintue / 10], 0);
	gx_widget_find(widget, IDC_TIME_MINTUE2, IDC_TIME_MINTUE2, sport_goal);
	gx_icon_pixelmap_set((GX_ICON*)sport_goal[0], distance_time_TAB[mintue % 10], 0);
}

void distance_length(GX_WIDGET* widget, int m)
{
	GX_WIDGET* sport_goal[1];
	GX_RESOURCE_ID distance_num_TAB[] = {
	GX_PIXELMAP_ID_SPORTS1_NUM0, GX_PIXELMAP_ID_SPORTS1_NUM1,
	GX_PIXELMAP_ID_SPORTS1_NUM2, GX_PIXELMAP_ID_SPORTS1_NUM3,
	GX_PIXELMAP_ID_SPORTS1_NUM4, GX_PIXELMAP_ID_SPORTS1_NUM5,
	GX_PIXELMAP_ID_SPORTS1_NUM6, GX_PIXELMAP_ID_SPORTS1_NUM7,
	GX_PIXELMAP_ID_SPORTS1_NUM8, GX_PIXELMAP_ID_SPORTS1_NUM9,
	};

	if (m < 10)
	{
		gx_widget_find(widget, IDC_DISTANCE_NUM1, IDC_DISTANCE_NUM1, sport_goal);
		gx_icon_pixelmap_set(sport_goal[0], distance_num_TAB[m], 0);
	}
	//else if (m < 100)
	//{
	//	GX_POINT num_point = { 0 };
	//	num_point.gx_point_x = 132;
	//	num_point.gx_point_y = 133;
	//	change_front(widget, IDC_DISTANCE_NUM1, sport_goal[0], distance_num_TAB[m / 10], num_point);
	//	num_point.gx_point_x = 157;
	//	change_front(widget, IDC_DISTANCE_NUM2, sport_goal[0], distance_num_TAB[m % 10], num_point);
	//}
	//else if (m < 1000)
	//{
	//	GX_POINT num_point = { 0 };
	//	num_point.gx_point_x = 126;
	//	num_point.gx_point_y = 133;
	//	change_front(widget, IDC_DISTANCE_NUM1, sport_goal[0], distance_num_TAB[m / 100], num_point);
	//	num_point.gx_point_x = 151;
	//	change_front(widget, IDC_DISTANCE_NUM2, sport_goal[0], distance_num_TAB[m % 100 / 10], num_point);
	//	num_point.gx_point_x = 176;
	//	change_front(widget, IDC_DISTANCE_NUM3, sport_goal[0], distance_num_TAB[m % 10], num_point);
	//}
	//else if (m < 10000)
	//{
	//	GX_POINT num_point = { 0 };
	//	num_point.gx_point_x = 106;
	//	num_point.gx_point_y = 133;
	//	change_front(widget, IDC_DISTANCE_NUM1, sport_goal[0], distance_num_TAB[m / 1000], num_point);
	//	num_point.gx_point_x = 132;
	//	change_front(widget, IDC_DISTANCE_NUM2, sport_goal[0], distance_num_TAB[m % 1000 / 100], num_point);
	//	num_point.gx_point_x = 157;
	//	change_front(widget, IDC_DISTANCE_NUM3, sport_goal[0], distance_num_TAB[m % 100 / 10], num_point);
	//	num_point.gx_point_x = 182;
	//	change_front(widget, IDC_DISTANCE_NUM4, sport_goal[0], distance_num_TAB[m % 10], num_point);
	//}
	//else if (m < 100000)
	//{
	//	GX_POINT num_point = { 0 };
	//	num_point.gx_point_x = 101;
	//	num_point.gx_point_y = 133;
	//	change_front(widget, IDC_DISTANCE_NUM1, sport_goal[0], distance_num_TAB[m / 10000], num_point);
	//	num_point.gx_point_x = 126;
	//	change_front(widget, IDC_DISTANCE_NUM2, sport_goal[0], distance_num_TAB[m % 10000 / 1000], num_point);
	//	num_point.gx_point_x = 151;
	//	change_front(widget, IDC_DISTANCE_NUM3, sport_goal[0], distance_num_TAB[m % 1000 / 100], num_point);
	//	num_point.gx_point_x = 176;
	//	change_front(widget, IDC_DISTANCE_NUM4, sport_goal[0], distance_num_TAB[m % 100 / 10], num_point);
	//	num_point.gx_point_x = 201;
	//	change_front(widget, IDC_DISTANCE_NUM5, sport_goal[0], distance_num_TAB[m % 10], num_point);
	//}
}

void change_front(GX_WIDGET* widget, int front, GX_WIDGET* sport_goal, int distance_num, GX_POINT point)
{
	gx_widget_find(widget, front, front, &sport_goal);
	GX_RECTANGLE rect;
	rect.gx_rectangle_left = point.gx_point_x;
	rect.gx_rectangle_top = point.gx_point_y;
	rect.gx_rectangle_right = point.gx_point_x + FRONT_WIDTH;
	rect.gx_rectangle_bottom = point.gx_point_y + FRONT_HEIGHT;
	gx_widget_resize(sport_goal, &rect);
	gx_icon_pixelmap_set(sport_goal, distance_num, 0);
}

void switch_interface(GX_WIDGET* widget, int current_interface,
	int change_interface) {
	GX_WIDGET* sport_goal[1];
	gx_widget_find(widget, change_interface, change_interface, sport_goal);
	GX_RECTANGLE rect = { 0 };
	rect.gx_rectangle_left = 0;
	rect.gx_rectangle_top = 0;
	rect.gx_rectangle_right = 320;
	rect.gx_rectangle_bottom = 385;
	gx_widget_resize(sport_goal[0], &rect);
	gx_widget_find(widget, current_interface, current_interface, sport_goal);
	rect.gx_rectangle_left = 1000;
	gx_widget_resize(sport_goal[0], &rect);
}

UINT string_length_get(GX_CONST GX_CHAR* input_string, UINT max_string_length) {
	UINT length = 0;

	if (input_string) {
		/* Traverse the string.  */
		for (length = 0; input_string[length]; length++) {
			/* Check if the string length is bigger than the max string length.  */
			if (length >= max_string_length) {
				break;
			}
		}
	}

	return length;
}

VOID tx_application_define(void* first_unused_memory) {
	/* Initialize GUIX.  */
	gx_system_initialize();

	gx_studio_display_configure(DISPLAY_1, win32_graphics_driver_setup_565rgb,
		LANGUAGE_ENGLISH, DISPLAY_1_THEME_1, &root);

	/* Create calculator screen */
	gx_studio_named_widget_create("window", (GX_WIDGET*)root, GX_NULL);

	/* Show the root window to make it and patients screen visible.  */
	gx_widget_show(root);

	/* start GUIX thread */
	gx_system_start();
}

int main(int argc, char** argv) {
	AllocConsole();
	FILE* new_stream = 0;
	freopen_s(&new_stream, "CONOUT$", "w", stdout);
	printf("retarget_console");
	tx_kernel_enter();
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧:
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5.
//   转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
