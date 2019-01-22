#pragma once

#include <iostream>
#include <chrono>
#include <ctime> 

class Util {
public:
	static std::chrono::system_clock::time_point GetCurrentTime() {
		auto start = std::chrono::system_clock::now();
		return start;
	}
	static float GetElapsedTime(std::chrono::system_clock::time_point start) {
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		return elapsed_seconds.count();
	}
	
	
};