#include "XRenderWindow.h"

#include "XFrontMaker.h"

namespace Smile
{
	XFrontMaker _Maker;

	GLuint _texture;

	void Smile::XRenderWindow::Begin()
	{
		_Maker.Init("../Resources/simsun.ttc", 20);
		_Maker.ScanEx(L"字体是一组可以被显示和打印的多样的字符映像，在单个字体中共享一些共有的特性，包括外表、风格、衬线等。按印刷领域的说法，它必须区别一个字体 家族和多种字体外观，后者通常是从同样的模板而来，但是风格不同。例如，Palatino Regular 和 Palatino Italic是两种不同的外观，但是属于同样的家族Palatino单个字体术语根据上下文既可以指家族也可指外观。例如，大多文字处理器的用户用字体指不同的字体家族，然而，大多这些家族根据它们的格式会通过多 个数据文件实现。对于 TrueType来讲，通常是每个外观一个文件（arial.ttf对应Arial Regular外观，ariali.ttf对应Arial Italic外观）这个文件也叫字体，但是实际上只是一个字体外观数字字体是一个可以包含一个和多个字体外观的数据文件，它们每个都包含字符映像、字符度量，以及其他各种有关文本布局和特定字符编码的重要信息。 对有些难用的格式，像Adobe的Type1，一个字体外观由几个文件描述（一个包含字符映象，一个包含字符度量等）。在这里我们忽略这种情况，只考虑一 个外观一个文件的情况，不过在FT2.0中，能够处理多文件字体");
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

		_Maker.Render(0);
		_Maker.Write(L"12345, OpenGL Start! 你好中国。", 100, 200, 0, 0, 255, 255);
	}

	void Smile::XRenderWindow::End()
	{
		glDeleteTextures(1, &_texture);

		_Maker.Done();
	}
}

