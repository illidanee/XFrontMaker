#include <tchar.h>
#include <windows.h>

#include "XRenderWindow.h"

using namespace Smile;


int __stdcall WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	//ע�ᴰ����Ϣ��
	XGLWindow::RegisterInstance(hInstance);
	XGLWindow::RegisterWndClass(_T("illidan"));

	//��������
	XGLWindow* pWindow = XGLWindow::Create<XRenderWindow>(_T("illidan"), _T("������"), 100, 100, 1280, 800);

	XGLWindow::Update();

	//���ٴ�����Ϣ
	XGLWindow::ClearWndClass();
	XGLWindow::ClearInstance();

	return 0;
}