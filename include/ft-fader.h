// Header definitions for ft-fader
// A collection of faders for the Flaschen Taschen Demos
//
// A component of ft-utils
// Copyright (c) 2026 James Crowley (judgejc.net)
// https://github.com/judgejc/ft-utils
//
// A set of utilities to extend the Flaschen Taschen Server
// for easier management and integration with other platforms.
//
// ======================== CODE REFERENCES ========================
//
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
// 05/01/2026 - Initial version.
// ===================================================================

#ifndef FT_FADER_H
#define FT_FADER_H

#include "flaschen-taschen.h"
#include <time.h>

// Enums to represent fade status and type
enum FadeStatus
{
    START,
    FADEIN,
    FADEOUT,
    END
};
enum FadeType
{
    BRIGHTNESS,
    DISSOLVE,
    CROSSFADE
};

// Struct to represent
struct FadeOptions
{
    FadeStatus status{};
    FadeType type{};
    int layer{};
    double opt_r{};
    double opt_g{};
    double opt_b{};
    double opt_fadein{};
    double opt_fadeout{};
};

// Calculates difference between two timespecs for fade timing
struct timespec timespec_diff(struct timespec currenttime, struct timespec starttime);

// Base class for faders
class Fader
{
public:
    // RGB values during fade
    double new_r = 0, new_g = 0, new_b = 0;

    // Fade timing variables
    struct timespec ts_fadestart;
    struct timespec ts_fadeend;
    struct timespec ts_currenttime;
    struct timespec ts_elapsed;
    double fadeprogress{};
    double elapsedtime{};

    // Constructor
    Fader(string demoName, Color rgbValues, FadeOptions options);

    // Destructor
    ~Fader();

    // Update fade progress and return new RGB color
    Color update(FadeOptions options, bool debug);

private:
};

#endif // FT_FADER_H