#include "decryptPayload.h"

// Cl� XOR utilis�e pour le chiffrement
#define XOR_KEY 0xAA

void DecryptPayload(UCHAR** Dest, UCHAR* Src, SIZE_T sLen) {
    *Dest = (UCHAR*)LocalAlloc(LPTR, sLen); // Allocation m�moire
    if (*Dest == NULL) {
        std::cerr << "Erreur d'allocation m�moire pour le d�chiffrement." << std::endl;
        return;
    }

    for (SIZE_T i = 0; i < sLen; i++) {
        (*Dest)[i] = Src[i] ^ XOR_KEY; // Application XOR
    }
}
