/*******************************************************************************************
*
*   raylib [core] example - 3d camera first person
*
*   Example originally created with raylib 1.3, last time updated with raylib 1.3
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2015-2023 Ramon Santamaria (@raysan5)
*
********************************************************************************************/


// Adapted for Matte.

@:ray = import(module:'raylib.mt');

@:MAX_COLUMNS = 20

// Initialization
//--------------------------------------------------------------------------------------
@:screenWidth = 800;
@:screenHeight = 450;

ray.InitWindow(
    width:screenWidth, 
    height:screenHeight, 
    title:"raylib [core] example - 3d camera first person"
);

// Define the camera to look into our 3d world (position, target, up vector)
@:camera = { 
    position : { x:0.0, y:2.0, z:4.0 },    // Camera position
    target : { x:0.0, y:2.0, z:0.0 },      // Camera looking at point
    up : { x:0.0, y:1.0, z:0.0 },          // Camera up vector (rotation towards target)
    fovy : 60.0,                           // Camera field-of-view Y
    projection : ray.CAMERA_PERSPECTIVE    // Camera projection type
};

@cameraMode = ray.CAMERA_FIRST_PERSON;

// Generates some random columns
@heights = [];
@positions = [];
@colors = [];

for (0, MAX_COLUMNS) ::(i)
{
    heights[i] = ray.GetRandomValue(min:1, max:12);
    positions[i] = { 
        x:ray.GetRandomValue(min:-15, max:15), 
        y:heights[i]/2.0, 
        z:ray.GetRandomValue(min:-15, max:15) 
    };
    colors[i] = { 
        r:ray.GetRandomValue(min:20, max:255), 
        g:ray.GetRandomValue(min:10, max:55), 
        b:30, 
        a:255 
    };
}

ray.DisableCursor();                    // Limit cursor to relative movement inside the window

ray.SetTargetFPS(fps:60);               // Set our game to run at 60 frames-per-second
//--------------------------------------------------------------------------------------


@:to3Decimals ::(vec) <-
    "" +((vec.x * 1000)->floor / 1000) + ',' 
       +((vec.y * 1000)->floor / 1000) + ',' 
       +((vec.z * 1000)->floor / 1000) + ',';


