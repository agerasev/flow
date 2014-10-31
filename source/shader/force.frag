uniform sampler2D uVelocity;
uniform float uDelta;
uniform vec2 uForce;

void main()
{
	vec4 current = texture2D(uVelocity, gl_TexCoord[0].xy);
	gl_FragColor = current + uDelta*vec4(uForce*current.w,0.0,0.0);
}
