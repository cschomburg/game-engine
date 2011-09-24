#ifndef SUBSYSTEMTHREAD_H
#define SUBSYSTEMTHREAD_H

#include <thread>
#include <vector>

class Subsystem;

class SubsystemThread {
public:
	SubsystemThread();
	virtual ~SubsystemThread();

	void addSubsystem(Subsystem *subsystem);
	void start();
	bool isRunning() const;
	void stop();

private:
	bool m_running;
	std::vector<Subsystem *> m_subsystems;
	std::thread *m_thread;
};

#endif /* end of include guard: SUBSYSTEMTHREAD_H */
