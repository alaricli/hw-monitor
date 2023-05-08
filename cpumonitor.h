#include <QApplication>
#include <QLabel>
#include <Windows.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Retrieve the temperature
    double temperature;
    DWORD bufferSize = sizeof(temperature);
    DWORD bytesRead;
    DWORD returnCode;
    HANDLE hDevice = CreateFileW(L"\\\\.\\thermalcoolingtuner", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hDevice == INVALID_HANDLE_VALUE) {
        QLabel label("Error opening device!");
        label.show();
        return app.exec();
    }
    BOOL success = DeviceIoControl(hDevice, 0x80102040, NULL, 0, &temperature, bufferSize, &bytesRead, NULL);
    returnCode = GetLastError();
    CloseHandle(hDevice);

    if (success) {
        QString temperatureStr = QString("CPU Temperature: %1°C").arg(temperature);
        QLabel label(temperatureStr);
        label.show();
    } else {
        QString errorStr = QString("Error retrieving temperature! Error code: %1").arg(returnCode);
        QLabel label(errorStr);
        label.show();
    }

    return app.exec();
}
