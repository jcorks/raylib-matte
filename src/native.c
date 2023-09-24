#include "native.h"
#include "defines.h"
#include <stdlib.h>
#include "../matte/src/matte_store.h"
#include "../matte/src/matte_string.h"
#include "../matte/src/matte_array.h"

enum {
    //// Structs that have special getters
    RAYMATTE_NATIVE_TYPE__IMAGE = 866,
    RAYMATTE_NATIVE_TYPE__FONT,
    RAYMATTE_NATIVE_TYPE__MESH,
    RAYMATTE_NATIVE_TYPE__MODEL,
    RAYMATTE_NATIVE_TYPE__MODEL_ANIMATION,
    RAYMATTE_NATIVE_TYPE__WAVE,
    
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
    *((__TYPE__*)fd->data) = f;    \
    matte_value_object_set_userdata(store, out, fd);\
    matte_value_object_set_native_finalizer(store, out, native_to_value_finalizer, NULL);\
    }

#define NEW_KEY(__name__,__type__)\
    matte_value_object_set_key_string(store, out, MATTE_VM_STR_CAST(vm, "__name__"), native_to_value__type__(vm, in.__name__));


matteValue_t native_to_value_vector2(matteVM_t * vm, Vector2 in) {
    INIT_OUT();
    NEW_KEY(x, float);
    NEW_KEY(y, float);
    return out;
}
matteValue_t native_to_value_vector3(matteVM_t * vm, Vector3 in) {
    INIT_OUT();
    NEW_KEY(x, float);
    NEW_KEY(y, float);
    NEW_KEY(z, float);
    return out;
}
matteValue_t native_to_value_vector4(matteVM_t * vm, Vector4 in) {
    INIT_OUT();
    NEW_KEY(x, float);
    NEW_KEY(y, float);
    NEW_KEY(z, float);
    NEW_KEY(w, float);
    return out;
}
matteValue_t native_to_value_matrix(matteVM_t * vm, Matrix in) {
    INIT_OUT();
    NEW_KEY(m0, float);
    NEW_KEY(m1, float);
    NEW_KEY(m2, float);
    NEW_KEY(m3, float);

    NEW_KEY(m4, float);
    NEW_KEY(m5, float);
    NEW_KEY(m6, float);
    NEW_KEY(m7, float);

    NEW_KEY(m8, float);
    NEW_KEY(m9, float);
    NEW_KEY(m10, float);
    NEW_KEY(m11, float);

    NEW_KEY(m12, float);
    NEW_KEY(m13, float);
    NEW_KEY(m14, float);
    NEW_KEY(m15, float);
    return out;
    
}
matteValue_t native_to_value_color(matteVM_t * vm, Color in) {
    INIT_OUT();
    NEW_KEY(r, int);
    NEW_KEY(g, int);
    NEW_KEY(b, int);
    NEW_KEY(a, int);
    return out;
}
matteValue_t native_to_value_rectangle(matteVM_t * vm, Rectangle in) {
    INIT_OUT();
    NEW_KEY(x, float);
    NEW_KEY(y, float);
    NEW_KEY(width, float);
    NEW_KEY(height, float);
    return out;
}
matteValue_t native_to_value_image(matteVM_t * vm, Image in) {
    INIT_OUT();
    NATIVIZE(Image, RAYMATTE_NATIVE_TYPE__IMAGE);
    NEW_KEY(width, int);
    NEW_KEY(height, int);
    NEW_KEY(mipmaps, int);
    NEW_KEY(format, int);
    return out;
}
matteValue_t native_to_value_texture(matteVM_t * vm, Texture in) {
    INIT_OUT();
    NATIVIZE(Texture, RAYMATTE_NATIVE_TYPE__TEXTURE);
    NEW_KEY(width, int);
    NEW_KEY(height, int);
    NEW_KEY(mipmaps, int);
    NEW_KEY(format, int);
    return out;
}
matteValue_t native_to_value_renderTexture(matteVM_t * vm, RenderTexture in) {
    INIT_OUT();
    NATIVIZE(RenderTexture, RAYMATTE_NATIVE_TYPE__RENDER_TEXTURE);
    NEW_KEY(texture, texture);
    NEW_KEY(depth,   texture);
    return out;
}
matteValue_t native_to_value_nPatchInfo(matteVM_t * vm, NPatchInfo in) {
    INIT_OUT();
    NEW_KEY(source, rectangle);
    NEW_KEY(left, int);
    NEW_KEY(top, int);
    NEW_KEY(right, int);
    NEW_KEY(bottom, int);
    return out;
}
matteValue_t native_to_value_glyphInfo(matteVM_t * vm, GlyphInfo in) {
    INIT_OUT();
    NEW_KEY(image, image);
    NEW_KEY(value, int);
    NEW_KEY(offsetX, int);
    NEW_KEY(offsetY, int);
    NEW_KEY(advanceX, int);
    return out;
}
matteValue_t native_to_value_font(matteVM_t * vm, Font in) {
    INIT_OUT();
    NATIVIZE(Font, RAYMATTE_NATIVE_TYPE__FONT);
    NEW_KEY(image, image);
    NEW_KEY(baseSize, int);
    NEW_KEY(glyphPadding, int);
    NEW_KEY(texture, int);
    return out;
}
matteValue_t native_to_value_camera(matteVM_t * vm, Camera in) {
    INIT_OUT();
    NEW_KEY(position, vector3);
    NEW_KEY(target, vector3);
    NEW_KEY(up, vector3);
    NEW_KEY(fovy, float);
    NEW_KEY(projection, int);
    return out;
}
matteValue_t native_to_value_camera2D(matteVM_t * vm, Camera2D in) {
    INIT_OUT();
    NEW_KEY(offset, vector2);
    NEW_KEY(target, vector2);
    NEW_KEY(rotation, float);
    NEW_KEY(zoom, float);
    return out;
}
matteValue_t native_to_value_mesh(matteVM_t * vm, Mesh in) {
    INIT_OUT();
    NATIVIZE(Mesh, RAYMATTE_NATIVE_TYPE__MESH);
    NEW_KEY(vertexCount, int);
    NEW_KEY(triangleCount, int);
    return out;
}
matteValue_t native_to_value_shader(matteVM_t * vm, Shader in) {
    INIT_OUT();
    NATIVIZE(Shader, RAYMATTE_NATIVE_TYPE__SHADER);
    return out;
}
matteValue_t native_to_value_materialMap(matteVM_t * vm, MaterialMap in) {
    INIT_OUT();
    NEW_KEY(texture, texture);
    NEW_KEY(color, color);
    NEW_KEY(value, float);
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
    NATIVIZE(Material, RAYMATTE_NATIVE_TYPE__MATERIAL)
    NEW_KEY(shader, shader);
    NEW_KEY(maps0, materialMap);
    NEW_KEY(maps1, materialMap);
    NEW_KEY(maps2, materialMap);
    NEW_KEY(maps3, materialMap);

    NEW_KEY(maps4, materialMap);
    NEW_KEY(maps5, materialMap);
    NEW_KEY(maps6, materialMap);
    NEW_KEY(maps7, materialMap);

    NEW_KEY(maps8, materialMap);
    NEW_KEY(maps9, materialMap);
    NEW_KEY(maps10, materialMap);
    NEW_KEY(maps11, materialMap);

    NEW_KEY(params0, float);
    NEW_KEY(params1, float);
    NEW_KEY(params2, float);
    NEW_KEY(params3, float);


    return out;        
}
matteValue_t native_to_value_transform(matteVM_t * vm, Transform in) {
    INIT_OUT();
    NEW_KEY(translation, vector3);
    NEW_KEY(rotation, vector4);
    NEW_KEY(scale, vector3);
    return out;
}
matteValue_t native_to_value_boneInfo(matteVM_t * vm, BoneInfo in) {
    INIT_OUT();
    NEW_KEY(parent, int);
    
    char * str = MemAlloc(33);
    memset(str, 0, 33);
    memcpy(str, in.name, 32);
    matte_value_object_set_key_string(store, out, MATTE_VM_STR_CAST(vm, "name"), native_to_value_string(vm, str));
    return out;    
}
matteValue_t native_to_value_model(matteVM_t * vm, Model in) {
    INIT_OUT();
    NATIVIZE(Model, RAYMATTE_NATIVE_TYPE__MODEL);
    NEW_KEY(transform, transform);
    NEW_KEY(meshCount, int);
    NEW_KEY(materialCount, int);
    NEW_KEY(boneCount, int);
    return out;
}
matteValue_t native_to_value_modelAnimation(matteVM_t * vm, ModelAnimation in) {
    INIT_OUT();
    NATIVIZE(Mesh, RAYMATTE_NATIVE_TYPE__MODEL_ANIMATION);
    NEW_KEY(boneCount, int);
    NEW_KEY(frameCount, int);
    char * str = MemAlloc(33);
    memset(str, 0, 33);
    memcpy(str, in.name, 32);
    matte_value_object_set_key_string(store, out, MATTE_VM_STR_CAST(vm, "name"), native_to_value_string(vm, str));
    return out;    
}
matteValue_t native_to_value_ray(matteVM_t * vm, Ray in) {
    INIT_OUT();
    NEW_KEY(direction, vector3);
    NEW_KEY(position, vector3);
    return out;
}
matteValue_t native_to_value_rayCollision(matteVM_t * vm, RayCollision in) {
    INIT_OUT();
    NEW_KEY(hit, int);
    NEW_KEY(distance, float);
    NEW_KEY(point, vector3);
    NEW_KEY(normal, vector3);
    return out;

}

