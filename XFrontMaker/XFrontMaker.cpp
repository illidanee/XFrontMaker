#include "XFrontMaker.h"

#include "XFileManager.h"

namespace Smile
{
	XFrontMaker::XFrontMaker()
	{

	}

	XFrontMaker::~XFrontMaker()
	{

	}

	void XFrontMaker::Init(const char* pFront, int size)
	{
		glEnable(GL_TEXTURE_2D);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		//初始化FreeType
		FT_Init_FreeType(&_Library);
		//生成字体Face
		FT_New_Face(_Library, pFront, 0, &_Face);
		//设置使用字符表
		FT_Select_Charmap(_Face, FT_ENCODING_UNICODE);
		//设置字体大小
		_Size = size;
		FT_Set_Pixel_Sizes(_Face, 0, _Size);

		//使用DPI设置像素的时候，如果DPI不是大于72,则字体的宽高会大于_Size,此时字体的缓存换行判断就会出问题。
		//如果需要使用需要修改代码保存字体的最大宽高，用于字体缓存换行判断。
		//FT_F26Dot6 ftSize = (FT_F26Dot6)(_Size * (1 << 6));
		//FT_Set_Char_Size(_Face, ftSize, 0, 200, 200);

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
		//销毁字体Face
		FT_Done_Face(_Face);
		//销毁FreeType
		FT_Done_FreeType(_Library);

		glDisable(GL_TEXTURE_2D);
	}

	void XFrontMaker::Scan(wchar_t* pStr)
	{
		int size = (int)wcslen(pStr);
		for (int i = 0; i < size; ++i)
		{
			ScanChar(pStr[i]);
		}
	}

