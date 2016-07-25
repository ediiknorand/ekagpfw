#include "program.h"
#include "../../gl/program.h"

void gui_text_program(GUI_TextProgram *p, const char *vshader, const char *fshader)
{
  p->id = program_create(vshader, fshader);
  p->attr_coord = program_attribute(p->id, "coord");
  p->attr_texcoord = program_attribute(p->id, "texcoord");
  p->unif_tex = program_uniform(p->id, "tex");
}

void gui_text_program_delete(GUI_TextProgram *p)
{
  glDeleteProgram(p->id);
}

void gui_text_program_enable(GUI_TextProgram *p)
{
  glUseProgram(p->id);
}

void gui_text_program_disable(GUI_TextProgram *p)
{
  glUseProgram(0);
}
