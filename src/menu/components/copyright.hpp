/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#pragma once

#include "utils/system.hpp"
#include "includes.hpp"
#include "component.hpp"
#include "version.hpp"

class MenuCopyright : public Component{
public:
	MenuCopyright();
	virtual void Reset();
	virtual void Update(float Tick);
	virtual void Render();
private:
	string copyright_text;
	string version_text;
};