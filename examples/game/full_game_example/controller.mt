@:game   = import(module:"game.mt");
@:ray    = import(module:"raylib.mt");
@:class  = import(module:"Matte.Core.Class");


@:Enemy = import(module:"enemy.mt"); 
@:Shooter = import(module:"shooter.mt"); 
@:camera = import(module:"camera.mt");
@:room   = import(module:"room.mt");
@:res    = import(module:"resources.mt");
@:Upgrade = import(module:"upgrade.mt");
@:HowToPlay = import(module:"how_to_play.mt");
@:uiLayer = import(module:"ui_layer.mt");


@:WAVE_DISPLAY_ENTER = 1;
@:WAVE_DISPLAY_STAY  = 2.5;
@:WAVE_DISPLAY_LEAVE = 1;
@:SPAWN_RADIUS = 5;

@:FONT_SIZE = 40;
@:FONT_SIZE_SUB = 28;

@:MUSIC_MENU_VOLUME = 0.1;
@:MUSIC_BASE_VOLUME = 0.5;
@:MUSIC_BASE_PITCH = 0.91;
@:MUSIC_PITCH_CHANGE_PER_WAVE = 0.03;

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
        @upgradeMenu;
        @tutorial;

        // Resource prep
        @:musicMain = res.music["main"];
        
        @:spawnTimer = game.Timer.new();
        spawnTimer.installHook(
            event:"onTimeout",
            hook ::(detail) {
                // spawn
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
                        position : pos,
                        health: 
                            if (waveCount < 5) 
                                4 + (Number.random()*3)->floor
                            else
                                (
                                    if (Number.random() < 0.15)
                                        1
                                    else
                                        4 + (Number.random()*(2 + (waveCount / 4)->ceil))->floor
                                )
                    )
                    room.attach(child:e);
                    remaining -= 1;
                }                    
            }
        )

        sm.states = {
            "displayWave_enter" : {
                onEnter ::{
                    textLength = ray.MeasureText(text:"Wave " + waveCount, fontSize: FONT_SIZE);
                    waveCount += 1;
                    targetPos = {x:ray.GetRenderWidth() / 2 - textLength/2, y:ray.GetRenderHeight() / 2};
                    counter = WAVE_DISPLAY_ENTER;

                    // Update music pitch scaling with wave count
                    ray.SetMusicPitch(
                        music: musicMain,
                        pitch: MUSIC_BASE_PITCH + MUSIC_PITCH_CHANGE_PER_WAVE * (waveCount - 1)
                    );
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
            
            "showTutorial" : {
                onEnter ::{
                    tutorial = HowToPlay.new();
                    uiLayer.attach(child:tutorial);
                },
                
                onStep ::{
                    if (ray.IsMouseButtonPressed(button:ray.MOUSE_BUTTON_LEFT)) ::<= {
                        tutorial.destroy();
                        sm.state = "displayWave_enter";
                    }
                }
            },
            
            "wave" : {
                onEnter :: {
                    remaining = waveCount * 3 +  waveCount * 2 * Number.random();
                    active = waveCount * 2;
                    
                    spawnTimer.endless = true;
                    spawnTimer.start(seconds: 1.25 * (0.95 ** waveCount));
                },
                onStep ::{
                    foreach(Enemy.getAll()) ::(enemy, t) {
                        if (ray.Vector2Length(v:enemy.position) < enemy.speedThisFrame)
                            sm.state = "gameover";
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
                    upgradeMenu = Upgrade.new();
                    uiLayer.attach(child:upgradeMenu);
                    game.Log.display = [];

                    // Adjust music volume
                    ray.SetMusicVolume(music: musicMain, volume: MUSIC_MENU_VOLUME);
                },
                
                onStep :: {
                    if (upgradeMenu.shouldContinue) ::<= {
                        upgradeMenu.detach(); // TODO: enter and exit anims
                        sm.state = 'displayWave_enter';
                    }
                },
                
                onLeave :: {
                    game.Log.display = [];                

                    // Adjust music volume
                    ray.SetMusicVolume(music: musicMain, volume: MUSIC_BASE_VOLUME);
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
            this.attach(child:spawnTimer);
            sm.state = 'showTutorial';

            // Start playing music buffer
            ray.SetMusicVolume(music: musicMain, volume: MUSIC_BASE_VOLUME);
            ray.PlayMusicStream(music: musicMain);
        }
        
        this.interface = {
            wave : {
                get ::<- waveCount
            },
            
            onStep :: {
                // Update music buffer
                ray.UpdateMusicStream(music: musicMain);
            }
        }
        
    }
).new();
