#include <DawnStar/dspch.hpp>
#include "GameLayer.hpp"
#include "Scene/GameScene.hpp"
#include "Scene/RobbyScene.hpp"
#include "Network/NetworkManager.hpp"

GameLayer::GameLayer()
{
}
void GameLayer::OnAttach()
{

	// Setting scenes
	_scenes.insert({"Game", CreateRef<GameScene>(this)});
	_scenes.insert({"Robby", CreateRef<RobbyScene>(this)});

	ChangeScene("Robby");

    for(const auto& item : _scenes)
	{
		item.second->OnAttach();
	}

	// Network initialization
	NetworkManager::Instance().Init();
}

void GameLayer::OnDetach()
{
    for(const auto& item : _scenes)
	{
		item.second->OnDetach();
	}
}

void GameLayer::OnUpdate(Timestep ts)
{
	Renderer2D::ResetStats();
	RenderCommand::SetClearColor({0.4f, 0.4f, 0.4f, 1.0f});
	RenderCommand::Clear();

	_currentScene->OnUpdate(ts);
}

void GameLayer::OnImGuiRender()
{

	
#if DS_DEBUG
	_statPanel.OnImGuiRender();
	_objListPanel.OnImGuiRender();
#endif

	_currentScene->OnImGuiRender();
}

void GameLayer::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowResizeEvent>(DS_BIND_EVENT_FN(GameLayer::OnWindowResize));
	dispatcher.Dispatch<MouseMovedEvent>(DS_BIND_EVENT_FN(GameLayer::OnMouseMoved));
}

void GameLayer::ChangeScene(std::string name)
{
	_currentScene = GetSceneByName(name);
	
#if DS_DEBUG
	_objListPanel.SetContext(_currentScene->GetScene());
#endif
}

bool GameLayer::OnWindowResize(WindowResizeEvent &e)
{

	_currentScene->GetScene()->OnViewportResize(e.GetWidth(), e.GetHeight());
    return false;
}

bool GameLayer::OnMouseMoved(MouseMovedEvent &e)
{
	
	// auto pos = Input::GetMousePosition();
	// DS_APP_INFO("From event: ({0}, {1}), From system?: ({2}, {3}) {4}", 
	// 			e.GetX(), e.GetY(), pos.x, pos.y, (e.GetX() == pos.x && e.GetY() == pos.y));
    return false;
}

Ref<SceneWrapper> GameLayer::GetSceneByName(std::string name)
{
	auto iter = _scenes.find(name);
	if(iter == _scenes.end())
	{
		DS_ASSERT("{0} is not an existing scene", name)
		return nullptr;
	}
    return iter->second;
}
