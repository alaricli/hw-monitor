#include <iostream>
#include <Windows.h>
#include <conio.h>

int main() {
    // Retrieve the temperature
    double temperature;
    DWORD bufferSize = sizeof(temperature);
    DWORD bytesRead;
    DWORD returnCode;
    HANDLE hDevice = CreateFileW(L"\\\\.\\thermalcoolingtuner", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hDevice == INVALID_HANDLE_VALUE) {
        std::cerr << "Error opening device!" << std::endl;
        return 1;
    }
    BOOL success = DeviceIoControl(hDevice, 0x80102040, NULL, 0, &temperature, bufferSize, &bytesRead, NULL);
    returnCode = GetLastError();
    CloseHandle(hDevice);

    if (success) {
        std::cout << "CPU Temperature: " << temperature << "°C" << std::endl;
    } else {
        std::cerr << "Error retrieving temperature! Error code: " << returnCode << std::endl;
    }

    _getch();
    return 0;
}
