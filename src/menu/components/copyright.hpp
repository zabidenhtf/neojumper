/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#ifndef MENU_COPYRIGHT_H
#define MENU_COPYRIGHT_H

#include "interface.hpp"
#include "system.hpp"
#include "includes.hpp"
#include "component.hpp"

class menu_copyright : public component{
public:
	menu_copyright();
	virtual void reset();
	virtual void update(double tick);
	virtual void render();
private:
	string copyright_text;
};

#endif