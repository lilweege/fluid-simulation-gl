attribute vec4 position;
attribute vec4 color;
varying vec4 fragmentColor;
uniform mat4 mvp;

void main()
{
	gl_PointSize = 10.0;
	gl_Position = mvp * position;
	fragmentColor = color;
}

