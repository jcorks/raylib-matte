#include "native.h"
#include "defines.h"
#include <stdlib.h>
#include "../matte/src/matte_store.h"
#include "../matte/src/matte_string.h"
#include "../matte/src/matte_array.h"
#include <string.h>


#define MAX_MATERIAL_MAPS 12

enum {
    //// Structs that have special getters
    RAYMATTE_NATIVE_TYPE__IMAGE = 866,
    RAYMATTE_NATIVE_TYPE__FONT,
    RAYMATTE_NATIVE_TYPE__MESH,
    RAYMATTE_NATIVE_TYPE__MODEL,
    RAYMATTE_NATIVE_TYPE__MODEL_ANIMATION,
    RAYMATTE_NATIVE_TYPE__WAVE,
    RAYMATTE_NATIVE_TYPE__MATRIX,
    
    //// Structs that have unimplemented 
    //// members and need to have some help
    RAYMATTE_NATIVE_TYPE__TEXTURE,
    RAYMATTE_NATIVE_TYPE__RENDER_TEXTURE,
    RAYMATTE_NATIVE_TYPE__SHADER,
    RAYMATTE_NATIVE_TYPE__AUDIO_STREAM,
    RAYMATTE_NATIVE_TYPE__MUSIC,
    RAYMATTE_NATIVE_TYPE__MATERIAL,
    RAYMATTE_NATIVE_TYPE__BONEINFO,
};


typedef struct {
    int typeTag;
    void * data;
} NativeEncodeData_t;

static void native_to_value_finalizer(void * objectUserdata, void * functionUserdata) {
    NativeEncodeData_t * m = objectUserdata;
    free(m->data);
    free(m);
}


int native_is_value_closed(matteVM_t * vm, matteValue_t val) {
    matteStore_t * store = matte_vm_get_store(vm);
    if (val.binID != MATTE_VALUE_TYPE_OBJECT) {
        return FALSE;
    }
    
    NativeEncodeData_t * object = matte_value_object_get_userdata(store, val);
    if (object == NULL || object->typeTag == 0) {
        return FALSE;
    }    
    
    return TRUE;
}











matteValue_t native_to_value_int(matteVM_t * vm, int value) {
    matteValue_t v;
    v.binID = MATTE_VALUE_TYPE_NUMBER;
    v.value.number = value;
    return v;
}

matteValue_t native_to_value_boolean(matteVM_t * vm, int value) {
    matteValue_t v;
    v.binID = MATTE_VALUE_TYPE_BOOLEAN;
    v.value.boolean = value;
    return v;
}

matteValue_t native_to_value_float(matteVM_t * vm, float value) {
    matteValue_t v;
    v.binID = MATTE_VALUE_TYPE_NUMBER;
    v.value.number = value;
    return v;
}

matteValue_t native_to_value_double(matteVM_t * vm, double value) {
    matteValue_t v;
    v.binID = MATTE_VALUE_TYPE_NUMBER;
    v.value.number = value;
    return v;
}

matteValue_t native_to_value_string(matteVM_t * vm, const char * value) {
    matteStore_t * store = matte_vm_get_store(vm);
    matteValue_t v = matte_store_new_value(store);
    matte_value_into_string(store, &v, MATTE_VM_STR_CAST(vm, value));
    return v;
}




#define INIT_OUT()\
    matteStore_t * store = matte_vm_get_store(vm);\
    matteValue_t out = matte_store_new_value(store);\
    matte_value_into_new_object_ref(store, &out);\
    
#define NATIVIZE(__TYPE__, __TAG__)\
    {\
    NativeEncodeData_t * fd = calloc(1, sizeof(NativeEncodeData_t));\
    fd->data = calloc(1, sizeof(__TYPE__));\
    fd->typeTag = __TAG__;\
    *((__TYPE__*)fd->data) = in;    \
    matte_value_object_set_userdata(store, out, fd);\
    matte_value_object_set_native_finalizer(store, out, native_to_value_finalizer, NULL);\
    }

