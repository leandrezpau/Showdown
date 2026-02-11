#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {

  if (argc < 2) {
    printf("uso: unpacker <nombre>\n");
    return 0;
  }

  char* objetivo = argv[1];

  FILE* dat = fopen("sprites.dat","rb");
  FILE* idx = fopen("index.txt","r");

  if (!dat || !idx) {
    printf("faltan archivos\n");
    return 0;
  }

  char name[256];
  long offset, size;
  int encontrado = 0;

  while (fscanf(idx,"%s %ld %ld",
         name,&offset,&size) == 3) {

    if (strcmp(name, objetivo) == 0) {

      unsigned char* buf = malloc(size);

      fseek(dat, offset, SEEK_SET);
      fread(buf,1,size,dat);

      FILE* out = fopen(name,"wb");
      fwrite(buf,1,size,out);

      fclose(out);
      free(buf);

      printf("extraido: %s\n", name);

      encontrado = 1;
      break;
    }
  }

  if (!encontrado)
    printf("no existe: %s\n", objetivo);

  fclose(dat);
  fclose(idx);

  return 0;
}