matteValue_t native_to_value_boundingBox(matteVM_t * vm, BoundingBox in) {
    INIT_OUT();
    NEW_KEY(min, vector3);
    NEW_KEY(max, vector3);
    return out;
}

matteValue_t native_to_value_wave(matteVM_t * vm, Wave in) {
    INIT_OUT();
    NATIVIZE(Wave, RAYMATTE_NATIVE_TYPE__WAVE);
    NEW_KEY(frameCount, int);
    NEW_KEY(sampleRate, int);
    NEW_KEY(sampleSize, int);
    NEW_KEY(channels, int);
    return out;
}
matteValue_t native_to_value_audioStream(matteVM_t * vm, AudioStream in) {
    INIT_OUT();
    NATIVIZE(AudioStream, RAYMATTE_NATIVE_TYPE__AUDIO_STREAM);
    NEW_KEY(sampleRate, int);
    NEW_KEY(sampleSize, int);
    NEW_KEY(channels, int);
    return out;
}
matteValue_t native_to_value_sound(matteVM_t * vm, Sound in) {
    INIT_OUT();
    NEW_KEY(frameCount, int);
    NEW_KEY(stream, audioStream);
    return out;
}
matteValue_t native_to_value_music(matteVM_t * vm, Music in) {
    INIT_OUT();
    NATIVIZE(Music, RAYMATTE_NATIVE_TYPE__MUSIC);
    NEW_KEY(frameCount, int);
    NEW_KEY(stream, audioStream);
    NEW_KEY(loooping, int);
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
    matte_value_object_set_key_string(store, in, MATTE_VM_STR_CAST(vm, "__name__"), native_to_value__type__(vm, object->__name__));

#define RETRIEVE_NATIVE_OBJECT(__TYPE__,__TAG__)\
    matteStore_t * store = matte_vm_get_store(vm);\
    if (in.binID != MATTE_VALUE_TYPE_OBJECT) {\
        matte_vm_raise_error_cstring(vm, "Could not decode __TYPE__: value is not an Object.");\
        __TYPE__ dout = {};\
        return dout;\
    }\
    NativeEncodeData_t * objectSrc = matte_value_object_get_userdata(store, img);\
    if (objectSrc == NULL || objectSrc->typeTag != __TAG__) {\
        matte_vm_raise_error_cstring(vm, "Could not decode __TYPE__: value is not an __TYPE__.");\
        __TYPE__ dout = {};\
        return dout;\
    }\
    __TYPE__ * object = (__TYPE__*)objectSrc->data;
    


#define RETRIEVE_NATIVE(__TYPE__,__TAG__)\
    matteStore_t * store = matte_vm_get_store(vm);\
    if (in.binID != MATTE_VALUE_TYPE_OBJECT) {\
        matte_vm_raise_error_cstring(vm, "Could not decode __TYPE__: value is not an Object.");\
        __TYPE__ dout = {};\
        return dout;\
    }\
    NativeEncodeData_t * object = matte_value_object_get_userdata(store, img);\
    if (object == NULL || object->typeTag != __TAG__) {\
        matte_vm_raise_error_cstring(vm, "Could not decode __TYPE__: value is not an __TYPE__.");\
        __TYPE__ dout = {};\
        return dout;\
    }\
    return *((__TYPE__*)object->data);

#define READ_NUMBER(__NAME__)\
    out.__NAME__ = matte_value_as_number(store, matte_value_object_access_string(store, in, MATTE_VM_STR_CAST(vm, "__NAME__")));
    
#define READ_KEY(__NAME__,__TYPE__)\
    out.__NAME__ = native_from_value___TYPE__(vm, matte_value_object_access_string(store, in, MATTE_VM_STR_CAST(vm, "__NAME__")));






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
    INIT_FROM(Matrix);
    READ_NUMBER(m0);
    READ_NUMBER(m1);
    READ_NUMBER(m2);
    READ_NUMBER(m3);

    READ_NUMBER(m4);
    READ_NUMBER(m5);
    READ_NUMBER(m6);
    READ_NUMBER(m7);

    READ_NUMBER(m8);
    READ_NUMBER(m9);
    READ_NUMBER(m10);
    READ_NUMBER(m11);

    READ_NUMBER(m12);
    READ_NUMBER(m13);
    READ_NUMBER(m14);
    READ_NUMBER(m15);

    return out;
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
    RETRIEVE_NATIVE(Image, RAYMATTE_NATIVE_TYPE__TEXTURE);
}
RenderTexture native_from_value_renderTexture(matteVM_t * vm, matteValue_t in) {
    RETRIEVE_NATIVE(Image, RAYMATTE_NATIVE_TYPE__RENDER_TEXTURE);
}
NPatchInfo native_from_value_nPatchInfo(matteVM_t * vm, matteValue_t in) {
    INIT_FROM(NPatchInfo);
    READ_NUMBER(top);
    READ_NUMBER(left);
    READ_NUMBER(bottom);
    READ_NUMBER(right);
    READ_KEY(source, rectangle);
    return out;
}
GlyphInfo native_from_value_glyphInfo(matteVM_t * vm, matteValue_t in) {
    INIT_FROM(GlyphInfo);
    READ_NUMBER(value);
    READ_NUMBER(offsetX);
    READ_NUMBER(offsetY);
    READ_NUMBER(advanceX);
    READ_KEY(image, image);
    return out;

}
Font native_from_value_font(matteVM_t * vm, matteValue_t in) {
    RETRIEVE_NATIVE(Font, RAYMATTE_NATIVE_TYPE__FONT);
}
Camera3D native_from_value_camera(matteVM_t * vm, matteValue_t in) {
    INIT_FROM(Camera);
    READ_NUMBER(fovy);
    READ_NUMBER(projection);
    READ_KEY(position, vector3);
    READ_KEY(target, vector3);
    READ_KEY(up, vector3);
    return out;
}
Camera2D native_from_value_camera2D(matteVM_t * vm, matteValue_t in) {
    INIT_FROM(Camera2D);
    READ_NUMBER(rotation);
    READ_NUMBER(zoom);
    READ_KEY(position, vector2);
    READ_KEY(target, vector2);
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
    READ_KEY(texture, texture);
    READ_KEY(color, color);
    READ_NUMBER(value);
    return out;
}
Material native_from_value_material(matteVM_t * vm, matteValue_t in) {
    RETRIEVE_NATIVE(Material, RAYMATTE_NATIVE_TYPE__MATERIAL);
}
Transform native_from_value_transform(matteVM_t * vm, matteValue_t in) {
    INIT_FROM(Transform);
    READ_KEY(translation, vector3);
    READ_KEY(rotation, vector4);
    READ_KEY(scale, vector3);
    return out;
}