#define NEW_KEY(__name__, __type__)\
    matte_value_object_set_key_string(store, out, MATTE_VM_STR_CAST(vm, #__name__), __type__(vm, in.__name__));


matteValue_t native_to_value_vector2(matteVM_t * vm, Vector2 in) {
    INIT_OUT();
    NEW_KEY(x, native_to_value_float);
    NEW_KEY(y, native_to_value_float);
    return out;
}
matteValue_t native_to_value_vector3(matteVM_t * vm, Vector3 in) {
    INIT_OUT();
    NEW_KEY(x, native_to_value_float);
    NEW_KEY(y, native_to_value_float);
    NEW_KEY(z, native_to_value_float);
    return out;
}
matteValue_t native_to_value_vector4(matteVM_t * vm, Vector4 in) {
    INIT_OUT();
    NEW_KEY(x, native_to_value_float);
    NEW_KEY(y, native_to_value_float);
    NEW_KEY(z, native_to_value_float);
    NEW_KEY(w, native_to_value_float);
    return out;
}
matteValue_t native_to_value_matrix(matteVM_t * vm, Matrix in) {
    INIT_OUT();
    NATIVIZE(Matrix, RAYMATTE_NATIVE_TYPE__MATRIX);
    return out;
}
matteValue_t native_to_value_color(matteVM_t * vm, Color in) {
    INIT_OUT();
    NEW_KEY(r, native_to_value_int);
    NEW_KEY(g, native_to_value_int);
    NEW_KEY(b, native_to_value_int);
    NEW_KEY(a, native_to_value_int);
    return out;
}
matteValue_t native_to_value_rectangle(matteVM_t * vm, Rectangle in) {
    INIT_OUT();
    NEW_KEY(x, native_to_value_float);
    NEW_KEY(y, native_to_value_float);
    NEW_KEY(width, native_to_value_float);
    NEW_KEY(height, native_to_value_float);
    return out;
}
matteValue_t native_to_value_image(matteVM_t * vm, Image in) {
    INIT_OUT();
    NATIVIZE(Image, RAYMATTE_NATIVE_TYPE__IMAGE);
    NEW_KEY(width, native_to_value_int);
    NEW_KEY(height, native_to_value_int);
    NEW_KEY(mipmaps, native_to_value_int);
    NEW_KEY(format, native_to_value_int);
    return out;
}
matteValue_t native_to_value_texture(matteVM_t * vm, Texture in) {
    INIT_OUT();
    NATIVIZE(Texture, RAYMATTE_NATIVE_TYPE__TEXTURE);
    NEW_KEY(width, native_to_value_int);
    NEW_KEY(height, native_to_value_int);
    NEW_KEY(mipmaps, native_to_value_int);
    NEW_KEY(format, native_to_value_int);
    return out;
}
matteValue_t native_to_value_renderTexture(matteVM_t * vm, RenderTexture in) {
    INIT_OUT();
    NATIVIZE(RenderTexture, RAYMATTE_NATIVE_TYPE__RENDER_TEXTURE);
    NEW_KEY(texture, native_to_value_texture);
    NEW_KEY(depth, native_to_value_texture);
    return out;
}
matteValue_t native_to_value_nPatchInfo(matteVM_t * vm, NPatchInfo in) {
    INIT_OUT();
    NEW_KEY(source, native_to_value_rectangle);
    NEW_KEY(left, native_to_value_int);
    NEW_KEY(top, native_to_value_int);
    NEW_KEY(right, native_to_value_int);
    NEW_KEY(bottom, native_to_value_int);
    return out;
}
matteValue_t native_to_value_glyphInfo(matteVM_t * vm, GlyphInfo in) {
    INIT_OUT();
    NEW_KEY(image, native_to_value_image);
    NEW_KEY(value, native_to_value_int);
    NEW_KEY(offsetX, native_to_value_int);
    NEW_KEY(offsetY, native_to_value_int);
    NEW_KEY(advanceX, native_to_value_int);
    return out;
}
matteValue_t native_to_value_font(matteVM_t * vm, Font in) {
    INIT_OUT();
    NATIVIZE(Font, RAYMATTE_NATIVE_TYPE__FONT);
    NEW_KEY(glyphCount, native_to_value_int);
    NEW_KEY(baseSize, native_to_value_int);
    NEW_KEY(glyphPadding, native_to_value_int);
    NEW_KEY(texture, native_to_value_texture);
    return out;
}
matteValue_t native_to_value_camera(matteVM_t * vm, Camera in) {
    INIT_OUT();
    NEW_KEY(position, native_to_value_vector3);
    NEW_KEY(target, native_to_value_vector3);
    NEW_KEY(up, native_to_value_vector3);
    NEW_KEY(fovy, native_to_value_float);
    NEW_KEY(projection, native_to_value_int);
    return out;
}
matteValue_t native_to_value_camera2D(matteVM_t * vm, Camera2D in) {
    INIT_OUT();
    NEW_KEY(offset, native_to_value_vector2);
    NEW_KEY(target, native_to_value_vector2);
    NEW_KEY(rotation, native_to_value_float);
    NEW_KEY(zoom, native_to_value_float);
    return out;
}
matteValue_t native_to_value_mesh(matteVM_t * vm, Mesh in) {
    INIT_OUT();
    NATIVIZE(Mesh, RAYMATTE_NATIVE_TYPE__MESH);
    NEW_KEY(vertexCount, native_to_value_int);
    NEW_KEY(triangleCount, native_to_value_int);
    return out;
}
matteValue_t native_to_value_shader(matteVM_t * vm, Shader in) {
    INIT_OUT();
    NATIVIZE(Shader, RAYMATTE_NATIVE_TYPE__SHADER);
    return out;
}
matteValue_t native_to_value_materialMap(matteVM_t * vm, MaterialMap in) {
    INIT_OUT();
    NEW_KEY(texture, native_to_value_texture);
    NEW_KEY(color, native_to_value_color);
    NEW_KEY(value, native_to_value_float);
    return out;
}
matteValue_t native_to_value_material(matteVM_t * vm, Material in_src) {
    typedef struct {
        Shader shader;
        MaterialMap maps0;
        MaterialMap maps1;    
        MaterialMap maps2;    
        MaterialMap maps3;    

        MaterialMap maps4;    
        MaterialMap maps5;    
        MaterialMap maps6;    
        MaterialMap maps7;    

        MaterialMap maps8;    
        MaterialMap maps9;    
        MaterialMap maps10;    
        MaterialMap maps11;
        
        
        float params0;    
        float params1;    
        float params2;    
        float params3;    
    } MaterialExt;
    MaterialExt in;
    in.shader = in_src.shader;
    memcpy(&in.maps0, in_src.maps, sizeof(MaterialMap)*MAX_MATERIAL_MAPS);
    memcpy(&in.params0, in_src.params, sizeof(float)*4);
    
    
    INIT_OUT();

    {
        NativeEncodeData_t * fd = calloc(1, sizeof(NativeEncodeData_t));
        fd->data = calloc(1, sizeof(Material));
        fd->typeTag = RAYMATTE_NATIVE_TYPE__MATERIAL;
        *((Material*)fd->data) = in_src;    
        matte_value_object_set_userdata(store, out, fd);
        matte_value_object_set_native_finalizer(store, out, native_to_value_finalizer, NULL);
    }



    NEW_KEY(shader, native_to_value_shader);
    NEW_KEY(maps0, native_to_value_materialMap);
    NEW_KEY(maps1, native_to_value_materialMap);
    NEW_KEY(maps2, native_to_value_materialMap);
    NEW_KEY(maps3, native_to_value_materialMap);

    NEW_KEY(maps4, native_to_value_materialMap);
    NEW_KEY(maps5, native_to_value_materialMap);
    NEW_KEY(maps6, native_to_value_materialMap);
    NEW_KEY(maps7, native_to_value_materialMap);

    NEW_KEY(maps8, native_to_value_materialMap);
    NEW_KEY(maps9, native_to_value_materialMap);
    NEW_KEY(maps10, native_to_value_materialMap);
    NEW_KEY(maps11, native_to_value_materialMap);

    NEW_KEY(params0, native_to_value_float);
    NEW_KEY(params1, native_to_value_float);
    NEW_KEY(params2, native_to_value_float);
    NEW_KEY(params3, native_to_value_float);


    return out;        
}
matteValue_t native_to_value_transform(matteVM_t * vm, Transform in) {
    INIT_OUT();
    NEW_KEY(translation, native_to_value_vector3);
    NEW_KEY(rotation, native_to_value_vector4);
    NEW_KEY(scale, native_to_value_vector3);
    return out;
}
matteValue_t native_to_value_boneInfo(matteVM_t * vm, BoneInfo in) {
    INIT_OUT();
    NEW_KEY(parent, native_to_value_int);
    
    char * str = MemAlloc(33);
    memset(str, 0, 33);
    memcpy(str, in.name, 32);
    matte_value_object_set_key_string(store, out, MATTE_VM_STR_CAST(vm, "name"), native_to_value_string(vm, str));
    return out;    
}
matteValue_t native_to_value_model(matteVM_t * vm, Model in) {
    INIT_OUT();
    NATIVIZE(Model, RAYMATTE_NATIVE_TYPE__MODEL);
    NEW_KEY(transform, native_to_value_matrix);
    NEW_KEY(meshCount, native_to_value_int);
    NEW_KEY(materialCount, native_to_value_int);
    NEW_KEY(boneCount, native_to_value_int);
    return out;
}
matteValue_t native_to_value_modelAnimation(matteVM_t * vm, ModelAnimation in) {
    INIT_OUT();
    NATIVIZE(ModelAnimation, RAYMATTE_NATIVE_TYPE__MODEL_ANIMATION);
    NEW_KEY(boneCount, native_to_value_int);
    NEW_KEY(frameCount, native_to_value_int);
    char * str = MemAlloc(33);
    memset(str, 0, 33);
    memcpy(str, in.name, 32);
    matte_value_object_set_key_string(store, out, MATTE_VM_STR_CAST(vm, "name"), native_to_value_string(vm, str));
    return out;    
}
matteValue_t native_to_value_ray(matteVM_t * vm, Ray in) {
    INIT_OUT();
    NEW_KEY(direction, native_to_value_vector3);
    NEW_KEY(position, native_to_value_vector3);
    return out;
}
matteValue_t native_to_value_rayCollision(matteVM_t * vm, RayCollision in) {
    INIT_OUT();
    NEW_KEY(hit, native_to_value_int);
    NEW_KEY(distance, native_to_value_float);
    NEW_KEY(point, native_to_value_vector3);
    NEW_KEY(normal, native_to_value_vector3);
    return out;

}

matteValue_t native_to_value_boundingBox(matteVM_t * vm, BoundingBox in) {
    INIT_OUT();
    NEW_KEY(min, native_to_value_vector3);
    NEW_KEY(max, native_to_value_vector3);
    return out;
}

matteValue_t native_to_value_wave(matteVM_t * vm, Wave in) {
    INIT_OUT();
    NATIVIZE(Wave, RAYMATTE_NATIVE_TYPE__WAVE);
    NEW_KEY(frameCount, native_to_value_int);
    NEW_KEY(sampleRate, native_to_value_int);
    NEW_KEY(sampleSize, native_to_value_int);
    NEW_KEY(channels, native_to_value_int);
    return out;
}
matteValue_t native_to_value_audioStream(matteVM_t * vm, AudioStream in) {
    INIT_OUT();
    NATIVIZE(AudioStream, RAYMATTE_NATIVE_TYPE__AUDIO_STREAM);
    NEW_KEY(sampleRate, native_to_value_int);
    NEW_KEY(sampleSize, native_to_value_int);
    NEW_KEY(channels, native_to_value_int);
    return out;
}
matteValue_t native_to_value_sound(matteVM_t * vm, Sound in) {
    INIT_OUT();
    NEW_KEY(frameCount, native_to_value_int);
    NEW_KEY(stream, native_to_value_audioStream);
    return out;
}
matteValue_t native_to_value_music(matteVM_t * vm, Music in) {
    INIT_OUT();
    NATIVIZE(Music, RAYMATTE_NATIVE_TYPE__MUSIC);
    NEW_KEY(frameCount, native_to_value_int);
    NEW_KEY(stream, native_to_value_audioStream);
    NEW_KEY(looping, native_to_value_int);
    return out;

}














const char * native_from_value_string_unsafe(matteVM_t * vm, matteValue_t str) {   
    return matte_string_get_c_str(matte_value_string_get_string_unsafe(matte_vm_get_store(vm), str));
}
    
    
matteValue_t native_to_value_filePathList_reduced(matteVM_t * vm, FilePathList list) {
    matteStore_t * store = matte_vm_get_store(vm);    

    matteValue_t capacity = native_to_value_int(vm, list.capacity);

    matteValue_t * vals = calloc(list.count, sizeof(matteValue_t));
    int i;
    for(i = 0; i < list.count; ++i) {
        vals[i] = native_to_value_string(vm, list.paths[i]);
    }

    matteValue_t paths = matte_store_new_value(store);
    matteArray_t pathsArr = MATTE_ARRAY_CAST(vals, matteValue_t, list.count);
    matte_value_into_new_object_array_ref(
        store,
        &paths, 
        &pathsArr
    );
    free(vals);


    matteValue_t v = matte_store_new_value(store);
    matte_value_into_new_object_ref(store, &v);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "capacity"), capacity);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "paths"), paths);

    return v;    
}



