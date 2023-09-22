#include "native.h"
#include "defines.h"
#include <stdlib.h>
#include "../matte/src/matte_store.h"
#include "../matte/src/matte_string.h"
#include "../matte/src/matte_array.h"

enum {
    RAYMATTE_NATIVE_TYPE__IMAGE = 866,
    RAYMATTE_NATIVE_TYPE__RENDER_TEXTURE,
    RAYMATTE_NATIVE_TYPE__TEXTURE,
    RAYMATTE_NATIVE_TYPE__SHADER,
    RAYMATTE_NATIVE_TYPE__FONT
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




matteValue_t native_to_value_pointer(matteVM_t * vm, void * ptr) {
    matteValue_t out;
    matteStore_t * store = matte_vm_get_store(vm);
    matteString_t * ptrStr = matte_string_create_from_c_str("%p", ptr);
    matte_value_into_string(store, &out, ptrStr);
    matte_string_destroy(ptrStr);
    return out;
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

// convert into a simple object.
matteValue_t native_to_value_image(matteVM_t * vm, Image img) {
    matteStore_t * store = matte_vm_get_store(vm);
    matteValue_t out = matte_store_new_value(store);
    matte_value_into_new_object_ref(store, &out);

    NativeEncodeData_t * imgd = calloc(1, sizeof(NativeEncodeData_t));
    imgd->data = calloc(1, sizeof(Image));
    *((Image*)imgd->data) = img;
    imgd->typeTag = RAYMATTE_NATIVE_TYPE__IMAGE;
    
    matte_value_object_set_userdata(store, out, imgd);
    matte_value_object_set_native_finalizer(store, out, native_to_value_finalizer, NULL);

    return out;
}


matteValue_t native_to_value_vector2(matteVM_t * vm, Vector2 v2) {
    matteStore_t * store = matte_vm_get_store(vm);    

    matteValue_t x = native_to_value_float(vm, v2.x);
    matteValue_t y = native_to_value_float(vm, v2.y);

    matteValue_t v = matte_store_new_value(store);
    matte_value_into_new_object_ref(store, &v);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "x"), x);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "y"), y);

    return v;
}   

matteValue_t native_to_value_vector3(matteVM_t * vm, Vector3 v3) {
    matteStore_t * store = matte_vm_get_store(vm);    

    matteValue_t x = native_to_value_float(vm, v3.x);
    matteValue_t y = native_to_value_float(vm, v3.y);
    matteValue_t z = native_to_value_float(vm, v3.z);


    matteValue_t v = matte_store_new_value(store);
    matte_value_into_new_object_ref(store, &v);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "x"), x);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "y"), y);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "z"), z);

    return v;
}   

matteValue_t native_to_value_vector4(matteVM_t * vm, Vector4 v4) {
    matteStore_t * store = matte_vm_get_store(vm);    

    matteValue_t x = native_to_value_float(vm, v4.x);
    matteValue_t y = native_to_value_float(vm, v4.y);
    matteValue_t z = native_to_value_float(vm, v4.z);
    matteValue_t w = native_to_value_float(vm, v4.w);


    matteValue_t v = matte_store_new_value(store);
    matte_value_into_new_object_ref(store, &v);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "x"), x);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "y"), y);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "z"), z);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "w"), w);

    return v;
}   

matteValue_t native_to_value_color(matteVM_t * vm, Color c) {
    matteStore_t * store = matte_vm_get_store(vm);    

    matteValue_t r = native_to_value_float(vm, c.r);
    matteValue_t g = native_to_value_float(vm, c.g);
    matteValue_t b = native_to_value_float(vm, c.b);
    matteValue_t a = native_to_value_float(vm, c.a);


    matteValue_t v = matte_store_new_value(store);
    matte_value_into_new_object_ref(store, &v);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "r"), r);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "g"), g);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "b"), b);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "a"), a);

    return v;
}   

