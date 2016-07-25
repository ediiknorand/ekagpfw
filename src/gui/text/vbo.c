#include "vbo.h"

int gui_text_vbo_buffer(GUI_TextVBOChar *buffer, const char *string, int len, GUI_TextAtlas *atlas, int w, int h, int linesep)
{
  int x = 0;
  int y = atlas->h;
  int bsize = 0;

  int i;
  for(i = 0; string[i]; i++) {
    if(len > 0 && i >= len)
      break;

    if(string[i] == '\n') {
      x = 0;
      y += atlas->h + linesep;
      continue;
    }

    if(string[i] < 32 || string[i] >= 128)
      continue;

    GUI_TextAtlasCharData *data = &atlas->chardata[CHARIDX(string[i])];

    if(data->w == 0 || data->h == 0) {
      x+= data->ax;
      continue;
    }

    if(y+data->h+linesep >= h || x+data->ax >= w)
      break;

#define SHORTNORM(n,m) ((short)(((float)(n)/(m))*(0x7fff)))

    buffer[bsize].v[0].x = SHORTNORM(x+data->bl,w);
    buffer[bsize].v[0].y = SHORTNORM(y-data->bt,h);
    buffer[bsize].v[0].s = data->t[0].s;
    buffer[bsize].v[0].t = data->t[0].t;

    buffer[bsize].v[1].x = SHORTNORM(x+data->bl+data->w,w);
    buffer[bsize].v[1].y = SHORTNORM(y-data->bt,h);
    buffer[bsize].v[1].s = data->t[1].s;
    buffer[bsize].v[1].t = data->t[1].t;

    buffer[bsize].v[2].x = SHORTNORM(x+data->bl,w);
    buffer[bsize].v[2].y = SHORTNORM(y-data->bt+data->h,h);
    buffer[bsize].v[2].s = data->t[2].s;
    buffer[bsize].v[2].t = data->t[2].t;

    buffer[bsize].v[3].x = SHORTNORM(x+data->bl+data->w,w);
    buffer[bsize].v[3].y = SHORTNORM(y-data->bt+data->h,h);
    buffer[bsize].v[3].s = data->t[3].s;
    buffer[bsize].v[3].t = data->t[3].t;

#undef SHORTNORM

    x+= data->ax;
    bsize += 1;

  }
  return bsize;
}

GLuint gui_text_vbo_upload(GUI_TextVBOChar *buffer, int len, GLenum usage)
{
  GLuint vbo;

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, len*sizeof(GUI_TextVBOChar), buffer, usage);

  return vbo;
}

void gui_text_vbo_unload(GLuint vbo)
{
  glDeleteBuffers(1, &vbo);
}
