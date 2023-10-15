#!/bin/bash

# Check for required dependencies
command -v gcc >/dev/null 2>&1 || { echo >&2 "GCC is required but it's not installed. Aborting."; exit 1; }
command -v gdbus >/dev/null 2>&1 || { echo >&2 "GDBus is required but it's not installed. Aborting."; exit 1; }

# Copy the switcher binary
echo "Copying switcher binary to /usr/local/bin..."
sudo cp switcher /usr/local/bin/

# Copy the systemd service file
echo "Setting up systemd service for user..."
mkdir -p ~/.config/systemd/user/
cp systemd/layout-switcher.service ~/.config/systemd/user/

# Enable and start the service
echo "Enabling and starting the layout-switcher service..."
systemctl --user enable layout-switcher.service
systemctl --user start layout-switcher.service

echo "Setup completed!"
