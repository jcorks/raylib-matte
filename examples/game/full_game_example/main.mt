@:ray    = import(module:"raylib.mt");


ray.InitWindow(width: 800, height: 480, title: 'Game');


@:game = import(module:"game.mt");
@:Shooter = import(module:"shooter.mt");
@:Controller = import(module:"controller.mt");
@:room = import(module:"room.mt");
@:camera = import(module:"camera.mt");


// Add it to the roots so it and its 
// children get updated
game.roots->push(value:room);
game.roots->push(value:camera);


// Create a new cube
@:player = Shooter.new();


@:controller = Controller.new();
room.attach(child:controller);

// The root node that acts as a room.
room.attach(child:player);

// Starts the main loop.
game.StartLoop();
