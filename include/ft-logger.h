// Header definitions for ft-logger
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
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
// ============================ CHANGELOG ============================
// 01/01/2026 - Initial version.
// ===================================================================

#ifndef FT_LOGGER_H
#define FT_LOGGER_H

#include <string>
#include <fstream>

// Enum to represent log levels
enum LogLevel { DEBUG, INFO, WARNING, ERROR, CRITICAL };

class Logger {
public:
    // Constructor: Opens the log file in append mode
    Logger(const std::string& filename);

    // Destructor: Closes the log file
    ~Logger();

    // Logs a message with a given log level
    void log(LogLevel level, const std::string& message);

private:
    std::ofstream logFile; // File stream for the log file

    // Converts log level to a string for output
    std::string levelToString(LogLevel level);
};

#endif // FT_LOGGER_H