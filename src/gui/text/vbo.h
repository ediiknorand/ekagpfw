#ifndef H_GUI_TEXT_VBO_H
#define H_GUI_TEXT_VBO_H

#include <GL/glew.h>
#include "atlas.h"

typedef struct {
  GLshort x,y;
  GLushort s,t;
} GUI_TextVBOVertex;

typedef struct {
  GUI_TextVBOVertex v[4];
} GUI_TextVBOChar;

int gui_text_vbo_buffer(GUI_TextVBOChar *buffer, const char *string, int len, GUI_TextAtlas *atlas, int w, int h, int linesep);

GLuint gui_text_vbo_upload(GUI_TextVBOChar *buffer, int len, GLenum usage);
void gui_text_vbo_unload(GLuint vbo);

#endif
