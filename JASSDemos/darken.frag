#version 440
//uniform sampler2D qt_Texture0;
layout(location = 0) in vec2 qt_TexCoord0;
layout(location = 1) in vec4 qt_Vertex;
layout(location = 0) out vec4 fragColor;
layout(std140, binding = 0) uniform buf {
	mat4 qt_Matrix;
	float qt_Opacity;
	float percentColor;
};
layout(binding = 1) uniform sampler2D source;

void main(void) {
	vec4 tex = texture(source, qt_TexCoord0);
	fragColor = vec4(tex.rgb*percentColor, tex.a)*qt_Opacity;
}
