#include "GL_Shader.hpp"

	
GL_Shader::GL_Shader()
{
	compiled = false; 
}

	
void GL_Shader::Compile()
{
	GETGL
	bool hasGeometry=geometrySrc.size()>0;

	//make array to pointer for source code (needed for opengl )
	const char* vsrc[1];
	const char* fsrc[1];
	const char* gsrc[1];
	vsrc[0] = vertSrc.c_str();
	fsrc[0] = fragSrc.c_str();
	if(hasGeometry)gsrc[0] = geometrySrc.c_str();
	
	//compile vertex and fragment shaders from source
	vertexShaderObject = gl->glCreateShader(GL_VERTEX_SHADER);
	gl->glShaderSource(vertexShaderObject, 1, vsrc, NULL);
	gl->glCompileShader(vertexShaderObject);
	fragmentShaderObject = gl->glCreateShader(GL_FRAGMENT_SHADER);
	gl->glShaderSource(fragmentShaderObject, 1, fsrc, NULL);
	gl->glCompileShader(fragmentShaderObject);
	if(hasGeometry) {
		geometryShaderObject = gl->glCreateShader(GL_GEOMETRY_SHADER);
		gl->glShaderSource(geometryShaderObject, 1, gsrc, NULL);
		gl->glCompileShader(geometryShaderObject); 
	}
	std::cout << "Shader:Compile: Linking shader" << std::endl;
	
	//link vertex and fragment shader to create shader program object
	programShaderObject = gl->glCreateProgram();
	gl->glAttachShader(programShaderObject, vertexShaderObject);
	gl->glAttachShader(programShaderObject, fragmentShaderObject);
	if(hasGeometry) gl->glAttachShader(programShaderObject, geometryShaderObject);
	gl->glLinkProgram(programShaderObject);
	std::cout << "Shader:Compile: checking shader status" << std::endl;
	
	//Check status of shader and log any compile time errors
	int linkStatus;
	gl->glGetProgramiv(programShaderObject, GL_LINK_STATUS, &linkStatus);
	if (linkStatus != GL_TRUE) 
	{
		char log[5000];
		int lglen; 
		gl->glGetProgramInfoLog(programShaderObject, 5000, &lglen, log);
		std::cerr << "Shader:Compile: Could not link program: " << std::endl;
		std::cerr << log << std::endl;
		gl->glGetShaderInfoLog(vertexShaderObject, 5000, &lglen, log);
		std::cerr << "vertex shader log:\n" << log << std::endl;
		gl->glGetShaderInfoLog(fragmentShaderObject, 5000, &lglen, log);
		std::cerr << "fragment shader log:\n" << log << std::endl;
		gl->glDeleteProgram(programShaderObject);
		programShaderObject = 0;
	}
	else
	{
		std::cout << "Shader:Compile: compile success " << std::endl;
		compiled = true; 
	}
}

