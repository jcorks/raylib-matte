@:game   = import(module:"game.mt");
@:ray    = import(module:"raylib.mt");
@:class  = import(module:"Matte.Core.Class");

@:Bullet = import(module:"bullet.mt"); 
@:camera = import(module:"camera.mt");
@:room   = import(module:"room.mt");

@main;


@:BULLET_SPREAD_DEGREES = 30;
@:AMMO_HEIGHT = 0.1
@:AMMO_WIDTH = 0.05

return class(
    name: "Shooter",
    inherits : [game.Entity],
    statics : {
        getMain ::<- main
    },
    define::(this) {
        @rankCount = 0;
        @rankSpread = 0;
        @rankCooldown = 0;
        @rankFirerate = 0;
        @rankKnockback = 0;
        @rankRange = 0;

        // Rank scaling helpers
        @:getMaxShots ::<- 4 + rankCount * 3;
        @:getCooldown ::<- 1.5 * (0.7 ** rankCooldown);
        @:getFirerate ::<- 0.1 * (0.7 ** rankFirerate);
        @:getKnockback ::<- 0.03 * (1.4 ** rankKnockback);
        @:getFriction ::<- 0.02 + 0.03 * (0.9 ** rankRange);


        main = this;
        @:shootBullet ::{
            camera.shake(amount: .5, length: 0.05);
            @dir = direction - ((rankSpread)*BULLET_SPREAD_DEGREES / 2)
            for(0, rankSpread + 1) ::(i) {
            
                @:b = Bullet.new();                
                b.setup(
                    position:  this.position,
                    direction: 
                        dir + Number.random() * 20 - 10,
                    speed:
                        Number.random() * 1.5 + 10,
                    knockback: 
                        getKnockback(),
                    friction:
                        getFriction()
                );
                
                room.attach(child:b);
                dir += BULLET_SPREAD_DEGREES;
            }
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
                },
                onStep :: {
                    if (ray.IsKeyDown(key:ray.KEY_SPACE))
                        sm.state = "shooting"
                        
                }
            },
            
            // State means is in the process of shooting
            // Shooting happens for 1.5 seconds
            "shooting" : {
                onEnter :: {
                    shotCount = 0;
                    shootingTimer.endless = true;
                    shootingTimer.start(seconds:getFirerate());
                },
                
                onLeave :: {
                    shootingTimer.stop();
                    cooldown = getCooldown();
                },
                onStep :: {
                    if (shotCount == getMaxShots()) ::<={
                        sm.state = "cooldown";
                        shotCount = 0;
                    }
                }
            },
            
            // Has to 
            "cooldown" : {
                onEnter :: {
                    targetColor.r = 32;
                    targetColor.g = 32;
                    targetColor.b = 32;                
                },
                onStep :: {
                    cooldown -= ray.GetFrameTime();
                    if (cooldown < 0)
                        sm.state = "ready";
                }
            }
        };
        
        sm.state = "ready";
 

        this.constructor = ::{
            this.attach(child:shootingTimer);
            this.attach(child:sm);               
        }
 
        
        this.interface = {
            rankCount : {
                get ::<- rankCount,
                set ::(value) <- rankCount = value
            },
            rankCooldown : {
                get ::<- rankCooldown,
                set ::(value) <- rankCooldown = value
            },
            rankSpread : {
                get ::<- rankSpread,
                set ::(value) <- rankSpread = value
            },
            rankFirerate : {
                get ::<- rankFirerate,
                set ::(value) <- rankFirerate = value
            },
            rankKnockback : {
                get ::<- rankKnockback,
                set ::(value) <- rankKnockback = value
            },
            rankRange : {
                get ::<- rankRange,
                set ::(value) <- rankRange = value
            },
            
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
                @:maxShots = getMaxShots();
                @:barHorizontalOffset = AMMO_WIDTH * (maxShots * 1.5 - 0.5) / 2;

                // ease color
                currentColor.r = ray.Lerp(start:currentColor.r, end:targetColor.r, amount: 5 * delta);
                currentColor.g = ray.Lerp(start:currentColor.g, end:targetColor.r, amount: 5 * delta);
                currentColor.b = ray.Lerp(start:currentColor.b, end:targetColor.r, amount: 5 * delta);
            
                ray.BeginMode3D(camera);
                    model.transform = this.globalMatrix;
                    ray.DrawModelWires(model, position:ray.Vector3Zero(), scale: 1, tint:currentColor);                                    
                    
                    if (sm.state == "cooldown") ::<= {
                        @ratio = cooldown / getCooldown();

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
                        for (0, maxShots) ::(i) {
                            @xPos = camera.target.x + barHorizontalOffset - AMMO_WIDTH * (i * 1.5);
                            @yPos = camera.target.y - 0.5 - AMMO_HEIGHT / 2;

                            ray.DrawLineEx(
                                startPos: {
                                    x: xPos,
                                    y: yPos
                                },
                                endPos: {
                                    x: xPos,
                                    y: yPos + AMMO_HEIGHT * 0.2 + AMMO_HEIGHT * 0.8 * (i >= shotCount)
                                },
                                thick: AMMO_WIDTH,
                                color: currentColor
                            );
                        }
                    }
                ray.EndMode3D();            
                
            }
        }
    }
);

