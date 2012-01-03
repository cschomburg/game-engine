#ifndef COMPONENT_H
#define COMPONENT_H

#include <memory>
#include <string>

class Component {
public:
	typedef std::shared_ptr<Component> Ptr;

	Component(const std::string &type, const std::string &objectID);
	virtual ~Component();

	std::string type() const;
	std::string objectID() const;

private:
	std::string m_type;
	std::string m_objectID;
};

#endif /* end of include guard: COMPONENT_H */
