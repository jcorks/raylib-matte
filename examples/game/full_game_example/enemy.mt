@:game   = import(module:"game.mt");
@:ray    = import(module:"raylib.mt");
@:class  = import(module:"Matte.Core.Class");


@:Bullet = import(module:"bullet.mt"); 
@:camera = import(module:"camera.mt");
@:room   = import(module:"room.mt");
@:res    = import(module:"resources.mt");
@:Explosion = import(module:"explosion.mt");

@:mesh = ray.GenMeshCube(width:1, length: 1, height: 1);


@:SPAWN_TIME = 4;
@:HURT_TIME = 0.1;
@:DYING_TIME = 0.5;

@:HEALTH_WIDTH = 0.05;
@:HEALTH_HEIGHT = 0.05;
@:HEALTH_BORDER_OFFSET = 0.02;

@:all = {};
return class(
    name: "Enemy",
    inherits : [game.Entity],
    statics : {
        getCount :: <- all->keycount,
        getAll ::<- all
        
    },

    define::(this) {
        @:controller = import(module:"controller.mt");
        @size;
        @health_;
        @maxHealth;
        @rotation = {x:Number.random()*1000, y:Number.random()*1000, z:Number.random()*1000};

        @model = ray.LoadModelFromMesh(mesh);

        @sm = game.StateMachine.new();
        @spawnTime = SPAWN_TIME;
        @dyingTime = 0;
        @hurtTime = 0;
        @flip = false;
        @tPos;
        @lastBulletKnockback = 0;

        // Resource prep
        @:soundHit = ray.LoadSoundAlias(source: res.sounds["enemyHit"]);
        @:soundDeath = ray.LoadSoundAlias(source: res.sounds["enemyDeath"]);

        @:playPositionedSound ::(sound) {
            // Pan sound according to x coordinates, but with some reasonable scaling and clamp
            ray.SetSoundPan(
                sound: sound,
                pan: ray.Clamp(value: this.x / 8 + 0.5, min: 0.1, max: 0.9)
            );
            ray.PlaySound(sound: sound);
        }

        @:drawHealthBar ::(color) {
            when(maxHealth == 1) empty;
            @:barHorizontalOffset = HEALTH_WIDTH * (maxHealth * 1.5 - 0.5) / 2;
            @:ratio = health_ / maxHealth;

            ray.DrawRectangleLinesEx(    
                rec: {
                    x: this.position.x - barHorizontalOffset - HEALTH_BORDER_OFFSET * 2,
                    y: this.position.y - HEALTH_HEIGHT / 2 - HEALTH_BORDER_OFFSET * 2 - 0.5,
                    width: (barHorizontalOffset + HEALTH_BORDER_OFFSET * 2) * 2,
                    height: HEALTH_HEIGHT + HEALTH_BORDER_OFFSET * 4
                }, 
                lineThick: HEALTH_BORDER_OFFSET,
                color: {...color, a: 128}
            );

            ray.DrawLineEx(    
                startPos: {
                    x: this.position.x + barHorizontalOffset,
                    y: this.position.y - 0.5
                }, 
                endPos: {
                    x: this.position.x - barHorizontalOffset + barHorizontalOffset  * (1 - ratio) * 2,
                    y: this.position.y - 0.5
                }, 
                thick: HEALTH_HEIGHT,
                color: color
            );
        }

        @:hurt = ::{
            health_ -= 1;           
            if (health_ <= 0)
                sm.state = "dead"
            else
                sm.state = "hurt";

            // Position sound and play
            playPositionedSound(sound: soundHit);        
        }

        sm.states = {
            "spawning" : {
                onEnter :: {                
                    this.scale = ray.Vector3Zero(); 
                },
                onStep ::{
                    spawnTime -= ray.GetFrameTime();
                    @rate = 1 - (spawnTime / SPAWN_TIME);
                    @scale = {
                        x: ray.Lerp(start:0, end:1, amount:rate*rate) * size,
                        y: ray.Lerp(start:0, end:1, amount:rate*rate) * size,
                        z: ray.Lerp(start:0, end:1, amount:rate*rate) * size
                    }   
                    this.scale = scale;                    
                    if (spawnTime < 0)
                        sm.state = "hunting"                 
                },
                onDraw :: {
                    ray.BeginMode3D(camera);
                        @color;
                        if (flip == false) 
                            color = {
                                r: 0,
                                g: 0,
                                b: 0,
                                a: 255
                            }
                        else
                            color = {
                                r: 255,
                                g: 0,
                                b: 0,
                                a: 255
                            }
                        ;
                        flip = !flip;
                        model.transform = this.globalMatrix;
                        ray.DrawModelWires(model, position:ray.Vector3Zero(), scale: 1, tint: color);                                
                    ray.EndMode3D();                       
                }
            },
            
            "hunting" : {
                onEnter :: {
                    this.scale = {x:size, y:size, z:size}
                },
                onStep ::{
                    @:frame = ray.GetFrameTime();
                    
                    @hit = Bullet.collidedWithABullet(entity:this);
                    if (hit != empty) ::<= {
                        lastBulletKnockback = hit.knockback;
                        hit.explode();
                        hurt();
                    } else if (Explosion.isInDamagingExplosion(entity:this)) ::<= {
                        hurt();
                    };
                    
                    rotation.x += frame * 4;
                    rotation.y += frame * 3;
                    rotation.z += frame * 5;
                    this.rotation = ray.QuaternionFromEuler(
                        pitch:rotation.x,
                        yaw : rotation.y,
                        roll : rotation.z
                    );
                    
                    @dir = {
                        x: 0 - this.x,
                        y: 0 - this.y
                    }
                    dir = ray.Vector2Normalize(v:dir);
                    
                    @:s = this.speedThisFrame;
                    this.x += dir.x * s;
                    this.y += dir.y * s;
                    
   

                },
                onDraw :: {
                    ray.BeginMode3D(camera);
                        @:color = {
                                r: 255,
                                g: if (maxHealth == 1) 255 else 0,
                                b: 0,
                                a:255
                            }
                        ;
                        model.transform = this.globalMatrix;
                        ray.DrawModelWires(model, position:ray.Vector3Zero(), scale: 1, tint: color);                                

                        drawHealthBar(color: color);
                    ray.EndMode3D();                       
                }
            },    
            
            
            "hurt" : {
                onEnter :: {
                    // Flicker scale when hurt for extra juice
                    @:pop = 0.9 + Number.random() * 0.5;

                    this.scale = {
                        x:size * pop,
                        y:size * pop,
                        z:size * pop
                    }
                    hurtTime = HURT_TIME;  


                    // Knockback
                    @dir = {
                        x: this.x,
                        y: this.y
                    }
                    dir = ray.Vector2Normalize(v:dir);
                    
                    this.x += dir.x * lastBulletKnockback / size ** 2;
                    this.y += dir.y * lastBulletKnockback / size ** 2;

                    tPos = {...this.position};
                },
                onStep :: {
                    hurtTime -= ray.GetFrameTime();
                    this.x = tPos.x +  0.2*(Number.random() - 0.5);
                    this.y = tPos.y +  0.2*(Number.random() - 0.5);
                    if (hurtTime < 0)
                        sm.state = "hunting"
                },
                onLeave :: {
                    this.x = tPos.x;
                    this.y = tPos.y;
                },
                onDraw :: {
                    ray.BeginMode3D(camera);
                        @color;
                        color = {
                            r: 255,
                            g: 255,
                            b: 255,
                            a:255
                        }
                        model.transform = this.globalMatrix;
                        ray.DrawModelWires(model, position:ray.Vector3Zero(), scale: 1, tint: color);                                

                        drawHealthBar(color: color);
                    ray.EndMode3D();                      
                }
            },                              

            "dead" : {
                onEnter ::{
                    dyingTime = DYING_TIME;
                },
                onStep ::{
                    dyingTime -= ray.GetFrameTime();
                    @rate = 1 - (dyingTime / DYING_TIME);
                    @scale = {
                        x: ray.Lerp(start:1, end:0, amount:rate*rate) * size,
                        y: ray.Lerp(start:1, end:0, amount:rate*rate) * size,
                        z: ray.Lerp(start:1, end:0, amount:rate*rate) * size
                    }   
                    this.scale = scale;                    
                    if (dyingTime < 0) ::<={
                        @exp = Explosion.new();
                        exp.setup(position:this.position, intensity:0.8);

                        // Sound
                        playPositionedSound(sound: soundDeath);

                        room.attach(child:exp);
                        this.destroy();
                        all->remove(key:this);
                    }
                },
                onDraw :: {
                    ray.BeginMode3D(camera);
                        @color = {
                            r: 255,
                            g: 255,
                            b: 255,
                            a: 255
                        }
                    
                        model.transform = this.globalMatrix;
                        ray.DrawModelWires(model, position:ray.Vector3Zero(), scale: 1, tint: color);                                
                    ray.EndMode3D();                       
                }
            },
            
        }

        this.constructor = ::{
            this.attach(child:sm);
            sm.state = "spawning";
        }

        this.interface = {
            setup ::(
                position,
                health
            ) {
                health_ = health;
                maxHealth = health;
                size = 0.3 + (health * 0.10)
                all[this] = true;
                this.x = position.x;
                this.y = position.y;
            },
            
            speedThisFrame : {
                get ::<- ray.GetFrameTime() * 1/size * 0.18 * (1 + 0.015 * (controller.wave))
            },
            
            collideRadius : {
                get ::<- size
            }
        }
    }
);
