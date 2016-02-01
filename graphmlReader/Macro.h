#pragma once

#include <stdio.h>

#ifdef _MSC_VER
#include <Windows.h>
#endif

#define SAFE_DEL(x) if(x) {	\
					delete x;			\
					x = NULL;			\
					}
