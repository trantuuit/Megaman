#include<Windows.h>
#include"MGMForm.h"
#include"MGMGameTime.h"
#include"MGMGame.h"
#include"MGMDirectXTool.h"
#include"KEY.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MGMForm::getInstance()->initHandleWindows(hInstance, nCmdShow); //Tạo cửa sổ
	DWORD timeSleep = 1000.0 / FPS;

	//Khoi tao thoi gian giua 2 frame = timeSleep
	MGMGameTime timeDelay(timeSleep);
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	MGMGame::getInstance()->init(); //Init game
	CKeyboard::Create(hInstance, MGMForm::getInstance()->getHandleWindow());

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (timeDelay.atTime())
		{
			CKeyboard::getInstance()->PollKeyboard();
			KEY::getInstance()->update();
			MGMGame::getInstance()->update(timeSleep);//update
			MGMDirectXTool::getInstance()->BeginGraphics();//bat dau ve len backbuffer
			MGMGame::getInstance()->render();
			MGMDirectXTool::getInstance()->EndGraphics();// ket thuc ve len backbuffer
			MGMDirectXTool::getInstance()->PresentBackBuffer();// swap backbuffer va man hinh
		}
		else
			Sleep(timeDelay.tickPerFrame);

	}

	//delete instance

}
