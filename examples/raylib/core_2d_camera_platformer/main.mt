/*******************************************************************************************
*
*   raylib [core] example - 2d camera platformer
*
*   Example originally created with raylib 2.5, last time updated with raylib 3.0
*
*   Example contributed by arvyy (@arvyy) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2019-2023 arvyy (@arvyy)
*
********************************************************************************************/


// adapted for Matte.

@:raylib = import(module:"raylib.mt");
@:class = import(module:"Matte.Core.Class");


@:G = 400
@:PLAYER_JUMP_SPD = 350.0
@:PLAYER_HOR_SPD = 200.0


@:Player = class(
    name: "Player",
    define::(this) {
        @position = { x:400, y:280 };
        @canJump = false;
        @speed = 0;
    
        this.interface = {
            Update ::(envItems, deltaTime) {
                if (raylib.IsKeyDown(key:raylib.KEY_LEFT)) position.x -= PLAYER_HOR_SPD*deltaTime;
                if (raylib.IsKeyDown(key:raylib.KEY_RIGHT)) position.x += PLAYER_HOR_SPD*deltaTime;
                if (raylib.IsKeyDown(key:raylib.KEY_SPACE) && canJump)
                ::<={
                    speed = -PLAYER_JUMP_SPD;
                    canJump = false;
                }

                // shows off the debugger.
                // If youre currently in the debugger, welcome!
                // Try to print a variable to see it in action.
                //
                // See the project README for commands, but it follows
                // a reduced set of command from gdb.
                breakpoint();



                @hitObstacle = false;
                foreach(envItems) ::(i, ei) {   
                    if (ei.blocking &&
                        ei.rect.x <= position.x &&
                        ei.rect.x + ei.rect.width >= position.x &&
                        ei.rect.y >= position.y &&
                        ei.rect.y <= position.y + speed*deltaTime)
                    ::<={
                        hitObstacle = true;
                        speed = 0.0;
                        position.y = ei.rect.y;
                    }
                }

                if (!hitObstacle)
                ::<={
                    position.y += speed*deltaTime;
                    speed += G*deltaTime;
                    canJump = false;
                }
                else canJump = true;
            },
        
            position : {
                set ::(value) {
                    position = value;
                },
                
                get:: <- position
            },
            
            canJump : {get::<- canJump},
            speed : {get::<- speed}
        }
    }
);



// Initialization
//--------------------------------------------------------------------------------------
@:screenWidth = 800;
@:screenHeight = 450;

raylib.InitWindow(
    width:screenWidth, 
    height:screenHeight, 
    title:"raylib [core] example - 2d camera"
);

@:player = Player.new();
@:envItems = [
    {
        rect:{ x:0, y:0, width:1000, height:400 }, 
        blocking:false, 
        color:raylib.LIGHTGRAY 
    },
    {
        rect:{ x:0, y:400, width:1000, height:200 }, 
        blocking:true, 
        color:raylib.GRAY 
    },
    {
        rect:{ x:300, y:200, width:400, height:10 }, 
        blocking:true, 
        color:raylib.GRAY 
    },
    {   
        rect:{ x:250, y:300, width:100, height:10 }, 
        blocking:true, 
        color:raylib.GRAY 
    },
    {
        rect:{ x:650, y:300, width:100, height:10 }, 
        blocking:true, 
        color:raylib.GRAY 
    }
];


@:camera = {
    target : player.position,
    offset : { x:screenWidth/2.0, y:screenHeight/2.0 },
    rotation : 0.0,
    zoom : 1.0
}





@:minf::(a, b) <- if (a < b) a else b;
@:maxf::(a, b) <- if (a > b) a else b;


@:UpdateCameraCenter::(camera, player, envItems, deltaTime)
{
    camera.offset = { x:screenWidth/2.0, y:screenHeight/2.0 };
    camera.target = {
        x:player.position.x,
        y:player.position.y
    };
}

