#pragma once

#include <glad/gl.h>
#include <glm/vec4.hpp>
#include <json/json.hpp>

namespace our {
    // There are some options in the render pipeline that we cannot control via shaders
    // such as blending, depth testing and so on
    // Since each material could require different options (e.g. transparent materials usually use blending),
    // we will encapsulate all these options into a single structure that will also be responsible for configuring OpenGL's pipeline
    struct PipelineState {
        // This set of pipeline options specifies whether face culling will be used or not and how it will be configured
        struct {
            bool enabled = false;
            GLenum culledFace = GL_BACK;
            GLenum frontFace = GL_CCW;
        } faceCulling;

        // This set of pipeline options specifies whether depth testing will be used or not and how it will be configured
        struct {
            bool enabled = false;
            GLenum function = GL_LEQUAL;
        } depthTesting;

        // This set of pipeline options specifies whether blending will be used or not and how it will be configured
        struct {
            bool enabled = false;
            GLenum equation = GL_FUNC_ADD;
            GLenum sourceFactor = GL_SRC_ALPHA;
            GLenum destinationFactor = GL_ONE_MINUS_SRC_ALPHA;
            glm::vec4 constantColor = {0, 0, 0, 0};
        } blending;

        // These options specify the color and depth mask which can be used to
        // prevent the rendering/clearing from modifying certain channels of certain targets in the framebuffer
        glm::bvec4 colorMask = {true, true, true, true}; // To know how to use it, check glColorMask
        bool depthMask = true; // To know how to use it, check glDepthMask


        // This function should set the OpenGL options to the values specified by this structure
        // For example, if faceCulling.enabled is true, you should call glEnable(GL_CULL_FACE), otherwise, you should call glDisable(GL_CULL_FACE)
        void setup() const {
            //TODO: Write this function

            // optimizing performance by not rendering unneeded faces
            if(!faceCulling.enabled) 
            {
                glDisable(GL_CULL_FACE);//if faceculling flag is not enabled, disable it
            }
            else
            {
                glEnable(GL_CULL_FACE);  //enable face culling 
                glCullFace(faceCulling.culledFace); //set the cull direction to the direction recieved from jsonc, file CW or CCW  
                glFrontFace(faceCulling.frontFace); //set the cull face to the face recieved from jsonc file, front or back
            }
           
            // decides what to draw over what
            if(!depthTesting.enabled)
            {
                glDisable(GL_DEPTH_TEST);//if depth testing flag is not enabled, disable it
            }
            else
            {
                glEnable(GL_DEPTH_TEST);   //enable depth testing
                glDepthFunc(depthTesting.function); //set the depth testing function with the function recieved from jsonc  
            }

            // optimizes the colors of the destination in case of transparency
            if(!blending.enabled) 
            {
                glDisable(GL_BLEND); //if blending flag is not enabled, disable it
            }
            else
            {
                glEnable(GL_BLEND); //enable blending
                glBlendEquation(blending.equation);    //set blending equation with eq recieved from jsonc
                glBlendFunc(blending.sourceFactor,blending.destinationFactor); //set blending function with func recieved from jsonc
                glBlendColor(blending.constantColor.r,blending.constantColor.g,blending.constantColor.b,blending.constantColor.a); //set color with color recieved from jsonc
            }

            //same with color mask and depth mask
            //set them with values recieved from Jsonc
            
            // enables any color of the pixel to change according to the drawing operation
            glColorMask(colorMask.r,colorMask.g,colorMask.b,colorMask.a);
            
            // eneables overwritting z-buffer
            glDepthMask(depthMask);

        }

        // Given a json object, this function deserializes a PipelineState structure
        void deserialize(const nlohmann::json& data);
    };

}