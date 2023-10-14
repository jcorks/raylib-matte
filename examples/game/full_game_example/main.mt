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