@:UpdateCameraCenterInsideMap::(camera, player, envItems, deltaTime)
{
    camera.target = {
        x:player.position.x,
        y:player.position.y
    };
    camera.offset = { x:screenWidth/2.0, y:screenHeight/2.0 };
    @minX = 1000;
    @minY = 1000; 
    @maxX = -1000; 
    @maxY = -1000;


    foreach(envItems)::(i, ei) 
    {
        minX = minf(a:ei.rect.x, b:minX);
        maxX = maxf(a:ei.rect.x + ei.rect.width, b:maxX);
        minY = minf(a:ei.rect.y, b:minY);
        maxY = maxf(a:ei.rect.y + ei.rect.height, b:maxY);
    }

    @max = raylib.GetWorldToScreen2D(position:{ x:maxX, y:maxY }, camera);
    @min = raylib.GetWorldToScreen2D(position:{ x:minX, y:minY }, camera);

    if (max.x < screenWidth) camera.offset.x = screenWidth - (max.x - screenWidth/2);
    if (max.y < screenHeight) camera.offset.y = screenHeight - (max.y - screenHeight/2);
    if (min.x > 0) camera.offset.x = screenWidth/2 - min.x;
    if (min.y > 0) camera.offset.y = screenHeight/2 - min.y;
}

@:UpdateCameraCenterSmoothFollow = ::<= {
    @minSpeed = 30;
    @minEffectLength = 10;
    @fractionSpeed = 0.8;
   
    return ::(camera, player, envItems, deltaTime) {
        @width = screenWidth;
        @height = screenHeight;

        camera.offset = { x:width/2.0, y:height/2.0 };
        @diff = raylib.Vector2Subtract(v1:player.position, v2:camera.target);
        @length = raylib.Vector2Length(v:diff);


        if (length > minEffectLength)
        ::<={
            @speed = maxf(a:fractionSpeed*length, b:minSpeed);
            camera.target = raylib.Vector2Add(v1:camera.target, v2:raylib.Vector2Scale(v:diff, scale:speed*deltaTime/length));
        }
    }
}

@:UpdateCameraEvenOutOnLanding = ::<= {
    @evenOutSpeed = 700;
    @eveningOut = false;
    @evenOutTarget;

    return ::(camera, player, envItems, deltaTime) {

        @width = screenWidth;
        @height = screenHeight;

        camera.offset = { x:width/2.0, y:height/2.0 };
        camera.target.x = player.position.x;

        if (eveningOut)
        ::<={
            if (evenOutTarget > camera.target.y)
            ::<={
                camera.target.y += evenOutSpeed*deltaTime;

                if (camera.target.y > evenOutTarget)
                ::<={
                    camera.target.y = evenOutTarget;
                    eveningOut = 0;
                }
            }
            else
            ::<={
                camera.target.y -= evenOutSpeed*deltaTime;

                if (camera.target.y < evenOutTarget)
                ::<={
                    camera.target.y = evenOutTarget;
                    eveningOut = 0;
                }
            }
        }
        else
        ::<={
            if (player.canJump && (player.speed == 0) && (player.position.y != camera.target.y))
            ::<={
                eveningOut = 1;
                evenOutTarget = player.position.y;
            }
        }
    }
}

@:UpdateCameraPlayerBoundsPush = ::<= {
    @:bbox = { x:0.2f, y:0.2f };


    return ::(camera, player, envItems, deltaTime) {
        @:width = screenWidth;
        @:height = screenHeight;
    
        @bboxWorldMin = raylib.GetScreenToWorld2D(position:{x:(1 - bbox.x)*0.5*width, y:(1 - bbox.y)*0.5*height }, camera);
        @bboxWorldMax = raylib.GetScreenToWorld2D(position:{x:(1 + bbox.x)*0.5*width, y:(1 + bbox.y)*0.5*height }, camera);
        camera.offset = { x:(1 - bbox.x)*0.5 * width, y:(1 - bbox.y)*0.5*height };

        if (player.position.x < bboxWorldMin.x) camera.target.x = player.position.x;
        if (player.position.y < bboxWorldMin.y) camera.target.y = player.position.y;
        if (player.position.x > bboxWorldMax.x) camera.target.x = bboxWorldMin.x + (player.position.x - bboxWorldMax.x);
        if (player.position.y > bboxWorldMax.y) camera.target.y = bboxWorldMin.y + (player.position.y - bboxWorldMax.y);
    }
}


