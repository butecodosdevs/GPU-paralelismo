#include "linear_algebra.hpp"
#include <glm/gtc/matrix_transform.hpp>

void chorume::linear_algebra_calculate_camera_look(float m_x, float m_y, float rel_x, float rel_y) {
    chorume::application.camera.yaw += rel_x * chorume::application.camera.sensitivity;
    chorume::application.camera.pitch -= rel_y * chorume::application.camera.sensitivity;

    if (chorume::application.camera.pitch > 89.0f) {
        chorume::application.camera.pitch = 89.0f;
    }

    if (chorume::application.camera.pitch < -89.0f) {
        chorume::application.camera.pitch = -89.0f;
    }

    /*
     * Look At e uma matriz super importante,
     * pois nela e aonde podemos definir
     * o controle da camera e alterar a posicao
     * dos objetos, em realidade, nos nao se movemos, sao os objetos.
     */

    float yaw {glm::radians(chorume::application.camera.yaw)};
    float pitch {glm::radians(chorume::application.camera.pitch)};

    /*
     * Para calcular o look at, precisamos saber a direcao que
     * estamos olhando.
     */
    glm::vec3 direction {
        glm::cos(yaw) * glm::cos(pitch),
        glm::sin(pitch),
        glm::sin(yaw) * glm::cos(pitch)
    };

    /* Normalizamos essa direcao. */
    direction = glm::normalize(direction);

    /* up diz sobre o eixo que estamos. */
    glm::vec3 up {0.0f, 1.0f, 0.0f};

    /*
     * Cross diz sobre o vetor perpendicular ao eixo que
     * estamos (up) em relacao a direcao que estamos olhando.
     * Normalizado pois queremos a direcao desse vetor perpendicular.
     */
    glm::vec3 camera_right {glm::normalize(glm::cross(direction, up))};

    /*
     * Do mesmo modo, queremos saber sobre a direcao perpendicular em relacao
     * ao eixo que estamos, queremos saber sobre a direcao do eixo up (em relacao ao right).
     */
    glm::vec3 camera_up {glm::normalize(glm::cross(camera_right, direction))};

    /*
     * Look At e uma matriz super importante para a transformacao linear,
     * para o espaco normalizado da GPU/API.
     */

    glm::vec3 eye {chorume::application.camera.position};
    glm::vec3 center {eye + direction};
    up = camera_up;

    glm::vec3 f {glm::normalize(center - eye)};
    glm::vec3 s {glm::normalize(glm::cross(f, up))};
    glm::vec3 u {glm::cross(s, f)};

    /* Uma matriz identidade (vale com 1) */
    /* chorume::application.camera.mat_look_at_view = glm::mat4 {
         s.x,  s.y,  s.z, 0.0f,
         u.x,  u.y,  u.z, 0.0f,
        -f.x, -f.y, -f.z, 0.0f,
        -glm::dot(s, eye), -glm::dot(u, eye), glm::dot(f, eye), 1.0f
    }; */

    chorume::application.camera.mat_look_at_view = glm::lookAt(chorume::application.camera.position, 
                                                               chorume::application.camera.position + direction, camera_up);
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