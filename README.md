# NexiScan

NexiScan is a simple port scanner implemented in C++. It allows you to scan a target IP address for open ports and determine the associated service name.

## Prerequisites

- C++ compiler
- Linux operating system (or compatible terminal emulator) or MacOS
- Make

## Installation and Compilation

1. Open a terminal.
2. Clone the Repo `git clone https://github.com/AmTriiX/NexiScan.git`
3. Navigate in the Folder `cd NexiScan`
4. Run `make` command to compile the program.

## Usage

```
./nexis -t/--target <IP address> [-p/--port <port>]
```

- `-t/--target`: Specify the target IP address to scan.
- `-p/--port`: Optional. Specify a single port or a comma-separated list of ports to scan. If not provided, the program will scan the default port range (from 1 to 65535).

## Examples

1. Scan a target IP address for open ports using the default port range:
   ```
   ./nexis -t 192.168.1.1
   ```

2. Scan a target IP address for a specific port:
   ```
   ./nexis -t 192.168.1.1 -p 80
   ```

3. Scan a target IP address for multiple specific ports:
   ```
   ./nexis -t 192.168.1.1 -p 80,443,8080
   ```

## Notes

- Open ports will be displayed in green, indicating that they are open. The associated service name, if available, will be shown in yellow.
- Closed ports will be displayed in red.


## Cleaning Up

To clean up the compiled files, run the following command:

```
make clean
```

This will remove the executable file and any object files generated during the compilation process.

## Recommendation

Please use this program responsibly and ensure that you have the necessary permissions to scan the target IP address. Port scanning should only be performed on systems you are authorized to scan, and in compliance with applicable laws and regulations.

## Contributing

Contributions are welcome! If you find any issues or have suggestions for improvements, feel free to open an issue or submit a pull request.

## License 

This project is licensed under the MIT License. See the LICENSE file for details.