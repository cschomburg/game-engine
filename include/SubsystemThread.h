#ifndef SUBSYSTEMTHREAD_H
#define SUBSYSTEMTHREAD_H

#include <thread>
#include <vector>

#if !defined(_GLIBCXX_HAS_GTHREADS) && defined(__GNUG__)

#include <boost/thread.hpp>

namespace std {
  using boost::thread;
  
  using boost::mutex;
  using boost::timed_mutex;
  using boost::recursive_mutex;
  using boost::recursive_timed_mutex;
  
  using boost::lock_guard;
  using boost::unique_lock;
  
  using boost::condition_variable;
  using boost::condition_variable_any;
}

#endif /* Crippled GCC */

class Subsystem;

class SubsystemThread {
public:
	SubsystemThread();
	virtual ~SubsystemThread();

	void addSubsystem(Subsystem *subsystem);
	void start();
	bool isRunning() const;
	void stop();

	int fps() const;

private:
	bool m_running;
	std::vector<Subsystem *> m_subsystems;
	std::thread *m_thread;

	int m_lastSecond;
	int m_frameCount;
	int m_fps;
};

#endif /* end of include guard: SUBSYSTEMTHREAD_H */