#define INIT_FROM(__TYPE__)\
    matteStore_t * store = matte_vm_get_store(vm);\
    __TYPE__ out = {};\
    if (in.binID != MATTE_VALUE_TYPE_OBJECT) {\
        matte_vm_raise_error_cstring(vm, "Could not decode __TYPE__: value is not an Object.");\
        return out;\
    }\

#define UPDATE_KEY(__name__, __type__)\
    matte_value_object_set_key_string(store, in, MATTE_VM_STR_CAST(vm, #__name__), __type__(vm, object->__name__));

#define RETRIEVE_NATIVE_OBJECT_PTR(__TYPE__,__TAG__)\
    matteStore_t * store = matte_vm_get_store(vm);\
    if (in.binID != MATTE_VALUE_TYPE_OBJECT) {\
        matte_vm_raise_error_cstring(vm, "Could not decode __TYPE__: value is not an Object.");\
        return NULL;\
    }\
    NativeEncodeData_t * objectSrc = matte_value_object_get_userdata(store, in);\
    if (objectSrc == NULL || objectSrc->typeTag != __TAG__) {\
        matte_vm_raise_error_cstring(vm, "Could not decode __TYPE__: value is not an __TYPE__.");\
        return NULL;\
    }\
    __TYPE__ * object = (__TYPE__*)objectSrc->data;
    
    
#define RETRIEVE_NATIVE_OBJECT(__TYPE__,__TAG__)\
    matteStore_t * store = matte_vm_get_store(vm);\
    if (in.binID != MATTE_VALUE_TYPE_OBJECT) {\
        matte_vm_raise_error_cstring(vm, "Could not decode __TYPE__: value is not an Object.");\
        return;\
    }\
    NativeEncodeData_t * objectSrc = matte_value_object_get_userdata(store, in);\
    if (objectSrc == NULL || objectSrc->typeTag != __TAG__) {\
        matte_vm_raise_error_cstring(vm, "Could not decode __TYPE__: value is not an __TYPE__.");\
        return;\
    }\
    __TYPE__ * object = (__TYPE__*)objectSrc->data;    


#define RETRIEVE_NATIVE(__TYPE__,__TAG__)\
    matteStore_t * store = matte_vm_get_store(vm);\
    if (in.binID != MATTE_VALUE_TYPE_OBJECT) {\
        matte_vm_raise_error_cstring(vm, "Could not decode __TYPE__: value is not an Object.");\
        __TYPE__ dout = {};\
        return dout;\
    }\
    NativeEncodeData_t * object = matte_value_object_get_userdata(store, in);\
    if (object == NULL || object->typeTag != __TAG__) {\
        matte_vm_raise_error_cstring(vm, "Could not decode __TYPE__: value is not an __TYPE__.");\
        __TYPE__ dout = {};\
        return dout;\
    }\
    return *((__TYPE__*)object->data);
    
    
#define RETRIEVE_NATIVE_PRELUDE(__TYPE__,__TAG__)\
    matteStore_t * store = matte_vm_get_store(vm);\
    if (in.binID != MATTE_VALUE_TYPE_OBJECT) {\
        matte_vm_raise_error_cstring(vm, "Could not decode __TYPE__: value is not an Object.");\
        __TYPE__ dout = {};\
        return dout;\
    }\
    NativeEncodeData_t * object = matte_value_object_get_userdata(store, in);\
    if (object == NULL || object->typeTag != __TAG__) {\
        matte_vm_raise_error_cstring(vm, "Could not decode __TYPE__: value is not an __TYPE__.");\
        __TYPE__ dout = {};\
        return dout;\
    }\
    __TYPE__ * out = (__TYPE__*)object->data;

#define UPDATE_PRELUDE_KEY(__NAME__, __TYPE__)\
    out->__NAME__ = __TYPE__(vm, matte_value_object_access_string(store, in, MATTE_VM_STR_CAST(vm, #__NAME__)));

#define READ_NUMBER(__NAME__)\
    out.__NAME__ = matte_value_as_number(store, matte_value_object_access_string(store, in, MATTE_VM_STR_CAST(vm, #__NAME__)));
    
#define READ_KEY(__NAME__, __TYPE__)\
    out.__NAME__ = __TYPE__(vm, matte_value_object_access_string(store, in, MATTE_VM_STR_CAST(vm, #__NAME__)));





Vector2 native_from_value_vector2(matteVM_t * vm, matteValue_t in) {
    INIT_FROM(Vector2);
    READ_NUMBER(x);
    READ_NUMBER(y);
    return out;
}
Vector3 native_from_value_vector3(matteVM_t * vm, matteValue_t in) {
    INIT_FROM(Vector3);
    READ_NUMBER(x);
    READ_NUMBER(y);
    READ_NUMBER(z);
    return out;

}
Vector4 native_from_value_vector4(matteVM_t * vm, matteValue_t in) {
    INIT_FROM(Vector4);
    READ_NUMBER(x);
    READ_NUMBER(y);
    READ_NUMBER(z);
    READ_NUMBER(w);
    return out;
}
Matrix native_from_value_matrix(matteVM_t * vm, matteValue_t in) {
    RETRIEVE_NATIVE(Matrix, RAYMATTE_NATIVE_TYPE__MATRIX);
}
Color native_from_value_color(matteVM_t * vm, matteValue_t in) {
    INIT_FROM(Color);
    READ_NUMBER(r);
    READ_NUMBER(g);
    READ_NUMBER(b);
    READ_NUMBER(a);
    return out;
}

Rectangle native_from_value_rectangle(matteVM_t * vm, matteValue_t in) {
    INIT_FROM(Rectangle);
    READ_NUMBER(x);
    READ_NUMBER(y);
    READ_NUMBER(width);
    READ_NUMBER(height);
    return out;
}
Image native_from_value_image(matteVM_t * vm, matteValue_t in) {
    RETRIEVE_NATIVE(Image, RAYMATTE_NATIVE_TYPE__IMAGE);
}
Texture native_from_value_texture(matteVM_t * vm, matteValue_t in) {
    RETRIEVE_NATIVE(Texture, RAYMATTE_NATIVE_TYPE__TEXTURE);
}
RenderTexture native_from_value_renderTexture(matteVM_t * vm, matteValue_t in) {
    RETRIEVE_NATIVE(RenderTexture, RAYMATTE_NATIVE_TYPE__RENDER_TEXTURE);
}
NPatchInfo native_from_value_nPatchInfo(matteVM_t * vm, matteValue_t in) {
    INIT_FROM(NPatchInfo);
    READ_NUMBER(top);
    READ_NUMBER(left);
    READ_NUMBER(bottom);
    READ_NUMBER(right);
    READ_KEY(source, native_from_value_rectangle);
    return out;
}
GlyphInfo native_from_value_glyphInfo(matteVM_t * vm, matteValue_t in) {
    INIT_FROM(GlyphInfo);
    READ_NUMBER(value);
    READ_NUMBER(offsetX);
    READ_NUMBER(offsetY);
    READ_NUMBER(advanceX);
    READ_KEY(image, native_from_value_image);
    return out;

}
Font native_from_value_font(matteVM_t * vm, matteValue_t in) {
    RETRIEVE_NATIVE(Font, RAYMATTE_NATIVE_TYPE__FONT);
}
Camera3D native_from_value_camera(matteVM_t * vm, matteValue_t in) {
    INIT_FROM(Camera);
    READ_NUMBER(fovy);
    READ_NUMBER(projection);
    READ_KEY(position, native_from_value_vector3);
    READ_KEY(target, native_from_value_vector3);
    READ_KEY(up, native_from_value_vector3);
    return out;
}
Camera2D native_from_value_camera2D(matteVM_t * vm, matteValue_t in) {
    INIT_FROM(Camera2D);
    READ_NUMBER(rotation);
    READ_NUMBER(zoom);
    READ_KEY(offset, native_from_value_vector2);
    READ_KEY(target, native_from_value_vector2);
    return out;

}
Mesh native_from_value_mesh(matteVM_t * vm, matteValue_t in) {
    RETRIEVE_NATIVE(Mesh, RAYMATTE_NATIVE_TYPE__MESH);
}
Shader native_from_value_shader(matteVM_t * vm, matteValue_t in) {
    RETRIEVE_NATIVE(Shader, RAYMATTE_NATIVE_TYPE__SHADER);    
}
MaterialMap native_from_value_materialMap(matteVM_t * vm, matteValue_t in) {
    INIT_FROM(MaterialMap);
    READ_KEY(texture, native_from_value_texture);
    READ_KEY(color, native_from_value_color);
    READ_NUMBER(value);
    return out;
}
Material native_from_value_material(matteVM_t * vm, matteValue_t in) {
    RETRIEVE_NATIVE(Material, RAYMATTE_NATIVE_TYPE__MATERIAL);
}
Transform native_from_value_transform(matteVM_t * vm, matteValue_t in) {
    INIT_FROM(Transform);
    READ_KEY(translation, native_from_value_vector3);
    READ_KEY(rotation, native_from_value_vector4);
    READ_KEY(scale, native_from_value_vector3);
    return out;
}

BoneInfo native_from_value_boneInfo(matteVM_t * vm, matteValue_t in) {
    RETRIEVE_NATIVE(BoneInfo, RAYMATTE_NATIVE_TYPE__BONEINFO);
}
Model native_from_value_model(matteVM_t * vm, matteValue_t in) {
    //RETRIEVE_NATIVE(Model, RAYMATTE_NATIVE_TYPE__MODEL);
    RETRIEVE_NATIVE_PRELUDE(Model, RAYMATTE_NATIVE_TYPE__MODEL);
    UPDATE_PRELUDE_KEY(transform, native_from_value_matrix);
    return *out;
}
ModelAnimation native_from_value_modelAnimation(matteVM_t * vm, matteValue_t in) {
    RETRIEVE_NATIVE(ModelAnimation, RAYMATTE_NATIVE_TYPE__MODEL_ANIMATION);
}
Ray native_from_value_ray(matteVM_t * vm, matteValue_t in) {
    INIT_FROM(Ray);
    READ_KEY(position, native_from_value_vector3);
    READ_KEY(direction, native_from_value_vector3);
    return out;
}
RayCollision native_from_value_rayCollision(matteVM_t * vm, matteValue_t in) {
    INIT_FROM(RayCollision);
    READ_KEY(point, native_from_value_vector3);
    READ_KEY(normal, native_from_value_vector3);
    READ_NUMBER(hit);
    READ_NUMBER(distance);
    return out;
    
}
BoundingBox native_from_value_boundingBox(matteVM_t * vm, matteValue_t in) {
    INIT_FROM(BoundingBox);
    READ_KEY(min, native_from_value_vector3);
    READ_KEY(max, native_from_value_vector3);
    return out;
}
Wave native_from_value_wave(matteVM_t * vm, matteValue_t in) {
    RETRIEVE_NATIVE(Wave, RAYMATTE_NATIVE_TYPE__WAVE);
}
AudioStream native_from_value_audioStream(matteVM_t * vm, matteValue_t in) {
    RETRIEVE_NATIVE(AudioStream, RAYMATTE_NATIVE_TYPE__AUDIO_STREAM);
}
Sound native_from_value_sound(matteVM_t * vm, matteValue_t in) {
    INIT_FROM(Sound);
    READ_KEY(stream, native_from_value_audioStream);
    READ_NUMBER(frameCount);
    return out;
}
Music native_from_value_music(matteVM_t * vm, matteValue_t in) {
    RETRIEVE_NATIVE(Music, RAYMATTE_NATIVE_TYPE__MUSIC);
}







void native_update_value_camera(matteVM_t * vm, matteValue_t v, Camera cam) {
    matteStore_t * store = matte_vm_get_store(vm);    


    matteValue_t position   = native_to_value_vector3(vm, cam.position);
    matteValue_t target     = native_to_value_vector3(vm, cam.target);
    matteValue_t up         = native_to_value_vector3(vm, cam.up);
    matteValue_t fovy       = native_to_value_float(vm, cam.fovy);
    matteValue_t projection = native_to_value_float(vm, cam.projection);


    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "position"), position);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "target"), target);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "up"), up);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "fovy"), fovy);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "projection"), projection);
}



void native_update_value_vector2(matteVM_t * vm, matteValue_t v, Vector2 vec) {
    matteStore_t * store = matte_vm_get_store(vm);    


    matteValue_t x   = native_to_value_float(vm, vec.x);
    matteValue_t y   = native_to_value_float(vm, vec.y);


    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "x"), x);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "y"), y);
}

