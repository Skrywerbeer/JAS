#version 440
layout(location = 0) in vec4 qt_Vertex;
layout(location = 1) in vec2 qt_MultiTexCoord0;
layout(location = 0) out vec2 qt_TexCoord0;

layout(std140, binding = 0) uniform buf {
	mat4 qt_Matrix;
	float qt_Opacity;

	float width;
	float height;
	vec2 scale;
};
out gl_PerVertex {
	vec4 gl_Position;
};

bool inRect(vec2 p, vec2 topLeft, vec2 bottomRight) {
	if (any(lessThan(p, topLeft)) || any(greaterThan(p, bottomRight)))
		return false;
	return true;
}

void main(void) {
	const vec2 center = vec2(width/2, height/2);

	const mat4 translation1 = mat4(vec4(1, 0, 0, 0),
	                               vec4(0, 1, 0, 0),
	                               vec4(0, 0, 1, 0),
	                               vec4(-center.x, -center.y, 0, 1));
	const mat4 scale = mat4(vec4(scale.x, 0, 0, 0),
	                        vec4(0, scale.y, 0, 0),
	                        vec4(0, 0, 1, 0),
	                        vec4(0, 0, 0, 1));
	const mat4 translation2 = mat4(vec4(1, 0, 0, 0),
	                               vec4(0, 1, 0, 0),
	                               vec4(0, 0, 1, 0),
	                               vec4(center.x, center.y, 0, 1));

	qt_TexCoord0 = qt_MultiTexCoord0;
	vec4 transformed = translation2*scale*translation1*qt_Vertex;
	vec4 pos = qt_Matrix*transformed;
	gl_Position = vec4(pos.xy, -1, pos.w);
//	gl_Position = ubuf.qt_Matrix*translation*qt_Vertex;
}
