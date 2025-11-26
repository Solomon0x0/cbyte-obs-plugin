# CByte OBS Plugin

A modern, Windows-only **OBS Studio** plugin architecture developed with **C++17** and **Qt 6**.

This project implements a clean, "out-of-tree" build system, removing legacy cross-platform bloat to focus entirely on a robust Windows development environment using **Visual Studio 2022** and **PowerShell**.

## Architecture

* **Backend:** Modern C++ (C++17/20 compliant).
* **Frontend:** Qt 6 Widgets (Dockable UI).
* **Build System:** CMake with `Presets` (No legacy wrapper scripts).
* **CI/CD:** GitHub Actions (Windows Server 2022 + PowerShell Core).

## Prerequisites

To build this project locally, you need:

* **Windows 10/11 (x64)**
* **Visual Studio 2022** (Desktop development with C++ workload)
* **CMake** (v3.20 or newer)
* **Qt 6.x** (LTS recommended, e.g., 6.6.3) - *Must include MSVC 2019/2022 64-bit components.*