BoneInfo native_from_value_boneInfo(matteVM_t * vm, matteValue_t in) {
    RETRIEVE_NATIVE(BoneInfo, RAYMATTE_NATIVE_TYPE__BONEINFO);
}
Model native_from_value_model(matteVM_t * vm, matteValue_t in) {
    RETRIEVE_NATIVE(Model, RAYMATTE_NATIVE_TYPE__MODEL);
}
ModelAnimation native_from_value_modelAnimation(matteVM_t * vm, matteValue_t in) {
    RETRIEVE_NATIVE(ModelAnimation, RAYMATTE_NATIVE_TYPE__MODEL_ANIMATION);
}
Ray native_from_value_ray(matteVM_t * vm, matteValue_t in) {
    INIT_FROM(Ray);
    READ_KEY(position, vector3);
    READ_KEY(direction, vector3);
    return out;
}
RayCollision native_from_value_rayCollision(matteVM_t * vm, matteValue_t in) {
    INIT_FROM(RayCollision);
    READ_KEY(point, vector3);
    READ_KEY(normal, vector3);
    READ_NUMBER(hit);
    READ_NUMBER(distance);
    return out;
    
}
BoundingBox native_from_value_boundingBox(matteVM_t * vm, matteValue_t in) {
    INIT_FROM(BoundingBox);
    READ_KEY(min, vector3);
    READ_KEY(max, vector3);
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
    READ_KEY(stream, audioStream);
    READ_NUMBER(frameCount);
    return out;
}
Music native_from_value_music(matteVM_t * vm, matteValue_t in) {
    RETRIEVE_NATIVE(Music, RAYMATTE_NATIVE_TYPE__MUSIC);
}