void native_update_value_vector3(matteVM_t * vm, matteValue_t v, Vector3 vec) {
    matteStore_t * store = matte_vm_get_store(vm);    


    matteValue_t x   = native_to_value_float(vm, vec.x);
    matteValue_t y   = native_to_value_float(vm, vec.y);
    matteValue_t z   = native_to_value_float(vm, vec.z);


    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "x"), x);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "y"), y);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "z"), z);
}





void native_unload(matteVM_t * vm, matteValue_t obj) {
    matteStore_t * store = matte_vm_get_store(vm);    

    if (obj.binID != MATTE_VALUE_TYPE_OBJECT) {
        return;
    }
    
    NativeEncodeData_t * object = matte_value_object_get_userdata(store, obj);
    if (object == NULL) {
        return;
    }
    
    free(object->data);
    object->typeTag = 0;
    object->data = NULL; // free() ok!
}

Image * native_from_value_image_ref(matteVM_t * vm, matteValue_t in) {
    RETRIEVE_NATIVE_OBJECT_PTR(Image, RAYMATTE_NATIVE_TYPE__IMAGE);
    return object;
}   

void native_update_value_image(matteVM_t * vm, matteValue_t in) {
    RETRIEVE_NATIVE_OBJECT(Image, RAYMATTE_NATIVE_TYPE__IMAGE);
    UPDATE_KEY(width, native_to_value_int);
    UPDATE_KEY(height, native_to_value_int);
    UPDATE_KEY(mipmaps, native_to_value_int);
    UPDATE_KEY(format, native_to_value_int);
}


