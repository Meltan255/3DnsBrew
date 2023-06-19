#include <3ds.h>
#include <citro3d.h>

#include "pizzatower.io.h"

int main(int argc, char **argv) {
    // Initialize 3DS system
    gfxInitDefault();

    // Initialize citro3d
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);

    // Initialize pizzatower.io
    pizzatower_io_init();

    // Main loop
    while (aptMainLoop()) {
        // Scan for user input
        hidScanInput();

        // Update pizzatower.io
        pizzatower_io_update();

        // Render pizzatower.io
        pizzatower_io_render();

        // Flush and swap framebuffers
        gfxFlushBuffers();
        gfxSwapBuffers();

        // Check if the user wants to exit
        if (hidKeysDown() & KEY_START) break;
    }

    // Deinitialize pizzatower.io
    pizzatower_io_exit();

    // Deinitialize citro3d
    C3D_Fini();

    // Deinitialize 3DS system
    gfxExit();

    return 0;
}
