/*
 * File: lumi_main.cpp
 * Created: 04/09/19
 * Authors: Zelin Liu
 * Content: This is the main file for Lumi-Talk.
 *
 *
 * */

/*
 * Memo:
 *
 *
 *
 * */

#include <windows.h>
#include "macro.h"
#include "letter.h"

LRESULT CALLBACK LumiWndProc(HWND, UINT, WPARAM, LPARAM);
void Handle_WM_COMMAND(HWND hwnd, WPARAM wParam, LPARAM lParam);
void Draw_Control(HWND hwnd);




/*
 * The main function for Windows application
 * https://docs.microsoft.com/en-us/windows/desktop/learnwin32/winmain--the-application-entry-point
 */
int WINAPI WinMain(HINSTANCE hInstance,
		HINSTANCE hPrevInstance,
		LPSTR lpCmdLine,
		int nCmdShow) {


	// window can only be created using one of the windows default color, this function overwrites a default color with my own color
	INT color = COLOR_APPWORKSPACE;
	COLORREF toset = WINDOWS_BACKGROUND_COLOR;
	if(!SetSysColors(1,&color,&toset)){
		MessageBox(NULL, "Error: Unable to set background color", "Lumi-Pins", MB_OK);
	}



	// create a window class main window
	const char CLASS_NAME[]  = "class0";
	WNDCLASSEXA  wc0 = { };
	wc0.cbSize = sizeof(WNDCLASSEX);	// default size
	wc0.lpfnWndProc = LumiWndProc;	// callback process
	wc0.hInstance     = hInstance;	// instance handle
	wc0.lpszClassName = CLASS_NAME;	// set class name
	wc0.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// class style, you can OR these macros
	wc0.cbClsExtra = 0;
	wc0.cbWndExtra = 0;
	wc0.lpszMenuName = "lumi_menu_rc";	// set menu resource
	wc0.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE+1);	// background color
	wc0.hCursor = LoadCursorA(NULL, IDC_ARROW);	//	default cursor
	wc0.hIcon = LoadIcon(NULL, IDI_APPLICATION); // class icon ***PLANNED***

	// register window class
	if (!RegisterClassExA(&wc0)){	// returns a class atom on success, 0 on failure
		MessageBox(NULL, "Error: RegisterClassExA returned 0", "Lumi-Pins", MB_OK);
		return false;
	}




	// https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-createwindowa
	HWND hwnd = CreateWindowExA(	// returns an handle
			0, // Extra Window styles
			CLASS_NAME,	// WNDCLASSEXA name
			"LumiPins", // Top bar name
			WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_CLIPCHILDREN , // Window styles
			CW_USEDEFAULT,CW_USEDEFAULT,CLIENTAREA_WIDTH,CLIENTAREA_HEIGHT, // X,Y,W,H
			NULL, // Parent handle
			NULL, // Menu handle
			hInstance, // Instance handle
			NULL // Passing value
	);

	// Check window creation, handle would be null on failure
	if (hwnd == NULL){
		MessageBox(NULL, "Error: CreateWindowExA returned NULL", "Lumi-Pins", MB_OK);
		return false;
	}


	ShowWindow(hwnd, nCmdShow);	// show window
	ShowWindow(::GetConsoleWindow(), SW_HIDE); // hide console if it shows
	UpdateWindow(hwnd); // sends WM_PAINT to draw client area


	// sent message loop to the callback function, WIN32 API stuff no need to change
	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	return false;
}

/*
 * The call back function for Windows application
 * https://msdn.microsoft.com/en-us/library/windows/desktop/ms633573%28v=vs.85%29.aspx?f=255&MSPPError=-2147217396
 */
LRESULT CALLBACK LumiWndProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
	switch(msg){
	case WM_CREATE: // Draw Buttons when created, these Buttons do not get redrawn through out life cycle
		Draw_Control(hwnd); // see function
		break;
	case WM_DESTROY: // When Window is destroyed, make sure to close the background thread as well
		PostQuitMessage(0);	// closes background thread
		return false;
	case WM_PAINT: // Redraw on this msg
		Draw_Control(hwnd); // see function
		break;
	case WM_COMMAND:	// When a menu item or a button is activated
		Handle_WM_COMMAND(hwnd, wParam, lParam); // see function
		break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}


/*
 * This function handles all the WM_COMMAND message, these messages are received when a control element or menu element is activated.
 * Parameter: Handle for window, wParam, lParam ( see https://docs.microsoft.com/en-us/windows/desktop/menurc/wm-command )
 * Return: None
 */
void Handle_WM_COMMAND(HWND hwnd, WPARAM wParam, LPARAM lParam){
	switch(HIWORD(wParam)){
	case BN_CLICKED:// menu or button
		switch(LOWORD(wParam)){ // identifier


		}

		break;
		case 1: // accelerator
			break;
		default:
			break;
	}
}

void Draw_Control(HWND hwnd){

	CreateWindowExA(
			0,
			"BUTTON",
			"Select File",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			BUTTON_SELECT_FILES_X,
			BUTTON_SELECT_FILES_Y,
			BUTTON_WIDTH,
			BUTTON_HIGHT,
			hwnd,
			(HMENU)IDM_SELECT_FILES,
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
			NULL
	);

	CreateWindowExA(
			0,
			"BUTTON",
			"Start Talking",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			BUTTON_START_TALKING_X,
			BUTTON_START_TALKING_Y,
			BUTTON_WIDTH,
			BUTTON_HIGHT,
			hwnd,
			(HMENU)IDM_SELECT_FILES,
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
			NULL
	);

	CreateWindowExA(
			0,
			"BUTTON",
			"Stop Talking",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			BUTTON_STOP_TALKING_X,
			BUTTON_STOP_TALKING_Y,
			BUTTON_WIDTH,
			BUTTON_HIGHT,
			hwnd,
			(HMENU)IDM_SELECT_FILES,
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
			NULL
	);

	CreateWindowExA(
			0,
			"BUTTON",
			"Stop Talking",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			BUTTON_STOP_TALKING_X,
			BUTTON_STOP_TALKING_Y,
			BUTTON_WIDTH,
			BUTTON_HIGHT,
			hwnd,
			(HMENU)IDM_SELECT_FILES,
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
			NULL
	);

	CreateWindowEx(WS_EX_CLIENTEDGE,
			"LISTBOX",
			NULL,
			WS_CHILD | WS_VISIBLE| WS_VSCROLL |ES_AUTOVSCROLL,
			LISTBOX_FILES_X, LISTBOX_FILES_Y, LISTBOX_FILES_W, LISTBOX_FILES_H,
			hwnd,
			NULL,
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
			NULL);

	CreateWindowEx(WS_EX_CLIENTEDGE,
			"Edit",
			NULL,
			WS_CHILD | WS_VISIBLE| WS_VSCROLL |ES_AUTOVSCROLL|ES_MULTILINE|ES_WANTRETURN,
			TEXTBOX_MAIN_X, TEXTBOX_MAIN_Y, TEXTBOX_MAIN_W, TEXTBOX_MAIN_H,
			hwnd,
			NULL,
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
			NULL);


}

