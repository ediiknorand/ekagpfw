attribute vec2 coord;
uniform sampler2D texture;
varying vec2 f_texcoord;

void main(void)
{
  gl_Position = vec4(coord, 0.0, 1.0);
  f_texcoord = (coord + 1.0) / 2.0;
}
