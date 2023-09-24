# Raylib-Matte (raymatte)
raylib bindings for Matte with some extra goodies and an emphasis 
on reducing potential undefined behavior.


**STILL A WORK IN PROGRESS.**

*Progress: 60%*


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
          `SetTraceLogCallback` (Used by the raylib-matte implementation)
          `SetLoadFileDataCallback` (Used by the raylib-matte implementation, unavailable)
          `SetSaveFileDataCallback` (Used by the raylib-matte implementation, unavailable)
          `SetLoadTextDataCallback` (Used by the raylib-matte implementation, unavailable)
          `SetSaveTextDataCallback` (Used by the raylib-matte implementation, unavailable)
          `UnloadFileData` (Not needed. MemoryBuffer can either be freed manually or will auto-free on GC)
          `UnloadTextData` (Not needed.)
          `UnloadDirectoryFiles` (Not needed.)
          `UnloadDroppedFiles` (Not needed.)
          `UnloadImageColors` (Not needed.)
          `UnloadImagePalette` (Not needed.)
          `UnloadFontData` (Not needed.)
          `DrawTextCodepoint` (Not especially needed with Matte string access.)
          `DrawTextCodepoints` (Not especially needed with Matte strings access.)
          All `Text*`, `UTF8`, and `Codepoint` functions (Not needed. Can be handled at the Matte level with the Matte string type, functions, and querries)
          `UnloadModelAnimations` (Not needed.)
          `Vector3toFloatV` (Not needed.)
          `MatrixToFloatV` (Not needed.)
            
- Instances of output/input that call for char * (C-Strings) are replaced 
  with Matte strings.            
          
- Some structs contain members which point to managed references 
  or arrays. These members have specialized getter functions that generate 
  copies of results that can be worked with.
  
  The following functions were added to facilitate these changes:
    `ImageGetData(Image)` (returns a MemoryBuffer copy of the "data" of the image.)

    `FontGetRecs(Font)` (returns an array copy of "recs" as Rectangle objects)
    `FontGetGlyphs(Font)` (returns an array copy of "glyphs" as GlyphInfo objects)

    `MeshGetVertices(Mesh)` (returns a MemoryBuffer copy of "vertices")
    `MeshGetTexCoords(Mesh)` (returns a MemoryBuffer copy of "texcoords")
    `MeshGetTexCoords2(Mesh)` (returns a MemoryBuffer copy of "texcoords2")
    `MeshGetNormals(Mesh)` (returns a MemoryBuffer copy of "normals")
    `MeshGetTangents(Mesh)` (returns a MemoryBuffer copy of "tangents")
    `MeshGetColors(Mesh)` (returns a MemoryBuffer copy of "colors")
    `MeshGetIndices(Mesh)` (returns a MemoryBuffer copy of "vertices")
    `MeshGetAnimVertices(Mesh)` (returns a MemoryBuffer copy of "animVertices")
    `MeshGetAnimNormals(Mesh)` (returns a MemoryBuffer copy of "animNormals")
    `MeshGetBoneIDs(Mesh)` (returns a MemoryBuffer copy of "boneIds")
    `MeshGetBoneWeights(Mesh)` (returns a MemoryBuffer copy of "boneIds")

    `ModelGetMeshes(Model)` (returns an array of Mesh, a copy of "meshes")
    `ModelGetMaterials(Model)` (returns an array of Material, a copy of "materials")
    `ModelGetMaterialNumbers(Model)` (returns an array of numbers, a copy of "meshMaterial")
    `ModelGetBones(Model)` (returns an array of BoneInfo, a copy of "bones")
    `ModelGetBindPoses(Model)` (returns an array of Transform, a copy of "bindPose")
    
    `ModelAnimationGetBones(ModelAnimation)` (returns an array of BoneInfo, a copy of "bones")
    `ModelAnimationGetFramePoses(ModelAnimation)` (returns an array of array of Transforms, a deep copy "framePoses", which is indexed by frame, then by bone)
    
    
    `WaveGetData(Wave)` (returns a MemoryBuffer copy of "data")



  Such objects are NOT able to be produced "by hand" and need to be 
  sourced from raylib functions on some level. Many of these objects 
  also contain OpenGL primitives or other external primitives. The getters 
  to these are inaccessible.

- The Material struct replaces accessible "params[4]" with serially defined 
  "param0" "param1", "param2", and "param3". Similarly, "maps" is serially
  defined with "map0", "map1", etc.
  
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
  be called "bytes"
  

  
- TraceLog only takes logLevel and text, since built-in string 
  operations for Matte cover the text utilities provided.

- CompressData and DecompressData returns a MemoryBuffer and takes a MemoryBuffer ("bytes").

- DrawLineStrip, DrawTriangleFan, DrawTriangleStrip, and CheckCollisionPointPoly all take an input array of "flat values", that is, an array of 
  number values in a single array, rather than an array of xy objects.
  
  I.e.
  ```
  raylib.DrawLineStrip(
    points: [1, 2   3, 4   5, 6],
    color: raylib.GREEN
  )
  ```
  
- LoadImageAnim will return an image object with an extra public member called "frames",
  which contains the output frame count
  
- UpdateTexture and UpdateTextureRec do not take a raw buffer of pixels to 
  update the texture, instead they take an image. They behave as follows:
    UpdateTexture(
        Texture2D texture,
        Image image
    )

    UpdateTextureRec(
        Texture2D texture,
        Vector2 position, // the top-left to place the Image
        Image image
    )
- GetPixelColor and SetPixelColor use a MemoryBuffer object to 
  facilitate byte access.
  
- LoadFontEx and LoadFontData takes an array of single-character strings into "fontChars" argument,
  removing the glyphCount argument.
  
- LoadFontData takes bytes (a MemoryBuffer), fontSize, fontChars (an array of single-character strings), and type.
   
- GenImageFontAtlas has the "recs" argument removed, instead, the return value is changed: an object is returned with 2 members, 
  "image" containing the output Image, and "recs" containing an array of recs that would have been output.
  In addition, "chars" input will be an array of GlyphInfo, removing the need for glyphCount.
  
- DrawTriangleStrip3D takes an array of points and a color.
  
- DrawMeshInstanced takes 3 arguments, the last of which is an array of Matrix.
  The size of the array determines the instance count
  
- LoadMaterials returns an array of Material instances and removes the 
  materialCount argument

- Vector2Equals returns a boolean instead of an int.

- Vector3Equals returns a boolean instead of an int.

- QuaternionEquals returns a boolean instead of an int.
  
- QuaternionToAxisAngle only takes the quaternion argument and, instead, returns 
  an object containing an "axis" and "angle" member, representing the 
  output of the function
## Additional Notes

When cloning, use git clone --recursive (url to this repo) to ensure copying the submodules matte and raylib.
