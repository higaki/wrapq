#pragma once
#include <iostream>

class Stub {
private:
    int m_id;
public:
    Stub(int id): m_id(id) {}
    void print(std::ostream& out) const {
	out << m_id;
    }
};

std::ostream& operator<<(std::ostream& out, const Stub& s);
