#pragma once

#include "CommonIncludes.hpp"
	
class GL_Shader
{		
	private:
		bool compiled; 
	public:
		//shader source	
		std::string vertSrc;
		std::string fragSrc;
		std::string geometrySrc;
	
		//shader programs
		int programShaderObject;
		int vertexShaderObject;
		int geometryShaderObject;
		int fragmentShaderObject;

		GL_Shader();
		void Compile();

};