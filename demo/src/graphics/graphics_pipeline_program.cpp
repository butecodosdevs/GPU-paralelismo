#include "graphics_pipeline_program.hpp"
#include <fstream>

chorume::graphics_pipeline_program::graphics_pipeline_program() {
    this->program = glCreateProgram();
}

chorume::graphics_pipeline_program::~graphics_pipeline_program() {
    glDeleteProgram(this->program);
}

void chorume::graphics_pipeline_program::set_uniform_mat4(std::string_view uniform_name, const float *p_value) {
    glUniformMatrix4fv(glGetUniformLocation(this->program, uniform_name.data()), 1, GL_FALSE, p_value);
}

void chorume::graphics_pipeline_program::set_uniform_vec3(std::string_view uniform_name, const float *p_value) {
    glUniform3f(glGetUniformLocation(this->program, uniform_name.data()), p_value[0], p_value[1], p_value[2]);
}

chorume::result set_pipeline_program_uniform_mat4(chorume::graphics_pipeline_program *p_pipeline_program, const float *p_value);

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

            chorume::log() << "Shader '" << shading_source.p_file_path << "' não conseguiu ser compilada 😿!" << '\n' << info_log;
            issue = chorume::result::failed;

            break;
        }

        jit_compiled_shader_list.emplace_back() = shader;
        glAttachShader(p_pipeline_program->program, shader);

        chorume::log() << "Shader '" << shading_source.p_file_path << "' compilada 😸!";
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

            chorume::log() << "Programa não conseguiu linkar as shaders ao programa 😿! " << '\n' << info_log;
            issue = chorume::result::failed;
        }

        chorume::log() << "Programa ligado na GPU 😸!";
    }

    for (uint32_t &shaders : jit_compiled_shader_list) {
        glDeleteShader(shaders);
    }

    return issue;
}