/*******************************************************************************************
*
*   raylib [shapes] example - top down lights
*
*   Example originally created with raylib 4.2, last time updated with raylib 4.2
*
*   Example contributed by Vlad Adrian (@demizdor) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2022-2023 Jeffery Myers (@JeffM2501)
*
********************************************************************************************/



// Adapted for Matte.
//
// NOTE, this example included rlgl calls, which are not 
// bound

@:ray = import(module:'raylib.mt');


@:MAX_BOXES     = 20;
@:MAX_SHADOWS   = MAX_BOXES*3;         // MAX_BOXES *3. Each box can cast up to two shadow volumes for the edges it is away from, and one for the box itself
@:MAX_LIGHTS    = 16;


@:makeShadowGeometry ::<- 
    {
        vertices : [
            0, 0,
            0, 0,
            0, 0,
            0, 0
        ]    
    }



@:makeLightInfo ::<- 
    {
        active: false,          // Is this light slot active?
        dirty:  false,          // Does this light need to be updated?
        valid:  false,          // Is this light in a valid position?
        position : {x:0, y:0},  // Light position
        mask : empty,           // Alpha mask for the light 
        outerRadius : 0,        // The distance the light touches
        bounds : {              // A cached rectangle of the light bounds to help with culling
            x: 0,
            y: 0,
            width: 0,
            height : 0
        },
        shadows : [],
        shadowCount : 0
    }
    
    
    



@:lights = [];
for(0, MAX_LIGHTS) ::(i) {
    lights[i] = makeLightInfo();
    for(0, MAX_SHADOWS) ::(n){
        lights[i].shadows[n] = makeShadowGeometry();
    }
}


// Move a light and mark it as dirty so that we update it's mask next frame
@:MoveLight::(slot, x, y)
{
    lights[slot].dirty = true;
    lights[slot].position.x = x; 
    lights[slot].position.y = y;

    // update the cached bounds
    lights[slot].bounds.x = x - lights[slot].outerRadius;
    lights[slot].bounds.y = y - lights[slot].outerRadius;
}

// Compute a shadow volume for the edge
// It takes the edge and projects it back by the light radius and turns it into a quad
@:ComputeShadowVolumeForEdge::(slot, sp, ep)
{
    when (lights[slot].shadowCount >= MAX_SHADOWS) empty;
    // Draw the shadows to the alpha mask

    @extension = lights[slot].outerRadius*2;

    @spVector = ray.Vector2Normalize(
        v:ray.Vector2Subtract(v1:sp, v2:lights[slot].position)
    );
    @spProjection = ray.Vector2Add(
        v1:sp, 
        v2:ray.Vector2Scale(
            v:spVector, 
            scale:extension
        )
    );

    @epVector = ray.Vector2Normalize(
        v:ray.Vector2Subtract(v1:ep, v2:lights[slot].position)
    );
    @epProjection = ray.Vector2Add(
        v1:ep, 
        v2:ray.Vector2Scale(
            v:epVector, 
            scale:extension
        )
    );

    lights[slot].shadows[lights[slot].shadowCount].vertices = [
        sp.x, sp.y,
        ep.x, ep.y,
        epProjection.x, epProjection.y,
        spProjection.x, spProjection.y
    ];
    
    lights[slot].shadowCount += 1;
}

@:lightColor = {
    r:30,
    g:30,
    b:30,
    a:255,
};

// Draw the light and shadows to the mask for a light
@:DrawLightMask::(slot)
{
    
    // Use the light mask
    ray.BeginTextureMode(target:lights[slot].mask);
        ray.ClearBackground(color:{r:0, g:0, b:0, a:0});
        ray.BeginBlendMode(mode:ray.BLEND_ALPHA);        
        // If we are valid, then draw the light radius to the alpha mask
            if (lights[slot].valid) ray.DrawCircleGradient(
                centerX:lights[slot].position.x, 
                centerY:lights[slot].position.y, 
                radius:lights[slot].outerRadius, 
                color1:lightColor, color2:ray.ColorAlpha(color:lightColor, alpha:0)
            );
        ray.EndBlendMode();
    ray.EndTextureMode();
        
    ray.BeginTextureMode(target:lights[slot].mask);
        ray.BeginBlendMode(mode:ray.BLEND_ALPHA);        
            for (0, lights[slot].shadowCount) ::(i) {
                //breakpoint();
                ray.DrawTriangleFan(
                    points:lights[slot].shadows[i].vertices, color:ray.BLACK);
            }
        ray.EndBlendMode();
    ray.EndTextureMode();

}

