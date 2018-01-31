#ifndef __XFILE_MANAGER_H__
#define __XFILE_MANAGER_H__

#ifdef EXPORT_XAPI
#define XAPI __declspec(dllexport)
#else
#define XAPI __declspec(dllimport)
#endif

#define XIN
#define XOUT

class XAPI  XFileManager
{
public:
	int XInit();
	int XDone();

	int XLoadImage(XOUT unsigned char*& pBuffer, XOUT int& w, XOUT int& h, XIN const char* pFile);
	int XSaveImage(XOUT unsigned char*& pBuffer, XOUT int& w, XOUT int& h, XIN const char* pFile);
	int XSaveImageRed(XOUT unsigned char*& pBuffer, XOUT int& w, XOUT int& h, XIN const char* pFile);
	int XSaveImageGreen(XOUT unsigned char*& pBuffer, XOUT int& w, XOUT int& h, XIN const char* pFile);
	int XSaveImageBlue(XOUT unsigned char*& pBuffer, XOUT int& w, XOUT int& h, XIN const char* pFile);
	int XSaveImageAlpha(XOUT unsigned char*& pBuffer, XOUT int& w, XOUT int& h, XIN const char* pFile);

	int XFreeBuffer(XIN unsigned char*& pBuffer);
};

#endif