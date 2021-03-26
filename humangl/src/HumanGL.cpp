#include <opfor.hpp>

#include <components/ModelComponent.hpp>
#include <components/TransformComponent.hpp>
#include <components/PointLightComponent.hpp>
#include <components/SkyboxComponent.hpp>
#include <opfor/renderer/Model.hpp>
#include <opfor/renderer/ShaderManager.hpp>

#include <opfor/editor/EditorInspector.hpp>
#include <opfor/editor/EditorLog.hpp>
#include <opfor/editor/EditorMenuBar.hpp>
#include <opfor/editor/EditorSceneHierarchy.hpp>
#include <opfor/editor/EditorViewport.hpp>

#include <opfor/layers/ImGuiLayer.hpp>

#include <utility>

using namespace opfor;

class HumanGL : public Application
{
  private:

    unsigned int _shaderId;

    static std::vector<unsigned> LoadModel(std::string const &filename)
    {
        Model model{};
        model.LoadFromGLTF(filename);
        return model.GetMeshes();
    }

    static void InsertMeshes(std::vector<unsigned> &meshContainer, std::vector<unsigned> const &meshes)
    {
        if (!meshes.empty())
        {
            meshContainer.reserve(meshes.size());
            meshContainer.insert(meshContainer.end(), meshes.begin(), meshes.end());
        }
    }

    std::pair<ecs::IEntity<TransformComponent> *, ecs::IEntity<TransformComponent, ModelComponent> *> CreateMember(std::string const &name, glm::vec3 position, glm::vec3 scale, std::vector<unsigned> const &meshes)
    {
        auto *member = CreateEntity<TransformComponent>();
        member->SetName(name);
        member->Get<TransformComponent>().position = position;

        auto *memberModelComponent = CreateEntity<TransformComponent, ModelComponent>();
        memberModelComponent->SetName("Head Model");
        memberModelComponent->Get<TransformComponent>().parent = member->Get<TransformComponent>();
        memberModelComponent->Get<TransformComponent>().scale = scale;

        auto &memberModel = memberModelComponent->Get<ModelComponent>();
        InsertMeshes(memberModel.meshes, meshes);
        memberModel.shader = _shaderId;

        return {member, memberModelComponent};
    }

  public:
    HumanGL() : Application()
    {
        ImGuiLayer::Get().OpenWindow<EditorViewport>();
        ImGuiLayer::Get().OpenWindow<EditorMenuBar>();
        ImGuiLayer::Get().OpenWindow<EditorLog>();
        ImGuiLayer::Get().OpenWindow<EditorSceneHierarchy>();
        ImGuiLayer::Get().OpenWindow<EditorInspector>();

        auto *skyBox = CreateEntity<SkyboxComponent>();
        skyBox->SetName("SkyBox");

        auto [modelShaderId, modelShader] = ShaderManager::Get().Create("shaders/basic.glsl");

        _shaderId = modelShaderId;

        auto model = LoadModel("./assets/cube/cube.gltf");

 
        auto [head, headModel] =
            CreateMember("Head", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(100.0f, 100.0f, 100.0f), model);

        auto [torso, torsoModel] =
            CreateMember("Torso", glm::vec3(0.0f, -150.0f, 0.0f), glm::vec3(80.0f, 200.0f, 100.0f), model);
        torso->Get<TransformComponent>().parent = head->Get<TransformComponent>();

        auto [leftArm, leftArmModel] =
            CreateMember("Left Arm", glm::vec3(0.0f, 50.0f, 75.0f), glm::vec3(50.0f, 100.f, 50.0f), model);
        leftArm->Get<TransformComponent>().parent = torso->Get<TransformComponent>();
        leftArm->Get<TransformComponent>().rotation *= glm::quat(glm::vec3(0.0f, 0.0f, -45.0f));

        auto [leftForearm, leftForearmModel] =
            CreateMember("Left Forearm", glm::vec3(0.0f, -100.0f, 0.0f), glm::vec3(50.0f, 100.0f, 50.0f), model);
        leftForearm->Get<TransformComponent>().parent = leftArm->Get<TransformComponent>();
        leftForearm->Get<TransformComponent>().rotation *= glm::quat(glm::vec3(0.0f, 0.0f, -45.0f));

        auto [rightArm, rightArmModel] = CreateMember("Right Arm",
            glm::vec3(0.0f, 50.0f, -75.0f),
            glm::vec3(50.0f, 100.0f, 50.0f), model);
        rightArm->Get<TransformComponent>().parent = torso->Get<TransformComponent>();

        auto [rightForearm, righForearmModel] = CreateMember("Left Forearm",
            glm::vec3(0.0f, -100.0f, 0.0f),
            glm::vec3(50.0f, 100.0f, 50.0f), model);
        rightForearm->Get<TransformComponent>().parent = rightArm->Get<TransformComponent>();

        auto [leftThigh, leftThighModel] = CreateMember("Left Thigh",
            glm::vec3(0.0f, -150.0f, 25.0f),
            glm::vec3(50.0f, 100.0f, 50.0f), model);
        leftThigh->Get<TransformComponent>().parent = torso->Get<TransformComponent>();

        auto [leftShin, leftShinModel] = CreateMember("Left Shin",
            glm::vec3(0.0f, -100.0f, 0.0f),
            glm::vec3(50.0f, 100.0f, 50.0f), model);
        leftShin->Get<TransformComponent>().parent = leftThigh->Get<TransformComponent>();

        auto [rightThigh, rightThighModel] = CreateMember("Right Thigh",
            glm::vec3(0.0f, -150.0f, -25.0f),
            glm::vec3(50.0f, 100.0f, 50.0f), model);
        rightThigh->Get<TransformComponent>().parent = torso->Get<TransformComponent>();

        auto [rightShin, rightShinModel] = CreateMember("Right Shin",
            glm::vec3(0.0f, -100.0f, 0.0f),
            glm::vec3(50.0f, 100.0f, 50.0f), model);
        rightShin->Get<TransformComponent>().parent = rightThigh->Get<TransformComponent>();

        auto *light = CreateEntity<PointLightComponent, TransformComponent>();
        light->Get<TransformComponent>().position = glm::vec3(0.0f, -1000.0f, 100.0f);
        light->Get<PointLightComponent>().Intensity = 10000.f;
        light->SetName("Light");
    }
};

namespace opfor
{

UniquePtr<Application> CreateApplication()
{
    return MakeUnique<HumanGL>();
}

} // namespace opfor
