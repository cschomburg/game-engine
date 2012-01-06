#include <algorithm>
#include <iomanip>
#include <cfloat>

#include "subsystems/Profiler.h"

Profiler::Profiler(GameEngine *engine)
	: Subsystem(engine) {}

Profiler::~Profiler() {}

void Profiler::start(const std::string &name) {
	auto it = m_profiles.find(name);
	if (it != m_profiles.end()) {
		it->second.start = engine()->time();
		return;
	}

	Profile profile{0, FLT_MAX, 0, 0, 0, 0};
	profile.start = engine()->time();
	m_profiles.insert(std::make_pair(name, profile));
}

void Profiler::stop(const std::string &name) {
	float end = engine()->time();
	auto it = m_profiles.find(name);
	if (it == m_profiles.end()) {
		return;
	}

	Profile &profile = it->second;
	float diff = end - profile.start;
	profile.n++;
	float n = profile.n;
	profile.min = std::min(profile.min, diff);
	profile.max = std::max(profile.max, diff);
	profile.last = diff;
	profile.avg = (n-1)/n*profile.avg + 1.0f/n*diff;
}

Profile Profiler::profile(const std::string &name) const {
	auto it = m_profiles.find(name);
	if (it == m_profiles.end()) {
		return Profile();
	}
	return it->second;
}

const ProfileMap &Profiler::profiles() const {
	return m_profiles;
}

void Profiler::report(std::ostream &ostream) {
	ostream << std::fixed << std::setprecision(3);
	ostream << std::setw(14) << "" << "\t\tmin\t\tavg\t\tmax\t\tlast" << std::endl;
	for (auto pair : m_profiles) {
		const Profile &p = pair.second;
		ostream << std::setw(14) << pair.first
		        << "\t\t" << p.min
				<< "\t\t" << p.avg
				<< "\t\t" << p.max
				<< "\t\t" << p.last
				<< std::endl;
	}
}
