#ifndef H_UTIL_MATRIX_H
#define H_UTIL_MATRIX_H

#include <GL/glew.h>

#define MAT_OFFSET(i,j) (j+4*i)

#define MAT_CARD_XY 0
#define MAT_CARD_XYZ 1

#define MAT_AXIS_X 0
#define MAT_AXIS_Y 1
#define MAT_AXIS_Z 2

GLfloat *matrix4(GLfloat f);
void mat_free(GLfloat *mat);

void mat_init(GLfloat *mat, GLfloat f);

void mat_mult(GLfloat *m1, GLfloat *m2);

void mat_translate(GLfloat *mat, GLfloat *coord, int card);

void mat_translate_xy(GLfloat *mat, GLfloat *coord);
void mat_translate_xyz(GLfloat *mat, GLfloat *coord);

void mat_rotate_axis(GLfloat *mat, GLfloat angle, int axis);

void mat_rotate_x(GLfloat *mat, GLfloat angle);
void mat_rotate_y(GLfloat *mat, GLfloat angle);
void mat_rotate_z(GLfloat *mat, GLfloat angle);

void mat_rotate(GLfloat *mat, GLfloat angle, GLfloat *vector, int normed);

void mat_scale(GLfloat *mat, GLfloat sx, GLfloat sy, GLfloat sz);

/* MVP */
void mat_lookAt(GLfloat *mat, GLfloat *eye, GLfloat *target, GLfloat *up); /* view matrix */
void mat_perspective(GLfloat *mat, GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar);

/* Orthographic */
void mat_ortho(GLfloat *mat, GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far);
/* util util */
void vec_normalize(GLfloat *vec, GLfloat *v1);
GLfloat vec_dot(GLfloat *v1, GLfloat *v2);
void vec_cross(GLfloat *vec, GLfloat *v1, GLfloat *v2);

#endif