Shader native_from_value_shader(matteVM_t * vm, matteValue_t shad) {
    matteStore_t * store = matte_vm_get_store(vm);    

    if (shad.binID != MATTE_VALUE_TYPE_OBJECT) {
        matte_vm_raise_error_cstring(vm, "Could not decode Shader: value is not an Shader.");
        Shader imgOut = {};
        return imgOut;
    }
    
    NativeEncodeData_t * object = matte_value_object_get_userdata(store, shad);
    if (object == NULL || object->typeTag != RAYMATTE_NATIVE_TYPE__TEXTURE) {
        matte_vm_raise_error_cstring(vm, "Could not decode Shader: value is not an Shader.");
        Shader imgOut = {};
        return imgOut;
    }

    return *((Shader*)object->data);
}   


Font native_from_value_font(matteVM_t * vm, matteValue_t shad) {
    matteStore_t * store = matte_vm_get_store(vm);    

    if (shad.binID != MATTE_VALUE_TYPE_OBJECT) {
        matte_vm_raise_error_cstring(vm, "Could not decode Font: value is not an Font.");
        Font imgOut = {};
        return imgOut;
    }
    
    NativeEncodeData_t * object = matte_value_object_get_userdata(store, shad);
    if (object == NULL || object->typeTag != RAYMATTE_NATIVE_TYPE__FONT) {
        matte_vm_raise_error_cstring(vm, "Could not decode Font: value is not an Font.");
        Font imgOut = {};
        return imgOut;
    }

    return *((Font*)object->data);
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
    RETRIEVE_NATIVE_OBJECT(Image, RAYMATTE_NATIVE_TYPE__IMAGE);
    return object;
}   

