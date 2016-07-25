#ifndef H_GUI_TEXT_IBO_H
#define H_GUI_TEXT_IBO_H

#include <GL/glew.h>

typedef struct {
  GLushort elem[6];
} GUI_TextIBOChar;

void gui_text_ibo_buffer(GUI_TextIBOChar *buffer, int len);

GLuint gui_text_ibo_upload(GUI_TextIBOChar *buffer, int len);
void gui_text_ibo_unload(GLuint ibo);

#endif
