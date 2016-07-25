#include "text.h"

void gui_text_draw(GUI_TextProgram *p, GLuint vbo, GLuint ibo, GLuint tex, int len)
{
  glActiveTexture(GL_TEXTURE0);
  glUniform1i(p->unif_tex, 0);
  glBindTexture(GL_TEXTURE_2D, tex);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  glEnableVertexAttribArray(p->attr_coord);
  glVertexAttribPointer(
    p->attr_coord,
    2,
    GL_SHORT,
    GL_TRUE,
    sizeof(GUI_TextVBOVertex),
    (GLvoid*)0
  );

  glEnableVertexAttribArray(p->attr_texcoord);
  glVertexAttribPointer(
    p->attr_texcoord,
    2,
    GL_UNSIGNED_SHORT,
    GL_TRUE,
    sizeof(GUI_TextVBOVertex),
    (GLvoid*)4
  );

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  glDrawElements(GL_TRIANGLES, 6*len, GL_UNSIGNED_SHORT, 0);

  glDisableVertexAttribArray(p->attr_coord);
  glDisableVertexAttribArray(p->attr_texcoord);
}
