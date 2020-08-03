#include "opfor.hpp"

#include "systems/CameraMovementSystem.hpp"

#include "components/PlayerCameraComponent.hpp"
#include "components/TransformComponent.hpp"
#include "components/SkyboxComponent.hpp"

class Sandbox : public opfor::Application
{
private:
	opfor::UniquePtr<ImGuiLayer> _ImGui;

public:
	Sandbox() : opfor::Application()
	{
		CreateComponentSystem<CameraMovementSystem>();

		auto player = CreateEntity<PlayerCameraComponent, TransformComponent>();

		PlayerCameraComponent p;
			p.projection = glm::perspective(glm::radians(90.0f), 16.0f / 9.0f, 0.1f, 10000.0f);
			p.model = glm::mat4(1.0f);
			p.view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
			p.viewProjection = p.projection * p.view;
			p.exposure = 2.0f;
		player->Set(p);
		player->SetName("Player");

		TransformComponent t;
			t.direction = glm::vec3(0.0f, 0.0f, 1.0f);
			t.position = glm::vec3(0.0f, 18.0f, -0.5f);
		player->Set(t);

		auto __attribute__((unused)) skybox = CreateEntity<SkyboxComponent>();

		opfor::Application::Get().LoadLevel("levels/pbr.level");
	}
};

opfor::UniquePtr<opfor::Application> opfor::CreateApplication()
{
	return MakeUnique<Sandbox>();
}