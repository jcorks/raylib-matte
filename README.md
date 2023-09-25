<img src="https://github.com/jcorks/raylib-matte/blob/main/logo/logo.png" width=256>


# raylib-matte (raymatte)
Raylib bindings as a standalone Matte executable, adding the full base and math libraries for raylib while also tayloring each function for use within a high-level language. 













**STILL A WORK IN PROGRESS.**
- Extra functions for making game organization easier
- Makefile for MSYS2 (Windows)
- Additional examples


## Compiling
`raymatte` is compiled using Make. Run `make` in the 
base directory with the makefile of your choosing.

## Usage 
`raymatte` can be used in a few different modes.
The default is to look for a `main.mt` in the running directory.
`main.mt` always acts as the first script in the program and is 
run immediately.

Optionally, you can specify a path to start within: 
```
raymatte ./examples/core_2d_camera_platformer
```
Which will change the current directory of `raymatte`, affecting 
`import()`, `LoadFile*` calls as well.

### Debugging
`raymatte` also is built-in with a stdio, GDB-based debugger.
It is accessible by using the `debug` command:
```
raymatte debug ./examples/core_2d_camera_platformer
```

The debugger will pause execution when the `breakpoint()` function
is called, or when an error is thrown.

The currently-understood commands are as follows:

- `p` / `print` : prints an expression, which can include a variable name in scope.
- `s` / `step` : evaluates the next instruction in the VM, which may "step into" a function call.
- `n` / `next` : evaluates the next instruction in the VM, automatically running any instruction that would generate further function scopes. This essentially lets you step to the next instruction in the same scope or higher.
- `bt` / `backtrace` : prints the entire callstack.



### Packaging 

It is possible to bundle scripts and assets in a single file.
Using the `package` command, `raymatte` will create this file 
for you.

```
raymatte package ./path/to/project/
```
In the directory pointed to, there must be a `package.mt` file,
which is a script that returns an array of strings denoting
all asset files that are part of the project. For example,
`package.mt` might look like:

```
return [
  "main.mt",
  "game.mt",
  "assets/a.png",
  "assets/music.mp3"
]
```

Once packaged, the project will exist within a `raymatte.data` file.
When this file is in the running directory of `raymatte`, 
this will be loaded instead of `main.mt`, and all `import()`,
`LoadFileData`, and `LoadFileText` calls will pull from 
this data file with each file corresponding to the name 
output in the original `package.mt` array.

### Embedding

Once `raymatte.data` is created, it is possible to create a new 
version of the `raymatte` binary with `raymatte.data` embedded within it.
This removes the need for any file to be bundled with your binary, simplifying
the process of having people run your game.

This can be done using the `embed` command, which will take a directory
containing the `raymatte.data` and combine it with the running `raymatte` 
instance.

`raymatte embed ./path/to/packagedata/`

This process produces a `raymatte_embedded` which can be used in a 
standalone manner.


## Differences vs. the C API

A number of strict changes exist between the original C/C++ API 
and the Matte bindings. Many of the changes are to leverage
the higher-level nature of the environment, such as replacing 
C-string inputs with Matte strings, replacing "pointer + length" input 
sets with Matte arrays, replacing "byte pointer + length" with 
Matte MemoryBuffer objects, and avoiding use of direct pointers.

These changes are listed here:


- ALL symbols are part of a module object (referred to as a namespace) 
  rather than in scope references
  
- Enums are layed out flat within the raylib namespace

- Enum values were added for UpdateMeshBuffer: `MESH_BUFFER_ID_*`
  which contain values for each buffer index.

