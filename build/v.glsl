attribute vec2 coord;

void main(void)
{
  gl_Position = vec4(coord, 0.0, 1.0);
}
