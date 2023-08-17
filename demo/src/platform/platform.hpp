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
        glm::mat4 mat_projection_perspective {};
        glm::mat4 mat_projection_overlay {};
        glm::vec3 position {};
    };

    extern struct platform {
    public:
        const char     *p_application_name {};
        SDL_Window     *p_sdl_window {};
        bool            running {true};
        extent2d        extent {};
        SDL_GLContext   sdl_gl_context {};
        chorume::camera camera {};
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