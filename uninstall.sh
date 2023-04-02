#!/bin/bash

echo "Removing battery-status-indicator..."

systemctl stop battery-status-indicator.service

systemctl disable battery-status-indicator.service

rm /etc/systemd/system/battery-status-indicator.service

rm /usr/local/bin/battery-status-indicator

echo "Done."
