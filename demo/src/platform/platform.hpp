#ifndef CHORUME_PLATFORM_H
#define CHORUME_PLATFORM_H

#include <iostream>
#include <ostream>
#include <sstream>
#include <glm/glm.hpp>

#if defined(WIN32)

#include <SDL2/SDL.h>
#include <GL/glew.h>

#else

#include "SDL2/SDL.h"
#include "GL/glew.h"

#endif // include platform checker]

namespace chorume {
    enum class result {
        ok, failed
    };

    struct extent2d {
    public:
        int32_t w {};
        int32_t h {};
    };

    struct camera {
    public:
        // propiedades espacial da camêra
        glm::mat4 mat_look_at_view {};
        glm::mat4 mat_ortho_view {};
        glm::mat4 mat_perspective {};
        glm::mat4 mat_projection {};
        glm::vec3 position {};
        float     yaw {};
        float     pitch {};
        // configurações e estados da camêra
        float     sensitivity {0.2f};
        float     fov {90.0f};
        float     editor {};
        int8_t    locked {};
        int8_t    moved {};
    };

    extern struct platform {
    public:
        const char     *p_application_name {};
        SDL_Window     *p_sdl_window {};
        bool            running {true};
        extent2d        extent {};
        SDL_GLContext   sdl_gl_context {};
        chorume::camera camera {};
        float           gravity {0.0f};
        // o runtime nao se importa e nem calcula delta time,
        // pre-supondo que isso ta rodando sempre a 60fps
        float           dt {0.016f};
    } application;

    struct log {
    protected:
        std::ostringstream buffer {};
    public:    
        explicit log() {
            this->buffer << "[CHORUME] ";
        }
    
        ~log() {
            this->buffer << '\n';
            std::cout << this->buffer.str();
        }
    
        template<typename t>
        log &operator<<(const t &value) {
            this->buffer << value;
            return *this;
        }
    };
}

#endif