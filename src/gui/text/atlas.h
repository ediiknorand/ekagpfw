#ifndef H_GUI_TEXT_ATLAS_H
#define H_GUI_TEXT_ATLAS_H

#include <GL/glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#define CHARIDX(i) ((i)-32)

typedef struct {
  GLushort s,t;
} GUI_TextAtlasCharTexCoord;

typedef struct {
  unsigned short w,h;
  unsigned short ax;
  short bt,bl;
  GUI_TextAtlasCharTexCoord t[4];
} GUI_TextAtlasCharData;

typedef struct {
  GLuint tex;
  unsigned char *bitmap;
  GUI_TextAtlasCharData chardata[128-32];

  int w,h;
} GUI_TextAtlas;

int gui_text_atlas_init(FT_Library ft, GUI_TextAtlas *atlas, const char *fontfile, int size);
void gui_text_atlas_end(GUI_TextAtlas *atlas);

void gui_text_atlas_upload(GUI_TextAtlas *atlas);
void gui_text_atlas_unload(GUI_TextAtlas *atlas);

#endif
