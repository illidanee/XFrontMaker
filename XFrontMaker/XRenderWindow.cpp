#include "XRenderWindow.h"

#include "XResource.h"
#include "XFrontMaker.h"

namespace Smile
{
	XFrontMaker _Maker;

	GLuint _texture;

	void Smile::XRenderWindow::Begin()
	{
		_Maker.Init("../Resources/simsun.ttc");
		//_Maker.Scan()
		char* pBuffer;
		int w, h;
		_texture = _Maker.CreateTex("./0.png", w, h);
		//glEnable(GL_TEXTURE_2D);
		//XResource::LoadTextureFile("./0.png", &pBuffer, &w, &h);
		//{
		//	glGenTextures(1, &_texture);
		//	glBindTexture(GL_TEXTURE_2D, _texture);
		//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pBuffer);
		//	glBindTexture(GL_TEXTURE_2D, 0);
		//}
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

		_Maker.Render(_texture);
	}

	void Smile::XRenderWindow::End()
	{
		glDeleteTextures(1, &_texture);

		_Maker.Done();
	}
}

