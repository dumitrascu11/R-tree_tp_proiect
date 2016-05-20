#include <windows.h>
#include"rtree.h"
const char g_szClassName[] = "myWindowClass";
#define IDC_MAIN_BUTTON	101			// Button identifier
#define IDC_HELP_BUTTON	102	
#define IDC_LOCATE_BUTTON 103
#define IDC_ADRESS_BUTTON 104
//#define IDC_HELP_EDIT	102			// Edit box identifier

HWND hEdit;

int ok_start = 0;
int poz_x=0 ;
int poz_y=0 ;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	PAINTSTRUCT Ps;


	switch (msg)
	{

	case WM_PAINT:
	{	HFONT	    font;
	hDC = BeginPaint(hwnd, &Ps);

	HPEN hLinePen;
	COLORREF qLineColor;
	qLineColor = RGB(255, 0, 0);
	hLinePen = CreatePen(PS_SOLID, 7, qLineColor);
	{
		int x1 = 10, x2 = 10, x3 = 1260, x4 = 680;

		font = CreateFont(3, 3, 0, 0,
			FW_NORMAL, FALSE, FALSE, FALSE,
			ANSI_CHARSET, OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_ROMAN,
			"Times New Roman");
		SelectObject(hDC, font);
		TextOut(hDC, 1320, 689, "Johnny", 6);
		DeleteObject(font);
		///de aici colorez
		HBRUSH BrushYellow = CreateSolidBrush(RGB(250, 255,0));
		HBRUSH      NewBrush;	
		POINT       Pt[4];
		NewBrush = CreateSolidBrush(RGB(255, 0, 0));
		SelectObject(hDC, NewBrush);
		Pt[0].x = x1; Pt[0].y = x2;
		Pt[1].x = x3; Pt[1].y = x2;
		Pt[2].x = x3; Pt[2].y = x4;
		Pt[3].x = x1; Pt[3].y = x4;
		Polygon(hDC, Pt, 4);
		DeleteObject(NewBrush);
	//		SelectObject(hDC, BrushYellow);
		//	NewBrush = CreateSolidBrush(RGB(255, 255, 255));
		SelectObject(hDC, NewBrush);
		x1 = 10; x2 = 10; x3 = 30; x4 = 30;
		Pt[0].x = x1; Pt[0].y = x2;
		Pt[1].x = x3; Pt[1].y = x2;
		Pt[2].x = x3; Pt[2].y = x4;
		Pt[3].x = x1; Pt[3].y = x4;
		Polygon(hDC, Pt, 4);
		MoveToEx(hDC, x1, x2, NULL);
		LineTo(hDC, x3, x2);
		LineTo(hDC, x3, x4);
		LineTo(hDC, x1, x4);
		LineTo(hDC, x1, x2);

	}
	EndPaint(hwnd, &Ps);
	break; }

	case WM_LBUTTONDOWN:
	{	if (ok_start == 1)
	{
		wchar_t waCoord[20];
		wsprintf((LPSTR)waCoord, ("(%i, %i)"), LOWORD(lParam), HIWORD(lParam));
		int msg_return = MessageBox(hwnd, (LPCSTR)waCoord, ("Ai ales coordonatele:"), MB_OKCANCEL);
		{	if (msg_return == IDOK)
		{
			poz_x = LOWORD(lParam);
			poz_y = HIWORD(lParam);
			hDC = BeginPaint(hwnd, &Ps);
			hDC = GetWindowDC(hwnd);
			TextOut(hDC, poz_x + 7, poz_y + 23, "x", 1);

			/*   char v[7];
			   itoa(poz_x, v, 10);

			   TextOut(hDC, poz_x + 7, poz_y + 23, v, lung_nr(poz_x));
			   TextOut(hDC, poz_x + 38, poz_y + 23, ";", 1);
			   itoa(poz_y, v, 10);
			   TextOut(hDC, poz_x + 40, poz_y + 23, v, lung_nr(poz_y));
			   EndPaint(hwnd, &Ps);*/
			ReleaseDC(hwnd, hDC);
		}
		if (msg_return == IDCANCEL)
		{
			int poz_x = 0;
			int poz_y = 0;
		}

		}

	}
	else MessageBox(NULL,
		(LPCSTR)"Nu ai citit Instructiunile!",
		"Atentie!!!",
		MB_ICONERROR);
	break;
	}
	case WM_CREATE:
	{/*HWND hWndButton = */CreateWindowEx(NULL,
		"BUTTON",
		"Start!",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		1265,
		10,
		80,
		24,
		hwnd,
		(HMENU)IDC_MAIN_BUTTON,
		GetModuleHandle(NULL),
		NULL);
	CreateWindowEx(NULL,
		"BUTTON",
		"Localizare",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		1265,
		50,
		80,
		24,
		hwnd,
		(HMENU)IDC_LOCATE_BUTTON,
		GetModuleHandle(NULL),
		NULL);
	CreateWindowEx(NULL,
		"BUTTON",
		"Adresa",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		1265,
		90,
		80,
		24,
		hwnd,
		(HMENU)IDC_ADRESS_BUTTON,
		GetModuleHandle(NULL),
		NULL);
	CreateWindowEx(NULL,
		"BUTTON",
		"Ajutor!",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		1265,
		130,
		80,
		24,
		hwnd,
		(HMENU)IDC_HELP_BUTTON,
		GetModuleHandle(NULL),
		NULL);


	}
		break;
	case WM_COMMAND:
	{ switch (wParam)
	{
	case IDC_MAIN_BUTTON:
	{	HFONT	    font;
	hDC = BeginPaint(hwnd, &Ps);
	hDC = GetWindowDC(hwnd);
	root = radacina("coord.txt");

	afisare_arbore(root, hDC);
	ok_start = 1;
	EndPaint(hwnd, &Ps);
	ReleaseDC(hwnd, hDC);
	break; }

	case IDC_HELP_BUTTON:
	{	char buffer[256];
	SendMessage(hEdit,
		WM_GETTEXT,
		sizeof(buffer) / sizeof(buffer[0]),
		reinterpret_cast<LPARAM>(buffer));
	MessageBox(NULL,
		(LPCSTR)fisier_help("ajutor.txt"),
		"Ajutor",
		MB_ICONINFORMATION);
	break; }
	case IDC_LOCATE_BUTTON:
	{if (poz_x != 0 && poz_y != 0)

	{
		MessageBox(NULL,
			(LPCSTR)nume_localizare(root, poz_x, poz_y),
			"Zona in care te aflii este:",
			MB_ICONINFORMATION);
	}
	else MessageBox(NULL,
		(LPCSTR)"Nu ai citit Instructiunile!",
		"Atentie!!!",
		MB_ICONERROR);
	}	break;
	
	case IDC_ADRESS_BUTTON:
	{if (poz_x != 0 && poz_y != 0)

	{
		MessageBox(NULL,
			(LPCSTR)nume_adresa(root, poz_x, poz_y),
			"Adresa zonei in care te aflii este:",
			MB_ICONINFORMATION);
	}
	 else MessageBox(NULL,
		(LPCSTR)"Nu ai citit Instructiunile!",
		"Atentie!!!",
		MB_ICONERROR);
	}
	break; }
	}break;
	case WM_DESTROY:
		PostQuitMessage(WM_QUIT);
		break;

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;


}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;

	//Step 1: Registering the Window Class
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// Step 2: Creating the Window
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		"R-tree Application",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 1366, 768,
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// Step 3: The Message Loop
	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}