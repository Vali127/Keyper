#!/bin/sh

# Compiling the program
g++ -std=c++23 -Wall -Wextra -Werror main.cpp utils/*.cpp -I include -o keyper
if [ $? -ne 0 ]; then
    echo "verify you have the compiler g++."
    exit 1
fi

# Installing keyper
sudo mv keyper /usr/local/bin
if [ $? -ne 0 ]; then
    echo "verify that /usr/local/bin exists."
    exit 1
fi

# Vérify if /usr/local/bin is not in PATH
if ! echo ":$PATH:" | grep -q ":/usr/local/bin:";then
    # finding the good config file for the shell
    SHELL_RC=""
    if [ -n "$ZSH_VERSION" ] || [ "$(basename "$SHELL")" = "zsh" ]; then
        SHELL_RC="$HOME/.zshrc"
    elif [ -n "$BASH_VERSION" ] || [ "$(basename "$SHELL")" = "bash" ]; then
        SHELL_RC="$HOME/.bashrc"
    else
        echo "Can't find the config file for the shell"
        exit 1
    fi

    if ! grep -q '/usr/local/bin' "$SHELL_RC"; then
       echo 'export PATH="/usr/local/bin:$PATH"' >> "$SHELL_RC"
    fi
    
    # adding the /usr/local/bin in path temporary for the current session 
    export PATH="/usr/local/bin:$PATH"
fi
exec keyper