void native_update_value_image(matteVM_t * vm, matteValue_t in) {
    RETRIEVE_NATIVE_OBJECT(Image, RAYMATTE_NATIVE_TYPE__IMAGE);
    UPDATE_KEY(width, int);
    UPDATE_KEY(height, int);
    UPDATE_KEY(mipmaps, int);
    UPDATE_KEY(format, int);
}


Image * native_from_value_texture_ref(matteVM_t * vm, matteValue_t in) {
    RETRIEVE_NATIVE_OBJECT(Texture, RAYMATTE_NATIVE_TYPE__TEXTURE);
    return object;
}   

void native_update_value_texture(matteVM_t * vm, matteValue_t in) {
    RETRIEVE_NATIVE_OBJECT(Texture, RAYMATTE_NATIVE_TYPE__TEXTURE);
    UPDATE_KEY(width, int);
    UPDATE_KEY(height, int);
    UPDATE_KEY(mipmaps, int);
    UPDATE_KEY(format, int);
} 



Mesh * native_from_value_mesh_ref(matteVM_t * vm, matteValue_t in) {
    RETRIEVE_NATIVE_OBJECT(Mesh, RAYMATTE_NATIVE_TYPE__MESH);
    return object;
}   

void native_update_value_mesh(matteVM_t * vm, matteValue_t in) {
    RETRIEVE_NATIVE_OBJECT(Mesh, RAYMATTE_NATIVE_TYPE__MESH);
    UPDATE_KEY(vertexCount, int);
    UPDATE_KEY(triangleCount, int);
} 

