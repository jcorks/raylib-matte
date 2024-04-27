/*
Copyright (c) 2023 

Johnathan Corkery
Adrian "Radscale" Hernik

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
@:ray    = import(:"raylib.mt");
@:class  = import(:"Matte.Core.Class");
@:game = import(:"game.mt");


@:Camera = class(
    name: "Camera",
    inherits : [game.Node],
    define::(this) {
        @:position = {x:0, y:0, z:-10};
        @:idealPosition = {x:0, y:0};
        @:target = {x:0, y:0, z:1};
        @:up = {x:0, y:1, z:0};
        
        @variance = 0;
        @duration = 0;
        this.interface = {
            position : {get ::<- position},
            target : {get ::<- target},
            up : {get::<- up},
            
            fovy : {get::<- 45},
            projection : {get::<- ray.CAMERA_PERSPECTIVE},
            
            shake ::(amount, length) {
                variance = amount;
                duration = length;
            },
            
            onStep ::{
                if (duration > 0) ::<={
                    position.x = idealPosition.x + (Number.random() * variance - variance/2);
                    position.y = idealPosition.y + (Number.random() * variance - variance/2);
                    duration -= ray.GetFrameTime();
                }
            }
        }    
    }
);


return Camera.new();
