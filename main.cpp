#include <Windows.h>
#include <stdio.h>
#include <winhttp.h>

#pragma comment(lib, "Winhttp.lib")

int main()
{
    HINTERNET hSession = NULL;
    HINTERNET hConnect = NULL;
    HINTERNET hRequest = NULL;
    BOOL      bResults = FALSE;
    DWORD     dwSize = 0;
    DWORD     dwBytes = 0;
    SIZE_T    dwCurrentSize = 0;
    LPSTR     pszOutBuffer = NULL;

    hSession = WinHttpOpen(
        L"My Custom User Agent",
        WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS,
        0);

    if (!hSession)
    {
        printf("Failed to WinHttpOpen. Error: %d\n", GetLastError());
        goto cleanExit;
    }

    hConnect = WinHttpConnect(hSession, L"perdu.com", INTERNET_DEFAULT_HTTP_PORT, 0);

    if (!hConnect)
    {
        printf("Failed to WinHttpConnect. Error: %d\n", GetLastError());
        goto cleanExit;
    }

    hRequest = WinHttpOpenRequest(
        hConnect, L"GET", L"/", NULL,
        WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);

    if (!hRequest)
    {
        printf("Failed to WinHttpOpenRequest. Error: %d\n", GetLastError());
        goto cleanExit;
    }

    bResults = WinHttpSendRequest(
        hRequest,
        WINHTTP_NO_ADDITIONAL_HEADERS,
        0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);

    if (!bResults)
    {
        printf("Failed to WinHttpSendRequest. Error: %d\n", GetLastError());
        goto cleanExit;
    }

    bResults = WinHttpReceiveResponse(hRequest, NULL);

    if (!bResults)
    {
        printf("Failed to WinHttpReceiveResponse. Error: %d\n", GetLastError());
        goto cleanExit;
    }

    do
    {
        // Check for data available and retrieve its length
        dwSize = 0;
        if (!WinHttpQueryDataAvailable(hRequest, &dwSize))
            printf("Failed to WinHttpQueryDataAvailable. Error: %d\n", GetLastError());

        // Allocate a buffer
        if (!pszOutBuffer)
            pszOutBuffer = (LPSTR)LocalAlloc(LPTR, dwSize);

        // Reallocate memory 
        else
            pszOutBuffer = (LPSTR)LocalReAlloc(pszOutBuffer, dwCurrentSize + dwSize, LMEM_MOVEABLE | LMEM_ZEROINIT);

        if (!pszOutBuffer)
        {
            printf("Memory allocation failed\n");
            continue;
        }

        // Read the available data
        if (!WinHttpReadData(hRequest, pszOutBuffer + dwCurrentSize, dwSize, &dwBytes))
        {
            printf("Failed to WinHttpReadData. Error: %d\n", GetLastError());
        }

        // Increase the counter
        dwCurrentSize += dwSize;


    } while (dwSize > 0);

    printf("HTTP Response:\n%s\n", pszOutBuffer);

    LocalFree(pszOutBuffer);


cleanExit:
    if (hSession)
        WinHttpCloseHandle(hSession);
    if (hConnect)
        WinHttpCloseHandle(hConnect);
    if (hRequest)
        WinHttpCloseHandle(hRequest);
}