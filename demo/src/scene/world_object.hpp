#ifndef CHORUME_SCENE_WORLD_OBJECT_H
#define CHORUME_SCENE_WORLD_OBJECT_H

#include <iostream>
#include <glm/glm.hpp>

namespace chorume {
    class world_object {
    public:
        uint64_t id {};
        glm::mat4 mat_model_trs {};
        glm::vec3 position {};
        glm::vec3 scale {1.0f, 1.0f, 1.0f};
    public:
        void auto_registry();

        virtual void create();
        virtual void destroy();
        virtual void update();
        virtual void invoke();
        virtual void revoke(); 
        virtual void draw();
    };

    extern uint64_t world_object_token_id;
};

#endif