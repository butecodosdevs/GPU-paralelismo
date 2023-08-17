#include "graphics/graphics_pipeline_program.hpp"
#include "graphics/graphics_immediate_shape.hpp"
#include "math/linear_algebra.hpp"

int32_t main(int32_t, char**) {
    chorume::log() << "Preparando o contexto do OpenGL.";

    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);

    chorume::application.extent = {1280, 720};
    chorume::application.p_application_name = "Pompom do Chorume";
    chorume::application.p_sdl_window = SDL_CreateWindow(chorume::application.p_application_name,
                                                         SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                                         800, 600,
                                                         SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

    chorume::log() << "Janela criada.";

    chorume::application.sdl_gl_context = SDL_GL_CreateContext(chorume::application.p_sdl_window);
    chorume::log() << "Contexto acelerado por GPU com a API OpenGL criada!";

    glewExperimental = GL_TRUE;
    glewInit();

    // Liga o v-sync porque não precisa usar 100% da GPU.
    SDL_GL_SetSwapInterval(1);
    SDL_SetWindowSize(chorume::application.p_sdl_window, chorume::application.extent.w, chorume::application.extent.h);

    chorume::graphics_pipeline_program *p_overlay_program = new chorume::graphics_pipeline_program();
    chorume::create_graphics_pipeline_program(p_overlay_program, {
        {"./data/overlay.glsl.vert", GL_VERTEX_SHADER},
        {"./data/overlay.glsl.frag", GL_FRAGMENT_SHADER}
    });

    chorume::graphics_immediate_shape immediate_shape {};
    immediate_shape.set_pipeline_program(p_overlay_program->program);

    float lerp {};

    SDL_Event sdl_event {};
    while (chorume::application.running) {
        while (SDL_PollEvent(&sdl_event)) {
            if (sdl_event.type == SDL_QUIT) {
                chorume::application.running = false;
            }

            if (sdl_event.type == SDL_WINDOWEVENT && sdl_event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                chorume::application.extent.w = sdl_event.window.data1;
                chorume::application.extent.h = sdl_event.window.data2;

                chorume::application.camera.mat_projection_overlay = {
                    chorume::linear_algebra_calculate_orthographic_matrix(0.0f, static_cast<float>(sdl_event.window.data1), static_cast<float>(sdl_event.window.data2), 0.0f)
                };

                chorume::log() << "Janela redimensionada " << sdl_event.window.data1 << 'x' << sdl_event.window.data2;
            }
        }

        // Definimos o viewport do render passa para renderizar.
        glViewport(0, 0, chorume::application.extent.w, chorume::application.extent.h);

        // Render pass de renderização.
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        lerp += 0.03f;

        immediate_shape.invoke();
        immediate_shape.draw({20.0f, 20.0f, 900.0f, 900.0f}, {0.0f, sin(lerp), 0.9894543f, 1.0f});
        immediate_shape.revoke();

        SDL_GL_SwapWindow(chorume::application.p_sdl_window);
        SDL_Delay(16);
    }

    return 0;
}