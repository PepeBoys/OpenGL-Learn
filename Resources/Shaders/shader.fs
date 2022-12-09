#version 460

in vec3 normal;
in vec3 fragPos;

out vec4 fragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main() {
	float ambient = 0.1;
	
	vec3 lightDir = normalize(lightPos - fragPos);
	float diffuse = max(dot(normal, lightDir), 0.0);
	
	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	float specular = pow(max(dot(viewDir, reflectDir), 0.0), 32) * specularStrength;
	
	vec3 result = objectColor * lightColor * (ambient + diffuse + specular);
	fragColor = vec4(result, 1.0);
};