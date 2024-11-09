//
//  Uniform.h
//  opengl-expe
//
//  Created by EL KHANTOUR Nassim on 31/10/2024.
//

#ifndef Uniform_h
#define Uniform_h

#include <variant>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>

enum class UniformType{
    INT,
    FLOAT,
    VECTOR_3,
    VECTOR_2,
    MATRIX_4,
    SAMPLER_2D,
    UNIFORM_BLOCK,
    BOOLEAN
};

using UniformValue = std::variant<bool, int, float, glm::vec2, glm::vec3, glm::mat4, GLuint>;

struct Uniform{
    UniformType type;
    UniformValue value;
    std::string name;
};

using UniformList = std::vector<Uniform>;


#endif /* Uniform_h */
