uniform sampler2D substance;
uniform sampler2D velocity;

void main()
{
	gl_FragColor = texture2D(substance,gl_TexCoord[0].xy) + texture2D(velocity,gl_TexCoord[0].xy);
}
