## **Structure du Projet**

|**Fichier/Dossier**|**Description**|
|---|---|
|`main.cpp`|Code source principal du loader.|
|`server.py`|Script Python servant le shellcode chiffré.|
|`http.cpp`|Code pour lancer le serveur http.|
|`decryptPayload.cpp`|Code pour déchiffrer le payload|
|`inject.cpp`|Code pour injecter le shellcode|
|`README.md`|Instructions d'utilisation (ce fichier).|

## **Résumé des Objectifs Réalisés**

|**Objectif**|**Statut**|
|---|---|
|Injection de shellcode dans un processus distant|✅ Réalisé|
|Utilisation exclusive de l'API Windows|✅ Réalisé|
|Pas d'appel à des fonctions comme printf, scanf, malloc, free, strcpy, memcpy|✅ Réalisé|
|Téléchargement du shellcode depuis un serveur Web Python|✅ Réalisé|
|La page mémoire où le shellcode est injectée a les permissions RX|✅ Réalisé|
|README explicatif|✅ Réalisé|
|Pas de Warnings a la compilation|✅ Réalisé|
|Les variables allouées avec LocalAlloc sont libérées|✅ Réalisé|

|**Points Bonus**|**Statut**|
|---|---|
|GetModuleHandle & GetProcAddress Masking|❌ Pas fait|
|Custom GetModuleHandle & GetProcAddress|❌ Pas fait (+2)|
|API Hashing|❌ Pas fait|
|---|---|
|RC4 Encryption|❌ Pas fait|
|---|---|
|Random Key on Download|❌ Pas fait (+2)|
|---|---|
|Injection via PID|❌ Pas fait|
|Injection via Process Name|❌ Pas fait (+2)|
|---|---|
|Overwrite Shellcode Buffer with Zeros|❌ Pas fait (+1)|
|---|---|
|Use NTDLL Functions|❌ Pas fait|
|---|---|
|Alternative Injection Methods (APC, etc.)|❌ Pas fait|
|---|---|
|Other Relevant Features|❌ Pas fait|

Etape à suivre
Télcharger l'ensemble des fichiers.
Dans un powershell "python3 serveur.py"
Il suffira maintenant de lancer le main.