// Setup a light
@:SetupLight::(slot, x, y, radius)
{
    lights[slot].active = true;
    lights[slot].valid = false;  // The light must prove it is valid
    lights[slot].mask = ray.LoadRenderTexture(
        width:ray.GetScreenWidth(), 
        height:ray.GetScreenHeight()
    );
    lights[slot].outerRadius = radius;

    lights[slot].bounds.width = radius * 2;
    lights[slot].bounds.height = radius * 2;

    MoveLight(slot, x, y);

    // Force the render texture to have something in it
    DrawLightMask(slot);
}

// See if a light needs to update it's mask
@:UpdateLight::(slot, boxes)
{
    @count = boxes->size;
    
    when (!lights[slot].active || !lights[slot].dirty) false;

    lights[slot].dirty = false;
    lights[slot].shadowCount = 0;
    lights[slot].valid = false;

    @continue = {:::} {
        for (0, count)::(i)
        {
            // Are we in a box? if so we are not valid
            when (ray.CheckCollisionPointRec(point:lights[slot].position, rec:boxes[i])) send(message:false); // hmm

            // If this box is outside our bounds, we can skip it
            when (!ray.CheckCollisionRecs(rec1:lights[slot].bounds, rec2:boxes[i])) empty;

            // Check the edges that are on the same side we are, and cast shadow volumes out from them
            
            // Top
            @sp = { x:boxes[i].x, y:boxes[i].y };
            @ep = { x:boxes[i].x + boxes[i].width, y:boxes[i].y };

            if (lights[slot].position.y > ep.y) ComputeShadowVolumeForEdge(slot, sp, ep);

            // Right
            
            sp = {...ep};
            ep.y += boxes[i].height;
            if (lights[slot].position.x < ep.x) ComputeShadowVolumeForEdge(slot, sp, ep);

            // Bottom
            sp = {...ep};
            ep.x -= boxes[i].width;
            if (lights[slot].position.y < ep.y) ComputeShadowVolumeForEdge(slot, sp, ep);

            // Left
            sp = {...ep};
            ep.y -= boxes[i].height;
            if (lights[slot].position.x > ep.x) ComputeShadowVolumeForEdge(slot, sp, ep);
            
            // The box itself
            lights[slot].shadows[lights[slot].shadowCount].vertices = [
                boxes[i].x, boxes[i].y,
                boxes[i].x, boxes[i].y + boxes[i].height,
                boxes[i].x + boxes[i].width, boxes[i].y + boxes[i].height,
                boxes[i].x + boxes[i].width, boxes[i].y 
            ];
            lights[slot].shadowCount += 1;
                   
        }
        return true;
    }
    
    when(!continue) false;

    lights[slot].valid = true;
    DrawLightMask(slot);

    return true;
}

// Set up some boxes
@:SetupBoxes::(boxes)
{
    boxes[0] = { x:150,  y:80,  width:40, height:40 };
    boxes[1] = { x:1200, y:700, width:40, height:40 };
    boxes[2] = { x:200,  y:600, width:40, height:40 };
    boxes[3] = { x:1000, y:50,  width:40, height:40 };
    boxes[4] = { x:500,  y:350, width:40, height:40 };

    for (5, MAX_BOXES) ::(i) 
    {
        boxes[i] = {
            x:ray.GetRandomValue(min:0,max:ray.GetScreenWidth()), 
            y:ray.GetRandomValue(min:0,max:ray.GetScreenHeight()), 
            width:ray.GetRandomValue(min:10,max:100), 
            height:ray.GetRandomValue(min:10,max:100) 
        }
    }

}




// Initialization
//--------------------------------------------------------------------------------------
@:screenWidth = 800;
@:screenHeight = 450;

ray.InitWindow(
    width:screenWidth, 
    height:screenHeight, 
    title:"raylib [shapes] example - top down lights");

// Initialize our 'world' of boxes
@:boxes = [];
SetupBoxes(boxes);

// Create a checkerboard ground texture
@img = ray.GenImageChecked(
    width:64, 
    height:64, 
    checksX:32, 
    checksY:32, 
    col1:ray.DARKBROWN, 
    col2:ray.DARKGRAY
);
@:backgroundTexture = ray.LoadTextureFromImage(image:img);
ray.UnloadImage(image:img);

// Create a global light mask to hold all the blended lights
@:lightMask = ray.LoadRenderTexture(
    width:ray.GetScreenWidth(), 
    height:ray.GetScreenHeight()
);

// Setup initial light
SetupLight(
    slot:0, 
    x:600, 
    y:400, 
    radius:300);

@nextLight = 1;

@showLines = false;

ray.SetTargetFPS(fps:60);               // Set our game to run at 60 frames-per-second
//--------------------------------------------------------------------------------------

