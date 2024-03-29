#include "ShaderProgram.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "glm/gtc/type_ptr.hpp"

ShaderProgram::ShaderProgram() : mHandle(0)
{

}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(mHandle);
}

bool ShaderProgram::loadShaders(const char* vsFilename, const char* fsFilename)
{
    string vsString = fileToString(vsFilename);
    string fsString = fileToString(fsFilename);
    const GLchar* vsSourcePtr = vsString.c_str();
    const GLchar* fsSourcePtr = fsString.c_str();

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vs, 1, &vsSourcePtr, NULL);
    glShaderSource(fs, 1, &fsSourcePtr, NULL);
    
    glCompileShader(vs);
    checkCompilerErrors(vs, VERTX);

    glCompileShader(fs);
    checkCompilerErrors(fs, FRAGMENT);

    mHandle = glCreateProgram();
    glAttachShader(mHandle, vs);
    glAttachShader(mHandle, fs);
    glLinkProgram(mHandle);

    checkCompilerErrors(mHandle, PROGRAM);

    glDeleteShader(vs);
    glDeleteShader(fs);

	return true;
}

void ShaderProgram::use()
{
	if (mHandle > 0)
		glUseProgram(mHandle);
}

string ShaderProgram::fileToString(const string& filename)
{
	std::stringstream ss;
	std::ifstream file;

	try
	{
		file.open(filename, std::ios::in);

		if (!file.fail())
		{
			ss << file.rdbuf();
		}

		file.close();
	}
	catch (std::exception ex)
	{
		std::cerr << "Error reading shader filename!" << std::endl;
	}

	return ss.str();
}

void ShaderProgram::checkCompilerErrors(GLuint shader, ShaderType type)
{
    int status = 0;

    if (type == PROGRAM)
    {
        glGetProgramiv(mHandle, GL_LINK_STATUS, &status);
        if (status == GL_FALSE)
        {
            GLint lenght = 0;
            glGetProgramiv(mHandle, GL_INFO_LOG_LENGTH, &lenght);

            string errorLog(lenght, '  ');
            glGetProgramInfoLog(mHandle, lenght, &lenght, &errorLog[0]);

            std::cerr << "Error! Program failed to link" << errorLog << std::endl;
        }
    }
    else
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        if (status = GL_FALSE)
        {
            GLint lenght = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &lenght);

            string errorLog(lenght, '  ');
            glGetShaderInfoLog(shader, lenght, &lenght, &errorLog[0]);

            std::cerr << "Error! shader failed to compile" << errorLog << std::endl;
        }
    }
}

GLuint ShaderProgram::getProgram() const
{
    return mHandle;
}

GLint ShaderProgram::getUniformLocation(const GLchar* name)
{
    std::map<string, GLint>::iterator it = mUniformLocations.find(name);

    if (it == mUniformLocations.end())
        mUniformLocations[name] = glGetUniformLocation(mHandle, name);

    return mUniformLocations[name];
}

void ShaderProgram::setUniform(const GLchar* name, const glm::vec2& v)
{
    GLint loc = getUniformLocation(name);
    glUniform2f(loc,v.x, v.y);
}

void ShaderProgram::setUniform(const GLchar* name, const glm::vec3& v)
{
    GLint loc = getUniformLocation(name);
    glUniform3f(loc, v.x, v.y, v.z);
}

void ShaderProgram::setUniform(const GLchar* name, const glm::vec4& v)
{
    GLint loc = getUniformLocation(name);
    glUniform4f(loc, v.x, v.y, v.z, v.w);
}

void ShaderProgram::setUniform(const GLchar* name, const glm::mat4& m)
{
    GLint loc = getUniformLocation(name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(m));
}

void ShaderProgram::setUniform(const GLchar* name, const GLint& m)
{
    GLint loc = getUniformLocation(name);
    glUniform1i(loc, m);
}