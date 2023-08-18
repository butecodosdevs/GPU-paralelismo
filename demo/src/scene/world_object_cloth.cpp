#include "world_object_cloth.hpp"
#include "platform/platform.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "platform/platform.hpp"

void chorume::world_object_cloth::update_constraint() {
    glm::vec3 delta {};
    float delta_length {};
    float delta_diff {};

    for (chorume::world_object_cloth::constraint &constraint : this->loaded_constraint_list) {
        chorume::world_object_cloth::point &point_a {this->loaded_point_list.at(constraint.point[0])};
        chorume::world_object_cloth::point &point_b {this->loaded_point_list.at(constraint.point[1])};

        delta = point_b.position - point_a.position;
        delta_length = glm::length(delta);
        delta_diff = (delta_length - constraint.rest_length) / delta_length;

        if (!point_a.is_fixed) {
            point_a.position += delta * 0.5f * delta_diff;
        }

        if (point_b.is_fixed) {
            point_b.position -= delta * 0.5f * delta_diff;
        }
    }
}

void chorume::world_object_cloth::update_gravity() {
    for (chorume::world_object_cloth::point &point : this->loaded_point_list) {
        if (point.is_fixed) {
            continue;
        }

        point.position.y -= chorume::application.gravity * chorume::application.dt * chorume::application.dt;
    }
}

void chorume::world_object_cloth::update_verlet_integration() {
    glm::vec3 next_pos {};
    for (uint64_t it {}; it < this->loaded_point_list.size(); it++) {
        chorume::world_object_cloth::point &point {this->loaded_point_list.at(it)};

        next_pos = point.position + (point.position - point.old_position);
        point.old_position = point.position;
        point.position = next_pos;

        this->geometry_resource_list.at(point.rendering_index + 0) = point.position.x;
        this->geometry_resource_list.at(point.rendering_index + 1) = point.position.y;
        this->geometry_resource_list.at(point.rendering_index + 2) = point.position.z;
    }
}

void chorume::world_object_cloth::create() {
    if (this->list_buffer) {
        return;
    }

    glm::vec3 point_position {};
    chorume::world_object_cloth::constraint constraint {};
    bool should_be_a_fixed_point {};

    for (int32_t x {}; x < this->plane.x - 1; x++) {
        for (int32_t z {}; z < this->plane.z - 1; z++) {
            should_be_a_fixed_point = (x == 0 || z == 0);

            point_position = {
                static_cast<float>(x) / static_cast<float>(this->plane.x),
                0.0f,
                static_cast<float>(z) / static_cast<float>(this->plane.z)
            };

            constraint.rest_length = 1.0f;
            constraint.point[0] = this->loaded_point_list.size();            

            this->loaded_point_list.emplace_back() = {
                .position = point_position,
                .old_position = point_position,
                .is_fixed = should_be_a_fixed_point,
                .rendering_index = this->geometry_resource_list.size()
            };

            constraint.point[1] = this->loaded_point_list.size();
            this->loaded_constraint_list.push_back(constraint);

            this->geometry_resource_list.emplace_back() = point_position.x;
            this->geometry_resource_list.emplace_back() = point_position.y;
            this->geometry_resource_list.emplace_back() = point_position.z;

            point_position = {
                static_cast<float>(x) / static_cast<float>(this->plane.x),
                0.0f,
                static_cast<float>(z + 1) / static_cast<float>(this->plane.z)
            };

            constraint.rest_length = 1.0f;
            constraint.point[0] = this->loaded_point_list.size();            

            this->loaded_point_list.emplace_back() = {
                .position = point_position,
                .old_position = point_position,
                .is_fixed = should_be_a_fixed_point,
                .rendering_index = this->geometry_resource_list.size()
            };

            constraint.point[1] = this->loaded_point_list.size();
            this->loaded_constraint_list.push_back(constraint);

            this->geometry_resource_list.emplace_back() = point_position.x;
            this->geometry_resource_list.emplace_back() = point_position.y;
            this->geometry_resource_list.emplace_back() = point_position.z;

            point_position = {
                static_cast<float>(x + 1) / static_cast<float>(this->plane.x),
                0.0f,
                static_cast<float>(z) / static_cast<float>(this->plane.z)
            };

            constraint.rest_length = 1.0f;
            constraint.point[0] = this->loaded_point_list.size();            

            this->loaded_point_list.emplace_back() = {
                .position = point_position,
                .old_position = point_position,
                .is_fixed = should_be_a_fixed_point,
                .rendering_index = this->geometry_resource_list.size()
            };

            constraint.point[1] = this->loaded_point_list.size();
            this->loaded_constraint_list.push_back(constraint);

            this->geometry_resource_list.emplace_back() = point_position.x;
            this->geometry_resource_list.emplace_back() = point_position.y;
            this->geometry_resource_list.emplace_back() = point_position.z;

            point_position = {
                static_cast<float>(x + 1) / static_cast<float>(this->plane.x),
                0.0f,
                static_cast<float>(z + 1) / static_cast<float>(this->plane.z)
            };

            constraint.rest_length = 1.0f;
            constraint.point[0] = this->loaded_point_list.size();            

            this->loaded_point_list.emplace_back() = {
                .position = point_position,
                .old_position = point_position,
                .is_fixed = should_be_a_fixed_point,
                .rendering_index = this->geometry_resource_list.size()
            };

            this->geometry_resource_list.emplace_back() = point_position.x;
            this->geometry_resource_list.emplace_back() = point_position.y;
            this->geometry_resource_list.emplace_back() = point_position.z;
        }
    }

    chorume::log() << this->geometry_resource_list.size();

    glGenVertexArrays(1, &this->list_buffer);
    glGenBuffers(1, &this->buffer_resources);

    glBindVertexArray(this->list_buffer);

    glBindBuffer(GL_ARRAY_BUFFER, this->buffer_resources);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->geometry_resource_list.size(), nullptr, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

    glBindVertexArray(0);
}

void chorume::world_object_cloth::destroy() {   
}

void chorume::world_object_cloth::update() {
    this->update_gravity();
    this->update_constraint();
    this->update_verlet_integration();
}

void chorume::world_object_cloth::revoke() {
}

void chorume::world_object_cloth::invoke() {
    this->mat_model_trs = glm::mat4(1.0f);
    this->mat_model_trs = glm::translate(this->mat_model_trs, this->position);
    this->mat_model_trs = glm::scale(this->mat_model_trs, this->scale);
}

void chorume::world_object_cloth::draw() {
    glBindBuffer(GL_ARRAY_BUFFER, this->buffer_resources);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * this->geometry_resource_list.size(), this->geometry_resource_list.data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(this->list_buffer);
    glDrawArrays(GL_POINTS, 0, this->geometry_resource_list.size()/3);
    glBindVertexArray(0);
}