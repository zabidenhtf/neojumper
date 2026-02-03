/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */

#pragma once

#include "includes.hpp"

struct ConsoleSystem{
	void Write(string Message); // Simple interface for cout
	void WriteDebug(string Tag, string Message); // Writing "[TAG] Message"
};

int RandomInt(int Min, int Max); // Find random number in range
string ReadFile(string Path);

// Global object
extern ConsoleSystem Console;