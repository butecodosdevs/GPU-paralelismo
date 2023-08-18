#include "graphics/graphics_pipeline_program.hpp"
#include "graphics/graphics_immediate_shape.hpp"
#include "math/linear_algebra.hpp"
#include "scene/world_object_cloth.hpp"
#include <glm/gtc/matrix_transform.hpp>

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

    chorume::graphics_pipeline_program *p_world_object_program = new chorume::graphics_pipeline_program();
    chorume::create_graphics_pipeline_program(p_world_object_program, {
        {"./data/world.object.glsl.vert", GL_VERTEX_SHADER},
        {"./data/world.object.glsl.frag", GL_FRAGMENT_SHADER}
    });

    chorume::graphics_immediate_shape immediate_shape {};
    immediate_shape.set_pipeline_program(p_overlay_program->program);

    chorume::world_object_cloth *p_world_obj_coth = new chorume::world_object_cloth();
    p_world_obj_coth->create();
    p_world_obj_coth->position.y -= 3.0f;
    p_world_obj_coth->scale = glm::vec3(4.0f, 1.0f, 4.0f);

    chorume::camera &camera {chorume::application.camera};
    SDL_Event sdl_event {};

    glDisable(GL_CULL_FACE);

    while (chorume::application.running) {
        while (SDL_PollEvent(&sdl_event)) {
            if (sdl_event.type == SDL_QUIT) {
                chorume::application.running = false;
            }

            if (sdl_event.type == SDL_MOUSEMOTION) {
                chorume::linear_algebra_calculate_camera_look(sdl_event.motion.x, sdl_event.motion.y, sdl_event.motion.xrel, sdl_event.motion.yrel);
            }

            if (sdl_event.type == SDL_WINDOWEVENT && sdl_event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                chorume::application.extent.w = sdl_event.window.data1;
                chorume::application.extent.h = sdl_event.window.data2;

                float viewport_extent[2] {
                    static_cast<float>(sdl_event.window.data1),
                    static_cast<float>(sdl_event.window.data2)
                };

                float aspect {viewport_extent[0] / viewport_extent[1]};
                float far {1000.0f};

                camera.mat_perspective = glm::perspective(glm::radians(camera.fov), aspect, 0.03f, far);
                camera.mat_ortho_view = {
                    chorume::linear_algebra_calculate_orthographic_matrix(0.0f, viewport_extent[0], viewport_extent[0], 0.0f)
                };

                chorume::log() << "Janela redimensionada " << sdl_event.window.data1 << 'x' << sdl_event.window.data2;
            }
        }

        // É legal sempre atualizar antes do segmento de renderização.
        p_world_obj_coth->update();

        // Multiplicamos as duas matrizes: Perspectiva (definições do olho da camera e distância dos objetos) e camera view (posição, direção dela etc).
        camera.mat_projection = camera.mat_perspective *
                                camera.mat_look_at_view;
 
        // Definimos o viewport do render passa para renderizar.
        glViewport(0, 0, chorume::application.extent.w, chorume::application.extent.h);

        // Render pass de renderização.
        glClearColor(0.213423894f, 0.235423894f, 0.234243894f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //immediate_shape.invoke();
        //immediate_shape.draw({20.0f, 20.0f, 20.0f, 20.0f}, {0.0f, 0.034234324f, 0.9894543f, 1.0f});
        //immediate_shape.revoke();

        glUseProgram(p_world_object_program->program);

        p_world_obj_coth->invoke();
        glm::mat4 mat_modelview_perspective {camera.mat_projection * p_world_obj_coth->mat_model_trs};

        p_world_object_program->set_uniform_mat4("uMatrixProjection", &mat_modelview_perspective[0][0]);
        p_world_object_program->set_uniform_mat4("uMatrixModel", &p_world_obj_coth->mat_model_trs[0][0]);
        p_world_object_program->set_uniform_vec3("uLightPos", &glm::vec3(20.0f, 5.0f, 0.0f)[0]);
        p_world_object_program->set_uniform_vec3("uMaterialColor", &glm::vec3(1.0f, 1.0f, 1.0f)[0]);
        p_world_obj_coth->draw();

        SDL_GL_SwapWindow(chorume::application.p_sdl_window);
        SDL_Delay(16);
    }

    return 0;
}