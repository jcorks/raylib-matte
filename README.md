# Raylib-Matte (raymatte)
Raylib bindings for Matte with some extra goodies.


**STILL A WORK IN PROGRESS.**

*Progress: 12%*


## Differences vs. the C API

- ALL symbols are part of a module object (referred to as a namespace) 
  rather than in scope references
  
- Enums are layed out flat within the raylib namespace

- Some functions are not implemented or supported:

     Functions which are currently NOT implemented
          `BeginVrStereoMode`
          `EndVrStereoMode`
          `LoadVrStereoConfig`
          `UnloadVrStereoConfig`

     Functions that are NOT supported (with reasons in parentheses)
          `GetWindowHandle` (No access to lower-level windowing functions to utilize)
          `MemAlloc` (Not needed. Can just use MemoryBuffer)
          `MemRealloc` (Not needed. Can just use MemoryBuffer)
          `MemFree` (Not needed. Can just use MemoryBuffer)
          `SetTraceLogCallback` (Used by the raylib-matte)
          `SetLoadFileDataCallback` (Used by the raylib-matte, unavailable)
          `SetSaveFileDataCallback` (Used by the raylib-matte, unavailable)
          `SetLoadTextDataCallback` (Used by the raylib-matte, unavailable)
          `SetSaveTextDataCallback` (Used by the raylib-matte, unavailable)
          `UnloadFileData` (Not needed. MemoryBuffer can either be freed manually or will auto-free on GC)
          `UnloadTextData` (Not needed. MemoryBuffer can either be freed manually or will auto-free on GC)
          `UnloadDirectoryFiles` (Not needed)
          `UnloadDroppedFiles` (Not needed)
        
- Instances of output/input that call for char * (C-Strings) are replaced 
  with matte strings.            
          
- Some structs are designated as "read-only".
  "read-only structs" are where the object is maintained by raylib 
  and isnt meant to be modified by usercode. As such members are retrieved
  using Getters from the Read-Only Member Accessor functions. They follow 
  the syntax [StructName]Get[MemberName] using PascalCase. I.e.:
  ImageGetWidth().
  
  The objects that are read-only structs are:

    `Image` 
    `RenderTexture` / `RenderTexture2D`
    `Texture` / `Texture2D`
    `Shader` (no getters)

  Such objects are NOT able to be produced "by hand" and need to be 
  sourced from raylib functions on some level. 
  
- Members of structs that point to native objects, such as OpenGL 
  texture IDs are not made available.

- SetShaderValue / SetShaderValueV takes a pointer argument in 
  C for the data to be uploaded. This has been replaced with 
  SetShaderValueFloat / SetShaderValueFloatV and 
  SetShaderValueInt / SetShaderValueIntV for each uniform 
  type available. Sampler2D has a separate 
  SetShaderValueSampler2D / SetShaderValueSampler2DV
  
  
  For The V variants, a "numComponents" 
  argument is provided, consisting of the number of values per 
  item. I.e. for a Vec3, numComponents would be 3. 
  The "value" argument is replaced with a "values" array input 
  consisting of a (flat) array of numbers to pack into the shader.             
  Thus, numComponents denotes the groupings of these values within the "values"
  array.

  I.e. uploading 2 Vector3s to a shader would look like:
    
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
  by called "bytes"
  
- Matrix is implemented as an array of Numbers in Matte in OpenGL 
  (column-major) order.
  
- TraceLog only takes logLevel and text, since built-in string 
  operations for Matte cover the text utilities provided.



## Additional Notes

When cloning, use git clone --recursive (url to this repo) to ensure copying the submodules matte and raylib.
