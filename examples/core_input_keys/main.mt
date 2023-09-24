/*******************************************************************************************
*
*   raylib [core] example - Keyboard input
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2014-2023 Ramon Santamaria (@raysan5)
*
********************************************************************************************/


// Adapted for Matte

@:raylib = import(module:"raylib.mt");

@:screenWidth = 800;
@:screenHeight = 450;

raylib.InitWindow(
    width:screenWidth, 
    height:screenHeight, 
    title:"raylib [core] example - keyboard input"
);

@:ballPosition = {
    x:screenWidth/2, 
    y:screenHeight/2 
};

raylib.SetTargetFPS(fps:60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
{:::} {
    forever ::{
        when (raylib.WindowShouldClose())    // Detect window close button or ESC key
            send();
        // Update
        //----------------------------------------------------------------------------------
        if (raylib.IsKeyDown(key:raylib.KEY_RIGHT)) ballPosition.x += 2.0;
        if (raylib.IsKeyDown(key:raylib.KEY_LEFT)) ballPosition.x -= 2.0;
        if (raylib.IsKeyDown(key:raylib.KEY_UP)) ballPosition.y -= 2.0;
        if (raylib.IsKeyDown(key:raylib.KEY_DOWN)) ballPosition.y += 2.0;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        raylib.BeginDrawing();
            breakpoint();
            raylib.ClearBackground(color:raylib.RAYWHITE);

            raylib.DrawText(
                text:"move the ball with arrow keys", 
                posX:10, 
                posY:10, 
                fontSize:20, 
                color:raylib.DARKGRAY
            );

            raylib.DrawCircleV(center:ballPosition, radius:50, color:raylib.MAROON);

        raylib.EndDrawing();
        //----------------------------------------------------------------------------------
    }
}


// De-Initialization
//--------------------------------------------------------------------------------------
raylib.CloseWindow();        // Close window and OpenGL context

