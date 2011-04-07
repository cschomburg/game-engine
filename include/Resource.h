#ifndef RESOURCE_H
#define RESOURCE_H

class Resource {
public:
	Resource();
	virtual ~Resource();

	void init();
	void free();

protected:
	virtual void load();
	virtual void destroy();

private:
	int m_numUsed;
};

#endif /* end of include guard: RESOURCE_H */
