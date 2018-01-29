#include "XGLWindow.h"

namespace Smile
{
/*
	静态区
*/
	std::map<LPCTSTR, WNDCLASSEX*> XGLWindow::_WCCache;
	std::map<HWND, XGLWindow*> XGLWindow::_WindowCache;
	HINSTANCE XGLWindow::_hInstance = 0;
	CRITICAL_SECTION XGLWindow::_CS;

	void XGLWindow::RegisterInstance(HINSTANCE hInstance)
	{
		_hInstance = hInstance;
	}

	void XGLWindow::ClearInstance()
	{
		_hInstance = 0;
	}

	void XGLWindow::RegisterWndClass(LPCTSTR wcName)
	{
		if (_WCCache.find(wcName) != _WCCache.end())
			return;

		WNDCLASSEX* pWC = new WNDCLASSEX;

		memset(pWC, 0, sizeof(WNDCLASSEX));
		pWC->cbSize = sizeof(WNDCLASSEX);
		pWC->cbClsExtra = 0;
		pWC->cbWndExtra = 0;
		pWC->hbrBackground = 0;
		pWC->hCursor = 0;
		pWC->hIcon = 0;
		pWC->hIconSm = 0;
		pWC->hInstance = _hInstance;
		pWC->lpfnWndProc = WindowProc;
		pWC->lpszClassName = wcName;
		pWC->lpszMenuName = 0;
		pWC->style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;

		RegisterClassEx(pWC);
	
		_WCCache.insert(std::pair<LPCTSTR, WNDCLASSEX*>(wcName, pWC));
	}

	void XGLWindow::ClearWndClass()
	{
		for (std::map<LPCTSTR, WNDCLASSEX*>::iterator it = _WCCache.begin(); it != _WCCache.end(); ++it)
		{
			UnregisterClass(it->first, _hInstance);
			delete it->second;
		}

		_WCCache.clear();
	}

	void XGLWindow::Update()
	{
		InitializeCriticalSection(&_CS);

		for (std::map<HWND, XGLWindow*>::iterator it = _WindowCache.begin(); it != _WindowCache.end(); ++it)
		{
			EnterCriticalSection(&_CS);

			it->second->BeginInner();
			UpdateWindow(it->first);
			ShowWindow(it->first, SW_SHOW);

			LeaveCriticalSection(&_CS);
		}

		MSG msg = { 0 };
		while (WM_QUIT != msg.message)
		{
			if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				//绘制
				for (std::map<HWND, XGLWindow*>::iterator it = _WindowCache.begin(); it != _WindowCache.end(); ++it)
				{
					EnterCriticalSection(&_CS);

					it->second->RenderInner();

					LeaveCriticalSection(&_CS);
				}
				
				//销毁死亡窗口
				for (std::map<HWND, XGLWindow*>::iterator it = _WindowCache.begin(); it != _WindowCache.end(); )
				{
					if (it->second->_die)
					{
						EnterCriticalSection(&_CS);

						it->second->EndInner();

						LeaveCriticalSection(&_CS);

						//DestroyWindow()函数发出 WM_DESTROY 消息，当收到此消息也就说明调用了DestroyWindow()函数。
						//DestroyWindow(it->first);
						//如果此处不delete,则需要调用者删除。这样就需要把析构函数公开。
						delete it->second;
						it = _WindowCache.erase(it);
					}
					else
					{
						++it;
					}
				}

				//判断退出
				if (_WindowCache.size() == 0)
					PostQuitMessage(0);

				Sleep(16);
			}
		}
		
		//Bug
		//推出循环时_WindowCache为空了。此处永远执行不到。
		//for (std::map<HWND, XGLWindow*>::iterator it = _WindowCache.begin(); it != _WindowCache.end(); ++it)
		//{
		//	EnterCriticalSection(&_CS);

		//	it->second->EndInner();

		//	LeaveCriticalSection(&_CS);
		//}

