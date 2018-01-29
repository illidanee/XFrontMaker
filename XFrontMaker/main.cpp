#include <tchar.h>
#include <windows.h>

#include "XRenderWindow.h"

using namespace Smile;


int __stdcall WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	//注册窗口信息。
	XGLWindow::RegisterInstance(hInstance);
	XGLWindow::RegisterWndClass(_T("illidan"));

	//创建窗口
	XGLWindow* pWindow = XGLWindow::Create<XRenderWindow>(_T("illidan"), _T("主窗口"), 100, 100, 1280, 800);

	XGLWindow::Update();

	//销毁窗口信息
	XGLWindow::ClearWndClass();
	XGLWindow::ClearInstance();

	return 0;
}