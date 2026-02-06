#include <stdio.h>
#include <stdlib.h>

#include "sprites.h"

int Sprite::ExtractSprite(int kNPokemons) {

    FILE *in = fopen("../assets/sprites.dat", "rb");
    if (!in) { perror("fopen"); return 1; }

    for(int i = 0; i < kNPokemons; i++) {

        char fileSprite[50];
        snprintf(fileSprite, sizeof(fileSprite), "../assets/sprites/%04d.png", i + 1);

        // Leer índice correcto
        fseek(in, i * sizeof(SpriteIndex), SEEK_SET);

        SpriteIndex idx;
        if (fread(&idx, sizeof(SpriteIndex), 1, in) != 1) {
            printf("Error leyendo índice %d\n", i);
            fclose(in);
            return 1;
        } 

        fseek(in, idx.offset, SEEK_SET);

        char *buffer = (char*)malloc(idx.size);
        if (!buffer) { perror("malloc"); fclose(in); return 1; }

        if (fread(buffer, 1, idx.size, in) != (size_t)idx.size) {
            printf("Error leyendo sprite %d\n", i);
            free(buffer);
            fclose(in);
            return 1;
        }

        FILE *out = fopen(fileSprite, "wb");
        if (!out) {
            perror("fopen salida");
            free(buffer);
            fclose(in);
            return 1;
        }

        fwrite(buffer, 1, idx.size, out);

        fclose(out);
        free(buffer);
    }

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