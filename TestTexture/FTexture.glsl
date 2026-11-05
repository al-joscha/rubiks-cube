#version 330

uniform sampler2D baseColor;

in vec2 texCoord;
out vec4 color;

void main()
{
	color = vec4(texCoord.x, texCoord.y, 0.0, 1.0);
	// color = texture(baseColor, texCoord);
}