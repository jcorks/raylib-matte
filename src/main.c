#include <string.h>
#include "../matte/src/matte.h"
#include "../matte/src/matte_string.h"
#include "../matte/src/matte_store.h"
#include "../matte/src/matte_array.h"
#include "defines.h"
#include "native.h"
#include <stdio.h>
#include <stdlib.h>



////// Helpers
// Defines to quickly deploy raylib bindings
#define RAYLIB_FN__ARG0(__T__) matteValue_t __T__(matteVM_t * vm, matteValue_t fn, const matteValue_t * args, void * userData) { matteStore_t * store = matte_vm_get_store(vm);
#define RAYLIB_FN__ARG1(__T__, __T0__) matteValue_t __T__(matteVM_t * vm, matteValue_t fn, const matteValue_t * args, void * userData) { matteStore_t * store = matte_vm_get_store(vm); if (!ensure_arg_types1(vm, args, __T0__)) return matte_store_new_value(store);
#define RAYLIB_FN__ARG2(__T__, __T0__, __T1__) matteValue_t __T__(matteVM_t * vm, matteValue_t fn, const matteValue_t * args, void * userData) { matteStore_t * store = matte_vm_get_store(vm); if (!ensure_arg_types2(vm, args, __T0__, __T1__)) return matte_store_new_value(store);
#define RAYLIB_FN__ARG3(__T__, __T0__, __T1__, __T2__) matteValue_t __T__(matteVM_t * vm, matteValue_t fn, const matteValue_t * args, void * userData) { matteStore_t * store = matte_vm_get_store(vm); if (!ensure_arg_types3(vm, args, __T0__, __T1__, __T2__)) return matte_store_new_value(store);
#define RAYLIB_FN__ARG4(__T__, __T0__, __T1__, __T2__, __T3__) matteValue_t __T__(matteVM_t * vm, matteValue_t fn, const matteValue_t * args, void * userData) { matteStore_t * store = matte_vm_get_store(vm); if (!ensure_arg_types4(vm, args, __T0__, __T1__, __T2__, __T3__)) return matte_store_new_value(store);
#define RAYLIB_FN__ARG5(__T__, __T0__, __T1__, __T2__, __T3__, __T4__) matteValue_t __T__(matteVM_t * vm, matteValue_t fn, const matteValue_t * args, void * userData) { matteStore_t * store = matte_vm_get_store(vm); if (!ensure_arg_types5(vm, args, __T0__, __T1__, __T2__, __T3__, __T4__)) return matte_store_new_value(store);
#define RAYLIB_FN__ARG6(__T__, __T0__, __T1__, __T2__, __T3__, __T4__, __T5__) matteValue_t __T__(matteVM_t * vm, matteValue_t fn, const matteValue_t * args, void * userData) { matteStore_t * store = matte_vm_get_store(vm); if (!ensure_arg_types6(vm, args, __T0__, __T1__, __T2__, __T3__, __T4__, __T5__)) return matte_store_new_value(store);
#define RAYLIB_FN__ARG7(__T__, __T0__, __T1__, __T2__, __T3__, __T4__, __T5__, __T6__) matteValue_t __T__(matteVM_t * vm, matteValue_t fn, const matteValue_t * args, void * userData) { matteStore_t * store = matte_vm_get_store(vm); if (!ensure_arg_types7(vm, args, __T0__, __T1__, __T2__, __T3__, __T4__, __T5__, __T6__)) return matte_store_new_value(store);
#define RAYLIB_FN__ARG8(__T__, __T0__, __T1__, __T2__, __T3__, __T4__, __T5__, __T6__, __T7__) matteValue_t __T__(matteVM_t * vm, matteValue_t fn, const matteValue_t * args, void * userData) { matteStore_t * store = matte_vm_get_store(vm); if (!ensure_arg_types8(vm, args, __T0__, __T1__, __T2__, __T3__, __T4__, __T5__, __T6__, __T7__)) return matte_store_new_value(store);
#define RAYLIB_FN__ARG9(__T__, __T0__, __T1__, __T2__, __T3__, __T4__, __T5__, __T6__, __T7__, __T8__) matteValue_t __T__(matteVM_t * vm, matteValue_t fn, const matteValue_t * args, void * userData) { matteStore_t * store = matte_vm_get_store(vm); if (!ensure_arg_types9(vm, args, __T0__, __T1__, __T2__, __T3__, __T4__, __T5__, __T6__, __T7__, __T8__)) return matte_store_new_value(store);
#define RAYLIB_FN__END return matte_store_new_value(store);}


// Input type checkers to raylib functions
static int ensure_arg_types1(matteVM_t * vm, const matteValue_t * args, int bin0) {
    if (args[0].binID != bin0) {
        matte_vm_raise_error_cstring(vm, "An argument was passed of an incorrect type.");
        return FALSE;
    }
    return TRUE;
}

static int ensure_arg_types2(matteVM_t * vm, const matteValue_t * args, int bin0, int bin1) {
    if (args[0].binID != bin0 ||
        args[1].binID != bin1) {
        matte_vm_raise_error_cstring(vm, "An argument was passed of an incorrect type.");
        return FALSE;
    }
    return TRUE;
}

static int ensure_arg_types3(matteVM_t * vm, const matteValue_t * args, int bin0, int bin1, int bin2) {
    if (args[0].binID != bin0 ||
        args[1].binID != bin1 ||
        args[2].binID != bin2) {
        matte_vm_raise_error_cstring(vm, "An argument was passed of an incorrect type.");
        return FALSE;
    }
    return TRUE;
}

static int ensure_arg_types4(matteVM_t * vm, const matteValue_t * args, int bin0, int bin1, int bin2, int bin3) {
    if (args[0].binID != bin0 ||
        args[1].binID != bin1 ||
        args[2].binID != bin2 ||
        args[3].binID != bin3) {
        matte_vm_raise_error_cstring(vm, "An argument was passed of an incorrect type.");
        return FALSE;
    }
    return TRUE;
}

static int ensure_arg_types5(matteVM_t * vm, const matteValue_t * args, int bin0, int bin1, int bin2, int bin3, int bin4) {
    if (args[0].binID != bin0 ||
        args[1].binID != bin1 ||
        args[2].binID != bin2 ||
        args[3].binID != bin3 ||
        args[4].binID != bin4) {
        matte_vm_raise_error_cstring(vm, "An argument was passed of an incorrect type.");
        return FALSE;
    }
    return TRUE;
}

static int ensure_arg_types6(matteVM_t * vm, const matteValue_t * args, int bin0, int bin1, int bin2, int bin3, int bin4, int bin5) {
    if (args[0].binID != bin0 ||
        args[1].binID != bin1 ||
        args[2].binID != bin2 ||
        args[3].binID != bin3 ||
        args[4].binID != bin4 ||
        args[5].binID != bin5) {
        matte_vm_raise_error_cstring(vm, "An argument was passed of an incorrect type.");
        return FALSE;
    }
    return TRUE;
}

static int ensure_arg_types7(matteVM_t * vm, const matteValue_t * args, int bin0, int bin1, int bin2, int bin3, int bin4, int bin5, int bin6) {
    if (args[0].binID != bin0 ||
        args[1].binID != bin1 ||
        args[2].binID != bin2 ||
        args[3].binID != bin3 ||
        args[4].binID != bin4 ||
        args[5].binID != bin5 ||
        args[6].binID != bin6) {
        matte_vm_raise_error_cstring(vm, "An argument was passed of an incorrect type.");
        return FALSE;
    }
    return TRUE;
}

static int ensure_arg_types8(matteVM_t * vm, const matteValue_t * args, int bin0, int bin1, int bin2, int bin3, int bin4, int bin5, int bin6, int bin7) {
    if (args[0].binID != bin0 ||
        args[1].binID != bin1 ||
        args[2].binID != bin2 ||
        args[3].binID != bin3 ||
        args[4].binID != bin4 ||
        args[5].binID != bin5 ||
        args[6].binID != bin6 ||
        args[7].binID != bin7) {
        matte_vm_raise_error_cstring(vm, "An argument was passed of an incorrect type.");
        return FALSE;
    }
    return TRUE;
}


static int ensure_arg_types9(matteVM_t * vm, const matteValue_t * args, int bin0, int bin1, int bin2, int bin3, int bin4, int bin5, int bin6, int bin7, int bin8) {
    if (args[0].binID != bin0 ||
        args[1].binID != bin1 ||
        args[2].binID != bin2 ||
        args[3].binID != bin3 ||
        args[4].binID != bin4 ||
        args[5].binID != bin5 ||
        args[6].binID != bin6 ||
        args[7].binID != bin7 ||
        args[8].binID != bin8) {
        matte_vm_raise_error_cstring(vm, "An argument was passed of an incorrect type.");
        return FALSE;
    }
    return TRUE;
}



////// Implementations


/* Struct interfacing for closed objects


*/



#define VARIABLE_TO_ARRAY(__ACCESS__,__COUNT__,__CONV__,__OUTPUT__)\
matteValue_t __OUTPUT__ = matte_store_new_value(store);\
{\
    uint32_t i;\
    matteValue_t * vals = MemAlloc(sizeof(matteValue_t) * (__COUNT__));\
    for(i = 0; i < (__COUNT__); ++i) {\
        vals[i] = __CONV__(vm, (__ACCESS__)[i]);\
    }\
    matteArray_t arrC = MATTE_ARRAY_CAST(vals, matteValue_t, __COUNT__);\
    matte_value_into_new_object_array_ref(store, &__OUTPUT__, &arrC);\
    MemFree(vals);\
}\




RAYLIB_FN__ARG1(raylib_ImageGetData, MATTE_VALUE_TYPE_OBJECT)
    Image img = native_from_value_image(vm, args[0]);
    return matte_vm_create_memory_buffer_handle_from_data(
        vm,
        img.data,
        GetPixelDataSize(img.height, img.width, img.format)
    );
RAYLIB_FN__END




RAYLIB_FN__ARG1(raylib_FontGetRecs, MATTE_VALUE_TYPE_OBJECT)
    Font f = native_from_value_font(vm, args[0]);
    VARIABLE_TO_ARRAY(
        f.recs,
        f.glyphCount,
        native_to_value_rectangle,
        output
    );
    return output;
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_FontGetGlyphs, MATTE_VALUE_TYPE_OBJECT)
    Font f = native_from_value_font(vm, args[0]);
    VARIABLE_TO_ARRAY(
        f.glyphs,
        f.glyphCount,
        native_to_value_glyphInfo,
        output
    );
    return output;
RAYLIB_FN__END





RAYLIB_FN__ARG1(raylib_MeshGetVertices, MATTE_VALUE_TYPE_OBJECT)
    Mesh mesh = native_from_value_mesh(vm, args[0]);
    return matte_vm_create_memory_buffer_handle_from_data(
        vm,
        (void*)mesh.vertices,
        mesh.vertexCount * sizeof(Vector3)
    );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_MeshGetTexCoords, MATTE_VALUE_TYPE_OBJECT)
    Mesh mesh = native_from_value_mesh(vm, args[0]);
    return matte_vm_create_memory_buffer_handle_from_data(
        vm,
        (void*)mesh.texcoords,
        mesh.vertexCount * sizeof(Vector2)
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_MeshGetTexCoords2, MATTE_VALUE_TYPE_OBJECT)
    Mesh mesh = native_from_value_mesh(vm, args[0]);
    return matte_vm_create_memory_buffer_handle_from_data(
        vm,
        (void*)mesh.texcoords2,
        mesh.vertexCount * sizeof(Vector2)
    );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_MeshGetNormals, MATTE_VALUE_TYPE_OBJECT)
    Mesh mesh = native_from_value_mesh(vm, args[0]);
    return matte_vm_create_memory_buffer_handle_from_data(
        vm,
        (void*)mesh.normals,
        mesh.vertexCount * sizeof(Vector3)
    );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_MeshGetTangents, MATTE_VALUE_TYPE_OBJECT)
    Mesh mesh = native_from_value_mesh(vm, args[0]);
    return matte_vm_create_memory_buffer_handle_from_data(
        vm,
        (void*)mesh.tangents,
        mesh.vertexCount * sizeof(Vector4)
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_MeshGetColors, MATTE_VALUE_TYPE_OBJECT)
    Mesh mesh = native_from_value_mesh(vm, args[0]);
    return matte_vm_create_memory_buffer_handle_from_data(
        vm,
        (void*)mesh.colors,
        mesh.vertexCount * 4
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_MeshGetIndices, MATTE_VALUE_TYPE_OBJECT)
    Mesh mesh = native_from_value_mesh(vm, args[0]);
    return matte_vm_create_memory_buffer_handle_from_data(
        vm,
        (void*)mesh.indices,
        mesh.vertexCount * sizeof(uint32_t)
    );
RAYLIB_FN__END



RAYLIB_FN__ARG1(raylib_MeshGetAnimVertices, MATTE_VALUE_TYPE_OBJECT)
    Mesh mesh = native_from_value_mesh(vm, args[0]);
    return matte_vm_create_memory_buffer_handle_from_data(
        vm,
        (void*)mesh.animVertices,
        mesh.vertexCount * sizeof(Vector3)
    );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_MeshGetAnimNormals, MATTE_VALUE_TYPE_OBJECT)
    Mesh mesh = native_from_value_mesh(vm, args[0]);
    return matte_vm_create_memory_buffer_handle_from_data(
        vm,
        (void*)mesh.animNormals,
        mesh.vertexCount * sizeof(Vector3)
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_MeshGetBoneIDs, MATTE_VALUE_TYPE_OBJECT)
    Mesh mesh = native_from_value_mesh(vm, args[0]);
    return matte_vm_create_memory_buffer_handle_from_data(
        vm,
        (void*)mesh.boneIds,
        mesh.vertexCount * 4
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_MeshGetBoneWeights, MATTE_VALUE_TYPE_OBJECT)
    Mesh mesh = native_from_value_mesh(vm, args[0]);
    return matte_vm_create_memory_buffer_handle_from_data(
        vm,
        (void*)mesh.boneWeights,
        mesh.vertexCount * 4 * sizeof(float)
    );
RAYLIB_FN__END





RAYLIB_FN__ARG1(raylib_ModelGetMeshes, MATTE_VALUE_TYPE_OBJECT)
    Model model = native_from_value_model(vm, args[0]);
    VARIABLE_TO_ARRAY(
        model.meshes,
        model.meshCount,
        native_to_value_mesh,
        output
    );
    return output;
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_ModelGetMaterials, MATTE_VALUE_TYPE_OBJECT)
    Model model = native_from_value_model(vm, args[0]);
    VARIABLE_TO_ARRAY(
        model.materials,
        model.materialCount,
        native_to_value_material,
        output
    );
    return output;
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_ModelGetMaterialNumbers, MATTE_VALUE_TYPE_OBJECT)
    Model model = native_from_value_model(vm, args[0]);
    VARIABLE_TO_ARRAY(
        model.meshMaterial,
        model.materialCount,
        native_to_value_int,
        output
    );
    return output;
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_ModelGetBones, MATTE_VALUE_TYPE_OBJECT)
    Model model = native_from_value_model(vm, args[0]);
    VARIABLE_TO_ARRAY(
        model.bones,
        model.boneCount,
        native_to_value_boneInfo,
        output
    );
    return output;
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_ModelGetBindPoses, MATTE_VALUE_TYPE_OBJECT)
    Model model = native_from_value_model(vm, args[0]);
    VARIABLE_TO_ARRAY(
        model.bindPose,
        model.boneCount,
        native_to_value_transform,
        output
    );
    return output;
RAYLIB_FN__END





RAYLIB_FN__ARG1(raylib_ModelAnimationGetBones, MATTE_VALUE_TYPE_OBJECT)
    ModelAnimation model = native_from_value_modelAnimation(vm, args[0]);
    VARIABLE_TO_ARRAY(
        model.bones,
        model.boneCount,
        native_to_value_boneInfo,
        output
    );
    return output;
RAYLIB_FN__END



RAYLIB_FN__ARG1(raylib_ModelAnimationGetFramePoses, MATTE_VALUE_TYPE_OBJECT)
    ModelAnimation model = native_from_value_modelAnimation(vm, args[0]);

    matteValue_t output = matte_store_new_value(store);
    {
        uint32_t i;
        matteValue_t * vals = MemAlloc(sizeof(matteValue_t) * (model.frameCount));
        for(i = 0; i < (model.frameCount); ++i) {
            matteValue_t sub = matte_store_new_value(store);
            {
                uint32_t n;
                matteValue_t * vals = MemAlloc(sizeof(matteValue_t) * (model.frameCount));
                for(n = 0; n < (model.frameCount); ++n) {
                    matteValue_t sub = matte_store_new_value(store);
                    
                    vals[n] = native_to_value_transform(vm, model.framePoses[i][n]);
                }
                matteArray_t arrC = MATTE_ARRAY_CAST(vals, matteValue_t, model.frameCount);
                matte_value_into_new_object_array_ref(store, &sub, &arrC);
                MemFree(vals);
            }            
            vals[i] = sub;
        }
        matteArray_t arrC = MATTE_ARRAY_CAST(vals, matteValue_t, model.frameCount);
        matte_value_into_new_object_array_ref(store, &output, &arrC);
        MemFree(vals);
    }

    return output;
RAYLIB_FN__END




RAYLIB_FN__ARG1(raylib_WaveGetData, MATTE_VALUE_TYPE_OBJECT)
    Wave wave = native_from_value_wave(vm, args[0]);
    return matte_vm_create_memory_buffer_handle_from_data(
        vm,
        wave.data,
        wave.frameCount * wave.channels * (wave.sampleSize / 8)
    );
RAYLIB_FN__END


/*
    rcore: Windowing


*/
RAYLIB_FN__ARG3(raylib_InitWindow,
    MATTE_VALUE_TYPE_NUMBER, 
    MATTE_VALUE_TYPE_NUMBER, 
    MATTE_VALUE_TYPE_STRING
)
    InitWindow(
        (int)args[0].value.number,
        (int)args[1].value.number,
        matte_string_get_c_str(matte_value_string_get_string_unsafe(store, args[2]))
    );
RAYLIB_FN__END




RAYLIB_FN__ARG0(raylib_WindowShouldClose)
    return native_to_value_boolean(vm, WindowShouldClose());
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_CloseWindow)
    CloseWindow();
RAYLIB_FN__END



RAYLIB_FN__ARG0(raylib_IsWindowReady)
    return native_to_value_boolean(vm, IsWindowReady());
RAYLIB_FN__END


RAYLIB_FN__ARG0(raylib_IsWindowFullscreen)
    return native_to_value_boolean(vm, IsWindowFullscreen());
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_IsWindowHidden)
    return native_to_value_boolean(vm, IsWindowHidden());
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_IsWindowMinimized)
    return native_to_value_boolean(vm, IsWindowMinimized());
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_IsWindowMaximized)
    return native_to_value_boolean(vm, IsWindowMaximized());
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_IsWindowFocused)
    return native_to_value_boolean(vm, IsWindowFocused());
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_IsWindowResized)
    return native_to_value_boolean(vm, IsWindowResized());
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_IsWindowState, MATTE_VALUE_TYPE_NUMBER)
    return native_to_value_boolean(vm, (unsigned int)args[0].value.number);
RAYLIB_FN__END



RAYLIB_FN__ARG1(raylib_SetWindowState, MATTE_VALUE_TYPE_NUMBER)
    SetWindowState((unsigned int)args[0].value.number);
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_ClearWindowState, MATTE_VALUE_TYPE_NUMBER)
    ClearWindowState((unsigned int)args[0].value.number);
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_ToggleFullscreen)
    ToggleFullscreen();
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_MaximizeWindow)
    MaximizeWindow();
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_MinimizeWindow)
    MinimizeWindow();
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_RestoreWindow)
    RestoreWindow();
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_SetWindowIcon, MATTE_VALUE_TYPE_OBJECT)
    SetWindowIcon(native_from_value_image(vm, args[0]));
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_SetWindowIcons, MATTE_VALUE_TYPE_OBJECT)
    matteArray_t * arr = matte_array_create(sizeof(Image));
    
    uint32_t i;
    uint32_t len = matte_value_object_get_number_key_count(store, args[0]);
    for(i = 0; i < len; ++i) {
        Image img = native_from_value_image(vm, matte_value_object_access_index(store, args[0], i));
        matte_array_push(arr, img);
    }
    
    SetWindowIcons(matte_array_get_data(arr), len);
    matte_array_destroy(arr);
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_SetWindowTitle, MATTE_VALUE_TYPE_STRING)
    SetWindowTitle(matte_string_get_c_str(matte_value_string_get_string_unsafe(store, args[0])));
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_SetWindowPosition, MATTE_VALUE_TYPE_NUMBER, MATTE_VALUE_TYPE_NUMBER)
    SetWindowPosition(
        args[0].value.number,
        args[1].value.number
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_SetWindowMonitor, MATTE_VALUE_TYPE_NUMBER) 
    SetWindowMonitor(
        (int)args[0].value.number
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_SetWindowMinSize, MATTE_VALUE_TYPE_NUMBER, MATTE_VALUE_TYPE_NUMBER)
    SetWindowMinSize(
        args[0].value.number,
        args[1].value.number
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_SetWindowSize, MATTE_VALUE_TYPE_NUMBER, MATTE_VALUE_TYPE_NUMBER) 
    SetWindowSize(
        args[0].value.number,
        args[1].value.number
    );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_SetWindowOpacity, MATTE_VALUE_TYPE_NUMBER) 
    SetWindowOpacity(
        args[0].value.number
    );
RAYLIB_FN__END


RAYLIB_FN__ARG0(raylib_GetScreenWidth) 
    return native_to_value_int(vm, GetScreenWidth());
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_GetScreenHeight) 
    return native_to_value_int(vm, GetScreenHeight());
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_GetRenderWidth) 
    return native_to_value_int(vm, GetRenderWidth());
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_GetRenderHeight) 
    return native_to_value_int(vm, GetRenderHeight());
RAYLIB_FN__END


RAYLIB_FN__ARG0(raylib_GetMonitorCount) 
    return native_to_value_int(vm, GetMonitorCount());
RAYLIB_FN__END


RAYLIB_FN__ARG0(raylib_GetCurrentMonitor)
    return native_to_value_int(vm, GetCurrentMonitor());
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_GetMonitorPosition, MATTE_VALUE_TYPE_NUMBER)
    return native_to_value_vector2(vm, GetMonitorPosition(args[0].value.number));
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_GetMonitorWidth, MATTE_VALUE_TYPE_NUMBER)
    return native_to_value_int(vm, GetMonitorWidth(args[0].value.number));
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_GetMonitorHeight, MATTE_VALUE_TYPE_NUMBER)
    return native_to_value_int(vm, GetMonitorHeight(args[0].value.number));
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_GetMonitorPhysicalWidth, MATTE_VALUE_TYPE_NUMBER)
    return native_to_value_int(vm, GetMonitorPhysicalWidth(args[0].value.number));
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_GetMonitorPhysicalHeight, MATTE_VALUE_TYPE_NUMBER) 
    return native_to_value_int(vm, GetMonitorPhysicalHeight(args[0].value.number));
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_GetMonitorRefreshRate, MATTE_VALUE_TYPE_NUMBER) 
    return native_to_value_int(vm, GetMonitorRefreshRate(args[0].value.number));
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_GetWindowPosition)
    return native_to_value_vector2(vm, GetWindowPosition());
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_GetWindowScaleDPI)
    return native_to_value_vector2(vm, GetWindowScaleDPI());
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_GetMonitorName, MATTE_VALUE_TYPE_NUMBER)
    return native_to_value_string(vm, GetMonitorName(args[0].value.number));
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_SetClipboardText, MATTE_VALUE_TYPE_STRING)
    SetClipboardText(matte_string_get_c_str(matte_value_string_get_string_unsafe(store, args[0])));
RAYLIB_FN__END


RAYLIB_FN__ARG0(raylib_GetClipboardText)
    return native_to_value_string(vm, GetClipboardText());
RAYLIB_FN__END


RAYLIB_FN__ARG0(raylib_EnableEventWaiting)
    EnableEventWaiting();
RAYLIB_FN__END


RAYLIB_FN__ARG0(raylib_DisableEventWaiting)
    DisableEventWaiting();
RAYLIB_FN__END



// Custom frame control
RAYLIB_FN__ARG0(raylib_SwapScreenBuffer)
    SwapScreenBuffer();
RAYLIB_FN__END 


RAYLIB_FN__ARG0(raylib_PollInputEvents)
    PollInputEvents();
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_WaitTime, MATTE_VALUE_TYPE_NUMBER)
    WaitTime(args[0].value.number);
RAYLIB_FN__END


// Cursor functions

RAYLIB_FN__ARG0(raylib_ShowCursor)
    ShowCursor();
RAYLIB_FN__END


RAYLIB_FN__ARG0(raylib_HideCursor) 
    HideCursor();
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_IsCursorHidden) 
    return native_to_value_boolean(vm, IsCursorHidden());
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_EnableCursor)
   EnableCursor();
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_DisableCursor)
   DisableCursor();
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_IsCursorOnScreen) 
    return native_to_value_boolean(vm, IsCursorOnScreen());
RAYLIB_FN__END



// Drawing functions 

RAYLIB_FN__ARG1(raylib_ClearBackground, MATTE_VALUE_TYPE_OBJECT)
    ClearBackground(native_from_value_color(vm, args[0]));
RAYLIB_FN__END


RAYLIB_FN__ARG0(raylib_BeginDrawing)
    BeginDrawing();
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_EndDrawing)
    EndDrawing();
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_BeginMode2D, MATTE_VALUE_TYPE_OBJECT)
    BeginMode2D(native_from_value_camera2D(vm, args[0]));
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_EndMode2D)
    EndMode2D();
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_BeginMode3D, MATTE_VALUE_TYPE_OBJECT)
    BeginMode3D(native_from_value_camera(vm, args[0]));
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_EndMode3D)
    EndMode3D();
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_BeginTextureMode, MATTE_VALUE_TYPE_OBJECT)
    BeginTextureMode(native_from_value_renderTexture(vm, args[0]));
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_EndTextureMode)
    EndTextureMode();
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_BeginShaderMode, MATTE_VALUE_TYPE_OBJECT)
    BeginShaderMode(native_from_value_shader(vm, args[0]));
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_EndShaderMode)
    EndShaderMode();
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_BeginBlendMode, MATTE_VALUE_TYPE_NUMBER)
    BeginBlendMode(args[0].value.number);
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_EndBlendMode)
    EndBlendMode();
RAYLIB_FN__END


RAYLIB_FN__ARG4(raylib_BeginScissorMode, 
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    BeginScissorMode(
        args[0].value.number,
        args[1].value.number,
        args[2].value.number,
        args[3].value.number
    );
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_EndScissorMode)
   EndScissorMode();
RAYLIB_FN__END


// TODO: vrstereoconfig / mode



