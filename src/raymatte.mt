// GetWindowHandle is NOT supported.


@:raylib = {
    // Struct Accessors 
    ImageGetWidth  : getExternalFunction(name:"raylib_ImageGetWidth"),
    ImageGetHeight : getExternalFunction(name:"raylib_ImageGetHeight"),
    ImageGetMipmaps: getExternalFunction(name:"raylib_ImageGetMipmaps"),
    ImageGetFormat : getExternalFunction(name:"raylib_ImageGetFormat"),









    // rcore: Windowing
    InitWindow : getExternalFunction(name:"raylib_InitWindow"),
    WindowShouldClose : getExternalFunction(name:"raylib_WindowShouldClose"),
    CloseWindow : getExternalFunction(name:"raylib_CloseWindow"), 
    IsWindowReady : getExternalFunction(name:"raylib_IsWindowReady"),
    IsWindowFullscreen : getExternalFunction(name:"raylib_IsWindowFullscreen"),
    IsWindowHidden : getExternalFunction(name:"raylib_IsWindowHidden"),  
    IsWindowMinimized : getExternalFunction(name:"raylib_IsWindowMinimized"), 
    IsWindowMaximized : getExternalFunction(name:"raylib_IsWindowMaximized"),
    IsWindowFocused : getExternalFunction(name:"raylib_IsWindowFocused"),
    IsWindowResized : getExternalFunction(name:"raylib_IsWindowResized"),
    IsWindowState : getExternalFunction(name:"raylib_IsWindowState"),
    SetWindowState : getExternalFunction(name:"raylib_SetWindowState"),
    ClearWindowState : getExternalFunction(name:"raylib_ClearWindowState"),  
    ToggleFullscreen : getExternalFunction(name:"raylib_ToggleFullscreen"),
    MaximizeWindow : getExternalFunction(name:"raylib_MaximizeWindow"),
    MinimizeWindow : getExternalFunction(name:"raylib_MinimizeWindow"),
    RestoreWindow : getExternalFunction(name:"raylib_RestoreWindow"),
    SetWindowIcon : getExternalFunction(name:"raylib_SetWindowIcon"),
    SetWindowIcons : getExternalFunction(name:"raylib_SetWindowIcons"),
    SetWindowTitle : getExternalFunction(name:"raylib_SetWindowTitle"),
    SetWindowPosition : getExternalFunction(name:"raylib_SetWindowPosition"),
    SetWindowMonitor : getExternalFunction(name:"raylib_SetWindowMonitor"),
    SetWindowMinSize : getExternalFunction(name:"raylib_SetWindowMinSize"),
    SetWindowSize : getExternalFunction(name:"raylib_SetWindowSize"),
    SetWindowOpacity : getExternalFunction(name:"raylib_SetWindowOpacity"),
    GetScreenWidth : getExternalFunction(name:"raylib_GetScreenWidth"),
    GetScreenHeight : getExternalFunction(name:"raylib_GetScreenHeight"),
    GetRenderWidth : getExternalFunction(name:"raylib_GetRenderWidth"),
    GetRenderHeight : getExternalFunction(name:"raylib_GetRenderHeight"),
    GetMonitorCount : getExternalFunction(name:"raylib_GetMonitorCount"),
    GetCurrentMonitor : getExternalFunction(name:"raylib_GetCurrentMonitor"),
    GetMonitorPosition : getExternalFunction(name:"raylib_GetMonitorPosition"),
    GetMonitorWidth : getExternalFunction(name:"raylib_GetMonitorWidth"),
    GetMonitorHeight : getExternalFunction(name:"raylib_GetMonitorHeight"),
    GetMonitorPhysicalWidth : getExternalFunction(name:"raylib_GetMonitorPhysicalWidth"),
    GetMonitorPhysicalHeight : getExternalFunction(name:"raylib_GetMonitorPhysicalHeight"),
    GetMonitorRefreshRate : getExternalFunction(name:"raylib_GetMonitorRefreshRate"),    
    GetWindowPosition : getExternalFunction(name:"raylib_GetWindowPosition"),
    GetWindowScaleDPI : getExternalFunction(name:"raylib_GetWindowScaleDPI"),
    GetMonitorName : getExternalFunction(name:"raylib_GetMonitorName"),
    SetClipboardText : getExternalFunction(name:"raylib_SetClipboardText"),
    GetClipboardText : getExternalFunction(name:"raylib_GetClipboardText"),
    EnableEventWaiting : getExternalFunction(name:"raylib_EnableEventWaiting"),
    DisableEventWaiting : getExternalFunction(name:"raylib_DisableEventWaiting")
};


raylib->setIsInterface(enabled:true);

return raylib;
