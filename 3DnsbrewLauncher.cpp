#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <sys/stat.h>

using namespace std;

bool isConnectedToInternet(const string& dns) {
    string command = "ping -n 1 " + dns;
    int result = system(command.c_str());
    return result == 0;
}

int main() {
    string dns = "8.8.8.8";

    // Check for internet connection and specific DNS
    while (!isConnectedToInternet(dns)) {
        cout << "Not connected to the internet with DNS " << dns << endl;
        sleep(5); // Wait for 5 seconds before checking again
    }

    cout << "Connected to the internet with DNS " << dns << endl;

    if (access("/luma/", F_OK) != -1) {
        cout << "Luma is already installed" << endl;
        string reboot = "reboot";
        system(reboot.c_str());
    } else {
        string lumaInstall = "https://github.com/LumaTeam/Luma3DS/releases/download/v12.0.1/Luma3DSv12.0.1.zip";
        string lumaCommand = "mkdir /luma/ && curl -L " + lumaInstall + " -o Luma3DSv12.0.1.zip && unzip Luma3DSv12.0.1.zip && cp -r Luma3DS /luma/ && rm -rf Luma3DSv12.0.1.zip";
        system(lumaCommand.c_str());
        system("/luma/Luma3DS.firm");
        cout << "Luma3DS has been installed" << endl;
        string reboot = "reboot";
        system(reboot.c_str());
    }

    return 0;
}
