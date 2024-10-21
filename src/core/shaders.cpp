#include "pixl/src/core/debug.hpp"
#include "pixl/src/pixl-precomp.hpp"
#include "pixl/src/core/shaders.hpp"

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

namespace pixl {

Shader::Shader(const std::string &vShaderPath, const std::string &fShaderPath) {
    std::string vShaderCode;
    std::string fShaderCode;

    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
    fShaderFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);

    try {
        // open the shader file
        vShaderFile.open(vShaderPath);
        fShaderFile.open(fShaderPath);

        // read contents from the shader buffer
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        // close the file handlers
        vShaderFile.close();
        fShaderFile.close();

        vShaderCode = vShaderStream.str();
        fShaderCode = fShaderStream.str();

    } catch (std::ifstream::failure error) {
        errorN("Failed to read shader file \n");
    }

    const char *vShader = vShaderCode.c_str();
    const char *fShader = fShaderCode.c_str();

    unsigned int vertex, fragment;
    int success;
    char infolog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShader, NULL);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, nullptr, infolog);
        error("Failed to compile Shader %s", infolog);
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShader, NULL);
    glCompileShader(fragment);

    int fSuccess;
    char finfolog[512];

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &fSuccess);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, nullptr, finfolog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED %s", infolog);
    }

    _programID = glCreateProgram();
    glAttachShader(_programID, vertex);
    glAttachShader(_programID, fragment);
    glLinkProgram(_programID);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader() {
    glDeleteProgram(_programID);
}

void Shader::use() {
    glUseProgram(_programID);
}

void Shader::setInt(const std::string &uniformName, int value) const {
    GLint id = glGetUniformLocation(_programID, uniformName.c_str());
    glUniform1i(id, value);
}

void Shader::setBool(const std::string &uniformName, bool value) const {
    GLint id = glGetUniformLocation(_programID, uniformName.c_str());
    glUniform1i(id, (int)value);
}

void Shader::setMat4(const std::string &uniformName, const glm::mat4 &value) const {
    GLint id = glGetUniformLocation(_programID, uniformName.c_str());
    glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setVec3(const std::string &uniformName, const glm::vec3 &value) const {
    GLint id = glGetUniformLocation(_programID, uniformName.c_str());
    glUniform3fv(id, 1, glm::value_ptr(value));

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cout << "ERROR::SHADER::SET_VEC3::" << error << " " << uniformName.c_str() << std::endl;
    }
}

} // namespace pixl

