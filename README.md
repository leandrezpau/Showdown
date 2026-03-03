# ShowDown

Motor de combate estilo Pokémon desarrollado en C/C++ con SDL3 y SQLite.  
Proyecto académico / experimental enfocado en arquitectura modular, IA básica y gestión de datos desde base de datos.

---

# Tabla de Contenidos

- Descripción
- Características
- Tecnologías
- Requisitos
- Instalación de Dependencias
- Compilación
- Ejecución
- Estructura del Proyecto
- Arquitectura Interna
- Base de Datos
- Scripts y Herramientas
- Modo Debug
- Problemas Comunes
- Roadmap
- Licencia

---

# Descripción

ShowDown es un sistema de combate por turnos inspirado en Pokémon.  
Incluye:

- Sistema de tipos
- Cálculo de daño
- IA básica
- Carga de datos desde SQLite
- Renderizado con SDL3

El objetivo es mantener una arquitectura clara y modular.

---

# Características

- Motor de combate por turnos
- Sistema de tipos y efectividades
- Movimientos con estadísticas
- IA básica para decisiones
- Base de datos SQLite integrada
- Sistema modular por componentes
- Multi-arquitectura (x86, x64, arm64)

# Estructura del proyecto

```
C:/
  ├─ .DS_Store
  ├─ .gitignore
  ├─ README.md
  ├─ STRUCTURE.md
  │
  ├─ assets/
  │  ├─ background_Sprites/
  │  ├─ Database/
  │  └─ SpritesAnimated/
  │
  ├─ bin/
  │  └─ ShowDown.exe
  │
  ├─ build/
  │  └─ ShowDown.sln
  │
  ├─ cmake/
  │
  ├─ include/
  │  ├─ SDL3/
  │  ├─ SDL3_image/
  │  ├─ SDL3_ttf/
  │  └─ sqlite/
  │
  ├─ lib/
  │  ├─ arm64/
  │  ├─ x64/
  │  └─ x86/
  │
  ├─ src/
  │  ├─ battleai.cc
  │  ├─ battleai.h
  │  ├─ game.h
  │  ├─ main.cc
  │  ├─ movements.cc
  │  ├─ movements.h
  │  ├─ pokemon.cc
  │  ├─ pokemon.h
  │  ├─ sprites.cc
  │  ├─ sprites.h
  │  ├─ trainer.cc
  │  ├─ trainer.h
  │  ├─ types.cc
  │  ├─ types.h
  │  │
  │  ├─ packer/
  │  │  └─ unpackThis.cc
  │  │
  │  └─ sqlfuncs/
  │     ├─ returnPokeData.cc
  │     └─ returnPokeData.h
  │
  └─ tools/
     ├─ compile_vs2022.bat
     ├─ mac_compile.sh
     └─ premake.lua
```

# Tecnologías

- C / C++
- SDL3
- SDL3_image
- SDL3_ttf
- SQLite3
- CMake
- Premake
- Visual Studio 2022

---

# Requisitos

## Windows
- Visual Studio 2022
- SDK de Windows

## macOS
- Clang
- Make

---

# Instalación de Dependencias

## SDL3

Ya instalado

https://github.com/libsdl-org/SDL


## SDL3_image

Ya instalado

https://github.com/libsdl-org/SDL_image

## SDL3_ttf

Ya instalado

https://github.com/libsdl-org/SDL_ttf


## SQLite

Ya instalado

https://www.sqlite.org/download.html


# Compilación

## Windows: Visual Studio (Recomendada)

1. Ejecutar:

tools/compile_vs2022.bat

build/ShowDown.sln

* Click sobre "Depurador Local de Windows"

## Windows: MSCV

1. Ejecutar:

Abrir: x64 Native Tools Command Prompt for VS 2022

ir a /tools

ejecutar ./lang_compile.bat

* .exe Generado en /bin/ShowDown.exe