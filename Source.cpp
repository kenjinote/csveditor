#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "Comctl32")

#include <windows.h>
#include <commctrl.h>
#include "resource.h"

WCHAR szClassName[] = L"csveditor";

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND hEdit;
	static ULONGLONG xPos, xPosMax;
	static ULONGLONG yPos, yPosMax;
	static HPEN hPen;
	switch (msg)
	{
	case WM_CREATE:
		InitCommonControls();
		hPen = CreatePen(PS_SOLID, 1, RGB(192, 192, 192));
		break;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);

			RECT rect;
			GetClientRect(hWnd, &rect);

			HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

			for (int x = 0; x * 128 < rect.right; x++)
			{
				MoveToEx(hdc, x * 128, 0, 0);
				LineTo(hdc, x * 128, rect.bottom);
			}

			for (int y = 0; y * 32 < rect.bottom; y++)
			{
				MoveToEx(hdc, 0, y * 32, 0);
				LineTo(hdc, rect.right, y * 32);
			}

			SelectObject(hdc, hOldPen);

			WCHAR szText[1024];
			for (int y = 0; y * 32 < rect.bottom; y++) {
				for (int x = 0; x * 128 < rect.right; x++) {
					wsprintf(szText, L"(%d, %d)", x, y);
					TextOut(hdc, x * 128 + 1, y * 32 + 1, szText, lstrlen(szText));
				}
			}

			EndPaint(hWnd, &ps);
		}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_ALL:
			MessageBox(hWnd, L"すべて選択", 0, 0);
			break;
		case ID_CUT:
			MessageBox(hWnd, L"カット", 0, 0);
			break;
		case ID_COPY:
			MessageBox(hWnd, L"コピー", 0, 0);
			break;
		case ID_PASTE:
			MessageBox(hWnd, L"ペースト", 0, 0);
			break;
		case ID_DEL:
			MessageBox(hWnd, L"削除", 0, 0);
			break;
		case ID_UNDO:
			MessageBox(hWnd, L"元に戻す", 0, 0);
			break;
		case ID_REDO:
			MessageBox(hWnd, L"やり直し", 0, 0);
			break;
		case ID_FIND:
			MessageBox(hWnd, L"検索", 0, 0);
			break;
		case ID_REPLACE:
			MessageBox(hWnd, L"置換", 0, 0);
			break;
		case ID_NEXT:
			MessageBox(hWnd, L"次を検索", 0, 0);
			break;
		case ID_PREV:
			MessageBox(hWnd, L"前を検索", 0, 0);
			break;
		case ID_EDIT:
			MessageBox(hWnd, L"値を編集", 0, 0);
			break;
		case ID_NEW:
			MessageBox(hWnd, L"新規作成", 0, 0);
			break;
		case ID_OPEN:
			MessageBox(hWnd, L"開く", 0, 0);
			break;
		case ID_SAVE:
			MessageBox(hWnd, L"上書き保存", 0, 0);
			break;
		case ID_SAVEAS:
			MessageBox(hWnd, L"名前を付けて保存", 0, 0);
			break;
		case ID_EXIT:
			MessageBox(hWnd, L"終了", 0, 0);
			break;
		case ID_HEADER:
			MessageBox(hWnd, L"ヘッダー", 0, 0);
			break;
		case ID_LINE:
			MessageBox(hWnd, L"目盛り線", 0, 0);
			break;
		case ID_HELP:
			MessageBox(hWnd, L"ヘルプ", 0, 0);
			break;
		}
		break;
	case WM_DESTROY:
		DeleteObject(hPen);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPreInst, LPWSTR pCmdLine, int nCmdShow)
{
	MSG msg;
	WNDCLASS wndclass = {
		CS_HREDRAW | CS_VREDRAW,
		WndProc,
		0,
		0,
		hInstance,
		LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1)),
		LoadCursor(0,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		MAKEINTRESOURCE(IDR_MENU1),
		szClassName
	};
	RegisterClass(&wndclass);
	HWND hWnd = CreateWindowW(
		szClassName,
		L"csveditor",
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_HSCROLL | WS_VSCROLL,
		CW_USEDEFAULT,
		0,
		CW_USEDEFAULT,
		0,
		0,
		0,
		hInstance,
		0
	);
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	HACCEL hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));
	while (GetMessage(&msg, 0, 0, 0))
	{
		if (!TranslateAccelerator(hWnd, hAccel, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
}