		DeleteCriticalSection(&_CS);
	}

	void XGLWindow::_CheckError(const char *file, const int line)
	{
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
		{
			switch (error)
			{
			case GL_INVALID_ENUM:                  
				MessageBox(0, _T("INVALID_ENUM!"), 0, MB_OK);
				break;
			case GL_INVALID_VALUE:                
				MessageBox(0, _T("INVALID_VALUE!"), 0, MB_OK);
				break; 
			case GL_INVALID_OPERATION:             
				MessageBox(0, _T("INVALID_OPERATION!"), 0, MB_OK);
				break; 
			case GL_STACK_OVERFLOW:                
				MessageBox(0, _T("STACK_OVERFLOW!"), 0, MB_OK);
				break; 
			case GL_STACK_UNDERFLOW:               
				MessageBox(0, _T("STACK_UNDERFLOW!"), 0, MB_OK);
				break; 
			case GL_OUT_OF_MEMORY:                 
				MessageBox(0, _T("OUT_OF_MEMORY!"), 0, MB_OK);
				break; 
			case GL_INVALID_FRAMEBUFFER_OPERATION: 
				MessageBox(0, _T("INVALID_FRAMEBUFFER_OPERATION!"), 0, MB_OK);
				break; 
			default:
				MessageBox(0, _T("Other Error!"), 0, MB_OK);
			}
		}
	}

	LRESULT CALLBACK XGLWindow::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		if (uMsg == WM_CREATE)
		{
			LPCREATESTRUCT pData = (LPCREATESTRUCT)lParam;
			if (pData)
			{
				XGLWindow* pWindow = (XGLWindow*)pData->lpCreateParams;
				if (pWindow)
				{
					SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pWindow);
				}
			}
		}
		else
		{
			XGLWindow* pThis = (XGLWindow*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
			if (pThis)
			{
				//调用自身事件处理。
				pThis->Event(hWnd, uMsg, wParam, lParam);

				if (uMsg == WM_CLOSE && pThis->_die == false)
				{
					pThis->_die = true;
				}
			}
		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}


/*
	成员区
*/
	XGLWindow::XGLWindow()
	{

	}

	XGLWindow::XGLWindow(const XGLWindow& that)
	{

	}

	XGLWindow XGLWindow::operator = (const XGLWindow& that)
	{
		return *this;
	}

	XGLWindow::~XGLWindow()
	{

	}

	void XGLWindow::Construct(LPCTSTR wcName, LPCTSTR wName, int x, int y, int w, int h)
	{
		_w = w;
		_h = h;

		//计算窗口大小和位置
		int screenW = GetSystemMetrics(SM_CXSCREEN);
		int screenH = GetSystemMetrics(SM_CYSCREEN);

		RECT rect
		{
			(screenW - w) / 2,
			(screenH - h) / 2,
			rect.left + w,
			rect.top + h
		};

		AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, FALSE, 0);

		/** 创建OpenGL环境 **/
		if (x == 0 && y == 0)
			_hWnd = CreateWindowEx(0, wcName, wName, WS_OVERLAPPEDWINDOW, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, 0, 0, this);
		else
			_hWnd = CreateWindowEx(0, wcName, wName, WS_OVERLAPPEDWINDOW, x, y, rect.right - rect.left, rect.bottom - rect.top, 0, 0, 0, this);

		_die = false;
	
		_content.Construct(_hWnd);


		/** 创建OpenGL MSAA环境 **/
		_die = true;

		DestroyWindow(_hWnd);

		if (x == 0 && y == 0)
			_hWnd = CreateWindowEx(0, wcName, wName, WS_OVERLAPPEDWINDOW, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, 0, 0, this);
		else
			_hWnd = CreateWindowEx(0, wcName, wName, WS_OVERLAPPEDWINDOW, x, y, rect.right - rect.left, rect.bottom - rect.top, 0, 0, 0, this);

		_die = false;

		_content.ConstructMSAA(_hWnd);

		CheckError();
	}

	void XGLWindow::Register()
	{
		if (_WindowCache.find(_hWnd) != _WindowCache.end())
			return;

		_WindowCache.insert(std::pair<HWND, XGLWindow*>(_hWnd, this));
	}

	void XGLWindow::BeginInner()
	{
		_content.MakeCurrent();
		_content.Begin();
		
		Begin();
		CheckError();
	}

	void XGLWindow::RenderInner()
	{
		_content.MakeCurrent();
		Render();
		_content.SwapBuffer();

		CheckError();
	}

	void XGLWindow::EndInner()
	{
		_content.MakeCurrent();

		End();
		CheckError();

		_content.End();
	}

	void XGLWindow::Event(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{

	}

	void XGLWindow::Begin()
	{
		
	}

	void XGLWindow::Render()
	{	

	}

	void XGLWindow::End()
	{
		
	}
}