- Some functions are not implemented.

  Functions which are currently NOT implemented, but may be in the future:
  -  `BeginVrStereoMode`
  -  `EndVrStereoMode`
  -  `LoadVrStereoConfig`
  -  `UnloadVrStereoConfig`
  -  `SetAudioStreamCallback`
  -  `AttachAudioStreamProcessor`
  -  `DetachAudioStreamProcessor`
  -  `AttachAudioMixedProcessor`
  -  `DetachAudioMixedProcessor`
          
  Functions which do NOT have bindings:
  | Function | Reason |
  |----------|--------|
  |`GetWindowHandle`| No access to lower-level windowing functions to utilize |
  |`MemAlloc` | Not needed. Can just use MemoryBuffer|
  |`MemRealloc` | Not needed. Can just use MemoryBuffer |
  |`MemFree` | Not needed. Can just use MemoryBuffer |
  |`SetTraceLogCallback` | Used by the raylib-matte implementation |
  |`SetLoadFileDataCallback` | Used by the raylib-matte implementation, unavailable |
  |`SetSaveFileDataCallback` | Used by the raylib-matte implementation, unavailable |
  |`SetLoadTextDataCallback` | Used by the raylib-matte implementation, unavailable |
  |`SetSaveTextDataCallback` | Used by the raylib-matte implementation, unavailable |
  |`UnloadFileData` | Not needed. MemoryBuffer can either be freed manually or will auto-free on GC |
  |`UnloadTextData` | Not needed. |
  |`UnloadDirectoryFiles` | Not needed. |
  |`UnloadDroppedFiles` | Not needed. |
  |`UnloadImageColors` | Not needed. |
  |`UnloadImagePalette` | Not needed. |
  |`UnloadFontData` | Not needed. |
  |`DrawTextCodepoint` | Not especially needed with Matte string access. |
  |`DrawTextCodepoints` | Not especially needed with Matte strings access. |
  |All `Text*`, `UTF8`, and `Codepoint` functions | Not needed. Can be handled at the Matte level with the Matte string type, functions, and querries
  |`UnloadModelAnimations` | Not needed. |
  |`Vector3toFloatV` | Not needed. |
  |`MatrixToFloatV` | Not needed. |
  |`UnloadWaveSamples` | Not needed. |
            
- Instances of output/input that call for char * (C-Strings) are replaced 
  with Matte strings.            
          
- Some structs contain members which point to managed references 
  or arrays. These members have specialized getter functions that generate 
  copies of results that can be worked with.
  
  The following functions were added to facilitate these changes:
  | Function | Effect |
  |----------|--------|
  |`ImageGetData(Image)` | Returns a MemoryBuffer copy of the "data" of the image. |
  |`FontGetRecs(Font)` | Returns an array copy of "recs" as Rectangle objects |
  |`FontGetGlyphs(Font)` | Returns an array copy of "glyphs" as GlyphInfo objects |
  |`MeshGetVertices(Mesh)` | Returns a MemoryBuffer copy of "vertices" |
  |`MeshGetTexCoords(Mesh)` | Returns a MemoryBuffer copy of "texcoords" |
  |`MeshGetTexCoords2(Mesh)` | Returns a MemoryBuffer copy of "texcoords2" |
  |`MeshGetNormals(Mesh)` | Returns a MemoryBuffer copy of "normals" |
  |`MeshGetTangents(Mesh)` | Returns a MemoryBuffer copy of "tangents" |
  |`MeshGetColors(Mesh)` | Returns a MemoryBuffer copy of "colors" |
  |`MeshGetIndices(Mesh)` | Returns a MemoryBuffer copy of "vertices" |
  |`MeshGetAnimVertices(Mesh)` | Returns a MemoryBuffer copy of "animVertices" |
  |`MeshGetAnimNormals(Mesh)` | Returns a MemoryBuffer copy of "animNormals" |
  |`MeshGetBoneIDs(Mesh)` | Returns a MemoryBuffer copy of "boneIds" |
  |`MeshGetBoneWeights(Mesh)` | Returns a MemoryBuffer copy of "boneIds" |
  |`ModelGetMeshes(Model)` | Returns an array of Mesh, a copy of "meshes" |
  |`ModelGetMaterials(Model)` | Returns an array of Material, a copy of "materials" |
  |`ModelGetMaterialNumbers(Model)` | Returns an array of numbers, a copy of "meshMaterial" |
  |`ModelGetBones(Model)` | Returns an array of BoneInfo, a copy of "bones" |
  |`ModelGetBindPoses(Model)` | Returns an array of Transform, a copy of "bindPose" |
  |`ModelAnimationGetBones(ModelAnimation)` | Returns an array of BoneInfo, a copy of "bones" |
  |`ModelAnimationGetFramePoses(ModelAnimation)` | Returns an array of array of Transforms, a deep copy "framePoses", which is indexed by frame, then by bone |
  |`WaveGetData(Wave)` | Returns a MemoryBuffer copy of "data" |

  Such objects are NOT able to be produced "by hand" and need to be 
  sourced from raylib functions on some level. Many of these objects 
  also contain OpenGL primitives or other external primitives. The getters 
  to these are inaccessible.

- The `Material` struct replaces accessible "params[4]" with serially defined 
  "param0" "param1", "param2", and "param3". Similarly, "maps" is serially
  defined with "map0", "map1", etc.
  
- Members of structs that point to native objects, such as OpenGL 
  texture IDs are not made available.