matteValue_t native_to_value_rectangle(matteVM_t * vm, Rectangle r) {
    matteStore_t * store = matte_vm_get_store(vm);    

    matteValue_t x = native_to_value_float(vm, r.x);
    matteValue_t y = native_to_value_float(vm, r.y);
    matteValue_t width = native_to_value_float(vm, r.width);
    matteValue_t height = native_to_value_float(vm, r.height);


    matteValue_t v = matte_store_new_value(store);
    matte_value_into_new_object_ref(store, &v);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "x"), x);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "y"), y);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "width"), width);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "height"), height);

    return v;
}   



matteValue_t native_to_value_glyphInfo(matteVM_t * vm, GlyphInfo g) {
    matteStore_t * store = matte_vm_get_store(vm);    

    matteValue_t value = native_to_value_float(vm, g.value);
    matteValue_t offsetX = native_to_value_float(vm, g.offsetX);
    matteValue_t offsetY = native_to_value_float(vm, g.offsetY);
    matteValue_t advanceX = native_to_value_float(vm, g.advanceX);
    matteValue_t image = native_to_value_image(vm, g.image);

    matteValue_t v = matte_store_new_value(store);
    matte_value_into_new_object_ref(store, &v);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "value"), value);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "offsetX"), offsetX);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "offsetY"), offsetY);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "advanceX"), advanceX);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "image"), image);

    return v;
}   

matteValue_t native_to_value_camera(matteVM_t * vm, Camera cam) {
    matteStore_t * store = matte_vm_get_store(vm);    


    matteValue_t position   = native_to_value_vector3(vm, cam.position);
    matteValue_t target     = native_to_value_vector3(vm, cam.target);
    matteValue_t up         = native_to_value_vector3(vm, cam.up);
    matteValue_t fovy       = native_to_value_float(vm, cam.fovy);
    matteValue_t projection = native_to_value_float(vm, cam.projection);


    matteValue_t v = matte_store_new_value(store);
    matte_value_into_new_object_ref(store, &v);

    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "position"), position);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "target"), target);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "up"), up);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "fovy"), fovy);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "projection"), projection);

    return v;
}   



matteValue_t native_to_value_matrix(matteVM_t * vm, Matrix m) {
    matteStore_t * store = matte_vm_get_store(vm);    

    matteValue_t vals[] = {
        native_to_value_float(vm, m.m0),
        native_to_value_float(vm, m.m4),
        native_to_value_float(vm, m.m8),
        native_to_value_float(vm, m.m12),

        native_to_value_float(vm, m.m1),
        native_to_value_float(vm, m.m5),
        native_to_value_float(vm, m.m9),
        native_to_value_float(vm, m.m13),

        native_to_value_float(vm, m.m2),
        native_to_value_float(vm, m.m6),
        native_to_value_float(vm, m.m10),
        native_to_value_float(vm, m.m14),

        native_to_value_float(vm, m.m3),
        native_to_value_float(vm, m.m7),
        native_to_value_float(vm, m.m11),
        native_to_value_float(vm, m.m15)
    };

    matteArray_t arr = MATTE_ARRAY_CAST(
        vals,
        sizeof(matteValue_t),
        16
    );

    matteValue_t v = matte_store_new_value(store);
    matte_value_into_new_object_array_ref(store, &v, &arr);

    return v;
}   



matteValue_t native_to_value_ray(matteVM_t * vm, Ray ray) {
    matteStore_t * store = matte_vm_get_store(vm);    

    matteValue_t position = native_to_value_vector3(vm, ray.position);
    matteValue_t direction = native_to_value_vector3(vm, ray.direction);


    matteValue_t v = matte_store_new_value(store);
    matte_value_into_new_object_ref(store, &v);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "position"), position);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "direction"), direction);

    return v;

}


matteValue_t native_to_value_renderTexture(matteVM_t * vm, RenderTexture img) {
    matteStore_t * store = matte_vm_get_store(vm);
    matteValue_t out = matte_store_new_value(store);
    matte_value_into_new_object_ref(store, &out);

    NativeEncodeData_t * imgd = calloc(1, sizeof(NativeEncodeData_t));
    imgd->data = calloc(1, sizeof(RenderTexture));
    imgd->typeTag = RAYMATTE_NATIVE_TYPE__RENDER_TEXTURE;
    *((RenderTexture*)imgd->data) = img;
    
    matte_value_object_set_userdata(store, out, imgd);
    matte_value_object_set_native_finalizer(store, out, native_to_value_finalizer, NULL);

    return out;
}

