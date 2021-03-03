#version 330
in vec3 fragment_normal;
in vec3 fragment_color;
in float noise;
in float deformation;

uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 light_position2;
uniform vec3 light_position3;
uniform vec3 light_position4;
uniform vec3 light_position5;

uniform vec3 eye_position;
uniform float spotLight;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;
uniform float angle;

uniform vec3 object_color;

in vec2 texcoord;
in vec3 world_position;
in vec3 world_normal;

layout(location = 0) out vec4 out_color;

void main() {

	vec3 N = normalize(world_normal);
	float ka = 1.5f; // constanta de reflexie ambientala a materialului
	float light_intensity = 30.f; // intensitatea luminii
	float global_light = 0.4f; // intensitatea ambientala a luminii
	float distances;
	float attenuation_factor;

	float light_intensity_mini = 50.f;
	float ambient_light = ka * global_light;

	vec3 L = normalize(light_position - world_position); // vectorul directiei luminii incidente
	vec3 V = normalize(eye_position - world_position);
	vec3 H = normalize(L + V);
	vec3 R = normalize(reflect(-L, N));
	float specular_light = 0;
	vec3 color;

	// light 2
	vec3 L2 = normalize(light_position2 - world_position);
	vec3 R2 = normalize(reflect(-L2, N));
	float diffuse_light2 = material_kd * light_intensity_mini* max(dot(N, L2), 0);
	specular_light = 0;
	if (diffuse_light2 > 0.f){
		specular_light = material_ks * light_intensity_mini * pow(max(dot(V, R2), 0), material_shininess);
	}

	distances = 3 * distance(light_position2, world_position);
	attenuation_factor	= 1 / (1 + distances * distances);
	color = vec3(1) * (ambient_light + attenuation_factor * (diffuse_light2 + specular_light));


	// light 3
	vec3 L3 = normalize(light_position3 - world_position);
	vec3 R3 = normalize(reflect(-L3, N));
	float diffuse_light3 = material_kd * light_intensity_mini * max(dot(N, L3), 0);
	specular_light = 0;
	if (diffuse_light3 > 0.f){
		specular_light = material_ks * light_intensity_mini * pow(max(dot(V, R3), 0), material_shininess);
	}

	distances = 3 * distance(light_position3, world_position);
	attenuation_factor	= 1 / (1 + distances * distances);
	color *= vec3(1) * (ambient_light + attenuation_factor * (diffuse_light3 + specular_light));

	// light 4
	vec3 L4 = normalize(light_position4 - world_position);
	vec3 R4 = normalize(reflect(-L4, N));
	float diffuse_light4 = material_kd * light_intensity_mini * max(dot(N, L4), 0);
	specular_light = 0;
	if (diffuse_light4 > 0.f){
		specular_light = material_ks * light_intensity_mini * pow(max(dot(V, R4), 0), material_shininess);
	}

	distances = 3 * distance(light_position4, world_position);
	attenuation_factor	= 1 / (1 + distances * distances);
	color *= vec3(1) * (ambient_light + attenuation_factor * (diffuse_light4 + specular_light));

	// light 5
	vec3 L5 = normalize(light_position5 - world_position);
	vec3 R5 = normalize(reflect(-L5, N));
	float diffuse_light5 = material_kd * light_intensity_mini * max(dot(N, L5), 0);
	specular_light = 0;
	if (diffuse_light5 > 0.f){
		specular_light = material_ks * light_intensity_mini* pow(max(dot(V, R5), 0), material_shininess);
	}

	distances = 5 * distance(light_position5, world_position);
	attenuation_factor	= 1 / (1 + distances * distances);
	color *= vec3(1) * (ambient_light + attenuation_factor * (diffuse_light5 + specular_light));


	// spotlight
	float cut_off = radians(90);
	float spot_light = dot(-L, light_direction);
	float spot_light_limit = cos(cut_off);
	specular_light = 0;
	float diffuse_light = material_kd * light_intensity * max(dot(N, L), 0);

	float light = 0.f;
	if (spot_light > spot_light_limit) {
		float linear_att = (spot_light - spot_light_limit) / (1.f - spot_light_limit);
		float light_att_factor = pow(linear_att, 2);
		light = ambient_light + light_att_factor * (diffuse_light + specular_light);
	} else {
		light = ambient_light;
	}
	color *= vec3(1) * light;

	out_color = vec4(vec3(1, 1, 1), 1);

	if (deformation == 1.f) {
	  out_color = vec4(fragment_normal * (1.2f - 0.1f * noise), 1);
	}

	out_color *= vec4(color, 1);
}
