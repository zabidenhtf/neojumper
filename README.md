Warning, game now indev
# Open Jumper - 3D game about jumpstyle dancing

## Description
Open Jumper - 3D game about jumpstyle dancing writed on C++ language. In game available 0 maps and 1 jumper (player).
In game you can see
- 3D graphics
- Nice controls
- Combo system

## Authors
Mykyta Polishyk - main developer of game

## Controls
- Q - Kick forward with left leg
- E - Kick forward with right leg
- A - Stand on left feet
- D - Stand on right feet
- Z - Kick backward with left leg
- C - Kick backward with right leg
- Space - Flip

## Thanks for
- GLFW - Nice GL lib for C++
- LIBPNG and ZLIB - For png loading
- GLM - For graphics mathematics
- GLAD - For GL 3.3
- SimpleIni - For configs
- Freetype - Fonts render
- GIMP - my graphical editor
- ASSIMP - for 3d models loading 
- Blender - 3D editor

## Ingame combo
If you pressed more than 5 action buttons correctly, you will be get a combo. 
When combo score for each action button will be 40

## Building
### Windows
For build you need
* MinGW
* make
* G++
<br>
Use the powershell, and write
<br>
`
git clone https://github.com/zabidenhtf/openjumper.git
cd openjumper
make PLATFORM=WINDOWS
`

### Linux
Its similar to windows
For build you need
* g++ // it can be preinstalled into your distro
* libglfw3-dev
* libfreetype-dev
* libassimp-dev
* make // too
<br>
Use the terminal, and write
<br>
`
git clone https://github.com/zabidenhtf/openjumper.git
cd openjumper
make PLATFORM=LINUX
`

-------------
Milestone 0
Copyright (C) 2025-2026 Mykyta Polishyk

This project is licensed under the GNU General Public License v3.0 or later.
See the LICENSE file for details.