matteValue_t native_to_value_texture(matteVM_t * vm, Texture img) {
    matteStore_t * store = matte_vm_get_store(vm);
    matteValue_t out = matte_store_new_value(store);
    matte_value_into_new_object_ref(store, &out);

    NativeEncodeData_t * imgd = calloc(1, sizeof(NativeEncodeData_t));
    imgd->data = calloc(1, sizeof(Texture));
    imgd->typeTag = RAYMATTE_NATIVE_TYPE__TEXTURE;
    *((Texture*)imgd->data) = img;
    
    matte_value_object_set_userdata(store, out, imgd);
    matte_value_object_set_native_finalizer(store, out, native_to_value_finalizer, NULL);

    return out;
}

matteValue_t native_to_value_shader(matteVM_t * vm, Shader shad) {
    matteStore_t * store = matte_vm_get_store(vm);
    matteValue_t out = matte_store_new_value(store);
    matte_value_into_new_object_ref(store, &out);

    NativeEncodeData_t * imgd = calloc(1, sizeof(NativeEncodeData_t));
    imgd->data = calloc(1, sizeof(Shader));
    imgd->typeTag = RAYMATTE_NATIVE_TYPE__SHADER;
    *((Shader*)imgd->data) = shad;
    
    matte_value_object_set_userdata(store, out, imgd);
    matte_value_object_set_native_finalizer(store, out, native_to_value_finalizer, NULL);

    return out;
}


