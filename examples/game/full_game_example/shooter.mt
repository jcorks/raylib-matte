@:game   = import(module:"game.mt");
@:ray    = import(module:"raylib.mt");
@:class  = import(module:"Matte.Core.Class");

@:Bullet = import(module:"bullet.mt"); 
@:camera = import(module:"camera.mt");
@:room   = import(module:"room.mt");

return class(
    name: "Shooter",
    inherits : [game.Entity],
    define::(this) {
        @:shootBullet ::{
            camera.shake(amount: .5, length: 0.05);
            @:b = Bullet.new();                
            b.setup(
                position:  this.position,
                direction: 
                    direction + Number.random() * 20 - 10,
                speed :
                    Number.random() * 5 + 10
            );
            
            room.attach(child:b);
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
                    targetColor.r = 128;
                    targetColor.g = 128;
                    targetColor.b = 128;                
                },
                onStep :: {
                    if (ray.IsKeyPressed(key:ray.KEY_SPACE))
                        sm.state = "shooting"
                        
                }
            },
            
            // State means is in the process of shooting
            // Shooting happens for 1.5 seconds
            "shooting" : {
                onEnter :: {
                    shotCount = 0;
                    shootingTimer.endless = true;
                    shootingTimer.start(seconds:0.1);
                },
                
                onLeave :: {
                    shootingTimer.stop();
                    cooldown = 1.5;
                },
                onStep :: {
                    if (shotCount == 4) ::<={
                        sm.state = "cooldown";
                        shotCount = 0;
                    }
                }
            },
            
            // Has to 
            "cooldown" : {
                onEnter :: {
                    targetColor.r = 64;
                    targetColor.g = 64;
                    targetColor.b = 64;                
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
            onStep ::{
                @:delta = ray.GetFrameTime();
            
                // ease facing the mouse.
                @other = ray.GetMousePosition();
                other.x -= ray.GetRenderWidth()/2;
                other.y -= ray.GetRenderHeight()/2;
                other = ray.Vector2Normalize(v:other);
                @target = -ray.Vector2Angle(v1:{x:0, y:1}, v2:other)->asDegrees - 90;

                if (target < 0) target += 360;
                direction = ray.LerpAngle(start:direction, end:target, amount:7 * delta);

                this.rotation = ray.QuaternionFromAxisAngle(axis:{x:0, y:0, z:1}, angle:(direction + 45)->asRadians);                
            },
        
            onDraw ::{
                @:delta = ray.GetFrameTime();
                // ease color
                currentColor.r = ray.Lerp(start:currentColor.r, end:targetColor.r, amount: 7 * delta);
                currentColor.g = ray.Lerp(start:currentColor.g, end:targetColor.r, amount: 7 * delta);
                currentColor.b = ray.Lerp(start:currentColor.b, end:targetColor.r, amount: 7 * delta);
            
                ray.BeginMode3D(camera);
                    model.transform = this.globalMatrix;
                    ray.DrawModelWires(model, position:ray.Vector3Zero(), scale: 1, tint:currentColor);                                    
                ray.EndMode3D();            
                
            }
        }
    }
);

