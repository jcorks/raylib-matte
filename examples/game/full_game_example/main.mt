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
@:ray    = import(module:"raylib.mt");

ray.SetConfigFlags(flags:ray.FLAG_MSAA_4X_HINT);
ray.InitWindow(width: 800, height: 480, title: 'Game');
ray.InitAudioDevice();

@:game = import(module:"game.mt");
@:Shooter = import(module:"shooter.mt");

// Create a new cube
@:player = Shooter.new();

@:controller = import(module:"controller.mt");
@:room = import(module:"room.mt");
@:camera = import(module:"camera.mt");
@:res = import(module:"resources.mt");
@:uiLayer = import(module:"ui_layer.mt");

// Add it to the roots so it and its 
// children get updated
game.GetRoot().attach(child:room);
game.GetRoot().attach(child:camera);
game.GetRoot().attach(child:uiLayer);



// The root node that acts as a room.
room.attach(child:player);
room.attach(child:controller);


game.StartLoop(allowExit:true);

// Unload resources
res.unloadAll();
ray.CloseAudioDevice();
