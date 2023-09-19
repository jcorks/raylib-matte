#include <string.h>
#include "../matte/src/matte.h"
#include "../matte/src/matte_string.h"
#include "../matte/src/matte_store.h"
#include "../matte/src/matte_array.h"
#include "defines.h"
#include "native.h"
#include <stdio.h>



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


RAYLIB_FN__ARG1(raylib_ImageGetWidth, MATTE_VALUE_TYPE_OBJECT) 
    Image img = native_decode_image(vm, args[0]);  
    matteValue_t out = matte_store_new_value(store);
    matte_value_into_number(store, &out, img.width);
    return out;
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_ImageGetHeight, MATTE_VALUE_TYPE_OBJECT) 
    Image img = native_decode_image(vm, args[0]);  
    matteValue_t out = matte_store_new_value(store);
    matte_value_into_number(store, &out, img.height);
    return out;    
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_ImageGetMipmaps, MATTE_VALUE_TYPE_OBJECT) 
    Image img = native_decode_image(vm, args[0]);  
    matteValue_t out = matte_store_new_value(store);
    matte_value_into_number(store, &out, img.mipmaps);
    return out;    
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_ImageGetFormat, MATTE_VALUE_TYPE_OBJECT) 
    Image img = native_decode_image(vm, args[0]);  
    matteValue_t out = matte_store_new_value(store);
    matte_value_into_number(store, &out, img.format);
    return out;        
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
    int result = WindowShouldClose();
    matteValue_t out = matte_store_new_value(store);
    matte_value_into_boolean(store, &out, result);
    return out;
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_CloseWindow)
    CloseWindow();
RAYLIB_FN__END



RAYLIB_FN__ARG0(raylib_IsWindowReady)
    int result = IsWindowReady();
    matteValue_t out = matte_store_new_value(store);
    matte_value_into_boolean(store, &out, result);
    return out;
RAYLIB_FN__END


RAYLIB_FN__ARG0(raylib_IsWindowFullscreen)
    int result = IsWindowFullscreen();
    matteValue_t out = matte_store_new_value(store);
    matte_value_into_boolean(store, &out, result);
    return out;
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_IsWindowHidden)
    int result = IsWindowHidden();
    matteValue_t out = matte_store_new_value(store);
    matte_value_into_boolean(store, &out, result);
    return out;
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_IsWindowMinimized)
    int result = IsWindowMinimized();
    matteValue_t out = matte_store_new_value(store);
    matte_value_into_boolean(store, &out, result);
    return out;
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_IsWindowMaximized)
    int result = IsWindowMaximized();
    matteValue_t out = matte_store_new_value(store);
    matte_value_into_boolean(store, &out, result);
    return out;
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_IsWindowFocused)
    int result = IsWindowFocused();
    matteValue_t out = matte_store_new_value(store);
    matte_value_into_boolean(store, &out, result);
    return out;
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_IsWindowResized)
    int result = IsWindowResized();
    matteValue_t out = matte_store_new_value(store);
    matte_value_into_boolean(store, &out, result);
    return out;
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_IsWindowState, MATTE_VALUE_TYPE_NUMBER)
    int result = IsWindowState((unsigned int)args[0].value.number);
    matteValue_t out = matte_store_new_value(store);
    matte_value_into_boolean(store, &out, result);
    return out;
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
    Image m = native_decode_image(vm, args[0]);
    SetWindowIcon(m);
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_SetWindowIcons, MATTE_VALUE_TYPE_OBJECT)
    matteArray_t * arr = matte_array_create(sizeof(Image));
    
    uint32_t i;
    uint32_t len = matte_value_object_get_number_key_count(store, args[0]);
    for(i = 0; i < len; ++i) {
        Image img = native_decode_image(vm, matte_value_object_access_index(store, args[0], i));
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
    int result = GetScreenWidth();
    matteValue_t out = matte_store_new_value(store);
    matte_value_into_number(store, &out, result);
    return out;
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_GetScreenHeight) 
    int result = GetScreenHeight();
    matteValue_t out = matte_store_new_value(store);
    matte_value_into_number(store, &out, result);
    return out;
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_GetRenderWidth) 
    int result = GetRenderWidth();
    matteValue_t out = matte_store_new_value(store);
    matte_value_into_number(store, &out, result);
    return out;
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_GetRenderHeight) 
    int result = GetRenderHeight();
    matteValue_t out = matte_store_new_value(store);
    matte_value_into_number(store, &out, result);
    return out;