// Store pointers to the multiple update camera functions
@cameraUpdaters = [
    UpdateCameraCenter,
    UpdateCameraCenterInsideMap,
    UpdateCameraCenterSmoothFollow,
    UpdateCameraEvenOutOnLanding,
    UpdateCameraPlayerBoundsPush
];

@cameraOption = 0;

@:cameraDescriptions = [
    "Follow player center",
    "Follow player center, but clamp to map edges",
    "Follow player center; smoothed",
    "Follow player center horizontally; update player center vertically after landing",
    "Player push camera on getting too close to screen edge"
];

raylib.SetTargetFPS(fps:60);

{:::} {
    //--------------------------------------------------------------------------------------

    // Main game loop
    forever::{
        if (raylib.WindowShouldClose()) ::<= {
            send();
        }
        // Update
        //----------------------------------------------------------------------------------
        @:deltaTime = raylib.GetFrameTime();

        player.Update(envItems, deltaTime);

        camera.zoom += (raylib.GetMouseWheelMove()*0.05);

        if (camera.zoom > 3.0)  camera.zoom = 3.0;
        if (camera.zoom < 0.25) camera.zoom = 0.25;

        if (raylib.IsKeyPressed(key:raylib.KEY_R))
        ::<={
            camera.zoom = 1.0;
            player.position = { x:400, y:280 };
        };

        if (raylib.IsKeyPressed(key:raylib.KEY_C)) 
            cameraOption = (cameraOption + 1)%cameraUpdaters->size;

        // Call update camera function by its pointer
        cameraUpdaters[cameraOption](
            camera, 
            player, 
            envItems,
            deltaTime
        );
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        raylib.BeginDrawing();

            raylib.ClearBackground(color:raylib.LIGHTGRAY);

            raylib.BeginMode2D(camera);

                foreach(envItems) ::(i, ei) {
                     raylib.DrawRectangleRec(rec:ei.rect, color:ei.color);
                }
                
                @:playerRect = { x:player.position.x - 20, y:player.position.y - 40, width:40, height:40 };
                raylib.DrawRectangleRec(rec:playerRect, color:raylib.RED);

            raylib.EndMode2D();

            raylib.DrawText(text:"Controls:", posX:20, posY:20, fontSize:10, color:raylib.BLACK);
            raylib.DrawText(text:"- Right/Left to move", posX:40, posY:40, fontSize:10, color:raylib.DARKGRAY);
            raylib.DrawText(text:"- Space to jump", posX:40, posY:60, fontSize:10, color:raylib.DARKGRAY);
            raylib.DrawText(text:"- Mouse Wheel to Zoom in-out, R to reset zoom", posX:40, posY:80, fontSize:10, color:raylib.DARKGRAY);
            raylib.DrawText(text:"- C to change camera mode", posX:40, posY:100, fontSize:10, color:raylib.DARKGRAY);
            raylib.DrawText(text:"Current camera mode:", posX:20, posY:120, fontSize:10, color:raylib.BLACK);
            raylib.DrawText(text:cameraDescriptions[cameraOption], posX:40, posY:140, fontSize:10, color:raylib.DARKGRAY);

        raylib.EndDrawing();
        //----------------------------------------------------------------------------------
    }


}

// De-Initialization
//--------------------------------------------------------------------------------------
raylib.CloseWindow();        // Close window and OpenGL context
//--------------------------------------------------------------------------------------


