//
// Created by Aaron on 2019/7/10.
//

#include "common.h"

#include <stdio.h>

using namespace std;

struct Context
{
    int count;
    int64_t bytes;
    SessionMessage  session;
    Buffer output;

    Context(): count(0), bytes(0)
    {
        session.number = 0;
        session.length = 0;
    }
};
