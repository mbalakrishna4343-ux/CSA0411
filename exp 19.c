#include <stdio.h>
#include <windows.h>

int counter = 0;      
HANDLE mutex;

DWORD WINAPI threadFunction(LPVOID arg) {
    int i;

    for (i = 0; i < 1000000; i++) {
        WaitForSingleObject(mutex, INFINITE);
        counter++;
        ReleaseMutex(mutex);
    }
    return 0;
}

int main() {

    HANDLE t1, t2;

    // Create mutex
    mutex = CreateMutex(NULL, FALSE, NULL);
    if (mutex == NULL) {
        printf("Mutex creation failed!\n");
        system("pause");
        return 1;
    }

    // Create threads
    t1 = CreateThread(NULL, 0, threadFunction, NULL, 0, NULL);
    t2 = CreateThread(NULL, 0, threadFunction, NULL, 0, NULL);

    if (t1 == NULL || t2 == NULL) {
        printf("Thread creation failed!\n");
        system("pause");
        return 1;
    }

    // Wait for threads to finish
    WaitForSingleObject(t1, INFINITE);
    WaitForSingleObject(t2, INFINITE);

    // Cleanup
    CloseHandle(t1);
    CloseHandle(t2);
    CloseHandle(mutex);

    printf("Final counter value = %d\n", counter);

    system("pause");
    return 0;
}
