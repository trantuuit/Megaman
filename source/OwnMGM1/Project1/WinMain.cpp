#include<Windows.h>
#include"MGMForm.h"
#include"MGMGameTime.h"
#include"MGMGame.h"
#include"MGMDirectXTool.h"
#include"SelectionScreen.h"
#include"SelectionRectangle.h"
#include"KEY.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MGMForm::getInstance()->initHandleWindows(hInstance, nCmdShow); //Tạo cửa sổ
	DWORD timeSleep = 1000.0 / 1000;
	SelectionScreen *ss = new SelectionScreen();
	SelectionRectangle *sr = new SelectionRectangle();
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
			if (MGMGame::getInstance()->isStart)
			{
				sr->update();
				MGMDirectXTool::getInstance()->BeginGraphics();//bat dau ve len backbuffer
				ss->render();
				sr->render();
				MGMDirectXTool::getInstance()->EndGraphics();// ket thuc ve len backbuffer
				MGMDirectXTool::getInstance()->PresentBackBuffer();// swap backbuffer va man hinh

				if (!MGMGame::getInstance()->isStart)
				{
					MGMMap*map = MGMGame::getInstance()->map;
					if (map == MGMGame::getInstance()->mapCut)
					{
						Megaman::getInstance()->x = 22;
						Megaman::getInstance()->y = 111;
						MGMCamera::getInstance()->init(0, 232, BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT);
						/*Megaman::getInstance()->x = 1880;
						Megaman::getInstance()->y = 1400;
						MGMCamera::getInstance()->init(1780, 1460, BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT);*/
					}
					if (map == MGMGame::getInstance()->mapGut)
					{
						/*Megaman::getInstance()->x = 22;
						Megaman::getInstance()->y = 1100;
						MGMCamera::getInstance()->init(0, 1176, BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT);*/
					}
					for (int i = 0; i < map->nStage; i++)
					{
						if (MGMStage::checkMegamanInStage(Megaman::getInstance(), map->stages[i]))
							MGMStage::curStage = map->stages[i];
					}
				}
			}
			if (!MGMGame::getInstance()->isStart)
			{
				MGMGame::getInstance()->update(timeSleep);//update
				MGMDirectXTool::getInstance()->BeginGraphics();//bat dau ve len backbuffer
				MGMGame::getInstance()->render();
				MGMDirectXTool::getInstance()->EndGraphics();// ket thuc ve len backbuffer
				MGMDirectXTool::getInstance()->PresentBackBuffer();// swap backbuffer va man hinh
			}

		}
		else
			Sleep(timeDelay.tickPerFrame);

	}
}
