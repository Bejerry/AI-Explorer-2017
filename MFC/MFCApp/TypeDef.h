#pragma once

#include <string>
#include <vector>

using namespace std;

#define DWORD unsigned int
#define WORD  unsigned short
#define BYTE  unsigned char

typedef enum E_FILE_TYPE
{
	ICO,
	BMP,
	GIF,
	PNG,
	TIF,
	JPG,
	JPEG,
	WMF,
	EMF,
	MAX_TYPE
}F_Type;

typedef struct T_FILE_MAP
{
	F_Type type;
	string name;
}F_Map;

#define ICON ICO
#define GIFF GIF
#define TIFF TIF
//#define JPEG JPG
#define JPE  JPG

#define MAX_PIX 64
#define POS_INVALID  -1
#define RETURN_ERROR -1
#define THUMBNAIL_WIDTH 30
#define THUMBNAIL_HEIGHT 30
#define MAX_FILE_PATH_LEN 256
#define IMAGE_DVALUE_THRESHOLD 1000
#define ThumbnailFolder "Thummbnail"
#define TargetFolder "Target"
#define RESULT_SUCC 0
#define RESULT_FAIL 0xFFFFFFFF