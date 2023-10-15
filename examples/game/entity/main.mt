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

    raymatte: Entity example

    This example shows how to use the Node hierarchy to 
    have 3D objects inherit their transforms.
    
    This also demonstrates how to inherit from Node 
    to make your own custom class.
*/






@:ray = import(module:"raylib.mt");
@:game = import(module:"game.mt");
@:class = import(module:"Matte.Core.Class");



// The base camera.
@:camera = {
    position : {x:0, y:0, z:0},
    target : {x:0, y:0, z:1},
    up : {x:0, y:1, z:0},
    
    fovy: 45,
    projection : ray.CAMERA_PERSPECTIVE
}

// A class that shows a rotating, oscillating cube wireframe.
// It inherits from Entity.
@:Cube = class(
    name: 'Cube',
    inherits : [game.Entity],
    define::(this) {
        @model;
        @color = ray.GREEN;
        
        
        this.constructor = ::{
            // on creation of the instance, generate a cube mesh and 
            // make it into a model.
            @mesh = ray.GenMeshCube(
                width:4,
                height:4,
                length:4
            );
            
            model = ray.LoadModelFromMesh(mesh);
            
        };
        
        // The current rotation of the cube.
        @:v = {
            x: 0,
            y: 0,
            z: 0
        };      
        // scale of the object. will oscillate
        @scale = 0;  
        this.interface = {
            // setter for the color.  
            color : {
                set ::(value) <- color = value
            },
        
        
            // controls the 
            onStep :: {
                scale += ray.GetFrameTime();
                this.scale = {
                    x: 0.7 + (scale->sin) * 0.7,
                    y: 0.7 + (scale->sin) * 0.7,
                    z: 0.7 + (scale->sin) * 0.7                    
                }
            
            
                v.x += 0.001;
                v.y += 0.001;
                v.z += 0.002;
                
                
                this.rotation = ray.QuaternionFromEuler(
                    pitch:v.x,
                    yaw:v.y,
                    roll:v.z
                );
            },
        
            onDraw :: {
                //ray.DrawGrid(slices:10, spacing: 1);
                model.transform = this.globalMatrix;
                ray.BeginMode3D(camera);
                    ray.DrawModelWires(
                        model,
                        position: ray.Vector3Zero(),
                        scale : 1,
                        tint: color
                    );
                    
                ray.EndMode3D();
            }
        }
    }
);

// initialize window
ray.InitWindow(width: 800, height: 480, title: 'Entity Test');







// Create a new cube
@:cube = Cube.new();
cube.z = 30;

// Create a cube thats a sub component of the first cube.
@:cube2 = Cube.new();
cube.attach(child:cube2);
cube2.z += 5;
cube2.color = ray.RED;


// Add it to the roots so it and its 
// children get updated
game.GetRoot().attach(child:cube);

// Starts the main loop.
game.StartLoop(allowExit:true);

