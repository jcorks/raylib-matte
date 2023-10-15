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

#ifndef H_RAYMATTE_RAWPACK_INCLUDED
#define H_RAYMATTE_RAWPACK_INCLUDED

#include "rawpack.h"
#include "../matte/src/matte_table.h"
#include "../matte/src/matte_array.h"
#include "../matte/src/matte_string.h"
#include <stdlib.h>
#include <string.h>
#include "../raylib/src/raylib.h"

typedef struct rmRawPack_t {
    matteTable_t * entries;
} rmRawPack_t;


typedef struct {
    uint8_t * data;
    int       size;
} rmRawPack_Entry_t;



static void destroy_entry(rmRawPack_Entry_t * entry) {
    free(entry->data);
    free(entry);
}

#define PACK_TAG "RAYMATTE_RAWPACK_V1"





static void pack_int(matteArray_t * queue, int val) {
    matte_array_push_n(
        queue,
        &val,
        sizeof(int)
    );
}

static void pack_string(matteArray_t * queue, char * str) {
    int len = strlen(str);
    pack_int(queue, len);
    matte_array_push_n(
        queue,
        str,
        len+1
    );
}

static void pack_n(matteArray_t * queue, const uint8_t * buffer, int size) {
    pack_int(queue, size);
    matte_array_push_n(
        queue,
        buffer,
        size
    );
}





static int unpack_int(matteArray_t * data, int * iter) {
    if (*iter + sizeof(int) >= matte_array_get_size(data)) {
        return 0;
    }
    int out = *((int*) (((uint8_t*)matte_array_get_data(data))+*iter));
    *iter += sizeof(int);
    return out;
}


static char * unpack_string(matteArray_t * data, int * iter) {
    int len = unpack_int(data, iter);
    if (len == 0) return "";
    
    char * out = ((char*)matte_array_get_data(data)) + *iter;
    
    if (len != strlen(out)) {
        return "";
    }
    *iter += len+1;
    
    return out;
}


static uint8_t * unpack_n(matteArray_t * data, int * iter, int * size) {
    *size = unpack_int(data, iter);
    if (*size == 0)
        return NULL;
    uint8_t * out = ((uint8_t*)matte_array_get_data(data)) + *iter;
    *iter += *size;
    return out;
}




rmRawPack_t * rm_raw_pack_create_from_data(
    const uint8_t * bytes,
    int byteSize
) {
    int size;
    uint8_t * dataUnsafe = DecompressData(bytes, byteSize, &size);
    if (!dataUnsafe || !size)
        return NULL;
    
    
    
    
    uint8_t * data = MemAlloc(size+1);
    data[size] = 0;
    memcpy(data, dataUnsafe, size);
    MemFree(dataUnsafe);
        
    matteArray_t arr = MATTE_ARRAY_CAST(data, uint8_t, size);        
        
    int iter = 0;
    char * tag = unpack_string(&arr, &iter);
    
    if (strcmp(tag, PACK_TAG)) {
        goto L_FAIL;
    }
    
    int nEntries = unpack_int(&arr, &iter);
    if (nEntries == 0) goto L_FAIL;
    
    
    rmRawPack_t * out = calloc(1, sizeof(rmRawPack_t));
    out->entries = matte_table_create_hash_c_string();
    
    int i;
    for(i = 0; i < nEntries; ++i) {
        rmRawPack_Entry_t * entry = calloc(1, sizeof(rmRawPack_Entry_t));
        char * name = unpack_string(&arr, &iter);
        entry->data = unpack_n(&arr, &iter, &entry->size);
        matte_table_insert(
            out->entries,
            name,
            entry
        );
    }
    
    return out;    
    
  L_FAIL:
    MemFree(data);
    return NULL;    
}


// Bundles together a RawPack into a byte buffer.
// This byte buffer can then be used to create 
// a RawPack in the future.
uint8_t * rm_raw_pack_package(
    const rmRawPack_t * rm,
    int * size
) {
    matteArray_t * queue = matte_array_create(1);
    pack_string(queue, PACK_TAG);
    pack_int(queue, matte_table_get_size(rm->entries));

    matteTableIter_t * iter = matte_table_iter_create();
    for(
        matte_table_iter_start(iter, rm->entries);
        !matte_table_iter_is_end(iter);
        matte_table_iter_proceed(iter)
    ) {
        rmRawPack_Entry_t * entry = matte_table_iter_get_value(iter);
        pack_string(queue, (char*)matte_table_iter_get_key(iter));
        pack_n(queue, entry->data, entry->size);
    }
    
    
    
    uint8_t * out = CompressData(
        matte_array_get_data(queue),
        matte_array_get_size(queue),
        size 
    );
    
    matte_array_destroy(queue);
    matte_table_iter_destroy(iter);
    
    return out;
}

rmRawPack_t * rm_raw_pack_create_empty() {
    rmRawPack_t * out = calloc(1, sizeof(rmRawPack_t));
    out->entries = matte_table_create_hash_c_string();
        
    return out;
}








// Gets an entry by name within the rawpack.
const uint8_t * rm_raw_pack_get_entry(
    const rmRawPack_t * rm,
    const matteString_t * name,
    int * size
) {
    rmRawPack_Entry_t * entry = matte_table_find(rm->entries, name);
    if (entry) {
        *size = entry->size;
        return entry->data;
    }
    
    *size = 0;
    return NULL;
}

// Adds a new entry to the rawpack.
void rm_raw_pack_add_entry(
    rmRawPack_t * rm,
    const char * name,
    const uint8_t * data,
    int size
) {
    rmRawPack_Entry_t * entry = calloc(1, sizeof(rmRawPack_Entry_t));
    entry->size = size;
    entry->data = malloc(size);
    memcpy(entry->data, data, size);
    
    
    rmRawPack_Entry_t * old = matte_table_find(rm->entries, name);
    if (old) {
        destroy_entry(old);
    }
    
    matte_table_insert(
        rm->entries,
        name,
        entry
    );
}





#endif
