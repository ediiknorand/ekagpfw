#include "ibo.h"

void gui_text_ibo_buffer(GUI_TextIBOChar *buffer, int len)
{
  int i;
  for(i = 0; i < len; i++) {
    buffer[i].elem[0] = 4*i + 0;
    buffer[i].elem[1] = 4*i + 1;
    buffer[i].elem[2] = 4*i + 2;
    buffer[i].elem[3] = 4*i + 1;
    buffer[i].elem[4] = 4*i + 2;
    buffer[i].elem[5] = 4*i + 3;
  }
}

GLuint gui_text_ibo_upload(GUI_TextIBOChar *buffer, int len)
{
  GLuint ibo;
  glGenBuffers(1, &ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, len*sizeof(GUI_TextIBOChar), buffer, GL_STATIC_DRAW);

  return ibo;
}

void gui_text_ibo_unload(GLuint ibo)
{
  glDeleteBuffers(1, &ibo);
}
