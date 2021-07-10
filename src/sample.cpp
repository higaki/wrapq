#include "sample.h"

using namespace std;

class Stub;

Sample* Sample::m_sample   = nullptr;
size_t  Sample::m_max_size = 3;

Sample::Sample() {
}

Sample::~Sample() {
}

Sample* Sample::getInstance() {
    if (!m_sample)
	m_sample = new Sample();
    return m_sample;
}

void Sample::destroy() {
    delete m_sample;
    m_sample = nullptr;
}

Sample* Sample::push(Stub* stub) {
    if (m_queue.end() != find(m_queue.begin(), m_queue.end(), stub))
	return this;		// already
    while (m_max_size <= size())
	m_queue.pop_front();
    m_queue.push_back(stub);
    return this;
}

Stub* Sample::pop() {
    if (empty())
	return nullptr;
    Stub* s = m_queue.front();
    m_queue.pop_front();
    return s;
}
