#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
	float dist;
} ubo;

layout(location = 0) in vec3 vertLoc;
layout(location = 1) in float color;
layout(location = 2) in vec3 offset;

layout(location = 0) out vec4 fragColor;

out gl_PerVertex {
    vec4 gl_Position;
};

void main() {
    gl_Position = ubo.proj * ubo.view * ubo.model * vec4(vertLoc + offset, 1.0);
	vec4 offsLoc = ubo.view * ubo.model  * vec4(offset, 1.0);
	vec4 temp = vec4(color, 0.0f, sqrt(1.0-(color*color)), 1.0f);
	if(offsLoc.z>ubo.dist){
		temp.a = 0.0f;
	}
	
	if(color==0.0f){
		temp.a = 0.0f;
	}
	fragColor=temp;
}