#include "linear_algebra.hpp"

glm::mat4 chorume::linear_algebra_calculate_orthographic_matrix(float left, float right, float bottom, float top) {
    float far {
        1.0f
    };

    float near {
        0.0f
    };

    return glm::mat4 {
        2.0f / (right - left), 0.0f, 0.0f, 0.0f,
        0.0f, 2.0f / (top - bottom), 0.0f, 0.0f,
        0.0f, 0.0f, -2.0f / (far - near), 0.0f,
        -((right + left) / (right - left)), -((top + bottom) / (top - bottom)), -((far + near) / (far - near)), 1.0f
    };
}