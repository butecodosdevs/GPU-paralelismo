#include "graphics/graphics_pipeline_program.hpp"

int32_t main(int32_t, char**) {
    std::cout << "Preparando o contexto do OpenGL." << std::endl;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    chorume::application.extent = {1280, 720};
    chorume::application.p_application_name = "Pompom do Chorume";
    chorume::application.p_sdl_window = SDL_CreateWindow(chorume::application.p_application_name,
                                                         SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                                         chorume::application.extent.w, chorume::application.extent.h,
                                                         SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

    std::cout << "Janela criada." << std::endl;

    glewExperimental = GL_TRUE;
    glewInit();

    chorume::application.sdl_gl_context = SDL_GL_CreateContext(chorume::application.p_sdl_window);
    std::cout << "Contexto acelerado por GPU com a API OpenGL criada!" << std::endl;

    chorume::graphics_pipeline_program *p_overlay_program = new chorume::graphics_pipeline_program();
    chorume::create_graphics_pipeline_program(p_overlay_program, {
        {"./data/overlay.glsl.vert", GL_VERTEX_SHADER},
        {"./data/overlay.glsl.frag", GL_FRAGMENT_SHADER}
    });

    SDL_Event sdl_event {};
    while (chorume::application.running) {
        while (SDL_PollEvent(&sdl_event)) {
            if (sdl_event.type == SDL_QUIT) {
                chorume::application.running = false;
            }
        }

        // Definimos o viewport do render passa para renderizar.
        glViewport(0, 0, chorume::application.extent.w, chorume::application.extent.h);

        // Render pass de renderização.
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        SDL_GL_SwapWindow(chorume::application.p_sdl_window);
        SDL_Delay(16);
    }

    return 0;
}