/*
Copyright (c) 2023 Johnathan Corkery

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
void * dump_bytes(const char * filename, uint32_t * len, int terminateOnFail) {
    FILE * f = fopen(filename, "rb");
    if (!f) {
        if (terminateOnFail) {
            printf("Could not open input file %s\n", filename);
            exit(1);    
        } else {
            *len = 0;
            return NULL;
        }
    }
    char chunk[2048];
    int chunkSize;
    *len = 0;    
    while(chunkSize = (fread(chunk, 1, 2048, f))) *len += chunkSize;
    fseek(f, 0, SEEK_SET);


    void * out = malloc(*len);
    uint32_t iter = 0;
    while(chunkSize = (fread(chunk, 1, 2048, f))) {
        memcpy(((uint8_t*)out)+iter, chunk, chunkSize);
        iter += chunkSize;
    }
    fclose(f);
    return out;
}


int main() {
    uint32_t size;
    uint8_t * data = dump_bytes("raylib.mt", &size, 1);

    


    FILE * out = fopen("../raylib.mt.h", "wb");
    
    fprintf(out, "uint8_t RAYLIB_MT[%d] = {\n", (int)size+1);
    for(int i = 0; i < (int)size; ++i) {
        fprintf(out, "%d,", data[i]);
    }
    fprintf(out, "0};\n");

    
    free(data);
    data = dump_bytes("game.mt", &size, 1);

    fprintf(out, "uint8_t GAME_MT[%d] = {\n", (int)size+1);
    for(int i = 0; i < (int)size; ++i) {
        fprintf(out, "%d,", data[i]);
    }
    fprintf(out, "0};\n");


    free(data);
    data = dump_bytes("raygui.mt", &size, 1);

    fprintf(out, "uint8_t RAYGUI_MT[%d] = {\n", (int)size+1);
    for(int i = 0; i < (int)size; ++i) {
        fprintf(out, "%d,", data[i]);
    }
    fprintf(out, "0};\n");



    fclose(out);
}
