#include "Application.h"
#include "Input.h"
#include "AudioPlayer.h"
#include "States/SplashMenu.h"
#include "TimerModule.h"

Application* Application::s_Instance = nullptr;
SDL_Event Application::Event;
bool Application::m_Running;

Application* Application::Instance() {

	if (s_Instance == nullptr) {
		s_Instance = new Application();
	}
	
	return s_Instance;
}

Application::Application() {
	m_Running = true;

	m_Graphics = Graphics::Instance();
	if (!m_Graphics->Initialized()) {
		m_Running = false;
	}

	AudioPlayer::SetVolume(1, 0);

	TimerModule::UpdateDelta();

	StateMachine::addState(SplashMenu::GetInstance()); //Inserts menu; This state will appear first
}

Application::~Application() {

	m_Graphics->DestroyInstance();
	m_Graphics = nullptr;
	
	_StateMachine.KillAllStates();
}

void Application::DestroyInstance() {
	delete s_Instance;
	s_Instance = nullptr;
}

void Application::MainLoop() {
	while (m_Running)
	{

		TimerModule::UpdateDelta();

		while (SDL_PollEvent(&Event) != 0) {

			if (Event.type == SDL_QUIT) {
				m_Running = false;
			}
			
			switch (Event.window.event)
			{
			case SDL_WINDOWEVENT_MINIMIZED:
				while (SDL_WaitEvent(&Event))
				{
					if (Event.window.event == SDL_WINDOWEVENT_RESTORED)
					{
						break;
					}
				}
				break;
			}
			break;
		}

		Input::InputUpdate();
		Input::MouseUpdate(Event);

		m_Graphics->Update();
		_StateMachine.Update();

		///////////////////Everything to render goes in between here/////////////////////////

		_StateMachine.Render();

		////////////////////////////////////////////////////////////////////////////////////

		m_Graphics->Render();

		SDL_Delay(10); //reduces CPU usage
	}
}

void Application::ShutDown() {
	m_Running = false;
}

SDL_Event Application::GetEvent() {
	return Event;
}