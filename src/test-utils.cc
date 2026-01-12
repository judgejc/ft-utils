// test-utils
// Copyright (c) 2026 James Crowley (judgejc.net)
// https://github.com/judgejc/ft-utils
//
// A simple app to test the ft-utils library.
//
// ==================== CODE REFERENCES ====================
// FT Server: https://github.com/hzeller/flaschen-taschen
// FT Demos: https://github.com/cgorringe/ft-demos
// =========================================================
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
// 01/01/2026 - Initial version to test simple logging functionality.
// ===================================================================

#include "ft-logger.h"

// A simple program to test logger functionality
int main()
{
    Logger logger("ft-utils.log");

    logger.log(INFO, "ft-utils logging initialized.");
    logger.log(DEBUG, "This is a debug message.");
    logger.log(WARNING, "This is a warning message.");
    logger.log(ERROR, "This is an error message.");
    logger.log(CRITICAL, "This is a critical message.");

    return 0;
}