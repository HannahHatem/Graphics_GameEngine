#pragma once

#include "../ecs/world.hpp"
#include "../components/camera.hpp"
#include "../components/GameMovments.hpp"

#include "../application.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include <iostream>

namespace our
{
    class BowlingMovment
    {
        Application *app;          // The application in which the state runs
        bool mouse_locked = false; // Is the mouse locked
        bool to_right;
        bool to_forward;

    public:
        void enter(Application *app)
        {
            this->app = app;
            to_right = true;
            to_forward = false;
        }

        CameraComponent *camera = nullptr;
        GameMovments *controller = nullptr;

        void update(World *world, float deltaTime)
        {

            for (auto entity : world->getEntities())
            {
                camera = entity->getComponent<CameraComponent>();
                controller = entity->getComponent<GameMovments>();
                if (camera && controller)
                    break;
            }
            // If there is no entity with both a CameraComponent and a FreeCameraControllerComponent, we can do nothing so we return
            if (!(camera && controller))
                return;
            // Get the entity that we found via getOwner of camera (we could use controller->getOwner())
            Entity *entity = camera->getOwner();

            glm::vec3 &position = entity->localTransform.position;

            glm::mat4 matrix = entity->localTransform.toMat4();

            glm::vec3 front = glm::vec3(matrix * glm::vec4(0, 0, -1, 0)),
                      up = glm::vec3(matrix * glm::vec4(0, 1, 0, 0)),
                      right = glm::vec3(matrix * glm::vec4(1, 0, 0, 0));

            glm::vec3 current_sensitivity = controller->positionSensitivity;

            if(app->getKeyboard().isPressed(GLFW_KEY_SPACE))
            {
                to_forward = true;
            }

            if (to_forward)
            {
                position += front * (deltaTime * current_sensitivity.x * 7);
            }
            else
            {
                if (to_right)
                {
                    position += right * (deltaTime * current_sensitivity.x);
                    if (position.x >= 6)
                    {
                        to_right = false;
                    }
                }
                else
                {
                    position -= right * (deltaTime * current_sensitivity.x);
                    if (position.x <= -6)
                    {
                        to_right = true;
                    }
                }
            }
        }

        void exit()
        {
            if (mouse_locked)
            {
                mouse_locked = false;
                app->getMouse().unlockMouse(app->getWindow());
            }
        }
    };
}