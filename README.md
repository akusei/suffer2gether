# Green Hell Multiplayer Patch - More Suffering Together
TL;DR: Patch Green Hell to allow up to 8 people to play together instead of the default 4. Suffer More; Suffer Toegther!

![main patch window](/contrib/screenshot.png?raw=true "main patch window")

## Usage
Download the latest patch from the release page or build from source. The patch will detect if and where Green Hell is installed so all you have to do is click "PATCH". Once the patch says you're ready to play, exit the patch and start playing Green Hell.

This patch will need to be reapplied every time Green Hell is updated.

**NOTE:** Every player in your multiplayer session will need to apply this patch. If you don't, any player joining after the 4th will have no name plate above their head making it very difficult to see them.

## Building From source
This is not a cross-platform application as it's intended to be used on a Windows based game. It's also using MFC so only a Visual Studio solution is provided, no makefiles or other IDE project files. Everything you need to build from source is included in this repo, except [Visual Studio 2019](https://visualstudio.microsoft.com/downloads/) which you can download for free from Microsoft.

## Editing GIMP Resources
If you want to edit the buttons or font you will need to download and install the fonts listed in the [3rd Part Credit](#3rd-party-credit) section of this readme.

## Virus/Malware/Trojan Warnings
This file was written in C++ MFC with only 1 external lib dependency on uFMOD and it is NOT signed. For some reason this triggers a few anti-virus packages to see this as a generic trojan or malware. This is a false positive and can be safely ignored.

I originally started coding this in MASM32 Assembler for a much smaller executable and a more fun project but this was triggering A/V heuristic detections like crazy. So I switched to a Visual Studio MFC project and even test a blank MFC template on VirusTotal but even Microsoft's default MFC template with no modification is detected by a few A/V packages, including Microsoft Defender!

The source code is available to review or build from if you feel the release binary is untrusted. I will also be including the executable hash with every release

## 3rd Party Credit
**Background image:** Repurposed from the Green Hell game files and modified by me for use as a window background.

**Screen Font:** Neon Pixel-7 version 1.0 created by [styleseven.com](http://www.styleseven.com/php/get_product.php?product=Neon%20Pixel-7).

**Button Font:**
This font is copyright (c) Jakob Fischer at [www.pizzadude.dk](http://www.pizzadude.dk), all rights reserved. Do not distribute without the author's permission.
Use this font for non-commercial use only! If you plan to use it for commercial purposes, contact me before doing so!

**uFMOD:** [uFMOD](http://ufmod.sourceforge.net/) is used for playing the XM music file.

**Music:** Late at Morning created by Andreas Rohdin (MrGamer / Gamermachine). He has a lot of [great music](https://soundcloud.com/gamermachine). This module was downloaded from [modarchive](https://modarchive.org/index.php?request=view_by_moduleid&query=52842) and is distributed in this repository under the modarchive ["upload agreement"](https://modarchive.org/index.php?faq-licensing).
