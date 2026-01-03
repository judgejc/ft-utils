// C++ source file for ft-logger
// A simple logging utility for the Flaschen Taschen Server and Demos
//
// A component of ft-utils
// Copyright (c) 2026 James Crowley (judgejc.net)
// https://github.com/judgejc/ft-utils
//
// A set of utilities to extend the Flaschen Taschen Server
// for easier management and integration with other platforms.
// 
// ======================== CODE REFERENCES ========================
// Logger: https://www.geeksforgeeks.org/cpp/logging-system-in-cpp/
// =================================================================
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
// ============================ CHANGELOG ============================
// 01/01/2026 - Initial version.
// 02/01/2026 - Updated to write files to ./logs/ directory in CWD.
// 03/01/2026 - Create logs directory if it does not exist and fixed
// filename output in console when the logfile cannot be opened.
// ===================================================================

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include "ft-logger.h"

using namespace std;

// Constructor: Opens the log file in append mode
Logger::Logger(const string& filename)
{
    // Retrieve current working directory and set log file path
    std::filesystem::path cwd = std::filesystem::current_path();
    std::filesystem::path logDir = cwd / "logs";
    std::filesystem::path logPath = logDir / filename;
    
    // Debug output
    cout << "Log file name: " << filename << endl;
    cout << "Current working directory: " << cwd << endl;
    cout << "Log file path: " << logPath << endl;
    
    // Create logs directory if it doesn't exist
    if (!std::filesystem::exists(logDir)) {
        std::filesystem::create_directory(logDir);
        cout << "Created logs directory: " << logDir << endl;
    }

    // Open the log file in append mode
    logFile.open(logPath, ios::app);
    if (!logFile.is_open()) {
        cerr << "Error opening log file: " << filename << endl;
    }
}

// Destructor: Closes the log file
Logger::~Logger() { logFile.close(); }

// Logs a message with a given log level
void Logger::log(LogLevel level, const string& message)
{
    // Get current timestamp
    time_t now = time(0);
    tm* timeinfo = localtime(&now);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp),"%Y-%m-%d %H:%M:%S", timeinfo);

    // Create log entry
    std::ostringstream logEntry;
    logEntry << "[" << timestamp << "] "
            << Logger::levelToString(level) << ": " << message
            << endl;

    // Output to console
    cout << logEntry.str();

    // Output to log file
    if (Logger::logFile.is_open()) {
        Logger::logFile << logEntry.str();
        Logger::logFile
            .flush(); // Ensure immediate write to file
    }
}

// Converts log level to a string for output
string Logger::levelToString(LogLevel level)
{
    switch (level) {
    case DEBUG:
        return "DEBUG";
    case INFO:
        return "INFO";
    case WARNING:
        return "WARNING";
    case ERROR:
        return "ERROR";
    case CRITICAL:
        return "CRITICAL";
    default:
        return "UNKNOWN";
    }
}