#pragma once

#include "../ecs/component.hpp"

#include <glm/glm.hpp> 

namespace our {
class Box_collider : public Component {
    public:
    glm::vec3 center;
    float length, width, height;
    int action;

    static std::string getID() { return "Collider"; }

    void deserialize(const nlohmann::json& data) override;
};
}