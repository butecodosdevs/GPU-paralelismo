#ifndef CHORUME_MATH_LINEAR_ALGEBRA_H
#define CHORUME_MATH_LINEAR_ALGEBRA_H

#include "platform/platform.hpp"

namespace chorume {
    void linear_algebra_calculate_camera_look(float m_x, float m_y, float rel_x, float rel_y);
    glm::mat4 linear_algebra_calculate_orthographic_matrix(float left, float right, float bottom, float top);
}

#endif