matteValue_t native_to_value_filePathList(matteVM_t * vm, FilePathList list) {
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







const char * native_from_value_string_unsafe(matteVM_t * vm, matteValue_t str) {   
    return matte_string_get_c_str(matte_value_string_get_string_unsafe(matte_vm_get_store(vm), str));
}
    



Image native_from_value_image(matteVM_t * vm, matteValue_t img) {
    matteStore_t * store = matte_vm_get_store(vm);    

    if (img.binID != MATTE_VALUE_TYPE_OBJECT) {
        matte_vm_raise_error_cstring(vm, "Could not decode Image: value is not an Image.");
        Image imgOut = {};
        return imgOut;
    }
    
    NativeEncodeData_t * object = matte_value_object_get_userdata(store, img);
    if (object == NULL || object->typeTag != RAYMATTE_NATIVE_TYPE__IMAGE) {
        matte_vm_raise_error_cstring(vm, "Could not decode Image: value is not an Image.");
        Image imgOut = {};
        return imgOut;
    }

    return *((Image*)object->data);
}   


Image * native_from_value_image_ref(matteVM_t * vm, matteValue_t img) {
    matteStore_t * store = matte_vm_get_store(vm);    

    if (img.binID != MATTE_VALUE_TYPE_OBJECT) {
        matte_vm_raise_error_cstring(vm, "Could not decode Image: value is not an Image.");
        return NULL;
    }
    
    NativeEncodeData_t * object = matte_value_object_get_userdata(store, img);
    if (object == NULL || object->typeTag != RAYMATTE_NATIVE_TYPE__IMAGE) {
        matte_vm_raise_error_cstring(vm, "Could not decode Image: value is not an Image.");
        return NULL;
    }

    return (Image*)object->data;
}   

Vector2 native_from_value_vector2(matteVM_t * vm, matteValue_t v2) {
    matteStore_t * store = matte_vm_get_store(vm);    

    if (v2.binID != MATTE_VALUE_TYPE_OBJECT) {
        matte_vm_raise_error_cstring(vm, "Could not decode Vector2: value is not an Object.");
        Vector2 errOut = {};
        return errOut;
    }


    Vector2 v = {};
    v.x = matte_value_as_number(store, matte_value_object_access_string(store, v2, MATTE_VM_STR_CAST(vm, "x")));
    v.y = matte_value_as_number(store, matte_value_object_access_string(store, v2, MATTE_VM_STR_CAST(vm, "y")));

    return v;
}   

Vector3 native_from_value_vector3(matteVM_t * vm, matteValue_t v3) {
    matteStore_t * store = matte_vm_get_store(vm);    

    if (v3.binID != MATTE_VALUE_TYPE_OBJECT) {
        matte_vm_raise_error_cstring(vm, "Could not decode Vector3: value is not an Object.");
        Vector3 errOut = {};
        return errOut;
    }


    Vector3 v = {};
    v.x = matte_value_as_number(store, matte_value_object_access_string(store, v3, MATTE_VM_STR_CAST(vm, "x")));
    v.y = matte_value_as_number(store, matte_value_object_access_string(store, v3, MATTE_VM_STR_CAST(vm, "y")));
    v.z = matte_value_as_number(store, matte_value_object_access_string(store, v3, MATTE_VM_STR_CAST(vm, "z")));

    return v;
}   





Vector4 native_from_value_vector4(matteVM_t * vm, matteValue_t v4) {
    matteStore_t * store = matte_vm_get_store(vm);    

    if (v4.binID != MATTE_VALUE_TYPE_OBJECT) {
        matte_vm_raise_error_cstring(vm, "Could not decode Vector4: value is not an Object.");
        Vector4 errOut = {};
        return errOut;
    }


    Vector4 v = {};
    v.x = matte_value_as_number(store, matte_value_object_access_string(store, v4, MATTE_VM_STR_CAST(vm, "x")));
    v.y = matte_value_as_number(store, matte_value_object_access_string(store, v4, MATTE_VM_STR_CAST(vm, "y")));
    v.z = matte_value_as_number(store, matte_value_object_access_string(store, v4, MATTE_VM_STR_CAST(vm, "z")));
    v.w = matte_value_as_number(store, matte_value_object_access_string(store, v4, MATTE_VM_STR_CAST(vm, "w")));

    return v;
}   


Rectangle native_from_value_rectangle(matteVM_t * vm, matteValue_t rec) {
    matteStore_t * store = matte_vm_get_store(vm);    

    if (rec.binID != MATTE_VALUE_TYPE_OBJECT) {
        matte_vm_raise_error_cstring(vm, "Could not decode Rectangle: value is not an Object.");
        Rectangle errOut = {};
        return errOut;
    }


    Rectangle v = {};
    v.x = matte_value_as_number(store, matte_value_object_access_string(store, rec, MATTE_VM_STR_CAST(vm, "x")));
    v.y = matte_value_as_number(store, matte_value_object_access_string(store, rec, MATTE_VM_STR_CAST(vm, "y")));
    v.width = matte_value_as_number(store, matte_value_object_access_string(store, rec, MATTE_VM_STR_CAST(vm, "width")));
    v.height = matte_value_as_number(store, matte_value_object_access_string(store, rec, MATTE_VM_STR_CAST(vm, "height")));

    return v;
}   


Matrix native_from_value_matrix(matteVM_t * vm, matteValue_t ma) {
    matteStore_t * store = matte_vm_get_store(vm);    

    if (ma.binID != MATTE_VALUE_TYPE_OBJECT) {
        matte_vm_raise_error_cstring(vm, "Could not decode Matrix: value is not an Object.");
        Matrix errOut = {};
        return errOut;
    }

    if (matte_value_object_get_number_key_count(store, ma) != 16) {
        matte_vm_raise_error_cstring(vm, "Could not decode Matrix: Object does not contain 16 numbers.");
        Matrix errOut = {};
        return errOut;
    }
    
    Matrix m = {};
    m.m0  = matte_value_as_number(store, matte_value_object_access_index(store, ma, 0));
    m.m4  = matte_value_as_number(store, matte_value_object_access_index(store, ma, 1));
    m.m8  = matte_value_as_number(store, matte_value_object_access_index(store, ma, 2));
    m.m12 = matte_value_as_number(store, matte_value_object_access_index(store, ma, 3));


    m.m1  = matte_value_as_number(store, matte_value_object_access_index(store, ma, 4));
    m.m5  = matte_value_as_number(store, matte_value_object_access_index(store, ma, 5));
    m.m9  = matte_value_as_number(store, matte_value_object_access_index(store, ma, 6));
    m.m13 = matte_value_as_number(store, matte_value_object_access_index(store, ma, 7));

    m.m2  = matte_value_as_number(store, matte_value_object_access_index(store, ma, 8));
    m.m6  = matte_value_as_number(store, matte_value_object_access_index(store, ma, 9));
    m.m10 = matte_value_as_number(store, matte_value_object_access_index(store, ma, 10));
    m.m14 = matte_value_as_number(store, matte_value_object_access_index(store, ma, 11));

    m.m3  = matte_value_as_number(store, matte_value_object_access_index(store, ma, 12));
    m.m7  = matte_value_as_number(store, matte_value_object_access_index(store, ma, 13));
    m.m11 = matte_value_as_number(store, matte_value_object_access_index(store, ma, 14));
    m.m15 = matte_value_as_number(store, matte_value_object_access_index(store, ma, 15));

    return m;
} 


Color native_from_value_color(matteVM_t * vm, matteValue_t col) {
    matteStore_t * store = matte_vm_get_store(vm);    

    if (col.binID != MATTE_VALUE_TYPE_OBJECT) {
        matte_vm_raise_error_cstring(vm, "Could not decode Color: value is not an Color.");
        Color errOut = {};
        return errOut;
    }


    Color v = {};
    v.r = matte_value_as_number(store, matte_value_object_access_string(store, col, MATTE_VM_STR_CAST(vm, "r")));
    v.g = matte_value_as_number(store, matte_value_object_access_string(store, col, MATTE_VM_STR_CAST(vm, "g")));
    v.b = matte_value_as_number(store, matte_value_object_access_string(store, col, MATTE_VM_STR_CAST(vm, "b")));
    v.a = matte_value_as_number(store, matte_value_object_access_string(store, col, MATTE_VM_STR_CAST(vm, "a")));

    return v;
}   

Camera2D native_from_value_camera2D(matteVM_t * vm, matteValue_t cam) {
    matteStore_t * store = matte_vm_get_store(vm);    

    if (cam.binID != MATTE_VALUE_TYPE_OBJECT) {
        matte_vm_raise_error_cstring(vm, "Could not decode Camera2D: value is not an Camera2D.");
        Camera2D errOut = {};
        return errOut;
    }


    Camera2D v = {};
    v.offset   = native_from_value_vector2(vm, matte_value_object_access_string(store, cam, MATTE_VM_STR_CAST(vm, "offset")));
    v.target   = native_from_value_vector2(vm, matte_value_object_access_string(store, cam, MATTE_VM_STR_CAST(vm, "target")));
    v.rotation = matte_value_as_number(store, matte_value_object_access_string(store, cam, MATTE_VM_STR_CAST(vm, "rotation")));
    v.zoom     = matte_value_as_number(store, matte_value_object_access_string(store, cam, MATTE_VM_STR_CAST(vm, "zoom")));

    return v;
}   

Camera3D native_from_value_camera(matteVM_t * vm, matteValue_t cam) {
    matteStore_t * store = matte_vm_get_store(vm);    

    if (cam.binID != MATTE_VALUE_TYPE_OBJECT) {
        matte_vm_raise_error_cstring(vm, "Could not decode Camera3D: value is not an Camera3D.");
        Camera3D errOut = {};
        return errOut;
    }


    Camera3D v = {};
    v.position   = native_from_value_vector3(vm, matte_value_object_access_string(store, cam, MATTE_VM_STR_CAST(vm, "position")));
    v.target     = native_from_value_vector3(vm, matte_value_object_access_string(store, cam, MATTE_VM_STR_CAST(vm, "target")));
    v.up         = native_from_value_vector3(vm, matte_value_object_access_string(store, cam, MATTE_VM_STR_CAST(vm, "up")));
    v.fovy        = matte_value_as_number(store, matte_value_object_access_string(store, cam, MATTE_VM_STR_CAST(vm, "fovy")));
    v.projection  = matte_value_as_number(store, matte_value_object_access_string(store, cam, MATTE_VM_STR_CAST(vm, "projection")));

    return v;
}  


NPatchInfo native_from_value_nPatchInfo(matteVM_t * vm, matteValue_t n) {
    matteStore_t * store = matte_vm_get_store(vm);    

    if (n.binID != MATTE_VALUE_TYPE_OBJECT) {
        matte_vm_raise_error_cstring(vm, "Could not decode NPatchInfo: value is not an NPatchInfo.");
        NPatchInfo errOut = {};
        return errOut;
    }


    NPatchInfo v = {};
    v.source  = native_from_value_rectangle(vm, matte_value_object_access_string(store, cam, MATTE_VM_STR_CAST(vm, "source")));
    v.left    = matte_value_as_number(store, matte_value_object_access_string(store, cam, MATTE_VM_STR_CAST(vm, "left")));
    v.top     = matte_value_as_number(store, matte_value_object_access_string(store, cam, MATTE_VM_STR_CAST(vm, "top")));
    v.right   = matte_value_as_number(store, matte_value_object_access_string(store, cam, MATTE_VM_STR_CAST(vm, "right")));
    v.bottom  = matte_value_as_number(store, matte_value_object_access_string(store, cam, MATTE_VM_STR_CAST(vm, "bottom")));
    v.layout  = matte_value_as_number(store, matte_value_object_access_string(store, cam, MATTE_VM_STR_CAST(vm, "layout")));
    return v;
}  





RenderTexture native_from_value_renderTexture(matteVM_t * vm, matteValue_t img) {
    matteStore_t * store = matte_vm_get_store(vm);    

    if (img.binID != MATTE_VALUE_TYPE_OBJECT) {
        matte_vm_raise_error_cstring(vm, "Could not decode RenderTexture/RenderTexture2D: value is not an Object.");
        RenderTexture imgOut = {};
        return imgOut;
    }
    
    NativeEncodeData_t * object = matte_value_object_get_userdata(store, img);
    if (object == NULL || object->typeTag != RAYMATTE_NATIVE_TYPE__RENDER_TEXTURE) {
        matte_vm_raise_error_cstring(vm, "Could not decode RenderTexture/RenderTexture2D: value is not an RenderTexture/RenderTexture2D.");
        RenderTexture imgOut = {};
        return imgOut;
    }

    return *((RenderTexture*)object->data);
}   

Texture native_from_value_texture(matteVM_t * vm, matteValue_t img) {
    matteStore_t * store = matte_vm_get_store(vm);    

    if (img.binID != MATTE_VALUE_TYPE_OBJECT) {
        matte_vm_raise_error_cstring(vm, "Could not decode Texture/Texture2D: value is not an Object.");
        Texture imgOut = {};
        return imgOut;
    }
    
    NativeEncodeData_t * object = matte_value_object_get_userdata(store, img);
    if (object == NULL || object->typeTag != RAYMATTE_NATIVE_TYPE__RENDER_TEXTURE) {
        matte_vm_raise_error_cstring(vm, "Could not decode Texture/Texture2D: value is not an Texture/Texture2D.");
        Texture imgOut = {};
        return imgOut;
    }

    return *((Texture*)object->data);
}   

Texture native_from_value_texture_ref(matteVM_t * vm, matteValue_t img) {
    matteStore_t * store = matte_vm_get_store(vm);    

    if (img.binID != MATTE_VALUE_TYPE_OBJECT) {
        matte_vm_raise_error_cstring(vm, "Could not decode Texture/Texture2D: value is not an Object.");
        Texture imgOut = {};
        return imgOut;
    }
    
    NativeEncodeData_t * object = matte_value_object_get_userdata(store, img);
    if (object == NULL || object->typeTag != RAYMATTE_NATIVE_TYPE__RENDER_TEXTURE) {
        matte_vm_raise_error_cstring(vm, "Could not decode Texture/Texture2D: value is not an Texture/Texture2D.");
        Texture imgOut = {};
        return imgOut;
    }

    return object->data;
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



