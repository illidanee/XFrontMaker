#include "XFrontMaker.h"

namespace Smile
{
	XFrontMaker::XFrontMaker()
	{

	}

	XFrontMaker::~XFrontMaker()
	{

	}

	void XFrontMaker::Init(const char* pFront)
	{
		glEnable(GL_TEXTURE_2D);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		FT_Init_FreeType(&_Library);
		FT_New_Face(_Library, pFront, 0, &_Face);
		FT_Select_Charmap(_Face, FT_ENCODING_UNICODE);
		_Size = 18;
		FT_Set_Pixel_Sizes(_Face, 0, _Size);

		memset(_CharInfos, 0, (1 << 16) * sizeof(XFrontCharInfo));

		_TextureW = 1024;
		_TextureH = 1024;

		GLuint textureID;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, _TextureW, _TextureH, 0, GL_ALPHA, GL_UNSIGNED_BYTE, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);

		_AllTextures.push_back(textureID);
		_CurTextureIndex = 0;

		_CurTextureOffsetX = 0;
		_CurTextureOffsetY = 0;

	}

	void XFrontMaker::Done()
	{
		FT_Done_Face(_Face);
		FT_Done_FreeType(_Library);

		glDisable(GL_TEXTURE_2D);
	}

	void XFrontMaker::Scan(wchar_t* pStr)
	{
		size_t size = wcslen(pStr);
		for (size_t i = 0; i < size; ++i)
		{
			ScanChar(pStr[i]);
		}
	}

	void XFrontMaker::ScanChar(wchar_t c)
	{
		if (_CharInfos[c]._Found == true)
			return;

		FT_Load_Char(_Face, c, FT_LOAD_RENDER);
		FT_GlyphSlot glyph = _Face->glyph;
		FT_Bitmap bitmap = glyph->bitmap;

		_CharInfos[c]._Found = true;
		_CharInfos[c]._TexIndex = _CurTextureIndex;
		_CharInfos[c]._X = _CurTextureOffsetX;
		_CharInfos[c]._Y = _CurTextureOffsetY;
		_CharInfos[c]._Width = bitmap.width;
		_CharInfos[c]._Height = bitmap.rows;
		_CharInfos[c]._BearingX = glyph->bitmap_left;
		_CharInfos[c]._BearingY = glyph->bitmap_top;
		_CharInfos[c]._AdvanceX = glyph->advance.x / 64;
		_CharInfos[c]._AdvanceY = glyph->advance.y / 64;

		glBindTexture(GL_TEXTURE_2D, _AllTextures[_CurTextureIndex]);
		glTexSubImage2D(GL_TEXTURE_2D, 0, _CharInfos[c]._X, _CharInfos[c]._Y, _CharInfos[c]._Width, _CharInfos[c]._Height, GL_ALPHA, GL_UNSIGNED_BYTE, bitmap.buffer);
		glBindTexture(GL_TEXTURE_2D, 0);

		_CurTextureOffsetX += _CharInfos[c]._Width + 1; //此处使用_CharInfos[c]._AdvanceX会浪费空间。
		if (_CurTextureOffsetX + _Size >= _TextureW)
		{
			_CurTextureOffsetX = 0;

			_CurTextureOffsetY += _Size;
			if (_CurTextureOffsetY >= _TextureH)
			{
				GLuint textureID;
				glGenTextures(1, &textureID);
				glBindTexture(GL_TEXTURE_2D, textureID);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, _TextureW, _TextureH, 0, GL_ALPHA, GL_UNSIGNED_BYTE, NULL);
				glBindTexture(GL_TEXTURE_2D, 0);

				_AllTextures.push_back(textureID);
				++_CurTextureIndex;
				_CurTextureOffsetY = 0; 
			}	
		}
	}

	int XFrontMaker::GetTexNum()
	{
		return (int)_AllTextures.size();
	}

	void XFrontMaker::Save(unsigned int index)
	{
		char* pBuffer = new char[_TextureW * _TextureH];
		glBindTexture(GL_TEXTURE_2D, _AllTextures[index]);
		glGetTexImage(GL_TEXTURE_2D, 0, GL_ALPHA, GL_UNSIGNED_BYTE, pBuffer);
		glBindTexture(GL_TEXTURE_2D, 0);

		FIBITMAP* dib = FreeImage_Allocate(_TextureW, _TextureH, 32);
		unsigned char* pPixel = FreeImage_GetBits(dib);
		for (unsigned int i = 0; i < _TextureW * _TextureH; ++i)
		{
			pPixel[i * 4 + 0] = pBuffer[i];
			pPixel[i * 4 + 1] = 0;
			pPixel[i * 4 + 2] = 0;
			pPixel[i * 4 + 3] = 255;
		}

		char buffer[32] = {};
		sprintf(buffer, "%d.png", index);
		FreeImage_Save(FIF_PNG, dib, buffer, PNG_DEFAULT);
		FreeImage_Unload(dib);
	}

	void XFrontMaker::SaveAll()
	{
		for (unsigned int i = 0; i < _AllTextures.size(); ++i)
		{
			Save(i);
		}
	}

	void XFrontMaker::InitRender()
	{
		for (unsigned int i = 0; i < _AllTextures.size(); ++i)
		{
			GLuint texture = CreateTexture(i);
			_AllRenderTextures.push_back(texture);
		}
	}

	void XFrontMaker::Render(unsigned int index)
	{
		XVertexInfo vertices[] = {
			{ -1, -1, 0.0f,	0.0f,1.0f },
			{ +1, -1, 0.0f,	1.0f,1.0f },
			{ +1, +1, 0.0f,	1.0f,0.0f },
			{ -1, +1, 0.0f,	0.0f,0.0f }
		};

		glBindTexture(GL_TEXTURE_2D, _AllRenderTextures[index]);

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, sizeof(XVertexInfo), (const void*)&vertices[0]._X);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, sizeof(XVertexInfo), (const void*)&vertices[0]._U);

		glDrawArrays(GL_QUADS, 0, 4);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	GLuint XFrontMaker::CreateTexture(unsigned int index)
	{
		char buffer[32] = {};
		sprintf(buffer, "%d.png", index);

		FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(buffer, 0);
		if (fif == FIF_UNKNOWN)
			return 0;

		FIBITMAP* dib = FreeImage_Load(fif, buffer);

		FIBITMAP* temp = dib;
		dib = FreeImage_ConvertTo32Bits(dib);
		FreeImage_Unload(temp);

		char* pBuffer = (char*)FreeImage_GetBits(dib);
		int w = FreeImage_GetWidth(dib);
		int h = FreeImage_GetHeight(dib);

		GLuint _texture;
		glGenTextures(1, &_texture);
		glBindTexture(GL_TEXTURE_2D, _texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pBuffer);
		glBindTexture(GL_TEXTURE_2D, 0);

		FreeImage_Unload(dib);

		return _texture;
	}
}
