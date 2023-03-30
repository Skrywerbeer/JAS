#version 440
layout(location = 0) in vec2 qt_TexCoord0;
layout(location = 1) in vec4 vertColor;
layout(location = 2) in float vertOpacity;

layout(location = 0) out vec4 fragColor;

layout(std140, binding = 0) uniform buf {
	mat4 qt_Matrix;
	float qt_Opacity;
	// Variables.
	float width;
	float height;
	vec2 scale;
	float intensity;
};
layout(binding = 1) uniform sampler2D source;

bool inRect(vec2 point, vec2 topLeft, vec2 bottomRight) {
	if (((point.x >= topLeft.x) && (point.x <= bottomRight.x)) &&
	        (point.y >= topLeft.y) && (point.y <= bottomRight.y))
		return true;
	else
		return false;
}

float lin(float edge0, float edge1, float x) {
//	if (x <= edge0)
//		return 0;
//	else if (x >= edge1)
//		return 1;
//	else
	    return clamp((x-edge0)/(edge1 - edge0), 0, 1);
}

float minDistance(float x, float x0, float x1) {
	const float d1 = distance(x, x0);
	const float d2 = distance(x, x1);
	return d1 <= d2 ? d1 : d2;
}

float horzEdgeDistance(vec2 p, vec2 topLeft, vec2 bottomRight) {
	return min(abs(p.x - topLeft.x), abs(p.x - bottomRight.x));
	// 0 <= ^ <= 1.0 - 1/scale.x
}

float horzEdgeDistanceNorm(vec2 p, vec2 topLeft, vec2 bottomRight) {
	return lin(0, (1.0 - 1.0/scale.x)/2.0, horzEdgeDistance(p, topLeft, bottomRight));
	// 0 <= ^ <= 1
}

float vertEdgeDistance(vec2 p, vec2 topLeft, vec2 bottomRight) {
	return min(abs(p.y - topLeft.y), abs(p.y - bottomRight.y));
	// 0 <= ^ <= 1.0 - 1/scale.y
}

float vertEdgeDistanceNorm(vec2 p, vec2 topLeft, vec2 bottomRight) {
	return lin(0, (1.0 - 1.0/scale.y)/2.0, vertEdgeDistance(p, topLeft, bottomRight));
	// 0 <= ^ <= 1
}

float cornerDistance(vec2 p, vec2 topLeft, vec2 bottomRight) {
	const vec2 bottomLeft = vec2(topLeft.x, bottomRight.y);
	const vec2 topRight = vec2(bottomRight.x, topLeft.y);
	return min(distance(p, topLeft),
	           min(distance(p, bottomLeft),
	               min(distance(p, bottomRight), (distance(p, topRight)))));
}

float cornerDistanceNorm(vec2 p, vec2 topLeft, vec2 bottomRight) {
	return pow(pow(horzEdgeDistanceNorm(p, topLeft, bottomRight), 2) +
	            pow(vertEdgeDistanceNorm(p, topLeft, bottomRight), 2), 0.5);
	// 0 <= ^ <= sqrt(2)
}

void main(void) {
	//	const vec4 original = texture(source, vec2(lin(oldTopLeft.x, oldTopRight.x, qt_TexCoord0.x),
	//	                                           lin(oldTopLeft.y, oldBottomLeft.y, qt_TexCoord0.y)));
	// Just sample the color from the of the parent root Rectangle center.
	const vec4 base = texture(source, vec2(0.5));

	const vec2 oldTopLeft = vec2((1.0 - 1.0/scale.x), (1.0 - 1.0/scale.y))/2;
	const vec2 oldTopRight = vec2(1.0 - oldTopLeft.x, oldTopLeft.y);
	const vec2 oldBottomLeft = vec2(oldTopLeft.x, 1.0 - oldTopLeft.y);
	const vec2 oldBottomRight = vec2(oldTopRight.x, oldBottomLeft.y);
	vec4 color;
	if (((qt_TexCoord0.y <= oldTopLeft.y) || (qt_TexCoord0.y >= oldBottomLeft.y)) &&
	        ((qt_TexCoord0.x <= oldTopLeft.x) || (qt_TexCoord0.x >= oldTopRight.x)))
		color = base*pow(1.0 - cornerDistanceNorm(qt_TexCoord0, oldTopLeft, oldBottomRight), 3);
	else if ((qt_TexCoord0.y < oldTopLeft.y) || (qt_TexCoord0.y > oldBottomLeft.y))
		color = base*pow(1.0 - vertEdgeDistanceNorm(qt_TexCoord0, oldTopLeft, oldBottomRight), 3);
	else if ((qt_TexCoord0.x < oldTopLeft.x) || (qt_TexCoord0.x > oldTopRight.x))
		color = base*pow(1 - horzEdgeDistanceNorm(qt_TexCoord0, oldTopLeft, oldBottomRight), 3);
	else
		color = base;

	fragColor = intensity*color*qt_Opacity;
}
