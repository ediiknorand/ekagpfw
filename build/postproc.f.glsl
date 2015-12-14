uniform sampler2D texture;
uniform float offset;
varying vec2 f_texcoord;

void main(void)
{
  vec2 texcoord = f_texcoord;
  texcoord.x += sin(texcoord.y * 4*2*3.14159 + 64*offset)/70;
  gl_FragColor = vec4(1.0, 1.0, 1.0, 0.0) - texture2D(texture, texcoord);
}
