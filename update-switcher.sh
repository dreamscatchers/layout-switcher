#!/bin/bash

# Path to your compiled switcher binary
NEW_BINARY_PATH="./switcher"

# Stop the layout-switcher service
echo "Stopping layout-switcher service..."
systemctl --user stop layout-switcher.service

# Copy the new compiled switcher binary to /usr/local/bin/
echo "Copying new switcher binary to /usr/local/bin..."
sudo cp $NEW_BINARY_PATH /usr/local/bin/

# Start the layout-switcher service with the new binary
echo "Starting layout-switcher service with new binary..."
systemctl --user start layout-switcher.service

echo "Update completed!"
