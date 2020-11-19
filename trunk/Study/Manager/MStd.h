#pragma once
#include <windows.h>
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <tchar.h>
#include <string>
#include <algorithm>
#include <functional>
#include <set>

#define SAFE_NEW(A, B) { if(!A) A = new B; memset(A, 0, sizeof(B)); }
#define SAFE_DEL(A) { if(A) delete A; (A) = 0; }

using namespace std;
typedef basic_string<TCHAR> T_STR;
typedef basic_string<char> C_STR;
typedef basic_string<wchar_t> W_STR;

template <class T>
class MSingleton
{
	static T& instance()
	{
		static T* SgtIsts;
		return SgtIsts;
	}
};
