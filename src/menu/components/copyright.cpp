/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "copyright.hpp"

#include "utils/graphics.hpp"

MenuCopyright::MenuCopyright(){
	Reset();
}

void MenuCopyright::Reset(){
	copyright_text = string(GAME_MILESTONE) + " | Copyright (C) 2025-2026 Mykyta Polishyk";
	version_text = "Version: " + string(GAME_VERSION);
}

void MenuCopyright::Update(float Tick){
	Render();
}

void MenuCopyright::Render(){
    Graphics->SetViewport(Graphics->GetWidth(), Graphics->GetHeight());
    Graphics->SetOrtho(Graphics->GetWidth(), Graphics->GetHeight());
    // Just draw text, nothing special
	Graphics->DrawText(vec2(12,Graphics->GetHeight()-(24+12)*2), 16, 16, version_text, vec4(0,0,0,1));
	Graphics->DrawText(vec2(12,Graphics->GetHeight()-24-12), 16, 16, copyright_text, vec4(0,0,0,1));
}