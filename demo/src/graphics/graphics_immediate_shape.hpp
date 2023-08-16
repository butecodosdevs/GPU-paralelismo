#ifndef GRAPHICS_IMMEDIATE_SHAPE_H
#define GRAPHICS_IMMEDIATE_SHAPE_H

namespace chorume {
    struct immediate_shape {
    protected:
        uint32_t uniform_location_rect_id {};
        uint32_t uniform_location_color_id {};
        uint32_t buffer_resources_id {};
        uint32_t list_buffer_id {};
    public:
        uint32_t material {};
    public:
        void set_material(uint32_t material);
    };
};

#endif