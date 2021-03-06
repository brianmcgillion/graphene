/* -*- mode:c; c-file-style:"k&r"; c-basic-offset: 4; tab-width:4; indent-tabs-mode:nil; mode:auto-fill; fill-column:78; -*- */
/* vim: set ts=4 sw=4 et tw=78 fo=cqt wm=0: */

#include "pal.h"
#include "pal_debug.h"
#include "api.h"

int main (int argc, char ** argv, char ** envp)
{
    char buffer1[20] = "Hello World 1", buffer2[20] = "Hello World 2";
    char buffer3[20], buffer4[20];
    int ret;

    PAL_HANDLE pipe1 = DkStreamOpen("pipe.srv:1", PAL_ACCESS_RDWR, 0, 0, 0);

    if (pipe1) {
        pal_printf("Pipe Creation 1 OK\n");

        PAL_HANDLE pipe2 = DkStreamOpen("pipe:1", PAL_ACCESS_RDWR, 0, 0, 0);

        if (pipe2) {
            PAL_HANDLE pipe3 = DkStreamWaitForClient(pipe1);

            if (pipe3) {
                pal_printf("Pipe Connection 1 OK\n");

                ret = DkStreamWrite(pipe3, 0, 20, buffer1, NULL);
                if (ret > 0)
                    pal_printf("Pipe Write 1 OK\n");

                ret = DkStreamRead(pipe2, 0, 20, buffer3, NULL, 0);
                if (ret > 0)
                    pal_printf("Pipe Read 1: %s\n", buffer3);

                ret = DkStreamWrite(pipe2, 0, 20, buffer2, NULL);
                if (ret > 0)
                    pal_printf("Pipe Write 2 OK\n");

                ret = DkStreamRead(pipe3, 0, 20, buffer4, NULL, 0);
                if (ret > 0)
                    pal_printf("Pipe Read 2: %s\n", buffer4);
            }
        }
    }

    return 0;
}
