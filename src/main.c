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





////// Implementations


/* Struct interfacing for closed objects


*/
RAYLIB_FN__ARG1(raylib_IsObjectReadOnly, MATTE_VALUE_TYPE_OBJECT) 
    return native_to_value_boolean(vm, native_is_value_closed(vm, args[0]));  
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_ImageGetWidth, MATTE_VALUE_TYPE_OBJECT) 
    return native_to_value_int(vm, native_from_value_image(vm, args[0]).width);  
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_ImageGetHeight, MATTE_VALUE_TYPE_OBJECT) 
    return native_to_value_int(vm, native_from_value_image(vm, args[0]).height);  
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_ImageGetMipmaps, MATTE_VALUE_TYPE_OBJECT) 
    return native_to_value_int(vm, native_from_value_image(vm, args[0]).mipmaps);  
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_ImageGetFormat, MATTE_VALUE_TYPE_OBJECT) 
    return native_to_value_int(vm, native_from_value_image(vm, args[0]).format);  
RAYLIB_FN__END



RAYLIB_FN__ARG1(raylib_RenderTextureGetColorTexture, MATTE_VALUE_TYPE_OBJECT) 
    return native_to_value_texture(vm, native_from_value_renderTexture(vm, args[0]).texture);  
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_RenderTextureGetDepthTexture, MATTE_VALUE_TYPE_OBJECT) 
    return native_to_value_texture(vm, native_from_value_renderTexture(vm, args[0]).depth);  
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_TextureGetFormat, MATTE_VALUE_TYPE_OBJECT) 
    return native_to_value_int(vm, native_from_value_texture(vm, args[0]).format);  
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_TextureGetMipmaps, MATTE_VALUE_TYPE_OBJECT) 
    return native_to_value_int(vm, native_from_value_texture(vm, args[0]).mipmaps);  
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_TextureGetWidth, MATTE_VALUE_TYPE_OBJECT) 
    return native_to_value_int(vm, native_from_value_texture(vm, args[0]).width);  
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_TextureGetHeight, MATTE_VALUE_TYPE_OBJECT) 
    return native_to_value_int(vm, native_from_value_texture(vm, args[0]).height);  
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
    matteValue_t output = native_to_value_filePathList(vm, list);
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
    matteValue_t output = native_to_value_filePathList(vm, list);
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
    matteValue_t output = native_to_value_filePathList(vm, list);
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





static void raymatte_init_bindings(matte_t * m) {
    // struct interfacing

    matte_add_external_function(m, "raylib_IsObjectReadOnly", raylib_IsObjectReadOnly, NULL, "object", NULL);

    matte_add_external_function(m, "raylib_ImageGetWidth", raylib_ImageGetWidth, NULL, "image", NULL);
    matte_add_external_function(m, "raylib_ImageGetHeight", raylib_ImageGetHeight, NULL, "image", NULL);
    matte_add_external_function(m, "raylib_ImageGetMipmaps", raylib_ImageGetMipmaps, NULL, "image", NULL);
    matte_add_external_function(m, "raylib_ImageGetFormat", raylib_ImageGetFormat, NULL, "image", NULL);

    matte_add_external_function(m, "raylib_RenderTextureGetColorTexture", raylib_RenderTextureGetColorTexture, NULL, "renderTexture", NULL);
    matte_add_external_function(m, "raylib_RenderTextureGetDepthTexture", raylib_RenderTextureGetDepthTexture, NULL, "renderTexture", NULL);

    matte_add_external_function(m, "raylib_TextureGetFormat", raylib_TextureGetFormat, NULL, "texture", NULL);
    matte_add_external_function(m, "raylib_TextureGetHeight", raylib_TextureGetHeight, NULL, "texture", NULL);
    matte_add_external_function(m, "raylib_TextureGetMipmaps", raylib_TextureGetMipmaps, NULL, "texture", NULL);
    matte_add_external_function(m, "raylib_TextureGetWidth", raylib_TextureGetWidth, NULL, "texture", NULL);


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
