#include "world_object.hpp"

uint64_t chorume::world_object_token_id {};

void chorume::world_object::auto_registry() {
    if (this->id == 0) {
        this->id = ++chorume::world_object_token_id;
    } 
}

void chorume::world_object::create() {

}

void chorume::world_object::destroy() {

}

void chorume::world_object::update() {

}

void chorume::world_object::invoke() {

}

void chorume::world_object::revoke() {

}

void chorume::world_object::draw() {

}