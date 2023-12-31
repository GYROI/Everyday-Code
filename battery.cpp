#include <iostream>
#include <Windows.h>
using namespace std;

int main() {
    SYSTEM_POWER_STATUS powerStatus;
    if (GetSystemPowerStatus(&powerStatus)) {
        if (powerStatus.BatteryFlag != 128) { // 128 indicates the battery is not present
            int remainingMinutes = powerStatus.BatteryLifeTime;
            if (remainingMinutes != -1) { // -1 means unknown remaining time
                cout << "Remaining Battery Time: " << remainingMinutes << " minutes" << endl;
            } else {
                cout << "Remaining Battery Time: Unknown" << endl;
            }
        } else {
            cout << "Battery not present." << endl;
        }
    } else {
        cout << "Unable to retrieve battery status." << endl;
    }

    return 0;
}
