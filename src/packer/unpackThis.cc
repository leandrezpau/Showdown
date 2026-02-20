#include <stdio.h>
#include <stdlib.h>
#include <iostream>


int UnpackSprite(const char* objetivo,
                         const char* indice,
                         const char* ruta) {

  FILE* dat = fopen(ruta,"rb");
  FILE* idx = fopen(indice,"r");

  if (!dat || !idx) {
    printf("faltan archivos\n");
    return 0;
  }

  // ---- añadir .png al nombre buscado ----
  char objetivoPNG[256];
  snprintf(objetivoPNG, 256, "%s.png", objetivo);
  // ---------------------------------------

  char name[256];
  long offset, size;

  while (fscanf(idx,"%s %ld %ld",
         name,&offset,&size) == 3) {

    if (strcmp(name, objetivoPNG) == 0) {

      unsigned char* buf =
        (unsigned char*)malloc(size);

      fseek(dat, offset, SEEK_SET);
      fread(buf,1,size,dat);

      // ===== RUTA REAL DE SALIDA =====
      char salida[256];

      strcpy(salida, ruta);
      char* barra = strrchr(salida, '/');
      if (!barra) barra = strrchr(salida, '\\');

      if (barra) {
        *(barra+1) = 0;
        strcat(salida, name);
      } else {
        strcpy(salida, name);
      }

      printf("\n\nUnpacked .png file --> %s", salida);
      // ===============================

      FILE* out = fopen(salida,"wb");
      fwrite(buf,1,size,out);

      fclose(out);
      free(buf);

      fclose(dat);
      fclose(idx);

      return 1;   // OK
    }
  }

  fclose(dat);
  fclose(idx);

  return 0;       // no encontrado
}