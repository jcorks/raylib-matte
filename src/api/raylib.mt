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

@:MemoryBuffer = import(module:'Matte.Core.MemoryBuffer');


@:base__ImageGetData = getExternalFunction(name:"raylib_ImageGetData");
@:base__MeshGetVertices = getExternalFunction(name:"raylib_MeshGetVertices");
@:base__MeshGetTexCoords = getExternalFunction(name:"raylib_MeshGetTexCoords");
@:base__MeshGetTexCoords2 = getExternalFunction(name:"raylib_MeshGetTexCoords2");
@:base__MeshGetNormals = getExternalFunction(name:"raylib_MeshGetNormals");
@:base__MeshGetTangents = getExternalFunction(name:"raylib_MeshGetTangents");
@:base__MeshGetColors = getExternalFunction(name:"raylib_MeshGetColors");
@:base__MeshGetIndices = getExternalFunction(name:"raylib_MeshGetIndices");
@:base__MeshGetAnimVertices = getExternalFunction(name:"raylib_MeshGetAnimVertices");
@:base__MeshGetAnimNormals = getExternalFunction(name:"raylib_MeshGetAnimNormals");
@:base__MeshGetBoneIDs = getExternalFunction(name:"raylib_MeshGetBoneIDs");
@:base__MeshGetBoneWeights = getExternalFunction(name:"raylib_MeshGetBoneWeights");
@:base__WaveGetData = getExternalFunction(name:"raylib_WaveGetData");
@:base__MatrixGetData = getExternalFunction(name:"raylib_MatrixGetData");


@:base__LoadFileData = getExternalFunction(name:"raylib_LoadFileData");
@:base__SaveFileData = getExternalFunction(name:"raylib_SaveFileData");
@:base__ExportDataAsCode = getExternalFunction(name:"raylib_ExportDataAsCode");
@:base__CompressData = getExternalFunction(name:"raylib_CompressData");
@:base__DecompressData = getExternalFunction(name:"raylib_DecompressData");
@:base__EncodeDataBase64 = getExternalFunction(name:"raylib_EncodeDataBase64");
@:base__DecodeDataBase64 = getExternalFunction(name:"raylib_DecodeDataBase64");
@:base__LoadImageFromMemory = getExternalFunction(name: "raylib_LoadImageFromMemory");
@:base__GetPixelColor = getExternalFunction(name:"raylib_GetPixelColor");
@:base__SetPixelColor = getExternalFunction(name:"raylib_SetPixelColor");
@:base__LoadFontFromMemory = getExternalFunction(name:"raylib_LoadFontFromMemory");
@:base__LoadFontData = getExternalFunction(name:"raylib_LoadFontData");
@:base__UpdateMeshBuffer = getExternalFunction(name:"raylib_UpdateMeshBuffer");
@:base__LoadWaveFromMemory = getExternalFunction(name:"raylib_LoadWaveFromMemory");
@:base__UpdateSound = getExternalFunction(name:"raylib_UpdateSound");
@:base__LoadWaveSamples = getExternalFunction(name:"raylib_LoadWaveSamples");
@:base__LoadMusicStreamFromMemory = getExternalFunction(name:"raylib_LoadMusicStreamFromMemory");
@:base__UpdateAudioStream = getExternalFunction(name:"raylib_UpdateAudioStream");




