#!/bin/bash

# Stop the service
echo "Stopping layout-switcher service..."
systemctl --user stop layout-switcher.service

# Disable the service
echo "Disabling layout-switcher service..."
systemctl --user disable layout-switcher.service

# Remove the systemd service file
echo "Removing systemd service file..."
rm -f ~/.config/systemd/user/layout-switcher.service

# Remove the switcher binary
echo "Removing switcher binary from /usr/local/bin..."
sudo rm -f /usr/local/bin/switcher

echo "Uninstall completed!"
