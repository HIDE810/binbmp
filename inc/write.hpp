#pragma once

#define FILE_TYPE 0x4D42    /* "BM"をリトルエンディアンで解釈した値 */
#define FILE_HEADER_SIZE 14 /* BMPファイルヘッダサイズ */
#define INFO_HEADER_SIZE 40 /* Windowsヘッダサイズ */
#define DEFAULT_HEADER_SIZE (FILE_HEADER_SIZE + INFO_HEADER_SIZE) /* 標準のヘッダサイズ */

#pragma pack (push, 1)

typedef struct {
    unsigned short bfType;      /* ファイルタイプ */
    unsigned long  bfSize;      /* ファイルサイズ*/
    unsigned short bfReserved1; /* 予約領域1 */
    unsigned short bfReserved2; /* 予約領域2 */
    unsigned long  bfOffBits;   /* 先頭から画像データまでのオフセット */
} BITMAP_FILE_HEADER;

typedef struct {
    unsigned long  biSize;         /* ヘッダサイズ */
    long           biWidth;        /* 画像の幅(px)*/
    long           biHeight;       /* 画像の高さ(px) */
    unsigned short biPlanes;       /* プレーン数(常に1)*/
    unsigned short biBitCount;     /* 1画素あたりのデータサイズ */
    unsigned long  biCompression;  /* 圧縮形式*/
    unsigned long  biSizeImage;    /* 画像データ部のサイズ */
    long           biXPixPerMeter; /* 横横行解像度(dot/m) */
    long           biYPixPerMeter; /* 縦方向解像度(dot/m) */
    unsigned long  biClrUsed;      /* 格納されているパレット数(使用色数) */
    unsigned long  biClrImportant; /* 重要なパレットのインデックス */
} BITMAP_INFO_HEADER;

#pragma pack(pop)

typedef unsigned int u32;

void writeBitmap(std::ifstream &img, u32 size);