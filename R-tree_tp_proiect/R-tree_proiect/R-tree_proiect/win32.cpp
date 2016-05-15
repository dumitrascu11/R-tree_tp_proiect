#include <windows.h>
#include"rtree.h"
const char g_szClassName[] = "myWindowClass";
#define IDC_MAIN_BUTTON	101			// Button identifier
//#define IDC_MAIN_EDIT	102			// Edit box identifier
///HWND hEdit;




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

		font = CreateFont(8, 5, 0, 0,
			FW_NORMAL, FALSE, FALSE, FALSE,
			ANSI_CHARSET, OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_ROMAN,
			"Times New Roman");
		SelectObject(hDC, font);
		TextOut(hDC, x1, x2 - 8, "Johnny Carson", 13);
		DeleteObject(font);

		MoveToEx(hDC, x1, x2, NULL);
		LineTo(hDC, x3, x2);
		LineTo(hDC, x3, x4);
		LineTo(hDC, x1, x4);
		LineTo(hDC, x1, x2);

		/*x1 = 30, x2 = 30, x3 = 548, x4 = 338;
		MoveToEx(hDC, x1, x2, NULL);
		LineTo(hDC, x3, x2);
		LineTo(hDC, x3, x4);
		LineTo(hDC, x1, x4);
		LineTo(hDC, x1, x2);*/




	}
	EndPaint(hwnd, &Ps);
	break; }

	case WM_LBUTTONDOWN:
	{
		 int iPosX = LOWORD(lParam);
		 int iPosY = HIWORD(lParam);
         wchar_t waCoord[20];
	  /*   wsprintf((LPSTR)waCoord, ("(%i, %i)"), iPosX, iPosY);
	    ::MessageBox(hwnd, (LPCSTR)waCoord, ("Ai ales coordonatele:"), MB_OK);*/
       {
        hDC = BeginPaint(hwnd, &Ps);
	    hDC = GetWindowDC(hwnd);
	    //TextOut(hDC, iPosX + 7, iPosY + 23, "x",1);

	   char v[7];
	   itoa(iPosX, v, 10);

	   TextOut(hDC, iPosX + 7, iPosY + 23, v, lung_nr(iPosX));
	   TextOut(hDC, iPosX + 38, iPosY + 23, ";", 1);
 	   itoa(iPosY, v, 10);
	   TextOut(hDC, iPosX + 40, iPosY + 23, v, lung_nr(iPosY));
      EndPaint(hwnd, &Ps);
	   ReleaseDC(hwnd, hDC);
						   }
      break;
	}
	case WM_CREATE:
	{HWND hWndButton = CreateWindowEx(NULL,
		"BUTTON",
		"Start",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		1265,
		10,
		80,
		24,
		hwnd,
		(HMENU)IDC_MAIN_BUTTON,
		GetModuleHandle(NULL),
		NULL);

	}
		break;
	case WM_COMMAND:
	{	case IDC_MAIN_BUTTON:
	{	hDC = BeginPaint(hwnd, &Ps);
	hDC = GetWindowDC(hwnd);
	/**char buffer[256];
	SendMessage(hEdit,
	WM_GETTEXT,
	sizeof(buffer)/sizeof(buffer[0]),
	reinterpret_cast<LPARAM>(buffer));
	MessageBox(NULL,
	"Felicitari!!!",
	"Information",
	MB_ICONINFORMATION);*/
	root = radacina("coord.txt");

	afisare_arbore(root, hDC);
	EndPaint(hwnd, &Ps);
	ReleaseDC(hwnd, hDC);

	}
		break; }break;
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
		CW_USEDEFAULT, CW_USEDEFAULT, 240, 120,
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