#pragma once

#include <vector>

#include <tchar.h>
#include <windows.h>
#include <gl/glew.h>
#include <gl/wglew.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_BITMAP_H

#include "XMath.h"

namespace Smile
{
	struct XVertexInfo
	{
		XVec3f _Pos;
		XVec2f _UV;
		BGRA8U _Color;
	};

	struct XFrontCharInfo
	{
		bool _Found;
		int _TexIndex;
		int _X;
		int _Y;
		unsigned int _Width;
		unsigned int _Height;
		int _BearingX;
		int _BearingY;
		long _AdvanceX;
		long _AdvanceY;

		XFrontCharInfo()
		{
			_Found = false;
			_TexIndex = 0;
			_X = 0;
			_Y = 0;
			_Width = 0;
			_Height = 0;
			_BearingX = 0;
			_BearingY = 0;
			_AdvanceX = 0;
			_AdvanceY = 0;
		}
	};


	/****************************************************************************************************************
	 *
	 *    Brief   : �������Ҫ��̬���ɡ�ʹ��ջ�ռ�ᱨ��
	 *
	 ****************************************************************************************************************/
	class XFrontMaker
	{
	public:
		XFrontMaker();
		~XFrontMaker();

		void Init(const char* pFront, int size = 20);
		void Done();
		void Scan(wchar_t* pStr);
		void ScanChar(wchar_t c);
		void Write(wchar_t* pStr, int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a);

		int GetTexNum();
		void Save(unsigned int index);
		void SaveAll();
		void InitRender();
		void Render(unsigned int index);

		GLuint CreateTexture(unsigned int index);

		void _CheckError();

	private:
		//FT��
		FT_Library _Library;
		FT_Face _Face;

		//�����С
		int _Size;

		//�ַ�����
		XFrontCharInfo _CharInfos[1 << 16];

		//������
		int _TextureW;
		int _TextureH;

		std::vector<GLuint> _AllTextures;
		int _CurTextureIndex;

		int _CurTextureOffsetX;
		int _CurTextureOffsetY;

		//��Ⱦ����
		std::vector<GLuint> _AllRenderTextures;

		//���ƻ���
		XVertexInfo _VertexBuffer[1 << 16];
	};

}