- `SetShaderValue` / `SetShaderValueV` takes a pointer argument in 
  C for the data to be uploaded. This has been replaced with 
  `SetShaderValueFloat` / `SetShaderValueFloatV` and 
  `SetShaderValueInt` / `SetShaderValueIntV` for each uniform 
  type available. `Sampler2D` has a separate 
  `SetShaderValueSampler2D` / `SetShaderValueSampler2DV`
  
  
  For The V variants, a "numComponents" 
  argument is provided, consisting of the number of values per 
  item. I.e. for a `Vector3`, "numComponents" would be 3. 
  The "value" argument is replaced with a "values" array input 
  consisting of a (flat) array of numbers to pack into the shader.             
  Thus, "numComponents" denotes the groupings of these values within the "values"
  array.

  I.e. uploading 2 `Vector3`s to a shader would look like:
    
    ```
    raylib.SetShaderValueFloatV(
        shader:   myShader,
        locIndex: myLocationIndex,
        numComponents: 3
        values:   [
                        1, 0, 0, //<- Vector 1,
                        0, 1, 0, //<- Vector 2
                  ],
    );
    ```
    
    
  For non-V variants, the values array denotes how many components 
  the value has based on its length. For example, uploading a 
  single int would look like:

    ```
    raylib.SetShaderValueInt(
        shader:   myShader,
        locIndex: myLocationIndex,
        value: [10]
    );
    ```

- Any inputs / outputs that consist of "pointer + size" array are 
  converted to array objects in Matte. The exception to this rule are "pointer + size" 
  of single byte quantities, which are implied to be byte arrays. They follow 
  the rule below.

- Functions that return byte arrays and require byte arrays 
  as arguments are represented as MemoryBuffer objects 
  (import(module:"Matte.Core.MemoryBuffer")). Inputs will always 
  be called "bytes"
  

  
- TraceLog only takes logLevel and text, since built-in string 
  operations for Matte cover the text utilities provided.

- CompressData and DecompressData returns a MemoryBuffer and takes a MemoryBuffer ("bytes").

- `DrawLineStrip`, `DrawTriangleFan`, `DrawTriangleStrip`, and `CheckCollisionPointPoly` all take an input array of "flat values", that is, an array of 
  number values in a single array, rather than an array of xy objects.
  
  I.e.
  ```
  raylib.DrawLineStrip(
    points: [1, 2   3, 4   5, 6],
    color: raylib.GREEN
  )
  ```
  
- `LoadImageAnim` will return an image object with an extra public member called "frames",
  which contains the output frame count
  
- `UpdateTexture` and `UpdateTextureRec` do not take a raw buffer of pixels to 
  update the texture, instead they take an image. They behave as follows:
  ```
    UpdateTexture(
        Texture2D texture,
        Image image
    )

    UpdateTextureRec(
        Texture2D texture,
        Vector2 position, // the top-left to place the Image
        Image image
    )
  ```
- `GetPixelColor` and `SetPixelColor` use a MemoryBuffer object to 
  facilitate byte access.
  
- `LoadFontEx` and `LoadFontData` take an array of single-character strings into "fontChars" argument,
  removing the "glyphCount" argument.
  
- `LoadFontData` takes "bytes" (a MemoryBuffer), "fontSize", "fontChars" (an array of single-character strings), and type.
   
- `GenImageFontAtlas` has the "recs" argument removed. Instead, the return value is changed: an Object is returned with 2 members, 
  "image" containing the output `Image`, and "recs" containing an array of `Rectangle` that would have been output.
  In addition, "chars" input will be an array of `GlyphInfo`, removing the need for "glyphCount".
  
- `DrawTriangleStrip3D` takes an array of points and a color.
  
- `DrawMeshInstanced` takes 3 arguments, the last of which is an array of `Matrix`.
  The size of the array determines the instance count
  
- `LoadMaterials` returns an array of `Material` instances and removes the 
  "materialCount" argument

- `Vector2Equals` returns a boolean instead of an int.

- `Vector3Equals` returns a boolean instead of an int.

- `QuaternionEquals` returns a boolean instead of an int.
  
- `QuaternionToAxisAngle` only takes the `Quaternion` argument and, instead, returns 
  an object containing an "axis" and "angle" member, representing the 
  output of the function.
  
- `UpdateSound` takes a MemoryBuffer as input ("bytes")

- `LoadWaveFromMemory` takes a MemoryBuffer as input ("bytes")

- `LoadWaveSamples` returns a MemoryBuffer.

- `LoadMusicStreamFromMemory` takes a MemoryBuffer as input ("bytes")



## Additional Notes

When cloning, use git clone --recursive (url to this repo) to ensure copying the submodules matte and raylib.
