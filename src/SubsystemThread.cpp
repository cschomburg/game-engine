#include "Subsystem.h"
#include "SubsystemThread.h"

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

	m_running = true;
	m_thread = new std::thread([&m_running, &m_subsystems]() {
		while(m_running) {
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
}
