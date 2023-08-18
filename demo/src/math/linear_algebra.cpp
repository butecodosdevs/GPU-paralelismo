#include "linear_algebra.hpp"
#include <glm/gtc/matrix_transform.hpp>

void chorume::linear_algebra_calculate_camera_look(float m_x, float m_y, float rel_x, float rel_y) {
    chorume::application.camera.yaw += rel_x * chorume::application.camera.sensitivity;
    chorume::application.camera.pitch -= rel_y * chorume::application.camera.sensitivity;

    float yaw {glm::radians(chorume::application.camera.yaw)};
    float pitch {glm::radians(chorume::application.camera.pitch)};

    glm::vec3 direction {
        glm::cos(yaw) * glm::cos(pitch),
        glm::sin(pitch),
        glm::sin(yaw) * glm::cos(pitch)
    };

    direction = glm::normalize(direction);

    glm::vec3 up {0.0f, 1.0f, 0.0f};
    glm::vec3 camera_right {glm::normalize(glm::cross(direction, up))};
    glm::vec3 camera_up {glm::normalize(glm::cross(camera_right, direction))};

    chorume::application.camera.mat_look_at_view = glm::lookAt(chorume::application.camera.position, chorume::application.camera.position + direction, camera_up);
}

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