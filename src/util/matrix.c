#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "matrix.h"


GLfloat *matrix4(GLfloat f)
{
  GLfloat *mat = malloc(16*sizeof(GLfloat));
  if(!mat)
    return NULL;
  mat_init(mat, f);
  return mat;
}

void mat_free(GLfloat *mat)
{
  free(mat);
}

void mat_init(GLfloat *mat, GLfloat f)
{
  int i,j;
  for(i = 0; i < 4; i++)
    for(j = 0; j < 4; j++)
      mat[MAT_OFFSET(i,j)] = (i==j?f:0.0f);
}

void mat_mult(GLfloat *mat, GLfloat *m2)
{
  GLfloat m1[16];
  memcpy(m1, mat, 16*sizeof(GLfloat));

  int i,j,k;
  for(i = 0; i < 4; i++)
    for(j = 0; j < 4; j++) {
      mat[MAT_OFFSET(i,j)] = 0.0f;
      for(k = 0; k < 4; k++)
        mat[MAT_OFFSET(i,j)] += m1[MAT_OFFSET(k,j)] * m2[MAT_OFFSET(i,k)];
    }
}

void mat_translate(GLfloat *mat, GLfloat *coord, int card)
{
  switch(card) {
  case MAT_CARD_XY: mat_translate_xy(mat, coord); break;
  case MAT_CARD_XYZ: mat_translate_xyz(mat, coord); break;
  }
}

void mat_translate_xy(GLfloat *mat, GLfloat *coord)
{
  GLfloat m1[16];

  mat_init(m1, 1.0f);
  m1[MAT_OFFSET(3,0)] = coord[0];
  m1[MAT_OFFSET(3,1)] = coord[1];
  mat_mult(mat, m1);
}

void mat_translate_xyz(GLfloat *mat, GLfloat *coord)
{
  GLfloat m1[16];

  mat_init(m1, 1.0f);
  m1[MAT_OFFSET(3,0)] = coord[0];
  m1[MAT_OFFSET(3,1)] = coord[1];
  m1[MAT_OFFSET(3,2)] = coord[2];
  mat_mult(mat, m1);
}

void mat_rotate_axis(GLfloat *mat, GLfloat angle, int axis)
{
  switch(axis) {
  case MAT_AXIS_X: mat_rotate_x(mat, angle); break;
  case MAT_AXIS_Y: mat_rotate_y(mat, angle); break;
  case MAT_AXIS_Z: mat_rotate_z(mat, angle); break;
  }
}

void mat_rotate_x(GLfloat *mat, GLfloat angle)
{
  GLfloat m1[16];

  mat_init(m1, 1.0f);
  m1[MAT_OFFSET(1,1)] =  cosf(angle);
  m1[MAT_OFFSET(2,1)] = -sinf(angle);
  m1[MAT_OFFSET(1,2)] =  sinf(angle);
  m1[MAT_OFFSET(2,2)] =  cosf(angle);
  mat_mult(mat, m1);
}

void mat_rotate_y(GLfloat *mat, GLfloat angle)
{
  GLfloat m1[16];

  mat_init(m1, 1.0f);
  m1[MAT_OFFSET(0,0)] =  cosf(angle);
  m1[MAT_OFFSET(2,0)] =  sinf(angle);
  m1[MAT_OFFSET(0,2)] = -sinf(angle);
  m1[MAT_OFFSET(2,2)] =  cosf(angle);
  mat_mult(mat, m1);
}

void mat_rotate_z(GLfloat *mat, GLfloat angle)
{
  GLfloat m1[16];

  mat_init(m1, 1.0f);
  m1[MAT_OFFSET(0,0)] =  cosf(angle);
  m1[MAT_OFFSET(1,0)] = -sinf(angle);
  m1[MAT_OFFSET(0,1)] =  sinf(angle);
  m1[MAT_OFFSET(1,1)] =  cosf(angle);
  mat_mult(mat, m1);
}