{:::} {
    // Main game loop
    forever::{
        when(ray.WindowShouldClose()) send();       // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        // Switch camera mode
        if (ray.IsKeyPressed(key:ray.KEY_ONE))
        ::<={
            cameraMode = ray.CAMERA_FREE;
            camera.up = { x:0.0, y:1.0, z:0.0 }; // Reset roll
        }

        if (ray.IsKeyPressed(key:ray.KEY_TWO))
        ::<={
            cameraMode = ray.CAMERA_FIRST_PERSON;
            camera.up = { x:0.0, y:1.0, z:0.0 }; // Reset roll
        }

        if (ray.IsKeyPressed(key:ray.KEY_THREE))
        ::<={
            cameraMode = ray.CAMERA_THIRD_PERSON;
            camera.up = { x:0.0, y:1.0, z:0.0 }; // Reset roll
        }

        if (ray.IsKeyPressed(key:ray.KEY_FOUR))
        ::<={
            cameraMode = ray.CAMERA_ORBITAL;
            camera.up = { x:0.0, y:1.0, z:0.0 }; // Reset roll
        }

        // Switch camera projection
        if (ray.IsKeyPressed(key:ray.KEY_P))
        ::<={
            if (camera.projection == ray.CAMERA_PERSPECTIVE)
            ::<={
                // Create isometric view
                cameraMode = ray.CAMERA_THIRD_PERSON;
                // Note: The target distance is related to the render distance in the orthographic projection
                camera.position = { x:0.0, y:2.0, z:-100.0 };
                camera.target = { x:0.0, y:2.0, z:0.0 };
                camera.up = { x:0.0, y:1.0, z:0.0 };
                camera.projection = ray.CAMERA_ORTHOGRAPHIC;
                camera.fovy = 20.0; // near plane width in CAMERA_ORTHOGRAPHIC
                ray.CameraYaw(camera, angle:-135->asRadians, rotateAroundTarget:true);
                ray.CameraPitch(camera, angle:-45->asRadians, loackView:true, rotateAroundTarget:true, rotateUp:false);
            }
            if (camera.projection == ray.CAMERA_ORTHOGRAPHIC)
            ::<={
                // Reset to default view
                cameraMode = ray.CAMERA_THIRD_PERSON;
                camera.position = { x:0.0, y:2.0, z:10.0 };
                camera.target = { x:0.0, y:2.0, z:0.0 };
                camera.up = { x:0.0, y:1.0, z:0.0 };
                camera.projection = ray.CAMERA_PERSPECTIVE;
                camera.fovy = 60.0;
            }
        }

        // Update camera computes movement internally depending on the camera mode
        // Some default standard keyboard/mouse inputs are hardcoded to simplify use
        // For advance camera controls, it's reecommended to compute camera movement manually
        ray.UpdateCamera(camera, mode:cameraMode);                  // Update camera

    /*
        // Camera PRO usage example (EXPERIMENTAL)
        // This new camera function allows custom movement/rotation values to be directly provided
        // as input parameters, with this approach, rcamera module is internally independent of raylib inputs
        UpdateCameraPro(&camera,
            (Vector3){
                (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))*0.1f -      // Move forward-backward
                (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))*0.1f,    
                (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))*0.1f -   // Move right-left
                (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))*0.1f,
                0.0                                                // Move up-down
            },
            (Vector3){
                GetMouseDelta().x*0.05f,                            // Rotation: yaw
                GetMouseDelta().y*0.05f,                            // Rotation: pitch
                0.0                                                // Rotation: roll
            },
            GetMouseWheelMove()*2.0);                              // Move to target (zoom)
    */
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        ray.BeginDrawing();

            ray.ClearBackground(color:ray.RAYWHITE);

            ray.BeginMode3D(camera);

                ray.DrawPlane(centerPos:{ x:0.0, y:0.0, z:0.0 }, size:{ x:32.0, y:32.0 }, color:ray.LIGHTGRAY); // Draw ground
                ray.DrawCube(position:{ x:-16.0, y:2.5, z:0.0 }, width:1.0, height:5.0, length:32.0, color:ray.BLUE);     // Draw a blue wall
                ray.DrawCube(position:{ x:16.0, y:2.5, z:0.0 }, width:1.0, height:5.0, length:32.0, color:ray.LIME);      // Draw a green wall
                ray.DrawCube(position:{ x:0.0, y:2.5, z:16.0 }, width:32.0, height:5.0, length:1.0, color:ray.GOLD);      // Draw a yellow wall

                // Draw some cubes around
                for (0, MAX_COLUMNS)::(i) 
                {
                    ray.DrawCube(position:positions[i], width:2.0, height:heights[i], length:2.0, color:colors[i]);
                    ray.DrawCubeWires(position:positions[i], width:2.0, height:heights[i], length:2.0, color:ray.MAROON);
                }

                // Draw player cube
                if (cameraMode == ray.CAMERA_THIRD_PERSON)
                ::<={
                    ray.DrawCube(position:camera.target, width:0.5, height:0.5, length:0.5, color:ray.PURPLE);
                    ray.DrawCubeWires(position:camera.target, width:0.5, height:0.5, length:0.5, color:ray.DARKPURPLE);
                }

            ray.EndMode3D();

            // Draw info boxes
            ray.DrawRectangle(posX:5, posY:5, width:330, height:100, color:ray.Fade(color:ray.SKYBLUE, alpha:0.5));
            ray.DrawRectangleLines(posX:5, posY:5, width:330, height:100, color:ray.BLUE);

            ray.DrawText(text:"Camera controls:", posX:15, posY:15, fontSize:10, color:ray.BLACK);
            ray.DrawText(text:"- Move keys: W, A, S, D, Space, Left-Ctrl", posX:15, posY:30, fontSize:10, color:ray.BLACK);
            ray.DrawText(text:"- Look around: arrow keys or mouse", posX:15, posY:45, fontSize:10, color:ray.BLACK);
            ray.DrawText(text:"- Camera mode keys: 1, 2, 3, 4", posX:15, posY:60, fontSize:10, color:ray.BLACK);
            ray.DrawText(text:"- Zoom keys: num-plus, num-minus or mouse scroll", posX:15, posY:75, fontSize:10,color:ray.BLACK);
            ray.DrawText(text:"- Camera projection key: P", posX:15, posY:90, fontSize:10, color:ray.BLACK);

            ray.DrawRectangle(posX:600, posY:5, width:195, height:100, color:ray.Fade(color:ray.SKYBLUE, alpha:0.5));
            ray.DrawRectangleLines(posX:600, posY:5, width:195, height:100, color:ray.BLUE);

            ray.DrawText(text:"Camera status:", posX:610, posY:15, fontSize:10, color:ray.BLACK);
            ray.DrawText(   
                text : "- Mode: " + match(cameraMode) {
                  (ray.CAMERA_FREE):         "FREE",
                  (ray.CAMERA_FIRST_PERSON): "FIRST_PERSON",
                  (ray.CAMERA_THIRD_PERSON): "THIRD_PERSON",
                  (ray.CAMERA_ORBITAL) :     "ORBITAL",
                  default: "CUSTOM"
                }, posX:610, posY:30, fontSize:10, color:ray.BLACK);
            ray.DrawText(
                text:"- Projection: " + match(camera.projection) {
                    (ray.CAMERA_PERSPECTIVE):  "PERSPECTIVE",
                    (ray.CAMERA_ORTHOGRAPHIC): "ORTHOGRAPHIC",
                    default: "CUSTOM"
                }, posX:610, posY:45, fontSize:10, color:ray.BLACK);
                
                
            ray.DrawText(text:"- Position: " + to3Decimals(vec:camera.position), posX:610, posY:60, fontSize:10, color:ray.BLACK);
            ray.DrawText(text:"- Target: " + to3Decimals(vec:camera.target), posX:610, posY:75, fontSize:10, color:ray.BLACK);
            ray.DrawText(text:"- Up: " + to3Decimals(vec:camera.up), posX:610, posY:90, fontSize:10, color:ray.BLACK);

        ray.EndDrawing();
        //----------------------------------------------------------------------------------
    }
}
// De-Initialization
//--------------------------------------------------------------------------------------
ray.CloseWindow();        // Close window and OpenGL context
//--------------------------------------------------------------------------------------


