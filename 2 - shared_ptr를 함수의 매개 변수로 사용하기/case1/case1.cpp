// case1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <memory>
#include <chrono>


using namespace std;
using namespace chrono;
using namespace chrono_literals;

volatile int g_moo = 10;
const int TotalWorkCount = 100000000;

// #TODO 1. shared_ptr을 byvalue로 주고 받는 것과 byref를 주고 받는 것의 차이를 알아보자.

void Func2(shared_ptr<int64_t> a, shared_ptr<int64_t> b);

void Func1(shared_ptr<int64_t> a, shared_ptr<int64_t> b)
{
	(*a)++;
	(*b)++;
	Func2(a, b);
}

void Func2(shared_ptr<int64_t> a, shared_ptr<int64_t> b)
{
	(*a) += g_moo;
	(*b) += g_moo;
}

int main()
{
	auto t0 = high_resolution_clock::now();

	shared_ptr<int64_t> a = make_shared<int64_t>(0);
	shared_ptr<int64_t> b = make_shared<int64_t>(100);

	for (int i = 0; i < TotalWorkCount; i++)
	{
		Func1(a, b);
	}
	auto t1 = high_resolution_clock::now();

	auto elapsedMs = duration_cast<milliseconds>(t1 - t0).count();

	std::cout << "Work took " << elapsedMs << " ms.\n";
	std::cout << "a=" << *a << ", b=" << *b << endl;
}