void mat_rotate(GLfloat *mat, GLfloat angle, GLfloat *vector, int normed)
{
  GLfloat versor[3];
  versor[0] = vector[0];
  versor[1] = vector[1];
  versor[2] = vector[2];
  if(!normed)
    vec_normalize(versor, vector);

  GLfloat mincos = 1 - cosf(angle);
  GLfloat an_cos = cosf(angle);
  GLfloat an_sin = sinf(angle);
  GLfloat m1[16];
  mat_init(m1, 1.0f);
  m1[MAT_OFFSET(0,0)] = versor[0]*versor[0]*mincos + an_cos;
  m1[MAT_OFFSET(1,0)] = versor[1]*versor[0]*mincos - versor[2]*an_sin;
  m1[MAT_OFFSET(2,0)] = versor[2]*versor[0]*mincos + versor[1]*an_sin;

  m1[MAT_OFFSET(0,1)] = versor[0]*versor[1]*mincos + versor[2]*an_sin;
  m1[MAT_OFFSET(1,1)] = versor[1]*versor[1]*mincos + an_cos;
  m1[MAT_OFFSET(2,1)] = versor[2]*versor[1]*mincos - versor[0]*an_sin;

  m1[MAT_OFFSET(0,2)] = versor[0]*versor[2]*mincos - versor[1]*an_sin;
  m1[MAT_OFFSET(1,2)] = versor[1]*versor[2]*mincos + versor[0]*an_sin;
  m1[MAT_OFFSET(2,2)] = versor[2]*versor[2]*mincos + an_cos;

  mat_mult(mat, m1);
}

void mat_scale(GLfloat *mat, GLfloat sx, GLfloat sy, GLfloat sz)
{
  GLfloat m1[16];

  mat_init(m1, 1.0f);
  m1[MAT_OFFSET(0,0)] = sx;
  m1[MAT_OFFSET(1,1)] = sy;
  m1[MAT_OFFSET(2,2)] = sz;

  mat_mult(mat, m1);
}

/* MVP */

void mat_lookAt(GLfloat *mat, GLfloat *eye, GLfloat *target, GLfloat *up)
{
  GLfloat m1[16];
  mat_init(m1, 1.0f);

  GLfloat zaxis[3] = { eye[0] - target[0], eye[1] - target[1], eye[2] - target[2]};
  vec_normalize(zaxis, zaxis);

  GLfloat xaxis[3];
  vec_cross(xaxis, up, zaxis);
  vec_normalize(xaxis, xaxis);

  GLfloat yaxis[3];
  vec_cross(yaxis, zaxis, xaxis);

  int i;
  for(i = 0; i < 3; i++) {
    m1[MAT_OFFSET(i, 0)] = xaxis[i];
    m1[MAT_OFFSET(i, 1)] = yaxis[i];
    m1[MAT_OFFSET(i, 2)] = zaxis[i];
  }
  m1[MAT_OFFSET(3, 0)] = -vec_dot(xaxis, eye);
  m1[MAT_OFFSET(3, 1)] = -vec_dot(yaxis, eye);
  m1[MAT_OFFSET(3, 2)] = -vec_dot(zaxis, eye);

  mat_mult(mat, m1);
}

void mat_perspective(GLfloat *mat, GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar)
{
  GLfloat m1[16];
  mat_init(m1, 1.0f);

  GLfloat f = 1.0f/tanf(fovy/2);

  m1[MAT_OFFSET(0,0)] = f/aspect;
  m1[MAT_OFFSET(1,1)] = f;
  m1[MAT_OFFSET(2,2)] = (zFar+zNear)/(zNear-zFar);
  m1[MAT_OFFSET(3,2)] = 2*zFar*zNear/(zNear-zFar);
  m1[MAT_OFFSET(2,3)] = -1.0f;

  mat_mult(mat, m1);
}

/* Orthographic */
void mat_ortho(GLfloat *mat, GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far)
{
  GLfloat m1[16];
  mat_init(m1, 1.0f);

  m1[MAT_OFFSET(0,0)] = 2.0f/(right-left);
  m1[MAT_OFFSET(1,1)] = 2.0f/(top-bottom);
  m1[MAT_OFFSET(2,2)] = 2.0f/(far-near);
  m1[MAT_OFFSET(3,0)] = -(right+left)/(right-left);
  m1[MAT_OFFSET(3,1)] = -(top+bottom)/(top-bottom);
  m1[MAT_OFFSET(3,2)] = -(far+near)/(far-near);

  mat_mult(mat, m1);
}

/* util util */
void vec_normalize(GLfloat *vec, GLfloat *v1)
{
  GLfloat norm = sqrtf(v1[0]*v1[0] + v1[1]*v1[1] + v1[2]*v1[2]);
  vec[0] = v1[0]/norm;
  vec[1] = v1[1]/norm;
  vec[2] = v1[2]/norm;
}

GLfloat vec_dot(GLfloat *v1, GLfloat *v2)
{
  return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}

void vec_cross(GLfloat *vec, GLfloat *v1, GLfloat *v2)
{
  vec[0] =  v1[1]*v2[2] - v2[1]*v1[2];
  vec[1] = -v1[0]*v2[2] + v2[0]*v1[2];
  vec[2] =  v1[0]*v2[1] - v2[0]*v1[1];
}
