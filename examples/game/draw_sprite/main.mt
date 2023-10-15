/*
Copyright (c) 2023 Johnathan Corkery

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/*

    raymatte: DrawSprite example

    This example demonstrates the use of DrawSprite, which 
    is convenient to use in conjunction with Game.Entity for 2D development.
    
*/



@:ray = import(module:"raylib.mt");
@:class = import(module:"Matte.Core.Class");
@:game = import(module:"game.mt");

// need to init window early because we 
// generate textures immediately
ray.InitWindow(width: 800, height: 480, title: 'Entity Test');

// Represents the base gravity for the scene
@:GRAVITY = 1000;


// Since we use the same texture for everything,
// lets generate it by hand.
@:BALL_TEXTURE = ::<= {
    @:image = ray.GenImageColor(
        width:128,
        height:128,
        color : {
            r: 0,
            g: 0,
            b: 0,
            a: 0
        }
    );
    
    ray.ImageDrawCircle(
        dst:image, 
        centerX:64, 
        centerY:64,
        radius: 50,
        color: {
            r: 255,
            g: 255,
            b: 255,
            a: 255
        }
    );
    
    @:texture = ray.LoadTextureFromImage(image);
    ray.UnloadImage(image);
    
    return texture;
}

// Represents a single ball.
// The ball will stretch slightly based on its Y velocity.
@:Ball = class(
    name : "Ball",
    inherits : [game.Entity],
    define:::(this) {
        // initial velocity in 2D, which launches it upward.
        @velocity = -700;
        
        // Give it a random color.
        @:color = {
            r: Number.random() * 255,
            g: Number.random() * 255,
            b: Number.random() * 255,
            a: 255
        };

        @:max::(a, b) <- if (a > b) a else b;

        this.interface = {
            onStep ::{
                // recalculate its scale in the y direction based off of velocity.
                this.scale.y = max(a:1, b:(velocity / 500)->abs);
                
                // Apply gravity and velocity.
                velocity += GRAVITY * ray.GetFrameTime();
                this.y += velocity * ray.GetFrameTime();
                
                // if too far, just remove it.
                if (this.y > 1000)
                    this.destroy();
            },
            
            onDraw ::{
                // DrawSprite is extremely useful when 
                // doing 2D work with Entities, as you can provide 
                // the globalMatrix for drawing the texture, which 
                // takes into account the Node hierarchy for Entities
                // as well as wrapping the scale, rotation, and position 
                // all at once. It also supports tinting.
                game.DrawSprite(
                    transform: this.globalMatrix,
                    texture: BALL_TEXTURE,
                    tint: color
                )   
            }
        }
    }
);


// The controller simply lets us 
// have a means to instantiate balls.
@:Controller = class(
    inherits : [game.Node],
    define::(this) {
        this.interface = {
            onStep ::{
                // If left mouse button is pressed, spawn a ball.
                if (ray.IsMouseButtonPressed(button:ray.MOUSE_BUTTON_LEFT)) ::<={
                    @ball = Ball.new();
                    @pos = ray.GetMousePosition();
                    ball.x = pos.x;
                    ball.y = pos.y;
                    this.attach(child:ball);
                }
            }
        }
    }
);

// Let a user know whats up.
game.Log.display[0] = "Press Left Mouse to spawn a ball!"

// Create and attach controller.
@:controller = Controller.new();
game.GetRoot().attach(child:controller);

// Start the main loop.
game.StartLoop(allowExit:true);





