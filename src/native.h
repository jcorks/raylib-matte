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

#ifndef H_RAYMATTE_ENCODE_INCLUDED
#define H_RAYMATTE_ENCODE_INCLUDED

#include "../matte/src/matte_store.h"
#include "../matte/src/matte_vm.h"

#include "../raylib/src/raylib.h"
#include "../raylib/src/raymath.h"
#include "../raylib/src/rlgl.h"


// Standard functions to encode various datatypes into 
// matteValue_t s in a regular way.
// Use the decode.h family of functions to decode.


// Returns whether the value is a "closed" object, which 
// is opaque to normal use.
int native_is_value_closed(matteVM_t * vm, matteValue_t val);

matteValue_t native_to_value_int(matteVM_t * vm, int value);
matteValue_t native_to_value_boolean(matteVM_t * vm, int value);
matteValue_t native_to_value_float(matteVM_t * vm, float value);
matteValue_t native_to_value_double(matteVM_t * vm, double value);
matteValue_t native_to_value_string(matteVM_t * vm, const char * value);

matteValue_t native_to_value_vector2(matteVM_t * vm, Vector2 in); 
matteValue_t native_to_value_vector3(matteVM_t * vm, Vector3 in);
matteValue_t native_to_value_vector4(matteVM_t * vm, Vector4 in);
matteValue_t native_to_value_matrix(matteVM_t * vm, Matrix in);
matteValue_t native_to_value_color(matteVM_t * vm, Color in);
matteValue_t native_to_value_rectangle(matteVM_t * vm, Rectangle in);
matteValue_t native_to_value_image(matteVM_t * vm, Image in);
matteValue_t native_to_value_texture(matteVM_t * vm, Texture in);
matteValue_t native_to_value_renderTexture(matteVM_t * vm, RenderTexture in);
matteValue_t native_to_value_nPatchInfo(matteVM_t * vm, NPatchInfo in);
matteValue_t native_to_value_glyphInfo(matteVM_t * vm, GlyphInfo in);
matteValue_t native_to_value_font(matteVM_t * vm, Font in);
matteValue_t native_to_value_camera(matteVM_t * vm, Camera in);
matteValue_t native_to_value_camera2D(matteVM_t * vm, Camera2D in);
matteValue_t native_to_value_mesh(matteVM_t * vm, Mesh in);
matteValue_t native_to_value_shader(matteVM_t * vm, Shader in);
matteValue_t native_to_value_materialMap(matteVM_t * vm, MaterialMap in);
matteValue_t native_to_value_material(matteVM_t * vm, Material in);
matteValue_t native_to_value_transform(matteVM_t * vm, Transform in);
matteValue_t native_to_value_boneInfo(matteVM_t * vm, BoneInfo in);
matteValue_t native_to_value_model(matteVM_t * vm, Model in);
matteValue_t native_to_value_modelAnimation(matteVM_t * vm, ModelAnimation in);
matteValue_t native_to_value_ray(matteVM_t * vm, Ray in);
matteValue_t native_to_value_rayCollision(matteVM_t * vm, RayCollision in);
matteValue_t native_to_value_boundingBox(matteVM_t * vm, BoundingBox in);
matteValue_t native_to_value_wave(matteVM_t * vm, Wave in);
matteValue_t native_to_value_audioStream(matteVM_t * vm, AudioStream in);
matteValue_t native_to_value_sound(matteVM_t * vm, Sound in);
matteValue_t native_to_value_music(matteVM_t * vm, Music in);
matteValue_t native_to_value_vrDeviceInfo(matteVM_t * vm, VrDeviceInfo in);
matteValue_t native_to_value_vrStereoConfig(matteVM_t * vm, VrStereoConfig in); 

// DOES NOT check values
const char * native_from_value_string_unsafe(matteVM_t * vm, matteValue_t str);

// special reduced form
matteValue_t native_to_value_filePathList_reduced(matteVM_t * vm, FilePathList list);




