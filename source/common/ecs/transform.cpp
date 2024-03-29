#include "entity.hpp"
#include "../deserialize-utils.hpp"

#include <glm/gtx/euler_angles.hpp>

namespace our {

    // This function computes and returns a matrix that represents this transform
    // Remember that the order of transformations is: Scaling, Rotation then Translation
    // HINT: to convert euler angles to a rotation matrix, you can use glm::yawPitchRoll
    glm::mat4 Transform::toMat4() const {
        //TODO: Write this function
        // modeling transformation


        // suffers from gamble lock
        glm::mat4 rot = glm::yawPitchRoll(rotation.y,rotation.x,rotation.z); // set the rotation
        glm::mat4 trs = glm::translate(glm::mat4(1.0f), position); // tranlsates identity to posiotion
        glm::mat4 scl = glm::scale(glm::mat4(1.0f), scale); // transforms the idenetint into scale
        return trs * rot * scl;
    }

     // Deserializes the entity data and components from a json object
    void Transform::deserialize(const nlohmann::json& data){
        position = data.value("position", position);
        rotation = glm::radians(data.value("rotation", glm::degrees(rotation)));
        scale    = data.value("scale", scale);
    }

}