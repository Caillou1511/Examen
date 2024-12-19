#pragma once
#ifndef INJECT_H
#define INJECT_H

#include <windows.h>

// Déclaration de la fonction injectShellcode
bool injectShellcode(LPVOID shellcode, SIZE_T shellcodeSize, DWORD targetPid);

#endif // INJECT_H
