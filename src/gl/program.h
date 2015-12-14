#ifndef H_GL_PROGRAM_H
#define H_GL_PROGRAM_H

#include <GL/glew.h>

GLint program_attribute(GLuint program_id, const char* name);
GLint program_uniform(GLuint program_id, const char* name);
GLuint program_create(const char *vshader, const char *fshader);

#endif
