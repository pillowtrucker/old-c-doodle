#pragma once
#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mla.h"
struct MemoryStruct {
  char *memory;
  size_t size;
  pthread_mutex_t * chunk_mutex;
};
 
size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);
/*
static unsigned char eye[1059];
static unsigned int eye_len;
static unsigned char eye2[1060];
static unsigned int eye2_len;
static unsigned char eye3[1057];
static unsigned int eye3_len;
*/
static wchar_t weye[1059];
static unsigned int weye_len;
static wchar_t weye2[1060];
static unsigned int weye2_len;
static wchar_t weye3[1057];
static unsigned int weye3_len;

static unsigned char eye[] = {
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2e, 0x2e, 0x2e, 0x27,
  0x2c, 0x3b, 0x3b, 0x3a, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
  0x3a, 0x3b, 0x2c, 0x2e, 0x2e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2e, 0x2e,
  0x2c, 0x3b, 0x3a, 0x63, 0x63, 0x63, 0x63, 0x3a, 0x3a, 0x3a, 0x3a, 0x63,
  0x63, 0x63, 0x63, 0x63, 0x6c, 0x6c, 0x6f, 0x6f, 0x6f, 0x6f, 0x6c, 0x63,
  0x3b, 0x27, 0x2e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x2e, 0x27, 0x2c, 0x3b, 0x3a, 0x3a, 0x3a,
  0x3b, 0x3b, 0x3b, 0x3b, 0x3a, 0x6c, 0x6f, 0x6f, 0x64, 0x78, 0x6b, 0x30,
  0x6b, 0x6b, 0x78, 0x78, 0x6b, 0x78, 0x78, 0x64, 0x6f, 0x63, 0x63, 0x63,
  0x63, 0x3b, 0x3b, 0x27, 0x2e, 0x2e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2e, 0x2c, 0x3b, 0x3b, 0x3b, 0x2c,
  0x2c, 0x3b, 0x3a, 0x63, 0x6f, 0x78, 0x6c, 0x64, 0x4b, 0x4e, 0x57, 0x57,
  0x57, 0x4d, 0x4d, 0x4d, 0x4d, 0x57, 0x4e, 0x4e, 0x57, 0x57, 0x4e, 0x4e,
  0x4b, 0x6b, 0x64, 0x6f, 0x6c, 0x63, 0x63, 0x63, 0x63, 0x3a, 0x2c, 0x2e,
  0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2e, 0x27, 0x2c,
  0x3b, 0x3b, 0x2c, 0x27, 0x2c, 0x3b, 0x6c, 0x78, 0x6f, 0x3a, 0x2e, 0x2e,
  0x2e, 0x64, 0x58, 0x57, 0x4d, 0x4d, 0x4d, 0x4d, 0x4d, 0x4d, 0x4d, 0x4d,
  0x4e, 0x6b, 0x6c, 0x6f, 0x4f, 0x58, 0x4e, 0x4e, 0x4e, 0x58, 0x30, 0x6b,
  0x6f, 0x63, 0x3a, 0x63, 0x6f, 0x6f, 0x3b, 0x2e, 0x0a, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x2e, 0x2e, 0x2c, 0x3b, 0x3a, 0x3b, 0x2c, 0x2c, 0x2c, 0x3a,
  0x6c, 0x64, 0x6c, 0x27, 0x20, 0x20, 0x20, 0x2e, 0x6b, 0x57, 0x4d, 0x4d,
  0x4d, 0x57, 0x58, 0x58, 0x4e, 0x57, 0x4d, 0x4d, 0x4d, 0x4d, 0x58, 0x64,
  0x2e, 0x2e, 0x27, 0x3a, 0x64, 0x30, 0x58, 0x57, 0x57, 0x4e, 0x30, 0x64,
  0x3a, 0x3b, 0x6c, 0x6b, 0x64, 0x2c, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2e, 0x2e,
  0x2c, 0x3b, 0x3b, 0x2c, 0x2c, 0x27, 0x27, 0x3a, 0x6c, 0x6f, 0x63, 0x2e,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x6c, 0x4b, 0x4d, 0x4d, 0x4d, 0x4e, 0x6c,
  0x2e, 0x20, 0x2e, 0x63, 0x30, 0x4b, 0x4e, 0x57, 0x4e, 0x4b, 0x3a, 0x20,
  0x20, 0x2e, 0x2e, 0x27, 0x3b, 0x6c, 0x78, 0x30, 0x30, 0x58, 0x30, 0x6c,
  0x2c, 0x63, 0x78, 0x6f, 0x2c, 0x2e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2e, 0x2e, 0x27, 0x27,
  0x2e, 0x2e, 0x2e, 0x2e, 0x27, 0x63, 0x6f, 0x6f, 0x63, 0x2e, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x63, 0x30, 0x4e, 0x4d, 0x4d, 0x58, 0x3b,
  0x20, 0x20, 0x20, 0x2e, 0x6c, 0x30, 0x58, 0x57, 0x4e, 0x30, 0x3b, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2c, 0x64, 0x64, 0x78, 0x30, 0x30,
  0x6f, 0x63, 0x63, 0x6c, 0x3a, 0x2e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2e, 0x2e, 0x27, 0x2e, 0x2e, 0x20,
  0x20, 0x2e, 0x27, 0x3a, 0x6f, 0x64, 0x63, 0x2e, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x2e, 0x78, 0x30, 0x4b, 0x4b, 0x4b, 0x6b,
  0x6f, 0x6c, 0x63, 0x6c, 0x64, 0x30, 0x30, 0x30, 0x78, 0x63, 0x2e, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2e, 0x63, 0x78, 0x78, 0x78, 0x6b,
  0x6b, 0x64, 0x6c, 0x3a, 0x2c, 0x2e, 0x2e, 0x0a, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x2e, 0x2e, 0x27, 0x27, 0x2e, 0x2e, 0x20,
  0x20, 0x20, 0x3b, 0x64, 0x78, 0x6f, 0x6c, 0x63, 0x3b, 0x27, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2e, 0x6c, 0x78, 0x78, 0x30,
  0x30, 0x30, 0x6b, 0x6b, 0x78, 0x78, 0x30, 0x30, 0x6b, 0x63, 0x2e, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x2e, 0x3b, 0x6c, 0x6f, 0x6f, 0x6f, 0x6c,
  0x6c, 0x6c, 0x6f, 0x6c, 0x3a, 0x27, 0x2e, 0x2e, 0x0a, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x2e, 0x2e, 0x27, 0x2e, 0x2e, 0x20, 0x20,
  0x20, 0x20, 0x2e, 0x27, 0x3a, 0x6c, 0x6c, 0x6f, 0x6f, 0x6c, 0x63, 0x3a,
  0x2c, 0x2e, 0x2e, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x27, 0x6c,
  0x78, 0x6b, 0x6b, 0x6b, 0x6b, 0x6b, 0x30, 0x6b, 0x64, 0x2c, 0x20, 0x20,
  0x20, 0x2e, 0x2e, 0x27, 0x3a, 0x63, 0x6c, 0x63, 0x3a, 0x3a, 0x3a, 0x3b,
  0x2c, 0x2c, 0x3b, 0x3a, 0x3b, 0x2c, 0x27, 0x2e, 0x2e, 0x0a, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e,
  0x20, 0x20, 0x20, 0x2e, 0x2e, 0x2e, 0x2e, 0x27, 0x2c, 0x3b, 0x3b, 0x3b,
  0x3a, 0x63, 0x63, 0x63, 0x3a, 0x3a, 0x3b, 0x3b, 0x2c, 0x27, 0x27, 0x27,
  0x2c, 0x3a, 0x6c, 0x6f, 0x64, 0x64, 0x6f, 0x6c, 0x3a, 0x2c, 0x2c, 0x3b,
  0x3a, 0x63, 0x6c, 0x6c, 0x6c, 0x6f, 0x6c, 0x63, 0x3a, 0x3b, 0x3b, 0x2c,
  0x27, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x0a, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2e, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x2e, 0x2e, 0x2e, 0x2e, 0x27, 0x27, 0x27, 0x27,
  0x2c, 0x2c, 0x2c, 0x3b, 0x3b, 0x3a, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
  0x6c, 0x6c, 0x6c, 0x6c, 0x6f, 0x6f, 0x6f, 0x6f, 0x6c, 0x6c, 0x6c, 0x6c,
  0x63, 0x63, 0x63, 0x3a, 0x63, 0x3a, 0x3a, 0x3a, 0x3b, 0x2c, 0x27, 0x2e,
  0x2e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2e, 0x2e,
  0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x27, 0x27, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c,
  0x2c, 0x2c, 0x2c, 0x3b, 0x3b, 0x3a, 0x3a, 0x3a, 0x3a, 0x63, 0x63, 0x63,
  0x63, 0x63, 0x3a, 0x3a, 0x3a, 0x3a, 0x3b, 0x3b, 0x3b, 0x2c, 0x2c, 0x27,
  0x27, 0x2e, 0x2e, 0x2e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e,
  0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x27, 0x27, 0x27, 0x2c, 0x2c, 0x2c,
  0x3b, 0x3b, 0x3b, 0x2c, 0x2c, 0x27, 0x27, 0x27, 0x27, 0x27, 0x27, 0x2e,
  0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2e, 0x2e, 0x2e,
  0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e,
  0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e,
  0x2e, 0x0a, 0x00
};
static unsigned int eye_len = 1059;
static unsigned char eye2[] = {
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2e, 0x2e, 0x2e,
  0x27, 0x27, 0x2c, 0x3b, 0x3b, 0x3b, 0x3b, 0x3a, 0x3a, 0x3b, 0x3b, 0x3b,
  0x2c, 0x27, 0x2e, 0x2e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2e, 0x2e, 0x2c,
  0x3b, 0x3a, 0x63, 0x6c, 0x6f, 0x6f, 0x64, 0x64, 0x64, 0x78, 0x78, 0x78,
  0x6b, 0x6b, 0x6b, 0x6b, 0x6b, 0x6b, 0x6b, 0x6b, 0x78, 0x6f, 0x6c, 0x3b,
  0x2e, 0x2e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x2e, 0x27, 0x3b, 0x63, 0x6f, 0x64, 0x78, 0x78,
  0x6b, 0x6b, 0x6b, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
  0x30, 0x30, 0x30, 0x6b, 0x6b, 0x6b, 0x6b, 0x6b, 0x6b, 0x78, 0x64, 0x6f,
  0x63, 0x2c, 0x2e, 0x2e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x2e, 0x2c, 0x63, 0x6f, 0x64, 0x78, 0x6b, 0x30,
  0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
  0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
  0x6b, 0x6b, 0x78, 0x64, 0x64, 0x6f, 0x63, 0x2c, 0x2e, 0x2e, 0x0a, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2e, 0x27, 0x3a, 0x6c, 0x64,
  0x78, 0x6b, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
  0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
  0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x6b, 0x6b,
  0x78, 0x78, 0x6f, 0x6c, 0x3a, 0x27, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x2e, 0x2c, 0x3a, 0x6c, 0x64, 0x78, 0x6b, 0x6b, 0x30, 0x30, 0x30, 0x30,
  0x30, 0x30, 0x30, 0x30, 0x30, 0x4b, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
  0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x4b, 0x30, 0x30,
  0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x6b, 0x6b, 0x78, 0x6b,
  0x6b, 0x78, 0x3a, 0x2e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2e, 0x2e, 0x2c, 0x63, 0x6f,
  0x78, 0x6b, 0x6b, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
  0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x6b, 0x6b, 0x30, 0x30, 0x30, 0x30,
  0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
  0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x6b, 0x78, 0x78, 0x78,
  0x78, 0x6c, 0x27, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x2e, 0x2c, 0x3b, 0x63, 0x6f, 0x64, 0x78,
  0x78, 0x6b, 0x6b, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x6b,
  0x6b, 0x6b, 0x30, 0x4b, 0x4b, 0x30, 0x58, 0x4e, 0x57, 0x57, 0x57, 0x57,
  0x57, 0x57, 0x57, 0x57, 0x57, 0x4e, 0x58, 0x30, 0x6b, 0x6b, 0x6b, 0x6b,
  0x6b, 0x30, 0x30, 0x30, 0x30, 0x30, 0x6b, 0x6b, 0x78, 0x64, 0x6f, 0x6f,
  0x6c, 0x3b, 0x2e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x2e, 0x27, 0x3b, 0x3a, 0x3a, 0x63, 0x63, 0x6c, 0x64,
  0x6b, 0x30, 0x30, 0x4b, 0x4b, 0x4b, 0x4b, 0x30, 0x30, 0x6f, 0x63, 0x3b,
  0x2e, 0x2e, 0x2c, 0x78, 0x30, 0x30, 0x4b, 0x4e, 0x4e, 0x58, 0x58, 0x58,
  0x58, 0x58, 0x4e, 0x4e, 0x58, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
  0x30, 0x30, 0x30, 0x6b, 0x6b, 0x6b, 0x6b, 0x6b, 0x6b, 0x78, 0x6f, 0x63,
  0x3a, 0x2c, 0x2e, 0x2e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x2e, 0x2e, 0x2c, 0x3b, 0x2c, 0x27, 0x2e, 0x2e, 0x2c, 0x6f,
  0x30, 0x30, 0x30, 0x30, 0x30, 0x6b, 0x6b, 0x78, 0x6f, 0x2c, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x2c, 0x6c, 0x6b, 0x4b, 0x4b, 0x4b, 0x4b,
  0x4b, 0x4b, 0x30, 0x4b, 0x30, 0x64, 0x2c, 0x2e, 0x3b, 0x6c, 0x64, 0x6b,
  0x30, 0x30, 0x30, 0x4b, 0x4b, 0x30, 0x6b, 0x78, 0x78, 0x78, 0x64, 0x6f,
  0x63, 0x3a, 0x27, 0x2e, 0x2e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x2e, 0x2e, 0x2c, 0x2c, 0x27, 0x2e, 0x20, 0x20, 0x2e, 0x2c,
  0x6c, 0x6b, 0x30, 0x78, 0x78, 0x78, 0x64, 0x6f, 0x6c, 0x3a, 0x2c, 0x2e,
  0x2e, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2e, 0x2c, 0x6c, 0x64,
  0x64, 0x64, 0x6c, 0x3a, 0x2c, 0x2e, 0x20, 0x20, 0x20, 0x2e, 0x2c, 0x63,
  0x6f, 0x64, 0x6b, 0x6b, 0x30, 0x30, 0x6b, 0x78, 0x64, 0x6f, 0x6c, 0x6c,
  0x63, 0x3a, 0x2c, 0x2e, 0x2e, 0x2e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x2e, 0x2e, 0x27, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e,
  0x2e, 0x27, 0x2c, 0x3b, 0x3a, 0x63, 0x3a, 0x3a, 0x63, 0x63, 0x6c, 0x63,
  0x63, 0x63, 0x3a, 0x3a, 0x3b, 0x2c, 0x2c, 0x2c, 0x27, 0x2c, 0x2c, 0x3b,
  0x3a, 0x3a, 0x3a, 0x3a, 0x3b, 0x2c, 0x3b, 0x3b, 0x3a, 0x63, 0x6c, 0x6f,
  0x64, 0x64, 0x64, 0x78, 0x64, 0x6f, 0x6c, 0x3a, 0x3b, 0x3a, 0x3a, 0x3b,
  0x27, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x0a, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e,
  0x20, 0x20, 0x2e, 0x2e, 0x2e, 0x27, 0x27, 0x27, 0x2c, 0x2c, 0x2c, 0x3b,
  0x3b, 0x3b, 0x3a, 0x63, 0x63, 0x6c, 0x6c, 0x6c, 0x6f, 0x6f, 0x6f, 0x6f,
  0x6f, 0x6f, 0x6f, 0x6f, 0x6f, 0x6f, 0x6f, 0x6f, 0x6f, 0x6f, 0x6c, 0x6c,
  0x6c, 0x63, 0x63, 0x63, 0x63, 0x3a, 0x3b, 0x3b, 0x2c, 0x2e, 0x2e, 0x2e,
  0x2e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2e, 0x2e,
  0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x27, 0x27, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c,
  0x2c, 0x3b, 0x3b, 0x3b, 0x3a, 0x3a, 0x3a, 0x63, 0x63, 0x63, 0x6c, 0x6c,
  0x6c, 0x63, 0x63, 0x63, 0x3a, 0x3a, 0x3a, 0x3b, 0x3b, 0x3b, 0x2c, 0x27,
  0x27, 0x2e, 0x2e, 0x2e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e,
  0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x27, 0x27, 0x27, 0x27, 0x2c, 0x2c, 0x3b,
  0x3b, 0x3b, 0x3b, 0x3b, 0x2c, 0x2c, 0x2c, 0x27, 0x27, 0x27, 0x27, 0x2e,
  0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2e, 0x2e, 0x2e,
  0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e,
  0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e,
  0x2e, 0x2e, 0x0a, 0x00
};
static unsigned int eye2_len = 1060;
static unsigned char eye3[] = {
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2e, 0x2e, 0x2e, 0x27,
  0x27, 0x2c, 0x3b, 0x3b, 0x3b, 0x3b, 0x3b, 0x3b, 0x3b, 0x2c, 0x2c, 0x2e,
  0x2e, 0x2e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2e, 0x2e, 0x2c, 0x3a, 0x6c, 0x6f,
  0x78, 0x6b, 0x6b, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x4b, 0x4b, 0x4b,
  0x4b, 0x4b, 0x4b, 0x30, 0x30, 0x78, 0x64, 0x63, 0x2c, 0x2e, 0x2e, 0x0a,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x2e, 0x2c, 0x63, 0x6f, 0x78, 0x30, 0x30, 0x30, 0x4b, 0x58, 0x58, 0x58,
  0x58, 0x58, 0x58, 0x58, 0x58, 0x58, 0x58, 0x58, 0x58, 0x58, 0x58, 0x58,
  0x58, 0x58, 0x58, 0x58, 0x4b, 0x30, 0x30, 0x78, 0x6f, 0x3a, 0x2c, 0x2e,
  0x2e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2e,
  0x2e, 0x3b, 0x6c, 0x78, 0x30, 0x30, 0x30, 0x4b, 0x4b, 0x4b, 0x4b, 0x4b,
  0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
  0x30, 0x30, 0x30, 0x4b, 0x4b, 0x4b, 0x4b, 0x58, 0x58, 0x58, 0x58, 0x4b,
  0x30, 0x30, 0x78, 0x6c, 0x3b, 0x2e, 0x2e, 0x0a, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x2e, 0x2e, 0x2c, 0x3a, 0x6f, 0x78, 0x6b, 0x30, 0x30, 0x30,
  0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
  0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
  0x30, 0x30, 0x30, 0x30, 0x30, 0x4b, 0x4b, 0x4b, 0x4b, 0x4b, 0x4b, 0x30,
  0x64, 0x3a, 0x2e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2e, 0x2e, 0x3b, 0x63, 0x6f,
  0x64, 0x78, 0x6b, 0x6b, 0x30, 0x30, 0x30, 0x6b, 0x6b, 0x6b, 0x6b, 0x6b,
  0x6b, 0x6b, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78,
  0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x6b, 0x6b, 0x6b, 0x6b, 0x6b, 0x6b,
  0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x4b, 0x4b, 0x30, 0x6b, 0x6c, 0x27,
  0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x2e, 0x2e, 0x3b, 0x6c, 0x64, 0x78, 0x6b, 0x6b, 0x6b, 0x6b,
  0x6b, 0x6b, 0x78, 0x78, 0x78, 0x78, 0x78, 0x64, 0x64, 0x64, 0x64, 0x64,
  0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
  0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x78, 0x78, 0x78, 0x78, 0x78,
  0x78, 0x6b, 0x6b, 0x6b, 0x30, 0x30, 0x30, 0x78, 0x63, 0x2e, 0x0a, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2e, 0x2e,
  0x2c, 0x3a, 0x6f, 0x78, 0x78, 0x6b, 0x6b, 0x6b, 0x6b, 0x6b, 0x78, 0x78,
  0x78, 0x78, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
  0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
  0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x78,
  0x78, 0x6b, 0x6b, 0x6b, 0x6b, 0x78, 0x6c, 0x3b, 0x2e, 0x0a, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2e, 0x2e, 0x2c, 0x3b, 0x63,
  0x6f, 0x64, 0x78, 0x78, 0x6b, 0x6b, 0x6b, 0x78, 0x78, 0x64, 0x64, 0x64,
  0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
  0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
  0x64, 0x64, 0x64, 0x64, 0x64, 0x78, 0x64, 0x78, 0x78, 0x78, 0x6b, 0x30,
  0x30, 0x30, 0x6b, 0x78, 0x64, 0x6f, 0x3a, 0x2e, 0x2e, 0x0a, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2e, 0x27, 0x3b, 0x3a, 0x3a, 0x3a,
  0x3a, 0x63, 0x6c, 0x64, 0x6b, 0x30, 0x30, 0x30, 0x6b, 0x6b, 0x6b, 0x78,
  0x78, 0x78, 0x78, 0x78, 0x78, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
  0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
  0x64, 0x64, 0x78, 0x78, 0x78, 0x78, 0x78, 0x6b, 0x6b, 0x30, 0x30, 0x30,
  0x30, 0x78, 0x6b, 0x64, 0x64, 0x6c, 0x3b, 0x2e, 0x2e, 0x0a, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x2e, 0x27, 0x3b, 0x3a, 0x3b, 0x2c, 0x2e,
  0x2e, 0x2c, 0x63, 0x6b, 0x58, 0x58, 0x58, 0x4b, 0x4b, 0x4b, 0x30, 0x4b,
  0x4b, 0x30, 0x30, 0x30, 0x6b, 0x78, 0x6b, 0x30, 0x64, 0x6f, 0x64, 0x64,
  0x78, 0x78, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x78, 0x78, 0x78,
  0x78, 0x78, 0x78, 0x6b, 0x6b, 0x30, 0x30, 0x30, 0x30, 0x6b, 0x6b, 0x6b,
  0x6b, 0x6b, 0x78, 0x64, 0x6f, 0x63, 0x2c, 0x2e, 0x2e, 0x0a, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x2e, 0x27, 0x2c, 0x2c, 0x27, 0x27, 0x2e,
  0x2e, 0x2c, 0x3a, 0x6f, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x6b,
  0x6b, 0x78, 0x6b, 0x6b, 0x78, 0x6b, 0x30, 0x30, 0x78, 0x78, 0x6b, 0x30,
  0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x4b,
  0x4b, 0x4b, 0x4b, 0x4b, 0x4b, 0x4b, 0x30, 0x30, 0x30, 0x6b, 0x78, 0x64,
  0x6c, 0x6c, 0x6c, 0x6c, 0x3a, 0x2c, 0x2e, 0x2e, 0x0a, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e,
  0x2e, 0x2e, 0x27, 0x2c, 0x2c, 0x2c, 0x3a, 0x63, 0x63, 0x6c, 0x6c, 0x6c,
  0x6c, 0x6f, 0x6f, 0x6f, 0x6f, 0x78, 0x6b, 0x78, 0x78, 0x78, 0x30, 0x30,
  0x30, 0x6b, 0x6b, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
  0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x6b, 0x78, 0x64, 0x6f, 0x63,
  0x2c, 0x27, 0x2e, 0x2e, 0x2e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2e, 0x2e,
  0x2e, 0x2e, 0x2e, 0x2e, 0x27, 0x2c, 0x3b, 0x3b, 0x3a, 0x3a, 0x63, 0x63,
  0x3a, 0x3a, 0x63, 0x6c, 0x6c, 0x6c, 0x6c, 0x6f, 0x64, 0x64, 0x6f, 0x6f,
  0x78, 0x30, 0x78, 0x64, 0x78, 0x78, 0x6b, 0x78, 0x78, 0x78, 0x78, 0x64,
  0x64, 0x6f, 0x6c, 0x6c, 0x6c, 0x6c, 0x63, 0x3a, 0x27, 0x2e, 0x0a, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2e, 0x2e, 0x2e, 0x2e,
  0x2e, 0x27, 0x27, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x3b, 0x3b,
  0x3b, 0x3b, 0x3b, 0x3a, 0x3a, 0x63, 0x6c, 0x6c, 0x63, 0x3a, 0x3a, 0x63,
  0x63, 0x63, 0x3a, 0x3a, 0x3b, 0x3b, 0x2c, 0x2c, 0x2c, 0x27, 0x2e, 0x2e,
  0x2e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e,
  0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x27, 0x27, 0x27,
  0x2e, 0x2e, 0x27, 0x27, 0x27, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x0a,
  0x00
};
static unsigned int eye3_len = 1057;
