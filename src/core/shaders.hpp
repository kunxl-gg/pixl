#ifndef PIXL_SHADERS_H
#define PIXL_SHADERS_H

#include "pixl/src/pixl-precomp.hpp"

namespace pixl {

class Shader {
public:
    /** Shader Constructor with the shader and fragment path.
     * The file paths must absolute and not relative.
     * @param vShaderPath File path for the vertexShader
     * @param fShaderPath File path for the fragment Shader
     */
    Shader(std::string &vShaderPath, std::string &fShaderPath);

    /** Shader Destructor.
     *  Deletes the shader program.
     */
    ~Shader();

    /** A wrapper around glUseShader.
     *  Should be called each time before
     *  making any draw calls to make the shader program active.
     */
    void use();

    /** Utility methods to set the value of Uniforms.
     *  Add one for each data type you want to support.
     */
    void setBool(const std::string &uniformName, bool value) const;
    void setFloat(const std::string &uniformName, float value) const;
    void setInt(const std::string &uniformName, int value) const;
    void setMat4(const std::string &uniformName, const glm::mat4 &value) const;
    void setVec3(const std::string &uniformName, const glm::vec3 &value) const;

private:
    int _programID;
};

} // namespace pixl

#endif // PIXL_SHADERS_H
