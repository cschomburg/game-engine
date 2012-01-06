#ifndef PROFILER_H
#define PROFILER_H

#include <map>
#include <string>
#include <iostream>

#include "GameEngine.h"
#include "Subsystem.h"

struct Profile {
	int n;
	float min;
	float max;
	float last;
	float avg;
	float start;
};

typedef std::map<std::string, Profile> ProfileMap;

class Profiler : public Subsystem {
public:
	Profiler(GameEngine *engine);
	virtual ~Profiler();

	void start(const std::string &name);
	void stop(const std::string &name);

	Profile profile(const std::string &name) const;
	const ProfileMap &profiles() const;

	void report(std::ostream &ostream);

private:
	ProfileMap m_profiles;
};

#endif /* end of include guard: PROFILER_H */
