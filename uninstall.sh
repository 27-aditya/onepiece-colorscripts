#!/bin/sh
#Uninstall script

INSTALL_DIR='/usr/local/opt/onepiece-colorscripts'
BIN_DIR='/usr/local/bin/onepiece-colorscripts'

# Remove the installed files
if [ -d "$INSTALL_DIR" ]; then
  rm -rf "$INSTALL_DIR" || { echo "Failed to remove $INSTALL_DIR"; exit 1; }
  echo "Removed $INSTALL_DIR."
else
  echo "Installation directory not found: $INSTALL_DIR"
fi

# Remove the symlink in /usr/local/bin
if [ -L "$BIN_DIR" ]; then
  rm -f "$BIN_DIR" || { echo "Failed to remove $BIN_DIR"; exit 1; }
  echo "Removed symlink $BIN_DIR."
else
  echo "Symlink not found: $BIN_DIR"
fi

echo "Uninstallation complete."
