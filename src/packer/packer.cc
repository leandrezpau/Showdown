#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <filesystem>
namespace fs = std::filesystem;

int main(int argc, char** argv) {
  fs::path carpeta = "../../assets/SpritesAnimated/Icons shiny";

  if (!fs::exists(carpeta)) {
    printf("no existe carpeta\n");
    return 0;
  }

  FILE* dat = fopen("../../assets/SpritesAnimated/Icons shiny/_sprites.dat","wb");
  FILE* idx = fopen("../../assets/SpritesAnimated/Icons shiny/_index.txt","w");

  if (!dat || !idx) {
    printf("error creando salida\n");
    return 0;
  }

  long offset = 0;

  for (auto& p : fs::directory_iterator(carpeta)) {

    if (p.path().extension() != ".png")
      continue;

    std::string name = p.path().filename().string();
    std::string path = p.path().string();

    FILE* in = fopen(path.c_str(),"rb");
    if (!in) continue;

    fseek(in,0,SEEK_END);
    long size = ftell(in);
    fseek(in,0,SEEK_SET);

    unsigned char* buf =
      (unsigned char*)malloc(size);

    fread(buf,1,size,in);

    fwrite(buf,1,size,dat);

    fprintf(idx,"%s %ld %ld\n",
      name.c_str(), offset, size);

    offset += size;

    free(buf);
    fclose(in);

    printf("añadido: %s\n", name.c_str());
  }

  fclose(dat);
  fclose(idx);

  printf("OK\n");
  return 0;
}