// C++ source file for ft-fader
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

#include "flaschen-taschen.h"
#include "ft-logger.h"
#include "ft-fader.h"
#include <time.h>

using namespace std;

// Calculates difference between two timespecs for fade timing
struct timespec timespec_diff(struct timespec currenttime, struct timespec starttime)
{
    // Declare time constants
    constexpr long max_msec = 1000;
    constexpr long max_usec = 1000 * max_msec;
    constexpr long max_nsec = 1000 * max_usec;

    // Calculate timespec difference
    struct timespec result;
    result.tv_sec = currenttime.tv_sec - starttime.tv_sec;
    result.tv_nsec = currenttime.tv_nsec - starttime.tv_nsec;

    // Fix negative nanoseconds result
    if (result.tv_nsec < 0)
    {
        --result.tv_sec;
        result.tv_nsec += max_nsec;
    }
    return result;
}

// Constructor
Fader::Fader(string demoName, Color rgbValues, FadeOptions options)
{
    // Initialize fader variables if needed
}

// Destructor
Fader::~Fader()
{
}

// Creates a Logger instance for debug output
Logger logger("ft-fader.log");

Color Fader::update(FadeOptions options, bool debug)
{
    // Get fade type
    switch (options.type)
    {
    case BRIGHTNESS:
        // brightness fade logic here
        // Get current fade status
        switch (options.status)
        {
        case START:
            // get fade start time
            clock_gettime(CLOCK_MONOTONIC, &ts_fadestart);
            if (debug)
            {
                // debug output for fade start
                logger.log(LogLevel::DEBUG, "Fade started at: " +
                                                to_string((long long)ts_fadestart.tv_sec) + "." +
                                                to_string(ts_fadestart.tv_nsec));
            }
            break;
        case FADEIN:
        case FADEOUT:
            // calculate fade progress based on elapsed time
            clock_gettime(CLOCK_MONOTONIC, &ts_currenttime);
            ts_elapsed = timespec_diff(ts_currenttime, ts_fadestart);
            elapsedtime = ((double)(ts_elapsed.tv_sec) + ((double)(ts_elapsed.tv_nsec) / 1000000000));
            if (options.status == FADEIN)
            {
                // calculate fade progress for fade in
                fadeprogress = elapsedtime / options.opt_fadein;

                // calculate new rgb values based on fade progress
                new_r = options.opt_r * fadeprogress;
                new_g = options.opt_g * fadeprogress;
                new_b = options.opt_b * fadeprogress;

                // limit RGB max value to 255
                if (new_r > 255)
                {
                    new_r = 255;
                };
                if (new_g > 255)
                {
                    new_g = 255;
                };
                if (new_b > 255)
                {
                    new_b = 255;
                };
            }
            else if (options.status == FADEOUT)
            {
                // calculate fade progress for fade out
                fadeprogress = elapsedtime / options.opt_fadeout;

                // calculate new rgb values based on fade progress
                new_r = options.opt_r * (1.0 - fadeprogress);
                new_g = options.opt_g * (1.0 - fadeprogress);
                new_b = options.opt_b * (1.0 - fadeprogress);

                // limit RGB min value to 0
                if (new_r < 0)
                {
                    new_r = 0;
                };
                if (new_g < 0)
                {
                    new_g = 0;
                };
                if (new_b < 0)
                {
                    new_b = 0;
                };
            }

            if (debug)
            {
                // debug output for fade progress
                logger.log(LogLevel::DEBUG, "Fade progress: " +
                                                to_string(fadeprogress * 100) + "%, " +
                                                "Current time: " +
                                                to_string((long long)ts_currenttime.tv_sec) + "." +
                                                to_string(ts_currenttime.tv_nsec) + ", " +
                                                "Elapsed time: " +
                                                to_string(elapsedtime) + "s, " +
                                                "Original RGB: [" + to_string(options.opt_r) + ", " +
                                                to_string(options.opt_g) + ", " +
                                                to_string(options.opt_b) + "], " +
                                                "Modified RGB: [" + to_string((int)new_r) + ", " +
                                                to_string((int)new_g) + ", " +
                                                to_string((int)new_b) + "]");
            }
            break;
        case END:
            // get fade end time
            clock_gettime(CLOCK_MONOTONIC, &ts_fadeend);

            if (debug)
            {
                // debug output for fade end
                logger.log(LogLevel::DEBUG, "Fade ended at: " +
                                                to_string((long long)ts_fadeend.tv_sec) + "." +
                                                to_string(ts_fadeend.tv_nsec));
            }
            break;
        }
        break;
    case DISSOLVE:
        // dissolve fade logic here
        break;
    case CROSSFADE:
        // crossfade logic here
        break;
    }

    // Return new color based on calculated RGB values
    Color newColor((int)new_r, (int)new_g, (int)new_b);
    return newColor;
};