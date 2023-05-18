#include <arpa/inet.h>
#include <iostream>
#include <netdb.h>
#include <string>
#include <sstream>
#include <sys/socket.h>
#include <unistd.h>

const int MIN_PORT = 1;         // Minimum valid port number
const int MAX_PORT = 65535;     // Maximum valid port number

// Function to check if a port on the given IP address is open
bool isPortOpen(const std::string& ipAddress, int port) {
    int socketFD = socket(AF_INET, SOCK_STREAM, 0);  // Create a socket
    if (socketFD == -1) {
        std::cerr << "Error in socket creation" << std::endl;  // Error in socket creation
        return false;
    }

    struct sockaddr_in targetAddress;
    targetAddress.sin_family = AF_INET;
    targetAddress.sin_addr.s_addr = inet_addr(ipAddress.c_str());   // Convert IP address to network format
    targetAddress.sin_port = htons(port);    // Convert port number to network format

    if (connect(socketFD, (struct sockaddr*)&targetAddress, sizeof(targetAddress)) == 0) {
        close(socketFD);    // Close the socket if the connection is successful
        return true;
    }

    close(socketFD);    // Close the socket
    return false;
}

// Function to retrieve the service name associated with a port
std::string getServiceName(int port) {
    struct servent* serviceInfo = getservbyport(htons(port), "tcp");    // Look up service information by port number
    if (serviceInfo) {
        return serviceInfo->s_name;     // Return the service name if found
    }
    return "Unknown";   // Service name not found
}

// Function to print the usage instructions for the program
void printUsage(const std::string& programName) {
    std::cerr << "Usage: " << programName << " -t/--target <IP address> [-p/--port <port>]" << std::endl;
}

// Function to scan a range of ports on the specified IP address
void scanPorts(const std::string& ipAddress, int startPort, int endPort) {
    for (int port = startPort; port <= endPort; ++port) {
        if (isPortOpen(ipAddress, port)) {
            std::cout << "\033[32mPort " << port << " open\033[0m"   // Print the open port in green
                      << " - \033[33mService: " << getServiceName(port) << "\033[0m"   // Print the associated service name in yellow
                      << '\n';
        }
    }
}

// Function to scan a list of specified ports on the specified IP address
void scanSpecifiedPorts(const std::string& ipAddress, const std::string& portList) {
    std::stringstream ss(portList);
    std::string portString;
    while (getline(ss, portString, ',')) {
        int port = std::stoi(portString);
        if (port < MIN_PORT || port > MAX_PORT) {
            std::cerr << "Invalid port: " << port << ". Ports must be between " << MIN_PORT << " and " << MAX_PORT << "." << std::endl;
            return;
        }
        if (isPortOpen(ipAddress, port)) {
            std::cout << "\033[32mPort " << port << " open\033[0m"   // Print the open port in green
                      << " - \033[33mService: " << getServiceName(port) << "\033[0m"   // Print the associated service name in yellow
                      << '\n';
        } else {
            std::cout << "\033[31mPort " << port << " close\033[0m" << '\n';   // Print the closed port in red
        }
    }
}

int main(int argc, char* argv[]) {
    std::string ipAddress;
    int startPort = MIN_PORT;
    int endPort = MAX_PORT;

    if (argc < 3 || argc > 5) {
        printUsage(argv[0]);    // Print usage instructions if the number of arguments is incorrect
        return 1;
    }

    std::string option = argv[1];
    if (option == "-t" || option == "--target") {
        ipAddress = argv[2];    // Retrieve the target IP address from the command-line argument
    } else {
        std::cerr << "Invalid Option. ";
        printUsage(argv[0]);    // Print error message and usage instructions for an invalid option
        return 1;
    }

    if (argc > 3) {
        std::string portOption = argv[3];
        if (portOption == "-p" || portOption == "--port") {
            if (argc == 4) {
                std::cerr << "Specify at least one port or a comma-separated list of ports." << std::endl;
                return 1;
            }
            std::string portList = argv[4];    // Retrieve the port list from the command-line argument
            scanSpecifiedPorts(ipAddress, portList);    // Scan the specified ports
            return 0;
        } else {
            std::cerr << "Invalid Option. ";
            printUsage(argv[0]);    // Print error message and usage instructions for an invalid option
            return 1;
        }
    }

    scanPorts(ipAddress, startPort, endPort);    // Scan the default port range

    return 0;
}
