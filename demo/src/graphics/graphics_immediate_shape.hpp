#ifndef GRAPHICS_IMMEDIATE_SHAPE_H
#define GRAPHICS_IMMEDIATE_SHAPE_H

#include "platform/platform.hpp"

namespace chorume {
    struct graphics_immediate_shape {
    protected:
        int32_t uniform_location_rect_id {};
        int32_t uniform_location_color_id {};
        int32_t uniform_location_is_texture_active_id {};
        int32_t uniform_location_matrix_projection_id {};
        uint32_t buffer_resources_id {};
        uint32_t buffer_indices_id {};
        uint32_t list_buffer_id {};
        uint32_t current_texture_bound {};
        uint32_t pipeline_program {};
        float delta {};
    public:
        void set_pipeline_program(uint32_t _pipeline_program);
        void invoke();
        void draw(const glm::vec4 &rect, const glm::vec4 &color, uint32_t texture = 0);
        void revoke();
    };
};

#endif