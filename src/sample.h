#pragma once
#include <queue>

class Stub;

class Sample {
private:
    static Sample*    m_sample;
    static size_t     m_max_size;
    std::deque<Stub*> m_queue;

    Sample();
    ~Sample();
    Sample(const Sample&);
    Sample& operator=(const Sample&);

public:
    static Sample* getInstance();
    static void    destroy();

    bool   empty()    const {return m_queue.empty();}
    size_t size()     const {return m_queue.size();}
    size_t max_size() const {return m_max_size;}
    void   clear()          {       m_queue.clear();}

    Sample* push(Stub* stub);
    Stub*   pop();
};
