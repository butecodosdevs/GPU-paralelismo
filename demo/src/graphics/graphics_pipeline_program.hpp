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
        const char *p_source_location {};
        uint32_t shader_stage {};
    };

    chorume::result create_graphics_pipeline_program(chorume::graphics_pipeline_program *p_pipeline_program,
                                                     const std::vector<chorume::graphics_shading_source> &shaders);
}

#endif