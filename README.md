# Layout Switcher

**Layout Switcher** is a small utility to allow users to switch their keyboard layouts using specific key combinations in a GNOME environment.

## Table of Contents

- [Features](#features)
- [Installation](#installation)
  - [Dependencies](#dependencies)
  - [Building from Source](#building-from-source)
- [Setup](#setup)
  - [Using SystemD User Service](#using-systemd-user-service)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Features

- Switch between two predefined keyboard layouts using specific key combinations.
- Lightweight and efficient.
- Integrated with the GNOME desktop environment.

## Installation

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

3. Compile the program:
```
gcc -o switcher switcher.c -lX11 -lXi
```

4. Move the compiled binary to `/usr/local/bin/`:
```
sudo mv switcher /usr/local/bin/
```

## Setup

### Using SystemD User Service

1. Ensure the compiled `switcher` binary is in `/usr/local/bin/`.
2. Create a service file `layout-switcher.service` in `~/.config/systemd/user/` with the provided content.
3. Enable and start the service:

```
systemctl --user enable layout-switcher.service
systemctl --user start layout-switcher.service
```

## Usage

Once set up, simply use the defined key combinations (e.g., Left Shift + Other Key, Right Shift + Other Key) to switch between your two predefined layouts.

## Contributing

Contributions, issues, and feature requests are welcome! Feel free to check [issues page](https://github.com/dreamscatchers/layout-switcher/issues). 

## License

Distributed under the MIT License. See `LICENSE` for more information.
