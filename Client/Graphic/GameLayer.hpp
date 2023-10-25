#pragma once

#include <DawnStar/DawnStar.hpp>
#include <DawnStar/Debug/RenderStatPanel.hpp>

class GameLayer : public DawnStar::Layer
{
public:
	GameLayer();
	virtual ~GameLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(DawnStar::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(DawnStar::Event& e) override;

private:
	DawnStar::RenderStatPanel m_StatPanel;

	DawnStar::Ref<DawnStar::Scene> m_MainScene;
};