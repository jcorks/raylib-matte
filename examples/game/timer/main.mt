
/*

    game.Timer
    
    The Timer node provides a convenient 
    interface for working with timers.
    
    It utilizes the fact that game.Node inherits 
    from a Matte EventSystem, which can emit 
    events and allow hooking on these events.


*/


@:ray = import(module:"raylib.mt");
@:game = import(module:"game.mt");
@:class = import(module:"Matte.Core.Class");


// Create a custom Node class that will update the 
// game.Log with information and manage our 
// game.Timer
@:TimerExample = class(
    name : 'Timer',
    // Since it just uses the game.Log, no drawing is needed.
    inherits : [game.Node],
    
    define::(this) {
        // Creates a timer node.
        @:timer = game.Timer.new();
        @count = 0;   
             
        this.constructor  = ::{
            // Attaches the timer to this node.
            // The timer node needs to be attached, 
            // as it will need to be updated.
            this.attach(child:timer);
            
            // This sets whether the timer will auto-reset 
            // after it expires.
            timer.endless = true;
           
            // installHook is an EventSystem call that registers
            // a function to call when an event is triggered.
            // In our case, the game.Timer emits a "onTimeout" 
            // event when the timer expires. 
            timer.installHook(
                event: 'onTimeout',
                
                // when the timer expires, mark how many times its expired.
                hook ::(detail) {
                    count += 1;
                    game.Log.display[3] = 'Times elapsed: ' + count;
                }
            );

            // Starts the timer set for 5 seconds
            timer.start(seconds:5);

        }
        
    
        this.interface = {
            
            onStep :: {
                // If "a" is pressed, pause the timer.
                if (ray.IsKeyPressed(key:ray.KEY_A)) 
                    timer.pause();
                
                // If "s" is pressed, resume the paused timer.
                if (ray.IsKeyPressed(key:ray.KEY_S)) 
                    timer.resume();
                

                // update the display with current time remaining.
                game.Log.display[4] = 'Remaining: ' + ((timer.remaining*10)->ceil)/10 + 's...';
            }
        }    
    }
);

ray.InitWindow(width: 800, height: 480, title: 'Timer Test');

game.Log.display[0] = "Timer example.";
game.Log.display[1] = "a -> pause, s -> resume";

// Create and add the timer example as an instance 
// in the main loop.
game.roots->push(value:TimerExample.new());
game.StartLoop();
