uniform sampler2D uSource;
uniform float uFactor;
uniform float uDelta;

vec2 tex_size = textureSize(uSource,0);
vec2 tex_size_rev = vec2(1.0,1.0)/textureSize(uSource,0);
vec2 toPixCoords(vec2 tex_coords)
{
	return tex_coords*tex_size;
}
vec2 toTexCoords(vec2 pix_coords)
{
	return pix_coords*tex_size_rev;
}

/* Performs one step of the Jacobi iteration */
void main()
{
	vec4 left = texture2D(uSource, gl_TexCoord[0].xy + toTexCoords(vec2(-1.0,0.0)));
	vec4 right = texture2D(uSource, gl_TexCoord[0].xy + toTexCoords(vec2(1.0,0.0)));
	vec4 top = texture2D(uSource, gl_TexCoord[0].xy + toTexCoords(vec2(0.0,1.0)));
	vec4 bottom = texture2D(uSource, gl_TexCoord[0].xy + toTexCoords(vec2(0.0,-1.0)));

	float mult = 1.0/(uFactor*uDelta);
	float denom = 4.0 + mult;

	gl_FragColor = (left + right + top + bottom + mult*texture2D(uSource,gl_TexCoord[0].xy))/denom;
}
