#version 330 core

/*layout(points) in;
layout (triangle_strip, max_vertices = 5)out;

in VS_OUT
{
	vec3 color;
}gs_in[];

out vec3 fColor;

void buildHouse(vec4 pos)
{
	fColor = gs_in[0].color;
	gl_Position = pos + vec4(-0.2, -0.2, 0.0, 0.0);
	EmitVertex();
	
	gl_Position = pos + vec4(0.2, -0.2, 0.0, 0.0);
	EmitVertex();
	
	gl_Position = pos + vec4(-0.2, 0.2, 0.0, 0.0);
	EmitVertex();
	
	gl_Position = pos + vec4(0.2, 0.2, 0.0, 0.0);
	EmitVertex();
	
	gl_Position = pos + vec4(0.0, 0.4, 0.0, 0.0);
	fColor = vec3(1.0, 1.0, 1.0);
	EmitVertex();
	
	EndPrimitive();
}

void main()
{
	buildHouse(gl_in[0].gl_Position);
}*/



/*layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT
{
	vec2 texCoords;
}gs_in[];

out vec2 TexCoords;

uniform float time;

vec4 explode(vec4 pos, vec3 normal)
{
	float magnitude = 2.0;
	vec3 dir = normal * ((sin(time) + 1.0) / 2.0) * magnitude;
	return pos + vec4(dir, 0.0);
}

vec3 GetNormal()
{
	vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
	vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
	return normalize(cross(a,b));
}

void main()
{
	vec3 normal = GetNormal();
	
	gl_Position = explode(gl_in[0].gl_Position, normal);
	TexCoords = gs_in[0].texCoords;
	EmitVertex();
	
	gl_Position = explode(gl_in[1].gl_Position, normal);
	TexCoords = gs_in[1].texCoords;
	EmitVertex();
	
	gl_Position = explode(gl_in[2].gl_Position, normal);
	TexCoords = gs_in[2].texCoords;
	EmitVertex();
	
	EndPrimitive();
}*/

layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

in VS_OUT
{
	vec3 normal;
}gs_in[];

const float MAGNITUDE = 0.2;

void GenerateLine(int idx)
{
	gl_Position = gl_in[idx].gl_Position;
	EmitVertex();
	
	gl_Position = gl_in[idx].gl_Position + vec4(gs_in[idx].normal, 0.0) * MAGNITUDE;
	EmitVertex();
	
	EndPrimitive();
}

void main()
{
	GenerateLine(0);
	GenerateLine(1);
	GenerateLine(2);
}