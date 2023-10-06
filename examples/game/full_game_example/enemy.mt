@:game   = import(module:"game.mt");
@:ray    = import(module:"raylib.mt");
@:class  = import(module:"Matte.Core.Class");


@:Bullet = import(module:"bullet.mt"); 
@:camera = import(module:"camera.mt");
@:room   = import(module:"room.mt");

@:mesh = ray.GenMeshCube(width:1, length: 1, height: 1);


@:SPAWN_TIME = 4;
@:HURT_TIME = 0.2;
@:DYING_TIME = 2;

@:all = {};
return class(
    name: "Enemy",
    inherits : [game.Entity],
    statics : {
        getCount :: <- all->keycount
        
    },

    define::(this) {
        @size = Number.random() * 1 + 0.5;
        @health = (size*5)->ceil;
        @rotation = {x:Number.random()*1000, y:Number.random()*1000, z:Number.random()*1000};

        @model = ray.LoadModelFromMesh(mesh);

        @sm = game.StateMachine.new();
        @spawnTime = SPAWN_TIME;
        @dyingTime = 0;
        @hurtTime = 0;
        @flip = false;
        sm.states = {
            "spawning" : {
                onStep ::{
                    spawnTime -= ray.GetFrameTime();
                    @rate = 1 - (spawnTime / SPAWN_TIME);
                    @scale = {
                        x: ray.Lerp(start:0, end:1, amount:rate) * size,
                        y: ray.Lerp(start:0, end:1, amount:rate) * size,
                        z: ray.Lerp(start:0, end:1, amount:rate) * size
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
                                a:255
                            }
                        else
                            color = {
                                r: 255,
                                g: 0,
                                b: 0,
                                a:255
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
                        hit.explode();
                        health -= 1;           
                        if (health <= 0)
                            sm.state = "dead"
                        else
                            sm.state = "hurt";
                    }
                    
                    rotation.x += frame * 4;
                    rotation.y += frame * 3;
                    rotation.z += frame * 13;
                    this.rotation = ray.QuaternionFromEuler(
                        pitch:rotation.x,
                        yaw : rotation.y,
                        roll : rotation.z
                    );
                    
                    @target = -ray.Vector2Angle(v1:{x:0, y:0}, v2:this.position)->asDegrees - 180;
                    
                    this.x += frame * size * 0.5 * target->asRadians->cos;
                    this.y += frame * size * 0.5 * target->asRadians->sin;
                    
                    
                    // add some spin
                    target += 90;
                    this.x += frame * size * 0.1 * target->asRadians->cos;
                    this.y += frame * size * 0.1 * target->asRadians->sin;

                },
                onDraw :: {
                    ray.BeginMode3D(camera);
                        @:color = {
                                r: 255,
                                g: 0,
                                b: 0,
                                a:255
                            }
                        ;
                        model.transform = this.globalMatrix;
                        ray.DrawModelWires(model, position:ray.Vector3Zero(), scale: 1, tint: color);                                
                    ray.EndMode3D();                       
                }
            },    
            
            
            "hurt" : {
                onEnter :: {
                    this.scale = {x:size, y:size, z:size}               
                    hurtTime = HURT_TIME;  
                },
                onStep ::{
                    hurtTime -= ray.GetFrameTime();
                    if (hurtTime < 0)
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
                                a:255
                            }
                        else
                            color = {
                                r: 255,
                                g: 0,
                                b: 0,
                                a:255
                            }
                        ;
                        flip = !flip;
                        model.transform = this.globalMatrix;
                        ray.DrawModelWires(model, position:ray.Vector3Zero(), scale: 1, tint: color);                                
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
                        x: ray.Lerp(start:1, end:0, amount:rate) * size,
                        y: ray.Lerp(start:1, end:0, amount:rate) * size,
                        z: ray.Lerp(start:1, end:0, amount:rate) * size
                    }   
                    this.scale = scale;                    
                    if (dyingTime < 0) ::<={
                        this.detach();
                        all->remove(key:this);
                    }
                },
                onDraw :: {
                    ray.BeginMode3D(camera);
                        @color;
                        if (flip == false) 
                            color = {
                                r: 0,
                                g: 0,
                                b: 0,
                                a:255
                            }
                        else
                            color = {
                                r: 255,
                                g: 0,
                                b: 0,
                                a:255
                            }
                        ;
                        flip = !flip;
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
            ) {
                all[this] = true;
                this.x = position.x;
                this.y = position.y;
            },
            
            collideRadius : {
                get ::<- size
            }
        }
    }
);
