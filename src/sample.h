#pragma once
#include <queue>

class Stub;

template <class T>
class Sample {
private:
    static Sample*    m_sample;
    static size_t     m_max_size;

    std::deque<Stub*> m_queue;
    T                 m_hook;

    Sample() {}
    ~Sample() {}
    Sample(const Sample&);
    Sample& operator=(const Sample&);

public:
    static Sample* getInstance() {
	if (!m_sample)
	    m_sample = new Sample();
	return m_sample;
    }

    static void destroy() {
	delete m_sample;
	m_sample = nullptr;
    }

    bool   empty()    const {return m_queue.empty();}
    size_t size()     const {return m_queue.size();}
    size_t max_size() const {return m_max_size;}
    void   clear()          {       m_queue.clear();}

    Sample* push(Stub* stub) {
	if (m_queue.end() != find(m_queue.begin(), m_queue.end(), stub))
	    return this;		// already
	while (m_max_size <= size())
	    m_hook(pop());
	m_queue.push_back(stub);
	return this;
    }

    Stub* pop() {
	if (empty())
	    return nullptr;
	Stub* s = m_queue.front();
	m_queue.pop_front();
	return s;
    }
};
