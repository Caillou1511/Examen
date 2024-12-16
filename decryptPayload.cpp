#include "decryptPayload.h"

// Clé XOR utilisée pour le chiffrement
#define XOR_KEY 0xAA

void DecryptPayload(UCHAR** Dest, UCHAR* Src, SIZE_T sLen) {
    *Dest = (UCHAR*)LocalAlloc(LPTR, sLen); // Allocation mémoire
    if (*Dest == NULL) {
        std::cerr << "Erreur d'allocation mémoire pour le déchiffrement." << std::endl;
        return;
    }

    for (SIZE_T i = 0; i < sLen; i++) {
        (*Dest)[i] = Src[i] ^ XOR_KEY; // Application XOR
    }
}
