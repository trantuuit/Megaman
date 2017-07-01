#include<Windows.h>
#include"MGMWindow.h"
#include"MGMGameTime.h"
#include"MGMGame.h"
#include"MGMEngine.h"
#include"SelectionScreen.h"
#include"SelectionRectangle.h"
#include"GameOverMenu.h"
#include"MGMAudioManager.h"
#include"KeyCheck.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MGMWindow::getInstance()->initHandleWindows(hInstance, nCmdShow); //Tạo cửa sổ
	DWORD timeSleep = 1000.0 / FPS;
	SelectionScreen *ss = new SelectionScreen();
	SelectionRectangle *sr = new SelectionRectangle();

	MGMGameTime timeDelay(timeSleep);
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	MGMGame::getInstance()->init(); //Init game
	CKeyboard::Create(hInstance, MGMWindow::getInstance()->getHandleWindow());
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (timeDelay.at())
		{
			CKeyboard::getInstance()->PollKeyboard();
			KeyCheck::getInstance()->update();
			if (MGMGame::getInstance()->isStart)
			{
				sr->update();
				MGMEngine::getInstance()->BeginGraphics();//bat dau ve len backbuffer
				ss->render();
				sr->render();
				MGMEngine::getInstance()->EndGraphics();// ket thuc ve len backbuffer
				MGMEngine::getInstance()->PresentBackBuffer();// swap backbuffer va man hinh

				if (!MGMGame::getInstance()->isStart)
				{
					
					MGMMap*map = MGMGame::getInstance()->map;
					if (map == MGMGame::getInstance()->mapCut)
					{
						Megaman::getInstance()->x = 22;
						Megaman::getInstance()->y = 111;
						Megaman::getInstance()->map = 1;
						MGMCamera::getInstance()->init(0, 232, BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT);
					}
					if (map == MGMGame::getInstance()->mapGut)
					{
						
						Megaman::getInstance()->x = 22;
						Megaman::getInstance()->y = 1100;
						Megaman::getInstance()->map = 2;
						MGMCamera::getInstance()->init(0, 1176, BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT);
						
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
				GameOverMenu::getInstance()->update();

				if (GameOverMenu::getInstance()->isOpen){
					MGMEngine::getInstance()->BeginGraphics();//bat dau ve len backbuffer
					GameOverMenu::getInstance()->render();
					MGMEngine::getInstance()->EndGraphics();// ket thuc ve len backbuffer
					MGMEngine::getInstance()->PresentBackBuffer();// swap backbuffer va man hinh

				}
				else{
					MGMGame::getInstance()->update(timeSleep);//update
					MGMEngine::getInstance()->BeginGraphics();//bat dau ve len backbuffer
					MGMGame::getInstance()->render();
					MGMEngine::getInstance()->EndGraphics();// ket thuc ve len backbuffer
					MGMEngine::getInstance()->PresentBackBuffer();// swap backbuffer va man hinh
				}
			}

		}
	}
}
