#include <DawnStar/dspch.hpp>
#include "ObjectListPanel.hpp"

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <imgui/misc/cpp/imgui_stdlib.h>

#include <cstring>

namespace DawnStar
{

	ObjectListPanel::ObjectListPanel()
	{
		m_Context = {};
	}

	void ObjectListPanel::OnImGuiRender()
	{

		// Show Object List

		
		ImGui::Begin("Entity hierachy");
		if(m_Context)
		{
			m_Context->m_Registry.each([&](auto entityID)
				{
					Entity entity{ entityID , m_Context.get() };
					DrawEntityNode(entity);
				});
		}
		ImGui::End();
		

		ImGui::Begin("Properties");
		if (m_SelectionEntity)
		{
			DrawComponents(m_SelectionEntity);
		}
		ImGui::End();
	}

	void ObjectListPanel::SetContext(Ref<Scene> &context)
	{
		m_Context = context;
	}

	void ObjectListPanel::DrawEntityNode(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().Tag;
		
		ImGuiTreeNodeFlags flags = ((m_SelectionEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, "%s", tag.c_str());
		if (ImGui::IsItemClicked())
		{
			m_SelectionEntity = entity;
		}

		if (opened)
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
			bool opened = ImGui::TreeNodeEx((void*)9817239, flags, "%s", tag.c_str());
			if (opened)
				ImGui::TreePop();
			ImGui::TreePop();
		}
	}

	template<typename T, typename UIFunction>
	static void DrawComponent(const std::string& name, Entity entity, UIFunction uiFunction)
	{
		const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
		if (entity.HasComponent<T>())
		{
			auto& component = entity.GetComponent<T>();
			ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImGui::Separator();
			bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, "%s", name.c_str());
			ImGui::PopStyleVar();

			ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);
			if (ImGui::Button("+", ImVec2{ lineHeight, lineHeight }))
			{
				ImGui::OpenPopup("ComponentSettings");
			}

			bool removeComponent = false;
			if (ImGui::BeginPopup("ComponentSettings"))
			{
				if (ImGui::MenuItem("Remove component"))
					removeComponent = true;

				ImGui::EndPopup();
			}

			if (open)
			{
				uiFunction(component);
				ImGui::TreePop();
			}

			if (removeComponent)
				entity.RemoveComponent<T>();
		}
	}

	void ObjectListPanel::DrawComponents(Entity entity)
	{
		if (entity.HasComponent<TagComponent>())
		{
			auto& tag = entity.GetComponent<TagComponent>().Tag;

			// char buffer[256];
			// memset(buffer, 0, sizeof(buffer));
			// strncpy_s(buffer, sizeof(buffer), tag.c_str(), sizeof(buffer));
			// if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
			// {
			// 	tag = std::string(buffer);
			// }
		}

		ImGui::SameLine();

		DrawComponent<TransformComponent>("Transform", entity, [](auto& component)
		{
			DawnStar::ImGuiUI::DrawVec3Control("Translation", component.Translation);
			glm::vec3 rotation = glm::degrees(component.Rotation);
			DawnStar::ImGuiUI::DrawVec3Control("Rotation", rotation);
			component.Rotation = glm::radians(rotation);
			DawnStar::ImGuiUI::DrawVec3Control("Scale", component.Scale, 1.0f);
		});

	}
}