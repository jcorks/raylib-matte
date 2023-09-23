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
#define RAYLIB_FN__ARG7(__T__, __T0__, __T1__, __T2__, __T3__, __T4__, __T5__, __T6__, __T7__) matteValue_t __T__(matteVM_t * vm, matteValue_t fn, const matteValue_t * args, void * userData) { matteStore_t * store = matte_vm_get_store(vm); if (!ensure_arg_types8(vm, args, __T0__, __T1__, __T2__, __T3__, __T4__, __T5__, __T6__, __T7__)) return matte_store_new_value(store);
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





RAYLIB_FN__ARG1(raylib_FontGetBaseSize, MATTE_VALUE_TYPE_OBJECT) 
    return native_to_value_int(vm, native_from_value_font(vm, args[0]).baseSize);  
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_FontGetGlyphCount, MATTE_VALUE_TYPE_OBJECT) 
    return native_to_value_int(vm, native_from_value_font(vm, args[0]).glyphCount);  
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_FontGetGlyphPadding, MATTE_VALUE_TYPE_OBJECT) 
    return native_to_value_int(vm, native_from_value_font(vm, args[0]).glyphPadding);  
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_FontGetTexture, MATTE_VALUE_TYPE_OBJECT) 
    return native_to_value_texture(vm, native_from_value_font(vm, args[0]).texture);  
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_FontGetGlyphInfo, MATTE_VALUE_TYPE_OBJECT, MATTE_VALUE_TYPE_NUMBER) 
    int index = args[1].value.number;
    Font font = native_from_value_font(vm, args[0]);
    
    if (index < 0 || index > font.glyphCount) {
        matte_vm_raise_error_cstring(vm, "FontGetGlyphInfo: invalid glyph index");
        goto L_END;
    }
    
    return native_to_value_glyphInfo(vm, font.glyphs[index]);  
  L_END:
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_FontGetRectangle, MATTE_VALUE_TYPE_OBJECT, MATTE_VALUE_TYPE_NUMBER) 
    int index = args[1].value.number;
    Font font = native_from_value_font(vm, args[0]);
    
    if (index < 0 || index > font.glyphCount) {
        matte_vm_raise_error_cstring(vm, "FontGetRectangle: invalid glyph index");
        goto L_END;
    }
    
    return native_to_value_rectangle(vm, font.recs[index]);  
  L_END:
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
RAYLIB_FN__END



RAYLIB_FN__ARG2(raylib_ImageToPOT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)

    ImageToPOT(
        native_from_value_image_ref(vm, args[0]),
        native_from_value_color(vm, args[1])
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_ImageCrop,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)

    ImageCrop(
        native_from_value_image_ref(vm, args[0]),
        native_from_value_rectangle(vm, args[1])
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_ImageAlphaCrop,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)

    ImageAlphaCrop(
        native_from_value_image_ref(vm, args[0]),
        args[1].value.number
    );
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
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_ImageAlphaMask,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)

    ImageAlphaMask(
        native_from_value_image_ref(vm, args[0]),
        native_from_value_image(vm, args[1])
    );
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_ImageAlphaPremultiply,
    MATTE_VALUE_TYPE_OBJECT
)

    ImageAlphaPremultiply(
        native_from_value_image_ref(vm, args[0])
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_ImageBlurGaussian,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)

    ImageBlurGaussian(
        native_from_value_image_ref(vm, args[0]),
        args[1].value.number
    );
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
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_ImageMipmaps,
    MATTE_VALUE_TYPE_OBJECT
)

    ImageMipmaps(
        native_from_value_image_ref(vm, args[0])
    );
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
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_ImageRotateCW,
    MATTE_VALUE_TYPE_OBJECT
)

    ImageRotateCW(
        native_from_value_image_ref(vm, args[0])
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_ImageRotateCCW,
    MATTE_VALUE_TYPE_OBJECT
)

    ImageRotateCCW(
        native_from_value_image_ref(vm, args[0])
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_ImageColorTint,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)

    ImageColorTint(
        native_from_value_image_ref(vm, args[0]),
        native_from_value_color(vm, args[1])
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_ImageColorInvert,
    MATTE_VALUE_TYPE_OBJECT
)

    ImageColorInvert(
        native_from_value_image_ref(vm, args[0])
    );
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_ImageColorGrayscale,
    MATTE_VALUE_TYPE_OBJECT
)

    ImageColorGrayscale(
        native_from_value_image_ref(vm, args[0])
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_ImageColorContrast,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)

    ImageColorContrast(
        native_from_value_image_ref(vm, args[0]),
        args[1].value.number
    );
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_ImageColorBrightness,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
)

    ImageColorBrightness(
        native_from_value_image_ref(vm, args[0]),
        args[1].value.number
    );
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
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_ImageDrawPixelV,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    ImageDrawPixelV(
        native_from_value_image_ref(vm, args[0]),
        native_from_value_vector2(vm, args[1])
        native_from_value_color(vm, args[2])
    );    
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
RAYLIB_FN__END


