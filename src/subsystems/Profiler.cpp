#include <algorithm>
#include <iomanip>
#include <cfloat>

#include "subsystems/Profiler.h"

namespace bpt = boost::posix_time;

Profiler::Profiler(GameEngine *engine)
	: Subsystem(engine) {}

Profiler::~Profiler() {}

void Profiler::start(const std::string &name) {
	auto it = m_profiles.find(name);
	if (it != m_profiles.end()) {
		it->second.start = bpt::ptime(bpt::microsec_clock::local_time());
		return;
	}

	Profile profile{0, FLT_MAX, 0, 0, 0,
		bpt::ptime(bpt::microsec_clock::local_time())};
	m_profiles.insert(std::make_pair(name, profile));
}

void Profiler::stop(const std::string &name) {
	bpt::ptime end(bpt::microsec_clock::local_time());
	auto it = m_profiles.find(name);
	if (it == m_profiles.end()) {
		return;
	}

	Profile &profile = it->second;
	float diff = static_cast<float>(bpt::time_period(profile.start, end).length().total_microseconds()) / 1000.0f;
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
	ostream << std::setw(14) << "" << "\t\tmin [ms]\tavg [ms]\tmax [ms]\tlast [ms]" << std::endl;
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
