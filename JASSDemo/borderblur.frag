#version 440
layout(location = 0) in vec2 qt_TexCoord0;
layout(location = 1) in vec4 qt_Vertex;

layout(location = 0) out vec4 fragColor;

layout(std140, binding = 0) uniform buf {
	mat4 qt_Matrix;
	float qt_Opacity;
	// Variables.
};
layout(binding = 1) uniform sampler2D source;

void main(void) {
	const float padding = 0.2;
	const vec2 p0 = vec2(padding, padding);
	vec4 average = vec4(0);
	const float step = 0.001;
	for (int i = -3; i <= 3; ++i) {
		for (int j = -3; j <= 3; ++j) {
			vec2 point = vec2(qt_TexCoord0.x + step*i,
			                  qt_TexCoord0.y + step*j);
			average += texture(source, point);
		}
	}
	average.xyz /= 49;
//	vec4 base = texture(source, qt_TexCoord0);
	fragColor = average;
}
