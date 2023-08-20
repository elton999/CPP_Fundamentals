#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "GL/glew.h"
#include <string>

using std::string;

class ShaderProgram
{
public:

	ShaderProgram();
	~ShaderProgram();

	enum ShaderType
	{
		VERTX,
		FRAGMENT,
		PROGRAM
	};

	bool loadShaders(const char* vsFilename, const char* fsFilename);
	void use();

private:
	string fileToString(const string& filename);
	void checkCompilerErrors(GLuint shader, ShaderType type);

	GLuint mHandle;

};

#endif