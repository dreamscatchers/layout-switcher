#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/extensions/XInput2.h>

// Constants for the gdbus commands and key details
const char *CMD_GDBUS_US[] = {
    "gdbus", "call", "--session", "--dest=org.gnome.Shell",
    "--object-path=/org/gnome/Shell", "--method=org.gnome.Shell.Eval",
    "imports.ui.status.keyboard.getInputSourceManager().inputSources[0].activate()", NULL
};

const char *CMD_GDBUS_RU[] = {
    "gdbus", "call", "--session", "--dest=org.gnome.Shell",
    "--object-path=/org/gnome/Shell", "--method=org.gnome.Shell.Eval",
    "imports.ui.status.keyboard.getInputSourceManager().inputSources[1].activate()", NULL
};

#define LEFT_SHIFT_KEY 50
#define RIGHT_SHIFT_KEY 62

void switch_to_layout(const char *layout) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Failed to fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // Child process
        freopen("/dev/null", "w", stdout);
        freopen("/dev/null", "w", stderr);

        if (strcmp(layout, "us") == 0) {
            execvp(CMD_GDBUS_US[0], (char *const *)CMD_GDBUS_US);
        } else if (strcmp(layout, "ru") == 0) {
            execvp(CMD_GDBUS_RU[0], (char *const *)CMD_GDBUS_RU);
        }

        perror("Failed to execute command");
        exit(EXIT_FAILURE);
    }
}

void handle_key_press(int detail, int *LS, int *RS, int *OK) {
    if (detail == LEFT_SHIFT_KEY) {
        *LS = 1;
        *OK = 0;
    } else if (detail == RIGHT_SHIFT_KEY) {
        *RS = 1;
        *OK = 0;
    } else {
        if (*LS == 1 || *RS == 1) {
            *OK = 1;
        }
    }
}

void handle_key_release(int detail, int LS, int RS, int OK) {
    if (detail == LEFT_SHIFT_KEY && LS && !OK) {
        switch_to_layout("us");
    } else if (detail == RIGHT_SHIFT_KEY && RS && !OK) {
        switch_to_layout("ru");
    }
}

int main() {
    Display *display = XOpenDisplay(NULL);
    if (!display) {
        fprintf(stderr, "Unable to open display.\n");
        return 1;
    }

    int opcode, event, error;
    if (!XQueryExtension(display, "XInputExtension", &opcode, &event, &error)) {
        fprintf(stderr, "X Input extension not available.\n");
        return 1;
    }

    int major = 2, minor = 2;
    if (XIQueryVersion(display, &major, &minor) == BadRequest) {
        fprintf(stderr, "Not supported XI %d.%d\n", major, minor);
        return 1;
    }
    
    Window root = DefaultRootWindow(display);
    
    XIEventMask evmask;
    unsigned char mask[(XI_LASTEVENT + 7)/8] = { 0 };
    evmask.deviceid = XIAllDevices;
    evmask.mask_len = sizeof(mask);
    evmask.mask = mask;
    XISetMask(mask, XI_KeyPress);
    XISetMask(mask, XI_KeyRelease);
    
    XISelectEvents(display, root, &evmask, 1);

    XEvent ev;
    int LS = 0, RS = 0, OK = 0;

    while (1) {
        XNextEvent(display, &ev);
        XGenericEventCookie *cookie = &ev.xcookie;

        if (cookie->type == GenericEvent && cookie->extension == opcode) {
            if (XGetEventData(display, cookie) &&
               (cookie->evtype == XI_KeyPress || cookie->evtype == XI_KeyRelease)) {
                XIDeviceEvent* xievent = (XIDeviceEvent*)cookie->data;

                if (xievent) {
                    if (xievent->evtype == XI_KeyPress) {
                        handle_key_press(xievent->detail, &LS, &RS, &OK);
                    } else if (xievent->evtype == XI_KeyRelease) {
                        handle_key_release(xievent->detail, LS, RS, OK);
                    }
                } else {
                    fprintf(stderr, "xievent data is null!\n");
                }
            } else {
                fprintf(stderr, "Not an XI2 key event or failed to get event data.\n");
            }

            XFreeEventData(display, cookie);
        } else {
            fprintf(stderr, "Not a generic event.\n");
        }
    }

    XCloseDisplay(display);
    return 0;
}
