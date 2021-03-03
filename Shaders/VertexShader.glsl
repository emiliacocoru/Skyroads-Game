#version 330

// get vertex attributes from each location
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texture;
layout(location = 3) in vec3 color;


// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float Deformation;
uniform float Time;

// output values to fragment shader
out vec3 fragment_normal;
out vec3 fragment_color;
out float noise;
out float deformation;
out vec3 world_position;
out vec3 world_normal;


float rand3D(in vec3 co){
    return fract(sin(dot(co.xyz ,vec3(40.9898, 50.233, 180.7272))) * 43758.5453);
}

float turbulence (vec3 p) {
	float t = -0.5f;
	for (float i = 0.1f; i <= 10.f; i++) {
		t += abs(rand3D(vec3(pow(2.f, i) * p)));
	}
	return t;
}

void main()
{
	fragment_normal = normal;
  fragment_color = color;
	noise = 10.f * -0.04f * turbulence(0.5f * normal + 0.0000001 * Time);
  float displacement = -10.f * noise + 5.0 * rand3D(0.05f * position);

	deformation = Deformation;
	vec3 final;

  world_position = vec3(Model * vec4(position, 1));
  world_normal = normalize(vec3(Model * vec4(normal, 0))); // normala la suprafata


	if (Deformation == 0) {
		final = position;
	} else {
		final = position + normal * displacement;
	}
	gl_Position = Projection * View * Model * vec4(final, 1.0);
}
