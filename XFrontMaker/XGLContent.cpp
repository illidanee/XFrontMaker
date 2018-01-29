#include "XGLContent.h"

namespace Smile
{
	XGLContent::XGLContent()
	{
		_hWnd = 0;
		_hDC = 0;
		_hGLRC = 0;
	}

	XGLContent::~XGLContent()
	{

	}

	void XGLContent::Construct(HWND hWnd)
	{
		//初始化OpenGL环境
		_hWnd = hWnd;
		_hDC = GetDC(_hWnd);

		PIXELFORMATDESCRIPTOR pfd;
		memset(&pfd, 0, sizeof(pfd));
		pfd.nSize = sizeof(pfd);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;
		pfd.cDepthBits = 24;
		pfd.cStencilBits = 8;
		pfd.iLayerType = PFD_MAIN_PLANE;

		int iPixelFormat = ChoosePixelFormat(_hDC, &pfd);
		BOOL res = SetPixelFormat(_hDC, 60, &pfd);

		_hGLRC = wglCreateContext(_hDC);

		//设置当前
		MakeCurrent();

		//初始化OpenGL扩展环境  -- 注：必须在MakeCurrent()后才能初始化成功。
		glewInit();
	}

	void XGLContent::ConstructMSAA(HWND hWnd)
	{
		//初始化OpenGL环境
		_hWnd = hWnd;
		_hDC = GetDC(_hWnd);

		int iPixelFormat = GetMultiSamplePixelFormat();
		if (!iPixelFormat)
		{
			Construct(_hWnd);
			return;
		}

		PIXELFORMATDESCRIPTOR pfd;
		DescribePixelFormat(_hDC, iPixelFormat, sizeof(pfd), &pfd);
		BOOL res = SetPixelFormat(_hDC, iPixelFormat, &pfd);

		int contexAttribs[] =
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
			WGL_CONTEXT_MINOR_VERSION_ARB, 3,
			WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
			NULL
		};
		_hGLRC = wglCreateContextAttribsARB(_hDC, 0, contexAttribs);

		//设置当前
		MakeCurrent();
	}

	void XGLContent::Begin()
	{
		//设置垂直同步 -- 注：需要头文件<gl/wglew.h>
		wglSwapIntervalEXT(1);
	}

	void XGLContent::MakeCurrent()
	{
		//设置当前
		wglMakeCurrent(_hDC, _hGLRC);
	}

	void XGLContent::SwapBuffer()
	{
		SwapBuffers(_hDC);
	}

	void XGLContent::End()
	{
		wglMakeCurrent(0, 0);
		wglDeleteContext(_hGLRC);
		_hGLRC = 0;
		ReleaseDC(_hWnd, _hDC);
		_hDC = 0;
		_hWnd = 0;
	}

	int XGLContent::GetMultiSamplePixelFormat()
	{
		if (wglChoosePixelFormatARB == 0)
			return 0;

		int iAttributes[] = 
		{
			WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
			WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
			WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
			WGL_SWAP_METHOD_ARB, WGL_SWAP_EXCHANGE_ARB,
			WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
			WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
			WGL_SAMPLES_ARB, 8,
			WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
			WGL_RED_BITS_ARB, 8,
			WGL_GREEN_BITS_ARB, 8,
			WGL_BLUE_BITS_ARB, 8,
			WGL_ALPHA_BITS_ARB, 8,
			WGL_DEPTH_BITS_ARB, 24,
			WGL_STENCIL_BITS_ARB, 8,
			NULL, NULL
		};

		int iPixelFormat;
		UINT num;
		BOOL bRes = wglChoosePixelFormatARB(_hDC, iAttributes, NULL, 1, &iPixelFormat, &num);
		if (bRes && iPixelFormat >= 1 && num >= 1)
		{
			return iPixelFormat;
		}

		return 0;
	}
}