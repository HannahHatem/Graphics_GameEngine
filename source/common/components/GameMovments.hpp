#pragma once

#include "../ecs/component.hpp"

#include <glm/glm.hpp> 

namespace our{
    class GameMovments : public Component{
        public:
        glm::vec3 positionSensitivity = {3.0f, 3.0f, 3.0f}; // The unity per second of camera movement if WASD is pressed
        int reset = 0; 
        static std::string getID() { return "Game Movment"; }
        void deserialize(const nlohmann::json& data) override;
    };
}