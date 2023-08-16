#include "graphics_pipeline_program.hpp"
#include <fstream>

chorume::result chorume::read_file_as_string(std::string_view path, std::string &file_content_as_string) {
    std::ifstream ifs(path.data());
    if (ifs.is_open()) {
        std::string line {};
        while (std::getline(ifs, line)) {
            file_content_as_string += line;
            file_content_as_string += '\n';
        }

        ifs.close();
        return chorume::result::ok;
    }

    return chorume::result::failed;
}

chorume::result chorume::create_graphics_pipeline_program(chorume::graphics_pipeline_program *p_pipeline_program,
                                                          const std::vector<chorume::graphics_shading_source> &shaders) {
    p_pipeline_program->program = glCreateProgram(); // Cria um programa.

    chorume::result issue {chorume::result::ok};
    std::vector<uint32_t> jit_compiled_shader_list {};
    std::string shader_source {};

    for (const chorume::graphics_shading_source &shading_source : shaders) {
        shader_source.clear();
        if (chorume::read_file_as_string(shading_source.p_file_path, shader_source) == chorume::result::failed) {
            chorume::log() << "Failed to read '" << shading_source.p_file_path << "' shader!";
            issue = chorume::result::failed;
            break;
        }

        uint32_t shader {glCreateShader(shading_source.shader_stage)};
        const char *p_src {shader_source.c_str()};

        glShaderSource(shader, 1, &p_src, nullptr);
        glCompileShader(shader);

        int32_t out {};
        glGetShaderiv(shader, GL_COMPILE_STATUS, &out);

        if (out == GL_FALSE) {
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &out);
            std::string info_log {};
            info_log.resize(out);
            glGetShaderInfoLog(shader, out, nullptr, info_log.data());

            chorume::log() << "Failed to compile shader '" << shading_source.p_file_path << "`!" << '\n' << info_log;
            issue = chorume::result::failed;

            break;
        }

        jit_compiled_shader_list.emplace_back() = shader;
        glAttachShader(p_pipeline_program->program, shader);
    }

    if (jit_compiled_shader_list.size() == shaders.size()) {
        glLinkProgram(p_pipeline_program->program);

        int32_t out {};
        glGetProgramiv(p_pipeline_program->program, GL_LINK_STATUS, &out);

        if (out == GL_FALSE) {
            glGetProgramiv(p_pipeline_program->program, GL_INFO_LOG_LENGTH, &out);
            std::string info_log {};

            info_log.resize(out);
            glGetProgramInfoLog(p_pipeline_program->program, out, nullptr, info_log.data());

            chorume::log() << "Failed to link program " << '\n' << info_log;
            issue = chorume::result::failed;
        }
    }

    for (uint32_t &shaders : jit_compiled_shader_list) {
        glDeleteShader(shaders);
    }

    return issue;
}