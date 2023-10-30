#!/bin/bash
# Timeout after 30 seconds
end=$((SECONDS+30))

while true; do
    # Check for X server availability
    xdpyinfo -display $DISPLAY >/dev/null 2>&1 && break

    if [ $SECONDS -gt $end ]; then
        echo "Timed out waiting for X server on display $DISPLAY"
        exit 1
    fi

    sleep 1
done

/usr/local/bin/switcher