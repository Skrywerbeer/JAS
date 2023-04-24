#version 440
layout(location = 0) in vec2 qt_TexCoord0;
layout(location = 1) in vec4 qt_Vertex;

layout(location = 0) out vec4 fragColor;

layout(std140, binding = 0) uniform buf {
	mat4 qt_Matrix;
	float qt_Opacity;
	// Variables.
	float width;
	float height;
	int radius;
};
layout(binding = 1) uniform sampler2D source;

void main(void) {
	const float padding = 0.2;
	const vec2 p0 = vec2(padding, padding);
	vec4 average = vec4(0);
	const float step = 0.001;
	for (int i = -radius; i <= radius; ++i) {
		for (int j = -radius; j <= radius; ++j) {
			vec2 point = vec2(qt_TexCoord0.x + i/width,
			                  qt_TexCoord0.y + j/height);
			average += texture(source, point);
		}
	}
	average.rgba /= (2*radius + 1)*(2*radius + 1);
//	vec4 base = texture(source, qt_TexCoord0);
	fragColor = average;
}
