uniform sampler2D uVelocity;
uniform sampler2D uSource;
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
void main()
{
	gl_FragColor = texture2D(uSource, gl_TexCoord[0].xy - uDelta*toTexCoords(texture2D(uVelocity, gl_TexCoord[0].xy).xy));
}
