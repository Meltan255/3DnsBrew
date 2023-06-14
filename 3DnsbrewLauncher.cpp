#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main() {
    string dns = "18.188.135.9";
    string command = "ping -n 1 " + dns;
    int result = system(command.c_str());

    if (result == 0) {
        cout << "Connected to the internet with DNS " << dns << endl;
        string lumaCheck = "ls /luma/";
        int lumaResult = system(lumaCheck.c_str());

        if (lumaResult == 0) {
            cout << "Luma is already installed" << endl;
            string reboot = "reboot";
            system(reboot.c_str());
        } else {
            string lumaInstall = "https://github.com/LumaTeam/Luma3DS/releases/download/v12.0.1/Luma3DSv12.0.1.zip";
            string lumaCommand = "wget " + lumaInstall + " && 7z x Luma3DSv12.0.1.zip && cp -r Luma3DS /luma/ && rm -rf Luma3DSv12.0.1.zip";
            system(lumaCommand.c_str());
            cout << "Luma3DS has been installed" << endl;
            string reboot = "reboot";
            system(reboot.c_str());
        }
    } else {
        cout << "Not connected to the internet with DNS " << dns << endl;
    }

    return 0;
}
