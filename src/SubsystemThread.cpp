#include "Application.h"
#include "Subsystem.h"
#include "SubsystemThread.h"

namespace boost {
	void tss_cleanup_implemented() { }
}

SubsystemThread::SubsystemThread() {
	m_thread = 0;
	m_running = false;
}

SubsystemThread::~SubsystemThread() {
	if (m_running)
		stop();
}

void SubsystemThread::addSubsystem(Subsystem *subsystem) {
	m_subsystems.push_back(subsystem);
}

void SubsystemThread::start() {
	if (m_running)
		return;

	m_lastSecond = Application::instance()->time();
	m_frameCount = 0;
	m_fps = 0;

	m_running = true;
	m_thread = new std::thread([this, &m_running, &m_subsystems]() {
		while(m_running) {
			int time = Application::instance()->time();
			if (time >= m_lastSecond+1000) {
				m_lastSecond = time;
				m_fps = m_frameCount;
				m_frameCount = 0;
			}

			for (Subsystem *subsystem : m_subsystems) {
				subsystem->update();
			}
		}
	});
}

bool SubsystemThread::isRunning() const {
	return m_running;
}

void SubsystemThread::stop() {
	if (!m_running)
		return;

	m_running = false;
	m_thread->join();
	delete m_thread;
	m_thread = 0;
	m_fps = 0;
}

int SubsystemThread::fps() const {
	return m_fps;
}
