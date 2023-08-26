#ifndef GRAPHICS_COMPUTE_SHADER_H
#define GRAPHICS_COMPUTE_SHADER_H

#include <iostream>
#include <map>
#include <vector>
#include "platform/platform.hpp"

namespace chorume {
    struct sampler {
    public:
        uint32_t id {};
        uint32_t primitive {};
        uint32_t w {};
        uint32_t h {};
        uint32_t format {};
        uint32_t channel {};
        void *p_data {};
    };

    struct graphics_compute_shader {
    public:
        std::map<uint32_t, chorume::sampler> sampler_map {};
        uint32_t *p_compute_graphics_program {nullptr};
        uint32_t sampler_bound {};
        uint32_t worker_groups[3] {1, 1, 1};
        uint32_t memory_barrier { GL_ALL_BARRIER_BITS};
    public:
        void bind_sampler(uint32_t sampler_slot) {
            chorume::sampler &sampler {this->sampler_map[sampler_slot]};
            if (sampler.id == 0) {
                glGenTextures(1, &sampler.id);
            }

            this->sampler_bound = sampler_slot;
            glBindTexture(GL_TEXTURE_2D, sampler.id);
        }

        void unbind_sampler(uint32_t sampler_slot) {
            glBindTexture(GL_TEXTURE_2D, 0);
            this->sampler_bound = 0;
        }

        template<typename t>
        void set_sampler_propierties(const chorume::sampler &sampler_properties) {
            chorume::sampler &sampler {this->sampler_map[this->sampler_bound]};
            bool resize_sampler {};

            if (sampler_properties.w != 0 && sampler.w != sampler_properties.w) {
                sampler.w = sampler_properties.w;
                resize_sampler = true;
            }

            if (sampler_properties.h != 0 && sampler.h != sampler_properties.h) {
                sampler.h = sampler_properties.h;
                resize_sampler = true;
            }

            if (sampler_properties.channel != 0 && sampler.channel != sampler_properties.channel) {
                sampler.channel = sampler_properties.channel;
                resize_sampler = true;
            }

            if (sampler_properties.p_data != nullptr && sampler.p_data != sampler_properties.p_data) {
                sampler.p_data = sampler_properties.p_data;
                resize_sampler = true;
            }

            if (resize_sampler) {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

                glTexImage2D(GL_TEXTURE_2D,
                             0,
                             sampler.format, 
                             sampler.w, 
                             sampler.h,
                             0, 
                             sampler.channel, 
                             sampler.primitive, 
                             sampler.p_data);
            }
        }

        template<typename t>
        void write_back(uint32_t sampler_slot, std::vector<t> &data, uint32_t vec_count) {
            chorume::sampler &sampler {this->sampler_map[sampler_slot]};
            data.resize(sampler.w * sampler.h * vec_count);

            glBindTexture(GL_TEXTURE_2D, sampler.id);
            glGetTexImage(GL_TEXTURE_2D, 0, sampler.channel, sampler.primitive, data.data());
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        void attach(uint32_t sampler_slot, uint32_t shader_slot, uint32_t mode) {
            chorume::sampler &sampler {this->sampler_map[sampler_slot]};
            glBindImageTexture(shader_slot, sampler.id, 0, GL_FALSE, 0, mode, sampler.format);
        }

        void invoke() {
            glUseProgram(*this->p_compute_graphics_program);
        }

        void dispatch() {
            glDispatchCompute(this->worker_groups[0], this->worker_groups[1], this->worker_groups[2]);
            glMemoryBarrier(this->memory_barrier);
        }

        void revoke() {
            glUseProgram(0);
        }
    };
};

#endif