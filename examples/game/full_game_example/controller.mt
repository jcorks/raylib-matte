@:game   = import(module:"game.mt");
@:ray    = import(module:"raylib.mt");
@:class  = import(module:"Matte.Core.Class");


@:Enemy = import(module:"enemy.mt"); 
@:camera = import(module:"camera.mt");
@:room   = import(module:"room.mt");


@:WAVE_DISPLAY_ENTER = 1;
@:WAVE_DISPLAY_STAY  = 2.5;
@:WAVE_DISPLAY_LEAVE = 1;
@:SPAWN_RADIUS = 5;

@:FONT_SIZE = 40;

return class(
    inherits : [game.Node],
    name : "Controller",
    define::(this) {
        @waveCount = 0;
        @sm = game.StateMachine.new();
        
        @counter;
        @textPos = {x:-200, y:ray.GetRenderHeight()/2};
        @targetPos = {};
        @active;
        @remaining;
        sm.states = {
            "displayWave_enter" : {
                onEnter ::{
                    waveCount += 1;
                    targetPos = {x:ray.GetRenderWidth() / 2, y:ray.GetRenderHeight() / 2};
                    counter = WAVE_DISPLAY_ENTER;
                },
                
                onStep ::{
                    counter -= ray.GetFrameTime();
                    @progress = 1 - counter / WAVE_DISPLAY_ENTER;
                    
                    textPos.x = ray.Lerp(start:-200, end:targetPos.x, amount:progress * progress); 
                    when(counter <= 0) ::<= {
                        sm.state = "displayWave_stay"
                    }
                },
                
                onDraw ::{
                    ray.DrawText(
                        text:"Wave " + waveCount,
                        posX: textPos.x,
                        posY: textPos.y,
                        fontSize: FONT_SIZE,
                        color : ray.WHITE
                    );
                }
            },
            
            "displayWave_stay" : {
                onEnter ::{
                    counter = WAVE_DISPLAY_STAY;
                },
                
                onStep ::{
                    counter -= ray.GetFrameTime();
                    when(counter <= 0) ::<= {
                        sm.state = "displayWave_leave";
                    }
                },
                
                onDraw ::{
                    ray.DrawText(
                        text:"Wave " + waveCount,
                        posX: textPos.x,
                        posY: textPos.y,
                        fontSize: FONT_SIZE,
                        color : ray.WHITE                        
                    );
                }
            },

            "displayWave_leave" : {
                onEnter ::{
                    targetPos = {x:2000, y:ray.GetRenderHeight() / 2};
                    counter = WAVE_DISPLAY_LEAVE;
                },
                
                onStep ::{
                    counter -= ray.GetFrameTime();
                    @progress = 1 - counter / WAVE_DISPLAY_ENTER;
                    
                    textPos.x = ray.Lerp(start:ray.GetRenderWidth()/2, end:targetPos.x, amount:progress * progress); 
                    when(counter <= 0) ::<= {
                        sm.state = "wave"
                    }
                },
                
                onDraw ::{
                    ray.DrawText(
                        text:"Wave " + waveCount,
                        posX: textPos.x,
                        posY: textPos.y,
                        fontSize: FONT_SIZE,
                        color : ray.WHITE
                    );
                }
            },
            
            
            "wave" : {
                onEnter :: {
                    remaining = waveCount * 4 +  waveCount * 2 * Number.random();
                    active = waveCount * 2;
                },
                onStep ::{
                    if (remaining > 0 && Enemy.getCount() <= active) ::<= {
                        // spawn 
                        @e = Enemy.new();
                        
                        
                        @pos = {
                            x : Number.random() - 0.5,
                            y : Number.random() - 0.5,
                            z : 0
                        };
                        
                        pos = ray.Vector3Normalize(v:pos);
                        pos.x *= SPAWN_RADIUS;
                        pos.y *= SPAWN_RADIUS;
                        e.setup(
                            position : pos
                        )
                        room.attach(child:e);
                        remaining -= 1;
                    }                    
                    game.Log.display[0] = 'Remaining: ' + Enemy.getCount();

                
                    // wave complete
                    if (remaining <= 0 && Enemy.getCount() == 0) ::<= {
                        sm.state = 'displayWave_enter';
                    }
            }
            }
        
        }
        
        
        this.constructor = ::{
            this.attach(child:sm);
            sm.state = 'displayWave_enter';
        }
        
        this.interface = {
            onStep ::{
            }
        }
    }
);
