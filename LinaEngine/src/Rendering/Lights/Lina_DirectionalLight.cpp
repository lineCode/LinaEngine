#include "pch.h"
#include "Rendering/Lights/Lina_DirectionalLight.hpp"
#include "Game/Lina_Actor.hpp"

void Lina_DirectionalLight::AttachToActor(Lina_Actor& act)
{
	Lina_ActorComponent::AttachToActor(act);

	m_Actor->Lina->RenderingEngine()->AddDirectionalLight(this);

}
