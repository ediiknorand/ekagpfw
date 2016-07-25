#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "atlas.h"

static void get_atlas_size(FT_Face face, int *w, int *h)
{
  FT_GlyphSlot g = face->glyph;

  *w = 0;
  *h = 0;
  int i;
  for(i = 32; i < 128; i++) {
    if(FT_Load_Char(face, i, FT_LOAD_RENDER)) {
      fprintf(stderr, "Could not load character %c data\n", (char)i);
      continue;
    }
    *w += g->bitmap.width;
    if(g->bitmap.rows > *h)
      *h = g->bitmap.rows;
  }
}

static void gen_atlas_bitmap(unsigned char *dest, FT_Face face, int w, int h)
{
  FT_GlyphSlot g = face->glyph;

  int x = 0;
  int c,row;
  for(c = 32; c < 128; c++) {
    if(FT_Load_Char(face, c, FT_LOAD_RENDER))
      continue;
    for(row = 0; row < g->bitmap.rows; row++)
      //memcpy(&dest[x + w*(g->bitmap.rows-1-row)],
      memcpy(&dest[x + w*(row)],
             &(g->bitmap.buffer[g->bitmap.width*row]),
             g->bitmap.width*sizeof(unsigned char));

    x+= g->bitmap.width;
  }
}

static void gen_char_data(GUI_TextAtlasCharData *data, FT_Face face, int w, int h)
{
  FT_GlyphSlot g = face->glyph;

  int x = 0;
  int c;
  for(c = 32; c < 128; c++) {
    if(FT_Load_Char(face, c, FT_LOAD_RENDER))
      continue;

    data[CHARIDX(c)].w = g->bitmap.width;
    data[CHARIDX(c)].h = g->bitmap.rows;
    data[CHARIDX(c)].ax = (g->advance.x/64);

    data[CHARIDX(c)].bl = g->bitmap_left;
    data[CHARIDX(c)].bt = g->bitmap_top;

    GUI_TextAtlasCharTexCoord *t = data[CHARIDX(c)].t;

    float bw = g->bitmap.width;
    float bh = g->bitmap.rows;

#define USHORTNORM(n,m) ((unsigned short)(((float)(n)/(m))*0xffff))

    t[0].s = USHORTNORM(x,w);
    t[0].t = 0;

    t[1].s = USHORTNORM((float)x+bw,w);
    t[1].t = 0;

    t[2].s = USHORTNORM(x,w);
    t[2].t = USHORTNORM(bh,h);

    t[3].s = USHORTNORM((float)x+bw,w);
    t[3].t = USHORTNORM(bh,h);

#undef USHORTNORM

    x+= g->bitmap.width;
  }
}

int gui_text_atlas_init(FT_Library ft, GUI_TextAtlas *atlas, const char *fontfile, int size)
{
  FT_Face face;

  if(FT_New_Face(ft, fontfile, 0, &face)) {
    fprintf(stderr, "Could not open %s font file.\n", fontfile);
    return -1;
  }
  FT_Set_Pixel_Sizes(face, 0, size);

  int w,h;
  get_atlas_size(face, &w, &h);
  atlas->w = w;
  atlas->h = h;
  atlas->bitmap = malloc(sizeof(unsigned char)*w*h);

  if(!atlas->bitmap) {
    FT_Done_Face(face);
    return -2;
  }

  gen_atlas_bitmap(atlas->bitmap, face, w, h);
  gen_char_data(atlas->chardata, face, w, h);

  atlas->tex = 0;

  FT_Done_Face(face);
  return 0;
}

void gui_text_atlas_end(GUI_TextAtlas *atlas)
{
  free(atlas->bitmap);
}

void gui_text_atlas_upload(GUI_TextAtlas *atlas)
{
  glGenTextures(1, &atlas->tex);
  glBindTexture(GL_TEXTURE_2D, atlas->tex);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, atlas->w, atlas->h, 0, GL_RED, GL_UNSIGNED_BYTE, atlas->bitmap);
}

void gui_text_atlas_unload(GUI_TextAtlas *atlas)
{
  glDeleteTextures(1, &atlas->tex);
}

