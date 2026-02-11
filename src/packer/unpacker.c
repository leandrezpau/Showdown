#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

  FILE* dat = fopen("sprites.dat","rb");
  FILE* idx = fopen("index.txt","r");

  if (!dat || !idx) {
    printf("faltan archivos\n");
    return 0;
  }

  char name[256];
  long offset, size;

  while (fscanf(idx,"%s %ld %ld",
         name,&offset,&size) == 3) {

    unsigned char* buf = malloc(size);

    fseek(dat, offset, SEEK_SET);
    fread(buf,1,size,dat);

    FILE* out = fopen(name,"wb");
    fwrite(buf,1,size,out);

    fclose(out);
    free(buf);

    printf("extraido: %s\n", name);
  }

  fclose(dat);
  fclose(idx);

  return 0;
}