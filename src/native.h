#ifndef H_RAYMATTE_ENCODE_INCLUDED
#define H_RAYMATTE_ENCODE_INCLUDED

#include "../matte/src/matte_store.h"
#include "../matte/src/matte_vm.h"

#include "../raylib/src/raylib.h"



// Standard functions to encode various datatypes into 
// matteValue_t s in a regular way.
// Use the decode.h family of functions to decode.


matteValue_t native_encode_pointer(matteVM_t * vm, void * ptr);
matteValue_t native_encode_int(matteVM_t * vm, int value);
matteValue_t native_encode_image(matteVM_t * vm, const Image * img);
matteValue_t native_encode_vector2(matteVM_t * vm, const Vector2); 


Image native_decode_image(matteVM_t * vm, matteValue_t img);
Vector2 native_decode_vector2(matteVM_t * vm, matteValue_t v);


#endif
