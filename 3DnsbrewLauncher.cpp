#include <3ds.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char **argv) {
    // Initialize services
    srvInit();
    aptInit();
    hidInit(NULL);
    gfxInitDefault();

    // Set DNS to 1.1.1.1
    u32 dns = 0x01010101;
    Result res = setsockopt(0, SOL_SOCKET, SO_SETDNS, &dns, sizeof(dns));
    if (res < 0) {
        printf("Failed to set DNS: %08lx\n", res);
        return 1;
    }

    // Check internet connection
    u32 wifiStatus;
    while (1) {
        ACU_GetWifiStatus(&wifiStatus);
        if (wifiStatus & 0x10000) {
            break;
        }
        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
    }

    // Load Luma3DS
    Result lumaRes = loadArm9Payload("path/to/Luma3DS.bin");
    if (lumaRes < 0) {
        printf("Failed to load Luma3DS: %08lx\n", lumaRes);
        return 1;
    }

    // Exit services
    gfxExit();
    hidExit();
    aptExit();
    srvExit();
    return 0;
}