RAYLIB_FN__ARG2(raylib_LoadShader, MATTE_VALUE_TYPE_STRING, MATTE_VALUE_TYPE_STRING)
    return native_to_value_shader(
        vm,
        LoadShader(
            matte_string_get_c_str(matte_value_string_get_string_unsafe(store, args[0])),
            matte_string_get_c_str(matte_value_string_get_string_unsafe(store, args[1]))
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_LoadShaderFromMemory, MATTE_VALUE_TYPE_STRING, MATTE_VALUE_TYPE_STRING)
    return native_to_value_shader(
        vm,
        LoadShaderFromMemory(
            matte_string_get_c_str(matte_value_string_get_string_unsafe(store, args[0])),
            matte_string_get_c_str(matte_value_string_get_string_unsafe(store, args[1]))
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_IsShaderReady, MATTE_VALUE_TYPE_OBJECT)
    return native_to_value_boolean(
        vm,
        IsShaderReady(
            native_from_value_shader(vm, args[0])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_GetShaderLocation, 
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_STRING
)
    return native_to_value_int(
        vm,
        GetShaderLocation(
            native_from_value_shader(vm, args[0]),
            native_from_value_string_unsafe(vm, args[1]) // checked, OK!
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_GetShaderLocationAttrib, 
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_STRING
)
    return native_to_value_int(
        vm,
        GetShaderLocationAttrib(
            native_from_value_shader(vm, args[0]),
            native_from_value_string_unsafe(vm, args[1]) // checked, OK!
        )
    );
RAYLIB_FN__END




RAYLIB_FN__ARG3(raylib_SetShaderValueFloat, 
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)

    uint32_t len = matte_value_object_get_number_key_count(store, args[2]);
    if (len == 0) goto L_END;
    float * vals = calloc(len, sizeof(float));
    int i;
    for(i = 0; i < len; ++i) {
        vals[i] = matte_value_as_number(
            store,
            matte_value_object_access_index(
                store,
                args[2],
                i
            )
        );
    }

    int uniformType;
    switch(len) {
        case 1:  uniformType = SHADER_UNIFORM_FLOAT; break;
        case 2:  uniformType = SHADER_UNIFORM_VEC2; break;
        case 3:  uniformType = SHADER_UNIFORM_VEC3; break;
        default: uniformType = SHADER_UNIFORM_VEC4; break;
    }        

    SetShaderValue(
        native_from_value_shader(vm, args[0]),
        args[1].value.number,
        vals,
        uniformType
    );
    
    free(vals);
  L_END:
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_SetShaderValueInt, 
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)

    uint32_t len = matte_value_object_get_number_key_count(store, args[2]);
    if (len == 0) goto L_END;
    int * vals = calloc(len, sizeof(float));
    int i;
    for(i = 0; i < len; ++i) {
        vals[i] = matte_value_as_number(
            store,
            matte_value_object_access_index(
                store,
                args[2],
                i
            )
        );
    }

    int uniformType;
    switch(len) {
        case 1:  uniformType = SHADER_UNIFORM_INT; break;
        case 2:  uniformType = SHADER_UNIFORM_IVEC2; break;
        case 3:  uniformType = SHADER_UNIFORM_IVEC3; break;
        default: uniformType = SHADER_UNIFORM_IVEC4; break;
    }        

    SetShaderValue(
        native_from_value_shader(vm, args[0]),
        args[1].value.number,
        vals,
        uniformType
    );
    
    free(vals);
  L_END:
RAYLIB_FN__END



RAYLIB_FN__ARG4(raylib_SetShaderValueFloatV, 
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)

    uint32_t len = matte_value_object_get_number_key_count(store, args[2]);
    if (len == 0) goto L_END;
    uint32_t numComponents = args[3].value.number;
    if (numComponents == 0 || numComponents > 4)
        goto L_END;
        
    float * vals = calloc(len, sizeof(float));
    int i;
    for(i = 0; i < len; ++i) {
        vals[i] = matte_value_as_number(
            store,
            matte_value_object_access_index(
                store,
                args[2],
                i
            )
        );
    }
    
    if (len % numComponents == 0) {

        int uniformType;
        switch(numComponents) {
            case 1:  uniformType = SHADER_UNIFORM_FLOAT; break;
            case 2:  uniformType = SHADER_UNIFORM_VEC2; break;
            case 3:  uniformType = SHADER_UNIFORM_VEC3; break;
            default: uniformType = SHADER_UNIFORM_VEC4; break;
        }        

        SetShaderValueV(
            native_from_value_shader(vm, args[0]),
            args[1].value.number,
            vals,
            uniformType,
            len / numComponents
        );
    } else {
        // non-even subdivide. Could cause undefined behavior
        matte_vm_raise_error_cstring(vm, "Uneven number of values in SetShaderValueFloatV. Check number of values in input array.");    
    }
    
    free(vals);
  L_END:
RAYLIB_FN__END




RAYLIB_FN__ARG4(raylib_SetShaderValueIntV, 
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)

    uint32_t len = matte_value_object_get_number_key_count(store, args[2]);
    if (len == 0) goto L_END;
    uint32_t numComponents = args[3].value.number;
    if (numComponents == 0 || numComponents > 4)
        goto L_END;
        
    int * vals = calloc(len, sizeof(int));
    int i;
    for(i = 0; i < len; ++i) {
        vals[i] = matte_value_as_number(
            store,
            matte_value_object_access_index(
                store,
                args[2],
                i
            )
        );
    }
    
    if (len % numComponents == 0) {

        int uniformType;
        switch(numComponents) {
            case 1:  uniformType = SHADER_UNIFORM_INT; break;
            case 2:  uniformType = SHADER_UNIFORM_IVEC2; break;
            case 3:  uniformType = SHADER_UNIFORM_IVEC3; break;
            default: uniformType = SHADER_UNIFORM_IVEC4; break;
        }        

        SetShaderValueV(
            native_from_value_shader(vm, args[0]),
            args[1].value.number,
            vals,
            uniformType,
            len / numComponents
        );
    } else {
        // non-even subdivide. Could cause undefined behavior
        matte_vm_raise_error_cstring(vm, "Uneven number of values in SetShaderValueFloatV. Check number of values in input array.");    
    }
    
    free(vals);
  L_END:
RAYLIB_FN__END



RAYLIB_FN__ARG3(raylib_SetShaderValueSampler2D, 
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    int id = args[2].value.number;
    SetShaderValue(
        native_from_value_shader(vm, args[0]),
        args[1].value.number,
        &id,
        SHADER_UNIFORM_SAMPLER2D    
    );
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_SetShaderValueSampler2DV, 
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)

    uint32_t len = matte_value_object_get_number_key_count(store, args[2]);
    if (len == 0) goto L_END;
    int * vals = calloc(len, sizeof(int));
    int i;
    for(i = 0; i < len; ++i) {
        vals[i] = matte_value_as_number(
            store,
            matte_value_object_access_index(
                store,
                args[2],
                i
            )
        );
    }


    int id = args[2].value.number;
    SetShaderValueV(
        native_from_value_shader(vm, args[0]),
        args[1].value.number,
        &id,
        SHADER_UNIFORM_SAMPLER2D,
        len
    );
    
    free(vals);
  L_END:
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_SetShaderValueMatrix, 
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    Matrix mat = native_from_value_matrix(vm, args[2]);
    SetShaderValueMatrix(
        native_from_value_shader(vm, args[0]),
        args[1].value.number,
        mat
    );
RAYLIB_FN__END

RAYLIB_FN__ARG3(raylib_SetShaderValueTexture, 
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    Texture2D tex = native_from_value_texture(vm, args[2]);
    SetShaderValueTexture(
        native_from_value_shader(vm, args[0]),
        args[1].value.number,
        tex
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_UnloadShader, 
    MATTE_VALUE_TYPE_OBJECT
)
    Shader sh = native_from_value_shader(vm, args[0]);
    UnloadShader(sh);
    native_unload(vm, args[0]); // safety
RAYLIB_FN__END




/// Screen-space-related functions 

RAYLIB_FN__ARG2(raylib_GetMouseRay, 
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_ray(
        vm,
        GetMouseRay(
            native_from_value_vector2(vm, args[0]),
            native_from_value_camera(vm, args[1])
        )
    );
RAYLIB_FN__END



RAYLIB_FN__ARG1(raylib_GetCameraMatrix, 
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_matrix(
        vm,
        GetCameraMatrix(
            native_from_value_camera(vm, args[0])
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_GetCameraMatrix2D, 
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_matrix(
        vm,
        GetCameraMatrix2D(
            native_from_value_camera2D(vm, args[0])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_GetWorldToScreen, 
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_vector2(
        vm,
        GetWorldToScreen(
            native_from_value_vector3(vm, args[0]),
            native_from_value_camera(vm, args[1])
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_GetScreenToWorld2D, 
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_vector2(
        vm,
        GetScreenToWorld2D(
            native_from_value_vector2(vm, args[0]),
            native_from_value_camera2D(vm, args[1])
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG4(raylib_GetWorldToScreenEx, 
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER    
)
    return native_to_value_vector2(
        vm,
        GetWorldToScreenEx(
            native_from_value_vector3(vm, args[0]),
            native_from_value_camera(vm, args[1]),
            args[2].value.number,
            args[3].value.number
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_GetWorldToScreen2D, 
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_vector2(
        vm,
        GetWorldToScreen2D(
            native_from_value_vector2(vm, args[0]),
            native_from_value_camera2D(vm, args[1])
        )
    );
RAYLIB_FN__END







// Timing-related functions 
RAYLIB_FN__ARG1(raylib_SetTargetFPS, MATTE_VALUE_TYPE_NUMBER)
    SetTargetFPS(args[0].value.number);
RAYLIB_FN__END


RAYLIB_FN__ARG0(raylib_GetFPS)
    return native_to_value_int(vm, 
        GetFPS()
    );
RAYLIB_FN__END


RAYLIB_FN__ARG0(raylib_GetFrameTime)
    return native_to_value_float(vm, 
        GetFrameTime()
    );
RAYLIB_FN__END


RAYLIB_FN__ARG0(raylib_GetTime)
    return native_to_value_float(vm, 
        GetTime()
    );
RAYLIB_FN__END









// Misc Functions 

RAYLIB_FN__ARG2(raylib_GetRandomValue,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_int(
        vm,
        GetRandomValue(
            args[0].value.number,
            args[1].value.number
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_SetRandomSeed,
    MATTE_VALUE_TYPE_NUMBER
)
    SetRandomSeed(
        args[0].value.number
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_TakeScreenshot,
    MATTE_VALUE_TYPE_STRING
)
    TakeScreenshot(
        native_from_value_string_unsafe(vm, args[0]) // ok!
    );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_SetConfigFlags,
    MATTE_VALUE_TYPE_NUMBER
)
    SetConfigFlags(
        args[0].value.number
    );
RAYLIB_FN__END



RAYLIB_FN__ARG2(raylib_TraceLog,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_STRING
)
    TraceLog(
        args[0].value.number,
        native_from_value_string_unsafe(vm, args[1]) // ok!
    );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_SetTraceLogLevel,
    MATTE_VALUE_TYPE_NUMBER
)
    SetTraceLogLevel(
        args[0].value.number
    );
RAYLIB_FN__END



RAYLIB_FN__ARG1(raylib_OpenURL,
    MATTE_VALUE_TYPE_STRING
)
    OpenURL(
        native_from_value_string_unsafe(vm, args[0]) // ok!
    );
RAYLIB_FN__END




// File management functions

RAYLIB_FN__ARG1(raylib_LoadFileData,
    MATTE_VALUE_TYPE_STRING
)
    unsigned int size = 0;
    unsigned char * data = LoadFileData(
        native_from_value_string_unsafe(vm, args[0]), // ok!
        &size
    );
    if (!data) size = 0;
    
    matteValue_t output = matte_vm_create_memory_buffer_handle_from_data(
        vm,
        data,
        size
    );
    
    UnloadFileData(data);

    return output;
RAYLIB_FN__END



RAYLIB_FN__ARG2(raylib_SaveFileData,
    MATTE_VALUE_TYPE_STRING,
    MATTE_VALUE_TYPE_OBJECT
)
    uint32_t size = 0;
    const uint8_t * data = matte_vm_get_memory_buffer_handle_raw_data(
        vm,
        args[0],
        &size
    );
    
    if (!data) size = 0;
    if (size == 0) goto L_END;
    
    
    return native_to_value_boolean(vm, 
        SaveFileData(
            native_from_value_string_unsafe(vm, args[0]), // ok!
            (void*)data,
            size
        )
    );
  L_END:
    return native_to_value_boolean(vm, FALSE);
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_ExportDataAsCode,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_STRING
)
    uint32_t size = 0;
    const uint8_t * data = matte_vm_get_memory_buffer_handle_raw_data(
        vm,
        args[0],
        &size
    );
    
    if (!data) size = 0;
    if (size == 0) goto L_END;
    
    
    return native_to_value_boolean(vm, ExportDataAsCode(
        data,
        size,
        native_from_value_string_unsafe(vm, args[0]) // ok!
    ));
  L_END:
    return native_to_value_boolean(vm, FALSE);
RAYLIB_FN__END




RAYLIB_FN__ARG1(raylib_LoadFileText,
    MATTE_VALUE_TYPE_STRING
)
    char * str = LoadFileText(native_from_value_string_unsafe(vm, args[0])); // ok!
    matteValue_t strv = native_to_value_string(vm, str);
    UnloadFileText(str);
    return strv;    
RAYLIB_FN__END



RAYLIB_FN__ARG2(raylib_SaveFileText,
    MATTE_VALUE_TYPE_STRING,
    MATTE_VALUE_TYPE_STRING
)
    return native_to_value_boolean(
        vm,
        SaveFileText(
            native_from_value_string_unsafe(vm, args[0]), // ok!
            (char*)native_from_value_string_unsafe(vm, args[1]) // ok! but for some reason SaveFileText() takes an input string that isnt const
        )
    );   
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_FileExists,
    MATTE_VALUE_TYPE_STRING
)
    return native_to_value_boolean(
        vm,
        FileExists(
            native_from_value_string_unsafe(vm, args[0]) // ok!
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_DirectoryExists,
    MATTE_VALUE_TYPE_STRING
)
    return native_to_value_boolean(
        vm,
        DirectoryExists(
            native_from_value_string_unsafe(vm, args[0]) // ok!
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_IsFileExtension,
    MATTE_VALUE_TYPE_STRING,
    MATTE_VALUE_TYPE_STRING
)
    return native_to_value_boolean(
        vm,
        IsFileExtension(
            native_from_value_string_unsafe(vm, args[0]), // ok!
            native_from_value_string_unsafe(vm, args[1]) // ok!
        )
    );   
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_GetFileLength,
    MATTE_VALUE_TYPE_STRING
)
    return native_to_value_int(
        vm,
        GetFileLength(
            native_from_value_string_unsafe(vm, args[0]) // ok!
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_GetFileExtension,
    MATTE_VALUE_TYPE_STRING
)
    return native_to_value_string(
        vm,
        GetFileExtension(
            native_from_value_string_unsafe(vm, args[0]) // ok!
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_GetFileName,
    MATTE_VALUE_TYPE_STRING
)
    return native_to_value_string(
        vm,
        GetFileName(
            native_from_value_string_unsafe(vm, args[0]) // ok!
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_GetFileNameWithoutExt,
    MATTE_VALUE_TYPE_STRING
)
    return native_to_value_string(
        vm,
        GetFileNameWithoutExt(
            native_from_value_string_unsafe(vm, args[0]) // ok!
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_GetDirectoryPath,
    MATTE_VALUE_TYPE_STRING
)
    return native_to_value_string(
        vm,
        GetDirectoryPath(
            native_from_value_string_unsafe(vm, args[0]) // ok!
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_GetPrevDirectoryPath,
    MATTE_VALUE_TYPE_STRING
)
    return native_to_value_string(
        vm,
        GetPrevDirectoryPath(
            native_from_value_string_unsafe(vm, args[0]) // ok!
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG0(raylib_GetWorkingDirectory
)
    return native_to_value_string(
        vm,
        GetWorkingDirectory(
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_GetApplicationDirectory
)
    return native_to_value_string(
        vm,
        GetApplicationDirectory(
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_ChangeDirectory,
    MATTE_VALUE_TYPE_STRING
)
    return native_to_value_boolean(
        vm,
        ChangeDirectory(
            native_from_value_string_unsafe(vm, args[0]) // ok!
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_IsPathFile,
    MATTE_VALUE_TYPE_STRING
)
    return native_to_value_boolean(
        vm,
        IsPathFile(
            native_from_value_string_unsafe(vm, args[0]) // ok!
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_LoadDirectoryFiles,
    MATTE_VALUE_TYPE_STRING
)
    FilePathList list = LoadDirectoryFiles(native_from_value_string_unsafe(vm, args[0]));
    matteValue_t output = native_to_value_filePathList_reduced(vm, list);
    UnloadDirectoryFiles(list);
    return output;
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_LoadDirectoryFilesEx,
    MATTE_VALUE_TYPE_STRING,
    MATTE_VALUE_TYPE_STRING,
    MATTE_VALUE_TYPE_BOOLEAN
)
    FilePathList list = LoadDirectoryFilesEx(
        native_from_value_string_unsafe(vm, args[0]), // ok!
        native_from_value_string_unsafe(vm, args[1]), // ok!
        args[0].value.boolean
    );
    matteValue_t output = native_to_value_filePathList_reduced(vm, list);
    UnloadDirectoryFiles(list);
    return output;
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_IsFileDropped
)
    return native_to_value_boolean(
        vm,
        IsFileDropped(
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_LoadDroppedFiles
)
    FilePathList list = LoadDroppedFiles(
    );
    matteValue_t output = native_to_value_filePathList_reduced(vm, list);
    UnloadDroppedFiles(list);
    return output;
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_GetFileModTime,
    MATTE_VALUE_TYPE_STRING
)
    return native_to_value_double(
        vm,
        GetFileModTime(
            native_from_value_string_unsafe(vm, args[0]) // ok!
        )
    );
RAYLIB_FN__END




// Compression / Encoding 
RAYLIB_FN__ARG1(raylib_CompressData,
    MATTE_VALUE_TYPE_OBJECT
)
    uint32_t sizeSrc = 0;
    const uint8_t * dataSrc = matte_vm_get_memory_buffer_handle_raw_data(
        vm,
        args[0],
        &sizeSrc
    );
    if (!dataSrc || sizeSrc == 0)
        goto L_END;


    unsigned int sizeOut;
    unsigned char * dataOut = CompressData(dataSrc, sizeSrc, &sizeOut);


    matteValue_t output = matte_vm_create_memory_buffer_handle_from_data(
        vm,
        dataOut,
        sizeOut
    );    
    
    MemFree(dataOut);
    return output;
  L_END:
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_DecompressData,
    MATTE_VALUE_TYPE_OBJECT
)
    uint32_t sizeSrc = 0;
    const uint8_t * dataSrc = matte_vm_get_memory_buffer_handle_raw_data(
        vm,
        args[0],
        &sizeSrc
    );
    if (!dataSrc || sizeSrc == 0)
        goto L_END;


    unsigned int sizeOut;
    unsigned char * dataOut = DecompressData(dataSrc, sizeSrc, &sizeOut);


    matteValue_t output = matte_vm_create_memory_buffer_handle_from_data(
        vm,
        dataOut,
        sizeOut
    );    
    
    MemFree(dataOut);
    return output;
  L_END:
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_EncodeDataBase64,
    MATTE_VALUE_TYPE_OBJECT
)
    uint32_t sizeSrc = 0;
    const uint8_t * dataSrc = matte_vm_get_memory_buffer_handle_raw_data(
        vm,
        args[0],
        &sizeSrc
    );
    if (!dataSrc || sizeSrc == 0)
        goto L_END;


    unsigned int sizeOut;
    char * dataOut = EncodeDataBase64(dataSrc, sizeSrc, &sizeOut);

    // data is NOT null-terminated.... Sigh...
    char * dataOutCStr = MemAlloc(sizeOut+1);
    memcpy(dataOutCStr, dataOut, sizeOut);
    dataOutCStr[sizeOut] = 0;
    MemFree(dataOut);
    
    
    matteValue_t val = native_to_value_string(vm, dataOutCStr);
    MemFree(dataOutCStr);
    return val;
  L_END:
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_DecodeDataBase64,
    MATTE_VALUE_TYPE_STRING
)

    unsigned int sizeOut;
    unsigned char * dataOut = DecodeDataBase64(
        native_from_value_string_unsafe(vm, args[0]), // ok! 
        &sizeOut);


    matteValue_t output = matte_vm_create_memory_buffer_handle_from_data(
        vm,
        dataOut,
        sizeOut
    );    
    
    MemFree(dataOut);
    return output;
  L_END:
RAYLIB_FN__END




// input keyboard
RAYLIB_FN__ARG1(raylib_IsKeyPressed,
    MATTE_VALUE_TYPE_NUMBER
)
    return 
        native_to_value_boolean(
            vm,
            IsKeyPressed(
                args[0].value.number 
            )
        );
RAYLIB_FN__END



RAYLIB_FN__ARG1(raylib_IsKeyDown,
    MATTE_VALUE_TYPE_NUMBER
)
    return 
        native_to_value_boolean(
            vm,
            IsKeyDown(
                args[0].value.number 
            )
        );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_IsKeyReleased,
    MATTE_VALUE_TYPE_NUMBER
)
    return 
        native_to_value_boolean(
            vm,
            IsKeyReleased(
                args[0].value.number 
            )
        );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_IsKeyUp,
    MATTE_VALUE_TYPE_NUMBER
)
    return 
        native_to_value_boolean(
            vm,
            IsKeyUp(
                args[0].value.number 
            )
        );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_SetExitKey,
    MATTE_VALUE_TYPE_NUMBER
)
    SetExitKey(
        args[0].value.number
    );
RAYLIB_FN__END


RAYLIB_FN__ARG0(raylib_GetKeyPressed
)
    return 
        native_to_value_int(
            vm,
            GetKeyPressed(
            )
        );
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_GetCharPressed
)
    return 
        native_to_value_int(
            vm,
            GetCharPressed(
            )
        );
RAYLIB_FN__END










// input: gamepads


RAYLIB_FN__ARG1(raylib_IsGamepadAvailable,
    MATTE_VALUE_TYPE_NUMBER
)
    return 
        native_to_value_boolean(
            vm,
            IsGamepadAvailable(
                args[0].value.number 
            )
        );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_GetGamepadName,
    MATTE_VALUE_TYPE_NUMBER
)
    return 
        native_to_value_string(
            vm,
            GetGamepadName(
                args[0].value.number 
            )
        );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_IsGamepadButtonPressed,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    return 
        native_to_value_boolean(
            vm,
            IsGamepadButtonPressed(
                args[0].value.number,
                args[1].value.number
            )
        );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_IsGamepadButtonDown,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    return 
        native_to_value_boolean(
            vm,
            IsGamepadButtonDown(
                args[0].value.number,
                args[1].value.number
            )
        );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_IsGamepadButtonReleased,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    return 
        native_to_value_boolean(
            vm,
            IsGamepadButtonReleased(
                args[0].value.number,
                args[1].value.number
            )
        );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_IsGamepadButtonUp,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    return 
        native_to_value_boolean(
            vm,
            IsGamepadButtonUp(
                args[0].value.number,
                args[1].value.number
            )
        );
RAYLIB_FN__END


RAYLIB_FN__ARG0(raylib_GetGamepadButtonPressed
)
    return 
        native_to_value_int(
            vm,
            GetGamepadButtonPressed(
            )
        );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_GetGamepadAxisCount,
    MATTE_VALUE_TYPE_NUMBER
)
    return 
        native_to_value_int(
            vm,
            GetGamepadAxisCount(
                args[0].value.number 
            )
        );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_GetGamepadAxisMovement,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    return 
        native_to_value_float(
            vm,
            GetGamepadAxisMovement(
                args[0].value.number,
                args[1].value.number
            )
        );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_SetGamepadMappings,
    MATTE_VALUE_TYPE_STRING
)
    return 
        native_to_value_int(
            vm,
            SetGamepadMappings(
                native_from_value_string_unsafe(vm, args[0]) // ok!
            )
        );
RAYLIB_FN__END




// input: mouse

RAYLIB_FN__ARG1(raylib_IsMouseButtonPressed,
    MATTE_VALUE_TYPE_NUMBER
)
    return 
        native_to_value_boolean(
            vm,
            IsMouseButtonPressed(
                args[0].value.number 
            )
        );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_IsMouseButtonDown,
    MATTE_VALUE_TYPE_NUMBER
)
    return 
        native_to_value_boolean(
            vm,
            IsMouseButtonDown(
                args[0].value.number 
            )
        );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_IsMouseButtonReleased,
    MATTE_VALUE_TYPE_NUMBER
)
    return 
        native_to_value_boolean(
            vm,
            IsMouseButtonReleased(
                args[0].value.number 
            )
        );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_IsMouseButtonUp,
    MATTE_VALUE_TYPE_NUMBER
)
    return 
        native_to_value_boolean(
            vm,
            IsMouseButtonUp(
                args[0].value.number 
            )
        );
RAYLIB_FN__END







RAYLIB_FN__ARG0(raylib_GetMouseX
)
    return 
        native_to_value_int(
            vm,
            GetMouseX(
            )
        );
RAYLIB_FN__END


RAYLIB_FN__ARG0(raylib_GetMouseY
)
    return 
        native_to_value_int(
            vm,
            GetMouseY(
            )
        );
RAYLIB_FN__END



RAYLIB_FN__ARG0(raylib_GetMousePosition
)
    return 
        native_to_value_vector2(
            vm,
            GetMousePosition(
            )
        );
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_GetMouseDelta
)
    return 
        native_to_value_vector2(
            vm,
            GetMouseDelta(
            )
        );
RAYLIB_FN__END



RAYLIB_FN__ARG2(raylib_SetMousePosition,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    SetMousePosition(
        args[0].value.number,
        args[1].value.number
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_SetMouseOffset,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    SetMouseOffset(
        args[0].value.number,
        args[1].value.number
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_SetMouseScale,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    SetMouseScale(
        args[0].value.number,
        args[1].value.number
    );
RAYLIB_FN__END


RAYLIB_FN__ARG0(raylib_GetMouseWheelMove
)
    return 
        native_to_value_float(
            vm,
            GetMouseWheelMove(
            )
        );
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_GetMouseWheelMoveV
)
    return 
        native_to_value_vector2(
            vm,
            GetMouseWheelMoveV(
            )
        );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_SetMouseCursor,
    MATTE_VALUE_TYPE_NUMBER
)
    SetMouseCursor(
        args[0].value.number
    );
RAYLIB_FN__END






// input: touch
RAYLIB_FN__ARG0(raylib_GetTouchX
)
    return 
        native_to_value_int(
            vm,
            GetTouchX(
            )
        );
RAYLIB_FN__END


RAYLIB_FN__ARG0(raylib_GetTouchY
)
    return 
        native_to_value_int(
            vm,
            GetTouchY(
            )
        );
RAYLIB_FN__END



RAYLIB_FN__ARG1(raylib_GetTouchPosition,
    MATTE_VALUE_TYPE_NUMBER
)
    return 
        native_to_value_vector2(
            vm,
            GetTouchPosition(
                args[0].value.number
            )
        );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_GetTouchPointId,
    MATTE_VALUE_TYPE_NUMBER
)
    return 
        native_to_value_int(
            vm,
            GetTouchPointId(
                args[0].value.number
            )
        );
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_GetTouchPointCount
)
    return 
        native_to_value_int(
            vm,
            GetTouchPointCount(
            )
        );
RAYLIB_FN__END







// input gestures

RAYLIB_FN__ARG1(raylib_SetGesturesEnabled,
    MATTE_VALUE_TYPE_NUMBER
)
    SetGesturesEnabled(
        args[0].value.number
    );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_IsGestureDetected,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_boolean(
        vm,
        IsGestureDetected(
            args[0].value.number
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_GetGestureDetected
)
    return native_to_value_int(
        vm,
        GetGestureDetected(
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG0(raylib_GetGestureHoldDuration
)
    return native_to_value_float(
        vm,
        GetGestureHoldDuration(
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_GetGestureDragVector
)
    return native_to_value_vector2(
        vm,
        GetGestureDragVector(
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG0(raylib_GetGestureDragAngle
)
    return native_to_value_float(
        vm,
        GetGestureDragAngle(
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_GetGesturePinchVector
)
    return native_to_value_vector2(
        vm,
        GetGesturePinchVector(
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_GetGesturePinchAngle
)
    return native_to_value_float(
        vm,
        GetGesturePinchAngle(
        )
    );
RAYLIB_FN__END








RAYLIB_FN__ARG2(raylib_UpdateCamera,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    Camera cam = native_from_value_camera(vm, args[0]);
    UpdateCamera(
        &cam,
        args[1].value.number
    );
    
    native_update_value_camera(vm, args[0], cam);
RAYLIB_FN__END



RAYLIB_FN__ARG4(raylib_UpdateCameraPro,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    Camera cam = native_from_value_camera(vm, args[0]);
    UpdateCameraPro(
        &cam,   
        native_from_value_vector3(vm, args[1]),
        native_from_value_vector3(vm, args[2]),
        args[3].value.number
    );
    
    native_update_value_camera(vm, args[0], cam);
RAYLIB_FN__END





// rshapes 
RAYLIB_FN__ARG2(raylib_SetShapesTexture,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    SetShapesTexture(
        native_from_value_texture(vm, args[0]),
        native_from_value_rectangle(vm, args[1])
    );
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_DrawPixel,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawPixel(  
        args[0].value.number,
        args[1].value.number,
        native_from_value_color(vm, args[2])
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_DrawPixelV,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawPixelV(  
        native_from_value_vector2(vm, args[0]),
        native_from_value_color(vm, args[1])
    );
RAYLIB_FN__END

RAYLIB_FN__ARG5(raylib_DrawLine,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawLine(  
        args[0].value.number,
        args[1].value.number,
        args[2].value.number,
        args[3].value.number,
        native_from_value_color(vm, args[4])
    );
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_DrawLineV,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawLineV(  
        native_from_value_vector2(vm, args[0]),
        native_from_value_vector2(vm, args[1]),
        native_from_value_color(vm, args[2])
    );
RAYLIB_FN__END

RAYLIB_FN__ARG4(raylib_DrawLineEx,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawLineEx(  
        native_from_value_vector2(vm, args[0]),
        native_from_value_vector2(vm, args[1]),
        args[2].value.number,
        native_from_value_color(vm, args[3])
    );
RAYLIB_FN__END


RAYLIB_FN__ARG4(raylib_DrawLineBezier,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawLineBezier(  
        native_from_value_vector2(vm, args[0]),
        native_from_value_vector2(vm, args[1]),
        args[2].value.number,
        native_from_value_color(vm, args[3])
    );
RAYLIB_FN__END

RAYLIB_FN__ARG5(raylib_DrawLineBezierQuad,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawLineBezierQuad(  
        native_from_value_vector2(vm, args[0]),
        native_from_value_vector2(vm, args[1]),
        native_from_value_vector2(vm, args[2]),
        args[3].value.number,
        native_from_value_color(vm, args[4])
    );
RAYLIB_FN__END

RAYLIB_FN__ARG6(raylib_DrawLineBezierCubic,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawLineBezierCubic(  
        native_from_value_vector2(vm, args[0]),
        native_from_value_vector2(vm, args[1]),
        native_from_value_vector2(vm, args[2]),
        native_from_value_vector2(vm, args[3]),
        args[4].value.number,
        native_from_value_color(vm, args[5])
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_DrawLineStrip,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    uint32_t num = matte_value_object_get_number_key_count(store, args[0]);
    if (num % 2 != 0) {
        matte_vm_raise_error_cstring(vm, "DrawLineStrip received a points array of uneven values.");
        goto L_END;
    }

    Vector2 * pts = MemAlloc(sizeof(Vector2)*num);
    
    uint32_t i;
    for(i = 0; i < num/2; ++i) {
        pts[i].x = matte_value_as_number(store, matte_value_object_access_index(store, args[0], i*2));
        pts[i].y = matte_value_as_number(store, matte_value_object_access_index(store, args[0], i*2+1));
    }

    DrawLineStrip(  
        pts,
        num/2,
        native_from_value_color(vm, args[1])
    );
    
    MemFree(pts);
  L_END:
RAYLIB_FN__END


RAYLIB_FN__ARG4(raylib_DrawCircle,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawCircle(  
        args[0].value.number,
        args[1].value.number,
        args[2].value.number,
        native_from_value_color(vm, args[3])
    );
RAYLIB_FN__END


RAYLIB_FN__ARG6(raylib_DrawCircleSector,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawCircleSector(  
        native_from_value_vector2(vm, args[0]),
        args[1].value.number,
        args[2].value.number,
        args[3].value.number,
        args[4].value.number,
        native_from_value_color(vm, args[5])
    );
RAYLIB_FN__END


RAYLIB_FN__ARG6(raylib_DrawCircleSectorLines,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawCircleSectorLines(  
        native_from_value_vector2(vm, args[0]),
        args[1].value.number,
        args[2].value.number,
        args[3].value.number,
        args[4].value.number,
        native_from_value_color(vm, args[5])
    );
RAYLIB_FN__END


RAYLIB_FN__ARG5(raylib_DrawCircleGradient,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawCircleGradient(  
        args[0].value.number,
        args[1].value.number,
        args[2].value.number,
        native_from_value_color(vm, args[3]),
        native_from_value_color(vm, args[4])
    );
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_DrawCircleV,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawCircleV(  
        native_from_value_vector2(vm, args[0]),
        args[1].value.number,
        native_from_value_color(vm, args[2])
    );
RAYLIB_FN__END

RAYLIB_FN__ARG4(raylib_DrawCircleLines,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawCircleLines(  
        args[0].value.number,
        args[1].value.number,
        args[2].value.number,
        native_from_value_color(vm, args[3])
    );
RAYLIB_FN__END

RAYLIB_FN__ARG5(raylib_DrawEllipse,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawEllipse(  
        args[0].value.number,
        args[1].value.number,
        args[2].value.number,
        args[3].value.number,
        native_from_value_color(vm, args[4])
    );
RAYLIB_FN__END

RAYLIB_FN__ARG5(raylib_DrawEllipseLines,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawEllipseLines(  
        args[0].value.number,
        args[1].value.number,
        args[2].value.number,
        args[3].value.number,
        native_from_value_color(vm, args[4])
    );
RAYLIB_FN__END


RAYLIB_FN__ARG7(raylib_DrawRing,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawRing(  
        native_from_value_vector2(vm, args[0]),
        args[1].value.number,
        args[2].value.number,
        args[3].value.number,
        args[4].value.number,
        args[5].value.number,
        native_from_value_color(vm, args[6])
    );
RAYLIB_FN__END

RAYLIB_FN__ARG7(raylib_DrawRingLines,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawRingLines(  
        native_from_value_vector2(vm, args[0]),
        args[1].value.number,
        args[2].value.number,
        args[3].value.number,
        args[4].value.number,
        args[5].value.number,
        native_from_value_color(vm, args[6])
    );
RAYLIB_FN__END


RAYLIB_FN__ARG5(raylib_DrawRectangle,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawRectangle(  
        args[0].value.number,
        args[1].value.number,
        args[2].value.number,
        args[3].value.number,
        native_from_value_color(vm, args[4])
    );
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_DrawRectangleV,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawRectangleV(  
        native_from_value_vector2(vm, args[0]),
        native_from_value_vector2(vm, args[1]),
        native_from_value_color(vm, args[2])
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_DrawRectangleRec,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawRectangleRec(  
        native_from_value_rectangle(vm, args[0]),
        native_from_value_color(vm, args[1])
    );
RAYLIB_FN__END

RAYLIB_FN__ARG4(raylib_DrawRectanglePro,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawRectanglePro(  
        native_from_value_rectangle(vm, args[0]),
        native_from_value_vector2(vm, args[1]),
        args[2].value.number,
        native_from_value_color(vm, args[3])
    );
RAYLIB_FN__END

RAYLIB_FN__ARG6(raylib_DrawRectangleGradientV,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawRectangleGradientV(  
        args[0].value.number,
        args[1].value.number,
        args[2].value.number,
        args[3].value.number,

        native_from_value_color(vm, args[4]),
        native_from_value_color(vm, args[5])
    );
RAYLIB_FN__END


RAYLIB_FN__ARG6(raylib_DrawRectangleGradientH,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawRectangleGradientH(  
        args[0].value.number,
        args[1].value.number,
        args[2].value.number,
        args[3].value.number,

        native_from_value_color(vm, args[4]),
        native_from_value_color(vm, args[5])
    );
RAYLIB_FN__END


RAYLIB_FN__ARG5(raylib_DrawRectangleGradientEx,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawRectangleGradientEx(  
        native_from_value_rectangle(vm, args[0]),
        native_from_value_color(vm, args[1]),
        native_from_value_color(vm, args[2]),
        native_from_value_color(vm, args[3]),
        native_from_value_color(vm, args[4])
    );
RAYLIB_FN__END

RAYLIB_FN__ARG5(raylib_DrawRectangleLines,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawRectangleLines(  
        args[0].value.number,
        args[1].value.number,
        args[2].value.number,
        args[3].value.number,

        native_from_value_color(vm, args[4])
    );
RAYLIB_FN__END

RAYLIB_FN__ARG3(raylib_DrawRectangleLinesEx,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawRectangleLinesEx(  
        native_from_value_rectangle(vm, args[0]),
        args[1].value.number,
        native_from_value_color(vm, args[2])
    );
RAYLIB_FN__END

RAYLIB_FN__ARG4(raylib_DrawRectangleRounded,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawRectangleRounded(  
        native_from_value_rectangle(vm, args[0]),
        args[1].value.number,
        args[2].value.number,
        native_from_value_color(vm, args[3])
    );
RAYLIB_FN__END


RAYLIB_FN__ARG5(raylib_DrawRectangleRoundedLines,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawRectangleRoundedLines(  
        native_from_value_rectangle(vm, args[0]),
        args[1].value.number,
        args[2].value.number,
        args[3].value.number,
        native_from_value_color(vm, args[4])
    );
RAYLIB_FN__END


RAYLIB_FN__ARG4(raylib_DrawTriangle,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawTriangle(  
        native_from_value_vector2(vm, args[0]),
        native_from_value_vector2(vm, args[1]),
        native_from_value_vector2(vm, args[2]),
        native_from_value_color(vm, args[3])
    );
RAYLIB_FN__END

RAYLIB_FN__ARG4(raylib_DrawTriangleLines,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawTriangleLines(  
        native_from_value_vector2(vm, args[0]),
        native_from_value_vector2(vm, args[1]),
        native_from_value_vector2(vm, args[2]),
        native_from_value_color(vm, args[3])
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_DrawTriangleFan,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    uint32_t num = matte_value_object_get_number_key_count(store, args[0]);
    if (num % 2 != 0) {
        matte_vm_raise_error_cstring(vm, "DrawTriangleStrip received a points array of uneven values.");
        goto L_END;
    }

    Vector2 * pts = MemAlloc(sizeof(Vector2)*num);
    
    uint32_t i;
    for(i = 0; i < num/2; ++i) {
        pts[i].x = matte_value_as_number(store, matte_value_object_access_index(store, args[0], i*2));
        pts[i].y = matte_value_as_number(store, matte_value_object_access_index(store, args[0], i*2+1));
    }

    DrawTriangleFan(  
        pts,
        num/2,
        native_from_value_color(vm, args[1])
    );
    
    MemFree(pts);
  L_END:
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_DrawTriangleStrip,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    uint32_t num = matte_value_object_get_number_key_count(store, args[0]);
    if (num % 2 != 0) {
        matte_vm_raise_error_cstring(vm, "DrawTriangleStrip received a points array of uneven values.");
        goto L_END;
    }

    Vector2 * pts = MemAlloc(sizeof(Vector2)*num);
    
    uint32_t i;
    for(i = 0; i < num/2; ++i) {
        pts[i].x = matte_value_as_number(store, matte_value_object_access_index(store, args[0], i*2));
        pts[i].y = matte_value_as_number(store, matte_value_object_access_index(store, args[0], i*2+1));
    }

    DrawTriangleStrip(  
        pts,
        num/2,
        native_from_value_color(vm, args[1])
    );
    
    MemFree(pts);
  L_END:
RAYLIB_FN__END

RAYLIB_FN__ARG5(raylib_DrawPoly,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawPoly(  
        native_from_value_vector2(vm, args[0]),
        args[1].value.number,
        args[2].value.number,
        args[3].value.number,
        native_from_value_color(vm, args[4])
    );
RAYLIB_FN__END

RAYLIB_FN__ARG5(raylib_DrawPolyLines,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawPolyLines(  
        native_from_value_vector2(vm, args[0]),
        args[1].value.number,
        args[2].value.number,
        args[3].value.number,
        native_from_value_color(vm, args[4])
    );
RAYLIB_FN__END


RAYLIB_FN__ARG6(raylib_DrawPolyLinesEx,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawPolyLinesEx(  
        native_from_value_vector2(vm, args[0]),
        args[1].value.number,
        args[2].value.number,
        args[3].value.number,
        args[4].value.number,
        native_from_value_color(vm, args[5])
    );
RAYLIB_FN__END





// Collision

RAYLIB_FN__ARG2(raylib_CheckCollisionRecs,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_boolean(
        vm,
        CheckCollisionRecs(  
            native_from_value_rectangle(vm, args[0]),
            native_from_value_rectangle(vm, args[1])
        )        
    );
RAYLIB_FN__END


RAYLIB_FN__ARG4(raylib_CheckCollisionCircles,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_boolean(
        vm,
        CheckCollisionCircles(  
            native_from_value_vector2(vm, args[0]),
            args[1].value.number,
            native_from_value_vector2(vm, args[2]),
            args[3].value.number
        )        
    );
RAYLIB_FN__END

RAYLIB_FN__ARG3(raylib_CheckCollisionCircleRec,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_boolean(
        vm,
        CheckCollisionCircleRec(  
            native_from_value_vector2(vm, args[0]),
            args[1].value.number,
            native_from_value_rectangle(vm, args[2])
        )        
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_CheckCollisionPointRec,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_boolean(
        vm,
        CheckCollisionPointRec(  
            native_from_value_vector2(vm, args[0]),
            native_from_value_rectangle(vm, args[1])
        )        
    );
RAYLIB_FN__END

RAYLIB_FN__ARG3(raylib_CheckCollisionPointCircle,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_boolean(
        vm,
        CheckCollisionPointCircle(  
            native_from_value_vector2(vm, args[0]),
            native_from_value_vector2(vm, args[1]),
            args[2].value.number
        )        
    );
RAYLIB_FN__END


RAYLIB_FN__ARG4(raylib_CheckCollisionPointTriangle,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_boolean(
        vm,
        CheckCollisionPointTriangle(  
            native_from_value_vector2(vm, args[0]),
            native_from_value_vector2(vm, args[1]),
            native_from_value_vector2(vm, args[2]),
            native_from_value_vector2(vm, args[3])
        )        
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_CheckCollisionPointPoly,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    uint32_t num = matte_value_object_get_number_key_count(store, args[1]);
    if (num % 2 != 0) {
        matte_vm_raise_error_cstring(vm, "CheckCollisionPointPoly received a points array of uneven values.");
        goto L_END;
    }

    Vector2 * pts = MemAlloc(sizeof(Vector2)*num);
    
    uint32_t i;
    for(i = 0; i < num/2; ++i) {
        pts[i].x = matte_value_as_number(store, matte_value_object_access_index(store, args[1], i*2));
        pts[i].y = matte_value_as_number(store, matte_value_object_access_index(store, args[1], i*2+1));
    }

    int out = CheckCollisionPointPoly(  
        native_from_value_vector2(vm, args[0]),
        pts,
        num/2
    );
    
    MemFree(pts);
    
    return native_to_value_boolean(vm, out);
  L_END:

RAYLIB_FN__END


RAYLIB_FN__ARG4(raylib_CheckCollisionLines,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    Vector2 location = native_from_value_vector2(vm, args[4]);
    matteValue_t out = native_to_value_boolean(
        vm,
        CheckCollisionLines(  
            native_from_value_vector2(vm, args[0]),
            native_from_value_vector2(vm, args[1]),
            native_from_value_vector2(vm, args[2]),
            native_from_value_vector2(vm, args[3]),
            &location
        )        
    );
    
    native_update_value_vector2(vm, args[4], location);
    return out;
RAYLIB_FN__END

RAYLIB_FN__ARG4(raylib_CheckCollisionPointLine,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_boolean(
        vm,
        CheckCollisionPointLine(  
            native_from_value_vector2(vm, args[0]),
            native_from_value_vector2(vm, args[1]),
            native_from_value_vector2(vm, args[2]),
            args[3].value.number
        )        
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_GetCollisionRec,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_rectangle(
        vm,
        GetCollisionRec(  
            native_from_value_rectangle(vm, args[0]),
            native_from_value_rectangle(vm, args[1])
        )        
    );
RAYLIB_FN__END




// rtextures

RAYLIB_FN__ARG1(raylib_LoadImage,
    MATTE_VALUE_TYPE_STRING
)
    return native_to_value_image(
        vm,
        LoadImage(  
            native_from_value_string_unsafe(vm, args[0]) // ok!
        )        
    );
RAYLIB_FN__END

RAYLIB_FN__ARG5(raylib_LoadImageRaw,
    MATTE_VALUE_TYPE_STRING,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_image(
        vm,
        LoadImageRaw(  
            native_from_value_string_unsafe(vm, args[0]), // ok!
            args[1].value.number,
            args[2].value.number,
            args[3].value.number,
            args[4].value.number
        )        
    );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_LoadImageAnim,
    MATTE_VALUE_TYPE_STRING
)
    int nframes = 0;
    matteValue_t img = native_to_value_image(
        vm,
        LoadImageAnim(  
            native_from_value_string_unsafe(vm, args[0]), // ok!
            &nframes
        )        
    );
    
    matteValue_t nframesv = native_to_value_int(vm, nframes);
    matte_value_object_set_key_string(store, img, MATTE_VM_STR_CAST(vm, "frames"), nframesv);
    return img;
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_LoadImageFromMemory,
    MATTE_VALUE_TYPE_STRING,
    MATTE_VALUE_TYPE_OBJECT
)

    uint32_t size = 0;
    const uint8_t * data = matte_vm_get_memory_buffer_handle_raw_data(
        vm,
        args[0],
        &size
    );
    if (size == 0 || data == NULL) goto L_END;
    
    return native_to_value_image(
        vm,
        LoadImageFromMemory(
            native_from_value_string_unsafe(vm, args[0]),
            data,
            size 
        )
    );
    
  L_END:
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_LoadImageFromTexture,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_image(
        vm,
        LoadImageFromTexture(  
            native_from_value_texture(vm, args[0])
        )        
    );
RAYLIB_FN__END


RAYLIB_FN__ARG0(raylib_LoadImageFromScreen
)
    return native_to_value_image(
        vm,
        LoadImageFromScreen(  
        )        
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_IsImageReady,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_boolean(
        vm,
        IsImageReady(  
            native_from_value_image(vm, args[0])
        )        
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_UnloadImage,
    MATTE_VALUE_TYPE_OBJECT
)
    UnloadImage(  
        native_from_value_image(vm, args[0])
    );
    native_unload(vm, args[0]);
RAYLIB_FN__END



RAYLIB_FN__ARG2(raylib_ExportImage,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_STRING
)
    return native_to_value_boolean(
        vm,
        ExportImage(  
            native_from_value_image(vm, args[0]),
            native_from_value_string_unsafe(vm, args[1]) // ok!
        )        
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_ExportImageAsCode,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_STRING
)
    return native_to_value_boolean(
        vm,
        ExportImageAsCode(  
            native_from_value_image(vm, args[0]),
            native_from_value_string_unsafe(vm, args[1]) // ok!
        )        
    );
RAYLIB_FN__END



RAYLIB_FN__ARG3(raylib_GenImageColor,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_image(
        vm,
        GenImageColor(  
            args[0].value.number,
            args[1].value.number,
            native_from_value_color(vm, args[2])
        )        
    );
RAYLIB_FN__END


RAYLIB_FN__ARG5(raylib_GenImageGradientLinear,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_image(
        vm,
        GenImageGradientLinear(  
            args[0].value.number,
            args[1].value.number,
            args[2].value.number,
            native_from_value_color(vm, args[3]),
            native_from_value_color(vm, args[4])
        )        
    );
RAYLIB_FN__END


RAYLIB_FN__ARG5(raylib_GenImageGradientRadial,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_image(
        vm,
        GenImageGradientRadial(  
            args[0].value.number,
            args[1].value.number,
            args[2].value.number,
            native_from_value_color(vm, args[3]),
            native_from_value_color(vm, args[4])
        )        
    );
RAYLIB_FN__END

RAYLIB_FN__ARG5(raylib_GenImageGradientSquare,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_image(
        vm,
        GenImageGradientSquare(  
            args[0].value.number,
            args[1].value.number,
            args[2].value.number,
            native_from_value_color(vm, args[3]),
            native_from_value_color(vm, args[4])
        )        
    );
RAYLIB_FN__END


RAYLIB_FN__ARG6(raylib_GenImageChecked,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_image(
        vm,
        GenImageChecked(  
            args[0].value.number,
            args[1].value.number,
            args[2].value.number,
            args[3].value.number,
            native_from_value_color(vm, args[4]),
            native_from_value_color(vm, args[5])
        )        
    );
RAYLIB_FN__END

RAYLIB_FN__ARG3(raylib_GenImageWhiteNoise,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_image(
        vm,
        GenImageWhiteNoise(  
            args[0].value.number,
            args[1].value.number,
            args[2].value.number
        )        
    );
RAYLIB_FN__END

RAYLIB_FN__ARG5(raylib_GenImagePerlinNoise,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_image(
        vm,
        GenImagePerlinNoise(  
            args[0].value.number,
            args[1].value.number,
            args[2].value.number,
            args[3].value.number,
            args[4].value.number
        )        
    );
RAYLIB_FN__END

RAYLIB_FN__ARG3(raylib_GenImageCellular,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_image(
        vm,
        GenImageCellular(  
            args[0].value.number,
            args[1].value.number,
            args[2].value.number
        )        
    );
RAYLIB_FN__END


/// ??????
RAYLIB_FN__ARG3(raylib_GenImageText,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_STRING
)
    return native_to_value_image(
        vm,
        GenImageText(  
            args[0].value.number,
            args[1].value.number,
            native_from_value_string_unsafe(vm, args[2]) // ok!
        )        
    );
RAYLIB_FN__END






RAYLIB_FN__ARG1(raylib_ImageCopy,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_image(
        vm,
        ImageCopy(  
            native_from_value_image(vm, args[0])
        )        
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_ImageFromImage,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_image(
        vm,
        ImageFromImage(  
            native_from_value_image(vm, args[0]),
            native_from_value_rectangle(vm, args[1])
        )        
    );
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_ImageText,
    MATTE_VALUE_TYPE_STRING,
    MATTE_VALUE_TYPE_NUMBER,    
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_image(
        vm,
        ImageText(  
            native_from_value_string_unsafe(vm, args[0]), // ok!
            args[1].value.number,
            native_from_value_color(vm, args[2])
        )        
    );
RAYLIB_FN__END


RAYLIB_FN__ARG5(raylib_ImageTextEx,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_STRING,
    MATTE_VALUE_TYPE_NUMBER,    
    MATTE_VALUE_TYPE_NUMBER,    
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_image(
        vm,
        ImageTextEx(  
            native_from_value_font(vm, args[0]),
            native_from_value_string_unsafe(vm, args[1]), // ok!
            args[2].value.number,
            args[3].value.number,
            native_from_value_color(vm, args[4])
        )        
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_ImageFormat,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER  
)

    ImageFormat(
        native_from_value_image_ref(vm, args[0]),
        args[1].value.number
    );
    native_update_value_image(vm, args[0]);
RAYLIB_FN__END



RAYLIB_FN__ARG2(raylib_ImageToPOT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)

    ImageToPOT(
        native_from_value_image_ref(vm, args[0]),
        native_from_value_color(vm, args[1])
    );
    native_update_value_image(vm, args[0]);
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_ImageCrop,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)

    ImageCrop(
        native_from_value_image_ref(vm, args[0]),
        native_from_value_rectangle(vm, args[1])
    );
    native_update_value_image(vm, args[0]);
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_ImageAlphaCrop,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)

    ImageAlphaCrop(
        native_from_value_image_ref(vm, args[0]),
        args[1].value.number
    );
    native_update_value_image(vm, args[0]);
RAYLIB_FN__END

RAYLIB_FN__ARG3(raylib_ImageAlphaClear,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)

    ImageAlphaClear(
        native_from_value_image_ref(vm, args[0]),
        native_from_value_color(vm, args[1]),
        args[2].value.number
    );
    native_update_value_image(vm, args[0]);
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_ImageAlphaMask,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)

    ImageAlphaMask(
        native_from_value_image_ref(vm, args[0]),
        native_from_value_image(vm, args[1])
    );
    native_update_value_image(vm, args[0]);
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_ImageAlphaPremultiply,
    MATTE_VALUE_TYPE_OBJECT
)

    ImageAlphaPremultiply(
        native_from_value_image_ref(vm, args[0])
    );
    native_update_value_image(vm, args[0]);
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_ImageBlurGaussian,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)

    ImageBlurGaussian(
        native_from_value_image_ref(vm, args[0]),
        args[1].value.number
    );
    native_update_value_image(vm, args[0]);
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_ImageResize,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)

    ImageResize(
        native_from_value_image_ref(vm, args[0]),
        args[1].value.number,
        args[2].value.number
    );
    native_update_value_image(vm, args[0]);
RAYLIB_FN__END

RAYLIB_FN__ARG3(raylib_ImageResizeNN,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)

    ImageResizeNN(
        native_from_value_image_ref(vm, args[0]),
        args[1].value.number,
        args[2].value.number
    );
    native_update_value_image(vm, args[0]);
RAYLIB_FN__END

RAYLIB_FN__ARG6(raylib_ImageResizeCanvas,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)

    ImageResizeCanvas(
        native_from_value_image_ref(vm, args[0]),
        args[1].value.number,
        args[2].value.number,
        args[3].value.number,
        args[4].value.number,
        native_from_value_color(vm, args[5])
    );
    native_update_value_image(vm, args[0]);
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_ImageMipmaps,
    MATTE_VALUE_TYPE_OBJECT
)

    ImageMipmaps(
        native_from_value_image_ref(vm, args[0])
    );
    native_update_value_image(vm, args[0]);
RAYLIB_FN__END

RAYLIB_FN__ARG5(raylib_ImageDither,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)

    ImageDither(
        native_from_value_image_ref(vm, args[0]),
        args[1].value.number,
        args[2].value.number,
        args[3].value.number,
        args[4].value.number
    );
    native_update_value_image(vm, args[0]);
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_ImageFlipHorizontal,
    MATTE_VALUE_TYPE_OBJECT
)

    ImageFlipHorizontal(
        native_from_value_image_ref(vm, args[0])
    );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_ImageFlipVertical,
    MATTE_VALUE_TYPE_OBJECT
)

    ImageFlipVertical(
        native_from_value_image_ref(vm, args[0])
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_ImageRotate,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)

    ImageRotate(
        native_from_value_image_ref(vm, args[0]),
        args[1].value.number
    );
    native_update_value_image(vm, args[0]);
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_ImageRotateCW,
    MATTE_VALUE_TYPE_OBJECT
)

    ImageRotateCW(
        native_from_value_image_ref(vm, args[0])
    );
    native_update_value_image(vm, args[0]);
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_ImageRotateCCW,
    MATTE_VALUE_TYPE_OBJECT
)

    ImageRotateCCW(
        native_from_value_image_ref(vm, args[0])
    );
    native_update_value_image(vm, args[0]);
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_ImageColorTint,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)

    ImageColorTint(
        native_from_value_image_ref(vm, args[0]),
        native_from_value_color(vm, args[1])
    );
    native_update_value_image(vm, args[0]);
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_ImageColorInvert,
    MATTE_VALUE_TYPE_OBJECT
)

    ImageColorInvert(
        native_from_value_image_ref(vm, args[0])
    );
    native_update_value_image(vm, args[0]);
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_ImageColorGrayscale,
    MATTE_VALUE_TYPE_OBJECT
)

    ImageColorGrayscale(
        native_from_value_image_ref(vm, args[0])
    );
    native_update_value_image(vm, args[0]);
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_ImageColorContrast,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)

    ImageColorContrast(
        native_from_value_image_ref(vm, args[0]),
        args[1].value.number
    );
    native_update_value_image(vm, args[0]);
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_ImageColorBrightness,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)

    ImageColorBrightness(
        native_from_value_image_ref(vm, args[0]),
        args[1].value.number
    );
    native_update_value_image(vm, args[0]);
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_ImageColorReplace,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)

    ImageColorReplace(
        native_from_value_image_ref(vm, args[0]),
        native_from_value_color(vm, args[1]),
        native_from_value_color(vm, args[2])
    );
    native_update_value_image(vm, args[0]);
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_LoadImageColors,
    MATTE_VALUE_TYPE_OBJECT
)
    Image img = native_from_value_image(vm, args[0]);
    uint32_t len = img.width * img.height;
    matteValue_t * vals = MemAlloc(sizeof(matteValue_t)*len);
       
    Color * colors = LoadImageColors(
        img
    );
    
    uint32_t i;
    for(i = 0; i < len; ++i) {
        vals[i] = native_to_value_color(vm, colors[i]);
    }
    
    UnloadImageColors(colors);
    matteValue_t v = matte_store_new_value(store);
    matteArray_t arr = MATTE_ARRAY_CAST(vals, matteValue_t, len);
    matte_value_into_new_object_array_ref(store, &v, &arr);
    MemFree(vals);
    return v;
    
RAYLIB_FN__END



RAYLIB_FN__ARG2(raylib_LoadImagePalette,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    Image img = native_from_value_image(vm, args[0]);
    int len;
    Color * colors = LoadImagePalette(
        img,
        args[1].value.number,
        &len
    );

    matteValue_t * vals = MemAlloc(sizeof(matteValue_t)*len);
       
    
    uint32_t i;
    for(i = 0; i < len; ++i) {
        vals[i] = native_to_value_color(vm, colors[i]);
    }
    UnloadImagePalette(colors);
    
    matteValue_t v = matte_store_new_value(store);
    matteArray_t arr = MATTE_ARRAY_CAST(vals, matteValue_t, len);
    matte_value_into_new_object_array_ref(store, &v, &arr);
    MemFree(vals);
    return v;
    
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_GetImageAlphaBorder,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_rectangle(
        vm,
        GetImageAlphaBorder(
            native_from_value_image(vm, args[0]),
            args[1].value.number
        )
    );
    
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_GetImageColor,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_color(
        vm,
        GetImageColor(
            native_from_value_image(vm, args[0]),
            args[1].value.number,
            args[2].value.number
        )
    );
    
RAYLIB_FN__END








RAYLIB_FN__ARG2(raylib_ImageClearBackground,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    ImageClearBackground(
        native_from_value_image_ref(vm, args[0]),
        native_from_value_color(vm, args[1])
    );    
    native_update_value_image(vm, args[0]);
RAYLIB_FN__END



RAYLIB_FN__ARG4(raylib_ImageDrawPixel,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    ImageDrawPixel(
        native_from_value_image_ref(vm, args[0]),
        args[1].value.number,
        args[2].value.number,
        native_from_value_color(vm, args[3])
    );    
    native_update_value_image(vm, args[0]);
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_ImageDrawPixelV,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    ImageDrawPixelV(
        native_from_value_image_ref(vm, args[0]),
        native_from_value_vector2(vm, args[1]),
        native_from_value_color(vm, args[2])
    );    
    native_update_value_image(vm, args[0]);
RAYLIB_FN__END



RAYLIB_FN__ARG6(raylib_ImageDrawLine,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    ImageDrawLine(
        native_from_value_image_ref(vm, args[0]),
        args[1].value.number,
        args[2].value.number,
        args[3].value.number,
        args[4].value.number,
        native_from_value_color(vm, args[5])
    );    
    native_update_value_image(vm, args[0]);
RAYLIB_FN__END


RAYLIB_FN__ARG4(raylib_ImageDrawLineV,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    ImageDrawLineV(
        native_from_value_image_ref(vm, args[0]),
        native_from_value_vector2(vm, args[1]),
        native_from_value_vector2(vm, args[2]),
        native_from_value_color(vm, args[3])
    );    
    native_update_value_image(vm, args[0]);
RAYLIB_FN__END


RAYLIB_FN__ARG5(raylib_ImageDrawCircle,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    ImageDrawCircle(
        native_from_value_image_ref(vm, args[0]),
        args[1].value.number,
        args[2].value.number,
        args[3].value.number,
        native_from_value_color(vm, args[4])
    );    
    native_update_value_image(vm, args[0]);
RAYLIB_FN__END


RAYLIB_FN__ARG4(raylib_ImageDrawCircleV,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    ImageDrawCircleV(
        native_from_value_image_ref(vm, args[0]),
        native_from_value_vector2(vm, args[1]),
        args[2].value.number,
        native_from_value_color(vm, args[3])
    );    
    native_update_value_image(vm, args[0]);
RAYLIB_FN__END

RAYLIB_FN__ARG5(raylib_ImageDrawCircleLines,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    ImageDrawCircleLines(
        native_from_value_image_ref(vm, args[0]),
        args[1].value.number,
        args[2].value.number,
        args[3].value.number,
        native_from_value_color(vm, args[4])
    );    
    native_update_value_image(vm, args[0]);
RAYLIB_FN__END


RAYLIB_FN__ARG4(raylib_ImageDrawCircleLinesV,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    ImageDrawCircleLinesV(
        native_from_value_image_ref(vm, args[0]),
        native_from_value_vector2(vm, args[1]),
        args[2].value.number,
        native_from_value_color(vm, args[3])
    );    
    native_update_value_image(vm, args[0]);
RAYLIB_FN__END

RAYLIB_FN__ARG6(raylib_ImageDrawRectangle,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    ImageDrawRectangle(
        native_from_value_image_ref(vm, args[0]),
        args[1].value.number,
        args[2].value.number,
        args[3].value.number,
        args[4].value.number,
        native_from_value_color(vm, args[5])
    );    
    native_update_value_image(vm, args[0]);
RAYLIB_FN__END

RAYLIB_FN__ARG4(raylib_ImageDrawRectangleV,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    ImageDrawRectangleV(
        native_from_value_image_ref(vm, args[0]),
        native_from_value_vector2(vm, args[1]),
        native_from_value_vector2(vm, args[2]),
        native_from_value_color(vm, args[3])
    );    
    native_update_value_image(vm, args[0]);
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_ImageDrawRectangleRec,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    ImageDrawRectangleRec(
        native_from_value_image_ref(vm, args[0]),
        native_from_value_rectangle(vm, args[1]),
        native_from_value_color(vm, args[2])
    );    
    native_update_value_image(vm, args[0]);
RAYLIB_FN__END


RAYLIB_FN__ARG4(raylib_ImageDrawRectangleLines,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    ImageDrawRectangleLines(
        native_from_value_image_ref(vm, args[0]),
        native_from_value_rectangle(vm, args[1]),
        args[2].value.number,
        native_from_value_color(vm, args[3])
    );    
    native_update_value_image(vm, args[0]);
RAYLIB_FN__END



RAYLIB_FN__ARG5(raylib_ImageDraw,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    ImageDraw(
        native_from_value_image_ref(vm, args[0]),
        native_from_value_image(vm, args[1]),
        native_from_value_rectangle(vm, args[2]),
        native_from_value_rectangle(vm, args[3]),
        native_from_value_color(vm, args[4])
    );    
    native_update_value_image(vm, args[0]);
RAYLIB_FN__END


RAYLIB_FN__ARG6(raylib_ImageDrawText,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_STRING,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    ImageDrawText(
        native_from_value_image_ref(vm, args[0]),
        native_from_value_string_unsafe(vm, args[1]), // ok!
        args[2].value.number,
        args[3].value.number,
        args[4].value.number,
        native_from_value_color(vm, args[5])
    );    
    native_update_value_image(vm, args[0]);
RAYLIB_FN__END

RAYLIB_FN__ARG7(raylib_ImageDrawTextEx,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_STRING,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    ImageDrawTextEx(
        native_from_value_image_ref(vm, args[0]),
        native_from_value_font(vm, args[1]),
        native_from_value_string_unsafe(vm, args[2]), // ok!
        native_from_value_vector2(vm, args[3]),
        args[4].value.number,
        args[5].value.number,
        native_from_value_color(vm, args[6])
    );    
    native_update_value_image(vm, args[0]);
RAYLIB_FN__END




RAYLIB_FN__ARG1(raylib_LoadTexture,
    MATTE_VALUE_TYPE_STRING
)

    return native_to_value_texture(
        vm,
        LoadTexture(
            native_from_value_string_unsafe(vm, args[0]) // ok!
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_LoadTextureFromImage,
    MATTE_VALUE_TYPE_OBJECT
)

    return native_to_value_texture(
        vm,
        LoadTextureFromImage(
            native_from_value_image(vm, args[0])
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_LoadTextureCubemap,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)

    return native_to_value_texture(
        vm,
        LoadTextureCubemap(
            native_from_value_image(vm, args[0]),
            args[1].value.number
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_LoadRenderTexture,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)

    return native_to_value_renderTexture(
        vm,
        LoadRenderTexture(
            args[0].value.number,
            args[1].value.number
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_IsTextureReady,
    MATTE_VALUE_TYPE_OBJECT
)

    return native_to_value_boolean(
        vm,
        IsTextureReady(
            native_from_value_texture(vm, args[0])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_UnloadTexture,
    MATTE_VALUE_TYPE_OBJECT
)
    Texture img = native_from_value_texture(vm, args[0]);
    UnloadTexture(
        img
    );
    native_unload(vm, args[0]);
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_IsRenderTextureReady,
    MATTE_VALUE_TYPE_OBJECT
)

    return native_to_value_boolean(
        vm,
        IsRenderTextureReady(
            native_from_value_renderTexture(vm, args[0])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_UnloadRenderTexture,
    MATTE_VALUE_TYPE_OBJECT
)
    RenderTexture img = native_from_value_renderTexture(vm, args[0]);
    UnloadRenderTexture(
        img
    );
    native_unload(vm, args[0]);
RAYLIB_FN__END



RAYLIB_FN__ARG2(raylib_UpdateTexture,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    Texture tex = native_from_value_texture(vm, args[0]);
    Image img = native_from_value_image(vm, args[1]);
    
    img = ImageCopy(img);
    ImageFormat(&img, tex.format);
    
    UpdateTexture(tex, img.data);
   
    UnloadImage(img);
RAYLIB_FN__END



RAYLIB_FN__ARG3(raylib_UpdateTextureRec,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    Texture tex = native_from_value_texture(vm, args[0]);
    Vector2 pos = native_from_value_vector2(vm, args[1]);
    Image img = native_from_value_image(vm, args[2]);
    
    img = ImageCopy(img);
    Rectangle rec;
    rec.x = pos.x;
    rec.y = pos.y;
    rec.width = img.width;
    rec.height = img.height;
    ImageFormat(&img, tex.format);
    
    UpdateTextureRec(tex, rec, img.data);
   
    UnloadImage(img);
RAYLIB_FN__END





RAYLIB_FN__ARG1(raylib_GenTextureMipmaps,
    MATTE_VALUE_TYPE_OBJECT
)
    GenTextureMipmaps(
        native_from_value_texture_ref(vm, args[0])
    );
    native_update_value_texture(vm, args[0]);
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_SetTextureFilter,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    SetTextureFilter(
        native_from_value_texture(vm, args[0]),
        args[1].value.number
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_SetTextureWrap,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    SetTextureWrap(
        native_from_value_texture(vm, args[0]),
        args[1].value.number
    );
RAYLIB_FN__END








RAYLIB_FN__ARG4(raylib_DrawTexture,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawTexture(
        native_from_value_texture(vm, args[0]),
        args[1].value.number,
        args[2].value.number,
        native_from_value_color(vm, args[3])
    );
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_DrawTextureV,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawTextureV(
        native_from_value_texture(vm, args[0]),
        native_from_value_vector2(vm, args[1]),
        native_from_value_color(vm, args[2])
    );
RAYLIB_FN__END

RAYLIB_FN__ARG5(raylib_DrawTextureEx,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawTextureEx(
        native_from_value_texture(vm, args[0]),
        native_from_value_vector2(vm, args[1]),
        args[2].value.number,
        args[3].value.number,
        native_from_value_color(vm, args[4])
    );
RAYLIB_FN__END


RAYLIB_FN__ARG4(raylib_DrawTextureRec,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawTextureRec(
        native_from_value_texture(vm, args[0]),
        native_from_value_rectangle(vm, args[1]),
        native_from_value_vector2(vm, args[2]),
        native_from_value_color(vm, args[3])
    );
RAYLIB_FN__END

RAYLIB_FN__ARG6(raylib_DrawTexturePro,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawTexturePro(
        native_from_value_texture(vm, args[0]),
        native_from_value_rectangle(vm, args[1]),
        native_from_value_rectangle(vm, args[2]),
        native_from_value_vector2(vm, args[3]),
        args[4].value.number,
        native_from_value_color(vm, args[5])
    );
RAYLIB_FN__END


RAYLIB_FN__ARG6(raylib_DrawTextureNPatch,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawTextureNPatch(
        native_from_value_texture(vm, args[0]),
        native_from_value_nPatchInfo(vm, args[1]),
        native_from_value_rectangle(vm, args[2]),
        native_from_value_vector2(vm, args[3]),
        args[4].value.number,
        native_from_value_color(vm, args[5])
    );
RAYLIB_FN__END






RAYLIB_FN__ARG2(raylib_Fade,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_color(
        vm,
        Fade(
            native_from_value_color(vm, args[0]),
            args[1].value.number
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_ColorToInt,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_int(
        vm,
        ColorToInt(
            native_from_value_color(vm, args[0])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_ColorNormalize,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_vector4(
        vm,
        ColorNormalize(
            native_from_value_color(vm, args[0])
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_ColorFromNormalized,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_color(
        vm,
        ColorFromNormalized(
            native_from_value_vector4(vm, args[0])
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_ColorToHSV,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_vector3(
        vm,
        ColorToHSV(
            native_from_value_color(vm, args[0])
        )
    );
RAYLIB_FN__END



RAYLIB_FN__ARG3(raylib_ColorFromHSV,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_color(
        vm,
        ColorFromHSV(
            args[0].value.number,
            args[1].value.number,
            args[2].value.number
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_ColorTint,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_color(
        vm,
        ColorTint(
            native_from_value_color(vm, args[0]),
            native_from_value_color(vm, args[1])
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_ColorBrightness,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_color(
        vm,
        ColorBrightness(
            native_from_value_color(vm, args[0]),
            args[1].value.number
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_ColorContrast,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_color(
        vm,
        ColorContrast(
            native_from_value_color(vm, args[0]),
            args[1].value.number
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_ColorAlpha,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_color(
        vm,
        ColorAlpha(
            native_from_value_color(vm, args[0]),
            args[1].value.number
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_ColorAlphaBlend,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_color(
        vm,
        ColorAlphaBlend(
            native_from_value_color(vm, args[0]),
            native_from_value_color(vm, args[1]),
            native_from_value_color(vm, args[2])
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_GetColor,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_color(
        vm,
        GetColor(
            args[0].value.number
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_GetPixelColor,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    uint32_t size = 0;
    const uint8_t * data = matte_vm_get_memory_buffer_handle_raw_data(
        vm,
        args[0],
        &size
    );
    
    if (size < GetPixelDataSize(1, 1, args[1].value.number)) {
        matte_vm_raise_error_cstring(vm, "GetPixelColor: received buffer of insufficient size.");
        goto L_END;
    }

    return native_to_value_color(
        vm,
        GetPixelColor(
            (void*)data,    
            args[1].value.number
        )
    );
  L_END:
RAYLIB_FN__END



RAYLIB_FN__ARG3(raylib_SetPixelColor,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    uint32_t size = 0;
    uint8_t * data = matte_vm_get_memory_buffer_handle_raw_data(
        vm,
        args[0],
        &size
    );
    
    if (size < GetPixelDataSize(1, 1, args[1].value.number)) {
        matte_vm_raise_error_cstring(vm, "SetPixelColor: received buffer of insufficient size.");
        goto L_END;
    }

    SetPixelColor(
        data,
        native_from_value_color(vm, args[1]),        
        args[2].value.number
    );
  L_END:
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_GetPixelDataSize,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_int(
        vm,
        GetPixelDataSize(
            args[0].value.number,
            args[0].value.number,
            args[0].value.number
        )
    );
RAYLIB_FN__END








// r text

RAYLIB_FN__ARG0(raylib_GetFontDefault
)
    return native_to_value_font(
        vm,
        GetFontDefault(
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_LoadFont,
    MATTE_VALUE_TYPE_STRING
)
    return native_to_value_font(
        vm,
        LoadFont(
            native_from_value_string_unsafe(vm, args[0]) // ok!
        )
    );
RAYLIB_FN__END


// free with MemFree when done.
static int * get_codepoints(matteVM_t * vm, matteStore_t * store, matteValue_t v, int * glyphCount) {
    int count = matte_value_object_get_number_key_count(store, v);

    int * codepoints = MemAlloc(sizeof(int)*count);
    memset(codepoints, 0, sizeof(int)*count);
    int i;
    for(i = 0; i < count; ++i) {
        matteValue_t str = matte_value_as_string(store, matte_value_object_access_index(store, v, i));
        if (str.binID == MATTE_VALUE_TYPE_STRING) {
            const matteString_t * strS = matte_value_string_get_string_unsafe(store, str);
            if (matte_string_get_length(strS) > 0) {
                codepoints[i] = matte_string_get_char(strS, 0);
            }
        }
    }
    *glyphCount = count;
    return codepoints;
    
}


RAYLIB_FN__ARG3(raylib_LoadFontEx,
    MATTE_VALUE_TYPE_STRING,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    int count = 0;
    int * codepoints = get_codepoints(
        vm,
        store,
        args[2],
        &count
    );
    
    if (count <= 0) {
        goto L_END;
    }


    matteValue_t out = native_to_value_font(
        vm,
        LoadFontEx(
            native_from_value_string_unsafe(vm, args[0]), // ok!
            args[1].value.number,
            codepoints,
            count
        )
    );
    
    MemFree(codepoints);
    return out;
  L_END:
RAYLIB_FN__END




RAYLIB_FN__ARG3(raylib_LoadFontFromImage,
    MATTE_VALUE_TYPE_STRING,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_font(
        vm,
        LoadFontFromImage(
            native_from_value_image(vm, args[0]),
            native_from_value_color(vm, args[1]),
            args[2].value.number
        )
    );
RAYLIB_FN__END



RAYLIB_FN__ARG4(raylib_LoadFontFromMemory,
    MATTE_VALUE_TYPE_STRING,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)

    uint32_t size = 0;
    uint8_t * data = matte_vm_get_memory_buffer_handle_raw_data(
        vm,
        args[1],
        &size
    );

    int count = 0;
    int * codepoints = get_codepoints(
        vm,
        store,
        args[3],
        &count
    );


    matteValue_t f = native_to_value_font(
        vm,
        LoadFontFromMemory(
            native_from_value_string_unsafe(vm, args[0]), // ok!
            data,
            size,
            args[2].value.number,
            codepoints,
            count
        )
    );
    
    MemFree(codepoints);
    return f;
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_IsFontReady,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_boolean(
        vm,
        IsFontReady(
            native_from_value_font(vm, args[0])
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG4(raylib_LoadFontData,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)

    uint32_t size = 0;
    uint8_t * data = matte_vm_get_memory_buffer_handle_raw_data(
        vm,
        args[0],
        &size
    );


    int count = 0;
    int * codepoints = get_codepoints(
        vm,
        store,
        args[2],
        &count
    );

    GlyphInfo * gs = LoadFontData(
        data,
        size,
        args[1].value.number,
        codepoints,
        count,
        args[3].value.number
    );


    matteValue_t * argss = MemAlloc(sizeof(matteValue_t)*count);
    int i;
    for(i = 0; i < count; ++i) {
        argss[i] = native_to_value_glyphInfo(vm, gs[i]);
    }
    
    matteValue_t v = matte_store_new_value(store);
    matteArray_t arr = MATTE_ARRAY_CAST(argss, matteValue_t, count);
    matte_value_into_new_object_array_ref(store, &v, &arr);
    MemFree(argss);    

    UnloadFontData(gs, count);

    
    MemFree(codepoints);
    return v;
RAYLIB_FN__END





RAYLIB_FN__ARG4(raylib_GenImageFontAtlas,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)

    uint32_t count = matte_value_object_get_number_key_count(store, args[0]);

    Rectangle * recs = NULL;
    GlyphInfo * glyphs = MemAlloc(sizeof(GlyphInfo)* count);
    
    int i;
    for(i = 0; i < count; ++i) {
        glyphs[i] = native_from_value_glyphInfo(vm, matte_value_object_access_index(store, args[0], i));
    }
    
    Image img = GenImageFontAtlas(
        glyphs, 
        &recs, 
        count, 
        args[1].value.number,
        args[2].value.number,
        args[3].value.number
    );
    MemFree(glyphs);
    
    
    matteValue_t v = matte_store_new_value(store);
    matte_value_into_new_object_ref(store, &v);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "image"), native_to_value_image(vm, img));


    matteValue_t * argss = MemAlloc(sizeof(matteValue_t) * count);    
    for(i = 0; i < count; ++i) {
        argss[i] = native_to_value_rectangle(vm, recs[i]);
    }
    matteValue_t arrV = matte_store_new_value(store);
    matteArray_t arr = MATTE_ARRAY_CAST(argss, matteValue_t, count);
    matte_value_into_new_object_array_ref(store, &arrV, &arr);

    MemFree(argss);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "recs"), arrV);
    

    MemFree(recs);    
    

    return v;
RAYLIB_FN__END



RAYLIB_FN__ARG1(raylib_UnloadFont,
    MATTE_VALUE_TYPE_OBJECT
)
    UnloadFont(
        native_from_value_font(vm, args[0])
    );
    native_unload(vm, args[0]);
RAYLIB_FN__END



RAYLIB_FN__ARG2(raylib_ExportFontAsCode,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_STRING
)
    return native_to_value_boolean(
        vm,
        ExportFontAsCode(
            native_from_value_font(vm, args[0]),
            native_from_value_string_unsafe(vm, args[1]) // ok!
        )
    );
RAYLIB_FN__END






RAYLIB_FN__ARG2(raylib_DrawFPS,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    DrawFPS(
        args[0].value.number,
        args[1].value.number
    );
RAYLIB_FN__END


RAYLIB_FN__ARG5(raylib_DrawText,
    MATTE_VALUE_TYPE_STRING,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawText(
        native_from_value_string_unsafe(vm, args[0]), // ok!
        args[1].value.number,
        args[2].value.number,
        args[3].value.number,
        native_from_value_color(vm, args[4])
    );
RAYLIB_FN__END



RAYLIB_FN__ARG6(raylib_DrawTextEx,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_STRING,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawTextEx(
        native_from_value_font(vm, args[0]),
        native_from_value_string_unsafe(vm, args[1]), // ok!
        native_from_value_vector2(vm, args[2]),
        args[3].value.number,
        args[4].value.number,
        native_from_value_color(vm, args[5])
    );
RAYLIB_FN__END

RAYLIB_FN__ARG8(raylib_DrawTextPro,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_STRING,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawTextPro(
        native_from_value_font(vm, args[0]),
        native_from_value_string_unsafe(vm, args[1]), // ok!
        native_from_value_vector2(vm, args[2]),
        native_from_value_vector2(vm, args[3]),
        args[4].value.number,
        args[5].value.number,
        args[6].value.number,
        native_from_value_color(vm, args[7])
    );
RAYLIB_FN__END



RAYLIB_FN__ARG2(raylib_MeasureText,
    MATTE_VALUE_TYPE_STRING,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_int(
        vm,
        MeasureText(
            native_from_value_string_unsafe(vm, args[0]),
            args[1].value.number
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG4(raylib_MeasureTextEx,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_STRING,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_vector2(
        vm,
        MeasureTextEx(
            native_from_value_font(vm, args[0]),
            native_from_value_string_unsafe(vm, args[1]),
            args[2].value.number,
            args[3].value.number
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_GetGlyphIndex,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_int(
        vm,
        GetGlyphIndex(
            native_from_value_font(vm, args[0]),
            args[1].value.number
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_GetGlyphInfo,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_glyphInfo(
        vm,
        GetGlyphInfo(
            native_from_value_font(vm, args[0]),
            args[1].value.number
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_GetGlyphAtlasRec,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_rectangle(
        vm,
        GetGlyphAtlasRec(
            native_from_value_font(vm, args[0]),
            args[1].value.number
        )
    );
RAYLIB_FN__END







// rmodels

RAYLIB_FN__ARG3(raylib_DrawLine3D,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawLine3D(
        native_from_value_vector3(vm, args[0]),
        native_from_value_vector3(vm, args[1]),
        native_from_value_color(vm, args[2])
    );
RAYLIB_FN__END



RAYLIB_FN__ARG2(raylib_DrawPoint3D,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawPoint3D(
        native_from_value_vector3(vm, args[0]),
        native_from_value_color(vm, args[2])
    );
RAYLIB_FN__END



RAYLIB_FN__ARG5(raylib_DrawCircle3D,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawCircle3D(
        native_from_value_vector3(vm, args[0]),
        args[1].value.number,
        native_from_value_vector3(vm, args[2]),
        args[3].value.number,
        native_from_value_color(vm, args[4])
    );
RAYLIB_FN__END



RAYLIB_FN__ARG4(raylib_DrawTriangle3D,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawTriangle3D(
        native_from_value_vector3(vm, args[0]),
        native_from_value_vector3(vm, args[1]),
        native_from_value_vector3(vm, args[2]),
        native_from_value_color(vm, args[3])
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_DrawTriangleStrip3D,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    uint32_t count = matte_value_object_get_number_key_count(store, args[0]);
    Vector3 * pts = MemAlloc(sizeof(Vector3)*count);
    
    int i;
    for(i = 0; i < count; ++i) {
        pts[i] = native_from_value_vector3(vm, matte_value_object_access_index(store, args[0], i));
    }


    DrawTriangleStrip3D(
        pts,
        count,
        native_from_value_color(vm, args[3])
    );
    
    MemFree(pts);
RAYLIB_FN__END



RAYLIB_FN__ARG5(raylib_DrawCube,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawCube(
        native_from_value_vector3(vm, args[0]),
        args[1].value.number,
        args[2].value.number,
        args[3].value.number,
        native_from_value_color(vm, args[4])
    );
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_DrawCubeV,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawCubeV(
        native_from_value_vector3(vm, args[0]),
        native_from_value_vector3(vm, args[1]),
        native_from_value_color(vm, args[2])
    );
RAYLIB_FN__END



RAYLIB_FN__ARG5(raylib_DrawCubeWires,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawCubeWires(
        native_from_value_vector3(vm, args[0]),
        args[1].value.number,
        args[2].value.number,
        args[3].value.number,
        native_from_value_color(vm, args[4])
    );
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_DrawCubeWiresV,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawCubeWiresV(
        native_from_value_vector3(vm, args[0]),
        native_from_value_vector3(vm, args[1]),
        native_from_value_color(vm, args[2])
    );
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_DrawSphere,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawSphere(
        native_from_value_vector3(vm, args[0]),
        args[1].value.number,
        native_from_value_color(vm, args[2])
    );
RAYLIB_FN__END



RAYLIB_FN__ARG5(raylib_DrawSphereEx,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawSphereEx(
        native_from_value_vector3(vm, args[0]),
        args[1].value.number,
        args[2].value.number,
        args[3].value.number,
        native_from_value_color(vm, args[4])
    );
RAYLIB_FN__END


RAYLIB_FN__ARG5(raylib_DrawSphereWires,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawSphereWires(
        native_from_value_vector3(vm, args[0]),
        args[1].value.number,
        args[2].value.number,
        args[3].value.number,
        native_from_value_color(vm, args[4])
    );
RAYLIB_FN__END



RAYLIB_FN__ARG6(raylib_DrawCylinder,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawCylinder(
        native_from_value_vector3(vm, args[0]),
        args[1].value.number,
        args[2].value.number,
        args[3].value.number,
        args[4].value.number,
        native_from_value_color(vm, args[5])
    );
RAYLIB_FN__END



RAYLIB_FN__ARG6(raylib_DrawCylinderEx,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawCylinderEx(
        native_from_value_vector3(vm, args[0]),
        native_from_value_vector3(vm, args[1]),
        args[2].value.number,
        args[3].value.number,
        args[4].value.number,
        native_from_value_color(vm, args[5])
    );
RAYLIB_FN__END




RAYLIB_FN__ARG6(raylib_DrawCylinderWires,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawCylinderWires(
        native_from_value_vector3(vm, args[0]),
        args[1].value.number,
        args[2].value.number,
        args[3].value.number,
        args[4].value.number,
        native_from_value_color(vm, args[5])
    );
RAYLIB_FN__END



RAYLIB_FN__ARG6(raylib_DrawCylinderWiresEx,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawCylinderWiresEx(
        native_from_value_vector3(vm, args[0]),
        native_from_value_vector3(vm, args[1]),
        args[2].value.number,
        args[3].value.number,
        args[4].value.number,
        native_from_value_color(vm, args[5])
    );
RAYLIB_FN__END



RAYLIB_FN__ARG6(raylib_DrawCapsule,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawCapsule(
        native_from_value_vector3(vm, args[0]),
        native_from_value_vector3(vm, args[1]),
        args[2].value.number,
        args[3].value.number,
        args[4].value.number,
        native_from_value_color(vm, args[5])
    );
RAYLIB_FN__END



RAYLIB_FN__ARG6(raylib_DrawCapsuleWires,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawCapsuleWires(
        native_from_value_vector3(vm, args[0]),
        native_from_value_vector3(vm, args[1]),
        args[2].value.number,
        args[3].value.number,
        args[4].value.number,
        native_from_value_color(vm, args[5])
    );
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_DrawPlane,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawPlane(
        native_from_value_vector3(vm, args[0]),
        native_from_value_vector2(vm, args[1]),
        native_from_value_color(vm, args[2])
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_DrawRay,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawRay(
        native_from_value_ray(vm, args[0]),
        native_from_value_color(vm, args[1])
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_DrawGrid,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    DrawGrid(
        args[0].value.number,
        args[1].value.number
    );
RAYLIB_FN__END








RAYLIB_FN__ARG1(raylib_LoadModel,
    MATTE_VALUE_TYPE_STRING
)
    return native_to_value_model(
        vm,
        LoadModel(
            native_from_value_string_unsafe(vm, args[0]) // ok!
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_LoadModelFromMesh,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_model(
        vm,
        LoadModelFromMesh(
            native_from_value_mesh(vm, args[0])
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_IsModelReady,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_boolean(
        vm,
        IsModelReady(
            native_from_value_model(vm, args[0])
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_UnloadModel,
    MATTE_VALUE_TYPE_OBJECT
)
    UnloadModel(
        native_from_value_model(vm, args[0])
    );
    
    native_unload(vm, args[0]);
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_GetModelBoundingBox,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_boundingBox(
        vm,
        GetModelBoundingBox(
            native_from_value_model(vm, args[0])
        )
    );
RAYLIB_FN__END









RAYLIB_FN__ARG4(raylib_DrawModel,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawModel(
        native_from_value_model(vm, args[0]),
        native_from_value_vector3(vm, args[1]),
        args[2].value.number,
        native_from_value_color(vm, args[3])
    );
RAYLIB_FN__END



RAYLIB_FN__ARG6(raylib_DrawModelEx,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawModelEx(
        native_from_value_model(vm, args[0]),
        native_from_value_vector3(vm, args[1]),
        native_from_value_vector3(vm, args[2]),
        args[3].value.number,
        native_from_value_vector3(vm, args[4]),
        native_from_value_color(vm, args[5])
    );
RAYLIB_FN__END


RAYLIB_FN__ARG4(raylib_DrawModelWires,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawModelWires(
        native_from_value_model(vm, args[0]),
        native_from_value_vector3(vm, args[1]),
        args[2].value.number,
        native_from_value_color(vm, args[3])
    );
RAYLIB_FN__END



RAYLIB_FN__ARG6(raylib_DrawModelWiresEx,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawModelWiresEx(
        native_from_value_model(vm, args[0]),
        native_from_value_vector3(vm, args[1]),
        native_from_value_vector3(vm, args[2]),
        args[3].value.number,
        native_from_value_vector3(vm, args[4]),
        native_from_value_color(vm, args[5])
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_DrawBoundingBox,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawBoundingBox(
        native_from_value_boundingBox(vm, args[0]),
        native_from_value_color(vm, args[1])
    );
RAYLIB_FN__END



RAYLIB_FN__ARG5(raylib_DrawBillboard,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawBillboard(
        native_from_value_camera(vm, args[0]),
        native_from_value_texture(vm, args[1]),
        native_from_value_vector3(vm, args[2]),
        args[3].value.number,
        native_from_value_color(vm, args[4])
    );
RAYLIB_FN__END

RAYLIB_FN__ARG6(raylib_DrawBillboardRec,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawBillboardRec(
        native_from_value_camera(vm, args[0]),
        native_from_value_texture(vm, args[1]),
        native_from_value_rectangle(vm, args[2]),
        native_from_value_vector3(vm, args[3]),
        native_from_value_vector2(vm, args[4]),
        native_from_value_color(vm, args[5])
    );
RAYLIB_FN__END


RAYLIB_FN__ARG9(raylib_DrawBillboardPro,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawBillboardPro(
        native_from_value_camera(vm, args[0]),
        native_from_value_texture(vm, args[1]),
        native_from_value_rectangle(vm, args[2]),
        native_from_value_vector3(vm, args[3]),
        native_from_value_vector3(vm, args[4]),
        native_from_value_vector2(vm, args[5]),
        native_from_value_vector2(vm, args[6]),
        args[7].value.number,
        native_from_value_color(vm, args[8])
    );
RAYLIB_FN__END



RAYLIB_FN__ARG2(raylib_UploadMesh,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    UploadMesh(
        native_from_value_mesh_ref(vm, args[0]),
        args[1].value.number
    );
    native_update_value_mesh(vm, args[0]);
RAYLIB_FN__END




RAYLIB_FN__ARG4(raylib_UpdateMeshBuffer,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    uint32_t size = 0;
    const uint8_t * data = matte_vm_get_memory_buffer_handle_raw_data(
        vm,
        args[2],
        &size
    );

    UpdateMeshBuffer(
        native_from_value_mesh(vm, args[0]),
        args[1].value.number,
        data,
        size,
        args[3].value.number
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_UnloadMesh,
    MATTE_VALUE_TYPE_OBJECT
)
    UnloadMesh(
        native_from_value_mesh(vm, args[0])
    );
    native_unload(vm, args[0]);
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_DrawMesh,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    DrawMesh(
        native_from_value_mesh(vm, args[0]),
        native_from_value_material(vm, args[1]),
        native_from_value_matrix(vm, args[2])
    );
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_DrawMeshInstanced,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    uint32_t count = matte_value_object_get_number_key_count(store, args[2]);
    Matrix * transforms = MemAlloc(count * sizeof(Matrix));
    uint32_t i;
    for(i = 0; i < count; ++i) {
        transforms[i] = native_from_value_matrix(vm, matte_value_object_access_index(store, args[2], i));
    }
    DrawMeshInstanced(
        native_from_value_mesh(vm, args[0]),
        native_from_value_material(vm, args[1]),
        transforms,
        count
    );
    MemFree(transforms);
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_ExportMesh,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_boolean(
        vm,
        ExportMesh(
            native_from_value_mesh(vm, args[0]),
            native_from_value_string_unsafe(vm, args[1])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_GetMeshBoundingBox,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_boundingBox(
        vm,
        GetMeshBoundingBox(
            native_from_value_mesh(vm, args[0])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_GenMeshTangents,
    MATTE_VALUE_TYPE_OBJECT
)
    GenMeshTangents(
        native_from_value_mesh_ref(vm, args[0])
    );
    native_update_value_mesh(vm, args[0]);
RAYLIB_FN__END







RAYLIB_FN__ARG2(raylib_GenMeshPoly,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_mesh(
        vm, 
        GenMeshPoly(
            args[0].value.number,
            args[1].value.number
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG4(raylib_GenMeshPlane,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_mesh(
        vm, 
        GenMeshPlane(
            args[0].value.number,
            args[1].value.number,
            args[2].value.number,
            args[3].value.number
        )
    );
RAYLIB_FN__END



RAYLIB_FN__ARG3(raylib_GenMeshCube,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_mesh(
        vm,
        GenMeshCube(
            args[0].value.number,
            args[1].value.number,
            args[2].value.number
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG3(raylib_GenMeshSphere,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_mesh(
        vm,
        GenMeshSphere(
            args[0].value.number,
            args[1].value.number,
            args[2].value.number
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG3(raylib_GenMeshHemiSphere,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_mesh(
        vm,
        GenMeshHemiSphere(
            args[0].value.number,
            args[1].value.number,
            args[2].value.number
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG3(raylib_GenMeshCylinder,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_mesh(
        vm,
        GenMeshCylinder(
            args[0].value.number,
            args[1].value.number,
            args[2].value.number
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_GenMeshCone,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_mesh(
        vm,
        GenMeshCone(
            args[0].value.number,
            args[1].value.number,
            args[2].value.number
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG4(raylib_GenMeshTorus,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_mesh(
        vm,
        GenMeshTorus(
            args[0].value.number,
            args[1].value.number,
            args[2].value.number,
            args[3].value.number
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG4(raylib_GenMeshKnot,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_mesh(
        vm,
        GenMeshKnot(
            args[0].value.number,
            args[1].value.number,
            args[2].value.number,
            args[3].value.number
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_GenMeshHeightmap,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_mesh(
        vm,
        GenMeshHeightmap(
            native_from_value_image(vm, args[0]),
            native_from_value_vector3(vm, args[1])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_GenMeshCubicmap,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_mesh(
        vm,
        GenMeshCubicmap(
            native_from_value_image(vm, args[0]),
            native_from_value_vector3(vm, args[1])
        )
    );
RAYLIB_FN__END





RAYLIB_FN__ARG1(raylib_LoadMaterials,
    MATTE_VALUE_TYPE_STRING
)
    int count;
    Material * mat = LoadMaterials(
        native_from_value_string_unsafe(vm, args[0]), // ok!
        &count
    );
    
    matteValue_t * vals = MemAlloc(sizeof(matteValue_t) * count);
    int i;
    for(i = 0; i < count; ++i) {
        vals[i] = native_to_value_material(vm, mat[i]);
    }
    
    matteValue_t outV = matte_store_new_value(store);
    matteArray_t arr = MATTE_ARRAY_CAST(vals, matteValue_t, count);
    matte_value_into_new_object_array_ref(store, &outV, &arr);
    MemFree(vals);
    return outV;    
RAYLIB_FN__END


RAYLIB_FN__ARG0(raylib_LoadMaterialDefault
)
    native_to_value_material(
        vm,
        LoadMaterialDefault()
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_IsMaterialReady,
    MATTE_VALUE_TYPE_OBJECT
)
    native_to_value_boolean(
        vm,
        IsMaterialReady(
            native_from_value_material(vm, args[0])
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_UnloadMaterial,
    MATTE_VALUE_TYPE_OBJECT
)
    UnloadMaterial(
        native_from_value_material(vm, args[0])
    );
    native_unload(vm, args[0]);
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_SetMaterialTexture,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    SetMaterialTexture(
        native_from_value_material_ref(vm, args[0]),
        args[1].value.number, 
        native_from_value_texture(vm, args[2])
    );
    native_update_value_material(vm, args[0]);
RAYLIB_FN__END



RAYLIB_FN__ARG3(raylib_SetModelMeshMaterial,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    SetModelMeshMaterial(
        native_from_value_model_ref(vm, args[0]),
        args[1].value.number, 
        args[2].value.number
    );
    native_update_value_model(vm, args[0]);
RAYLIB_FN__END









RAYLIB_FN__ARG1(raylib_LoadModelAnimations,
    MATTE_VALUE_TYPE_STRING
)
    int count;
    ModelAnimation * mat = LoadModelAnimations(
        native_from_value_string_unsafe(vm, args[0]), // ok!
        &count
    );
    
    matteValue_t * vals = MemAlloc(sizeof(matteValue_t) * count);
    int i;
    for(i = 0; i < count; ++i) {
        vals[i] = native_to_value_modelAnimation(vm, mat[i]);
    }
    
    matteValue_t outV = matte_store_new_value(store);
    matteArray_t arr = MATTE_ARRAY_CAST(vals, matteValue_t, count);
    matte_value_into_new_object_array_ref(store, &outV, &arr);
    MemFree(vals);
    return outV;    
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_UpdateModelAnimation,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    UpdateModelAnimation(
        native_from_value_model(vm, args[0]),
        native_from_value_modelAnimation(vm, args[1]),
        args[2].value.number
    );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_UnloadModelAnimation,
    MATTE_VALUE_TYPE_OBJECT
)
    UnloadModelAnimation(
        native_from_value_modelAnimation(vm, args[0])
    );
    native_unload(vm, args[0]);
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_IsModelAnimationValid,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_boolean(
        vm,
        IsModelAnimationValid(
            native_from_value_model(vm, args[0]),        
            native_from_value_modelAnimation(vm, args[1])
        )
    );
RAYLIB_FN__END






RAYLIB_FN__ARG4(raylib_CheckCollisionSpheres,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_boolean(
        vm,
        CheckCollisionSpheres(
            native_from_value_vector3(vm, args[0]),
            args[1].value.number,        
            native_from_value_vector3(vm, args[2]),        
            args[3].value.number 
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_CheckCollisionBoxes,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_boolean(
        vm,
        CheckCollisionBoxes(
            native_from_value_boundingBox(vm, args[0]),
            native_from_value_boundingBox(vm, args[1])        
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG3(raylib_CheckCollisionBoxSphere,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_boolean(
        vm,
        CheckCollisionBoxSphere(
            native_from_value_boundingBox(vm, args[0]),
            native_from_value_vector3(vm, args[1]),
            args[2].value.number
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_GetRayCollisionSphere,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_rayCollision(
        vm,
        GetRayCollisionSphere(
            native_from_value_ray(vm, args[0]),
            native_from_value_vector3(vm, args[1]),
            args[2].value.number
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_GetRayCollisionBox,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_rayCollision(
        vm,
        GetRayCollisionBox(
            native_from_value_ray(vm, args[0]),
            native_from_value_boundingBox(vm, args[1])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_GetRayCollisionMesh,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_rayCollision(
        vm,
        GetRayCollisionMesh(
            native_from_value_ray(vm, args[0]),
            native_from_value_mesh(vm, args[1]),            
            native_from_value_matrix(vm, args[2])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG4(raylib_GetRayCollisionTriangle,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_rayCollision(
        vm,
        GetRayCollisionTriangle(
            native_from_value_ray(vm, args[0]),
            native_from_value_vector3(vm, args[1]),
            native_from_value_vector3(vm, args[2]),
            native_from_value_vector3(vm, args[3])
        )
    );
RAYLIB_FN__END



RAYLIB_FN__ARG5(raylib_GetRayCollisionQuad,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_rayCollision(
        vm,
        GetRayCollisionQuad(
            native_from_value_ray(vm, args[0]),
            native_from_value_vector3(vm, args[1]),
            native_from_value_vector3(vm, args[2]),
            native_from_value_vector3(vm, args[3]),
            native_from_value_vector3(vm, args[4])
        )
    );
RAYLIB_FN__END









RAYLIB_FN__ARG0(raylib_InitAudioDevice
)
    InitAudioDevice(
    );
RAYLIB_FN__END


RAYLIB_FN__ARG0(raylib_CloseAudioDevice
)
    CloseAudioDevice(
    );
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_IsAudioDeviceReady
)
    return native_to_value_boolean(
        vm,
        IsAudioDeviceReady(
        )
    );
RAYLIB_FN__END



RAYLIB_FN__ARG1(raylib_SetMasterVolume,
    MATTE_VALUE_TYPE_NUMBER
)
    SetMasterVolume(
        args[0].value.number
    );
RAYLIB_FN__END







RAYLIB_FN__ARG1(raylib_LoadWave,
    MATTE_VALUE_TYPE_STRING
)
    return native_to_value_wave(
        vm,
        LoadWave(
            native_from_value_string_unsafe(vm, args[0])
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_LoadWaveFromMemory,
    MATTE_VALUE_TYPE_STRING,
    MATTE_VALUE_TYPE_OBJECT
)
    uint32_t size = 0;
    const uint8_t * data = matte_vm_get_memory_buffer_handle_raw_data(
        vm,
        args[1],
        &size
    );

    return native_to_value_wave(
        vm,
        LoadWaveFromMemory(
            native_from_value_string_unsafe(vm, args[0]),
            data,
            size
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_IsWaveReady,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_boolean(
        vm,
        IsWaveReady(
            native_from_value_wave(vm, args[0])
        )
    );
RAYLIB_FN__END



RAYLIB_FN__ARG1(raylib_LoadSound,
    MATTE_VALUE_TYPE_STRING
)
    return native_to_value_sound(
        vm,
        LoadSound(
            native_from_value_string_unsafe(vm, args[0])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_LoadSoundFromWave,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_sound(
        vm,
        LoadSoundFromWave(
            native_from_value_wave(vm, args[0])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_IsSoundReady,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_boolean(
        vm,
        IsSoundReady(
            native_from_value_sound(vm, args[0])
        )
    );
RAYLIB_FN__END



RAYLIB_FN__ARG2(raylib_UpdateSound,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)

    uint32_t size = 0;
    const uint8_t * data = matte_vm_get_memory_buffer_handle_raw_data(
        vm,
        args[1],
        &size
    );

    UpdateSound(
        native_from_value_sound(vm, args[0]),
        data,
        size
    );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_UnloadWave,
    MATTE_VALUE_TYPE_OBJECT
)
    UnloadWave(
        native_from_value_wave(vm, args[0])
    );
    
    native_unload(vm, args[0]);
    
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_UnloadSound,
    MATTE_VALUE_TYPE_OBJECT
)
    UnloadSound(
        native_from_value_sound(vm, args[0])
    );
    
    native_unload(vm, args[0]);
    
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_ExportWave,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_STRING
)
    return native_to_value_boolean(
        vm,
        ExportWave(
            native_from_value_wave(vm, args[0]),
            native_from_value_string_unsafe(vm, args[0])
        )
    );    
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_ExportWaveAsCode,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_STRING
)
    return native_to_value_boolean(
        vm,
        ExportWaveAsCode(
            native_from_value_wave(vm, args[0]),
            native_from_value_string_unsafe(vm, args[0])
        )
    );    
RAYLIB_FN__END







RAYLIB_FN__ARG1(raylib_PlaySound,
    MATTE_VALUE_TYPE_OBJECT
)
    PlaySound(
        native_from_value_sound(vm, args[0])
    );
    
RAYLIB_FN__END



RAYLIB_FN__ARG1(raylib_StopSound,
    MATTE_VALUE_TYPE_OBJECT
)
    StopSound(
        native_from_value_sound(vm, args[0])
    );
    
RAYLIB_FN__END




RAYLIB_FN__ARG1(raylib_PauseSound,
    MATTE_VALUE_TYPE_OBJECT
)
    PauseSound(
        native_from_value_sound(vm, args[0])
    );
    
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_ResumeSound,
    MATTE_VALUE_TYPE_OBJECT
)
    ResumeSound(
        native_from_value_sound(vm, args[0])
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_IsSoundPlaying,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_boolean(
        vm,
            
        IsSoundPlaying(
            native_from_value_sound(vm, args[0])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_SetSoundVolume,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    SetSoundVolume(
        native_from_value_sound(vm, args[0]),
        args[1].value.number
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_SetSoundPitch,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    SetSoundPitch(
        native_from_value_sound(vm, args[0]),
        args[1].value.number
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_SetSoundPan,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    SetSoundPan(
        native_from_value_sound(vm, args[0]),
        args[1].value.number
    );
RAYLIB_FN__END




RAYLIB_FN__ARG1(raylib_WaveCopy,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_wave(
        vm,
        WaveCopy(
            native_from_value_wave(vm, args[0])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_WaveCrop,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER    
)
    
    WaveCrop(
        native_from_value_wave_ref(vm, args[0]),
        args[1].value.number,
        args[2].value.number
    );
    
    native_update_value_wave(vm, args[0]);
RAYLIB_FN__END



RAYLIB_FN__ARG4(raylib_WaveFormat,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER    
)
    
    WaveFormat(
        native_from_value_wave_ref(vm, args[0]),
        args[1].value.number,
        args[2].value.number,
        args[3].value.number
    );
    
    native_update_value_wave(vm, args[0]);
RAYLIB_FN__END



RAYLIB_FN__ARG1(raylib_LoadWaveSamples,
    MATTE_VALUE_TYPE_OBJECT
)
    Wave w = native_from_value_wave(vm, args[0]);

    
    float * samples = LoadWaveSamples(
        w
    );
    
    uint32_t size = 
        w.frameCount *
        w.channels *
        (w.sampleSize / 8)
    ;

    matteValue_t out = matte_vm_create_memory_buffer_handle_from_data(
        vm,
        (void*)samples,
        size
    );
    
    UnloadWaveSamples(samples);

    return out;
RAYLIB_FN__END



RAYLIB_FN__ARG1(raylib_LoadMusicStream,
    MATTE_VALUE_TYPE_STRING
)
    return native_to_value_music(
        vm,
            
        LoadMusicStream(
            native_from_value_string_unsafe(vm, args[0]) // ok!
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_LoadMusicStreamFromMemory,
    MATTE_VALUE_TYPE_STRING,
    MATTE_VALUE_TYPE_OBJECT
)
    uint32_t size = 0;
    const uint8_t * data = matte_vm_get_memory_buffer_handle_raw_data(
        vm,
        args[1],
        &size
    );

    return native_to_value_music(
        vm,
        LoadMusicStreamFromMemory(
            native_from_value_string_unsafe(vm, args[0]),
            (void*)data,
            size
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_IsMusicReady,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_boolean(
        vm,
        IsMusicReady(
            native_from_value_music(vm, args[0]) // ok!
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_IsMusicStreamPlaying,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_boolean(
        vm,
        IsMusicStreamPlaying(
            native_from_value_music(vm, args[0]) // ok!
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_UnloadMusicStream,
    MATTE_VALUE_TYPE_OBJECT
)
    UnloadMusicStream(
        native_from_value_music(vm, args[0]) // ok!
    );
    native_unload(vm, args[0]);
    
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_PlayMusicStream,
    MATTE_VALUE_TYPE_OBJECT
)
    PlayMusicStream(
        native_from_value_music(vm, args[0]) // ok!
    );
    
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_UpdateMusicStream,
    MATTE_VALUE_TYPE_OBJECT
)
    UpdateMusicStream(
        native_from_value_music(vm, args[0]) // ok!
    );
    
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_StopMusicStream,
    MATTE_VALUE_TYPE_OBJECT
)
    StopMusicStream(
        native_from_value_music(vm, args[0]) // ok!
    );
    
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_PauseMusicStream,
    MATTE_VALUE_TYPE_OBJECT
)
    PauseMusicStream(
        native_from_value_music(vm, args[0]) // ok!
    );
    
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_ResumeMusicStream,
    MATTE_VALUE_TYPE_OBJECT
)
    ResumeMusicStream(
        native_from_value_music(vm, args[0]) // ok!
    );
    
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_SeekMusicStream,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    SeekMusicStream(
        native_from_value_music(vm, args[0]),
        args[1].value.number
    );
    
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_SetMusicVolume,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    SetMusicVolume(
        native_from_value_music(vm, args[0]),
        args[1].value.number
    );
    
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_SetMusicPitch,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    SetMusicPitch(
        native_from_value_music(vm, args[0]),
        args[1].value.number
    );
    
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_SetMusicPan,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    SetMusicPan(
        native_from_value_music(vm, args[0]),
        args[1].value.number
    );
    
RAYLIB_FN__END




RAYLIB_FN__ARG1(raylib_GetMusicTimeLength,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_float(
        vm,
        GetMusicTimeLength(
            native_from_value_music(vm, args[0])
        )
    );
    
RAYLIB_FN__END



RAYLIB_FN__ARG1(raylib_GetMusicTimePlayed,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_float(
        vm,
        GetMusicTimePlayed(
            native_from_value_music(vm, args[0])
        )
    );
    
RAYLIB_FN__END






RAYLIB_FN__ARG3(raylib_LoadAudioStream,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_audioStream(
        vm,
        LoadAudioStream(
            args[0].value.number,
            args[1].value.number,
            args[2].value.number
        )        
    );
    
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_IsAudioStreamReady,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_boolean(
        vm,
        IsAudioStreamReady(
            native_from_value_audioStream(vm, args[0])
        )        
    );
    
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_UnloadAudioStream,
    MATTE_VALUE_TYPE_OBJECT
)
    UnloadAudioStream(
        native_from_value_audioStream(vm, args[0])
    );
    native_unload(vm, args[0]);        
RAYLIB_FN__END



RAYLIB_FN__ARG2(raylib_UpdateAudioStream,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    uint32_t size = 0;
    const uint8_t * data = matte_vm_get_memory_buffer_handle_raw_data(
        vm,
        args[1],
        &size
    );

    UpdateAudioStream(
        native_from_value_audioStream(vm, args[0]),
        data,
        size
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_IsAudioStreamProcessed,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_boolean(
        vm,
        IsAudioStreamProcessed(
            native_from_value_audioStream(vm, args[0])
        )        
    );
    
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_PlayAudioStream,
    MATTE_VALUE_TYPE_OBJECT
)
    PlayAudioStream(
        native_from_value_audioStream(vm, args[0])
    );
    
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_PauseAudioStream,
    MATTE_VALUE_TYPE_OBJECT
)
    PauseAudioStream(
        native_from_value_audioStream(vm, args[0])
    );
    
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_ResumeAudioStream,
    MATTE_VALUE_TYPE_OBJECT
)
    ResumeAudioStream(
        native_from_value_audioStream(vm, args[0])
    );
    
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_IsAudioStreamPlaying,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_boolean(
        vm,
        IsAudioStreamPlaying(
            native_from_value_audioStream(vm, args[0])
        )        
    );
    
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_StopAudioStream,
    MATTE_VALUE_TYPE_OBJECT
)
    StopAudioStream(
        native_from_value_audioStream(vm, args[0])
    );
    
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_SetAudioStreamVolume,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    SetAudioStreamVolume(
        native_from_value_audioStream(vm, args[0]),
        args[1].value.number
    );
    
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_SetAudioStreamPitch,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    SetAudioStreamPitch(
        native_from_value_audioStream(vm, args[0]),
        args[1].value.number
    );
    
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_SetAudioStreamPan,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    SetAudioStreamPan(
        native_from_value_audioStream(vm, args[0]),
        args[1].value.number
    );
    
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_SetAudioStreamBufferSizeDefault,
    MATTE_VALUE_TYPE_NUMBER
)
    SetAudioStreamBufferSizeDefault(
        args[0].value.number
    );
    
RAYLIB_FN__END



RAYLIB_FN__ARG3(raylib_Clamp,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_float(
        vm,
        Clamp(
            args[0].value.number,
            args[1].value.number,
            args[2].value.number
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_Lerp,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_float(
        vm,
        Lerp(
            args[0].value.number,
            args[1].value.number,
            args[2].value.number
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_Normalize,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_float(
        vm,
        Normalize(
            args[0].value.number,
            args[1].value.number,
            args[2].value.number
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG5(raylib_Remap,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_float(
        vm,
        Remap(
            args[0].value.number,
            args[1].value.number,
            args[2].value.number,
            args[3].value.number,
            args[4].value.number
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_Wrap,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_float(
        vm,
        Wrap(
            args[0].value.number,
            args[1].value.number,
            args[2].value.number
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_FloatEquals,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_boolean(
        vm,
        FloatEquals(
            args[0].value.number,
            args[1].value.number
        )
    );
RAYLIB_FN__END



RAYLIB_FN__ARG0(raylib_Vector2Zero
)
    return native_to_value_vector2(
        vm,
        Vector2Zero(
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG0(raylib_Vector2One
)
    return native_to_value_vector2(
        vm,
        Vector2One(
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_Vector2Add,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_vector2(
        vm,
        Vector2Add(
            native_from_value_vector2(vm, args[0]),
            native_from_value_vector2(vm, args[1])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_Vector2AddValue,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_vector2(
        vm,
        Vector2AddValue(
            native_from_value_vector2(vm, args[0]),
            args[1].value.number
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_Vector2Subtract,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_vector2(
        vm,
        Vector2Subtract(
            native_from_value_vector2(vm, args[0]),
            native_from_value_vector2(vm, args[1])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_Vector2SubtractValue,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_vector2(
        vm,
        Vector2SubtractValue(
            native_from_value_vector2(vm, args[0]),
            args[1].value.number
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_Vector2Length,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_float(
        vm,
        Vector2Length(
            native_from_value_vector2(vm, args[0])
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_Vector2LengthSqr,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_float(
        vm,
        Vector2LengthSqr(
            native_from_value_vector2(vm, args[0])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_Vector2DotProduct,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_float(
        vm,
        Vector2DotProduct(
            native_from_value_vector2(vm, args[0]),
            native_from_value_vector2(vm, args[1])
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_Vector2Distance,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_float(
        vm,
        Vector2Distance(
            native_from_value_vector2(vm, args[0]),
            native_from_value_vector2(vm, args[1])
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_Vector2DistanceSqr,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_float(
        vm,
        Vector2DistanceSqr(
            native_from_value_vector2(vm, args[0]),
            native_from_value_vector2(vm, args[1])
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_Vector2Angle,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_float(
        vm,
        Vector2Angle(
            native_from_value_vector2(vm, args[0]),
            native_from_value_vector2(vm, args[1])
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_Vector2Scale,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_vector2(
        vm,
        Vector2Scale(
            native_from_value_vector2(vm, args[0]),
            args[1].value.number
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_Vector2Multiply,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_vector2(
        vm,
        Vector2Multiply(
            native_from_value_vector2(vm, args[0]),
            native_from_value_vector2(vm, args[1])
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_Vector2Negate,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_vector2(
        vm,
        Vector2Negate(
            native_from_value_vector2(vm, args[0])
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_Vector2Divide,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_vector2(
        vm,
        Vector2Divide(
            native_from_value_vector2(vm, args[0]),
            native_from_value_vector2(vm, args[1])
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_Vector2Normalize,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_vector2(
        vm,
        Vector2Normalize(
            native_from_value_vector2(vm, args[0])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_Vector2Transform,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_vector2(
        vm,
        Vector2Transform(
            native_from_value_vector2(vm, args[0]),
            native_from_value_matrix(vm, args[1])
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG3(raylib_Vector2Lerp,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_vector2(
        vm,
        Vector2Lerp(
            native_from_value_vector2(vm, args[0]),
            native_from_value_vector2(vm, args[1]),
            args[2].value.number
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_Vector2Reflect,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_vector2(
        vm,
        Vector2Reflect(
            native_from_value_vector2(vm, args[0]),
            native_from_value_vector2(vm, args[1])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_Vector2Rotate,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_vector2(
        vm,
        Vector2Rotate(
            native_from_value_vector2(vm, args[0]),
            args[1].value.number
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_Vector2MoveTowards,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_vector2(
        vm,
        Vector2MoveTowards(
            native_from_value_vector2(vm, args[0]),
            native_from_value_vector2(vm, args[1]),
            args[2].value.number
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_Vector2Invert,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_vector2(
        vm,
        Vector2Invert(
            native_from_value_vector2(vm, args[0])
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG3(raylib_Vector2Clamp,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_vector2(
        vm,
        Vector2Clamp(
            native_from_value_vector2(vm, args[0]),
            native_from_value_vector2(vm, args[1]),
            native_from_value_vector2(vm, args[2])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_Vector2ClampValue,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_vector2(
        vm,
        Vector2ClampValue(
            native_from_value_vector2(vm, args[0]),
            args[1].value.number,
            args[2].value.number
        )
    );
RAYLIB_FN__END




RAYLIB_FN__ARG2(raylib_Vector2Equals,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_boolean(
        vm,
        Vector2Equals(
            native_from_value_vector2(vm, args[0]),
            native_from_value_vector2(vm, args[1])
        )
    );
RAYLIB_FN__END







RAYLIB_FN__ARG0(raylib_Vector3Zero
)
    return native_to_value_vector3(
        vm,
        Vector3Zero(
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG0(raylib_Vector3One
)
    return native_to_value_vector3(
        vm,
        Vector3One(
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_Vector3Add,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_vector3(
        vm,
        Vector3Add(
            native_from_value_vector3(vm, args[0]),
            native_from_value_vector3(vm, args[1])
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_Vector3AddValue,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_vector3(
        vm,
        Vector3AddValue(
            native_from_value_vector3(vm, args[0]),
            args[1].value.number
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_Vector3Subtract,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_vector3(
        vm,
        Vector3Subtract(
            native_from_value_vector3(vm, args[0]),
            native_from_value_vector3(vm, args[1])
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_Vector3SubtractValue,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_vector3(
        vm,
        Vector3SubtractValue(
            native_from_value_vector3(vm, args[0]),
            args[1].value.number
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_Vector3Multiply,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_vector3(
        vm,
        Vector3Multiply(
            native_from_value_vector3(vm, args[0]),
            native_from_value_vector3(vm, args[1])
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_Vector3Scale,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_vector3(
        vm,
        Vector3Scale(
            native_from_value_vector3(vm, args[0]),
            args[1].value.number
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_Vector3CrossProduct,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_vector3(
        vm,
        Vector3CrossProduct(
            native_from_value_vector3(vm, args[0]),
            native_from_value_vector3(vm, args[1])
        )
    );
RAYLIB_FN__END



RAYLIB_FN__ARG1(raylib_Vector3Perpendicular,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_vector3(
        vm,
        Vector3Perpendicular(
            native_from_value_vector3(vm, args[0])
        )
    );
RAYLIB_FN__END



RAYLIB_FN__ARG1(raylib_Vector3Length,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_float(
        vm,
        Vector3Length(
            native_from_value_vector3(vm, args[0])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_Vector3LengthSqr,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_float(
        vm,
        Vector3LengthSqr(
            native_from_value_vector3(vm, args[0])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_Vector3DotProduct,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_float(
        vm,
        Vector3DotProduct(
            native_from_value_vector3(vm, args[0]),
            native_from_value_vector3(vm, args[1])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_Vector3Distance,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_float(
        vm,
        Vector3Distance(
            native_from_value_vector3(vm, args[0]),
            native_from_value_vector3(vm, args[1])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_Vector3DistanceSqr,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_float(
        vm,
        Vector3DistanceSqr(
            native_from_value_vector3(vm, args[0]),
            native_from_value_vector3(vm, args[1])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_Vector3Angle,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_float(
        vm,
        Vector3Angle(
            native_from_value_vector3(vm, args[0]),
            native_from_value_vector3(vm, args[1])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_Vector3Negate,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_vector3(
        vm,
        Vector3Negate(
            native_from_value_vector3(vm, args[0])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_Vector3Divide,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_vector3(
        vm,
        Vector3Divide(
            native_from_value_vector3(vm, args[0]),
            native_from_value_vector3(vm, args[1])
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_Vector3Normalize,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_vector3(
        vm,
        Vector3Normalize(
            native_from_value_vector3(vm, args[0])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_Vector3OrthoNormalize,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    Vector3 a = native_from_value_vector3(vm, args[0]);
    Vector3 b = native_from_value_vector3(vm, args[1]);
    Vector3OrthoNormalize(
        &a,
        &b
    );
    native_update_value_vector3(vm, args[0], a);
    native_update_value_vector3(vm, args[1], b);
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_Vector3Transform,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_vector3(
        vm,
        Vector3Transform(
            native_from_value_vector3(vm, args[0]),
            native_from_value_matrix(vm, args[1])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_Vector3RotateByQuaternion,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_vector3(
        vm,
        Vector3RotateByQuaternion(
            native_from_value_vector3(vm, args[0]),
            native_from_value_vector4(vm, args[1])
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG3(raylib_Vector3RotateByAxisAngle,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_vector3(
        vm,
        Vector3RotateByAxisAngle(
            native_from_value_vector3(vm, args[0]),
            native_from_value_vector3(vm, args[1]),
            args[2].value.number
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG3(raylib_Vector3Lerp,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_vector3(
        vm,
        Vector3Lerp(
            native_from_value_vector3(vm, args[0]),
            native_from_value_vector3(vm, args[1]),
            args[2].value.number
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_Vector3Reflect,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_vector3(
        vm,
        Vector3Reflect(
            native_from_value_vector3(vm, args[0]),
            native_from_value_vector3(vm, args[1])
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_Vector3Min,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_vector3(
        vm,
        Vector3Min(
            native_from_value_vector3(vm, args[0]),
            native_from_value_vector3(vm, args[1])
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_Vector3Max,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_vector3(
        vm,
        Vector3Max(
            native_from_value_vector3(vm, args[0]),
            native_from_value_vector3(vm, args[1])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG4(raylib_Vector3Barycenter,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_vector3(
        vm,
        Vector3Barycenter(
            native_from_value_vector3(vm, args[0]),
            native_from_value_vector3(vm, args[1]),
            native_from_value_vector3(vm, args[2]),
            native_from_value_vector3(vm, args[3])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_Vector3Unproject,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_vector3(
        vm,
        Vector3Unproject(
            native_from_value_vector3(vm, args[0]),
            native_from_value_matrix(vm, args[1]),
            native_from_value_matrix(vm, args[2])
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_Vector3Invert,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_vector3(
        vm,
        Vector3Invert(
            native_from_value_vector3(vm, args[0])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_Vector3Clamp,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_vector3(
        vm,
        Vector3Clamp(
            native_from_value_vector3(vm, args[0]),
            native_from_value_vector3(vm, args[1]),
            native_from_value_vector3(vm, args[2])
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG3(raylib_Vector3ClampValue,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_vector3(
        vm,
        Vector3ClampValue(
            native_from_value_vector3(vm, args[0]),
            args[1].value.number,
            args[2].value.number
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_Vector3Equals,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_boolean(
        vm,
        Vector3Equals(
            native_from_value_vector3(vm, args[0]),
            native_from_value_vector3(vm, args[1])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_Vector3Refract,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_vector3(
        vm,
        Vector3Refract(
            native_from_value_vector3(vm, args[0]),
            native_from_value_vector3(vm, args[1]),
            args[2].value.number
        )
    );
RAYLIB_FN__END







RAYLIB_FN__ARG1(raylib_MatrixDeterminant,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_float(
        vm,
        MatrixDeterminant(
            native_from_value_matrix(vm, args[0])
        )
    );
RAYLIB_FN__END



RAYLIB_FN__ARG1(raylib_MatrixTrace,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_float(
        vm,
        MatrixTrace(
            native_from_value_matrix(vm, args[0])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_MatrixTranspose,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_matrix(
        vm,
        MatrixTranspose(
            native_from_value_matrix(vm, args[0])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_MatrixInvert,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_matrix(
        vm,
        MatrixInvert(
            native_from_value_matrix(vm, args[0])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG0(raylib_MatrixIdentity
)
    return native_to_value_matrix(
        vm,
        MatrixIdentity(
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_MatrixAdd,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_matrix(
        vm,
        MatrixAdd(
            native_from_value_matrix(vm, args[0]),
            native_from_value_matrix(vm, args[1])
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_MatrixSubtract,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_matrix(
        vm,
        MatrixSubtract(
            native_from_value_matrix(vm, args[0]),
            native_from_value_matrix(vm, args[1])
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_MatrixMultiply,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_matrix(
        vm,
        MatrixMultiply(
            native_from_value_matrix(vm, args[0]),
            native_from_value_matrix(vm, args[1])
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG3(raylib_MatrixTranslate,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_matrix(
        vm,
        MatrixTranslate(
            args[0].value.number,
            args[1].value.number,
            args[2].value.number
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_MatrixRotate,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_matrix(
        vm,
        MatrixRotate(
            native_from_value_vector3(vm, args[1]),
            args[1].value.number
        )
    );
RAYLIB_FN__END



RAYLIB_FN__ARG1(raylib_MatrixRotateX,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_matrix(
        vm,
        MatrixRotateX(
            args[0].value.number
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_MatrixRotateY,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_matrix(
        vm,
        MatrixRotateY(
            args[0].value.number
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_MatrixRotateZ,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_matrix(
        vm,
        MatrixRotateZ(
            args[0].value.number
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_MatrixRotateXYZ,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_matrix(
        vm,
        MatrixRotateXYZ(
            native_from_value_vector3(vm, args[0])
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_MatrixRotateZYX,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_matrix(
        vm,
        MatrixRotateZYX(
            native_from_value_vector3(vm, args[0])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_MatrixScale,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_matrix(
        vm,
        MatrixScale(
            args[0].value.number,
            args[1].value.number,
            args[2].value.number
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG6(raylib_MatrixFrustum,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_matrix(
        vm,
        MatrixFrustum(
            args[0].value.number,
            args[1].value.number,
            args[2].value.number,
            args[3].value.number,
            args[4].value.number,
            args[5].value.number
        )
    );
RAYLIB_FN__END



RAYLIB_FN__ARG4(raylib_MatrixPerspective,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_matrix(
        vm,
        MatrixPerspective(
            args[0].value.number,
            args[1].value.number,
            args[2].value.number,
            args[3].value.number
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG6(raylib_MatrixOrtho,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_matrix(
        vm,
        MatrixOrtho(
            args[0].value.number,
            args[1].value.number,
            args[2].value.number,
            args[3].value.number,
            args[4].value.number,
            args[5].value.number
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_MatrixLookAt,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_matrix(
        vm,
        MatrixLookAt(
            native_from_value_vector3(vm, args[0]),
            native_from_value_vector3(vm, args[1]),
            native_from_value_vector3(vm, args[2])
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_QuaternionAdd,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_vector4(
        vm,
        QuaternionAdd(
            native_from_value_vector4(vm, args[0]),
            native_from_value_vector4(vm, args[1])
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_QuaternionAddValue,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_vector4(
        vm,
        QuaternionAddValue(
            native_from_value_vector4(vm, args[0]),
            args[1].value.number
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_QuaternionSubtract,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_vector4(
        vm,
        QuaternionSubtract(
            native_from_value_vector4(vm, args[0]),
            native_from_value_vector4(vm, args[1])
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_QuaternionSubtractValue,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_vector4(
        vm,
        QuaternionSubtractValue(
            native_from_value_vector4(vm, args[0]),
            args[1].value.number
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_QuaternionIdentity
)
    return native_to_value_vector4(
        vm,
        QuaternionIdentity(
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_QuaternionLength,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_float(
        vm,
        QuaternionLength(
            native_from_value_vector4(vm, args[0])
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_QuaternionNormalize,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_vector4(
        vm,
        QuaternionNormalize(
            native_from_value_vector4(vm, args[0])            
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_QuaternionInvert,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_vector4(
        vm,
        QuaternionInvert(
            native_from_value_vector4(vm, args[0])            
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_QuaternionMultiply,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_vector4(
        vm,
        QuaternionMultiply(
            native_from_value_vector4(vm, args[0]),
            native_from_value_vector4(vm, args[1])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_QuaternionDivide,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_vector4(
        vm,
        QuaternionDivide(
            native_from_value_vector4(vm, args[0]),
            native_from_value_vector4(vm, args[1])
        )
    );
RAYLIB_FN__END




RAYLIB_FN__ARG2(raylib_QuaternionScale,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_vector4(
        vm,
        QuaternionScale(
            native_from_value_vector4(vm, args[0]),
            args[1].value.number
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_QuaternionLerp,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_vector4(
        vm,
        QuaternionLerp(
            native_from_value_vector4(vm, args[0]),
            native_from_value_vector4(vm, args[1]),
            args[2].value.number
        )
    );
RAYLIB_FN__END



RAYLIB_FN__ARG3(raylib_QuaternionNlerp,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_vector4(
        vm,
        QuaternionNlerp(
            native_from_value_vector4(vm, args[0]),
            native_from_value_vector4(vm, args[1]),
            args[2].value.number
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG3(raylib_QuaternionSlerp,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_vector4(
        vm,
        QuaternionSlerp(
            native_from_value_vector4(vm, args[0]),
            native_from_value_vector4(vm, args[1]),
            args[2].value.number
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_QuaternionFromVector3ToVector3,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_vector4(
        vm,
        QuaternionFromVector3ToVector3(
            native_from_value_vector3(vm, args[0]),
            native_from_value_vector3(vm, args[1])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_QuaternionFromMatrix,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_vector4(
        vm,
        QuaternionFromMatrix(
            native_from_value_matrix(vm, args[0])
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_QuaternionToMatrix,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_matrix(
        vm,
        QuaternionToMatrix(
            native_from_value_vector4(vm, args[0])
        )
    );
RAYLIB_FN__END



RAYLIB_FN__ARG2(raylib_QuaternionFromAxisAngle,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_vector4(
        vm,
        QuaternionFromAxisAngle(
            native_from_value_vector3(vm, args[0]),
            args[1].value.number
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_QuaternionToAxisAngle,
    MATTE_VALUE_TYPE_OBJECT
)
    Vector3 outAxis;
    float outAngle;
    
    QuaternionToAxisAngle(
        native_from_value_vector4(vm, args[0]),
        &outAxis,
        &outAngle
    );
    
    matteValue_t v = matte_store_new_value(store);
    matte_value_into_new_object_ref(store, &v);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "axis"), native_to_value_vector3(vm, outAxis));
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "angle"), native_to_value_float(vm, outAngle));
    return v;
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_QuaternionFromEuler,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_NUMBER
)
    return native_to_value_vector4(
        vm,
        QuaternionFromEuler(
            args[0].value.number,
            args[1].value.number,
            args[2].value.number
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_QuaternionToEuler,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_vector3(
        vm,
        QuaternionToEuler(
            native_from_value_vector4(vm, args[0])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_QuaternionTransform,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_vector4(
        vm,
        QuaternionTransform(
            native_from_value_vector4(vm, args[0]),
            native_from_value_matrix(vm, args[1])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_QuaternionEquals,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_boolean(
        vm,
        QuaternionEquals(
            native_from_value_vector4(vm, args[0]),
            native_from_value_vector4(vm, args[1])
        )
    );
RAYLIB_FN__END




static void raymatte_init_bindings(matte_t * m) {
    // struct interfacing
    
    matte_add_external_function(m, "raylib_ImageGetData", raylib_ImageGetData, NULL, "image", NULL),

    matte_add_external_function(m, "raylib_FontGetRecs", raylib_FontGetRecs, NULL, "font", NULL),
    matte_add_external_function(m, "raylib_FontGetGlyphs", raylib_FontGetGlyphs, NULL, "font", NULL),

    matte_add_external_function(m, "raylib_MeshGetVertices", raylib_MeshGetVertices, NULL, "mesh", NULL),
    matte_add_external_function(m, "raylib_MeshGetTexCoords", raylib_MeshGetTexCoords, NULL, "mesh", NULL),
    matte_add_external_function(m, "raylib_MeshGetTexCoords2", raylib_MeshGetTexCoords2, NULL, "mesh", NULL),
    matte_add_external_function(m, "raylib_MeshGetNormals", raylib_MeshGetNormals, NULL, "mesh", NULL),
    matte_add_external_function(m, "raylib_MeshGetTangents", raylib_MeshGetTangents, NULL, "mesh", NULL),
    matte_add_external_function(m, "raylib_MeshGetColors", raylib_MeshGetColors, NULL, "mesh", NULL),
    matte_add_external_function(m, "raylib_MeshGetIndices", raylib_MeshGetIndices, NULL, "mesh", NULL),
    matte_add_external_function(m, "raylib_MeshGetAnimVertices", raylib_MeshGetAnimVertices, NULL, "mesh", NULL),
    matte_add_external_function(m, "raylib_MeshGetAnimNormals", raylib_MeshGetAnimNormals, NULL, "mesh", NULL),
    matte_add_external_function(m, "raylib_MeshGetBoneIDs", raylib_MeshGetBoneIDs, NULL, "mesh", NULL),
    matte_add_external_function(m, "raylib_MeshGetBoneWeights", raylib_MeshGetBoneWeights, NULL, "mesh", NULL),

    matte_add_external_function(m, "raylib_ModelGetMeshes", raylib_ModelGetMeshes, NULL, "model", NULL),
    matte_add_external_function(m, "raylib_ModelGetMaterials", raylib_ModelGetMaterials, NULL, "model", NULL),
    matte_add_external_function(m, "raylib_ModelGetMaterialNumbers", raylib_ModelGetMaterialNumbers, NULL, "model", NULL),
    matte_add_external_function(m, "raylib_ModelGetBones", raylib_ModelGetBones, NULL, "model", NULL),
    matte_add_external_function(m, "raylib_ModelGetBindPoses", raylib_ModelGetBindPoses, NULL, "model", NULL),

    matte_add_external_function(m, "raylib_ModelAnimationGetBones", raylib_ModelAnimationGetBones, NULL, "modelAnimation", NULL),
    matte_add_external_function(m, "raylib_ModelAnimationGetFramePoses", raylib_ModelAnimationGetFramePoses, NULL, "modelAnimation", NULL),


    matte_add_external_function(m, "raylib_WaveGetData", raylib_WaveGetData, NULL, "wave", NULL),




    //rcore: windowing
    matte_add_external_function(m, "raylib_InitWindow", raylib_InitWindow, NULL, "width", "height", "title", NULL);
    matte_add_external_function(m, "raylib_WindowShouldClose", raylib_WindowShouldClose, NULL, NULL);
    matte_add_external_function(m, "raylib_CloseWindow", raylib_CloseWindow, NULL, NULL);
    matte_add_external_function(m, "raylib_IsWindowReady", raylib_IsWindowReady, NULL, NULL);
    matte_add_external_function(m, "raylib_IsWindowFullscreen", raylib_IsWindowFullscreen, NULL, NULL);
    matte_add_external_function(m, "raylib_IsWindowHidden", raylib_IsWindowHidden, NULL, NULL);
    matte_add_external_function(m, "raylib_IsWindowMinimized", raylib_IsWindowMinimized, NULL, NULL);
    matte_add_external_function(m, "raylib_IsWindowMaximized", raylib_IsWindowMaximized, NULL, NULL);
    matte_add_external_function(m, "raylib_IsWindowFocused", raylib_IsWindowFocused, NULL, NULL);
    matte_add_external_function(m, "raylib_IsWindowResized", raylib_IsWindowResized, NULL, NULL);
    matte_add_external_function(m, "raylib_IsWindowState", raylib_IsWindowState, NULL, "flag", NULL);
    matte_add_external_function(m, "raylib_SetWindowState", raylib_SetWindowState, NULL, "flags", NULL);
    matte_add_external_function(m, "raylib_ClearWindowState", raylib_ClearWindowState, NULL, "flags", NULL);
    matte_add_external_function(m, "raylib_ToggleFullscreen", raylib_ToggleFullscreen, NULL, NULL);
    matte_add_external_function(m, "raylib_MaximizeWindow", raylib_MaximizeWindow, NULL, NULL);
    matte_add_external_function(m, "raylib_MinimizeWindow", raylib_MinimizeWindow, NULL, NULL);
    matte_add_external_function(m, "raylib_RestoreWindow", raylib_RestoreWindow, NULL, NULL);
    matte_add_external_function(m, "raylib_SetWindowIcon", raylib_SetWindowIcon, NULL, "image", NULL);
    matte_add_external_function(m, "raylib_SetWindowIcons", raylib_SetWindowIcons, NULL, "images", NULL);
    matte_add_external_function(m, "raylib_SetWindowTitle", raylib_SetWindowTitle, NULL, "title", NULL);
    matte_add_external_function(m, "raylib_SetWindowPosition", raylib_SetWindowPosition, NULL, "x", "y", NULL);
    matte_add_external_function(m, "raylib_SetWindowMonitor", raylib_SetWindowMonitor, NULL, "monitor", NULL);
    matte_add_external_function(m, "raylib_SetWindowMinSize", raylib_SetWindowMinSize, NULL, "width", "height", NULL);
    matte_add_external_function(m, "raylib_SetWindowSize", raylib_SetWindowSize, NULL, "width", "height", NULL);
    matte_add_external_function(m, "raylib_SetWindowOpacity", raylib_SetWindowOpacity, NULL, "opacity", NULL);
    matte_add_external_function(m, "raylib_GetScreenWidth", raylib_GetScreenWidth, NULL, NULL);
    matte_add_external_function(m, "raylib_GetScreenHeight", raylib_GetScreenHeight, NULL, NULL);
    matte_add_external_function(m, "raylib_GetRenderWidth", raylib_GetRenderWidth, NULL, NULL);
    matte_add_external_function(m, "raylib_GetRenderHeight", raylib_GetRenderHeight, NULL, NULL);
    matte_add_external_function(m, "raylib_GetMonitorCount", raylib_GetMonitorCount, NULL, NULL);
    matte_add_external_function(m, "raylib_GetCurrentMonitor", raylib_GetCurrentMonitor, NULL, NULL);
    matte_add_external_function(m, "raylib_GetMonitorPosition", raylib_GetMonitorPosition, NULL, "monitor", NULL);
    matte_add_external_function(m, "raylib_GetMonitorWidth", raylib_GetMonitorWidth, NULL, "monitor", NULL);
    matte_add_external_function(m, "raylib_GetMonitorHeight", raylib_GetMonitorHeight, NULL, "monitor", NULL);
    matte_add_external_function(m, "raylib_GetMonitorPhysicalWidth", raylib_GetMonitorPhysicalWidth, NULL, "monitor", NULL);
    matte_add_external_function(m, "raylib_GetMonitorPhysicalHeight", raylib_GetMonitorPhysicalHeight, NULL, "monitor", NULL);
    matte_add_external_function(m, "raylib_GetMonitorRefreshRate", raylib_GetMonitorRefreshRate, NULL, "monitor", NULL);
    matte_add_external_function(m, "raylib_GetWindowPosition", raylib_GetWindowPosition, NULL, NULL);
    matte_add_external_function(m, "raylib_GetWindowScaleDPI", raylib_GetWindowScaleDPI, NULL, NULL);
    matte_add_external_function(m, "raylib_GetMonitorName", raylib_GetMonitorName, NULL, "monitor", NULL);
    matte_add_external_function(m, "raylib_SetClipboardText", raylib_SetClipboardText, NULL, "text", NULL);
    matte_add_external_function(m, "raylib_GetClipboardText", raylib_GetClipboardText, NULL, NULL);
    matte_add_external_function(m, "raylib_EnableEventWaiting", raylib_EnableEventWaiting, NULL, NULL);
    matte_add_external_function(m, "raylib_DisableEventWaiting", raylib_DisableEventWaiting, NULL, NULL);
    
    
    matte_add_external_function(m, "raylib_SwapScreenBuffer", raylib_SwapScreenBuffer,NULL, NULL);
    matte_add_external_function(m, "raylib_PollInputEvents", raylib_PollInputEvents,NULL, NULL);
    matte_add_external_function(m, "raylib_WaitTime", raylib_WaitTime,NULL, "seconds", NULL);

    matte_add_external_function(m, "raylib_ShowCursor", raylib_ShowCursor,NULL, NULL);
    matte_add_external_function(m, "raylib_HideCursor", raylib_HideCursor,NULL, NULL);
    matte_add_external_function(m, "raylib_IsCursorHidden", raylib_IsCursorHidden,NULL, NULL);
    matte_add_external_function(m, "raylib_EnableCursor", raylib_EnableCursor,NULL, NULL);
    matte_add_external_function(m, "raylib_DisableCursor", raylib_DisableCursor,NULL, NULL);
    matte_add_external_function(m, "raylib_IsCursorOnScreen", raylib_IsCursorOnScreen,NULL, NULL);
    
    matte_add_external_function(m, "raylib_ClearBackground", raylib_ClearBackground,NULL, "color", NULL);
    matte_add_external_function(m, "raylib_BeginDrawing", raylib_BeginDrawing,NULL, NULL);
    matte_add_external_function(m, "raylib_EndDrawing", raylib_EndDrawing,NULL, NULL);
    matte_add_external_function(m, "raylib_BeginMode2D", raylib_BeginMode2D,NULL, "camera", NULL);
    matte_add_external_function(m, "raylib_EndMode2D", raylib_EndMode2D,NULL, NULL);
    matte_add_external_function(m, "raylib_BeginMode3D", raylib_BeginMode3D,NULL, "camera", NULL);
    matte_add_external_function(m, "raylib_EndMode3D", raylib_EndMode3D,NULL, NULL);
    matte_add_external_function(m, "raylib_BeginTextureMode", raylib_BeginTextureMode,NULL, "target", NULL);
    matte_add_external_function(m, "raylib_EndTextureMode", raylib_EndTextureMode,NULL, NULL);
    matte_add_external_function(m, "raylib_BeginShaderMode", raylib_BeginShaderMode,NULL,"shader",  NULL);
    matte_add_external_function(m, "raylib_EndShaderMode", raylib_EndShaderMode,NULL, NULL);
    matte_add_external_function(m, "raylib_BeginBlendMode", raylib_BeginBlendMode,NULL, "mode", NULL);
    matte_add_external_function(m, "raylib_EndBlendMode", raylib_EndBlendMode,NULL, NULL);
    matte_add_external_function(m, "raylib_BeginScissorMode", raylib_BeginScissorMode,NULL, "x", "y", "width", "height", NULL);
    matte_add_external_function(m, "raylib_EndScissorMode", raylib_EndScissorMode,NULL, NULL);
    //matte_add_external_function(m, "raylib_BeginVrStereoMode", raylib_BeginVrStereoMode,NULL, "config", NULL);
    //matte_add_external_function(m, "raylib_EndVrStereoMode", raylib_EndVrStereoMode, NULL, NULL);
    
    matte_add_external_function(m, "raylib_LoadShader", raylib_LoadShader, NULL, NULL);
    matte_add_external_function(m, "raylib_LoadShaderFromMemory", raylib_LoadShaderFromMemory, NULL, "vsFileName", "fsFileName", NULL);
    matte_add_external_function(m, "raylib_IsShaderReady", raylib_IsShaderReady, NULL, "vsCode", "fsCode",  NULL);
    matte_add_external_function(m, "raylib_GetShaderLocation", raylib_GetShaderLocation, NULL, "shader", NULL);
    matte_add_external_function(m, "raylib_GetShaderLocationAttrib", raylib_GetShaderLocationAttrib, NULL, "shader", "uniformName", NULL);
    matte_add_external_function(m, "raylib_SetShaderValueFloat", raylib_SetShaderValueFloat, NULL, "shader", "locIndex", "value", NULL);
    matte_add_external_function(m, "raylib_SetShaderValueInt", raylib_SetShaderValueInt, NULL, "shader", "locIndex", "value", NULL);
    matte_add_external_function(m, "raylib_SetShaderValueFloatV", raylib_SetShaderValueFloatV, NULL, "shader", "locIndex", "values",  "numComponents",NULL);
    matte_add_external_function(m, "raylib_SetShaderValueIntV", raylib_SetShaderValueIntV, NULL, "shader", "locIndex", "values",  "numComponents",NULL);
    matte_add_external_function(m, "raylib_SetShaderValueSampler2D", raylib_SetShaderValueSampler2D, NULL, "shader", "locIndex", "value", NULL);
    matte_add_external_function(m, "raylib_SetShaderValueSampler2DV", raylib_SetShaderValueSampler2DV, NULL, "shader", "locIndex", "values", NULL);
    matte_add_external_function(m, "raylib_SetShaderValueMatrix", raylib_SetShaderValueMatrix, NULL, "shader", "locIndex", "mat", NULL);
    matte_add_external_function(m, "raylib_SetShaderValueTexture", raylib_SetShaderValueTexture, NULL, "shader", "locIndex", "texture", NULL);
    matte_add_external_function(m, "raylib_UnloadShader", raylib_UnloadShader, NULL, "shader", NULL);
    
    
    matte_add_external_function(m, "raylib_GetMouseRay", raylib_GetMouseRay, NULL, "mousePosition", "camera", NULL);
    matte_add_external_function(m, "raylib_GetCameraMatrix", raylib_GetCameraMatrix, NULL, "camera", NULL);
    matte_add_external_function(m, "raylib_GetCameraMatrix2D", raylib_GetCameraMatrix2D, NULL, "camera", NULL);
    matte_add_external_function(m, "raylib_GetWorldToScreen", raylib_GetWorldToScreen, NULL, "position", "camera", NULL);
    matte_add_external_function(m, "raylib_GetScreenToWorld2D", raylib_GetScreenToWorld2D, NULL, "position", "camera", NULL);
    matte_add_external_function(m, "raylib_GetWorldToScreenEx", raylib_GetWorldToScreenEx, NULL, "position", "camera", "width", "height", NULL);
    matte_add_external_function(m, "raylib_GetWorldToScreen2D", raylib_GetWorldToScreen2D, NULL, "position", "camera", NULL);


    matte_add_external_function(m, "raylib_SetTargetFPS", raylib_SetTargetFPS, NULL, "fps",  NULL);
    matte_add_external_function(m, "raylib_GetFPS", raylib_GetFPS, NULL, NULL);
    matte_add_external_function(m, "raylib_GetFrameTime", raylib_GetFrameTime, NULL, NULL);
    matte_add_external_function(m, "raylib_GetTime", raylib_GetTime, NULL, NULL);
    
    
    matte_add_external_function(m, "raylib_GetRandomValue", raylib_GetRandomValue, NULL, "min", "max",  NULL);
    matte_add_external_function(m, "raylib_SetRandomSeed", raylib_SetRandomSeed, NULL, "seed", NULL);
    matte_add_external_function(m, "raylib_TakeScreenshot", raylib_TakeScreenshot, NULL, "fileName", NULL);
    matte_add_external_function(m, "raylib_SetConfigFlags", raylib_SetConfigFlags, NULL, "flags", NULL);

    matte_add_external_function(m, "raylib_TraceLog", raylib_TraceLog, NULL, "logLevel", "text",  NULL);
    matte_add_external_function(m, "raylib_SetTraceLogLevel", raylib_SetTraceLogLevel, NULL, "logLevel", NULL);

    matte_add_external_function(m, "raylib_OpenURL", raylib_OpenURL, NULL, "url", NULL);

    matte_add_external_function(m, "raylib_LoadFileData", raylib_LoadFileData, NULL, "fileName", NULL);
    matte_add_external_function(m, "raylib_SaveFileData", raylib_SaveFileData, NULL, "fileName", "bytes", NULL);
    matte_add_external_function(m, "raylib_ExportDataAsCode", raylib_ExportDataAsCode, NULL, "bytes", "fileName", NULL);
    matte_add_external_function(m, "raylib_LoadFileText", raylib_LoadFileText, NULL, "fileName", NULL);
    matte_add_external_function(m, "raylib_SaveFileText", raylib_SaveFileText, NULL, "fileName", "text", NULL);
    matte_add_external_function(m, "raylib_FileExists", raylib_FileExists, NULL, "fileName", NULL);
    matte_add_external_function(m, "raylib_DirectoryExists", raylib_DirectoryExists, NULL, "dirPath", NULL);
    matte_add_external_function(m, "raylib_IsFileExtension", raylib_IsFileExtension, NULL, "fileName", "ext", NULL);
    matte_add_external_function(m, "raylib_GetFileLength", raylib_GetFileLength, NULL, "fileName", NULL);
    matte_add_external_function(m, "raylib_GetFileExtension", raylib_GetFileExtension, NULL, "fileName", NULL);
    matte_add_external_function(m, "raylib_GetFileName", raylib_GetFileName, NULL, "filePath", NULL);
    matte_add_external_function(m, "raylib_GetFileNameWithoutExt", raylib_GetFileNameWithoutExt, NULL, "filePath",  NULL);
    matte_add_external_function(m, "raylib_GetDirectoryPath", raylib_GetDirectoryPath, NULL, "filePath", NULL);
    matte_add_external_function(m, "raylib_GetPrevDirectoryPath", raylib_GetPrevDirectoryPath, NULL, "dirPath", NULL);
    matte_add_external_function(m, "raylib_GetWorkingDirectory", raylib_GetWorkingDirectory, NULL, NULL);
    matte_add_external_function(m, "raylib_GetApplicationDirectory", raylib_GetApplicationDirectory, NULL, NULL);
    matte_add_external_function(m, "raylib_ChangeDirectory", raylib_ChangeDirectory, NULL, "dir", NULL);
    matte_add_external_function(m, "raylib_IsPathFile", raylib_IsPathFile, NULL, "path", NULL);
    matte_add_external_function(m, "raylib_LoadDirectoryFiles", raylib_LoadDirectoryFiles, NULL, "dirPath", NULL);
    matte_add_external_function(m, "raylib_LoadDirectoryFilesEx", raylib_LoadDirectoryFilesEx, NULL, "basePath", "filter", "scanSubdirs",NULL);
    matte_add_external_function(m, "raylib_IsFileDropped", raylib_IsFileDropped, NULL, NULL);
    matte_add_external_function(m, "raylib_LoadDroppedFiles", raylib_LoadDroppedFiles, NULL, NULL);
    matte_add_external_function(m, "raylib_GetFileModTime", raylib_GetFileModTime, NULL, "fileName", NULL);
    
    
    matte_add_external_function(m, "raylib_CompressData", raylib_CompressData, NULL,"bytes", NULL);
    matte_add_external_function(m, "raylib_DecompressData", raylib_DecompressData, NULL, "bytes", NULL);
    matte_add_external_function(m, "raylib_EncodeDataBase64", raylib_EncodeDataBase64, NULL, "bytes", NULL);
    matte_add_external_function(m, "raylib_DecodeDataBase64", raylib_DecodeDataBase64, NULL, "data", NULL);

    matte_add_external_function(m, "raylib_IsKeyPressed", raylib_IsKeyPressed, NULL, "key", NULL);
    matte_add_external_function(m, "raylib_IsKeyDown", raylib_IsKeyDown, NULL, "key", NULL);
    matte_add_external_function(m, "raylib_IsKeyReleased", raylib_IsKeyReleased, NULL, "key", NULL);
    matte_add_external_function(m, "raylib_IsKeyUp", raylib_IsKeyUp, NULL, "key", NULL);
    matte_add_external_function(m, "raylib_SetExitKey", raylib_SetExitKey, NULL, "key", NULL);
    matte_add_external_function(m, "raylib_GetKeyPressed", raylib_GetKeyPressed, NULL, NULL);
    matte_add_external_function(m, "raylib_GetCharPressed", raylib_GetCharPressed, NULL, NULL);

    matte_add_external_function(m, "raylib_IsGamepadAvailable", raylib_IsGamepadAvailable, NULL, "gamepad", NULL);
    matte_add_external_function(m, "raylib_GetGamepadName", raylib_GetGamepadName, NULL, "gamepad",NULL);
    matte_add_external_function(m, "raylib_IsGamepadButtonPressed", raylib_IsGamepadButtonPressed, NULL, "gamepad", "button", NULL);
    matte_add_external_function(m, "raylib_IsGamepadButtonDown", raylib_IsGamepadButtonDown, NULL, "gamepad", "button", NULL);
    matte_add_external_function(m, "raylib_IsGamepadButtonReleased", raylib_IsGamepadButtonReleased, NULL, "gamepad", "button", NULL);
    matte_add_external_function(m, "raylib_IsGamepadButtonUp", raylib_IsGamepadButtonUp, NULL, "gamepad", "button", NULL);
    matte_add_external_function(m, "raylib_GetGamepadButtonPressed", raylib_GetGamepadButtonPressed, NULL, NULL);
    matte_add_external_function(m, "raylib_GetGamepadAxisCount", raylib_GetGamepadAxisCount, NULL, "gamepad", NULL);
    matte_add_external_function(m, "raylib_GetGamepadAxisMovement", raylib_GetGamepadAxisMovement, NULL, "gamepad", "axis", NULL);
    matte_add_external_function(m, "raylib_SetGamepadMappings", raylib_SetGamepadMappings, NULL, "mapps", NULL);


    matte_add_external_function(m, "raylib_IsMouseButtonPressed", raylib_IsMouseButtonPressed, NULL, "button", NULL);
    matte_add_external_function(m, "raylib_IsMouseButtonDown", raylib_IsMouseButtonDown, NULL, "button", NULL);
    matte_add_external_function(m, "raylib_IsMouseButtonReleased", raylib_IsMouseButtonReleased, NULL, "button",  NULL);
    matte_add_external_function(m, "raylib_IsMouseButtonUp", raylib_IsMouseButtonUp, NULL,"button",  NULL);
    matte_add_external_function(m, "raylib_GetMouseX", raylib_GetMouseX, NULL, NULL);
    matte_add_external_function(m, "raylib_GetMouseY", raylib_GetMouseY, NULL, NULL);
    matte_add_external_function(m, "raylib_GetMousePosition", raylib_GetMousePosition, NULL, NULL);
    matte_add_external_function(m, "raylib_GetMouseDelta", raylib_GetMouseDelta, NULL, NULL);
    matte_add_external_function(m, "raylib_SetMousePosition", raylib_SetMousePosition, NULL, "x", "y",  NULL);
    matte_add_external_function(m, "raylib_SetMouseOffset", raylib_SetMouseOffset, NULL, "offsetX", "offsetY", NULL);
    matte_add_external_function(m, "raylib_SetMouseScale", raylib_SetMouseScale, NULL, "scaleX", "scaleY", NULL);
    matte_add_external_function(m, "raylib_GetMouseWheelMove", raylib_GetMouseWheelMove, NULL, NULL);
    matte_add_external_function(m, "raylib_GetMouseWheelMoveV", raylib_GetMouseWheelMoveV, NULL, NULL);
    matte_add_external_function(m, "raylib_SetMouseCursor", raylib_SetMouseCursor, NULL, "cursor", NULL);


    matte_add_external_function(m, "raylib_GetTouchX", raylib_GetTouchX, NULL, NULL);
    matte_add_external_function(m, "raylib_GetTouchY", raylib_GetTouchY, NULL, NULL);
    matte_add_external_function(m, "raylib_GetTouchPosition", raylib_GetTouchPosition, NULL, "index", NULL);
    matte_add_external_function(m, "raylib_GetTouchPointId", raylib_GetTouchPointId, NULL, "index", NULL);
    matte_add_external_function(m, "raylib_GetTouchPointCount", raylib_GetTouchPointCount, NULL, NULL);

    matte_add_external_function(m, "raylib_SetGesturesEnabled", raylib_SetGesturesEnabled, NULL, "flags", NULL);
    matte_add_external_function(m, "raylib_IsGestureDetected", raylib_IsGestureDetected, NULL, "gesture", NULL);
    matte_add_external_function(m, "raylib_GetGestureDetected", raylib_GetGestureDetected, NULL, NULL);
    matte_add_external_function(m, "raylib_GetGestureHoldDuration", raylib_GetGestureHoldDuration, NULL, NULL);
    matte_add_external_function(m, "raylib_GetGestureDragVector", raylib_GetGestureDragVector, NULL, NULL);
    matte_add_external_function(m, "raylib_GetGestureDragAngle", raylib_GetGestureDragAngle, NULL, NULL);
    matte_add_external_function(m, "raylib_GetGesturePinchVector", raylib_GetGesturePinchVector, NULL, NULL);
    matte_add_external_function(m, "raylib_GetGesturePinchAngle", raylib_GetGesturePinchAngle, NULL, NULL);

    matte_add_external_function(m, "raylib_UpdateCamera", raylib_UpdateCamera, NULL, "camera", "mode", NULL);
    matte_add_external_function(m, "raylib_UpdateCameraPro", raylib_UpdateCameraPro, NULL, "camera", "movement", "rotation", "zoom", NULL);
    
    
    matte_add_external_function(m, "raylib_SetShapesTexture", raylib_SetShapesTexture, NULL, "texture", "source",  NULL);
    matte_add_external_function(m, "raylib_DrawPixel", raylib_DrawPixel, NULL, "posX", "posY", "color", NULL);
    matte_add_external_function(m, "raylib_DrawPixelV", raylib_DrawPixelV, NULL, "position", "color", NULL);
    matte_add_external_function(m, "raylib_DrawLine", raylib_DrawLine, NULL, "startPosX", "startPosY", "endPosX", "endPosY", "color", NULL);
    matte_add_external_function(m, "raylib_DrawLineV", raylib_DrawLineV, NULL, "startPos", "endPos", "color", NULL);
    matte_add_external_function(m, "raylib_DrawLineEx", raylib_DrawLineEx, NULL, "startPos", "endPos", "thick", "color", NULL);
    matte_add_external_function(m, "raylib_DrawLineBezier", raylib_DrawLineBezier, NULL, "startPos", "endPos", "thick", "color", NULL);
    matte_add_external_function(m, "raylib_DrawLineBezierQuad", raylib_DrawLineBezierQuad, NULL, "startPos", "endPos", "controlPos", "thick", "color", NULL);
    matte_add_external_function(m, "raylib_DrawLineBezierCubic", raylib_DrawLineBezierCubic, NULL, "startPos", "endPos", "startControlPos", "endControlPos", "thick", "color", NULL);
    matte_add_external_function(m, "raylib_DrawLineStrip", raylib_DrawLineStrip, NULL, "points", "color", NULL);
    matte_add_external_function(m, "raylib_DrawCircle", raylib_DrawCircle, NULL, "centerX", "centerY", "radius", "color", NULL);
    matte_add_external_function(m, "raylib_DrawCircleSector", raylib_DrawCircleSector, NULL, "center", "radius", "startAngle", "endAngle", "segments", "color", NULL);
    matte_add_external_function(m, "raylib_DrawCircleSectorLines", raylib_DrawCircleSectorLines, NULL, "center", "radius", "startAngle", "endAngle", "segments", "color", NULL);
    matte_add_external_function(m, "raylib_DrawCircleGradient", raylib_DrawCircleGradient, NULL, "centerX", "centerY", "radius", "color1", "color2", NULL);
    matte_add_external_function(m, "raylib_DrawCircleV", raylib_DrawCircleV, NULL, "center", "radius", "color", NULL);
    matte_add_external_function(m, "raylib_DrawCircleLines", raylib_DrawCircleLines, NULL, "centerX", "centerY", "radius", "color", NULL);
    matte_add_external_function(m, "raylib_DrawEllipse", raylib_DrawEllipse, NULL, "centerX", "centerY", "radiusH", "radiusB", "color", NULL);
    matte_add_external_function(m, "raylib_DrawEllipseLines", raylib_DrawEllipseLines, NULL, "centerX", "centerY", "radiusH", "radiusB", "color", NULL);
    matte_add_external_function(m, "raylib_DrawRing", raylib_DrawRing, NULL, "center", "innerRadius", "outerRadius", "startAngle", "endAngle", "segments", "color", NULL);
    matte_add_external_function(m, "raylib_DrawRingLines", raylib_DrawRingLines, NULL, "center", "innerRadius", "outerRadius", "startAngle", "endAngle", "segments", "color", NULL);
    matte_add_external_function(m, "raylib_DrawRectangle", raylib_DrawRectangle, NULL, "posX", "posY", "width", "height", NULL);
    matte_add_external_function(m, "raylib_DrawRectangleV", raylib_DrawRectangleV, NULL, "position", "size", "color", NULL);
    matte_add_external_function(m, "raylib_DrawRectangleRec", raylib_DrawRectangleRec, NULL, "rec", "color", NULL);
    matte_add_external_function(m, "raylib_DrawRectanglePro", raylib_DrawRectanglePro, NULL, "rec", "origin", "rotation", "color", NULL);
    matte_add_external_function(m, "raylib_DrawRectangleGradientV", raylib_DrawRectangleGradientV, NULL, "posX", "posY", "width", "height", "color1", "color2", NULL);
    matte_add_external_function(m, "raylib_DrawRectangleGradientH", raylib_DrawRectangleGradientH, NULL, "posX", "posY", "width", "height", "color1", "color2", NULL);
    matte_add_external_function(m, "raylib_DrawRectangleGradientEx", raylib_DrawRectangleGradientEx, NULL, "rec", "col1", "col2", "col3", "col4", NULL);
    matte_add_external_function(m, "raylib_DrawRectangleLines", raylib_DrawRectangleLines, NULL, "posX", "posY", "width", "height", "color", NULL);
    matte_add_external_function(m, "raylib_DrawRectangleLinesEx", raylib_DrawRectangleLinesEx, NULL, "rec", "lineThick", "color", NULL);
    matte_add_external_function(m, "raylib_DrawRectangleRounded", raylib_DrawRectangleRounded, NULL, "rec", "roundness", "segments", "color", NULL);
    matte_add_external_function(m, "raylib_DrawRectangleRoundedLines", raylib_DrawRectangleRoundedLines, NULL, "rec", "roundness", "segments", "lineThick", "color", NULL);
    matte_add_external_function(m, "raylib_DrawTriangle", raylib_DrawTriangle, NULL, "v1", "v2", "v3", "color", NULL);
    matte_add_external_function(m, "raylib_DrawTriangleLines", raylib_DrawTriangleLines, NULL, "v1", "v2", "v3", "color", NULL);
    matte_add_external_function(m, "raylib_DrawTriangleFan", raylib_DrawTriangleFan, NULL, "points", "color", NULL);
    matte_add_external_function(m, "raylib_DrawTriangleStrip", raylib_DrawTriangleStrip, NULL, "points", "color", NULL);
    matte_add_external_function(m, "raylib_DrawPoly", raylib_DrawPoly, NULL, "center", "sides", "radius", "rotation", "color", NULL);
    matte_add_external_function(m, "raylib_DrawPolyLines", raylib_DrawPolyLines, NULL, "center", "sides", "radius", "rotation", "color", NULL);
    matte_add_external_function(m, "raylib_DrawPolyLinesEx", raylib_DrawPolyLinesEx, NULL, "center", "sides", "radius", "rotation", "lineThick", "color", NULL);


    matte_add_external_function(m, "raylib_CheckCollisionRecs", raylib_CheckCollisionRecs, NULL, "rec1", "rec2", NULL);
    matte_add_external_function(m, "raylib_CheckCollisionCircles", raylib_CheckCollisionCircles, NULL, "center1", "radius1", "vecter2", "radius2", NULL);
    matte_add_external_function(m, "raylib_CheckCollisionCircleRec", raylib_CheckCollisionCircleRec, NULL, "center", "radius", "rec", NULL);
    matte_add_external_function(m, "raylib_CheckCollisionPointRec", raylib_CheckCollisionPointRec, NULL, "point", "rec", NULL);
    matte_add_external_function(m, "raylib_CheckCollisionPointCircle", raylib_CheckCollisionPointCircle, NULL, "point", "center", "radius",  NULL);
    matte_add_external_function(m, "raylib_CheckCollisionPointTriangle", raylib_CheckCollisionPointTriangle, NULL, "point", "p1", "p2", "p3", NULL);
    matte_add_external_function(m, "raylib_CheckCollisionPointPoly", raylib_CheckCollisionPointPoly, NULL, "point", "points", NULL);
    matte_add_external_function(m, "raylib_CheckCollisionLines", raylib_CheckCollisionLines, NULL, "startPos1", "endPos1", "startPos2", "endPos2", "collisionPoint", NULL);
    matte_add_external_function(m, "raylib_CheckCollisionPointLine", raylib_CheckCollisionPointLine, NULL, "point", "p1", "p2", "threshold", NULL);
    matte_add_external_function(m, "raylib_GetCollisionRec", raylib_GetCollisionRec, NULL, "rec1", "rec2", NULL);


    // rtextures 
    
    matte_add_external_function(m, "raylib_LoadImage", raylib_LoadImage, NULL, "fileName", NULL);
    matte_add_external_function(m, "raylib_LoadImageRaw", raylib_LoadImageRaw, NULL, "fileName", "width", "height", "format", "headerSize", NULL);
    matte_add_external_function(m, "raylib_LoadImageAnim", raylib_LoadImageAnim, NULL, "fileName", NULL);
    matte_add_external_function(m, "raylib_LoadImageFromMemory", raylib_LoadImageFromMemory, NULL, "fileType", "bytes", NULL);
    matte_add_external_function(m, "raylib_LoadImageFromTexture", raylib_LoadImageFromTexture, NULL, "texture", NULL);
    matte_add_external_function(m, "raylib_LoadImageFromScreen", raylib_LoadImageFromScreen, NULL, NULL);
    matte_add_external_function(m, "raylib_IsImageReady", raylib_IsImageReady, NULL, "image", NULL);
    matte_add_external_function(m, "raylib_UnloadImage", raylib_UnloadImage, NULL, "image", NULL);
    matte_add_external_function(m, "raylib_ExportImage", raylib_ExportImage, NULL, "image", "fileName", NULL);
    matte_add_external_function(m, "raylib_ExportImageAsCode", raylib_ExportImageAsCode, NULL, "image", "fileName", NULL);

    matte_add_external_function(m, "raylib_GenImageColor", raylib_GenImageColor, NULL, "width", "height", "color",  NULL);
    matte_add_external_function(m, "raylib_GenImageGradientLinear", raylib_GenImageGradientLinear, NULL, "width", "height", "direction", "start", "end", NULL);
    matte_add_external_function(m, "raylib_GenImageGradientRadial", raylib_GenImageGradientRadial, NULL, "width", "height", "density", "inner", "outer", NULL);
    matte_add_external_function(m, "raylib_GenImageGradientSquare", raylib_GenImageGradientSquare, NULL, "width", "height", "density", "inner", "outer", NULL);
    matte_add_external_function(m, "raylib_GenImageChecked", raylib_GenImageChecked, NULL, "width", "height", "checksX", "checksY", "col1", "col2", NULL);
    matte_add_external_function(m, "raylib_GenImageWhiteNoise", raylib_GenImageWhiteNoise, NULL,"width", "height","factor",  NULL);
    matte_add_external_function(m, "raylib_GenImagePerlinNoise", raylib_GenImagePerlinNoise, NULL, "width", "height", "offsetX", "offsetY", "scale", NULL);
    matte_add_external_function(m, "raylib_GenImageCellular", raylib_GenImageCellular, NULL, "width", "height", "tileSize", NULL);
    matte_add_external_function(m, "raylib_GenImageText", raylib_GenImageText, NULL, "width", "height", "text", NULL);



    matte_add_external_function(m, "raylib_ImageCopy", raylib_ImageCopy, NULL, "image", NULL);
    matte_add_external_function(m, "raylib_ImageFromImage", raylib_ImageFromImage, NULL, "image", "rec", NULL);
    matte_add_external_function(m, "raylib_ImageText", raylib_ImageText, NULL, "text", "fontSize", "color", NULL);
    matte_add_external_function(m, "raylib_ImageTextEx", raylib_ImageTextEx, NULL, "font", "text", "fontSize", "spacing", "tint", NULL);
    matte_add_external_function(m, "raylib_ImageFormat", raylib_ImageFormat, NULL, "image", "newFormat", NULL);
    matte_add_external_function(m, "raylib_ImageToPOT", raylib_ImageToPOT, NULL, "image", "fill", NULL);
    matte_add_external_function(m, "raylib_ImageCrop", raylib_ImageCrop, NULL, "image", "crop", NULL);
    matte_add_external_function(m, "raylib_ImageAlphaCrop", raylib_ImageAlphaCrop, NULL, "image", "threshold", NULL);
    matte_add_external_function(m, "raylib_ImageAlphaClear", raylib_ImageAlphaClear, NULL, "image", "color", "threshold", NULL);
    matte_add_external_function(m, "raylib_ImageAlphaMask", raylib_ImageAlphaMask, NULL, "image", "alphaMask", NULL);
    matte_add_external_function(m, "raylib_ImageAlphaPremultiply", raylib_ImageAlphaPremultiply, NULL, "image", NULL);
    matte_add_external_function(m, "raylib_ImageBlurGaussian", raylib_ImageBlurGaussian, NULL, "image", "blurSize", NULL);
    matte_add_external_function(m, "raylib_ImageResize", raylib_ImageResize, NULL, "image", "newWidth", "newHeight", NULL);
    matte_add_external_function(m, "raylib_ImageResizeNN", raylib_ImageResizeNN, NULL, "image", "newWidth", "newHeight", NULL);
    matte_add_external_function(m, "raylib_ImageResizeCanvas", raylib_ImageResizeCanvas, NULL, "image", "newWidth", "newHeight", "offsetX", "offsetY", "fill", NULL);
    matte_add_external_function(m, "raylib_ImageMipmaps", raylib_ImageMipmaps, NULL, "image", NULL);
    matte_add_external_function(m, "raylib_ImageDither", raylib_ImageDither, NULL, "image", "rBpp", "gBpp", "bBpp", NULL);
    matte_add_external_function(m, "raylib_ImageFlipVertical", raylib_ImageFlipVertical, NULL, "image", NULL);
    matte_add_external_function(m, "raylib_ImageFlipHorizontal", raylib_ImageFlipHorizontal, NULL, "image", NULL);
    matte_add_external_function(m, "raylib_ImageRotate", raylib_ImageRotate, NULL, "image", "degrees", NULL);
    matte_add_external_function(m, "raylib_ImageRotateCW", raylib_ImageRotateCW, NULL, "image", NULL);
    matte_add_external_function(m, "raylib_ImageRotateCCW", raylib_ImageRotateCCW, NULL, "image", NULL);
    matte_add_external_function(m, "raylib_ImageColorTint", raylib_ImageColorTint, NULL, "image", "color", NULL);
    matte_add_external_function(m, "raylib_ImageColorInvert", raylib_ImageColorInvert, NULL, "image", NULL);
    matte_add_external_function(m, "raylib_ImageColorGrayscale", raylib_ImageColorGrayscale, NULL, "image", NULL);
    matte_add_external_function(m, "raylib_ImageColorContrast", raylib_ImageColorContrast, NULL, "image", "contrast", NULL);
    matte_add_external_function(m, "raylib_ImageColorBrightness", raylib_ImageColorBrightness, NULL, "image", "brightness", NULL);
    matte_add_external_function(m, "raylib_ImageColorReplace", raylib_ImageColorReplace, NULL, "image", "color", "replace", NULL);
    matte_add_external_function(m, "raylib_LoadImageColors", raylib_LoadImageColors, NULL, "image", NULL);
    matte_add_external_function(m, "raylib_LoadImagePalette", raylib_LoadImagePalette, NULL, "image", "maxPaletteSize", NULL);
    matte_add_external_function(m, "raylib_GetImageAlphaBorder", raylib_GetImageAlphaBorder, NULL, "image", "threshold", NULL);
    matte_add_external_function(m, "raylib_GetImageColor", raylib_GetImageColor, NULL, "image", "x", "y", NULL);

    matte_add_external_function(m, "raylib_ImageClearBackground", raylib_ImageClearBackground, NULL, "dst", "color",  NULL);                                                
    matte_add_external_function(m, "raylib_ImageDrawPixel", raylib_ImageDrawPixel, NULL, "dst", "posX",  "posY", "color", NULL);                                  
    matte_add_external_function(m, "raylib_ImageDrawPixelV", raylib_ImageDrawPixelV, NULL, "dst", "position",  "color", NULL);                                   
    matte_add_external_function(m, "raylib_ImageDrawLine", raylib_ImageDrawLine, NULL, "dst", "startPosX", "startPosY", "endPosX", "endPosY", "color", NULL); 
    matte_add_external_function(m, "raylib_ImageDrawLineV", raylib_ImageDrawLineV, NULL, "dst", "start",  "end", "color", NULL);                          
    matte_add_external_function(m, "raylib_ImageDrawCircle", raylib_ImageDrawCircle, NULL, "dst", "centerX",  "centerY", "radius", "color",  NULL);               
    matte_add_external_function(m, "raylib_ImageDrawCircleV", raylib_ImageDrawCircleV, NULL, "dst", "center",  "radius", "color", NULL);                        
    matte_add_external_function(m, "raylib_ImageDrawCircleLines", raylib_ImageDrawCircleLines, NULL, "dst", "centerX",  "centerY", "radius", "color",  NULL);          
    matte_add_external_function(m, "raylib_ImageDrawCircleLinesV", raylib_ImageDrawCircleLinesV, NULL, "dst", "center",  "radius", "color", NULL);                   
    matte_add_external_function(m, "raylib_ImageDrawRectangle", raylib_ImageDrawRectangle, NULL, "dst", "posX", "posY", "width", "height", "color", NULL);       
    matte_add_external_function(m, "raylib_ImageDrawRectangleV", raylib_ImageDrawRectangleV, NULL, "dst", "position",  "size", "color", NULL);                 
    matte_add_external_function(m, "raylib_ImageDrawRectangleRec", raylib_ImageDrawRectangleRec, NULL, "dst", "rec",  "color", NULL);                                
    matte_add_external_function(m, "raylib_ImageDrawRectangleLines", raylib_ImageDrawRectangleLines, NULL, "dst", "rec",  "thick", "color", NULL);                   
    matte_add_external_function(m, "raylib_ImageDraw", raylib_ImageDraw, NULL, "dst", "src",  "srcRec", "dstRec", "tint",  NULL);             
    matte_add_external_function(m, "raylib_ImageDrawText", raylib_ImageDrawText, NULL, "dst", "text", "posX", "posY", "fontSize", "color", NULL);   
    matte_add_external_function(m, "raylib_ImageDrawTextEx", raylib_ImageDrawTextEx, NULL, "dst", "font", "text", "position", "fontSize", "spacing", "tint", NULL); 



    matte_add_external_function(m, "raylib_LoadTexture", raylib_LoadTexture, NULL, "fileName",  NULL);                                                       
    matte_add_external_function(m, "raylib_LoadTextureFromImage", raylib_LoadTextureFromImage, NULL, "image", NULL);                                                       
    matte_add_external_function(m, "raylib_LoadTextureCubemap", raylib_LoadTextureCubemap, NULL, "image", "layout",  NULL);                                        
    matte_add_external_function(m, "raylib_LoadRenderTexture", raylib_LoadRenderTexture, NULL, "width", "height",  NULL);                                          
    matte_add_external_function(m, "raylib_IsTextureReady", raylib_IsTextureReady, NULL, "texture", NULL);                                                            
    matte_add_external_function(m, "raylib_UnloadTexture", raylib_UnloadTexture, NULL, "texture", NULL);                                                             
    matte_add_external_function(m, "raylib_IsRenderTextureReady", raylib_IsRenderTextureReady, NULL, "target", NULL);                                                       
    matte_add_external_function(m, "raylib_UnloadRenderTexture", raylib_UnloadRenderTexture, NULL, "target", NULL);                                                  
    matte_add_external_function(m, "raylib_UpdateTexture", raylib_UpdateTexture, NULL, "texture", "image", NULL);                                         
    matte_add_external_function(m, "raylib_UpdateTextureRec", raylib_UpdateTextureRec, NULL, "texture", "position", "image", NULL);                       


    matte_add_external_function(m, "raylib_GenTextureMipmaps", raylib_GenTextureMipmaps, NULL, "texture",  NULL);                                                        
    matte_add_external_function(m, "raylib_SetTextureFilter", raylib_SetTextureFilter, NULL, "texture", "filter",  NULL);                                              
    matte_add_external_function(m, "raylib_SetTextureWrap", raylib_SetTextureWrap, NULL, "texture", "wrap",  NULL);                                                  


    matte_add_external_function(m, "raylib_DrawTexture", raylib_DrawTexture, NULL, "texture", "posX",  "posY", "tint", NULL);                               
    matte_add_external_function(m, "raylib_DrawTextureV", raylib_DrawTextureV, NULL, "texture", "position",  "tint", NULL);                                
    matte_add_external_function(m, "raylib_DrawTextureEx", raylib_DrawTextureEx, NULL, "texture", "position",  "rotation", "scale", "tint",  NULL);  
    matte_add_external_function(m, "raylib_DrawTextureRec", raylib_DrawTextureRec, NULL, "texture", "source",  "position", "tint", NULL);            
    matte_add_external_function(m, "raylib_DrawTexturePro", raylib_DrawTexturePro, NULL, "texture", "source", "dest", "origin", "rotation", "tint", NULL); 
    matte_add_external_function(m, "raylib_DrawTextureNPatch", raylib_DrawTextureNPatch, NULL, "texture", "nPatchInfo", "dest", "origin", "rotation", "tint", NULL); 


    matte_add_external_function(m, "raylib_Fade", raylib_Fade, NULL, "color", "alpha",  NULL);                                 
    matte_add_external_function(m, "raylib_ColorToInt", raylib_ColorToInt, NULL, "color", NULL);                                          
    matte_add_external_function(m, "raylib_ColorNormalize", raylib_ColorNormalize, NULL, "color", NULL);                                  
    matte_add_external_function(m, "raylib_ColorFromNormalized", raylib_ColorFromNormalized, NULL, "normalized", NULL);                        
    matte_add_external_function(m, "raylib_ColorToHSV", raylib_ColorToHSV, NULL, "color", NULL);                                      
    matte_add_external_function(m, "raylib_ColorFromHSV", raylib_ColorFromHSV, NULL, "hue", "saturation",  "value", NULL);         
    matte_add_external_function(m, "raylib_ColorTint", raylib_ColorTint, NULL, "color", "tint",  NULL);                             
    matte_add_external_function(m, "raylib_ColorBrightness", raylib_ColorBrightness, NULL, "color", "factor",  NULL);                     
    matte_add_external_function(m, "raylib_ColorContrast", raylib_ColorContrast, NULL, "color", "contrast",  NULL);                     
    matte_add_external_function(m, "raylib_ColorAlpha", raylib_ColorAlpha, NULL, "color", "alpha",  NULL);                           
    matte_add_external_function(m, "raylib_ColorAlphaBlend", raylib_ColorAlphaBlend, NULL, "dst", "src",  "tint", NULL);              
    matte_add_external_function(m, "raylib_GetColor", raylib_GetColor, NULL, "hexValue", NULL);                                
    matte_add_external_function(m, "raylib_GetPixelColor", raylib_GetPixelColor, NULL, "bytes", "format",  NULL);                        
    matte_add_external_function(m, "raylib_SetPixelColor", raylib_SetPixelColor, NULL, "bytes", "color",  "format", NULL);            
    matte_add_external_function(m, "raylib_GetPixelDataSize", raylib_GetPixelDataSize, NULL, "width", "height",  "format", NULL);              


    matte_add_external_function(m, "raylib_GetFontDefault", raylib_GetFontDefault, NULL, NULL);                                                            
    matte_add_external_function(m, "raylib_LoadFont", raylib_LoadFont, NULL, "fileName",  NULL);                                                  
    matte_add_external_function(m, "raylib_LoadFontEx", raylib_LoadFontEx, NULL, "fileName", "fontSize", "fontChars", NULL);  
    matte_add_external_function(m, "raylib_LoadFontFromImage", raylib_LoadFontFromImage, NULL, "image", "key",  "firstChar", NULL);                        
    matte_add_external_function(m, "raylib_LoadFontFromMemory", raylib_LoadFontFromMemory, NULL, "fileType", "bytes", "fontSize", "fontChars", NULL); 
    matte_add_external_function(m, "raylib_IsFontReady", raylib_IsFontReady, NULL, "font", NULL);                                                          
    matte_add_external_function(m, "raylib_LoadFontData", raylib_LoadFontData, NULL, "bytes", "fontSize", "fontChars", "type", NULL); 
    matte_add_external_function(m, "raylib_GenImageFontAtlas", raylib_GenImageFontAtlas, NULL, "chars", "fontSize", "padding", "packMethod", NULL); 
    matte_add_external_function(m, "raylib_UnloadFont", raylib_UnloadFont, NULL, "font", NULL);                                                           
    matte_add_external_function(m, "raylib_ExportFontAsCode", raylib_ExportFontAsCode, NULL, "font", "fileName", NULL);                               


    matte_add_external_function(m, "raylib_DrawFPS", raylib_DrawFPS, NULL, "posX", "posY",  NULL);                                                     
    matte_add_external_function(m, "raylib_DrawText", raylib_DrawText, NULL, "text", "posX", "posY", "fontSize", "color", NULL);       
    matte_add_external_function(m, "raylib_DrawTextEx", raylib_DrawTextEx, NULL, "font", "text", "position", "fontSize", "spacing", "tint", NULL); 
    matte_add_external_function(m, "raylib_DrawTextPro", raylib_DrawTextPro, NULL, "font", "text", "position", "origin", "rotation", "fontSize", "spacing", "tint", NULL); 


    matte_add_external_function(m, "raylib_MeasureText", raylib_MeasureText, NULL, "text", "fontSize", NULL);                                      
    matte_add_external_function(m, "raylib_MeasureTextEx", raylib_MeasureTextEx, NULL, "font", "text", "fontSize", "spacing", NULL);    
    matte_add_external_function(m, "raylib_GetGlyphIndex", raylib_GetGlyphIndex, NULL, "font", "codepoint",  NULL);                                          
    matte_add_external_function(m, "raylib_GetGlyphInfo", raylib_GetGlyphInfo, NULL, "font", "codepoint",  NULL);                                     
    matte_add_external_function(m, "raylib_GetGlyphAtlasRec", raylib_GetGlyphAtlasRec, NULL, "font", "codepoint",  NULL);                                 





    matte_add_external_function(m, "raylib_DrawLine3D", raylib_DrawLine3D, NULL, "startPos", "endPos",  "color", NULL);                                    
    matte_add_external_function(m, "raylib_DrawPoint3D", raylib_DrawPoint3D, NULL, "position", "color",  NULL);                                                   
    matte_add_external_function(m, "raylib_DrawCircle3D", raylib_DrawCircle3D, NULL, "center", "radius",  "rotationAxis", "rotationAngle", "color",  NULL); 
    matte_add_external_function(m, "raylib_DrawTriangle3D", raylib_DrawTriangle3D, NULL, "v1", "v2",  "v3", "color", NULL);                              
    matte_add_external_function(m, "raylib_DrawTriangleStrip3D", raylib_DrawTriangleStrip3D, NULL, "points", "pointCount",  "color", NULL);                            
    matte_add_external_function(m, "raylib_DrawCube", raylib_DrawCube, NULL, "position", "width",  "height", "length", "color",  NULL);             
    matte_add_external_function(m, "raylib_DrawCubeV", raylib_DrawCubeV, NULL, "position", "size",  "color", NULL);                                       
    matte_add_external_function(m, "raylib_DrawCubeWires", raylib_DrawCubeWires, NULL, "position", "width",  "height", "length", "color",  NULL);        
    matte_add_external_function(m, "raylib_DrawCubeWiresV", raylib_DrawCubeWiresV, NULL, "position", "size",  "color", NULL);                                  
    matte_add_external_function(m, "raylib_DrawSphere", raylib_DrawSphere, NULL, "centerPos", "radius",  "color", NULL);                                     
    matte_add_external_function(m, "raylib_DrawSphereEx", raylib_DrawSphereEx, NULL, "centerPos", "radius",  "rings", "slices", "color",  NULL);            
    matte_add_external_function(m, "raylib_DrawSphereWires", raylib_DrawSphereWires, NULL, "centerPos", "radius",  "rings", "slices", "color",  NULL);         
    matte_add_external_function(m, "raylib_DrawCylinder", raylib_DrawCylinder, NULL, "position", "radiusTop", "radiusBottom", "height", "slices", "color", NULL); 
    matte_add_external_function(m, "raylib_DrawCylinderEx", raylib_DrawCylinderEx, NULL, "startPos", "endPos", "startRadius", "endRadius", "sides", "color", NULL); 
    matte_add_external_function(m, "raylib_DrawCylinderWires", raylib_DrawCylinderWires, NULL, "position", "radiusTop", "radiusBottom", "height", "slices", "color", NULL); 
    matte_add_external_function(m, "raylib_DrawCylinderWiresEx", raylib_DrawCylinderWiresEx, NULL, "startPos", "endPos", "startRadius", "endRadius", "sides", "color", NULL); 
    matte_add_external_function(m, "raylib_DrawCapsule", raylib_DrawCapsule, NULL, "startPos", "endPos", "radius", "slices", "rings", "color", NULL); 
    matte_add_external_function(m, "raylib_DrawCapsuleWires", raylib_DrawCapsuleWires, NULL, "startPos", "endPos", "radius", "slices", "rings", "color", NULL); 
    matte_add_external_function(m, "raylib_DrawPlane", raylib_DrawPlane, NULL, "centerPos", "size",  "color", NULL);                                      
    matte_add_external_function(m, "raylib_DrawRay", raylib_DrawRay, NULL, "ray", "color",  NULL);                                                                
    matte_add_external_function(m, "raylib_DrawGrid", raylib_DrawGrid, NULL, "slices", "spacing",  NULL);                                                          






    matte_add_external_function(m, "raylib_LoadModel", raylib_LoadModel, NULL, "fileName",  NULL);                                                
    matte_add_external_function(m, "raylib_LoadModelFromMesh", raylib_LoadModelFromMesh, NULL, "mesh", NULL);                                                   
    matte_add_external_function(m, "raylib_IsModelReady", raylib_IsModelReady, NULL, "model", NULL);                                                       
    matte_add_external_function(m, "raylib_UnloadModel", raylib_UnloadModel, NULL, "model", NULL);                                                        
    matte_add_external_function(m, "raylib_GetModelBoundingBox", raylib_GetModelBoundingBox, NULL, "model", NULL);                                         


    matte_add_external_function(m, "raylib_DrawModel", raylib_DrawModel, NULL, "model", "position",  "scale", "tint", NULL);               
    matte_add_external_function(m, "raylib_DrawModelEx", raylib_DrawModelEx, NULL, "model", "position", "rotationAxis", "rotationAngle", "scale", "tint", NULL); 
    matte_add_external_function(m, "raylib_DrawModelWires", raylib_DrawModelWires, NULL, "model", "position",  "scale", "tint", NULL);          
    matte_add_external_function(m, "raylib_DrawModelWiresEx", raylib_DrawModelWiresEx, NULL, "model", "position", "rotationAxis", "rotationAngle", "scale", "tint", NULL); 
    matte_add_external_function(m, "raylib_DrawBoundingBox", raylib_DrawBoundingBox, NULL, "box", "color",  NULL);                                   
    matte_add_external_function(m, "raylib_DrawBillboard", raylib_DrawBillboard, NULL, "camera", "texture",  "position", "size", "tint",  NULL);   
    matte_add_external_function(m, "raylib_DrawBillboardRec", raylib_DrawBillboardRec, NULL, "camera", "texture", "source", "position", "size", "tint", NULL); 
    matte_add_external_function(m, "raylib_DrawBillboardPro", raylib_DrawBillboardPro, NULL, "camera", "texture", "source", "position", "up", "size", "origin", "rotation", "tint", NULL); 


    matte_add_external_function(m, "raylib_UploadMesh", raylib_UploadMesh, NULL, "mesh", "dynamic",  NULL);                                            
    matte_add_external_function(m, "raylib_UpdateMeshBuffer", raylib_UpdateMeshBuffer, NULL, "mesh", "index", "bytes", "offset", NULL); 
    matte_add_external_function(m, "raylib_UnloadMesh", raylib_UnloadMesh, NULL, "mesh", NULL);                                                           
    matte_add_external_function(m, "raylib_DrawMesh", raylib_DrawMesh, NULL, "mesh", "material",  "transform", NULL);                        
    matte_add_external_function(m, "raylib_DrawMeshInstanced", raylib_DrawMeshInstanced, NULL, "mesh", "material", "transforms", NULL); 
    matte_add_external_function(m, "raylib_ExportMesh", raylib_ExportMesh, NULL, "mesh", "fileName", NULL);                                     
    matte_add_external_function(m, "raylib_GetMeshBoundingBox", raylib_GetMeshBoundingBox, NULL, "mesh", NULL);                                            
    matte_add_external_function(m, "raylib_GenMeshTangents", raylib_GenMeshTangents, NULL, "mesh",  NULL);                                                     


    matte_add_external_function(m, "raylib_GenMeshPoly", raylib_GenMeshPoly, NULL, "sides", "radius",  NULL);                                            
    matte_add_external_function(m, "raylib_GenMeshPlane", raylib_GenMeshPlane, NULL, "width", "length",  "resX", "resZ", NULL);                     
    matte_add_external_function(m, "raylib_GenMeshCube", raylib_GenMeshCube, NULL, "width", "height",  "length", NULL);                            
    matte_add_external_function(m, "raylib_GenMeshSphere", raylib_GenMeshSphere, NULL, "radius", "rings",  "slices", NULL);                              
    matte_add_external_function(m, "raylib_GenMeshHemiSphere", raylib_GenMeshHemiSphere, NULL, "radius", "rings",  "slices", NULL);                          
    matte_add_external_function(m, "raylib_GenMeshCylinder", raylib_GenMeshCylinder, NULL, "radius", "height",  "slices", NULL);                         
    matte_add_external_function(m, "raylib_GenMeshCone", raylib_GenMeshCone, NULL, "radius", "height",  "slices", NULL);                             
    matte_add_external_function(m, "raylib_GenMeshTorus", raylib_GenMeshTorus, NULL, "radius", "size",  "radSeg", "sides", NULL);                   
    matte_add_external_function(m, "raylib_GenMeshKnot", raylib_GenMeshKnot, NULL, "radius", "size",  "radSeg", "sides", NULL);                    
    matte_add_external_function(m, "raylib_GenMeshHeightmap", raylib_GenMeshHeightmap, NULL, "heightmap", "size",  NULL);                                 
    matte_add_external_function(m, "raylib_GenMeshCubicmap", raylib_GenMeshCubicmap, NULL, "cubicmap", "cubeSize",  NULL);                               


    matte_add_external_function(m, "raylib_LoadMaterials", raylib_LoadMaterials, NULL, "fileName", "materialCount", NULL);                    
    matte_add_external_function(m, "raylib_LoadMaterialDefault", raylib_LoadMaterialDefault, NULL, NULL);                                                   
    matte_add_external_function(m, "raylib_IsMaterialReady", raylib_IsMaterialReady, NULL, "material", NULL);                                              
    matte_add_external_function(m, "raylib_UnloadMaterial", raylib_UnloadMaterial, NULL, "material", NULL);                                               
    matte_add_external_function(m, "raylib_SetMaterialTexture", raylib_SetMaterialTexture, NULL, "material", "mapType",  "texture", NULL);          
    matte_add_external_function(m, "raylib_SetModelMeshMaterial", raylib_SetModelMeshMaterial, NULL, "model", "meshId",  "materialId", NULL);                  


    matte_add_external_function(m, "raylib_LoadModelAnimations", raylib_LoadModelAnimations, NULL, "fileName", "animCount", NULL);   
    matte_add_external_function(m, "raylib_UpdateModelAnimation", raylib_UpdateModelAnimation, NULL, "model", "anim",  "frame", NULL);               
    matte_add_external_function(m, "raylib_UnloadModelAnimation", raylib_UnloadModelAnimation, NULL, "anim", NULL);                                       
    matte_add_external_function(m, "raylib_IsModelAnimationValid", raylib_IsModelAnimationValid, NULL, "model", "anim",  NULL);                         


    matte_add_external_function(m, "raylib_CheckCollisionSpheres", raylib_CheckCollisionSpheres, NULL, "center1", "radius1",  "center2", "radius2", NULL);   
    matte_add_external_function(m, "raylib_CheckCollisionBoxes", raylib_CheckCollisionBoxes, NULL, "box1", "box2",  NULL);                                 
    matte_add_external_function(m, "raylib_CheckCollisionBoxSphere", raylib_CheckCollisionBoxSphere, NULL, "box", "center",  "radius", NULL);                  
    matte_add_external_function(m, "raylib_GetRayCollisionSphere", raylib_GetRayCollisionSphere, NULL, "ray", "center",  "radius", NULL);                    
    matte_add_external_function(m, "raylib_GetRayCollisionBox", raylib_GetRayCollisionBox, NULL, "ray", "box",  NULL);                                    
    matte_add_external_function(m, "raylib_GetRayCollisionMesh", raylib_GetRayCollisionMesh, NULL, "ray", "mesh",  "transform", NULL);                       
    matte_add_external_function(m, "raylib_GetRayCollisionTriangle", raylib_GetRayCollisionTriangle, NULL, "ray", "p1",  "p2", "p3", NULL);            
    matte_add_external_function(m, "raylib_GetRayCollisionQuad", raylib_GetRayCollisionQuad, NULL, "ray", "p1",  "p2", "p3", "p4",  NULL);    

    matte_add_external_function(m, "raylib_InitAudioDevice", raylib_InitAudioDevice, NULL, NULL);                                     
    matte_add_external_function(m, "raylib_CloseAudioDevice", raylib_CloseAudioDevice, NULL, NULL);                                    
    matte_add_external_function(m, "raylib_IsAudioDeviceReady", raylib_IsAudioDeviceReady, NULL, NULL);                                  
    matte_add_external_function(m, "raylib_SetMasterVolume", raylib_SetMasterVolume, NULL, "volume", NULL);                             


    matte_add_external_function(m, "raylib_LoadWave", raylib_LoadWave, NULL, "fileName",  NULL);                            
    matte_add_external_function(m, "raylib_LoadWaveFromMemory", raylib_LoadWaveFromMemory, NULL, "fileType", "bytes", NULL); 
    matte_add_external_function(m, "raylib_IsWaveReady", raylib_IsWaveReady, NULL, "wave", NULL);                                    
    matte_add_external_function(m, "raylib_LoadSound", raylib_LoadSound, NULL, "fileName",  NULL);                          
    matte_add_external_function(m, "raylib_LoadSoundFromWave", raylib_LoadSoundFromWave, NULL, "wave", NULL);                             
    matte_add_external_function(m, "raylib_IsSoundReady", raylib_IsSoundReady, NULL, "sound", NULL);                                 
    matte_add_external_function(m, "raylib_UpdateSound", raylib_UpdateSound, "sound", "data", "sampleCount", NULL); 
    matte_add_external_function(m, "raylib_UnloadWave", raylib_UnloadWave, NULL, "wave", NULL);                                     
    matte_add_external_function(m, "raylib_UnloadSound", raylib_UnloadSound, NULL, "sound", NULL);                                  
    matte_add_external_function(m, "raylib_ExportWave", raylib_ExportWave, NULL, "wave", "fileName", NULL);               
    matte_add_external_function(m, "raylib_ExportWaveAsCode", raylib_ExportWaveAsCode, "NULL", "wave", "fileName", NULL);         


    matte_add_external_function(m, "raylib_PlaySound", raylib_PlaySound, NULL, "sound", NULL);                                    
    matte_add_external_function(m, "raylib_StopSound", raylib_StopSound, NULL, "sound", NULL);                                    
    matte_add_external_function(m, "raylib_PauseSound", raylib_PauseSound, NULL, "sound", NULL);                                   
    matte_add_external_function(m, "raylib_ResumeSound", raylib_ResumeSound, NULL, "sound", NULL);                                  
    matte_add_external_function(m, "raylib_IsSoundPlaying", raylib_IsSoundPlaying, NULL, "sound", NULL);                               
    matte_add_external_function(m, "raylib_SetSoundVolume", raylib_SetSoundVolume, NULL, "sound", "volume",  NULL);                 
    matte_add_external_function(m, "raylib_SetSoundPitch", raylib_SetSoundPitch, NULL, "sound", "pitch",  NULL);                   
    matte_add_external_function(m, "raylib_SetSoundPan", raylib_SetSoundPan, NULL, "sound", "pan",  NULL);                       
    matte_add_external_function(m, "raylib_WaveCopy", raylib_WaveCopy, NULL, "wave", NULL);                                       
    matte_add_external_function(m, "raylib_WaveCrop", raylib_WaveCrop, NULL, "wave", "initSample",  "finalSample", NULL);     
    matte_add_external_function(m, "raylib_WaveFormat", raylib_WaveFormat, NULL, "wave", "sampleRate",  "sampleSize", "channels", NULL); 
    matte_add_external_function(m, "raylib_LoadWaveSamples", raylib_LoadWaveSamples, NULL, "wave", NULL);                              


    matte_add_external_function(m, "raylib_LoadMusicStream", raylib_LoadMusicStream, NULL, "fileName",  NULL);                    
    matte_add_external_function(m, "raylib_LoadMusicStreamFromMemory", raylib_LoadMusicStreamFromMemory, NULL, "fileType", "bytes", NULL); 
    matte_add_external_function(m, "raylib_IsMusicReady", raylib_IsMusicReady, NULL, "music", NULL);                                 
    matte_add_external_function(m, "raylib_UnloadMusicStream", raylib_UnloadMusicStream, NULL, "music", NULL);                            
    matte_add_external_function(m, "raylib_PlayMusicStream", raylib_PlayMusicStream, NULL, "music", NULL);                              
    matte_add_external_function(m, "raylib_IsMusicStreamPlaying", raylib_IsMusicStreamPlaying, NULL, "music", NULL);                         
    matte_add_external_function(m, "raylib_UpdateMusicStream", raylib_UpdateMusicStream, NULL, "music", NULL);                            
    matte_add_external_function(m, "raylib_StopMusicStream", raylib_StopMusicStream, NULL, "music", NULL);                              
    matte_add_external_function(m, "raylib_PauseMusicStream", raylib_PauseMusicStream, NULL, "music", NULL);                             
    matte_add_external_function(m, "raylib_ResumeMusicStream", raylib_ResumeMusicStream, NULL, "music", NULL);                            
    matte_add_external_function(m, "raylib_SeekMusicStream", raylib_SeekMusicStream, NULL, "music", "position",  NULL);              
    matte_add_external_function(m, "raylib_SetMusicVolume", raylib_SetMusicVolume, NULL, "music", "volume",  NULL);                 
    matte_add_external_function(m, "raylib_SetMusicPitch", raylib_SetMusicPitch, NULL, "music", "pitch",  NULL);                   
    matte_add_external_function(m, "raylib_SetMusicPan", raylib_SetMusicPan, NULL, "music", "pan",  NULL);                       
    matte_add_external_function(m, "raylib_GetMusicTimeLength", raylib_GetMusicTimeLength, NULL, "music", NULL);                          
    matte_add_external_function(m, "raylib_GetMusicTimePlayed", raylib_GetMusicTimePlayed, NULL, "music", NULL);                          


    matte_add_external_function(m, "raylib_LoadAudioStream", raylib_LoadAudioStream, NULL, "sampleRate", "sampleSize", "channels", NULL); 
    matte_add_external_function(m, "raylib_IsAudioStreamReady", raylib_IsAudioStreamReady, NULL, "stream", NULL);                    
    matte_add_external_function(m, "raylib_UnloadAudioStream", raylib_UnloadAudioStream, NULL, "stream", NULL);                     
    matte_add_external_function(m, "raylib_UpdateAudioStream", raylib_UpdateAudioStream, NULL, "stream", "bytes", NULL); 
    matte_add_external_function(m, "raylib_IsAudioStreamProcessed", raylib_IsAudioStreamProcessed, NULL, "stream", NULL);                
    matte_add_external_function(m, "raylib_PlayAudioStream", raylib_PlayAudioStream, NULL, "stream", NULL);                       
    matte_add_external_function(m, "raylib_PauseAudioStream", raylib_PauseAudioStream, NULL, "stream", NULL);                      
    matte_add_external_function(m, "raylib_ResumeAudioStream", raylib_ResumeAudioStream, NULL, "stream", NULL);                     
    matte_add_external_function(m, "raylib_IsAudioStreamPlaying", raylib_IsAudioStreamPlaying, NULL, "stream", NULL);                  
    matte_add_external_function(m, "raylib_StopAudioStream", raylib_StopAudioStream, NULL, "stream", NULL);                       
    matte_add_external_function(m, "raylib_SetAudioStreamVolume", raylib_SetAudioStreamVolume, NULL, "stream", "volume",  NULL);    
    matte_add_external_function(m, "raylib_SetAudioStreamPitch", raylib_SetAudioStreamPitch, NULL, "stream", "pitch",  NULL);      
    matte_add_external_function(m, "raylib_SetAudioStreamPan", raylib_SetAudioStreamPan, NULL, "stream", "pan",  NULL);          
    matte_add_external_function(m, "raylib_SetAudioStreamBufferSizeDefault", raylib_SetAudioStreamBufferSizeDefault, NULL, "size", NULL);                 
    /*
    matte_add_external_function(m, "raylib_SetAudioStreamCallback", raylib_SetAudioStreamCallback, NULL, "stream", "callback",  NULL);  

    matte_add_external_function(m, "raylib_AttachAudioStreamProcessor", raylib_AttachAudioStreamProcessor, NULL, "stream", "processor",  NULL); 
    matte_add_external_function(m, "raylib_DetachAudioStreamProcessor", raylib_DetachAudioStreamProcessor, NULL, "stream", "processor",  NULL); 

    matte_add_external_function(m, "raylib_AttachAudioMixedProcessor", raylib_AttachAudioMixedProcessor, NULL, "processor", NULL); 
    matte_add_external_function(m, "raylib_DetachAudioMixedProcessor", raylib_DetachAudioMixedProcessor, NULL, "processor", NULL); 
    */

    // raymath 

    matte_add_external_function(m, "raylib_Clamp", raylib_Clamp, NULL, "value","min", "max",NULL);                             
    matte_add_external_function(m, "raylib_Lerp", raylib_Lerp, NULL, "start","end", "amount",NULL);                           
    matte_add_external_function(m, "raylib_Normalize", raylib_Normalize, NULL, "value","start", "end",NULL);                       
    matte_add_external_function(m, "raylib_Remap", raylib_Remap, NULL, "value","inputStart", "inputEnd","outputStart", "outputEnd",NULL); 
    matte_add_external_function(m, "raylib_Wrap", raylib_Wrap, NULL, "value","min", "max",NULL);                              
    matte_add_external_function(m, "raylib_FloatEquals", raylib_FloatEquals, NULL, "x","y", NULL);                                          


    matte_add_external_function(m, "raylib_Vector2Zero", raylib_Vector2Zero, NULL, NULL);                                                  
    matte_add_external_function(m, "raylib_Vector2One", raylib_Vector2One, NULL, NULL);                                                   
    matte_add_external_function(m, "raylib_Vector2Add", raylib_Vector2Add, NULL, "v1","v2", NULL);                                 
    matte_add_external_function(m, "raylib_Vector2AddValue", raylib_Vector2AddValue, NULL, "v","add", NULL);                              
    matte_add_external_function(m, "raylib_Vector2Subtract", raylib_Vector2Subtract, NULL, "v1","v2", NULL);                            
    matte_add_external_function(m, "raylib_Vector2SubtractValue", raylib_Vector2SubtractValue, NULL, "v","sub", NULL);                         
    matte_add_external_function(m, "raylib_Vector2Length", raylib_Vector2Length, NULL, "v", NULL);                                             
    matte_add_external_function(m, "raylib_Vector2LengthSqr", raylib_Vector2LengthSqr, NULL, "v", NULL);                                          
    matte_add_external_function(m, "raylib_Vector2DotProduct", raylib_Vector2DotProduct, NULL, "v1","v2", NULL);                            
    matte_add_external_function(m, "raylib_Vector2Distance", raylib_Vector2Distance, NULL, "v1","v2", NULL);                              
    matte_add_external_function(m, "raylib_Vector2DistanceSqr", raylib_Vector2DistanceSqr, NULL, "v1","v2", NULL);                           
    matte_add_external_function(m, "raylib_Vector2Angle", raylib_Vector2Angle, NULL, "v1","v2", NULL);                                 
    matte_add_external_function(m, "raylib_Vector2Scale", raylib_Vector2Scale, NULL, "v","scale", NULL);                               
    matte_add_external_function(m, "raylib_Vector2Multiply", raylib_Vector2Multiply, NULL, "v1","v2", NULL);                            
    matte_add_external_function(m, "raylib_Vector2Negate", raylib_Vector2Negate, NULL, "v", NULL);                                           
    matte_add_external_function(m, "raylib_Vector2Divide", raylib_Vector2Divide, NULL, "v1","v2", NULL);                              
    matte_add_external_function(m, "raylib_Vector2Normalize", raylib_Vector2Normalize, NULL, "v", NULL);                                        
    matte_add_external_function(m, "raylib_Vector2Transform", raylib_Vector2Transform, NULL, "v","mat", NULL);                            
    matte_add_external_function(m, "raylib_Vector2Lerp", raylib_Vector2Lerp, NULL, "v1","v2", "amount",NULL);                  
    matte_add_external_function(m, "raylib_Vector2Reflect", raylib_Vector2Reflect, NULL, "v","normal", NULL);                          
    matte_add_external_function(m, "raylib_Vector2Rotate", raylib_Vector2Rotate, NULL, "v","angle", NULL);                              
    matte_add_external_function(m, "raylib_Vector2MoveTowards", raylib_Vector2MoveTowards, NULL, "v","target", "maxDistance",NULL);   
    matte_add_external_function(m, "raylib_Vector2Invert", raylib_Vector2Invert, NULL, "v", NULL);                                           
    matte_add_external_function(m, "raylib_Vector2Clamp", raylib_Vector2Clamp, NULL, "v","min", "max",NULL);                  
    matte_add_external_function(m, "raylib_Vector2ClampValue", raylib_Vector2ClampValue, NULL, "v","min", "max",NULL);                 
    matte_add_external_function(m, "raylib_Vector2Equals", raylib_Vector2Equals, NULL, "p","q", NULL);                                    


    matte_add_external_function(m, "raylib_Vector3Zero", raylib_Vector3Zero, NULL, NULL);                                                  
    matte_add_external_function(m, "raylib_Vector3One", raylib_Vector3One, NULL, NULL);                                                   
    matte_add_external_function(m, "raylib_Vector3Add", raylib_Vector3Add, NULL, "v1","v2", NULL);                                 
    matte_add_external_function(m, "raylib_Vector3AddValue", raylib_Vector3AddValue, NULL, "v","add", NULL);                              
    matte_add_external_function(m, "raylib_Vector3Subtract", raylib_Vector3Subtract, NULL, "v1","v2", NULL);                            
    matte_add_external_function(m, "raylib_Vector3SubtractValue", raylib_Vector3SubtractValue, NULL, "v","sub", NULL);                         
    matte_add_external_function(m, "raylib_Vector3Scale", raylib_Vector3Scale, NULL, "v","scalar", NULL);                              
    matte_add_external_function(m, "raylib_Vector3Multiply", raylib_Vector3Multiply, NULL, "v1","v2", NULL);                            
    matte_add_external_function(m, "raylib_Vector3CrossProduct", raylib_Vector3CrossProduct, NULL, "v1","v2", NULL);                        
    matte_add_external_function(m, "raylib_Vector3Perpendicular", raylib_Vector3Perpendicular, NULL, "v", NULL);                                    
    matte_add_external_function(m, "raylib_Vector3Length", raylib_Vector3Length, NULL, "v", NULL);                                       
    matte_add_external_function(m, "raylib_Vector3LengthSqr", raylib_Vector3LengthSqr, NULL, "v", NULL);                                    
    matte_add_external_function(m, "raylib_Vector3DotProduct", raylib_Vector3DotProduct, NULL, "v1","v2", NULL);                            
    matte_add_external_function(m, "raylib_Vector3Distance", raylib_Vector3Distance, NULL, "v1","v2", NULL);                              
    matte_add_external_function(m, "raylib_Vector3DistanceSqr", raylib_Vector3DistanceSqr, NULL, "v1","v2", NULL);                           
    matte_add_external_function(m, "raylib_Vector3Angle", raylib_Vector3Angle, NULL, "v1","v2", NULL);                                 
    matte_add_external_function(m, "raylib_Vector3Negate", raylib_Vector3Negate, NULL, "v", NULL);                                           
    matte_add_external_function(m, "raylib_Vector3Divide", raylib_Vector3Divide, NULL, "v1","v2", NULL);                              
    matte_add_external_function(m, "raylib_Vector3Normalize", raylib_Vector3Normalize, NULL, "v", NULL);                                        
    matte_add_external_function(m, "raylib_Vector3OrthoNormalize", raylib_Vector3OrthoNormalize, NULL, "v1","v2", NULL);                       
    matte_add_external_function(m, "raylib_Vector3Transform", raylib_Vector3Transform, NULL, "v","mat", NULL);                            
    matte_add_external_function(m, "raylib_Vector3RotateByQuaternion", raylib_Vector3RotateByQuaternion, NULL, "v","q", NULL);                 
    matte_add_external_function(m, "raylib_Vector3RotateByAxisAngle", raylib_Vector3RotateByAxisAngle, NULL, "v","axis", "angle",NULL);     
    matte_add_external_function(m, "raylib_Vector3Lerp", raylib_Vector3Lerp, NULL, "v1","v2", "amount",NULL);                  
    matte_add_external_function(m, "raylib_Vector3Reflect", raylib_Vector3Reflect, NULL, "v","normal", NULL);                          
    matte_add_external_function(m, "raylib_Vector3Min", raylib_Vector3Min, NULL, "v1","v2", NULL);                                 
    matte_add_external_function(m, "raylib_Vector3Max", raylib_Vector3Max, NULL, "v1","v2", NULL);                                 
    matte_add_external_function(m, "raylib_Vector3Barycenter", raylib_Vector3Barycenter, NULL, "p","a", "b","c",NULL);      
    matte_add_external_function(m, "raylib_Vector3Unproject", raylib_Vector3Unproject, NULL, "source","projection", "view",NULL);   
    matte_add_external_function(m, "raylib_Vector3Invert", raylib_Vector3Invert, NULL, "v", NULL);                                           
    matte_add_external_function(m, "raylib_Vector3Clamp", raylib_Vector3Clamp, NULL, "v","min", "max",NULL);                  
    matte_add_external_function(m, "raylib_Vector3ClampValue", raylib_Vector3ClampValue, NULL, "v","min", "max",NULL);                 
    matte_add_external_function(m, "raylib_Vector3Equals", raylib_Vector3Equals, NULL, "p","q", NULL);                                    
    matte_add_external_function(m, "raylib_Vector3Refract", raylib_Vector3Refract, NULL, "v","n", "r",NULL);                      


    matte_add_external_function(m, "raylib_MatrixDeterminant", raylib_MatrixDeterminant, NULL, "mat", NULL);                                        
    matte_add_external_function(m, "raylib_MatrixTrace", raylib_MatrixTrace, NULL, "mat", NULL);                                              
    matte_add_external_function(m, "raylib_MatrixTranspose", raylib_MatrixTranspose, NULL, "mat", NULL);                                         
    matte_add_external_function(m, "raylib_MatrixInvert", raylib_MatrixInvert, NULL, "mat", NULL);                                            
    matte_add_external_function(m, "raylib_MatrixIdentity", raylib_MatrixIdentity, NULL, NULL);                                                
    matte_add_external_function(m, "raylib_MatrixAdd", raylib_MatrixAdd, NULL, "left","right", NULL);                                
    matte_add_external_function(m, "raylib_MatrixSubtract", raylib_MatrixSubtract, NULL, "left","right", NULL);                           
    matte_add_external_function(m, "raylib_MatrixMultiply", raylib_MatrixMultiply, NULL, "left","right", NULL);                           
    matte_add_external_function(m, "raylib_MatrixTranslate", raylib_MatrixTranslate, NULL, "x","y", "z",NULL);                          
    matte_add_external_function(m, "raylib_MatrixRotate", raylib_MatrixRotate, NULL, "axis","angle", NULL);                             
    matte_add_external_function(m, "raylib_MatrixRotateX", raylib_MatrixRotateX, NULL, "angle", NULL);                                          
    matte_add_external_function(m, "raylib_MatrixRotateY", raylib_MatrixRotateY, NULL, "angle", NULL);                                          
    matte_add_external_function(m, "raylib_MatrixRotateZ", raylib_MatrixRotateZ, NULL, "angle", NULL);                                          
    matte_add_external_function(m, "raylib_MatrixRotateXYZ", raylib_MatrixRotateXYZ, NULL, "angle", NULL);                                      
    matte_add_external_function(m, "raylib_MatrixRotateZYX", raylib_MatrixRotateZYX, NULL, "angle", NULL);                                      
    matte_add_external_function(m, "raylib_MatrixScale", raylib_MatrixScale, NULL, "x","y", "z",NULL);                              
    matte_add_external_function(m, "raylib_MatrixFrustum", raylib_MatrixFrustum, NULL, "left","right", "bottom","top", "near", "far",NULL); 
    matte_add_external_function(m, "raylib_MatrixPerspective", raylib_MatrixPerspective, NULL, "fovy","aspect", "near","far",NULL); 
    matte_add_external_function(m, "raylib_MatrixOrtho", raylib_MatrixOrtho, NULL, "left","right", "bottom","top", "near", "far",NULL); 
    matte_add_external_function(m, "raylib_MatrixLookAt", raylib_MatrixLookAt, NULL, "eye","target", "up",NULL);               


    matte_add_external_function(m, "raylib_QuaternionAdd", raylib_QuaternionAdd, NULL, "q1","q2", NULL);                     
    matte_add_external_function(m, "raylib_QuaternionAddValue", raylib_QuaternionAddValue, NULL, "q","add", NULL);                     
    matte_add_external_function(m, "raylib_QuaternionSubtract", raylib_QuaternionSubtract, NULL, "q1","q2", NULL);                
    matte_add_external_function(m, "raylib_QuaternionSubtractValue", raylib_QuaternionSubtractValue, NULL, "q","sub", NULL);                
    matte_add_external_function(m, "raylib_QuaternionIdentity", raylib_QuaternionIdentity, NULL, NULL);                                        
    matte_add_external_function(m, "raylib_QuaternionLength", raylib_QuaternionLength, NULL, "q", NULL);                                       
    matte_add_external_function(m, "raylib_QuaternionNormalize", raylib_QuaternionNormalize, NULL, "q", NULL);                               
    matte_add_external_function(m, "raylib_QuaternionInvert", raylib_QuaternionInvert, NULL, "q", NULL);                                  
    matte_add_external_function(m, "raylib_QuaternionMultiply", raylib_QuaternionMultiply, NULL, "q1","q2", NULL);                
    matte_add_external_function(m, "raylib_QuaternionScale", raylib_QuaternionScale, NULL, "q","mul", NULL);                        
    matte_add_external_function(m, "raylib_QuaternionDivide", raylib_QuaternionDivide, NULL, "q1","q2", NULL);                  
    matte_add_external_function(m, "raylib_QuaternionLerp", raylib_QuaternionLerp, NULL, "q1","q2", "amount",NULL);      
    matte_add_external_function(m, "raylib_QuaternionNlerp", raylib_QuaternionNlerp, NULL, "q1","q2", "amount",NULL);     
    matte_add_external_function(m, "raylib_QuaternionSlerp", raylib_QuaternionSlerp, NULL, "q1","q2", "amount",NULL);     
    matte_add_external_function(m, "raylib_QuaternionFromVector3ToVector3", raylib_QuaternionFromVector3ToVector3, NULL, "from","to", NULL);        
    matte_add_external_function(m, "raylib_QuaternionFromMatrix", raylib_QuaternionFromMatrix, NULL, "mat", NULL);                                
    matte_add_external_function(m, "raylib_QuaternionToMatrix", raylib_QuaternionToMatrix, NULL, "q", NULL);                                    
    matte_add_external_function(m, "raylib_QuaternionFromAxisAngle", raylib_QuaternionFromAxisAngle, NULL, "axis","angle", NULL);              
    matte_add_external_function(m, "raylib_QuaternionToAxisAngle", raylib_QuaternionToAxisAngle, NULL, "q",NULL); 
    matte_add_external_function(m, "raylib_QuaternionFromEuler", raylib_QuaternionFromEuler, NULL, "pitch","yaw", "roll",NULL);         
    matte_add_external_function(m, "raylib_QuaternionToEuler", raylib_QuaternionToEuler, NULL, "q", NULL);                                    
    matte_add_external_function(m, "raylib_QuaternionTransform", raylib_QuaternionTransform, NULL, "q","mat", NULL);                   
    matte_add_external_function(m, "raylib_QuaternionEquals", raylib_QuaternionEquals, NULL, "p","q", NULL);                               


} 


static void raymatte_load_main(matte_t * m) {
    unsigned int bytesRead;
    char * data = LoadFileText("main.mt");
    
    matte_run_source(m, data);
    
    UnloadFileText(data);
}



int main(int argc, char ** argv) {
    if (strcmp(argv[0], "--help") == 0 ||
        strcmp(argv[0], "-h") == 0 ||
        strcmp(argv[0], "-v") == 0) {
        printf("raymatte v%s\n\n", RAYMATTE__VERSION);
        printf("Johnathan Corkery\n");
        printf("raylib https://github.com/raysan5/raylib\n");
        printf("matte  https://github.com/jcorks/matte\n");
        return 0;
    } 


    int isDebug = FALSE;
    if (strcmp(argv[0], "--debug") == 0 ||
        strcmp(argv[0], "debug") == 0 ||
        strcmp(argv[0], "-g") == 0) {
        isDebug = TRUE;
    } 





    matte_t * m = matte_create();
    matte_set_io(m, NULL, NULL, NULL);
    matte_set_importer(m, NULL, NULL);
    if (isDebug)
        matte_debugging_enable(m);


    raymatte_init_bindings(m);
    
    raymatte_load_main(m);
    return 0;
}
