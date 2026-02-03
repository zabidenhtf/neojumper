/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */

#include "includes.hpp"
#include <SimpleIni.h>

#pragma once

class ConfigureSystem{
public:
	ConfigureSystem();
	string LoadData(string Section, string Key, string Standart);
private:
	CSimpleIniA ini; // Simple ini lib
};

extern ConfigureSystem *Config; // Global config pointer