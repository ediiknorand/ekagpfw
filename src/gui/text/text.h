#ifndef H_GUI_TEXT_H
#define H_GUI_TEXT_H

#include "atlas.h"
#include "program.h"
#include "vbo.h"
#include "ibo.h"

void gui_text_draw(GUI_TextProgram *p, GLuint vbo, GLuint ibo, GLuint tex, int len);

#endif
