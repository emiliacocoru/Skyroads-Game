#version 330
uniform sampler2D texture_1;

in vec2 texcoord;
layout(location = 0) out vec4 out_color;

void main()
{
	vec4 text_1 = texture2D(texture_1, texcoord);

  out_color = text_1;
  if (out_color.a < 0.5f) {
    discard;
  }
}
