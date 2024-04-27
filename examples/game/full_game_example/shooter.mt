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
@:game   = import(:"game.mt");
@:ray    = import(:"raylib.mt");
@:class  = import(:"Matte.Core.Class");

@:Bullet = import(:"bullet.mt"); 
@:camera = import(:"camera.mt");
@:room   = import(:"room.mt");
@:res    = import(:"resources.mt");
@:Stats  = import(:"stats.mt");

@main;


@:BULLET_SPREAD_DEGREES = 30;
@:AMMO_HEIGHT = 0.1
@:AMMO_WIDTH = 0.05
@:CHARGE_THRESHOLD = 0.5;
@:BULLET_FRICTION = 7;

return class(
    name: "Shooter",
    inherits : [game.Entity],
    statics : {
        getMain ::<- main
    },
    define::(this) {
        @charge = 0;


        // Resource prep
        @:soundShoot = ray.LoadSoundAlias(source: res.sounds["shoot"]);
        @:soundLoaded = ray.LoadSoundAlias(source: res.sounds["loaded"]);

        main = this;
        @:shootBullet ::{
            camera.shake(amount: .5, length: 0.05);
            @:spreadCount = 0;//Stats.list[Stats.SPREAD].value;
            @dir = direction - ((spreadCount)*BULLET_SPREAD_DEGREES / 2)
            @:dirSpread = Stats.list[Stats.ACCURACY].value;

            for(0, spreadCount + 1) ::(i) {
            
                @:b = Bullet.new();                
                b.setup(
                    position:  this.position,
                    direction: 
                        dir + Number.random() * dirSpread - dirSpread/2,
                    speed:
                        Number.random() * 1.5 + Stats.list[Stats.SPEED].value,
                    knockback: 
                        Stats.list[Stats.KNOCKBACK].value,
                    friction:
                        BULLET_FRICTION,
                    isBomb: false
                );
                
                room.attach(child:b);
                dir += BULLET_SPREAD_DEGREES;

            }
            // Sound
            ray.PlaySound(sound: soundShoot);
        }
        
        
        @:shootBomb ::{
            camera.shake(amount: 4, length: 0.05);
            @:b = Bullet.new();                
            @:dirSpread = Stats.list[Stats.ACCURACY].value;
            b.setup(
                position:  this.position,
                direction: 
                    direction + Number.random() * dirSpread - dirSpread/2,
                speed:
                    3,
                knockback: 
                    Stats.list[Stats.KNOCKBACK].value,
                friction: 0,
                isBomb:
                    true,
                intensity:
                    (getShotsCharged() / 4) * Stats.list[Stats.CHARGED_INTENSITY].value
            );
            
            
            room.attach(child:b);

            // Maybe a different sound for bombs?
            ray.PlaySound(sound: soundShoot);
        
        }        
        
        @:getShotsCharged :: {
            @:maxShots = Stats.list[Stats.MAX_SHOTS].value;
            @:r = (charge - CHARGE_THRESHOLD);
            when (r > maxShots - shotCount) maxShots - shotCount
            return r->floor;
        }
            
        @model = ::<= {
            @mesh = ray.GenMeshCube(width:0.5, height:0.5, length:0.5);
            return ray.LoadModelFromMesh(mesh);
        }
        
        @direction = 0;
        @currentColor = {r:0, g:0, b:0, a:255};
        @targetColor = {r:128, g:128, b:128, a:255};

        @:sm = game.StateMachine.new();
        @:shootingTimer = game.Timer.new();
        
        shootingTimer.installHook(event:"onTimeout", hook::(detail){
            currentColor.r = 255;
            currentColor.g = 255;
            currentColor.b = 255;
            shootBullet();
            shotCount += 1;
        });
        

        @cooldown = 0;
        @shotCount = 0;
        sm.states = {
            // State means is ready to shoot
            "ready" : {
                onEnter :: {
                    // Flash for juice, particularly nice when cooldown ends
                    currentColor.r = 255;
                    currentColor.g = 255;
                    currentColor.b = 255;                
                    targetColor.r = 128;
                    targetColor.g = 128;
                    targetColor.b = 128;

                    // Sound
                    ray.PlaySound(sound: soundLoaded);
                },
                onStep :: {
                    if (ray.IsKeyDown(:ray.KEY_SPACE) || ray.IsMouseButtonDown(:ray.MOUSE_BUTTON_LEFT)) ::<= {
                        sm.state = "shootPrimary"
                        charge = 0;
                    } else ::<= {
                        if (ray.IsMouseButtonDown(:ray.MOUSE_BUTTON_RIGHT)) ::<= {
                            charge += Stats.list[Stats.CHARGE_RATE].value * ray.GetFrameTime();
                        } else ::<= {
                            if (charge < CHARGE_THRESHOLD)
                                charge = 0
                            else 
                                sm.state = "shootSecondary"
                        }
                    }
                }
            },
            
            
            // State means is in the process of shooting
            // Shooting happens for 1.5 seconds
            "shootPrimary" : {
                onEnter :: {
                    shootingTimer.endless = true;
                    shootingTimer.start(seconds:Stats.list[Stats.FIRERATE].value);
                },
                
                onLeave :: {
                    shootingTimer.stop();
                },
                onStep :: {
                    if (shotCount == Stats.list[Stats.MAX_SHOTS].value) ::<={
                        sm.state = "cooldown";
                        shotCount = 0;
                    }
                }
            },
            
            
            // Fires one large shot
            "shootSecondary" : {
                onEnter :: {
                    shootBomb();
                    charge = 0;                    
                },
                
                onStep ::{
                    sm.state = "cooldown";
                    shotCount = 0;
                }
            },
            
            
            // Has to recharge
            "cooldown" : {
                onEnter :: {
                    cooldown = Stats.list[Stats.COOLDOWN].value;
                    targetColor.r = 32;
                    targetColor.g = 32;
                    targetColor.b = 32;                
                },
                onStep :: {
                    cooldown -= ray.GetFrameTime();
                    if (cooldown < 0)
                        sm.state = "ready";
                },
                
                onLeave ::{
                    shotCount = 0;                
                }
            }
        };
        
        sm.state = "ready";
 

        this.constructor = ::{
            this.attach(:shootingTimer);
            this.attach(:sm);               
        }
 
        
        this.interface = {
            
            onStep ::{
                @:delta = ray.GetFrameTime();
            
                // ease facing the mouse.
                @other = ray.GetMousePosition();
                other.x -= ray.GetRenderWidth()/2;
                other.y -= ray.GetRenderHeight()/2;
                other = ray.Vector2Normalize(v:other);
                @target = -ray.Vector2Angle(v1:{x:0, y:1}, v2:other)->asDegrees - 90;

                if (target < 0) target += 360;
                direction = game.LerpAngle(start:direction, end:target, amount:7 * delta);

                this.rotation = ray.QuaternionFromAxisAngle(axis:{x:0, y:0, z:1}, angle:(direction + 45)->asRadians);                
            },
        
            onDraw ::{
                @:delta = ray.GetFrameTime();

                // Ammo bar rendering helpers 
                @:maxShots = Stats.list[Stats.MAX_SHOTS].value;
                @:barHorizontalOffset = AMMO_WIDTH * (maxShots * 1.5 - 0.5) / 2;

                // ease color
                currentColor.r = ray.Lerp(start:currentColor.r, end:targetColor.r, amount: 5 * delta);
                currentColor.g = ray.Lerp(start:currentColor.g, end:targetColor.r, amount: 5 * delta);
                currentColor.b = ray.Lerp(start:currentColor.b, end:targetColor.r, amount: 5 * delta);
            
                ray.BeginMode3D(camera);
                    model.transform = this.globalMatrix;
                    ray.DrawModelWires(model, position:ray.Vector3Zero(), scale: 1, tint:currentColor);                                    
                    
                    if (sm.state == "cooldown") ::<= {
                        @ratio = cooldown / Stats.list[Stats.COOLDOWN].value;

                        ray.DrawLineEx(    
                            startPos: {
                                x: camera.target.x + barHorizontalOffset - barHorizontalOffset
                                    * (1 - ratio)
                                    + AMMO_WIDTH / 2,
                                y: camera.target.y - 0.5
                            }, 
                            endPos: {
                                x: camera.target.x - barHorizontalOffset + barHorizontalOffset
                                    * (1 - ratio),
                                y: camera.target.y - 0.5
                            }, 
                            thick: AMMO_HEIGHT * 0.8,
                            color: {...currentColor, a: currentColor.a / 2}
                        );
                    } else ::<= {  
                        @shotsCharged = getShotsCharged(); 
                        for (0, maxShots) ::(i) {
                            @xPos = camera.target.x + barHorizontalOffset - AMMO_WIDTH * (i * 1.5);
                            @yPos = camera.target.y - 0.5 - AMMO_HEIGHT / 2;

                            @isReady = (i >= shotCount);
                            ray.DrawLineEx(
                                startPos: {
                                    x: xPos,
                                    y: yPos
                                },
                                endPos: {
                                    x: xPos,
                                    y: yPos + AMMO_HEIGHT * 0.2 + AMMO_HEIGHT * 0.8 * isReady
                                },
                                thick: AMMO_WIDTH,
                                color: if ((i < shotsCharged) && isReady) ray.GREEN else currentColor
                            );
                        }
                    }
                ray.EndMode3D();            
                
            }
        }
    }
);

