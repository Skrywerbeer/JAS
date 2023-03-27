#version 440
layout(location = 0) in vec4 qt_Vertex;
layout(location = 1) in vec2 qt_MultiTexCoord0;
layout(location = 0) out vec2 qt_TexCoord0;
layout(std140, binding = 0) uniform buf {
	mat4 qt_Matrix;
	float qt_Opacity;

	float width;
	float height;
} ubuf;
out gl_PerVertex {
	vec4 gl_Position;
};
layout(location = 2) out vec4 vertColor;

void main(void) {
	const vec2 center = vec2(ubuf.width/2, ubuf.height/2);

	qt_TexCoord0 = qt_MultiTexCoord0;
	vec2 pos = vec2(qt_Vertex.xy - center);
	const float angle = atan(pos.y, pos.x);
	gl_Position = ubuf.qt_Matrix*vec4(center.x + cos(angle)*50,
	                                  center.y + sin(angle)*50,
	                                  -3,
	                                  qt_Vertex.w);
}
