#pragma once

#include <vector>

#include "XGLContent.h"

#include <FreeImage.h>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace Smile
{
	struct XVertexInfo
	{
		float _X, _Y, _Z;
		float _U, _V;
	};

	struct XFrontCharInfo
	{
		bool _Found;
		int _TexIndex;
		int _X;
		int _Y;
		int _Width;
		int _Height;
		int _BearingX;
		int _BearingY;
		int _AdvanceX;
		int _AdvanceY;

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

	class XFrontMaker
	{
	public:
		XFrontMaker();
		~XFrontMaker();

		void Init(const char* pFront);
		void Done();
		void Scan(wchar_t* pStr);
		void ScanChar(wchar_t c);

		int GetTexNum();
		void Save(unsigned int index);
		void SaveAll();
		void Render(GLuint tex);

		GLuint CreateTex(const char* pTex, int& w, int& h);

	private:
		FT_Library _Library;
		FT_Face _Face;

		unsigned int _Size;

		XFrontCharInfo _CharInfos[1 << 16];

		unsigned int _TextureW;
		unsigned int _TextureH;

		std::vector<GLuint> _AllTextures;
		unsigned int _CurTextureIndex;

		unsigned int _CurTextureOffsetX;
		unsigned int _CurTextureOffsetY;
	};

}


