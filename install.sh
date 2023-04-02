#!/bin/bash

set -e

# Check if running as root

if [ "$EUID" -ne 0 ]

  then echo "Please run as root"

  exit

fi

# Install necessary packages

apt-get update

apt-get install -y build-essential

# Compile program

gcc -o battery-status-indicator battery-status-indicator.c

# Move program to /usr/local/bin

mv battery-status-indicator /usr/local/bin/

# Create systemd service file

cat <<EOF > /etc/systemd/system/battery-status-indicator.service

[Unit]

Description=Battery status indicator

[Service]

ExecStart=/usr/local/bin/battery-status-indicator

[Install]

WantedBy=multi-user.target

EOF

# Reload systemd

systemctl daemon-reload

# Enable service to run on startup

systemctl enable battery-status-indicator.service

# Start service

systemctl start battery-status-indicator.service

echo "Battery status indicator installed successfully."

