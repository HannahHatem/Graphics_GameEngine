#include "Box_collider.hpp"
#include "../ecs/entity.hpp"
#include "../deserialize-utils.hpp"

namespace our {
    // Reads sensitivities & speedupFactor from the given json object
    void Box_collider::deserialize(const nlohmann::json& data){
        if(!data.is_object()) return;
        length = data.value("length",length);
        width = data.value("width",width);
        height = data.value("height",height);
        action = data.value("action",action);
        
    }
}