// DOES check value and return default values with a thrown error.
Vector2 native_from_value_vector2(matteVM_t * vm, matteValue_t in);
Vector3 native_from_value_vector3(matteVM_t * vm, matteValue_t in);
Vector4 native_from_value_vector4(matteVM_t * vm, matteValue_t in);
Matrix native_from_value_matrix(matteVM_t * vm, matteValue_t in);
Color native_from_value_color(matteVM_t * vm, matteValue_t in);
Rectangle native_from_value_rectangle(matteVM_t * vm, matteValue_t in);
Image native_from_value_image(matteVM_t * vm, matteValue_t in);
Texture native_from_value_texture(matteVM_t * vm, matteValue_t in);
RenderTexture native_from_value_renderTexture(matteVM_t * vm, matteValue_t in);
NPatchInfo native_from_value_nPatchInfo(matteVM_t * vm, matteValue_t in);
GlyphInfo native_from_value_glyphInfo(matteVM_t * vm, matteValue_t in);
Font native_from_value_font(matteVM_t * vm, matteValue_t in);
Camera3D native_from_value_camera(matteVM_t * vm, matteValue_t in);
Camera2D native_from_value_camera2D(matteVM_t * vm, matteValue_t in);
Mesh native_from_value_mesh(matteVM_t * vm, matteValue_t in);
Shader native_from_value_shader(matteVM_t * vm, matteValue_t in);
MaterialMap native_from_value_materialMap(matteVM_t * vm, matteValue_t in);
Material native_from_value_material(matteVM_t * vm, matteValue_t in);
Transform native_from_value_transform(matteVM_t * vm, matteValue_t in);
BoneInfo native_from_value_boneInfo(matteVM_t * vm, matteValue_t in);
Model native_from_value_model(matteVM_t * vm, matteValue_t in);
ModelAnimation native_from_value_modelAnimation(matteVM_t * vm, matteValue_t in);
Ray native_from_value_ray(matteVM_t * vm, matteValue_t in);
RayCollision native_from_value_rayCollision(matteVM_t * vm, matteValue_t in);
BoundingBox native_from_value_boundingBox(matteVM_t * vm, matteValue_t in);
Wave native_from_value_wave(matteVM_t * vm, matteValue_t in);
AudioStream native_from_value_audioStream(matteVM_t * vm, matteValue_t in);
Sound native_from_value_sound(matteVM_t * vm, matteValue_t in);
Music native_from_value_music(matteVM_t * vm, matteValue_t in);
VrDeviceInfo native_from_value_vrDeviceInfo(matteVM_t * vm, matteValue_t in);
VrStereoConfig native_from_value_vrStereoConfig(matteVM_t * vm, matteValue_t in);

// for opaque objects, we can get an editable reference
Image * native_from_value_image_ref(matteVM_t * vm, matteValue_t img);
Texture2D * native_from_value_texture_ref(matteVM_t * vm, matteValue_t tex);
Mesh * native_from_value_mesh_ref(matteVM_t * vm, matteValue_t tex);
Model * native_from_value_model_ref(matteVM_t * vm, matteValue_t tex);
Material * native_from_value_material_ref(matteVM_t * vm, matteValue_t tex);
Wave * native_from_value_wave_ref(matteVM_t * vm, matteValue_t in);
void native_update_value_image(matteVM_t * vm, matteValue_t in);
void native_update_value_texture(matteVM_t * vm, matteValue_t in);
void native_update_value_mesh(matteVM_t * vm, matteValue_t in);
void native_update_value_material(matteVM_t * vm, matteValue_t in);
void native_update_value_model(matteVM_t * vm, matteValue_t in);
void native_update_value_wave(matteVM_t * vm, matteValue_t in);

void native_update_value_camera(matteVM_t * vm, matteValue_t v, Camera cam);
void native_update_value_vector2(matteVM_t * vm, matteValue_t v, Vector2 cam);
void native_update_value_vector3(matteVM_t * vm, matteValue_t v, Vector3 cam);
void native_update_value_rectangle(matteVM_t * vm, matteValue_t v, Rectangle r);
void native_update_value_color(matteVM_t * vm, matteValue_t v, Color c);

// Unloads a native object safely.
void native_unload(matteVM_t * vm, matteValue_t obj);


#endif
