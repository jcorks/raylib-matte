#include "native.h"
#include "defines.h"
#include <stdlib.h>
#include "../matte/src/matte_store.h"
#include "../matte/src/matte_string.h"


typedef struct {
    int typeTag;
    void * data;
} NativeEncodeData_t;

static void native_encode_finalizer(void * objectUserdata, void * functionUserdata) {
    NativeEncodeData_t * m = objectUserdata;
    free(m->data);
    free(m);
}




matteValue_t native_encode_pointer(matteVM_t * vm, void * ptr) {
    matteValue_t out;
    matteStore_t * store = matte_vm_get_store(vm);
    matteString_t * ptrStr = matte_string_create_from_c_str("%p", ptr);
    matte_value_into_string(store, &out, ptrStr);
    matte_string_destroy(ptrStr);
    return out;
}


matteValue_t native_encode_int(matteVM_t * vm, int value) {
    matteValue_t v;
    v.binID = MATTE_VALUE_TYPE_NUMBER;
    v.value.number = value;
    return v;
}

// convert into a simple object.
matteValue_t native_encode_image(matteVM_t * vm, const Image * img) {
    matteStore_t * store = matte_vm_get_store(vm);
    matteValue_t out = matte_store_new_value(store);
    matte_value_into_new_object_ref(store, &out);

    NativeEncodeData_t * imgd = calloc(1, sizeof(NativeEncodeData_t));
    imgd->data = calloc(1, sizeof(Image));
    imgd->typeTag = RAYMATTE_NATIVE_TYPE__IMAGE;
    
    matte_value_object_set_userdata(store, out, imgd);
    matte_value_object_set_native_finalizer(store, out, native_encode_finalizer, NULL);

    return out;
}


matteValue_t native_encode_vector2(matteVM_t * vm, Vector2 v2) {
    matteStore_t * store = matte_vm_get_store(vm);    

    matteValue_t x = matte_store_new_value(store);
    matteValue_t y = matte_store_new_value(store);

    matte_value_into_number(store, &x, v2.x);
    matte_value_into_number(store, &y, v2.y);

    matteValue_t v = matte_store_new_value(store);
    matte_value_into_new_object_ref(store, &v);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "x"), x);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "y"), y);

    return v;
}   








Image native_decode_image(matteVM_t * vm, matteValue_t img) {
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


Vector2 native_decode_vector2(matteVM_t * vm, matteValue_t v2) {
    matteStore_t * store = matte_vm_get_store(vm);    

    if (v2.binID != MATTE_VALUE_TYPE_OBJECT) {
        matte_vm_raise_error_cstring(vm, "Could not decode Image: value is not an Image.");
        Vector2 errOut = {};
        return errOut;
    }


    Vector2 v = {};
    v.x = matte_value_as_number(store, matte_value_object_access_string(store, v2, MATTE_VM_STR_CAST(vm, "x")));
    v.y = matte_value_as_number(store, matte_value_object_access_string(store, v2, MATTE_VM_STR_CAST(vm, "y")));

    return v;
}   









