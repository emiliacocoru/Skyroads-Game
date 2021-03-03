#version 330
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float time;

out vec2 texcoord;
out vec3 world_position;
out vec3 world_normal;

void main()
{
	// TODO : pass v_texture_coord as output to Fragment Shader
	if (time >= 0) {
		texcoord = v_texture_coord;
		texcoord.x = v_texture_coord.x - time / 5;
	} else {
		texcoord = v_texture_coord;
	}
	
	world_position = vec3(Model * vec4(v_position, 1));
	world_normal = normalize(vec3(Model * vec4(v_normal, 0))); // normala la suprafata

	gl_Position = Projection * View * Model * vec4(v_position, 1.0);
}
