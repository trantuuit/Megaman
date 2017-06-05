#include "MGMForm.h"


MGMForm::MGMForm(void)
{
}
MGMForm* MGMForm::instance = 0;
MGMForm *MGMForm::getInstance()
{
	if (instance == 0) instance = new MGMForm();
	return instance;
}

/*Hàm xử lý thông điệp*/
LRESULT MGMForm::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

/*Khởi tạo cửa sổ*/
void MGMForm::initHandleWindows(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(wcex));

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszClassName = MGMFORM_CLASS_NAME;
	RegisterClassEx(&wcex);
	HWND hWnd = CreateWindow(MGMFORM_CLASS_NAME, TITLE_STR, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, FORM_WIDTH, FORM_HEIGHT, 0, 0, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	this->hWnd = hWnd;
}
HWND MGMForm::getHandleWindow()
{
	return hWnd;
}
MGMForm::~MGMForm(void)
{
	if (instance != 0) delete instance;
}
