#!/bin/sh
# Install script

INSTALL_DIR='/usr/local/opt'
BIN_DIR='/usr/local/bin'

# Check if g++ is installed
if ! command -v g++ >/dev/null 2>&1; then
  echo "Error: g++ is not installed. Please install g++ and try again." >&2
  exit 1
fi

# Deleting the directory if it already exists
rm -rf "$INSTALL_DIR/onepiece-colorscripts" || { echo "Failed to remove existing directory."; exit 1; }

# Creating the necessary folder structure
mkdir -p "$INSTALL_DIR/onepiece-colorscripts" || { echo "Failed to create directories."; exit 1; }

# Moving files to appropriate locations
cp -rf colorscripts "$INSTALL_DIR/onepiece-colorscripts" || { echo "Failed to copy colorscripts."; exit 1; }
cp onepiece-colorscripts.cpp "$INSTALL_DIR/onepiece-colorscripts" || { echo "Failed to copy onepiece-colorscripts.cpp."; exit 1; }

# Compile the program
g++ -std=c++17 "$INSTALL_DIR/onepiece-colorscripts/onepiece-colorscripts.cpp" -o "$INSTALL_DIR/onepiece-colorscripts/onepiece-colorscripts" || { echo "Compilation failed."; exit 1; }

# Create symlink in /usr/local/bin
rm -rf "$BIN_DIR/onepiece-colorscripts" || { echo "Failed to remove old symlink."; exit 1; }
ln -s "$INSTALL_DIR/onepiece-colorscripts/onepiece-colorscripts" "$BIN_DIR/onepiece-colorscripts" || { echo "Failed to create symlink."; exit 1; }

echo "Installation complete. You can run the program using 'onepiece-colorscripts'."