Model * native_from_value_model_ref(matteVM_t * vm, matteValue_t in) {
    RETRIEVE_NATIVE_OBJECT(Model, RAYMATTE_NATIVE_TYPE__MODEL);
    return object;
}   

void native_update_value_model(matteVM_t * vm, matteValue_t in) {
    RETRIEVE_NATIVE_OBJECT(Model, RAYMATTE_NATIVE_TYPE__MODEL);
    UPDATE_KEY(transform, transform);
    UPDATE_KEY(meshCount, int);
    UPDATE_KEY(materialCount, int);
    UPDATE_KEY(boneCount, int);

} 


Material * native_from_value_material_ref(matteVM_t * vm, matteValue_t in) {
    RETRIEVE_NATIVE_OBJECT(Material, RAYMATTE_NATIVE_TYPE__MATERIAL);
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
    MaterialExt exp;
    ext.shader = object->shader;
    memcpy(&ext.maps0, object->maps, sizeof(MaterialMap)*MAX_MATERIAL_MAPS);
    memcpy(&ext.params0, object->params, sizeof(float)*4);
    
    {
        MaterialExt * object = &exp;
        UPDATE_KEY(shader, shader);
        UPDATE_KEY(maps0, materialMap);
        UPDATE_KEY(maps1, materialMap);
        UPDATE_KEY(maps2, materialMap);
        UPDATE_KEY(maps3, materialMap);

        UPDATE_KEY(maps4, materialMap);
        UPDATE_KEY(maps5, materialMap);
        UPDATE_KEY(maps6, materialMap);
        UPDATE_KEY(maps7, materialMap);

        UPDATE_KEY(maps8, materialMap);
        UPDATE_KEY(maps9, materialMap);
        UPDATE_KEY(maps10, materialMap);
        UPDATE_KEY(maps11, materialMap);

        UPDATE_KEY(params0, float);
        UPDATE_KEY(params1, float);
        UPDATE_KEY(params2, float);
        UPDATE_KEY(params3, float);
    }

} 


