#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char** argv) {

  if (argc < 2) {
    printf("uso: packer <carpeta>\n");
    return 0;
  }

  DIR* d = opendir(argv[1]);
  if (!d) {
    printf("no existe carpeta\n");
    return 0;
  }

  FILE* dat = fopen("sprites.dat","wb");
  FILE* idx = fopen("index.txt","w");

  struct dirent* f;
  long offset = 0;

  while ((f = readdir(d))) {

    if (strstr(f->d_name,".png") == NULL)
      continue;

    char path[256];
    sprintf(path,"%s/%s", argv[1], f->d_name);

    FILE* in = fopen(path,"rb");
    if (!in) continue;

    fseek(in,0,SEEK_END);
    long size = ftell(in);
    fseek(in,0,SEEK_SET);

    unsigned char* buf = malloc(size);
    fread(buf,1,size,in);

    fwrite(buf,1,size,dat);

    fprintf(idx,"%s %ld %ld\n",
      f->d_name, offset, size);

    offset += size;

    free(buf);
    fclose(in);

    printf("añadido: %s\n", f->d_name);
  }

  closedir(d);
  fclose(dat);
  fclose(idx);

  printf("OK\n");
  return 0;
}