#ifndef CHORUME_GRAPHICS_PIPELINE_PROGRAM_H
#define CHORUME_GRAPHICS_PIPELINE_PROGRAM_H

#include "platform/platform.hpp"
#include <vector>

namespace chorume {
    struct graphics_pipeline_program {
    public:
        uint32_t program {};
    public:
        void invoke();
        void revoke();
    };

    struct graphics_shading_source {
    public:
        const char *p_file_path {};
        uint32_t shader_stage {};
    };

    chorume::result read_file_as_string(std::string_view path, std::string &file_content_as_string);
    chorume::result create_graphics_pipeline_program(chorume::graphics_pipeline_program *p_pipeline_program,
                                                     const std::vector<chorume::graphics_shading_source> &shaders);
}

#endif