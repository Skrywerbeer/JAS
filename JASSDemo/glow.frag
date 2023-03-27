#version 440
layout(location = 0) in vec2 qt_TexCoord0;
layout(location = 1) in vec4 qt_Vertex;
layout(location = 2) in vec4 vertColor;

layout(location = 0) out vec4 fragColor;

layout(std140, binding = 0) uniform buf {
	mat4 qt_Matrix;
	float qt_Opacity;
	// Variables.
	float width;
	float height;
};
layout(binding = 1) uniform sampler2D source;
void main(void) {

	vec4 base = texture(source, qt_TexCoord0);
	if (qt_TexCoord0.x == 0.5)
		fragColor = base;
	else
		fragColor = (1.0/pow(distance(qt_TexCoord0.xy, vec2(0.5, 0.5)), 2))*
		        base/10;
}
