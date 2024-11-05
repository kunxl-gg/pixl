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

        successN("Read Shader %s\n", vShaderPath.c_str());
        successN("Read Shader %s\n", fShaderPath.c_str());

    } catch (std::ifstream::failure error) {
        errorN("Failed to read shader file %s\n", error.what());
    }

    const char *vShader = vShaderCode.c_str();
    const char *fShader = fShaderCode.c_str();

    unsigned int vertex, fragment;
    int success;
    char infolog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShader, NULL);
    glCompileShader(vertex);

    glGetShaderInfoLog(vertex, 512, nullptr, infolog);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        errorN("Failed to compile Shader %s\n", infolog);
    } else {
        successN("Compiled Shader %s\n", vShaderPath.c_str());
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShader, NULL);
    glCompileShader(fragment);

    glGetShaderInfoLog(fragment, 512, nullptr, infolog);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        errorN("Failed to Compile Shader %s\n", infolog);
    } else {
        successN("Compiled Shader %s\n", fShaderPath.c_str());
    }

    _programID = glCreateProgram();
    glAttachShader(_programID, vertex);
    glAttachShader(_programID, fragment);
    glLinkProgram(_programID);

    GLint programSuccess;
    glGetProgramiv(_programID, GL_LINK_STATUS, &programSuccess);
    if (!programSuccess) {
        glGetProgramInfoLog(_programID, 512, nullptr, infolog);
        errorN("Failed to link program %s\n", infolog);
    } else {
        successN("Linked Program %d\n", _programID);
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader() {
    debug("Deleting Shader %d", _programID);
    glDeleteProgram(_programID);
}

void Shader::use() {
    glUseProgram(_programID);
}

void Shader::setInt(const std::string &uniformName, int value) const {
    GLint id = glGetUniformLocation(_programID, uniformName.c_str());
    glUniform1i(id, value);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {

        errorN("ERROR::SHADER::SET_INT::%d %s\n", error, uniformName.c_str());
    }
}

void Shader::setBool(const std::string &uniformName, bool value) const {
    GLint id = glGetUniformLocation(_programID, uniformName.c_str());
    glUniform1i(id, (int)value);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        errorN("ERROR::SHADER::SET_BOOL::%d %s\n", error, uniformName.c_str());
    }
}

void Shader::setMat4(const std::string &uniformName, const glm::mat4 &value) const {
    debug("Setting Mat4 for program %d", _programID);
    glUseProgram(_programID);

    GLint currentProgram;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
    if (currentProgram != _programID) {
        errorN("Failed to activate shader program: expected %d, got %d\n", _programID, currentProgram);
    }

    GLint id = glGetUniformLocation(_programID, uniformName.c_str());
    glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(value));

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        errorN("ERROR::SHADER::SET_MAT4::%d %s\n", error, uniformName.c_str());
    }
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

