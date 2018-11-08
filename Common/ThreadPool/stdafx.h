// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#define NOMINMAX

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <memory>
#include <thread>
#include <mutex>
#include <array>
#include <condition_variable>
#include <atomic>
#include <chrono>
#include <future>
#include <assert.h>
#include <queue>

extern std::mutex g_mtxLog;
#define LOG(a) { std::lock_guard<std::mutex> lock(g_mtxLog); std::cout << a << std::endl; }