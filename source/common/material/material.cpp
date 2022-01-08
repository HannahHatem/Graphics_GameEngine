#include "material.hpp"

#include "../asset-loader.hpp"
#include "deserialize-utils.hpp"

namespace our
{

    // This function should setup the pipeline state and set the shader to be used
    void Material::setup() const
    {
        // TODO: Write this function
        pipelineState.setup(); // setup our object pipeline
        shader->use();         // use the shader
    }

    // This function read the material data from a json object
    void Material::deserialize(const nlohmann::json &data)
    {
        if (!data.is_object())
            return;

        if (data.contains("pipelineState"))
        {
            pipelineState.deserialize(data["pipelineState"]);
        }
        shader = AssetLoader<ShaderProgram>::get(data["shader"].get<std::string>());
        transparent = data.value("transparent", false);
    }

    // This function should call the setup of its parent and
    // set the "tint" uniform to the value in the member variable tint
    void TintedMaterial::setup() const
    {
        // TODO: Write this function
        Material::setup();
        shader->set("tint", tint);
    }

    // This function read the material data from a json object
    void TintedMaterial::deserialize(const nlohmann::json &data)
    {
        Material::deserialize(data);
        if (!data.is_object())
            return;
        tint = data.value("tint", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    }

    // This function should call the setup of its parent and
    // set the "alphaThreshold" uniform to the value in the member variable alphaThreshold
    // Then it should bind the texture and sampler to a texture unit and send the unit number to the uniform variable "tex"
    void TexturedMaterial::setup() const
    {
        // TODO: Write this function
        TintedMaterial::setup();
        shader->set("alphaThreshold", alphaThreshold);

        // Select active texture unit
        glActiveTexture(GL_TEXTURE0);
        // bind el texture to the active texture unit
        texture->bind();
        // Bind sampler to active texture unit
        sampler->bind(0);

        // Send the unit number to the shader
        shader->set("tex", 0);
    }

    // This function read the material data from a json object
    void TexturedMaterial::deserialize(const nlohmann::json &data)
    {
        TintedMaterial::deserialize(data);
        if (!data.is_object())
            return;
        alphaThreshold = data.value("alphaThreshold", 0.0f);
        texture = AssetLoader<Texture2D>::get(data.value("texture", ""));
        sampler = AssetLoader<Sampler>::get(data.value("sampler", ""));
    }

    // Implement the setup function for the lit material
    void LitMaterial::setup() const
    {
        TexturedMaterial::setup();

        if(emission != nullptr)
        {
            // Select active texture unit
            glActiveTexture(GL_TEXTURE1);
            // bind el texture to the active texture unit
            emission->bind();
            // Bind sampler to active texture unit
            sampler->bind(1);
            shader->set("material.emission", 1);
        }

        if (roughness != nullptr)
        {
            // Select active texture unit
            glActiveTexture(GL_TEXTURE2);
            // bind el texture to the active texture unit
            roughness->bind();
            // Bind sampler to active texture unit
            sampler->bind(2);
            shader->set("material.roughness", 2);
        }

        if (albedo != nullptr)
        {
            // Select active texture unit
            glActiveTexture(GL_TEXTURE3);
            // bind el texture to the active texture unit
            albedo->bind();
            // Bind sampler to active texture unit
            sampler->bind(3);
            shader->set("material.albedo", 3);
        }

        if(specular != nullptr){
            // Select active texture unit
            glActiveTexture(GL_TEXTURE4);
            // bind el texture to the active texture unit
            specular->bind();
            // Bind sampler to active texture unit
            sampler->bind(4);
            shader->set("material.specular", 4);
        }

        if(ao != nullptr)
        {
            // Select active texture unit
            glActiveTexture(GL_TEXTURE5);
            // bind el texture to the active texture unit
            ao->bind();
            // Bind sampler to active texture unit
            sampler->bind(5);
            shader->set("material.ambient_occlusion", 5);
        }

    }

    // implement deserialize for LintMaterial class
    void LitMaterial::deserialize(const nlohmann::json &data)
    {
        TexturedMaterial::deserialize(data);
        if (!data.is_object())
            return;
        albedo = AssetLoader<Texture2D>::get(data.value("albedo", ""));
        specular = AssetLoader<Texture2D>::get(data.value("specular", ""));
        roughness = AssetLoader<Texture2D>::get(data.value("roughness", ""));
        emission = AssetLoader<Texture2D>::get(data.value("emission", ""));
        ao = AssetLoader<Texture2D>::get(data.value("ao", ""));
        printf("sucessfully loaded lit material\n");
    }
}