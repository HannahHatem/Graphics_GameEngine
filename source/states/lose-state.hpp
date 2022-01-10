#pragma once

#include <application.hpp>

#include <ecs/world.hpp>
#include <systems/forward-renderer.hpp>
#include <systems/free-camera-controller.hpp>
#include <systems/movement.hpp>
#include <systems/GameMovments.hpp>
#include <asset-loader.hpp>
#include <iostream>

#define ICON_FA_AMP_GUITAR "\xef\xa2\xa1"

class LoseState : public our::State
{
    void onImmediateGui() override
    {
        ImGuiStyle &style = ImGui::GetStyle();
        style.FramePadding = ImVec2(15, 12);
        style.ItemSpacing = ImVec2(10, 50);
        style.Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
        auto windowSize = getApp()->getFrameBufferSize();
        ImGui::SetNextWindowSize(ImVec2(windowSize.x, windowSize.y));
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::Begin("Bowling Game", NULL, ImGuiWindowFlags_NoCollapse);

        if (ImGui::BeginTabBar("Welcome !"))
        {
            if (ImGui::BeginTabItem("LOSER"))
            {
                if (ImGui::Button(" return", ImVec2(200, 100)))
                {
                    getApp()->changeState("main");
                }
                ImGui::EndTabItem();
            }
        }

        ImGui::EndTabBar();
        ImGui::End();
    }
};