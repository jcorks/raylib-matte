/*******************************************************************************************
*
*   raylib [shapes] example - Draw raylib logo using basic shapes
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2014-2023 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

@:raylib = import(module:"raylib.mt");

// Initialization
//--------------------------------------------------------------------------------------
@:screenWidth = 256;
@:screenHeight = 256;

raylib.InitWindow(
    width:screenWidth, 
    height:screenHeight, 
    title:"raylib [shapes] example - raylib logo using shapes"
);

@:MATTE_BLUE = {
    r:72, 
    g:138, 
    b:224, 
    a:255
};

raylib.SetTargetFPS(fps:60);               // Set our game to run at 60 frames-per-second
//--------------------------------------------------------------------------------------

// Main game loop
{:::} {
    forever::{
        when(raylib.WindowShouldClose()) send()    // Detect window close button or ESC key

        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        raylib.BeginDrawing();

            raylib.ClearBackground(color:raylib.RAYWHITE);

            raylib.DrawRectangle(posX:screenWidth/2 - 128, posY:screenHeight/2 - 128, width:256, height:256, color:MATTE_BLUE);
            raylib.DrawRectangle(posX:screenWidth/2 - 112, posY:screenHeight/2 - 112, width:224, height:224, color:raylib.RAYWHITE);
            raylib.DrawText(text:"raylib", posX:screenWidth/2 - 44, posY:screenHeight/2 + 8, fontSize:50, color:MATTE_BLUE);
            raylib.DrawText(text:"mt",     posX:screenWidth/2 - 44, posY:screenHeight/2 + 48, fontSize:50, color:MATTE_BLUE);


        raylib.EndDrawing();
        //----------------------------------------------------------------------------------

        raylib.TakeScreenshot(fileName:"logo.png");
        send();
    }

}


// De-Initialization
//--------------------------------------------------------------------------------------
raylib.CloseWindow();        // Close window and OpenGL context
//--------------------------------------------------------------------------------------