{:::} {
    // Main game loop
    forever :: {
        when (ray.WindowShouldClose()) send();    // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        // Drag light 0
        if (ray.IsMouseButtonDown(button:ray.MOUSE_BUTTON_LEFT)) 
            MoveLight(slot:0, x:ray.GetMousePosition().x, y:ray.GetMousePosition().y);

        // Make a new light
        if (ray.IsMouseButtonPressed(button:ray.MOUSE_BUTTON_RIGHT) && 
            (nextLight < MAX_LIGHTS))
        ::<={
            // multiple lights requires blending that we do not have.
            /*
            SetupLight(
                slot:nextLight, 
                x:ray.GetMousePosition().x, 
                y:ray.GetMousePosition().y, 
                radius:200
            );
            nextLight+=1;
            */
        }

        // Toggle debug info
        if (ray.IsKeyPressed(key:ray.KEY_F1)) showLines = !showLines;

        // Update the lights and keep track if any were dirty so we know if we need to update the master light mask
        @dirtyLights = false;
        for (0, MAX_LIGHTS) ::(i)
        {
            if (UpdateLight(slot:i, boxes)) dirtyLights = true;
        }

        // Update the light mask
        if (dirtyLights)
        ::<={
            // Build up the light mask
            ray.BeginTextureMode(target:lightMask);
            
                ray.ClearBackground(color:ray.BLACK);

                ray.BeginBlendMode(mode:ray.BLEND_ALPHA);


                    // Merge in all the light masks
                    for (0, MAX_LIGHTS)::(i) 
                    {
                        if (lights[i].active) 
                            ray.DrawTextureRec(
                                texture:lights[i].mask.texture, 
                                source:{ 
                                    x:0, 
                                    y:0, 
                                    width:ray.GetScreenWidth(), 
                                    height:-ray.GetScreenHeight() 
                                }, 
                                position:ray.Vector2Zero(), 
                                tint:ray.WHITE
                            );
                    }

                ray.EndBlendMode();
            ray.EndTextureMode();
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        ray.BeginDrawing();

            ray.ClearBackground(color:ray.BLACK);
            
            @:source = { 
                x:0, 
                y:0, 
                width:ray.GetScreenWidth(), 
                height:ray.GetScreenHeight() 
            };
            
            // Draw the tile background
            ray.DrawTextureRec(
                texture:backgroundTexture, 
                source, 
                position:ray.Vector2Zero(), 
                tint:ray.WHITE
            );
            source.height *= -1;
            
            // Overlay the shadows from all the lights
            ray.DrawTextureRec(
                texture:lightMask.texture, 
                source, 
                position:ray.Vector2Zero(), 
                tint:ray.ColorAlpha(color:ray.WHITE, alpha: if(showLines) 0.75f  else 1.0f)
            );

            // Draw the lights
            for (0, MAX_LIGHTS)::(i)
            {
                if (lights[i].active) 
                    ray.DrawCircle(
                        centerX:lights[i].position.x, 
                        centerY:lights[i].position.y, 
                        radius:10, 
                        color: if(i == 0) ray.YELLOW else ray.WHITE);
            }

            if (showLines)
            ::<={
                for (0, lights[0].shadowCount)::(s) 
                {

                    ray.DrawTriangleFan(
                        points:lights[0].shadows[s].vertices, 
                        color:ray.DARKPURPLE
                    );
                }

                for (0, boxes->size)::(b)
                {
                    if (ray.CheckCollisionRecs(
                        rec1:boxes[b],
                        rec2:lights[0].bounds)
                    ) ray.DrawRectangleRec(rec:boxes[b], color:ray.PURPLE);

                    ray.DrawRectangleLines(
                        posX:boxes[b].x, 
                        posY:boxes[b].y, 
                        width:boxes[b].width, 
                        height:boxes[b].height, 
                        color:ray.DARKBLUE
                    );
                }

                ray.DrawText(text:"(F1) Hide Shadow Volumes", posX:10, posY:50, fontSize:10, color:ray.GREEN);
            }
            else
            ::<={
                ray.DrawText(text:"(F1) Show Shadow Volumes", posX:10, posY:50, fontSize:10, color:ray.GREEN);
            }

            ray.DrawFPS(posX:screenWidth - 80, posY:10);
            ray.DrawText(text:"Drag to move light", posX:10, posY:10, fontSize:10, color:ray.DARKGREEN);
            //ray.DrawText(text:"Right click to add new light", posX:10, posY:30, fontSize:10, color:ray.DARKGREEN);
        ray.EndDrawing();
        //----------------------------------------------------------------------------------
    }
}


// De-Initialization
//--------------------------------------------------------------------------------------
ray.UnloadTexture(target:backgroundTexture);
ray.UnloadRenderTexture(target:lightMask);
for (0, MAX_LIGHTS)::(i)
{
    if (lights[i].active) ray.UnloadRenderTexture(target:lights[i].mask);
}

ray.CloseWindow();        // Close window and OpenGL context
//--------------------------------------------------------------------------------------

