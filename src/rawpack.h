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




// Raymatte RawPack
//
// Used to bundle together assets for raymatte into a single file.
// The file is then compressed / decompressed using 
// raylibs inflate / deflate
typedef struct rmRawPack_t rmRawPack_t;


// Creates a new rawpack from data.
// The data MUST have been made through rm_raw_pack_package()
// (or through a reputable source!)
// If the data is unrecognized, NULL is returned.
rmRawPack_t * rm_raw_pack_create_from_data(
    const uint8_t * bytes,
    int byteSize
);


// Creates an empty RawPack.
rmRawPack_t * rm_raw_pack_create_empty();

// Bundles together a RawPack into a byte buffer.
// This byte buffer can then be used to create 
// a RawPack in the future.
uint8_t * rm_raw_pack_package(
    const rmRawPack_t *,
    uint32_t * size
);



// Gets an entry by name within the rawpack.
const uint8_t * rm_raw_pack_get_entry(
    const rmRawPack_t *,
    const char * name,
    int * size
);

// Adds a new entry to the rawpack.
void rm_raw_pack_add_entry(
    rmRawPack_t *,
    const char * name,
    const uint8_t * data,
    int size
);





#endif
