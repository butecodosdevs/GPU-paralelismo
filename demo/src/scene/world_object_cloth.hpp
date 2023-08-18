#ifndef WORLD_OBJECT_CLOTH_H
#define WORLD_OBJECT_CLOTH_H

#include "world_object.hpp"
#include <vector>

namespace chorume {
    class world_object_cloth : public chorume::world_object {
    protected:
        struct point {
        public:
            glm::vec3 position {};
            glm::vec3 old_position {};
            bool is_fixed {};
            uint64_t rendering_index {};
        };
    protected:
        struct constraint {
        public:
            uint64_t point[2] {};
            float rest_length {};
        };
    protected:
        void update_gravity();
        void update_verlet_integration();
        void update_constraint();
    protected:
        std::vector<chorume::world_object_cloth::point> loaded_point_list {};
        std::vector<chorume::world_object_cloth::constraint> loaded_constraint_list {};
        std::vector<float> geometry_resource_list {};
        uint32_t buffer_resources {};
        uint32_t list_buffer {};
    public:
        glm::ivec3 plane {20, 1, 20};
    public:
        void create() override;
        void destroy() override;
        void update() override;
        void invoke() override;
        void revoke() override;
        void draw() override;
    };
}

#endif