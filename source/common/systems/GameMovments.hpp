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
        glm::vec3 initialPos;
        bool set;
        bool reset;
        bool first;
        int pinnescount;

    public:
        void enter(Application *app)
        {
            reset = false;
            this->app = app;
            to_right = true;
            to_forward = false;
            set = false;
            first = true;
            pinnescount = 0;
        }

        CameraComponent *camera = nullptr;
        GameMovments *controller = nullptr;
        int planeScaleX = 0;

        void update(World *world, float deltaTime)
        {
            for (auto entity : world->getEntities())
            {
                //camera = entity->getComponent<CameraComponent>();
                controller = entity->getComponent<GameMovments>();
                if (controller)
                    break;
            }

             std::cout<<std::endl<<controller->downPinnes<<std::endl;

            if(controller->tries == 2)
            {
                if(controller->downPinnes == pinnescount)
                {
                    std::cout<<std::endl<<"I am here \n";
                    app->changeState("winnerWin");
                }
                else
                    app->changeState("loserWin");

            }

            for (auto entity : world->getEntities())
            {

                if(first && entity->name == "pin")
                    pinnescount++;

                // std::cout << std::endl
                //           << "Name: " << entity->name << std::endl;
                if (entity->name == "plane")
                {
                    planeScaleX = entity->localTransform.scale.x - 1;
                }
            }

            first = false;

            // If there is no entity with both a CameraComponent and a FreeCameraControllerComponent, we can do nothing so we return
            if (!(controller))
                return;
            // Get the entity that we found via getOwner of camera (we could use controller->getOwner())
            //std::cout<<"I am here \n";

            Entity *entity = controller->getOwner();

            if(entity->getComponent<GameMovments>()->reset == 1)
            {
                entity->getComponent<GameMovments>()->reset = 0;
                this->resetAll();
            }

            glm::vec3 &position = entity->localTransform.position;

            if(reset)
            {
                reset = false;
                position = initialPos;
                to_right = true;
                to_forward = false;
            }

            if(!set)
            {
                set = true;
                initialPos = position; 
            }

            glm::mat4 matrix = entity->localTransform.toMat4();

            glm::vec3 front = glm::vec3(matrix * glm::vec4(0, 0, -1, 0)),
                      up = glm::vec3(matrix * glm::vec4(0, 1, 0, 0)),
                      right = glm::vec3(matrix * glm::vec4(1, 0, 0, 0));

            glm::vec3 current_sensitivity = controller->positionSensitivity;

            //std::cout<<position.x<<" "<<position.y<<" "<<position.z<<std::endl;

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
                    if (position.x >= planeScaleX)
                    {
                        to_right = false;
                    }
                }
                else
                {
                    position -= right * (deltaTime * current_sensitivity.x);
                    if (position.x <= -planeScaleX)
                    {
                        to_right = true;
                    }
                }
            }
            //std::cout<<entity->name<<"\n";
        }

        void resetAll()
        {
            reset = true;
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