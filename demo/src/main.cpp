#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

struct extent2d {
public:
    int32_t w {};
    int32_t h {};
};

struct platform {
public:
    const char   *p_application_name {};
    SDL_Window   *p_sdl_window {};
    bool          running {true};
    extent2d      extent {};
    SDL_GLContext sdl_gl_context {};
} application;

int32_t main(int32_t, char**) {
    std::cout << "Preparando o contexto do OpenGL." << std::endl;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    application.extent = {1280, 720};
    application.p_application_name = "Pompom do Chorume";
    application.p_sdl_window = SDL_CreateWindow(application.p_application_name,
                                                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                                application.extent.w, application.extent.h,
                                                SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

    std::cout << "Janela criada." << std::endl;

    glewExperimental = GL_TRUE;
    glewInit();

    application.sdl_gl_context = SDL_GL_CreateContext(application.p_sdl_window);
    std::cout << "Contexto acelerado por GPU com a API OpenGL criada!" << std::endl;

    SDL_Event sdl_event {};
    while (application.running) {
        while (SDL_PollEvent(&sdl_event)) {
            if (sdl_event.type == SDL_QUIT) {
                application.running = false;
            }
        }

        // Render pass de renderização.
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        SDL_GL_SwapWindow(application.p_sdl_window);
        SDL_Delay(16);
    }

    return 0;
}