RAYLIB_FN__END


RAYLIB_FN__ARG0(raylib_GetMonitorCount) 
    int result = GetMonitorCount();
    matteValue_t out = matte_store_new_value(store);
    matte_value_into_number(store, &out, result);
    return out;
RAYLIB_FN__END


RAYLIB_FN__ARG0(raylib_GetCurrentMonitor)
    int result = GetCurrentMonitor();
    matteValue_t out = matte_store_new_value(store);
    matte_value_into_number(store, &out, result);
    return out;
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_GetMonitorPosition, MATTE_VALUE_TYPE_NUMBER)
    return native_encode_vector2(vm, GetMonitorPosition(args[0].value.number));
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_GetMonitorWidth, MATTE_VALUE_TYPE_NUMBER)
    int result = GetMonitorWidth(args[0].value.number);
    matteValue_t out = matte_store_new_value(store);
    matte_value_into_number(store, &out, result);
    return out;
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_GetMonitorHeight, MATTE_VALUE_TYPE_NUMBER)
    int result = GetMonitorHeight(args[0].value.number);
    matteValue_t out = matte_store_new_value(store);
    matte_value_into_number(store, &out, result);
    return out;
RAYLIB_FN__END


RAYLIB_FN__ARG1(raylib_GetMonitorPhysicalWidth, MATTE_VALUE_TYPE_NUMBER)
    int result = GetMonitorPhysicalWidth(args[0].value.number);
    matteValue_t out = matte_store_new_value(store);
    matte_value_into_number(store, &out, result);
    return out;
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_GetMonitorPhysicalHeight, MATTE_VALUE_TYPE_NUMBER) 
    int result = GetMonitorPhysicalHeight(args[0].value.number);
    matteValue_t out = matte_store_new_value(store);
    matte_value_into_number(store, &out, result);
    return out;
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_GetMonitorRefreshRate, MATTE_VALUE_TYPE_NUMBER) 
    int result = GetMonitorRefreshRate(args[0].value.number);
    matteValue_t out = matte_store_new_value(store);
    matte_value_into_number(store, &out, result);
    return out;
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_GetWindowPosition)
    return native_encode_vector2(vm, GetWindowPosition());
RAYLIB_FN__END

RAYLIB_FN__ARG0(raylib_GetWindowScaleDPI)
    return native_encode_vector2(vm, GetWindowScaleDPI());
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_GetMonitorName, MATTE_VALUE_TYPE_NUMBER)
    const char * str = GetMonitorName(args[0].value.number);
    matteString_t * mstr = matte_string_create_from_c_str("%s", str);
    matteValue_t out = matte_store_new_value(store);
    matte_value_into_string(store, &out, mstr);
    matte_string_destroy(mstr);
    return out;;
RAYLIB_FN__END

RAYLIB_FN__ARG1(raylib_SetClipboardText, MATTE_VALUE_TYPE_STRING)
    SetClipboardText(matte_string_get_c_str(matte_value_string_get_string_unsafe(store, args[0])));
RAYLIB_FN__END


RAYLIB_FN__ARG0(raylib_GetClipboardText)
    const char * str = GetClipboardText();
    matteString_t * mstr = matte_string_create_from_c_str("%s", str);
    matteValue_t out = matte_store_new_value(store);
    matte_value_into_string(store, &out, mstr);
    matte_string_destroy(mstr);
    return out;;
RAYLIB_FN__END


RAYLIB_FN__ARG0(raylib_EnableEventWaiting)
    EnableEventWaiting();
RAYLIB_FN__END


RAYLIB_FN__ARG0(raylib_DisableEventWaiting)
    DisableEventWaiting();
RAYLIB_FN__END

static void raymatte_init_bindings(matte_t * m) {
    // struct interfacing
    matte_add_external_function(m, "raylib_ImageGetWidth", raylib_ImageGetWidth, NULL, "image", NULL);
    matte_add_external_function(m, "raylib_ImageGetHeight", raylib_ImageGetHeight, NULL, "image", NULL);
    matte_add_external_function(m, "raylib_ImageGetMipmaps", raylib_ImageGetMipmaps, NULL, "image", NULL);
    matte_add_external_function(m, "raylib_ImageGetFormat", raylib_ImageGetFormat, NULL, "image", NULL);


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