	void XFrontMaker::ScanChar(wchar_t c)
	{
		if (_CharInfos[c]._Found == true)
			return;

		glEnable(GL_TEXTURE_2D);

		//获取字型信息
		FT_Load_Char(_Face, c, FT_LOAD_NO_BITMAP);

		//根据字体大小生成字型位图
		if (_Size < 20)
			//生成非抗锯齿字型位图
			FT_Render_Glyph(_Face->glyph, FT_RENDER_MODE_MONO);
		else
			//生成抗锯齿字型位图
			FT_Render_Glyph(_Face->glyph, FT_RENDER_MODE_NORMAL);

		//获取字型信息
		FT_GlyphSlot glyphSlot = _Face->glyph;
		FT_Bitmap bitmap = glyphSlot->bitmap;

		//数据转化，否则小字体不会正常显示。
		FT_Bitmap newBitmap;
		FT_Bitmap_New(&newBitmap);
		FT_Bitmap* pBitmap = &bitmap;
		if (bitmap.pixel_mode == FT_PIXEL_MODE_MONO)
		{
			if (FT_Bitmap_Convert(_Library, &bitmap, &newBitmap, 1) == 0)
			{
				/**
				*   Go through the bitmap and convert all of the nonzero values to 0xFF (white).
				*/
				for (unsigned char* p = newBitmap.buffer, *endP = p + newBitmap.width * newBitmap.rows; p != endP; ++p)
					*p ^= -*p ^ *p;
				pBitmap = &newBitmap;
			}
		}

		//保存字型信息
		_CharInfos[c]._Found = true;
		_CharInfos[c]._TexIndex = _CurTextureIndex;
		_CharInfos[c]._X = _CurTextureOffsetX;
		_CharInfos[c]._Y = _CurTextureOffsetY;
		_CharInfos[c]._Width = pBitmap->width;
		_CharInfos[c]._Height = pBitmap->rows;
		_CharInfos[c]._BearingX = glyphSlot->bitmap_left;
		_CharInfos[c]._BearingY = glyphSlot->bitmap_top;
		_CharInfos[c]._AdvanceX = glyphSlot->advance.x / 64;
		_CharInfos[c]._AdvanceY = glyphSlot->advance.y / 64;

		//保存字型纹理
		glBindTexture(GL_TEXTURE_2D, _AllTextures[_CurTextureIndex]);
		glTexSubImage2D(GL_TEXTURE_2D, 0, _CharInfos[c]._X, _CharInfos[c]._Y, _CharInfos[c]._Width, _CharInfos[c]._Height, GL_ALPHA, GL_UNSIGNED_BYTE, pBitmap->buffer);
		glBindTexture(GL_TEXTURE_2D, 0);

		//销毁
		FT_Bitmap_Done(_Library, &newBitmap);

		//辅助信息
		_CurTextureOffsetX += _CharInfos[c]._Width + 1; //此处使用_CharInfos[c]._AdvanceX会浪费空间。
		if (_CurTextureOffsetX + _Size >= _TextureW)
		{
			_CurTextureOffsetX = 0;

			_CurTextureOffsetY += _Size + 1;
			if (_CurTextureOffsetY >= _TextureH)
			{
				GLuint textureID;
				glGenTextures(1, &textureID);
				glBindTexture(GL_TEXTURE_2D, textureID);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, _TextureW, _TextureH, 0, GL_ALPHA, GL_UNSIGNED_BYTE, nullptr);
				glBindTexture(GL_TEXTURE_2D, 0);

				_AllTextures.push_back(textureID);
				++_CurTextureIndex;
				_CurTextureOffsetY = 0; 
			}	
		}
	}

	void XFrontMaker::Write(wchar_t* pStr, int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	{
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_DEPTH_TEST);

		int startX = x;
		int startY = y;
		int size = (int)wcslen(pStr);

		int texIndex = 0;
		int verIndex = 0;
		for (int i = 0; i < size; ++i)
		{
			ScanChar(pStr[i]);

			XFrontCharInfo cInfo = _CharInfos[pStr[i]];

			//切换纹理
			if (texIndex != cInfo._TexIndex)
			{
				glBindTexture(GL_TEXTURE_2D, _AllTextures[texIndex]);

				glEnableClientState(GL_VERTEX_ARRAY);
				glVertexPointer(3, GL_FLOAT, sizeof(XVertexInfo), &_VertexBuffer[verIndex]._Pos);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glTexCoordPointer(2, GL_FLOAT, sizeof(XVertexInfo), &_VertexBuffer[verIndex]._UV);
				glEnableClientState(GL_COLOR_ARRAY);
				glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(XVertexInfo), &_VertexBuffer[verIndex]._Color);

				glDrawArrays(GL_TRIANGLES, verIndex, (i - verIndex) * 6);

				glDisableClientState(GL_VERTEX_ARRAY);
				glDisableClientState(GL_TEXTURE_COORD_ARRAY);
				glDisableClientState(GL_COLOR_ARRAY);

				glBindTexture(GL_TEXTURE_2D, 0);

				texIndex = cInfo._TexIndex;
				verIndex = i;
			}

			int offsetX = cInfo._BearingX;
			int offsetY = -(int)(cInfo._Height - cInfo._BearingY);

			_VertexBuffer[i * 6 + 0]._Pos._x = (float)startX + offsetX;
			_VertexBuffer[i * 6 + 0]._Pos._y = (float)startY + offsetY;
			_VertexBuffer[i * 6 + 0]._Pos._z = (float)0;
			_VertexBuffer[i * 6 + 0]._UV._u = (float)cInfo._X / _TextureW;
			_VertexBuffer[i * 6 + 0]._UV._v = (float)(cInfo._Y + cInfo._Height) / _TextureH;
			_VertexBuffer[i * 6 + 0]._Color._r = r;
			_VertexBuffer[i * 6 + 0]._Color._g = g;
			_VertexBuffer[i * 6 + 0]._Color._b = b;
			_VertexBuffer[i * 6 + 0]._Color._a = a;

			_VertexBuffer[i * 6 + 1]._Pos._x = (float)startX + offsetX + cInfo._Width;
			_VertexBuffer[i * 6 + 1]._Pos._y = (float)startY + offsetY;
			_VertexBuffer[i * 6 + 1]._Pos._z = (float)0;
			_VertexBuffer[i * 6 + 1]._UV._u = (float)(cInfo._X + cInfo._Width) / _TextureW;
			_VertexBuffer[i * 6 + 1]._UV._v = (float)(cInfo._Y + cInfo._Height) / _TextureH;
			_VertexBuffer[i * 6 + 1]._Color._r = r;
			_VertexBuffer[i * 6 + 1]._Color._g = g;
			_VertexBuffer[i * 6 + 1]._Color._b = b;
			_VertexBuffer[i * 6 + 1]._Color._a = a;

			_VertexBuffer[i * 6 + 2]._Pos._x = (float)startX + offsetX + cInfo._Width;
			_VertexBuffer[i * 6 + 2]._Pos._y = (float)startY + offsetY + cInfo._Height;
			_VertexBuffer[i * 6 + 2]._Pos._z = (float)0;
			_VertexBuffer[i * 6 + 2]._UV._u = (float)(cInfo._X + cInfo._Width) / _TextureW;
			_VertexBuffer[i * 6 + 2]._UV._v = (float)cInfo._Y / _TextureH;
			_VertexBuffer[i * 6 + 2]._Color._r = r;
			_VertexBuffer[i * 6 + 2]._Color._g = g;
			_VertexBuffer[i * 6 + 2]._Color._b = b;
			_VertexBuffer[i * 6 + 2]._Color._a = a;

			_VertexBuffer[i * 6 + 3]._Pos._x = (float)startX + offsetX;
			_VertexBuffer[i * 6 + 3]._Pos._y = (float)startY + offsetY;
			_VertexBuffer[i * 6 + 3]._Pos._z = (float)0;
			_VertexBuffer[i * 6 + 3]._UV._u = (float)cInfo._X / _TextureW;
			_VertexBuffer[i * 6 + 3]._UV._v = (float)(cInfo._Y + cInfo._Height) / _TextureH;
			_VertexBuffer[i * 6 + 3]._Color._r = r;
			_VertexBuffer[i * 6 + 3]._Color._g = g;
			_VertexBuffer[i * 6 + 3]._Color._b = b;
			_VertexBuffer[i * 6 + 3]._Color._a = a;

			_VertexBuffer[i * 6 + 4]._Pos._x = (float)startX + offsetX + cInfo._Width;
			_VertexBuffer[i * 6 + 4]._Pos._y = (float)startY + offsetY + cInfo._Height;
			_VertexBuffer[i * 6 + 4]._Pos._z = (float)0;
			_VertexBuffer[i * 6 + 4]._UV._u = (float)(cInfo._X + cInfo._Width) / _TextureW;
			_VertexBuffer[i * 6 + 4]._UV._v = (float)cInfo._Y / _TextureH;
			_VertexBuffer[i * 6 + 4]._Color._r = r;
			_VertexBuffer[i * 6 + 4]._Color._g = g;
			_VertexBuffer[i * 6 + 4]._Color._b = b;
			_VertexBuffer[i * 6 + 4]._Color._a = a;

			_VertexBuffer[i * 6 + 5]._Pos._x = (float)startX + offsetX;
			_VertexBuffer[i * 6 + 5]._Pos._y = (float)startY + offsetY + cInfo._Height;
			_VertexBuffer[i * 6 + 5]._Pos._z = (float)0;
			_VertexBuffer[i * 6 + 5]._UV._u = (float)(cInfo._X) / _TextureW;
			_VertexBuffer[i * 6 + 5]._UV._v = (float)cInfo._Y / _TextureH;
			_VertexBuffer[i * 6 + 5]._Color._r = r;
			_VertexBuffer[i * 6 + 5]._Color._g = g;
			_VertexBuffer[i * 6 + 5]._Color._b = b;
			_VertexBuffer[i * 6 + 5]._Color._a = a;

			startX += cInfo._AdvanceX;
		}

		glBindTexture(GL_TEXTURE_2D, _AllTextures[texIndex]);

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, sizeof(XVertexInfo), &_VertexBuffer[verIndex]._Pos);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);	
		glTexCoordPointer(2, GL_FLOAT, sizeof(XVertexInfo), &_VertexBuffer[verIndex]._UV);
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(XVertexInfo), &_VertexBuffer[verIndex]._Color);

		glDrawArrays(GL_TRIANGLES, verIndex, (size - verIndex) * 6);
		
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	int XFrontMaker::GetTexNum()
	{
		return (int)_AllTextures.size();
	}

	void XFrontMaker::Save(unsigned int index)
	{
		glEnable(GL_TEXTURE_2D);

		unsigned char* pBuffer = new unsigned char[_TextureW * _TextureH];
		glBindTexture(GL_TEXTURE_2D, _AllTextures[index]);
		glGetTexImage(GL_TEXTURE_2D, 0, GL_ALPHA, GL_UNSIGNED_BYTE, pBuffer);
		glBindTexture(GL_TEXTURE_2D, 0);

		char buffer[32] = {};
		sprintf(buffer, "%d.png", index);
		XFileManager mgr;
		mgr.XSaveImageGreen(pBuffer, _TextureW, _TextureH, buffer);

		delete[] pBuffer;
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
		glEnable(GL_TEXTURE_2D);

		XVertexInfo vertices[] = {
			{ {100.0f, 100.0f, 0.0f},    {0.0f,1.0f},    {0, 0, 0, 255} },
			{ {1100.0f, 100.0f, 0.0f},    {1.0f,1.0f},    {0, 0, 0, 255} },
			{ { 1100.0f, 800.0f, 0.0f},    {1.0f,0.0f},    {0, 0, 0, 255} },
			{ {100.0f, 800.0f, 0.0f},    {0.0f,0.0f},    {0, 0, 0, 255} }
		};																	 

		glBindTexture(GL_TEXTURE_2D, _AllRenderTextures[index]);

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, sizeof(XVertexInfo), (const void*)&vertices[0]._Pos);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, sizeof(XVertexInfo), (const void*)&vertices[0]._UV);

		glDrawArrays(GL_QUADS, 0, 4);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	GLuint XFrontMaker::CreateTexture(unsigned int index)
	{
		glEnable(GL_TEXTURE_2D);

		char buffer[32] = {};
		sprintf(buffer, "%d.png", index);

		unsigned char* pBuffer = NULL;
		int w;
		int h;

		XFileManager mgr;
		mgr.XLoadImage(pBuffer, w, h, buffer);

		GLuint _texture;
		glGenTextures(1, &_texture);
		glBindTexture(GL_TEXTURE_2D, _texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pBuffer);
		glBindTexture(GL_TEXTURE_2D, 0);

		mgr.XFreeBuffer(pBuffer);

		return _texture;
	}

	void XFrontMaker::_CheckError()
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
}
