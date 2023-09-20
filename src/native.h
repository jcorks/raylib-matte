#ifndef H_RAYMATTE_ENCODE_INCLUDED
#define H_RAYMATTE_ENCODE_INCLUDED

#include "../matte/src/matte_store.h"
#include "../matte/src/matte_vm.h"

#include "../raylib/src/raylib.h"



// Standard functions to encode various datatypes into 
// matteValue_t s in a regular way.
// Use the decode.h family of functions to decode.


// Returns whether the value is a "closed" object, which 
// is opaque to normal use.
int native_is_value_closed(matteVM_t * vm, matteValue_t val);

matteValue_t native_to_value_pointer(matteVM_t * vm, void * ptr);
matteValue_t native_to_value_int(matteVM_t * vm, int value);
matteValue_t native_to_value_boolean(matteVM_t * vm, int value);
matteValue_t native_to_value_float(matteVM_t * vm, float value);
matteValue_t native_to_value_string(matteVM_t * vm, const char * value);

matteValue_t native_to_value_image(matteVM_t * vm, Image img);
matteValue_t native_to_value_vector2(matteVM_t * vm, Vector2); 
matteValue_t native_to_value_renderTexture(matteVM_t * vm, RenderTexture img);
matteValue_t native_to_value_texture(matteVM_t * vm, Texture img);
matteValue_t native_to_value_shader(matteVM_t * vm, Shader img);


// DOES NOT check values
const char * native_from_value_string_unsafe(matteVM_t * vm, matteValue_t str);




// DOES check value and return default values with a thrown error.
Image native_from_value_image(matteVM_t * vm, matteValue_t img);
Vector2 native_from_value_vector2(matteVM_t * vm, matteValue_t v);
Color native_from_value_color(matteVM_t * vm, matteValue_t cl);
Vector3 native_from_value_vector3(matteVM_t * vm, matteValue_t cl);
Vector4 native_from_value_vector4(matteVM_t * vm, matteValue_t cl);
Camera2D native_from_value_camera2D(matteVM_t * vm, matteValue_t cam);
Camera3D native_from_value_camera3D(matteVM_t * vm, matteValue_t cam);
RenderTexture native_from_value_renderTexture(matteVM_t * vm, matteValue_t tex);
Texture native_from_value_texture(matteVM_t * vm, matteValue_t tex);
Shader native_from_value_shader(matteVM_t * vm, matteValue_t shad);
Matrix native_from_value_matrix(matteVM_t * vm, matteValue_t cl);



// Unloads a native object safely.
void native_unload(matteVM_t * vm, matteValue_t obj);


#endif