Texture * native_from_value_texture_ref(matteVM_t * vm, matteValue_t in) {
    RETRIEVE_NATIVE_OBJECT_PTR(Texture, RAYMATTE_NATIVE_TYPE__TEXTURE);
    return object;
}   

void native_update_value_texture(matteVM_t * vm, matteValue_t in) {
    RETRIEVE_NATIVE_OBJECT(Texture, RAYMATTE_NATIVE_TYPE__TEXTURE);
    UPDATE_KEY(width, native_to_value_int);
    UPDATE_KEY(height, native_to_value_int);
    UPDATE_KEY(mipmaps, native_to_value_int);
    UPDATE_KEY(format, native_to_value_int);
} 



Mesh * native_from_value_mesh_ref(matteVM_t * vm, matteValue_t in) {
    RETRIEVE_NATIVE_OBJECT_PTR(Mesh, RAYMATTE_NATIVE_TYPE__MESH);
    return object;
}   

void native_update_value_mesh(matteVM_t * vm, matteValue_t in) {
    RETRIEVE_NATIVE_OBJECT(Mesh, RAYMATTE_NATIVE_TYPE__MESH);
    UPDATE_KEY(vertexCount, native_to_value_int);
    UPDATE_KEY(triangleCount, native_to_value_int);
} 


