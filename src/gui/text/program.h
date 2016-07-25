#ifndef H_GUI_TEXT_PROGRAM_H
#define H_GUI_TEXT_PROGRAM_H

#include <GL/glew.h>

typedef struct {
  GLuint id;
  GLint attr_coord;
  GLint attr_texcoord;
  GLint unif_tex;
} GUI_TextProgram;

void gui_text_program(GUI_TextProgram *p, const char *vshader, const char *fshader);
void gui_text_program_delete(GUI_TextProgram *p);

void gui_text_program_enable(GUI_TextProgram *p);
void gui_text_program_disable(GUI_TextProgram *p);

#endif
