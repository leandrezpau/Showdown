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
  │
  ├─ build/
  │  └─ ShowDown.sln
  │
  ├─ cmake/
  │
  ├─ include/
  │  ├─ SDL3/
  │  ├─ SDL3_image/
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
- SQLite3
- CMake
- Premake
- Visual Studio 2022

---

# Requisitos

## Windows
- Visual Studio 2022
- SDK de Windows
- SDL3
- SDL3_image
- SQLite3

## macOS
- Clang
- Make
- SDL3
- SDL3_image
- SQLite3

## Linux
- GCC o Clang
- Make
- SDL3
- SDL3_image
- SQLite3

---

# Instalación de Dependencias

## SDL3

Descargar desde el repositorio oficial:

https://github.com/libsdl-org/SDL

Colocar:
- headers en `include/SDL3`
- libs en `lib/x64` o arquitectura correspondiente

---

## SDL3_image

https://github.com/libsdl-org/SDL_image

Colocar:
- headers en `include/SDL3_image`
- libs en `lib/`

---

## SQLite

https://www.sqlite.org/download.html

Colocar:
- headers en `include/sqlite`
- librerías en `lib/`

---

# ⚙️ Compilación

---

## 🔹 Opción 1: Visual Studio (Recomendada en Windows)

1. Ejecutar:

tools/compile_vs2022.bat