Wave * native_from_value_wave_ref(matteVM_t * vm, matteValue_t in) {
    RETRIEVE_NATIVE_OBJECT_PTR(Wave, RAYMATTE_NATIVE_TYPE__WAVE);
    return object;
}   

void native_update_value_wave(matteVM_t * vm, matteValue_t in) {
    RETRIEVE_NATIVE_OBJECT(Wave, RAYMATTE_NATIVE_TYPE__WAVE);
    UPDATE_KEY(frameCount, native_to_value_int);
    UPDATE_KEY(sampleRate, native_to_value_int);
    UPDATE_KEY(sampleSize, native_to_value_int);
    UPDATE_KEY(channels, native_to_value_int);
} 

Model * native_from_value_model_ref(matteVM_t * vm, matteValue_t in) {
    RETRIEVE_NATIVE_OBJECT_PTR(Model, RAYMATTE_NATIVE_TYPE__MODEL);
    return object;
}   

void native_update_value_model(matteVM_t * vm, matteValue_t in) {
    RETRIEVE_NATIVE_OBJECT(Model, RAYMATTE_NATIVE_TYPE__MODEL);
    UPDATE_KEY(transform, native_to_value_matrix);
    UPDATE_KEY(meshCount, native_to_value_int);
    UPDATE_KEY(materialCount, native_to_value_int);
    UPDATE_KEY(boneCount, native_to_value_int);

} 


