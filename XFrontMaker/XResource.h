#pragma once

namespace Smile
{
	class XResource
	{
	public:
		static int LoadTextureFile(const char* pFile, char** pBuffer, int* w, int* h);
		static int SaveTextureFile(const char* pFile, char* pBuffer, int w, int h);
		static int SaveTextureFileOnlyA(const char* pFile, char* pBuffer, int w, int h);
	};
}