RAYLIB_FN__ARG3(raylib_ImageDrawRectangleRec,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    ImageDrawRectangleV(
        native_from_value_image_ref(vm, args[0]),
        native_from_value_rectangle(vm, args[1]),
        native_from_value_color(vm, args[2])
    );    
RAYLIB_FN__END


RAYLIB_FN__ARG4(raylib_ImageDrawRectangleLines,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    ImageDrawRectangleV(
        native_from_value_image_ref(vm, args[0]),
        native_from_value_rectangle(vm, args[1]),
        args[2].value.number,
        native_from_value_color(vm, args[3])
    );    
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

    return native_to_value_texture(
        vm,
        LoadRenderTexture(
            args[0].value.number,
            args[1].value.number
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_IsTextureReady,
    MATTE_VALUE_TYPE_OBJECT
)

    return native_to_value_boolean(
        vm,
        IsTextureReady(
            native_from_value_image(vm, args[0])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_UnloadTexture,
    MATTE_VALUE_TYPE_OBJECT
)
    Image img = native_from_value_image(vm, args[0]);
    UnloadTexture(
        img
    );
    native_unload(img, args[0]);
RAYLIB_FN__END

RAYLIB_FN__ARG2(raylib_IsRenderTextureReady,
    MATTE_VALUE_TYPE_OBJECT
)

    return native_to_value_boolean(
        vm,
        IsRenderTextureReady(
            native_from_value_image(vm, args[0])
        )
    );
RAYLIB_FN__END


RAYLIB_FN__ARG2(raylib_UnloadRenderTexture,
    MATTE_VALUE_TYPE_OBJECT
)
    Image img = native_from_value_image(vm, args[0]);
    UnloadRenderTexture(
        img
    );
    native_unload(img, args[0]);
RAYLIB_FN__END



RAYLIB_FN__ARG2(raylib_UpdateTexture,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_OBJECT
)
    Texture tex = native_from_value_texture(vm, args[0]),
    Image img = native_from_value_image(vm args[1]),
    
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
    Image img = native_from_value_image(vm args[2]);
    
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
    MATTE_VALUE_TYPE_NUMBER,
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
            data       
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


RAYLIB_FN__ARG1(raylib_LoadFont
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
    int count = matte_value_object_get_number_key_count(store, args[2]);

    int * codepoints = MemAlloc(sizeof(int)*count);
    memset(codepoint, 0, sizeof(int)*count);
    int i;
    for(i = 0; i < count; ++i) {
        matteValue_t str = matte_value_as_string(store, matte_value_object_access_index(store, args[2], i));
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


RAYLIB_FN__ARG3(raylib_LoadFontEx
    MATTE_VALUE_TYPE_STRING,
    MATTE_VALUE_TYPE_NUMBER,
    MATTE_VALUE_TYPE_OBJECT
)
    int count = 0;
    int * codepoints = get_codepoints(
        vm,
        store,
        args[2],
        &glyphCount
    );
    
    if (count <= 0) {
        goto L_END;
    }


    Font out = native_to_value_font(
        vm,
        LoadFontEx(
            native_from_value_string_unsafe(vm, args[0]) // ok!
            args[1].value.number,
            codepoints,
            count
        )
    );
    
    MemFree(codepoints);
    return out;
  L_END:
RAYLIB_FN__END




RAYLIB_FN__ARG3(raylib_LoadFontFromImage
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



RAYLIB_FN__ARG4(raylib_LoadFontFromMemory
    MATTE_VALUE_TYPE_STRING,
    MATTE_VALUE_TYPE_OBJECT,
    MATTE_VALUE_TYPE_NUMBER
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
        &glyphCount
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


RAYLIB_FN__ARG1(raylib_IsFontReady
    MATTE_VALUE_TYPE_OBJECT
)
    return native_to_value_boolean(
        vm,
        IsFontReady(
            native_from_value_font(vm, args[0])
        )
    );
RAYLIB_FN__END

RAYLIB_FN__ARG4(raylib_LoadFontData
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
        &glyphCount
    );

    GlyphInfo * gs = LoadFontData(
        data,
        size,
        args[1].value.number,
        codepoints,
        count,
        args[3].value.number
    );


    matteValue_t * args = MemAlloc(sizeof(matteValue_t)*count);
    int i;
    for(i = 0; i < count; ++i) {
        args[i] = native_to_value_glyphInfo(vm, gs[i]);
    }
    
    matteValue_t v = matte_store_new_value(store);
    matteArray_t arr = MATTE_ARRAY_CAST(args, matteValue_t, count);
    matte_value_into_new_object_array_ref(store, &v, &arr);
    MemFree(args);    

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
    GlyphInfo * glyphs = MemAlloc(sizeof(GlyphInfo), count);
    
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


    matteValue_t * args = MemAlloc(sizeof(matteValue_t) * count);    
    for(i = 0; i < count; ++i) {
        args[i] = native_to_value_rectangle(store, recs[i]);
    }
    matteValue_t arrV = matte_store_new_value(store);
    matteArray_t arr = MATTE_ARRAY_CAST(args, matteValue_t, count);
    matte_value_into_new_object_array_ref(store, &arrV, &arr);

    MemFree(args);
    matte_value_object_set_key_string(store, v, MATTE_VM_STR_CAST(vm, "recs"), arrV);
    

    MemFree(recs);    
    

    return v;
RAYLIB_FN__END



RAYLIB_FN__ARG1(raylib_UnloadFont
    MATTE_VALUE_TYPE_OBJECT
)
    UnloadFont(
        native_from_value_font(vm, args[0])
    );
    native_unload(vm, args[0]);
RAYLIB_FN__END



RAYLIB_FN__ARG2(raylib_ExportFontAsCode
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


    matte_add_external_function(m, "raylib_FontGetGlyphCount", raylib_FontGetGlyphCount, NULL, "font", NULL);
    matte_add_external_function(m, "raylib_FontGetGlyphPadding", raylib_FontGetGlyphPadding, NULL, "font", NULL);
    matte_add_external_function(m, "raylib_FontGetBaseSize", raylib_FontGetBaseSize, NULL, "font", NULL);
    matte_add_external_function(m, "raylib_FontGetGlyphInfo", raylib_FontGetGlyphInfo, NULL, "font", "index", NULL);
    matte_add_external_function(m, "raylib_FontGetTexture", raylib_FontGetTexture, NULL, "font", NULL);
    matte_add_external_function(m, "raylib_FontGetRectangle", raylib_FontGetGlyphCount, NULL, "font", "index", NULL);





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
    matte_add_external_function(m, "raylib_UnloadFontData", raylib_UnloadFontData, NULL, "chars", "glyphCount",  NULL);                                
    matte_add_external_function(m, "raylib_UnloadFont", raylib_UnloadFont, NULL, "font", NULL);                                                           
    matte_add_external_function(m, "raylib_ExportFontAsCode", raylib_ExportFontAsCode, NULL, "font", "fileName", NULL);                               


    matte_add_external_function(m, "raylib_DrawFPS", raylib_DrawFPS, NULL, "posX", "posY",  NULL);                                                     
    matte_add_external_function(m, "raylib_DrawText", raylib_DrawText, NULL, "text", "posX", "posY", "fontSize", "color", NULL);       
    matte_add_external_function(m, "raylib_DrawTextEx", raylib_DrawTextEx, NULL, "font", "text", "position", "fontSize", "spacing", "tint", NULL); 
    matte_add_external_function(m, "raylib_DrawTextPro", raylib_DrawTextPro, NULL, "font", "text", "position", "origin", "rotation", "fontSize", "spacing", "tint", NULL); 
    matte_add_external_function(m, "raylib_DrawTextCodepoint", raylib_DrawTextCodepoint, NULL, "font", "codepoint",  "position", "fontSize", "tint",  NULL); 
    matte_add_external_function(m, "raylib_DrawTextCodepoints", raylib_DrawTextCodepoints, NULL, "font", "codepoints", "count", "position", "fontSize", "spacing", "tint", NULL); 


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
    matte_add_external_function(m, "raylib_UpdateMeshBuffer", raylib_UpdateMeshBuffer, NULL, "mesh", "index", "data", "dataSize", "offset", NULL); 
    matte_add_external_function(m, "raylib_UnloadMesh", raylib_UnloadMesh, NULL, "mesh", NULL);                                                           
    matte_add_external_function(m, "raylib_DrawMesh", raylib_DrawMesh, NULL, "mesh", "material",  "transform", NULL);                        
    matte_add_external_function(m, "raylib_DrawMeshInstanced", raylib_DrawMeshInstanced, NULL, "mesh", "material", "transforms", "instances", NULL); 
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
    matte_add_external_function(m, "raylib_UnloadModelAnimations", raylib_UnloadModelAnimations, NULL, "animations", "count", NULL);           
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
    matte_add_external_function(m, "raylib_LoadWaveFromMemory", raylib_LoadWaveFromMemory, NULL, "fileType", "fileData", "dataSize", NULL); 
    matte_add_external_function(m, "raylib_IsWaveReady", raylib_IsWaveReady, NULL, "wave", NULL);                                    
    matte_add_external_function(m, "raylib_LoadSound", raylib_LoadSound, NULL, "fileName",  NULL);                          
    matte_add_external_function(m, "raylib_LoadSoundFromWave", raylib_LoadSoundFromWave, NULL, "wave", NULL);                             
    matte_add_external_function(m, "raylib_IsSoundReady", raylib_IsSoundReady, NULL, "sound", NULL);                                 
    matte_add_external_function(m, "raylib_UpdateSound", raylib_UpdateSound, "sound", "data", "sampleCount", NULL); 
    matte_add_external_function(m, "raylib_UnloadWave", raylib_UnloadWave, NULL, "wave", NULL);                                     
    matte_add_external_function(m, "raylib_UnloadSound", raylib_UnloadSound, NULL, "sound", NULL);                                  
    matte_add_external_function(m, "raylib_ExportWave", raylib_ExportWave, NULL, "wave", "fileName);               
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
    matte_add_external_function(m, "raylib_UnloadWaveSamples", raylib_UnloadWaveSamples, NULL, "samples",  NULL);                         


    matte_add_external_function(m, "raylib_LoadMusicStream", raylib_LoadMusicStream, NULL, "fileName",  NULL);                    
    matte_add_external_function(m, "raylib_LoadMusicStreamFromMemory", raylib_LoadMusicStreamFromMemory, NULL, "fileType", "data", "dataSize", NULL); 
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
    matte_add_external_function(m, "raylib_UpdateAudioStream", raylib_UpdateAudioStream, NULL, "stream", "data", "frameCount", NULL); 
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
    matte_add_external_function(m, "raylib_SetAudioStreamCallback", raylib_SetAudioStreamCallback, NULL, "stream", "callback",  NULL);  

    matte_add_external_function(m, "raylib_AttachAudioStreamProcessor", raylib_AttachAudioStreamProcessor, NULL, "stream", "processor",  NULL); 
    matte_add_external_function(m, "raylib_DetachAudioStreamProcessor", raylib_DetachAudioStreamProcessor, NULL, "stream", "processor",  NULL); 

    matte_add_external_function(m, "raylib_AttachAudioMixedProcessor", raylib_AttachAudioMixedProcessor, NULL, "processor", NULL); 
    matte_add_external_function(m, "raylib_DetachAudioMixedProcessor", raylib_DetachAudioMixedProcessor, NULL, "processor", NULL); 


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
    matte_add_external_function(m, "raylib_Vector3ToFloatV", raylib_Vector3ToFloatV, NULL, "v", NULL);                                          
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
    matte_add_external_function(m, "raylib_MatrixToFloatV", raylib_MatrixToFloatV, NULL, "mat", NULL);                                         


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
    matte_add_external_function(m, "raylib_QuaternionToAxisAngle", raylib_QuaternionToAxisAngle, NULL, "q","outAxis", "outAngle",NULL); 
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