Material * native_from_value_material_ref(matteVM_t * vm, matteValue_t in) {
    RETRIEVE_NATIVE_OBJECT_PTR(Material, RAYMATTE_NATIVE_TYPE__MATERIAL);
    return object;
}   

void native_update_value_material(matteVM_t * vm, matteValue_t in) {
    RETRIEVE_NATIVE_OBJECT(Material, RAYMATTE_NATIVE_TYPE__MATERIAL);

    typedef struct {
        Shader shader;
        MaterialMap maps0;
        MaterialMap maps1;    
        MaterialMap maps2;    
        MaterialMap maps3;    

        MaterialMap maps4;    
        MaterialMap maps5;    
        MaterialMap maps6;    
        MaterialMap maps7;    

        MaterialMap maps8;    
        MaterialMap maps9;    
        MaterialMap maps10;    
        MaterialMap maps11;
        
        
        float params0;    
        float params1;    
        float params2;    
        float params3;    
    } MaterialExt;
    MaterialExt ext;
    ext.shader = object->shader;
    memcpy(&ext.maps0, object->maps, sizeof(MaterialMap)*MAX_MATERIAL_MAPS);
    memcpy(&ext.params0, object->params, sizeof(float)*4);
    
    {
        MaterialExt * object = &ext;
        UPDATE_KEY(shader, native_to_value_shader);
        UPDATE_KEY(maps0, native_to_value_materialMap);
        UPDATE_KEY(maps1, native_to_value_materialMap);
        UPDATE_KEY(maps2, native_to_value_materialMap);
        UPDATE_KEY(maps3, native_to_value_materialMap);

        UPDATE_KEY(maps4, native_to_value_materialMap);
        UPDATE_KEY(maps5, native_to_value_materialMap);
        UPDATE_KEY(maps6, native_to_value_materialMap);
        UPDATE_KEY(maps7, native_to_value_materialMap);

        UPDATE_KEY(maps8, native_to_value_materialMap);
        UPDATE_KEY(maps9, native_to_value_materialMap);
        UPDATE_KEY(maps10, native_to_value_materialMap);
        UPDATE_KEY(maps11, native_to_value_materialMap);

        UPDATE_KEY(params0, native_to_value_float);
        UPDATE_KEY(params1, native_to_value_float);
        UPDATE_KEY(params2, native_to_value_float);
        UPDATE_KEY(params3, native_to_value_float);
    }

} 


