#pragma once

#include "../ecs/world.hpp"
#include "../components/camera.hpp"
#include "../components/Box_collider.hpp"
#include "../components/mesh-renderer.hpp"
#include "../components/GameMovments.hpp"
#include "GameMovments.hpp"
#include "../application.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include <vector>
#include <iostream>

namespace our
{
    class collider
    {
    public:
        Application *app;          // The application in which the state runs
        bool mouse_locked = false; // Is the mouse locked

        void enter(Application *app)
        {
            this->app = app;
        }

        void update(World *world, float deltaTime)
        {
            //std::cout<<"\nI am here"<<std::endl;
            std::vector<Box_collider *> colliders;
            //std::list<Box_collider*> colliders;
            //std::cout<<"\nI am here"<<std::endl;
            for (auto entity : world->getEntities())
            {
                Box_collider *check = entity->getComponent<Box_collider>();
                if (check)
                {
                    colliders.push_back(check);
                }
            }
            //std::cout<<"\nI am here"<<std::endl;

            /*for(auto iter : colliders)
            {

            }*/

            for (int i = 0; i < colliders.size(); i++)
            {
                Box_collider *first = colliders[i];
                for (int j = 0; j < colliders.size(); j++)
                {
                    if (j == i)
                        continue;
                    Box_collider *second = colliders[j];
                    float disz, disy, disx;
                    disy = first->getOwner()->localTransform.position.y - second->getOwner()->localTransform.position.y;
                    disx = first->getOwner()->localTransform.position.x - second->getOwner()->localTransform.position.x;
                    disz = first->getOwner()->localTransform.position.z - second->getOwner()->localTransform.position.z;

                    if (disx < 0)
                        disx = disx * -1;
                    if (disy < 0)
                        disy = disy * -1;
                    if (disz < 0)
                        disz = disz * -1;

                    if (disy <= (first->length + second->length) && disx <= (first->width + second->width) && disz <= (first->height + second->height))
                    {
                        std::cout << "collision detected " << first->action << std::endl;

                        if (second->getOwner()->name == "pin" && first->getOwner()->name == "ball")
                        {
                            first->getOwner()->getComponent<GameMovments>()->downPinnes++;
                        }

                        if (first->getOwner()->name == "ball" && second->getOwner()->name == "bound")
                        {
                            first->getOwner()->getComponent<GameMovments>()->reset = 1;
                            first->getOwner()->getComponent<GameMovments>()->tries++;
                        }
                        if (first->action == 1)
                        {
                            std::cout << first->getOwner()->name << std::endl;
                            //first->getOwner()->deleteComponent<Box_collider>();
                            //first->getOwner()->deleteComponent<MeshRendererComponent>();
                            world->markForRemoval(first->getOwner());
                            //world->deleteMarkedEntities();
                            //first->getOwner()->ignore = true;
                        }
                        if (second->action == 1)
                        {
                            //colliders.remove(second);
                            std::cout << second->getOwner()->name << std::endl;
                            //second->getOwner()->deleteComponent<Box_collider>();
                            //second->getOwner()->deleteComponent<MeshRendererComponent>();
                            //delete second->getOwner();
                            //world->markForRemoval(second->getOwner());
                            //world->deleteMarkedEntities();
                        }
                    }
                }
            }
        }
    };
}