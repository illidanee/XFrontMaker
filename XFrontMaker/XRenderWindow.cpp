#include "XRenderWindow.h"

#include "XFrontMaker.h"

namespace Smile
{
	XFrontMaker _Maker;

	GLuint _texture;

	void Smile::XRenderWindow::Begin()
	{
		_Maker.Init("../Resources/simsun.ttc");
		_Maker.Scan(L"1234567890OpenGL除了读取图像内存显示图像之外还有另一种图像显示方式：纹理显示。纹理显示相比于读内存直接显示稍复杂，读内存显示只需要glDrawPixels ()函数即可实现，纹理显示则需要设置更多参数，当然纹理显示的好处是让显示变得更灵活。由于涉及读取图片，依旧使用OpenCV图像读取");
		_Maker.SaveAll();
		_Maker.InitRender();
	}

	void Smile::XRenderWindow::Render()
	{
		//清空
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//正交投影绘制平面
		glViewport(0, 0, _w, _h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, _w, 0, _h, -100, 100);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//_Maker.Render(0);
		_Maker.Write(L"0OpenGL除了读  取图像内存显示图像", 100, 100, 255, 0, 0, 255);
	}

	void Smile::XRenderWindow::End()
	{
		glDeleteTextures(1, &_texture);

		_Maker.Done();
	}
}