@:raylib = {
    // Defines
    LIGHTGRAY  : {r:200, g:200, b:200, a:255},   // Light Gray
    GRAY       : {r:130, g:130, b:130, a:255},  // Gray
    DARKGRAY   : {r:80,  g:80,  b:80,  a:255},      // Dark Gray
    YELLOW     : {r:253, g:249, b:0,   a:255},     // Yellow
    GOLD       : {r:255, g:203, b:0,   a:255},     // Gold
    ORANGE     : {r:255, g:161, b:0,   a:255},     // Orange
    PINK       : {r:255, g:109, b:194, a:255},   // Pink
    RED        : {r:230, g:41,  b:55,  a:255},     // Red
    MAROON     : {r:190, g:33,  b:55,  a:255},     // Maroon
    GREEN      : {r:0,   g:228, b:48,  a:255},      // Green
    LIME       : {r:0,   g:158, b:47,  a:255},      // Lime
    DARKGREEN  : {r:0,   g:117, b:44,  a:255},     // Dark Green
    SKYBLUE    : {r:102, g:191, b:255, a:255},   // Sky Blue
    BLUE       : {r:0,   g:121, b:241, a:255},     // Blue
    DARKBLUE   : {r:0,   g:82,  b:172, a:255},      // Dark Blue
    PURPLE     : {r:200, g:122, b:255, a:255},   // Purple
    VIOLET     : {r:135, g:60,  b:190, a:255},    // Violet
    DARKPURPLE : {r:112, g:31,  b:126, a:255},    // Dark Purple
    BEIGE      : {r:211, g:176, b:131, a:255},   // Beige
    BROWN      : {r:127, g:106, b:79,  a:255},    // Brown
    DARKBROWN  : {r:76,  g:63,  b:47,  a:255},      // Dark Brown

    WHITE      : {r:255, g:255, b:255, a:255},   // White
    BLACK      : {r:0,   g:0,   b:0,   a:255},         // Black
    BLANK      : {r:0,   g:0,   b:0,   a:0  },           // Blank (Transparent)
    MAGENTA    : {r:255, g:0,   b:255, a:255},     // Magenta
    RAYWHITE   : {r:245, g:245, b:245, a:255},   // My own White (raylib logo)



    // Enums
    //
    // Enums are flatly splayed out within the raylib namespace.
    //
    FLAG_VSYNC_HINT         : 0x00000040,   // Set to try enabling V-Sync on GPU
    FLAG_FULLSCREEN_MODE    : 0x00000002,   // Set to run program in fullscreen
    FLAG_WINDOW_RESIZABLE   : 0x00000004,   // Set to allow resizable window
    FLAG_WINDOW_UNDECORATED : 0x00000008,   // Set to disable window decoration (frame and buttons)
    FLAG_WINDOW_HIDDEN      : 0x00000080,   // Set to hide window
    FLAG_WINDOW_MINIMIZED   : 0x00000200,   // Set to minimize window (iconify)
    FLAG_WINDOW_MAXIMIZED   : 0x00000400,   // Set to maximize window (expanded to monitor)
    FLAG_WINDOW_UNFOCUSED   : 0x00000800,   // Set to window non focused
    FLAG_WINDOW_TOPMOST     : 0x00001000,   // Set to window always on top
    FLAG_WINDOW_ALWAYS_RUN  : 0x00000100,   // Set to allow windows running while minimized
    FLAG_WINDOW_TRANSPARENT : 0x00000010,   // Set to allow transparent framebuffer
    FLAG_WINDOW_HIGHDPI     : 0x00002000,   // Set to support HighDPI
    FLAG_WINDOW_MOUSE_PASSTHROUGH : 0x00004000, // Set to support mouse passthrough, only supported when FLAG_WINDOW_UNDECORATED
    FLAG_BORDERLESS_WINDOWED_MODE : 0x00008000, // Set to run program in borderless windowed mode
    FLAG_MSAA_4X_HINT       : 0x00000020,   // Set to try enabling MSAA 4X
    FLAG_INTERLACED_HINT    : 0x00010000,    // Set to try enabling interlaced video format (for V3D)

    LOG_ALL : 0,        // Display all logs
    LOG_TRACE : 1,          // Trace logging, intended for internal use only
    LOG_DEBUG : 2,          // Debug logging, used for internal debugging, it should be disabled on release builds
    LOG_INFO : 3,           // Info logging, used for program execution info
    LOG_WARNING : 4,        // Warning logging, used on recoverable failures
    LOG_ERROR : 5,          // Error logging, used on unrecoverable failures
    LOG_FATAL : 6,          // Fatal logging, used to abort program: exit(EXIT_FAILURE)
    LOG_NONE : 7,           // Disable logging

    KEY_NULL            : 0,        // Key: NULL, used for no key pressed
    // Alphanumeric keys
    KEY_APOSTROPHE      : 39,       // Key: '
    KEY_COMMA           : 44,       // Key: ,
    KEY_MINUS           : 45,       // Key: -
    KEY_PERIOD          : 46,       // Key: .
    KEY_SLASH           : 47,       // Key: /
    KEY_ZERO            : 48,       // Key: 0
    KEY_ONE             : 49,       // Key: 1
    KEY_TWO             : 50,       // Key: 2
    KEY_THREE           : 51,       // Key: 3
    KEY_FOUR            : 52,       // Key: 4
    KEY_FIVE            : 53,       // Key: 5
    KEY_SIX             : 54,       // Key: 6
    KEY_SEVEN           : 55,       // Key: 7
    KEY_EIGHT           : 56,       // Key: 8
    KEY_NINE            : 57,       // Key: 9
    KEY_SEMICOLON       : 59,       // Key: ;
    KEY_EQUAL           : 61,       // Key: =
    KEY_A               : 65,       // Key: A | a
    KEY_B               : 66,       // Key: B | b
    KEY_C               : 67,       // Key: C | c
    KEY_D               : 68,       // Key: D | d
    KEY_E               : 69,       // Key: E | e
    KEY_F               : 70,       // Key: F | f
    KEY_G               : 71,       // Key: G | g
    KEY_H               : 72,       // Key: H | h
    KEY_I               : 73,       // Key: I | i
    KEY_J               : 74,       // Key: J | j
    KEY_K               : 75,       // Key: K | k
    KEY_L               : 76,       // Key: L | l
    KEY_M               : 77,       // Key: M | m
    KEY_N               : 78,       // Key: N | n
    KEY_O               : 79,       // Key: O | o
    KEY_P               : 80,       // Key: P | p
    KEY_Q               : 81,       // Key: Q | q
    KEY_R               : 82,       // Key: R | r
    KEY_S               : 83,       // Key: S | s
    KEY_T               : 84,       // Key: T | t
    KEY_U               : 85,       // Key: U | u
    KEY_V               : 86,       // Key: V | v
    KEY_W               : 87,       // Key: W | w
    KEY_X               : 88,       // Key: X | x
    KEY_Y               : 89,       // Key: Y | y
    KEY_Z               : 90,       // Key: Z | z
    KEY_LEFT_BRACKET    : 91,       // Key: [
    KEY_BACKSLASH       : 92,       // Key: '\'
    KEY_RIGHT_BRACKET   : 93,       // Key: ]
    KEY_GRAVE           : 96,       // Key: `
    // Function keys
    KEY_SPACE           : 32,       // Key: Space
    KEY_ESCAPE          : 256,      // Key: Esc
    KEY_ENTER           : 257,      // Key: Enter
    KEY_TAB             : 258,      // Key: Tab
    KEY_BACKSPACE       : 259,      // Key: Backspace
    KEY_INSERT          : 260,      // Key: Ins
    KEY_DELETE          : 261,      // Key: Del
    KEY_RIGHT           : 262,      // Key: Cursor right
    KEY_LEFT            : 263,      // Key: Cursor left
    KEY_DOWN            : 264,      // Key: Cursor down
    KEY_UP              : 265,      // Key: Cursor up
    KEY_PAGE_UP         : 266,      // Key: Page up
    KEY_PAGE_DOWN       : 267,      // Key: Page down
    KEY_HOME            : 268,      // Key: Home
    KEY_END             : 269,      // Key: End
    KEY_CAPS_LOCK       : 280,      // Key: Caps lock
    KEY_SCROLL_LOCK     : 281,      // Key: Scroll down
    KEY_NUM_LOCK        : 282,      // Key: Num lock
    KEY_PRINT_SCREEN    : 283,      // Key: Print screen
    KEY_PAUSE           : 284,      // Key: Pause
    KEY_F1              : 290,      // Key: F1
    KEY_F2              : 291,      // Key: F2
    KEY_F3              : 292,      // Key: F3
    KEY_F4              : 293,      // Key: F4
    KEY_F5              : 294,      // Key: F5
    KEY_F6              : 295,      // Key: F6
    KEY_F7              : 296,      // Key: F7
    KEY_F8              : 297,      // Key: F8
    KEY_F9              : 298,      // Key: F9
    KEY_F10             : 299,      // Key: F10
    KEY_F11             : 300,      // Key: F11
    KEY_F12             : 301,      // Key: F12
    KEY_LEFT_SHIFT      : 340,      // Key: Shift left
    KEY_LEFT_CONTROL    : 341,      // Key: Control left
    KEY_LEFT_ALT        : 342,      // Key: Alt left
    KEY_LEFT_SUPER      : 343,      // Key: Super left
    KEY_RIGHT_SHIFT     : 344,      // Key: Shift right
    KEY_RIGHT_CONTROL   : 345,      // Key: Control right
    KEY_RIGHT_ALT       : 346,      // Key: Alt right
    KEY_RIGHT_SUPER     : 347,      // Key: Super right
    KEY_KB_MENU         : 348,      // Key: KB menu
    // Keypad keys
    KEY_KP_0            : 320,      // Key: Keypad 0
    KEY_KP_1            : 321,      // Key: Keypad 1
    KEY_KP_2            : 322,      // Key: Keypad 2
    KEY_KP_3            : 323,      // Key: Keypad 3
    KEY_KP_4            : 324,      // Key: Keypad 4
    KEY_KP_5            : 325,      // Key: Keypad 5
    KEY_KP_6            : 326,      // Key: Keypad 6
    KEY_KP_7            : 327,      // Key: Keypad 7
    KEY_KP_8            : 328,      // Key: Keypad 8
    KEY_KP_9            : 329,      // Key: Keypad 9
    KEY_KP_DECIMAL      : 330,      // Key: Keypad .
    KEY_KP_DIVIDE       : 331,      // Key: Keypad /
    KEY_KP_MULTIPLY     : 332,      // Key: Keypad *
    KEY_KP_SUBTRACT     : 333,      // Key: Keypad -
    KEY_KP_ADD          : 334,      // Key: Keypad +
    KEY_KP_ENTER        : 335,      // Key: Keypad Enter
    KEY_KP_EQUAL        : 336,      // Key: Keypad =
    // Android key buttons
    KEY_BACK            : 4,        // Key: Android back button
    KEY_MENU            : 82,       // Key: Android menu button
    KEY_VOLUME_UP       : 24,       // Key: Android volume up button
    KEY_VOLUME_DOWN     : 25,        // Key: Android volume down button

    MOUSE_BUTTON_LEFT    : 0,       // Mouse button left
    MOUSE_BUTTON_RIGHT   : 1,       // Mouse button right
    MOUSE_BUTTON_MIDDLE  : 2,       // Mouse button middle (pressed wheel)
    MOUSE_BUTTON_SIDE    : 3,       // Mouse button side (advanced mouse device)
    MOUSE_BUTTON_EXTRA   : 4,       // Mouse button extra (advanced mouse device)
    MOUSE_BUTTON_FORWARD : 5,       // Mouse button forward (advanced mouse device)
    MOUSE_BUTTON_BACK    : 6,       // Mouse button back (advanced mouse device)

    MOUSE_CURSOR_DEFAULT       : 0,     // Default pointer shape
    MOUSE_CURSOR_ARROW         : 1,     // Arrow shape
    MOUSE_CURSOR_IBEAM         : 2,     // Text writing cursor shape
    MOUSE_CURSOR_CROSSHAIR     : 3,     // Cross shape
    MOUSE_CURSOR_POINTING_HAND : 4,     // Pointing hand cursor
    MOUSE_CURSOR_RESIZE_EW     : 5,     // Horizontal resize/move arrow shape
    MOUSE_CURSOR_RESIZE_NS     : 6,     // Vertical resize/move arrow shape
    MOUSE_CURSOR_RESIZE_NWSE   : 7,     // Top-left to bottom-right diagonal resize/move arrow shape
    MOUSE_CURSOR_RESIZE_NESW   : 8,     // The top-right to bottom-left diagonal resize/move arrow shape
    MOUSE_CURSOR_RESIZE_ALL    : 9,     // The omnidirectional resize/move cursor shape
    MOUSE_CURSOR_NOT_ALLOWED   : 10,     // The operation-not-allowed shape

    GAMEPAD_BUTTON_UNKNOWN : 0,         // Unknown button, just for error checking
    GAMEPAD_BUTTON_LEFT_FACE_UP : 1,        // Gamepad left DPAD up button
    GAMEPAD_BUTTON_LEFT_FACE_RIGHT : 2,     // Gamepad left DPAD right button
    GAMEPAD_BUTTON_LEFT_FACE_DOWN : 3,      // Gamepad left DPAD down button
    GAMEPAD_BUTTON_LEFT_FACE_LEFT : 4,      // Gamepad left DPAD left button
    GAMEPAD_BUTTON_RIGHT_FACE_UP : 5,       // Gamepad right button up (i.e. PS3: Triangle, Xbox: Y)
    GAMEPAD_BUTTON_RIGHT_FACE_RIGHT : 6,    // Gamepad right button right (i.e. PS3: Square, Xbox: X)
    GAMEPAD_BUTTON_RIGHT_FACE_DOWN : 7,     // Gamepad right button down (i.e. PS3: Cross, Xbox: A)
    GAMEPAD_BUTTON_RIGHT_FACE_LEFT : 8,     // Gamepad right button left (i.e. PS3: Circle, Xbox: B)
    GAMEPAD_BUTTON_LEFT_TRIGGER_1 : 9,      // Gamepad top/back trigger left (first), it could be a trailing button
    GAMEPAD_BUTTON_LEFT_TRIGGER_2 : 10,      // Gamepad top/back trigger left (second), it could be a trailing button
    GAMEPAD_BUTTON_RIGHT_TRIGGER_1 : 11,     // Gamepad top/back trigger right (one), it could be a trailing button
    GAMEPAD_BUTTON_RIGHT_TRIGGER_2 : 12,     // Gamepad top/back trigger right (second), it could be a trailing button
    GAMEPAD_BUTTON_MIDDLE_LEFT : 13,         // Gamepad center buttons, left one (i.e. PS3: Select)
    GAMEPAD_BUTTON_MIDDLE : 14,              // Gamepad center buttons, middle one (i.e. PS3: PS, Xbox: XBOX)
    GAMEPAD_BUTTON_MIDDLE_RIGHT : 15,        // Gamepad center buttons, right one (i.e. PS3: Start)
    GAMEPAD_BUTTON_LEFT_THUMB : 16,          // Gamepad joystick pressed button left
    GAMEPAD_BUTTON_RIGHT_THUMB : 17,          // Gamepad joystick pressed button right

    GAMEPAD_AXIS_LEFT_X        : 0,     // Gamepad left stick X axis
    GAMEPAD_AXIS_LEFT_Y        : 1,     // Gamepad left stick Y axis
    GAMEPAD_AXIS_RIGHT_X       : 2,     // Gamepad right stick X axis
    GAMEPAD_AXIS_RIGHT_Y       : 3,     // Gamepad right stick Y axis
    GAMEPAD_AXIS_LEFT_TRIGGER  : 4,     // Gamepad back trigger left, pressure level: [1..-1]
    GAMEPAD_AXIS_RIGHT_TRIGGER : 5,     // Gamepad back trigger right, pressure level: [1..-1]


    MATERIAL_MAP_ALBEDO : 0,        // Albedo material (same as: MATERIAL_MAP_DIFFUSE)
    MATERIAL_MAP_METALNESS : 1,         // Metalness material (same as: MATERIAL_MAP_SPECULAR)
    MATERIAL_MAP_NORMAL : 2,            // Normal material
    MATERIAL_MAP_ROUGHNESS : 3,         // Roughness material
    MATERIAL_MAP_OCCLUSION : 4,         // Ambient occlusion material
    MATERIAL_MAP_EMISSION : 5,          // Emission material
    MATERIAL_MAP_HEIGHT : 6,            // Heightmap material
    MATERIAL_MAP_CUBEMAP : 7,           // Cubemap material (NOTE: Uses GL_TEXTURE_CUBE_MAP)
    MATERIAL_MAP_IRRADIANCE : 8,        // Irradiance material (NOTE: Uses GL_TEXTURE_CUBE_MAP)
    MATERIAL_MAP_PREFILTER : 9,         // Prefilter material (NOTE: Uses GL_TEXTURE_CUBE_MAP)
    MATERIAL_MAP_BRDF  : 10,              // Brdf material

    MESH_BUFFER_ID_POSITIONS : 0,
    MESH_BUFFER_ID_TEXCOORDS : 1,
    MESH_BUFFER_ID_NORMALS   : 2,
    MESH_BUFFER_ID_COLORS    : 3,
    MESH_BUFFER_ID_TANGENTS  : 4,
    MESH_BUFFER_ID_TEXCOORDS2: 5,
    MESH_BUFFER_ID_INDICES   : 6,

    SHADER_LOC_VERTEX_POSITION : 0, // Shader location: vertex attribute: position
    SHADER_LOC_VERTEX_TEXCOORD01 : 1,   // Shader location: vertex attribute: texcoord01
    SHADER_LOC_VERTEX_TEXCOORD02 : 2,   // Shader location: vertex attribute: texcoord02
    SHADER_LOC_VERTEX_NORMAL : 3,       // Shader location: vertex attribute: normal
    SHADER_LOC_VERTEX_TANGENT : 4,      // Shader location: vertex attribute: tangent
    SHADER_LOC_VERTEX_COLOR : 5,        // Shader location: vertex attribute: color
    SHADER_LOC_MATRIX_MVP : 6,          // Shader location: matrix uniform: model-view-projection
    SHADER_LOC_MATRIX_VIEW : 7,         // Shader location: matrix uniform: view (camera transform)
    SHADER_LOC_MATRIX_PROJECTION : 8,   // Shader location: matrix uniform: projection
    SHADER_LOC_MATRIX_MODEL : 9,        // Shader location: matrix uniform: model (transform)
    SHADER_LOC_MATRIX_NORMAL : 10,       // Shader location: matrix uniform: normal
    SHADER_LOC_VECTOR_VIEW : 11,         // Shader location: vector uniform: view
    SHADER_LOC_COLOR_DIFFUSE : 12,       // Shader location: vector uniform: diffuse color
    SHADER_LOC_COLOR_SPECULAR : 13,      // Shader location: vector uniform: specular color
    SHADER_LOC_COLOR_AMBIENT : 14,       // Shader location: vector uniform: ambient color
    SHADER_LOC_MAP_ALBEDO : 15,          // Shader location: sampler2d texture: albedo (same as: SHADER_LOC_MAP_DIFFUSE)
    SHADER_LOC_MAP_METALNESS : 16,       // Shader location: sampler2d texture: metalness (same as: SHADER_LOC_MAP_SPECULAR)
    SHADER_LOC_MAP_NORMAL : 17,          // Shader location: sampler2d texture: normal
    SHADER_LOC_MAP_ROUGHNESS : 18,       // Shader location: sampler2d texture: roughness
    SHADER_LOC_MAP_OCCLUSION : 19,       // Shader location: sampler2d texture: occlusion
    SHADER_LOC_MAP_EMISSION : 20,        // Shader location: sampler2d texture: emission
    SHADER_LOC_MAP_HEIGHT : 21,          // Shader location: sampler2d texture: height
    SHADER_LOC_MAP_CUBEMAP : 22,         // Shader location: samplerCube texture: cubemap
    SHADER_LOC_MAP_IRRADIANCE : 23,      // Shader location: samplerCube texture: irradiance
    SHADER_LOC_MAP_PREFILTER : 24,       // Shader location: samplerCube texture: prefilter
    SHADER_LOC_MAP_BRDF : 25,             // Shader location: sampler2d texture: brdf


    SHADER_UNIFORM_FLOAT : 0,       // Shader uniform type: float
    SHADER_UNIFORM_VEC2 : 1,            // Shader uniform type: vec2 (2 float)
    SHADER_UNIFORM_VEC3 : 2,            // Shader uniform type: vec3 (3 float)
    SHADER_UNIFORM_VEC4 : 3,            // Shader uniform type: vec4 (4 float)
    SHADER_UNIFORM_INT : 4,             // Shader uniform type: int
    SHADER_UNIFORM_IVEC2 : 5,           // Shader uniform type: ivec2 (2 int)
    SHADER_UNIFORM_IVEC3 : 6,           // Shader uniform type: ivec3 (3 int)
    SHADER_UNIFORM_IVEC4 : 7,           // Shader uniform type: ivec4 (4 int)
    SHADER_UNIFORM_SAMPLER2D : 8,        // Shader uniform type: sampler2d


    SHADER_ATTRIB_FLOAT : 0,        // Shader attribute type: float
    SHADER_ATTRIB_VEC2 : 1,             // Shader attribute type: vec2 (2 float)
    SHADER_ATTRIB_VEC3 : 2,             // Shader attribute type: vec3 (3 float)
    SHADER_ATTRIB_VEC4 : 3,              // Shader attribute type: vec4 (4 float)

    PIXELFORMAT_UNCOMPRESSED_GRAYSCALE : 1, // 8 bit per pixel (no alpha)
    PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA : 2,    // 8*2 bpp (2 channels)
    PIXELFORMAT_UNCOMPRESSED_R5G6B5 : 3,        // 16 bpp
    PIXELFORMAT_UNCOMPRESSED_R8G8B8 : 4,        // 24 bpp
    PIXELFORMAT_UNCOMPRESSED_R5G5B5A1 : 5,      // 16 bpp (1 bit alpha)
    PIXELFORMAT_UNCOMPRESSED_R4G4B4A4 : 6,      // 16 bpp (4 bit alpha)
    PIXELFORMAT_UNCOMPRESSED_R8G8B8A8 : 7,      // 32 bpp
    PIXELFORMAT_UNCOMPRESSED_R32 : 8,           // 32 bpp (1 channel - float)
    PIXELFORMAT_UNCOMPRESSED_R32G32B32 : 9,     // 32*3 bpp (3 channels - float)
    PIXELFORMAT_UNCOMPRESSED_R32G32B32A32 : 10,  // 32*4 bpp (4 channels - float)
    PIXELFORMAT_UNCOMPRESSED_R16 : 11,           // 16 bpp (1 channel - half float)
    PIXELFORMAT_UNCOMPRESSED_R16G16B16 : 12,     // 16*3 bpp (3 channels - half float)
    PIXELFORMAT_UNCOMPRESSED_R16G16B16A16 : 13,  // 16*4 bpp (4 channels - half float)
    PIXELFORMAT_COMPRESSED_DXT1_RGB : 14,        // 4 bpp (no alpha)
    PIXELFORMAT_COMPRESSED_DXT1_RGBA : 15,       // 4 bpp (1 bit alpha)
    PIXELFORMAT_COMPRESSED_DXT3_RGBA : 16,       // 8 bpp
    PIXELFORMAT_COMPRESSED_DXT5_RGBA : 17,       // 8 bpp
    PIXELFORMAT_COMPRESSED_ETC1_RGB : 18,        // 4 bpp
    PIXELFORMAT_COMPRESSED_ETC2_RGB : 19,        // 4 bpp
    PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA : 20,   // 8 bpp
    PIXELFORMAT_COMPRESSED_PVRT_RGB : 21,        // 4 bpp
    PIXELFORMAT_COMPRESSED_PVRT_RGBA : 22,       // 4 bpp
    PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA : 23,   // 8 bpp
    PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA : 24,    // 2 bpp

    TEXTURE_FILTER_POINT : 0,               // No filter, just pixel approximation
    TEXTURE_FILTER_BILINEAR : 1,                // Linear filtering
    TEXTURE_FILTER_TRILINEAR : 2,               // Trilinear filtering (linear with mipmaps)
    TEXTURE_FILTER_ANISOTROPIC_4X : 3,          // Anisotropic filtering 4x
    TEXTURE_FILTER_ANISOTROPIC_8X : 4,          // Anisotropic filtering 8x
    TEXTURE_FILTER_ANISOTROPIC_16X : 5,         // Anisotropic filtering 16x


    TEXTURE_WRAP_REPEAT : 0,                // Repeats texture in tiled mode
    TEXTURE_WRAP_CLAMP : 1,                     // Clamps texture to edge pixel in tiled mode
    TEXTURE_WRAP_MIRROR_REPEAT : 2,             // Mirrors and repeats the texture in tiled mode
    TEXTURE_WRAP_MIRROR_CLAMP : 3,               // Mirrors and clamps to border the texture in tiled mode


    CUBEMAP_LAYOUT_AUTO_DETECT : 0,         // Automatically detect layout type
    CUBEMAP_LAYOUT_LINE_VERTICAL : 1,           // Layout is defined by a vertical line with faces
    CUBEMAP_LAYOUT_LINE_HORIZONTAL : 2,         // Layout is defined by a horizontal line with faces
    CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR : 3,     // Layout is defined by a 3x4 cross with cubemap faces
    CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE : 4,     // Layout is defined by a 4x3 cross with cubemap faces
    CUBEMAP_LAYOUT_PANORAMA : 5,                 // Layout is defined by a panorama image (equirrectangular map)

    FONT_DEFAULT : 0,               // Default font generation, anti-aliased
    FONT_BITMAP : 1,                    // Bitmap font generation, no anti-aliasing
    FONT_SDF : 2,                        // SDF font generation, requires external shader

    BLEND_ALPHA : 0,                // Blend textures considering alpha (default)
    BLEND_ADDITIVE : 1,                 // Blend textures adding colors
    BLEND_MULTIPLIED : 2,               // Blend textures multiplying colors
    BLEND_ADD_COLORS : 3,               // Blend textures adding colors (alternative)
    BLEND_SUBTRACT_COLORS : 4,          // Blend textures subtracting colors (alternative)
    BLEND_ALPHA_PREMULTIPLY : 5,        // Blend premultiplied textures considering alpha
    BLEND_CUSTOM : 6,                   // Blend textures using custom src/dst factors (use rlSetBlendFactors())
    BLEND_CUSTOM_SEPARATE : 7,           // Blend textures using custom rgb/alpha separate src/dst factors (use rlSetBlendFactorsSeparate())

    GESTURE_NONE        : 0,        // No gesture
    GESTURE_TAP         : 1,        // Tap gesture
    GESTURE_DOUBLETAP   : 2,        // Double tap gesture
    GESTURE_HOLD        : 4,        // Hold gesture
    GESTURE_DRAG        : 8,        // Drag gesture
    GESTURE_SWIPE_RIGHT : 16,       // Swipe right gesture
    GESTURE_SWIPE_LEFT  : 32,       // Swipe left gesture
    GESTURE_SWIPE_UP    : 64,       // Swipe up gesture
    GESTURE_SWIPE_DOWN  : 128,      // Swipe down gesture
    GESTURE_PINCH_IN    : 256,      // Pinch in gesture
    GESTURE_PINCH_OUT   : 512,       // Pinch out gesture

    CAMERA_CUSTOM : 0,              // Custom camera
    CAMERA_FREE : 1,                    // Free camera
    CAMERA_ORBITAL : 2,                 // Orbital camera
    CAMERA_FIRST_PERSON : 3,            // First person camera
    CAMERA_THIRD_PERSON : 4,             // Third person camera

    
    CAMERA_PERSPECTIVE : 0,         // Perspective projection
    CAMERA_ORTHOGRAPHIC  : 1,            // Orthographic projection

    NPATCH_NINE_PATCH : 0,          // Npatch layout: 3x3 tiles
    NPATCH_THREE_PATCH_VERTICAL : 1,    // Npatch layout: 1x3 tiles
    NPATCH_THREE_PATCH_HORIZONTAL : 2,   // Npatch layout: 3x1 tiles







    // Read-only Struct Accessors 

        ImageGetData ::(image) {
            @:m = MemoryBuffer.new();
            m.bindNative(handle:base__ImageGetData(image));
            return m;
        },
        FontGetRecs : getExternalFunction(name:"raylib_FontGetRecs"),
        FontGetGlyphs : getExternalFunction(name:"raylib_FontGetGlyphs"),
        
        
        MeshGetVertices :: (mesh) {
            @:m = MemoryBuffer.new();
            m.bindNative(handle:base__MeshGetVertices(mesh));
            return m;
        },
        MeshGetTexCoords :: (mesh) {
            @:m = MemoryBuffer.new();
            m.bindNative(handle:base__MeshGetTexCoords(mesh));
            return m;
        },
        MeshGetTexCoords2 :: (mesh) {
            @:m = MemoryBuffer.new();
            m.bindNative(handle:base__MeshGetTexCoords2(mesh));
            return m;
        },
        MeshGetNormals :: (mesh) {
            @:m = MemoryBuffer.new();
            m.bindNative(handle:base__MeshGetNormals(mesh));
            return m;
        },
        MeshGetTangents :: (mesh) {
            @:m = MemoryBuffer.new();
            m.bindNative(handle:base__MeshGetTangents(mesh));
            return m;
        },
        MeshGetColors :: (mesh) {
            @:m = MemoryBuffer.new();
            m.bindNative(handle:base__MeshGetColors(mesh));
            return m;
        },
        MeshGetIndices :: (mesh) {
            @:m = MemoryBuffer.new();
            m.bindNative(handle:base__MeshGetIndices(mesh));
            return m;
        },
        MeshGetAnimVertices :: (mesh) {
            @:m = MemoryBuffer.new();
            m.bindNative(handle:base__MeshGetAnimVertices(mesh));
            return m;
        },
        MeshGetAnimNormals :: (mesh) {
            @:m = MemoryBuffer.new();
            m.bindNative(handle:base__MeshGetAnimNormals(mesh));
            return m;
        },
        MeshGetBoneIDs :: (mesh) {
            @:m = MemoryBuffer.new();
            m.bindNative(handle:base__MeshGetBoneIDs(mesh));
            return m;
        },
        MeshGetBoneWeights :: (mesh) {
            @:m = MemoryBuffer.new();
            m.bindNative(handle:base__MeshGetBoneWeights(mesh));
            return m;
        },


        MatrixGetData :: (matrix) {
            @:m = MemoryBuffer.new();
            m.bindNative(handle:base__MatrixGetData(matrix));
            return m;
        },
        
        
        
        
        MatrixGetFormatted ::(matrix) {
            @:m = raylib.MatrixGetData(matrix);
            @index = 0;
            @:gn :: {
                @:num = m.readFloat32(offset:index*4);
                index += 1;
                return num;
            }
            return [
                [gn(), gn(), gn(), gn()],
                [gn(), gn(), gn(), gn()],
                [gn(), gn(), gn(), gn()],
                [gn(), gn(), gn(), gn()]            
            ]
        },


        ModelGetMeshes : getExternalFunction(name:"raylib_ModelGetMeshes"),
        ModelGetMaterials : getExternalFunction(name:"raylib_ModelGetMaterials"),
        ModelGetMaterialNumbers : getExternalFunction(name:"raylib_ModelGetMaterialNumbers"),
        ModelGetBones : getExternalFunction(name:"raylib_ModelGetBones"),
        ModelGetBindPoses : getExternalFunction(name:"raylib_ModelGetBindPoses"),

        ModelAnimationGetBones : getExternalFunction(name:"raylib_ModelAnimationGetBones"),
        ModelAnimationGetFramePoses : getExternalFunction(name:"raylib_ModelAnimationGetFramePoses"),


        WaveGetData :: (wave) {
            @:m = MemoryBuffer.new();
            m.bindNative(handle:base__WaveGetData(wave));
            return m;
        },        
        
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
    ToggleBorderlessWindowed : getExternalFunction(name:"raylib_ToggleBorderlessWindowed"),
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
    DisableEventWaiting : getExternalFunction(name:"raylib_DisableEventWaiting"),

    // Custom frame control
    SwapScreenBuffer : getExternalFunction(name:"raylib_SwapScreenBuffer"),
    PollInputEvents : getExternalFunction(name:"raylib_PollInputEvents"),
    WaitTime : getExternalFunction(name:"raylib_WaitTime"),
    
    
    // cursor 
    ShowCursor : getExternalFunction(name:"raylib_ShowCursor"),
    HideCursor : getExternalFunction(name:"raylib_HideCursor"),
    IsCursorHidden : getExternalFunction(name:"raylib_IsCursorHidden"),
    EnableCursor : getExternalFunction(name:"raylib_EnableCursor"),
    DisableCursor : getExternalFunction(name:"raylib_DisableCursor"),
    IsCursorOnScreen : getExternalFunction(name:"raylib_IsCursorOnScreen"),
    
    
    // Drawing related functions 
    ClearBackground : getExternalFunction(name:"raylib_ClearBackground"),
    BeginDrawing : getExternalFunction(name:"raylib_BeginDrawing"),
    EndDrawing : getExternalFunction(name:"raylib_EndDrawing"),
    BeginMode2D : getExternalFunction(name:"raylib_BeginMode2D"),
    EndMode2D : getExternalFunction(name:"raylib_EndMode2D"),
    BeginMode3D : getExternalFunction(name:"raylib_BeginMode3D"),
    EndMode3D : getExternalFunction(name:"raylib_EndMode3D"),
    BeginTextureMode : getExternalFunction(name:"raylib_BeginTextureMode"),
    EndTextureMode : getExternalFunction(name:"raylib_EndTextureMode"),
    BeginShaderMode : getExternalFunction(name:"raylib_BeginShaderMode"),
    EndShaderMode : getExternalFunction(name:"raylib_EndShaderMode"),
    BeginBlendMode : getExternalFunction(name:"raylib_BeginBlendMode"),
    EndBlendMode : getExternalFunction(name:"raylib_EndBlendMode"),
    BeginScissorMode : getExternalFunction(name:"raylib_BeginScissorMode"),
    EndScissorMode : getExternalFunction(name:"raylib_EndScissorMode"),
    //BeginVrStereoMode : getExternalFunction(name:"raylib_BeginVrStereoMode"),
    //EndVrStereoMode : getExternalFunction(name:"raylib_EndVrStereoMode),


    // Shader management 
    LoadShader : getExternalFunction(name:"raylib_LoadShader"),
    LoadShaderFromMemory : getExternalFunction(name:"raylib_LoadShaderFromMemory"),
    IsShaderReady : getExternalFunction(name:"raylib_IsShaderReady"),
    GetShaderLocation : getExternalFunction(name:"raylib_GetShaderLocation"),
    GetShaderLocationAttrib : getExternalFunction(name:"raylib_GetShaderLocationAttrib"),
    SetShaderValueFloat : getExternalFunction(name:"raylib_SetShaderValueFloat"),
    SetShaderValueInt : getExternalFunction(name:"raylib_SetShaderValueInt"),
    SetShaderValueFloatV : getExternalFunction(name:"raylib_SetShaderValueFloatV"),
    SetShaderValueIntV : getExternalFunction(name:"raylib_SetShaderValueIntV"),
    SetShaderValueSampler2D : getExternalFunction(name:"raylib_SetShaderValueSampler2D"),
    SetShaderValueSampler2DV : getExternalFunction(name:"raylib_SetShaderValueSampler2DV"),
    SetShaderValueMatrix : getExternalFunction(name:"raylib_SetShaderValueMatrix"),
    SetShaderValueTexture : getExternalFunction(name:"raylib_SetShaderValueTexture"),
    UnloadShader : getExternalFunction(name:"raylib_UnloadShader"),


    // Screen-space-related functions 
    GetMouseRay : getExternalFunction(name:"raylib_GetMouseRay"),
    GetCameraMatrix : getExternalFunction(name:"raylib_GetCameraMatrix"),
    GetCameraMatrix2D : getExternalFunction(name:"raylib_GetCameraMatrix2D"),
    GetWorldToScreen : getExternalFunction(name:"raylib_GetWorldToScreen"),
    GetScreenToWorld2D : getExternalFunction(name:"raylib_GetScreenToWorld2D"),
    GetWorldToScreenEx : getExternalFunction(name:"raylib_GetWorldToScreenEx"),
    GetWorldToScreen2D : getExternalFunction(name:"raylib_GetWorldToScreen2D"),
    
    // Timing related functions 
    SetTargetFPS : getExternalFunction(name:"raylib_SetTargetFPS"),
    GetFPS : getExternalFunction(name:"raylib_GetFPS"),
    GetFrameTime : getExternalFunction(name:"raylib_GetFrameTime"),
    GetTime : getExternalFunction(name:"raylib_GetTime"),
    
    
    // Misc Functions
    GetRandomValue : getExternalFunction(name:"raylib_GetRandomValue"),
    SetRandomSeed : getExternalFunction(name:"raylib_SetRandomSeed"),
    TakeScreenshot : getExternalFunction(name:"raylib_TakeScreenshot"),
    SetConfigFlags : getExternalFunction(name:"raylib_SetConfigFlags"),
    
    TraceLog : getExternalFunction(name:"raylib_TraceLog"),
    SetTraceLogLevel : getExternalFunction(name:"raylib_SetTraceLogLevel"),
    OpenURL : getExternalFunction(name:"raylib_OpenURL"),
    
    
    
    
    
    // File management functions
    LoadFileData :: (fileName) {
        @:buf = MemoryBuffer.new();
        buf.bindNative(handle:base__LoadFileData(fileName));
        return buf;
    },
    SaveFileData :: (fileName, bytes => MemoryBuffer.type) {
        base__SaveFileData(fileName, bytes:bytes.handle);
    },
        
    ExportDataAsCode ::(bytes => MemoryBuffer.type, fileName) {
        base__ExportDataAsCode(bytes:bytes.handle, fileName);
    },
    LoadFileText : getExternalFunction(name:"raylib_LoadFileText"),
    SaveFileText : getExternalFunction(name:"raylib_SaveFileText"),
    FileExists : getExternalFunction(name:"raylib_FileExists"),
    DirectoryExists : getExternalFunction(name:"raylib_DirectoryExists"),
    IsFileExtension : getExternalFunction(name:"raylib_IsFileExtension"),
    GetFileLength : getExternalFunction(name:"raylib_GetFileLength"),
    GetFileExtension : getExternalFunction(name:"raylib_GetFileExtension"),
    GetFileName : getExternalFunction(name:"raylib_GetFileName"),
    GetFileNameWithoutExt : getExternalFunction(name:"raylib_GetFileNameWithoutExt"),
    GetDirectoryPath : getExternalFunction(name:"raylib_GetDirectoryPath"),
    GetPrevDirectoryPath : getExternalFunction(name:"raylib_GetPrevDirectoryPath"),
    GetWorkingDirectory : getExternalFunction(name:"raylib_GetWorkingDirectory"),
    GetApplicationDirectory : getExternalFunction(name:"raylib_GetApplicationDirectory"),
    ChangeDirectory : getExternalFunction(name:"raylib_ChangeDirectory"),
    IsPathFile : getExternalFunction(name:"raylib_IsPathFile"),
    LoadDirectoryFiles : getExternalFunction(name:"raylib_LoadDirectoryFiles"),
    LoadDirectoryFilesEx : getExternalFunction(name:"raylib_LoadDirectoryFilesEx"),
    IsFileDropped : getExternalFunction(name:"raylib_IsFileDropped"),   
    LoadDroppedFiles : getExternalFunction(name:"raylib_LoadDroppedFiles"),
    GetFileModTime : getExternalFunction(name:"raylib_GetFileModTime"),
        
    
    
    // Compression/Encoding 
    CompressData ::(bytes => MemoryBuffer.type) {
        @:out = MemoryBuffer.new();
        out.bindNative(handle:base__CompressData(bytes:bytes.handle));
        return out;
    },
    DecompressData ::(bytes => MemoryBuffer.type) {
        @:out = MemoryBuffer.new();
        out.bindNative(handle:base__DecompressData(bytes:bytes.handle));
        return out;
    },
    EncodeDataBase64 ::(bytes => MemoryBuffer.type) {
        return base__EncodeDataBase64(bytes:bytes.handle);
    },
    DecodeDataBase64 ::(data => String) {
        @:out = MemoryBuffer.new();
        out.bindNative(handle:base__DecodeDataBase64(data));
        return out;        
    },
    // Input handling 
    
    // Keyboard
    IsKeyPressed : getExternalFunction(name:"raylib_IsKeyPressed"),
    IsKeyPressedRepeat : getExternalFunction(name:"raylib_IsKeyPressedRepeat"),
    IsKeyDown : getExternalFunction(name:"raylib_IsKeyDown"),
    IsKeyReleased : getExternalFunction(name:"raylib_IsKeyReleased"),
    IsKeyUp : getExternalFunction(name:"raylib_IsKeyUp"),
    SetExitKey : getExternalFunction(name:"raylib_SetExitKey"),
    GetKeyPressed : getExternalFunction(name:"raylib_GetKeyPressed"),
    GetCharPressed : getExternalFunction(name:"raylib_GetCharPressed"),
    
    // gamepads 
    IsGamepadAvailable : getExternalFunction(name:"raylib_IsGamepadAvailable"),
    GetGamepadName : getExternalFunction(name:"raylib_GetGamepadName"),
    IsGamepadButtonPressed : getExternalFunction(name:"raylib_IsGamepadButtonPressed"),
    IsGamepadButtonDown : getExternalFunction(name:"raylib_IsGamepadButtonDown"),
    IsGamepadButtonReleased : getExternalFunction(name:"raylib_IsGamepadButtonReleased"),
    IsGamepadButtonUp : getExternalFunction(name:"raylib_IsGamepadButtonUp"),
    GetGamepadButtonPressed : getExternalFunction(name:"raylib_GetGamepadButtonPressed"),
    GetGamepadAxisCount : getExternalFunction(name:"raylib_GetGamepadAxisCount"),
    GetGamepadAxisMovement : getExternalFunction(name:"raylib_GetGamepadAxisMovement"),
    SetGamepadMappings : getExternalFunction(name:"raylib_SetGamepadMappings"),
    
    
    // mouse 
    IsMouseButtonPressed : getExternalFunction(name:"raylib_IsMouseButtonPressed"),
    IsMouseButtonDown : getExternalFunction(name:"raylib_IsMouseButtonDown"),
    IsMouseButtonReleased : getExternalFunction(name:"raylib_IsMouseButtonReleased"),
    IsMouseButtonUp : getExternalFunction(name:"raylib_IsMouseButtonUp"),
    GetMouseX : getExternalFunction(name:"raylib_GetMouseX"),
    GetMouseY : getExternalFunction(name:"raylib_GetMouseY"),
    GetMousePosition : getExternalFunction(name:"raylib_GetMousePosition"),
    GetMouseDelta : getExternalFunction(name:"raylib_GetMouseDelta"),
    SetMousePosition : getExternalFunction(name:"raylib_SetMousePosition"),
    SetMouseOffset : getExternalFunction(name:"raylib_SetMouseOffset"),
    SetMouseScale : getExternalFunction(name:"raylib_SetMouseScale"),
    GetMouseWheelMove : getExternalFunction(name:"raylib_GetMouseWheelMove"),
    GetMouseWheelMoveV : getExternalFunction(name:"raylib_GetMouseWheelMoveV"),
    SetMouseCursor : getExternalFunction(name:"raylib_SetMouseCursor"),
    
    GetTouchX : getExternalFunction(name:"raylib_GetTouchX"),
    GetTouchY : getExternalFunction(name:"raylib_GetTouchY"),
    GetTouchPosition : getExternalFunction(name:"raylib_GetTouchPosition"),
    GetTouchPointId : getExternalFunction(name:"raylib_GetTouchPointId"),
    GetTouchPointCount : getExternalFunction(name:"raylib_GetTouchPointCount"),
    
    SetGesturedEnabled : getExternalFunction(name:"raylib_SetGesturesEnabled"),
    IsGestureDetected: getExternalFunction(name:"raylib_IsGestureDetected"),
    GetGestureDetected : getExternalFunction(name:"raylib_GetGestureDetected"),
    GetGestureHoldDuration : getExternalFunction(name:"raylib_GetGestureHoldDuration"),
    GetGestureDragVector : getExternalFunction(name: "raylib_GetGestureDragVector"),
    GetGestureDragAngle : getExternalFunction(name:"raylib_GetGestureDragAngle"),
    GetGesturePinchVector : getExternalFunction(name:"raylib_GetGesturePinchVector"),
    GetGesturePinchAngle : getExternalFunction(name:"raylib_GetGesturePinchAngle"),
    
    
    UpdateCamera : getExternalFunction(name:"raylib_UpdateCamera"),
    UpdateCameraPro : getExternalFunction(name:"raylib_UpdateCameraPro"),
    
    
    
    
    
    
    
    // rshapes
    
    SetShapesTexture : getExternalFunction(name:"raylib_SetShapesTexture"),
    
    
    // basic shapes
    DrawPixel : getExternalFunction(name:"raylib_DrawPixel"),
    DrawPixelV : getExternalFunction(name:"raylib_DrawPixelV"),
    DrawLine : getExternalFunction(name:"raylib_DrawLine"),
    DrawLineV : getExternalFunction(name:"raylib_DrawLineV"),
    DrawLineEx : getExternalFunction(name:"raylib_DrawLineEx"),
    DrawLineBezier : getExternalFunction(name:"raylib_DrawLineBezier"),
    DrawLineBezierQuad : getExternalFunction(name:"raylib_DrawLineBezierQuad"),
    DrawLineBezierCubic : getExternalFunction(name:"raylib_DrawLineBezierCubic"),
    DrawLineBSpline : getExternalFunction(name:"raylib_DrawLineBSpline"),
    DrawLineCatmullRom : getExternalFunction(name:"raylib_DrawLineCatmullRom"),
    DrawLineStrip : getExternalFunction(name:"raylib_DrawLineStrip"),
    DrawCircle : getExternalFunction(name:"raylib_DrawCircle"),
    DrawCircleSector : getExternalFunction(name:"raylib_DrawCircleSector"),
    DrawCircleSectorLines : getExternalFunction(name:"raylib_DrawCircleSectorLines"),
    DrawCircleGradient : getExternalFunction(name:"raylib_DrawCircleGradient"),
    DrawCircleV : getExternalFunction(name:"raylib_DrawCircleV"),
    DrawCircleLines : getExternalFunction(name: "raylib_DrawCircleLines"),
    DrawEllipse : getExternalFunction(name: "raylib_DrawEllipse"),
    DrawEllipseLines : getExternalFunction(name: "raylib_DrawEllipseLines"),
    DrawRing : getExternalFunction(name: "raylib_DrawRing"),
    DrawRingLines : getExternalFunction(name: "raylib_DrawRingLines"),
    DrawRectangle : getExternalFunction(name:"raylib_DrawRectangle"),
    DrawRectangleV : getExternalFunction(name:"raylib_DrawRectangleV"),
    DrawRectangleRec : getExternalFunction(name: "raylib_DrawRectangleRec"),
    DrawRectanglePro : getExternalFunction(name: "raylib_DrawRectanglePro"),
    DrawRectangleGradientV : getExternalFunction(name: "raylib_DrawRectangleGradientV"),
    DrawRectangleGradientH : getExternalFunction(name: "raylib_DrawRectangleGradientH"),
    DrawRectangleGradientEx : getExternalFunction(name: "raylib_DrawRectangleGradientEx"),
    DrawRectangleLines : getExternalFunction(name : "raylib_DrawRectangleLines"),
    DrawRectangleLinesEx : getExternalFunction(name : "raylib_DrawRectangleLinesEx"),
    DrawRectangleRounded : getExternalFunction(name : "raylib_DrawRectangleRounded"),
    DrawRectangleRoundedLines : getExternalFunction(name : "raylib_DrawRectangleRoundedLines"),
    DrawTriangle : getExternalFunction(name : "raylib_DrawTriangle"),
    DrawTriangleLines : getExternalFunction(name: "raylib_DrawTriangleLines"),
    DrawTriangleFan : getExternalFunction(name: "raylib_DrawTriangleFan"),
    DrawTriangleStrip : getExternalFunction(name: "raylib_DrawTriangleStrip"),
    DrawPoly : getExternalFunction(name : "raylib_DrawPoly"),
    DrawPolyLines : getExternalFunction(name : "raylib_DrawPolyLines"),
    DrawPolyLinesEx : getExternalFunction(name: "raylib_DrawPolyLinesEx"),
    
    
    CheckCollisionRecs : getExternalFunction(name: "raylib_CheckCollisionRecs"),
    CheckCollisionCircles : getExternalFunction(name: "raylib_CheckCollisionCircles"),
    CheckCollisionCircleRec : getExternalFunction(name : "raylib_CheckCollisionCircleRec"),
    CheckCollisionPointRec : getExternalFunction(name : "raylib_CheckCollisionPointRec"),
    CheckCollisionPointCircle : getExternalFunction(name: "raylib_CheckCollisionPointCircle"),
    CheckCollisionPointTriangle : getExternalFunction(name: "raylib_CheckCollisionPointTriangle"),
    CheckCollisionPointPoly : getExternalFunction(name: "raylib_CheckCollisionPointPoly"),
    CheckCollisionLines : getExternalFunction(name: "raylib_CheckCollisionLines"),
    CheckCollisionPointLine : getExternalFunction(name:"raylib_CheckCollisionPointLine"),
    GetCollisionRec : getExternalFunction(name: "raylib_GetCollisionRec"),
    
    
    
    // rtextures 
    LoadImage : getExternalFunction(name: "raylib_LoadImage"),
    LoadImageRaw : getExternalFunction(name: "raylib_LoadImageRaw"),
    LoadImageSvg : getExternalFunction(name: "raylib_LoadImageSvg"),
    LoadImageAnim : getExternalFunction(name: "raylib_LoadImageAnim"),
    LoadImageFromMemory :: (fileType, bytes => MemoryBuffer.type) {
        return base__LoadImageFromMemory(fileType, bytes:bytes.handle);
    },
    LoadImageFromTexture : getExternalFunction(name: "raylib_LoadImageFromTexture"),
    LoadImageFromScreen : getExternalFunction(name: "raylib_LoadImageFromScreen"),
    IsImageReady : getExternalFunction(name: "raylib_IsImageReady"),
    UnloadImage : getExternalFunction(name: "raylib_UnloadImage"),
    ExportImage : getExternalFunction(name: "raylib_ExportImage"),
    ExportImageToMemory : getExternalFunction(name: "raylib_ExportImageToMemory"),
    ExportImageAsCode : getExternalFunction(name: "raylib_ExportImageAsCode"),


    GenImageColor : getExternalFunction(name: "raylib_GenImageColor"),
    GenImageGradientLinear : getExternalFunction(name: "raylib_GenImageGradientLinear"),
    GenImageGradientRadial : getExternalFunction(name: "raylib_GenImageGradientRadial"),
    GenImageGradientSquare : getExternalFunction(name: "raylib_GenImageGradientSquare"),
    GenImageChecked : getExternalFunction(name: "raylib_GenImageChecked"),
    GenImageWhiteNoise : getExternalFunction(name: "raylib_GenImageWhiteNoise"),
    GenImagePerlinNoise : getExternalFunction(name: "raylib_GenImagePerlinNoise"),
    GenImageCellular : getExternalFunction(name: "raylib_GenImageCellular"),
    GenImageText : getExternalFunction(name: "raylib_GenImageText"),
  
    ImageCopy : getExternalFunction(name:"raylib_ImageCopy"),
    ImageFromImage : getExternalFunction(name:"raylib_ImageFromImage"),
    ImageText : getExternalFunction(name:"raylib_ImageText"),
    ImageTextEx : getExternalFunction(name:"raylib_ImageTextEx"),
    ImageFormat : getExternalFunction(name:"raylib_ImageFormat"),
    ImageToPOT : getExternalFunction(name:"raylib_ImageToPOT"),
    ImageCrop : getExternalFunction(name:"raylib_ImageCrop"),
    ImageAlphaCrop : getExternalFunction(name:"raylib_ImageAlphaCrop"),
    ImageAlphaClear : getExternalFunction(name:"raylib_ImageAlphaClear"),
    ImageAlphaMask : getExternalFunction(name:"raylib_ImageAlphaMask"),
    ImageAlphaPremultiply : getExternalFunction(name:"raylib_ImageAlphaPremultiply"),
    ImageBlurGaussian : getExternalFunction(name:"raylib_ImageBlurGaussian"),
    ImageResize : getExternalFunction(name:"raylib_ImageResize"),
    ImageResizeNN : getExternalFunction(name:"raylib_ImageResizeNN"),
    ImageResizeCanvas : getExternalFunction(name:"raylib_ImageResizeCanvas"),
    ImageMipmaps : getExternalFunction(name:"raylib_ImageMipmaps"),
    ImageDither : getExternalFunction(name:"raylib_ImageDither"),
    ImageFlipVertical : getExternalFunction(name:"raylib_ImageFlipVertical"),
    ImageFlipHorizontal : getExternalFunction(name:"raylib_ImageFlipHorizontal"),
    ImageRotate : getExternalFunction(name:"raylib_ImageRotate"),
    ImageRotateCW : getExternalFunction(name:"raylib_ImageRotateCW"),    
    ImageRotateCCW : getExternalFunction(name:"raylib_ImageRotateCCW"),    
    ImageColorTint : getExternalFunction(name:"raylib_ImageColorTint"),
    ImageColorInvert : getExternalFunction(name:"raylib_ImageColorInvert"),
    ImageColorGrayscale : getExternalFunction(name:"raylib_ImageColorGrayscale"),
    ImageColorContrast : getExternalFunction(name:"raylib_ImageColorContrast"),
    ImageColorBrightness : getExternalFunction(name:"raylib_ImageColorBrightness"),
    ImageColorReplace : getExternalFunction(name:"raylib_ImageColorReplace"),
    LoadImageColors : getExternalFunction(name:"raylib_LoadImageColors"),
    LoadImagePalette : getExternalFunction(name:"raylib_LoadImagePalette"),
    GetImageAlphaBorder : getExternalFunction(name:"raylib_GetImageAlphaBorder"),
    GetImageColor : getExternalFunction(name:"raylib_GetImageColor"),
    
    
    ImageClearBackground : getExternalFunction(name:"raylib_ImageClearBackground"),
    ImageDrawPixel : getExternalFunction(name:"raylib_ImageDrawPixel"),
    ImageDrawPixelV : getExternalFunction(name:"raylib_ImageDrawPixelV"),
    ImageDrawLine : getExternalFunction(name:"raylib_ImageDrawLine"),
    ImageDrawLineV : getExternalFunction(name:"raylib_ImageDrawLineV"),
    ImageDrawCircle : getExternalFunction(name:"raylib_ImageDrawCircle"),
    ImageDrawCircleV : getExternalFunction(name:"raylib_ImageDrawCircleV"),
    ImageDrawCircleLines : getExternalFunction(name:"raylib_ImageDrawCircleLines"),
    ImageDrawCircleLinesV : getExternalFunction(name:"raylib_ImageDrawCircleLinesV"),
    ImageDrawRectangle : getExternalFunction(name:"raylib_ImageDrawRectangle"),
    ImageDrawRectangleV : getExternalFunction(name:"raylib_ImageDrawRectangleV"),
    ImageDrawRectangleRec : getExternalFunction(name:"raylib_ImageDrawRectangleRec"),
    ImageDrawRectangleLines : getExternalFunction(name:"raylib_ImageDrawRectangleLines"),
    ImageDraw : getExternalFunction(name:"raylib_ImageDraw"),
    ImageDrawText : getExternalFunction(name:"raylib_ImageDrawText"),
    ImageDrawTextEx : getExternalFunction(name:"raylib_ImageDrawTextEx"),



    LoadTexture : getExternalFunction(name:"raylib_LoadTexture"),
    LoadTextureFromImage : getExternalFunction(name:"raylib_LoadTextureFromImage"),
    LoadTextureCubemap : getExternalFunction(name:"raylib_LoadTextureCubemap"),
    LoadRenderTexture : getExternalFunction(name:"raylib_LoadRenderTexture"),
    IsTextureReady : getExternalFunction(name:"raylib_IsTextureReady"),
    UnloadTexture : getExternalFunction(name:"raylib_UnloadTexture"),
    IsRenderTextureReady : getExternalFunction(name:"raylib_IsRenderTextureReady"),
    UnloadRenderTexture : getExternalFunction(name:"raylib_UnloadRenderTexture"),
    UpdateTexture : getExternalFunction(name:"raylib_UpdateTexture"),
    UpdateTextureRec : getExternalFunction(name:"raylib_UpdateTextureRec"),


    GenTextureMipmaps : getExternalFunction(name:"raylib_GenTextureMipmaps"),
    SetTextureFilter : getExternalFunction(name:"raylib_SetTextureFilter"),
    SetTextureWrap : getExternalFunction(name:"raylib_SetTextureWrap"),


    DrawTexture : getExternalFunction(name:"raylib_DrawTexture"),
    DrawTextureV : getExternalFunction(name:"raylib_DrawTextureV"),
    DrawTextureEx : getExternalFunction(name:"raylib_DrawTextureEx"),
    DrawTextureRec : getExternalFunction(name:"raylib_DrawTextureRec"),
    DrawTexturePro : getExternalFunction(name:"raylib_DrawTexturePro"),
    DrawTextureNPatch : getExternalFunction(name:"raylib_DrawTextureNPatch"),


    Fade : getExternalFunction(name:"raylib_Fade"),
    ColorToInt : getExternalFunction(name:"raylib_ColorToInt"),
    ColorNormalize : getExternalFunction(name:"raylib_ColorNormalize"),
    ColorFromNormalized : getExternalFunction(name:"raylib_ColorFromNormalized"),
    ColorToHSV : getExternalFunction(name:"raylib_ColorToHSV"),
    ColorFromHSV : getExternalFunction(name:"raylib_ColorFromHSV"),
    ColorTint : getExternalFunction(name:"raylib_ColorTint"),
    ColorBrightness : getExternalFunction(name:"raylib_ColorBrightness"),
    ColorContrast : getExternalFunction(name:"raylib_ColorContrast"),
    ColorAlpha : getExternalFunction(name:"raylib_ColorAlpha"),
    ColorAlphaBlend : getExternalFunction(name:"raylib_ColorAlphaBlend"),
    GetColor : getExternalFunction(name:"raylib_GetColor"),
    GetPixelColor ::(bytes => MemoryBuffer.type, format) {
        return base__GetPixelColor(bytes:bytes.handle, format);
    },
    SetPixelColor ::(bytes => MemoryBuffer.type, color, format) {
        return base__SetPixelColor(bytes:bytes.handle, color, format);
    },
    GetPixelDataSize : getExternalFunction(name:"raylib_GetPixelDataSize"),


    GetFontDefault : getExternalFunction(name:"raylib_GetFontDefault"),
    LoadFont : getExternalFunction(name:"raylib_LoadFont"),
    LoadFontEx : getExternalFunction(name:"raylib_LoadFontEx"),
    LoadFontFromImage : getExternalFunction(name:"raylib_LoadFontFromImage"),
    LoadFontFromMemory ::(fileType, bytes => MemoryBuffer.type, fontSize, fontChars) {
        return base__LoadFontFromMemory(fileType, bytes:bytes.handle, fontSize, fontChars);
    },
    IsFontReady : getExternalFunction(name:"raylib_IsFontReady"),
    LoadFontData :: (bytes, fontSize, fontChars, type) {
        return base__LoadFontData(bytes:bytes.handle, fontSize, fontChars, type);
    }, 
    GenImageFontAtlas : getExternalFunction(name:"raylib_GenImageFontAtlas"),
    UnloadFont : getExternalFunction(name:"raylib_UnloadFont"),
    ExportFontAsCode : getExternalFunction(name:"raylib_ExportFontAsCode"),


    DrawFPS : getExternalFunction(name:"raylib_DrawFPS"),
    DrawText : getExternalFunction(name:"raylib_DrawText"),
    DrawTextEx : getExternalFunction(name:"raylib_DrawTextEx"),
    DrawTextPro : getExternalFunction(name:"raylib_DrawTextPro"),


    SetTextLineSpacing : getExternalFunction(name:"raylib_SetTextLineSpacing"),
    MeasureText : getExternalFunction(name:"raylib_MeasureText"),
    MeasureTextEx : getExternalFunction(name:"raylib_MeasureTextEx"),
    GetGlyphIndex : getExternalFunction(name:"raylib_GetGlyphIndex"),
    GetGlyphInfo : getExternalFunction(name:"raylib_GetGlyphInfo"),
    GetGlyphAtlasRec : getExternalFunction(name:"raylib_GetGlyphAtlasRec"),





    DrawLine3D : getExternalFunction(name:"raylib_DrawLine3D"),
    DrawPoint3D : getExternalFunction(name:"raylib_DrawPoint3D"),
    DrawCircle3D : getExternalFunction(name:"raylib_DrawCircle3D"),
    DrawTriangle3D : getExternalFunction(name:"raylib_DrawTriangle3D"),
    DrawTriangleStrip3D : getExternalFunction(name:"raylib_DrawTriangleStrip3D"),
    DrawCube : getExternalFunction(name:"raylib_DrawCube"),
    DrawCubeV : getExternalFunction(name:"raylib_DrawCubeV"),
    DrawCubeWires : getExternalFunction(name:"raylib_DrawCubeWires"),
    DrawCubeWiresV : getExternalFunction(name:"raylib_DrawCubeWiresV"),
    DrawSphere : getExternalFunction(name:"raylib_DrawSphere"),
    DrawSphereEx : getExternalFunction(name:"raylib_DrawSphereEx"),
    DrawSphereWires : getExternalFunction(name:"raylib_DrawSphereWires"),
    DrawCylinder : getExternalFunction(name:"raylib_DrawCylinder"),
    DrawCylinderEx : getExternalFunction(name:"raylib_DrawCylinderEx"),
    DrawCylinderWires : getExternalFunction(name:"raylib_DrawCylinderWires"),
    DrawCylinderWiresEx : getExternalFunction(name:"raylib_DrawCylinderWiresEx"),
    DrawCapsule : getExternalFunction(name:"raylib_DrawCapsule"),
    DrawCapsuleWires : getExternalFunction(name:"raylib_DrawCapsuleWires"),
    DrawPlane : getExternalFunction(name:"raylib_DrawPlane"),
    DrawRay : getExternalFunction(name:"raylib_DrawRay"),
    DrawGrid : getExternalFunction(name:"raylib_DrawGrid"),






    LoadModel : getExternalFunction(name:"raylib_LoadModel"),
    LoadModelFromMesh : getExternalFunction(name:"raylib_LoadModelFromMesh"),
    IsModelReady : getExternalFunction(name:"raylib_IsModelReady"),
    UnloadModel : getExternalFunction(name:"raylib_UnloadModel"),
    GetModelBoundingBox : getExternalFunction(name:"raylib_GetModelBoundingBox"),


    DrawModel : getExternalFunction(name:"raylib_DrawModel"),
    DrawModelEx : getExternalFunction(name:"raylib_DrawModelEx"),
    DrawModelWires : getExternalFunction(name:"raylib_DrawModelWires"),
    DrawModelWiresEx : getExternalFunction(name:"raylib_DrawModelWiresEx"),
    DrawBoundingBox : getExternalFunction(name:"raylib_DrawBoundingBox"),
    DrawBillboard : getExternalFunction(name:"raylib_DrawBillboard"),
    DrawBillboardRec : getExternalFunction(name:"raylib_DrawBillboardRec"),
    DrawBillboardPro : getExternalFunction(name:"raylib_DrawBillboardPro"),


    UploadMesh : getExternalFunction(name:"raylib_UploadMesh"),
    UpdateMeshBuffer ::(mesh, index, bytes, offset) {
        base__UpdateMeshBuffer(mesh, index, bytes:bytes.handle, offset);
    },
    UnloadMesh : getExternalFunction(name:"raylib_UnloadMesh"),
    DrawMesh : getExternalFunction(name:"raylib_DrawMesh"),
    DrawMeshInstanced : getExternalFunction(name:"raylib_DrawMeshInstanced"),
    ExportMesh : getExternalFunction(name:"raylib_ExportMesh"),
    GetMeshBoundingBox : getExternalFunction(name:"raylib_GetMeshBoundingBox"),
    GenMeshTangents : getExternalFunction(name:"raylib_GenMeshTangents"),


    GenMeshPoly : getExternalFunction(name:"raylib_GenMeshPoly"),
    GenMeshPlane : getExternalFunction(name:"raylib_GenMeshPlane"),
    GenMeshCube : getExternalFunction(name:"raylib_GenMeshCube"),
    GenMeshSphere : getExternalFunction(name:"raylib_GenMeshSphere"),
    GenMeshHemiSphere : getExternalFunction(name:"raylib_GenMeshHemiSphere"),
    GenMeshCylinder : getExternalFunction(name:"raylib_GenMeshCylinder"),
    GenMeshCone : getExternalFunction(name:"raylib_GenMeshCone"),
    GenMeshTorus : getExternalFunction(name:"raylib_GenMeshTorus"),
    GenMeshKnot : getExternalFunction(name:"raylib_GenMeshKnot"),
    GenMeshHeightmap : getExternalFunction(name:"raylib_GenMeshHeightmap"),
    GenMeshCubicmap : getExternalFunction(name:"raylib_GenMeshCubicmap"),


    LoadMaterials : getExternalFunction(name:"raylib_LoadMaterials"),
    LoadMaterialDefault : getExternalFunction(name:"raylib_LoadMaterialDefault"),
    IsMaterialReady : getExternalFunction(name:"raylib_IsMaterialReady"),
    UnloadMaterial : getExternalFunction(name:"raylib_UnloadMaterial"),
    SetMaterialTexture : getExternalFunction(name:"raylib_SetMaterialTexture"),
    SetMaterialMapColor : getExternalFunction(name:"raylib_SetMaterialMapColor"),
    SetMaterialMapValue : getExternalFunction(name:"raylib_SetMaterialMapValue"),
    SetModelMeshMaterial : getExternalFunction(name:"raylib_SetModelMeshMaterial"),


    LoadModelAnimations : getExternalFunction(name:"raylib_LoadModelAnimations"),
    UpdateModelAnimation : getExternalFunction(name:"raylib_UpdateModelAnimation"),
    UnloadModelAnimation : getExternalFunction(name:"raylib_UnloadModelAnimation"),
    IsModelAnimationValid : getExternalFunction(name:"raylib_IsModelAnimationValid"),


    CheckCollisionSpheres : getExternalFunction(name:"raylib_CheckCollisionSpheres"),
    CheckCollisionBoxes : getExternalFunction(name:"raylib_CheckCollisionBoxes"),
    CheckCollisionBoxSphere : getExternalFunction(name:"raylib_CheckCollisionBoxSphere"),
    GetRayCollisionSphere : getExternalFunction(name:"raylib_GetRayCollisionSphere"),
    GetRayCollisionBox : getExternalFunction(name:"raylib_GetRayCollisionBox"),
    GetRayCollisionMesh : getExternalFunction(name:"raylib_GetRayCollisionMesh"),
    GetRayCollisionTriangle : getExternalFunction(name:"raylib_GetRayCollisionTriangle"),
    GetRayCollisionQuad : getExternalFunction(name:"raylib_GetRayCollisionQuad"),

    InitAudioDevice : getExternalFunction(name:"raylib_InitAudioDevice"),
    CloseAudioDevice : getExternalFunction(name:"raylib_CloseAudioDevice"),
    IsAudioDeviceReady : getExternalFunction(name:"raylib_IsAudioDeviceReady"),
    SetMasterVolume : getExternalFunction(name:"raylib_SetMasterVolume"),


    LoadWave : getExternalFunction(name:"raylib_LoadWave"),
    LoadWaveFromMemory ::(fileType, bytes => MemoryBuffer.type) {
        return base__LoadWaveFromMemory(fileType, bytes:bytes.handle);
    },
    IsWaveReady : getExternalFunction(name:"raylib_IsWaveReady"),
    LoadSound : getExternalFunction(name:"raylib_LoadSound"),
    LoadSoundAlias : getExternalFunction(name:"raylib_LoadSoundAlias"),
    LoadSoundFromWave : getExternalFunction(name:"raylib_LoadSoundFromWave"),
    IsSoundReady : getExternalFunction(name:"raylib_IsSoundReady"),
    UpdateSound ::(sound, bytes => MemoryBuffer.type) {
        base__UpdateSound(sound, bytes:bytes.handle);    
    },
    UnloadWave : getExternalFunction(name:"raylib_UnloadWave"),
    UnloadSound : getExternalFunction(name:"raylib_UnloadSound"),
    UnloadSoundAlias : getExternalFunction(name:"raylib_UnloadSoundAlias"),
    ExportWave : getExternalFunction(name:"raylib_ExportWave"),
    ExportWaveAsCode : getExternalFunction(name:"raylib_ExportWaveAsCode"),


    PlaySound : getExternalFunction(name:"raylib_PlaySound"),
    StopSound : getExternalFunction(name:"raylib_StopSound"),
    PauseSound : getExternalFunction(name:"raylib_PauseSound"),
    ResumeSound : getExternalFunction(name:"raylib_ResumeSound"),
    IsSoundPlaying : getExternalFunction(name:"raylib_IsSoundPlaying"),
    SetSoundVolume : getExternalFunction(name:"raylib_SetSoundVolume"),
    SetSoundPitch : getExternalFunction(name:"raylib_SetSoundPitch"),
    SetSoundPan : getExternalFunction(name:"raylib_SetSoundPan"),
    WaveCopy : getExternalFunction(name:"raylib_WaveCopy"),
    WaveCrop : getExternalFunction(name:"raylib_WaveCrop"),
    WaveFormat : getExternalFunction(name:"raylib_WaveFormat"),
    LoadWaveSamples ::(wave) {
        @:m = MemoryBuffer.new();
        m.bindNative(handle:base__LoadWaveSamples(wave));
        return m;
    },


    LoadMusicStream : getExternalFunction(name:"raylib_LoadMusicStream"),
    LoadMusicStreamFromMemory :: (fileType, bytes => MemoryBuffer.type) {
        return base__LoadMusicStreamFromMemory(fileType, bytes:bytes.handle);    
    },
    IsMusicReady : getExternalFunction(name:"raylib_IsMusicReady"),
    UnloadMusicStream : getExternalFunction(name:"raylib_UnloadMusicStream"),
    PlayMusicStream : getExternalFunction(name:"raylib_PlayMusicStream"),
    IsMusicStreamPlaying : getExternalFunction(name:"raylib_IsMusicStreamPlaying"),
    UpdateMusicStream : getExternalFunction(name:"raylib_UpdateMusicStream"),
    StopMusicStream : getExternalFunction(name:"raylib_StopMusicStream"),
    PauseMusicStream : getExternalFunction(name:"raylib_PauseMusicStream"),
    ResumeMusicStream : getExternalFunction(name:"raylib_ResumeMusicStream"),
    SeekMusicStream : getExternalFunction(name:"raylib_SeekMusicStream"),
    SetMusicVolume : getExternalFunction(name:"raylib_SetMusicVolume"),
    SetMusicPitch : getExternalFunction(name:"raylib_SetMusicPitch"),
    SetMusicPan : getExternalFunction(name:"raylib_SetMusicPan"),
    GetMusicTimeLength : getExternalFunction(name:"raylib_GetMusicTimeLength"),
    GetMusicTimePlayed : getExternalFunction(name:"raylib_GetMusicTimePlayed"),


    LoadAudioStream : getExternalFunction(name:"raylib_LoadAudioStream"),
    IsAudioStreamReady : getExternalFunction(name:"raylib_IsAudioStreamReady"),
    UnloadAudioStream : getExternalFunction(name:"raylib_UnloadAudioStream"),
    UpdateAudioStream ::(stream, bytes => MemoryBuffer.type) {
        base__UpdateAudioStream(stream, bytes:bytes.handle);
    },
    IsAudioStreamProcessed : getExternalFunction(name:"raylib_IsAudioStreamProcessed"),
    PlayAudioStream : getExternalFunction(name:"raylib_PlayAudioStream"),
    PauseAudioStream : getExternalFunction(name:"raylib_PauseAudioStream"),
    ResumeAudioStream : getExternalFunction(name:"raylib_ResumeAudioStream"),
    IsAudioStreamPlaying : getExternalFunction(name:"raylib_IsAudioStreamPlaying"),
    StopAudioStream : getExternalFunction(name:"raylib_StopAudioStream"),
    SetAudioStreamVolume : getExternalFunction(name:"raylib_SetAudioStreamVolume"),
    SetAudioStreamPitch : getExternalFunction(name:"raylib_SetAudioStreamPitch"),
    SetAudioStreamPan : getExternalFunction(name:"raylib_SetAudioStreamPan"),
    SetAudioStreamBufferSizeDefault : getExternalFunction(name:"raylib_SetAudioStreamBufferSizeDefault"),
    /*
    SetAudioStreamCallback : getExternalFunction(name:"raylib_SetAudioStreamCallback"),

    AttachAudioStreamProcessor : getExternalFunction(name:"raylib_AttachAudioStreamProcessor"),
    DetachAudioStreamProcessor : getExternalFunction(name:"raylib_DetachAudioStreamProcessor"),

    AttachAudioMixedProcessor : getExternalFunction(name:"raylib_AttachAudioMixedProcessor"),
    DetachAudioMixedProcessor : getExternalFunction(name:"raylib_DetachAudioMixedProcessor")
    */


    // Math

    Clamp : getExternalFunction(name:"raylib_Clamp"),
    Lerp : getExternalFunction(name:"raylib_Lerp"),
    Normalize : getExternalFunction(name:"raylib_Normalize"),
    Remap : getExternalFunction(name:"raylib_Remap"),
    Wrap : getExternalFunction(name:"raylib_Wrap"),
    FloatEquals : getExternalFunction(name:"raylib_FloatEquals"),


    Vector2Zero : getExternalFunction(name:"raylib_Vector2Zero"),
    Vector2One : getExternalFunction(name:"raylib_Vector2One"),
    Vector2Add : getExternalFunction(name:"raylib_Vector2Add"),
    Vector2AddValue : getExternalFunction(name:"raylib_Vector2AddValue"),
    Vector2Subtract : getExternalFunction(name:"raylib_Vector2Subtract"),
    Vector2SubtractValue : getExternalFunction(name:"raylib_Vector2SubtractValue"),
    Vector2Length : getExternalFunction(name:"raylib_Vector2Length"),
    Vector2LengthSqr : getExternalFunction(name:"raylib_Vector2LengthSqr"),
    Vector2DotProduct : getExternalFunction(name:"raylib_Vector2DotProduct"),
    Vector2Distance : getExternalFunction(name:"raylib_Vector2Distance"),
    Vector2DistanceSqr : getExternalFunction(name:"raylib_Vector2DistanceSqr"),
    Vector2Angle : getExternalFunction(name:"raylib_Vector2Angle"),
    Vector2LineAngle : getExternalFunction(name:"raylib_Vector2LineAngle"),
    Vector2Scale : getExternalFunction(name:"raylib_Vector2Scale"),
    Vector2Multiply : getExternalFunction(name:"raylib_Vector2Multiply"),
    Vector2Negate : getExternalFunction(name:"raylib_Vector2Negate"),
    Vector2Divide : getExternalFunction(name:"raylib_Vector2Divide"),
    Vector2Normalize : getExternalFunction(name:"raylib_Vector2Normalize"),
    Vector2Transform : getExternalFunction(name:"raylib_Vector2Transform"),
    Vector2Lerp : getExternalFunction(name:"raylib_Vector2Lerp"),
    Vector2Reflect : getExternalFunction(name:"raylib_Vector2Reflect"),
    Vector2Rotate : getExternalFunction(name:"raylib_Vector2Rotate"),
    Vector2MoveTowards : getExternalFunction(name:"raylib_Vector2MoveTowards"),
    Vector2Invert : getExternalFunction(name:"raylib_Vector2Invert"),
    Vector2Clamp : getExternalFunction(name:"raylib_Vector2Clamp"),
    Vector2ClampValue : getExternalFunction(name:"raylib_Vector2ClampValue"),
    Vector2Equals : getExternalFunction(name:"raylib_Vector2Equals"),


    Vector3Zero : getExternalFunction(name:"raylib_Vector3Zero"),
    Vector3One : getExternalFunction(name:"raylib_Vector3One"),
    Vector3Add : getExternalFunction(name:"raylib_Vector3Add"),
    Vector3AddValue : getExternalFunction(name:"raylib_Vector3AddValue"),
    Vector3Subtract : getExternalFunction(name:"raylib_Vector3Subtract"),
    Vector3SubtractValue : getExternalFunction(name:"raylib_Vector3SubtractValue"),
    Vector3Scale : getExternalFunction(name:"raylib_Vector3Scale"),
    Vector3Multiply : getExternalFunction(name:"raylib_Vector3Multiply"),
    Vector3CrossProduct : getExternalFunction(name:"raylib_Vector3CrossProduct"),
    Vector3Perpendicular : getExternalFunction(name:"raylib_Vector3Perpendicular"),
    Vector3Length : getExternalFunction(name:"raylib_Vector3Length"),
    Vector3LengthSqr : getExternalFunction(name:"raylib_Vector3LengthSqr"),
    Vector3DotProduct : getExternalFunction(name:"raylib_Vector3DotProduct"),
    Vector3Distance : getExternalFunction(name:"raylib_Vector3Distance"),
    Vector3DistanceSqr : getExternalFunction(name:"raylib_Vector3DistanceSqr"),
    Vector3Angle : getExternalFunction(name:"raylib_Vector3Angle"),
    Vector3Negate : getExternalFunction(name:"raylib_Vector3Negate"),
    Vector3Divide : getExternalFunction(name:"raylib_Vector3Divide"),
    Vector3Normalize : getExternalFunction(name:"raylib_Vector3Normalize"),
    Vector3Reject : getExternalFunction(name:"raylib_Vector3Reject"),
    Vector3Project : getExternalFunction(name:"raylib_Vector3Project"),
    Vector3OrthoNormalize : getExternalFunction(name:"raylib_Vector3OrthoNormalize"),
    Vector3Transform : getExternalFunction(name:"raylib_Vector3Transform"),
    Vector3RotateByQuaternion : getExternalFunction(name:"raylib_Vector3RotateByQuaternion"),
    Vector3RotateByAxisAngle : getExternalFunction(name:"raylib_Vector3RotateByAxisAngle"),
    Vector3Lerp : getExternalFunction(name:"raylib_Vector3Lerp"),
    Vector3Reflect : getExternalFunction(name:"raylib_Vector3Reflect"),
    Vector3Min : getExternalFunction(name:"raylib_Vector3Min"),
    Vector3Max : getExternalFunction(name:"raylib_Vector3Max"),
    Vector3Barycenter : getExternalFunction(name:"raylib_Vector3Barycenter"),
    Vector3Unproject : getExternalFunction(name:"raylib_Vector3Unproject"),
    Vector3Invert : getExternalFunction(name:"raylib_Vector3Invert"),
    Vector3Clamp : getExternalFunction(name:"raylib_Vector3Clamp"),
    Vector3ClampValue : getExternalFunction(name:"raylib_Vector3ClampValue"),
    Vector3Equals : getExternalFunction(name:"raylib_Vector3Equals"),
    Vector3Refract : getExternalFunction(name:"raylib_Vector3Refract"),


    MatrixDeterminant : getExternalFunction(name:"raylib_MatrixDeterminant"),
    MatrixTrace : getExternalFunction(name:"raylib_MatrixTrace"),
    MatrixTranspose : getExternalFunction(name:"raylib_MatrixTranspose"),
    MatrixInvert : getExternalFunction(name:"raylib_MatrixInvert"),
    MatrixIdentity : getExternalFunction(name:"raylib_MatrixIdentity"),
    MatrixAdd : getExternalFunction(name:"raylib_MatrixAdd"),
    MatrixSubtract : getExternalFunction(name:"raylib_MatrixSubtract"),
    MatrixMultiply : getExternalFunction(name:"raylib_MatrixMultiply"),
    MatrixTranslate : getExternalFunction(name:"raylib_MatrixTranslate"),
    MatrixRotate : getExternalFunction(name:"raylib_MatrixRotate"),
    MatrixRotateX : getExternalFunction(name:"raylib_MatrixRotateX"),
    MatrixRotateY : getExternalFunction(name:"raylib_MatrixRotateY"),
    MatrixRotateZ : getExternalFunction(name:"raylib_MatrixRotateZ"),
    MatrixRotateXYZ : getExternalFunction(name:"raylib_MatrixRotateXYZ"),
    MatrixRotateZYX : getExternalFunction(name:"raylib_MatrixRotateZYX"),
    MatrixScale : getExternalFunction(name:"raylib_MatrixScale"),
    MatrixFrustum : getExternalFunction(name:"raylib_MatrixFrustum"),
    MatrixPerspective : getExternalFunction(name:"raylib_MatrixPerspective"),
    MatrixOrtho : getExternalFunction(name:"raylib_MatrixOrtho"),
    MatrixLookAt : getExternalFunction(name:"raylib_MatrixLookAt"),


    QuaternionAdd : getExternalFunction(name:"raylib_QuaternionAdd"),
    QuaternionAddValue : getExternalFunction(name:"raylib_QuaternionAddValue"),
    QuaternionSubtract : getExternalFunction(name:"raylib_QuaternionSubtract"),
    QuaternionSubtractValue : getExternalFunction(name:"raylib_QuaternionSubtractValue"),
    QuaternionIdentity : getExternalFunction(name:"raylib_QuaternionIdentity"),
    QuaternionLength : getExternalFunction(name:"raylib_QuaternionLength"),
    QuaternionNormalize : getExternalFunction(name:"raylib_QuaternionNormalize"),
    QuaternionInvert : getExternalFunction(name:"raylib_QuaternionInvert"),
    QuaternionMultiply : getExternalFunction(name:"raylib_QuaternionMultiply"),
    QuaternionScale : getExternalFunction(name:"raylib_QuaternionScale"),
    QuaternionDivide : getExternalFunction(name:"raylib_QuaternionDivide"),
    QuaternionLerp : getExternalFunction(name:"raylib_QuaternionLerp"),
    QuaternionNlerp : getExternalFunction(name:"raylib_QuaternionNlerp"),
    QuaternionSlerp : getExternalFunction(name:"raylib_QuaternionSlerp"),
    QuaternionFromVector3ToVector3 : getExternalFunction(name:"raylib_QuaternionFromVector3ToVector3"),
    QuaternionFromMatrix : getExternalFunction(name:"raylib_QuaternionFromMatrix"),
    QuaternionToMatrix : getExternalFunction(name:"raylib_QuaternionToMatrix"),
    QuaternionFromAxisAngle : getExternalFunction(name:"raylib_QuaternionFromAxisAngle"),
    QuaternionToAxisAngle : getExternalFunction(name:"raylib_QuaternionToAxisAngle"),
    QuaternionFromEuler : getExternalFunction(name:"raylib_QuaternionFromEuler"),
    QuaternionToEuler : getExternalFunction(name:"raylib_QuaternionToEuler"),
    QuaternionTransform : getExternalFunction(name:"raylib_QuaternionTransform"),
    QuaternionEquals : getExternalFunction(name:"raylib_QuaternionEquals"),

    GetCameraForward : getExternalFunction(name:"raylib_GetCameraForward"),
    GetCameraUp : getExternalFunction(name:"raylib_GetCameraUp"),
    GetCameraRight : getExternalFunction(name:"raylib_GetCameraRight"),

    CameraMoveForward : getExternalFunction(name:"raylib_CameraMoveForward"),
    CameraMoveUp : getExternalFunction(name:"raylib_CameraMoveUp"),
    CameraMoveRight : getExternalFunction(name:"raylib_CameraMoveRight"),
    CameraMoveToTarget : getExternalFunction(name:"raylib_CameraMoveToTarget"),

    CameraYaw : getExternalFunction(name:"raylib_CameraYaw"),
    CameraPitch : getExternalFunction(name:"raylib_CameraPitch"),
    CameraRoll : getExternalFunction(name:"raylib_CameraRoll"),

    GetCameraViewMatrix : getExternalFunction(name:"raylib_GetCameraViewMatrix"),
    GetCameraProjectionMatrix : getExternalFunction(name:"raylib_GetCameraProjectionMatrix")
    
};  



return raylib;
