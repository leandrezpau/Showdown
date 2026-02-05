#include <stdio.h>
#include <stdlib.h>

#include "sprites.h"

int Sprite::ExtractSprite(int number, const char *out_path) {
    FILE *in = fopen("../assets/sprites/sprites.dat", "rb");
    if (!in) { perror("fopen"); return 1; }

    // Saltar al índice específico en la cabecera
    fseek(in, (number - 1) * sizeof(SpriteIndex), SEEK_SET);

    SpriteIndex idx;
    if (fread(&idx, sizeof(SpriteIndex), 1, in) != 1) {
        printf("Error leyendo índice %d\n", number);
        fclose(in);
        return 1;
    }

    // Ir al bloque de datos
    fseek(in, idx.offset, SEEK_SET);

    char *buffer = (char*) malloc(idx.size);
    if (!buffer) { perror("malloc"); fclose(in); return 1; }

    if (fread(buffer, 1, idx.size, in) != (size_t)idx.size) {
        printf("Error leyendo sprite %d\n", number);
        free(buffer);
        fclose(in);
        return 1;
    }

    FILE *out = fopen(out_path, "wb");
    if (!out) { perror("fopen salida"); free(buffer); fclose(in); return 1; }

    fwrite(buffer, 1, idx.size, out);

    fclose(out);
    free(buffer);
    fclose(in);
    return 0;
}

void Sprite::DeleteAllSprites(){
	char filename[64];
	for(int i = 0; i < 722; i++){
		snprintf(filename, sizeof(filename), "../assets/sprites/%04d.png", i);
		if(remove(filename) == 0){
			printf("Sprite %s eliminado.\n", filename);
		}
	}
}