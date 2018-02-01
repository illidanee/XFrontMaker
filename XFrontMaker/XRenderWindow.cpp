#include "XRenderWindow.h"

#include "XFrontMaker.h"

namespace Smile
{
	XFrontMaker _Maker;

	GLuint _texture;

	void Smile::XRenderWindow::Begin()
	{
		_Maker.Init("../Resources/simsun.ttc", 20);
		_Maker.ScanEx(L"������һ����Ա���ʾ�ʹ�ӡ�Ķ������ַ�ӳ���ڵ��������й���һЩ���е����ԣ����������񡢳��ߵȡ���ӡˢ�����˵��������������һ������ ����Ͷ���������ۣ�����ͨ���Ǵ�ͬ����ģ����������Ƿ��ͬ�����磬Palatino Regular �� Palatino Italic�����ֲ�ͬ����ۣ���������ͬ���ļ���Palatino��������������������ļȿ���ָ����Ҳ��ָ��ۡ����磬������ִ��������û�������ָ��ͬ��������壬Ȼ���������Щ����������ǵĸ�ʽ��ͨ���� �������ļ�ʵ�֡����� TrueType������ͨ����ÿ�����һ���ļ���arial.ttf��ӦArial Regular��ۣ�ariali.ttf��ӦArial Italic��ۣ�����ļ�Ҳ�����壬����ʵ����ֻ��һ�������������������һ�����԰���һ���Ͷ��������۵������ļ�������ÿ���������ַ�ӳ���ַ��������Լ����������й��ı����ֺ��ض��ַ��������Ҫ��Ϣ�� ����Щ���õĸ�ʽ����Adobe��Type1��һ����������ɼ����ļ�������һ�������ַ�ӳ��һ�������ַ������ȣ������������Ǻ������������ֻ����һ �����һ���ļ��������������FT2.0�У��ܹ�������ļ�����");
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

		_Maker.Render(0);
		_Maker.Write(L"12345, OpenGL Start! ����й���", 100, 200, 0, 0, 255, 255);
	}

	void Smile::XRenderWindow::End()
	{
		glDeleteTextures(1, &_texture);

		_Maker.Done();
	}
}

