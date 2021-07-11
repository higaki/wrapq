#pragma once

#include "stub.h"

struct overflow_hook {
    void operator()(Stub* s){
	std::cout << "flush stub(" << *s << ")" << std::endl;
    }
};
