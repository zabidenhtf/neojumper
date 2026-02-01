/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#pragma once

#include "interface.hpp"
#include "system.hpp"
#include "includes.hpp"
#include "component.hpp"
#include "version.hpp"

class menu_copyright : public component{
public:
	menu_copyright();
	virtual void reset();
	virtual void update(double tick);
	virtual void render();
private:
	string copyright_text;
	string version_text;
};