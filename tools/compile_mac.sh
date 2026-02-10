#!/bin/bash
clear

# 1. Compilar
premake5 --file=premake.lua gmake
make -C ../build config=debug TestSDL

if [ $? -eq 0 ]; then
  echo "\033[0;32mCOMPILADO\033[0m"
  
  # 2. REDIRECCIÓN
  # Forzamos las rutas locales
  install_name_tool -change "@rpath/SDL3.framework/Versions/A/SDL3" "@rpath/libSDL3.dylib" ../bin/TestSDL
  install_name_tool -change "@rpath/SDL3_image.framework/Versions/A/SDL3_image" "@rpath/libSDL3_image.dylib" ../bin/TestSDL
  
  # 3. FIRMA COMPLETA
  # --deep asegura que firme también las dependencias que el binario arrastra
  echo "Firmando binario y dependencias..."
  codesign --force --deep --sign - ../bin/TestSDL
  
  # 4. Limpiar caché de ejecución (Paso extra para evitar el Killed: 9)
  # A veces macOS recuerda que el binario era "malo"
  mv ../bin/TestSDL ../bin/TestSDL_tmp
  mv ../bin/TestSDL_tmp ../bin/TestSDL

  echo "Ejecutando..."
  ../bin/TestSDL
else
  echo "\033[0;31mERROR\033[0m"
fi