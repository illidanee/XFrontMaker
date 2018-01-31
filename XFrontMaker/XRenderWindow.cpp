#include "XRenderWindow.h"

#include "XFrontMaker.h"

namespace Smile
{
	XFrontMaker _Maker;

	GLuint _texture;

	void Smile::XRenderWindow::Begin()
	{
		_Maker.Init("../Resources/simsun.ttc");
		_Maker.Scan(L"1234567890OpenGL���˶�ȡͼ���ڴ���ʾͼ��֮�⻹����һ��ͼ����ʾ��ʽ��������ʾ��������ʾ����ڶ��ڴ�ֱ����ʾ�Ը��ӣ����ڴ���ʾֻ��ҪglDrawPixels ()��������ʵ�֣�������ʾ����Ҫ���ø����������Ȼ������ʾ�ĺô�������ʾ��ø��������漰��ȡͼƬ������ʹ��OpenCVͼ���ȡ");
		_Maker.SaveAll();
		_Maker.InitRender();
	}

	void Smile::XRenderWindow::Render()
	{
		//���
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//����ͶӰ����ƽ��
		glViewport(0, 0, _w, _h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, _w, 0, _h, -100, 100);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//_Maker.Render(0);
		_Maker.Write(L"0OpenGL���˶�  ȡͼ���ڴ���ʾͼ��", 100, 100, 255, 0, 0, 255);
	}

	void Smile::XRenderWindow::End()
	{
		glDeleteTextures(1, &_texture);

		_Maker.Done();
	}
}

