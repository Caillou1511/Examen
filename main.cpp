#include <iostream> 
#include <stdio.h>
#include <Windows.h>


#include "http.h" 


#include <tchar.h>

int main() {

    DWORD payloadSize = 0;
    PBYTE payload = getHTTPPayload(payloadSize);

    if (!payload) {
        std::cerr << "Erreur le shellcode n'est pas accessible " << std::endl;
        return 1;
    }

    std::cout << "Shellcode :" << std::endl;

    for (DWORD i = 0; i < payloadSize; i++) {
        printf("%02X ", payload[i]);
    }

    std::cout << std::endl;

    return 0;
}
