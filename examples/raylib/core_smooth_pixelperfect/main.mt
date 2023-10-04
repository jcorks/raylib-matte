/*******************************************************************************************
*
*   raylib [core] example - smooth pixel-perfect camera
*
*   Example originally created with raylib 3.7, last time updated with raylib 4.0
*   
*   Example contributed by Giancamillo Alessandroni (@NotManyIdeasDev) and
*   reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2021-2023 Giancamillo Alessandroni (@NotManyIdeasDev) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

// Adapted for Matte.


@:ray = import(module:"raylib.mt");

// Initialization
//--------------------------------------------------------------------------------------
@:screenWidth = 800;
@:screenHeight = 450;

@:virtualScreenWidth = 160;
@:virtualScreenHeight = 90;

@:virtualRatio = screenWidth/virtualScreenWidth;

ray.InitWindow(
    width:screenWidth, 
    height:screenHeight, 
    title:"raylib [core] example - smooth pixel-perfect camera"
);

// camera2d
@:worldSpaceCamera = { 
    target : {x:0, y:0},
    offset : {x:0, y:0},
    zoom : 1.0,
    rotation: 0
};  

// Game world camera

@:screenSpaceCamera = { 
    target : {x:0, y:0},
    offset : {x:0, y:0},
    zoom : 1.0,
    rotation: 0
}; // Smoothing camera



@:target = ray.LoadRenderTexture(
    width:virtualScreenWidth, 
    height:virtualScreenHeight
); // This is where we'll draw all our objects.

@rec01 = { x:70.0, y:35.0, width:20.0, height:20.0 };
@rec02 = { x:90.0, y:55.0, width:30.0, height:10.0 };
@rec03 = { x:80.0, y:65.0, width:15.0, height:25.0 };

// The target's height is flipped (in the source Rectangle), due to OpenGL reasons
@:sourceRec = { x:0.0, y:0.0, width:target.texture.width, height:-target.texture.height };
@:destRec = { x:-virtualRatio, y:-virtualRatio, width:screenWidth + (virtualRatio*2), height:screenHeight + (virtualRatio*2) };

@origin = { x:0.0, y:0.0 };

@rotation = 0.0;

@cameraX = 0.0;
@cameraY = 0.0;

ray.SetTargetFPS(fps:60);
    //--------------------------------------------------------------------------------------
{:::} {
    forever::{
    // Main game loop
        when(ray.WindowShouldClose()) send();   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        rotation += 60.0*ray.GetFrameTime();   // Rotate the rectangles, 60 degrees per second

        // Make the camera move to demonstrate the effect
        cameraX = ((ray.GetTime()->sin)*50.0) - 10.0;
        cameraY = (ray.GetTime()->cos)*30.0;

        // Set the camera's target to the values computed above
        screenSpaceCamera.target = { x:cameraX, y:cameraY };

        // Round worldSpace coordinates, keep decimals into screenSpace coordinates
        worldSpaceCamera.target.x = screenSpaceCamera.target.x->floor;
        screenSpaceCamera.target.x -= worldSpaceCamera.target.x;
        screenSpaceCamera.target.x *= virtualRatio;

        worldSpaceCamera.target.y = screenSpaceCamera.target.y->floor;
        screenSpaceCamera.target.y -= worldSpaceCamera.target.y;
        screenSpaceCamera.target.y *= virtualRatio;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        ray.BeginTextureMode(target);
            ray.ClearBackground(color:ray.RAYWHITE);

            ray.BeginMode2D(camera:worldSpaceCamera);
                ray.DrawRectanglePro(rec:rec01, origin, rotation, color:ray.BLACK);
                ray.DrawRectanglePro(rec:rec02, origin, rotation:-rotation, color:ray.RED);
                ray.DrawRectanglePro(rec:rec03, origin, rotation:rotation + 45.0, color:ray.BLUE);
            ray.EndMode2D();
        ray.EndTextureMode();

        ray.BeginDrawing();
            ray.ClearBackground(color:ray.RED);

            ray.BeginMode2D(camera:screenSpaceCamera);
                ray.DrawTexturePro(texture:target.texture, source:sourceRec, dest:destRec, origin, rotation:0.0, tint:ray.WHITE);
            ray.EndMode2D();

            ray.DrawText(text:"Screen resolution: %0x%1"->format(items:[screenWidth, screenHeight]), posX:10, posY:10, fontSize:20, color:ray.DARKBLUE);
            ray.DrawText(text:"World resolution: %0x%1"->format(items:[virtualScreenWidth, virtualScreenHeight]), posX:10, posY:40, fontSize:20, color:ray.DARKGREEN);
            ray.DrawFPS(posX:ray.GetScreenWidth() - 95, posY:10);
        ray.EndDrawing();
        //----------------------------------------------------------------------------------
    }
}


// De-Initialization
//--------------------------------------------------------------------------------------
ray.UnloadRenderTexture(target);    // Unload render texture

ray.CloseWindow();                  // Close window and OpenGL context
//--------------------------------------------------------------------------------------

