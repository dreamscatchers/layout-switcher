# Layout Switcher

**Layout Switcher** is a utility designed for the GNOME environment, enabling users to deterministically switch between keyboard layouts using specific key combinations. Unlike the typical circular layout switching, where each key press toggles to the next layout in a sequence, Layout Switcher utilizes the left and right shift keys to provide predictable layout changes. By pressing the dedicated key (left shift for one layout and right shift for another), users can be confident in which layout they're switching to, ensuring a more efficient and user-friendly experience.

## Table of Contents

- [How It Works](#howitworks)
- [Features](#features)
- [Dependencies](#dependencies)
- [Building from Source](#building-from-source)
- [Installation](#installation)
  - [Manual](#manual)
  - [Automated](#automated)
- [Usage](#usage)
- [Uninstallation](#uninstallation)
- [Contributing](#contributing)
  - [Updating the Layout Switcher Binary](#contributing)
- [License](#license)

## How It Works

Layout Switcher utilizes the left and right shift keys to deterministically switch between keyboard layouts:

    Left Shift: Activates the first keyboard layout (Layout #1).
    Right Shift: Activates the second keyboard layout (Layout #2).

It's crucial to understand that the utility relies on the order of the layouts as they're listed in GNOME's input source manager. The program doesn't specifically distinguish between "en", "ru", or any other language codes. Instead, it's based on the order in which the layouts are installed or listed:

    inputSources[0]: This will be the layout that gets activated with the Left Shift key.
    inputSources[1]: This will be the layout that gets activated with the Right Shift key.

If, for example, you have French (fr) as the first layout and German (de) as the second in your GNOME settings, then pressing the left shift will switch to French, and the right shift will switch to German.

## Features

- Switch between two predefined keyboard layouts using specific key combinations.
- Lightweight and efficient.
- Integrated with the GNOME desktop environment.

### Dependencies

Before you start, ensure you have the following dependencies installed:

- `gcc`
- `libX11-dev`
- `libXi-dev`

On Debian-based systems, you can install these using:

```
sudo apt-get install gcc libX11-dev libXi-dev
```

### Building from Source

1. Clone this repository:
```
git clone https://github.com/dreamscatchers/layout-switcher.git
```

2. Navigate to the project directory:
```
cd layout-switcher
```


## Installation
## Manual

1. Compile the program:
```
gcc -o switcher switcher.c -lX11 -lXi
```

2. Move the compiled binary to `/usr/local/bin/`:
```
sudo mv switcher /usr/local/bin/
```

3. Create a service file `layout-switcher.service` in `~/.config/systemd/user/` with the provided content:

```
[Unit]
Description=Layout Switcher Daemon
After=display-manager.service
Wants=display-manager.service

[Service]
ExecStart=/usr/local/bin/start-switcher.sh
Environment=DISPLAY=:0
Environment=XAUTHORITY=/run/user/1000/gdm/Xauthority
Environment=XDG_RUNTIME_DIR=/run/user/1000
Environment=DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/1000/bus
Environment=PATH=/usr/bin:/usr/local/bin:/usr/local/sbin
Restart=on-failure

[Install]
WantedBy=graphical-session.target
```

4. Copy start-switcher.sh to /usr/local/bin and make it runnable

```
sudo cp start-switcher.sh /usr/local/bin
```

This script starts service correctly after X server started

5. Enable and start the service:

```
systemctl --user enable layout-switcher.service
systemctl --user start layout-switcher.service
```

6. To check service status run:

```
systemctl --user status layout-switcher.service
```

## Automated
**⚠️ WARNING:** Always review the content of scripts before executing them, especially if they require elevated privileges. Running scripts from the internet without verifying their actions can be harmful.

For a quick setup, you can run the provided setup script:

```bash
chmod +x setup.sh
./setup.sh
```


## Usage

Once set up, simply use the defined key combinations (e.g., Left Shift, Right Shift) to switch between your two predefined layouts.

## Uninstallation

To remove the **Layout Switcher** and its traces, you can use the provided uninstallation script:

```bash
chmod +x uninstall.sh
./uninstall.sh
```
## Contributing

Contributions, issues, and feature requests are welcome! Feel free to check [issues page](https://github.com/dreamscatchers/layout-switcher/issues).

## Updating the Layout Switcher Binary

After making changes and recompiling the `switcher` binary, you can use the provided update script to replace the currently running version:

```bash
chmod +x update-switcher.sh
./update-switcher.sh
```

## License

Distributed under the MIT License. See `LICENSE` for more information.
