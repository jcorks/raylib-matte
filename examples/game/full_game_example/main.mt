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

ray.SetConfigFlags(flags:ray.FLAG_MSAA_4X_HINT);
ray.InitWindow(width: 800, height: 480, title: 'Game');
ray.InitAudioDevice();

@:game = import(:"game.mt");
@:Shooter = import(:"shooter.mt");

// Create a new cube
@:player = Shooter.new();

@:controller = import(:"controller.mt");
@:room = import(:"room.mt");
@:camera = import(:"camera.mt");
@:res = import(:"resources.mt");
@:uiLayer = import(:"ui_layer.mt");

// Add it to the roots so it and its 
// children get updated
game.GetRoot().attach(:room);
game.GetRoot().attach(:camera);
game.GetRoot().attach(:uiLayer);



// The root node that acts as a room.
room.attach(:player);
room.attach(:controller);


game.StartLoop(allowExit:true);

// Unload resources
res.unloadAll();
ray.CloseAudioDevice();
