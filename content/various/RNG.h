/**
 * Author: Simon Lindholm
 * Date: 2015-03-15
 * License: CC0
 * Source: own work
 * Description: Fast random number generator.
 * Usage: rng(); shuffle(all(v), rng);
 * Status: stress-tested
 */
#pragma once

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
