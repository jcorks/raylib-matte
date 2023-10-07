@:game   = import(module:"game.mt");
@:ray    = import(module:"raylib.mt");
@:class  = import(module:"Matte.Core.Class");


@:Enemy = import(module:"enemy.mt"); 
@:Shooter = import(module:"shooter.mt"); 
@:camera = import(module:"camera.mt");
@:room   = import(module:"room.mt");


@:WAVE_DISPLAY_ENTER = 1;
@:WAVE_DISPLAY_STAY  = 2.5;
@:WAVE_DISPLAY_LEAVE = 1;
@:SPAWN_RADIUS = 5;

@:FONT_SIZE = 40;
@:FONT_SIZE_SUB = 28;

return class(
    inherits : [game.Node],
    name : "Controller",
    define::(this) {
        @waveCount = 0;
        @sm = game.StateMachine.new();
        
        @counter;
        @textPos = {x:-200, y:ray.GetRenderHeight() * (1 / 3)};
        @textLength;
        @textLengthSub;
        @targetPos = {};
        @active;
        @remaining;
        sm.states = {
            "displayWave_enter" : {
                onEnter ::{
                    textLength = ray.MeasureText(text:"Wave " + waveCount, fontSize: FONT_SIZE);
                    waveCount += 1;
                    targetPos = {x:ray.GetRenderWidth() / 2 - textLength/2, y:ray.GetRenderHeight() / 2};
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
                    
                    textPos.x = ray.Lerp(start:ray.GetRenderWidth()/2- textLength/2, end:targetPos.x, amount:progress * progress); 
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
                    foreach(Enemy.getAll()) ::(enemy, t) {
                        if (ray.Vector2Length(v:enemy.position) < enemy.speedThisFrame)
                            sm.state = "gameover";
                    }
                
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
                    game.Log.display[0] = 'Remaining: ' + (remaining->ceil + Enemy.getCount());

                
                    // wave complete
                    if (remaining <= 0 && Enemy.getCount() == 0) ::<= {
                        sm.state = 'upgrade';
                    }
                }
            },
            
            
            "upgrade" : {
                onEnter :: {
                    game.Log.display[0] = "Pick an upgrade:";
                    game.Log.display[2] = "1 - Reduce Cooldown";
                    game.Log.display[3] = "2 - Bullet count";
                    game.Log.display[4] = "3 - Bullet spread";
                    game.Log.display[5] = "4 - Fire rate";
                    game.Log.display[6] = "5 - Knockback";
                    
                },
                
                onStep :: {
                    if (ray.IsKeyPressed(key:ray.KEY_ONE)) ::<= {
                        Shooter.getMain().upgradeCooldown();
                        sm.state = 'displayWave_enter';
                    }

                    if (ray.IsKeyPressed(key:ray.KEY_TWO)) ::<= {
                        Shooter.getMain().upgradeBulletCount();
                        sm.state = 'displayWave_enter';
                    }

                    if (ray.IsKeyPressed(key:ray.KEY_THREE)) ::<= {
                        Shooter.getMain().upgradeSpread();
                        sm.state = 'displayWave_enter';
                    }


                    if (ray.IsKeyPressed(key:ray.KEY_FOUR)) ::<= {
                        Shooter.getMain().upgradeFireRate();
                        sm.state = 'displayWave_enter';
                    }

                    if (ray.IsKeyPressed(key:ray.KEY_FIVE)) ::<= {
                        Shooter.getMain().upgradeKnockback();
                        sm.state = 'displayWave_enter';
                    }

                },
                
                onLeave :: {
                    game.Log.display = [];                
                }
            },
            
            
            "gameover" : {
                onEnter ::{
                    Shooter.getMain().detach();
                    textLength = ray.MeasureText(text:"Game Over", fontSize:FONT_SIZE);
                    textLengthSub = ray.MeasureText(text:"Made it to Wave " + waveCount, fontSize:FONT_SIZE_SUB);
                },
                
                
                onDraw ::{
                    ray.DrawText(
                        text:"Game Over",
                        posX: ray.GetRenderWidth()/2 - textLength/2,
                        posY: ray.GetRenderHeight()/3,
                        fontSize: FONT_SIZE,
                        color : ray.WHITE                        
                    );

                    ray.DrawText(
                        text:"Made it to Wave " + waveCount,
                        posX: ray.GetRenderWidth()/2 - textLengthSub/2,
                        posY: ray.GetRenderHeight()/2,
                        fontSize: FONT_SIZE_SUB,
                        color : ray.WHITE                        
                    );
                }
            },            
        
        }
        
        
        
        
        this.constructor = ::{
            this.attach(child:sm);
            sm.state = 'displayWave_enter';
        }
        
        this.interface = {
            wave : {
                get ::<- waveCount
            }
        }
        
    }
).new();
