/*******************************************************************************************
*
*   raylib [core] example - 2d camera
*
*   Example originally created with raylib 1.5, last time updated with raylib 3.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2016-2023 Ramon Santamaria (@raysan5)
*
********************************************************************************************/


// adapted for Matte.


@:raylib = import(module:"raylib.mt");

@:MAX_BUILDINGS = 100

// Initialization
//--------------------------------------------------------------------------------------
@:screenWidth = 800;
@:screenHeight = 450;

raylib.InitWindow(
    width:screenWidth, 
    height:screenHeight, 
    title:"raylib [core] example - 2d camera"
);

@:player = { 
    x:400,
    y:280, 
    width:40, 
    height:40 
};

@:buildings = [];
@:buildColors = [];

@spacing = 0;

for(0, MAX_BUILDINGS)::(i) {
    @:height = raylib.GetRandomValue(min:100, max:800)
    buildings[i] = {
        width : raylib.GetRandomValue(min:50, max:200),
        height : height,
        y : screenHeight - 130.0 -height,
        x : -6000.0 + spacing
    };

    spacing += buildings[i].width->floor;

    buildColors[i] = { 
        r:raylib.GetRandomValue(min:200, max:240), 
        g:raylib.GetRandomValue(min:200, max:240), 
        b:raylib.GetRandomValue(min:200, max:250), 
        a:255 
    };
}


@:camera = { 
    target : { x:player.x + 20.0, y:player.y + 20.0 },
    offset : { x:screenWidth/2.0, y:screenHeight/2.0 },
    rotation : 0.0,
    zoom : 1.0
}


raylib.SetTargetFPS(fps:60);                   // Set our game to run at 60 frames-per-second
//--------------------------------------------------------------------------------------

{:::} {
    // Main game loop
    forever::{
        when (raylib.WindowShouldClose()) send();        // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        // Player movement
        if (raylib.IsKeyDown(key:raylib.KEY_RIGHT)) player.x += 2;
        if (raylib.IsKeyDown(key:raylib.KEY_LEFT)) player.x -= 2;

        // Camera target follows player
        camera.target = { x:player.x + 20, y:player.y + 20 };

        // Camera rotation controls
        if (raylib.IsKeyDown(key:raylib.KEY_A)) camera.rotation-=1;
        if (raylib.IsKeyDown(key:raylib.KEY_S)) camera.rotation+=1;

        // Limit camera rotation to 80 degrees (-40 to 40)
        if (camera.rotation > 40) camera.rotation = 40;
        if (camera.rotation < -40) camera.rotation = -40;

        // Camera zoom controls
        camera.zoom += (raylib.GetMouseWheelMove()*0.05);

        if (camera.zoom > 3.0) camera.zoom = 3.0;
        if (camera.zoom < 0.1) camera.zoom = 0.1;

        // Camera reset (zoom and rotation)
        if (raylib.IsKeyPressed(key:raylib.KEY_R))
        ::<= {
            camera.zoom = 1.0;
            camera.rotation = 0.0;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        raylib.BeginDrawing();

            raylib.ClearBackground(color:raylib.RAYWHITE);

            raylib.BeginMode2D(camera);

                raylib.DrawRectangle(posX:-6000, posY:320, width:13000, height:8000, color:raylib.DARKGRAY);

                for (0, MAX_BUILDINGS)::(i) <-  
                    raylib.DrawRectangleRec(rec:buildings[i], color:buildColors[i]);

                raylib.DrawRectangleRec(rec:player, color:raylib.RED);

                raylib.DrawLine(    
                    startPosX:camera.target.x, 
                    startPosY:-screenHeight*10, 
                    endPosX:camera.target.x, 
                    endPosY:screenHeight*10, 
                    color: raylib.GREEN);
                    
                raylib.DrawLine(
                    startPosX:-screenWidth*10, 
                    startPosY:camera.target.y, 
                    endPosX:screenWidth*10, 
                    endPosY:camera.target.y, 
                    color:raylib.GREEN);

            raylib.EndMode2D();

            raylib.DrawText(text:"SCREEN AREA", posX:640, posY:10, fontSize:20, color:raylib.RED);

            raylib.DrawRectangle(posX:0, posY:0, width:screenWidth, height:5, color:raylib.RED);
            raylib.DrawRectangle(posX:0, posY:5, width:5, height:screenHeight - 10, color:raylib.RED);
            raylib.DrawRectangle(posX:screenWidth - 5, posY:5, width:5, height:screenHeight - 10, color:raylib.RED);
            raylib.DrawRectangle(posX:0, posY:screenHeight - 5, width:screenWidth, height:5, color:raylib.RED);

            raylib.DrawRectangle(posX:10, posY:10, width:250, height:113, color:raylib.Fade(color:raylib.SKYBLUE, alpha:0.5));
            raylib.DrawRectangleLines(posX:10, posY:10, width:250, height:113, color:raylib.BLUE);

            raylib.DrawText(text:"Free 2d camera controls:", posX:20, posY:20, fontSize:10, color:raylib.BLACK);
            raylib.DrawText(text:"- Right/Left to move Offset", posX:40, posY:40, fontSize:10, color:raylib.DARKGRAY);
            raylib.DrawText(text:"- Mouse Wheel to Zoom in-out", posX:40, posY:60, fontSize:10, color:raylib.DARKGRAY);
            raylib.DrawText(text:"- A / S to Rotate", posX:40, posY:80, fontSize:10, color:raylib.DARKGRAY);
            raylib.DrawText(text:"- R to reset Zoom and Rotation", posX:40, posY:100, fontSize:10, color:raylib.DARKGRAY);

        raylib.EndDrawing();
        //----------------------------------------------------------------------------------
    }
}

// De-Initialization
//--------------------------------------------------------------------------------------
raylib.CloseWindow();        // Close window and OpenGL context
//--------------------------------------------------------------------------------------

