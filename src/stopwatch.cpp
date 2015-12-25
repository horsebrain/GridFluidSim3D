/*
Copyright (c) 2015 Ryan L. Guy

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgement in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/
#include "stopwatch.h"

StopWatch::StopWatch()
{
}

void StopWatch::start() {
    
    #ifdef __linux__ 
        struct timeval tp;
        gettimeofday(&tp, NULL);
        _tbegin = (double)(tp.tv_sec * 1000 + tp.tv_usec / 1000);
    #elif _WIN32
        _tbegin = (float)GetTickCount() / 1000.0;
    #else
    #endif
    
    _isStarted = true;
}


void StopWatch::stop() {
    if (!_isStarted) {
        return;
    }

    #ifdef __linux__ 
        struct timeval tp;
        gettimeofday(&tp, NULL);
        _tend = (double)(tp.tv_sec * 1000 + tp.tv_usec / 1000);
    #elif _WIN32
        _tend = (float)GetTickCount() / 1000.0;
    #else
    #endif
    
    double time = _tend - _tbegin;
    _timeRunning += time;
}

void StopWatch::reset() {
    _isStarted = false;
    _timeRunning = 0.0;
}

double StopWatch::getTime() {
    return _timeRunning >= 0.0 ? _timeRunning : 0.0;
}