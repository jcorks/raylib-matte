@:game   = import(module:"game.mt");
@:ray    = import(module:"raylib.mt");
@:class  = import(module:"Matte.Core.Class");


@:bullet = import(module:"bullet.mt"); 
@:camera = import(module:"camera.mt");
@:room   = import(module:"room.mt");
@:Explosion = import(module:"explosion.mt");

@:mesh = ray.GenMeshCube(width:0.2, length: 0.2, height: 0.2);

@:all = {};


@:SPEED_FADE_THRESHOLD = 8;

return class(
    name: "Bullet",
    inherits : [game.Entity],
    statics : {
        // returns if collided with any active bullet.
        // if so, returns the bullet.
        collidedWithABullet::(entity) {
            return {:::} {
                foreach(all)::(bullet, v) {
                    if (ray.Vector2Distance(v1:bullet.position, v2:entity.position) < entity.collideRadius)
                        send(message:bullet);
                }
                return empty;
            }
        }
    },
    define::(this) {
        @direction_;
        @speed_;
        @origin;
        @isFar = false;
        @knockback_;
        @friction_;
        @isBomb_;
        @intensity_;
        
        @model = ray.LoadModelFromMesh(mesh);
        @rotation = {x:Number.random()*1000, y:Number.random()*1000, z:Number.random()*1000};
        @lastPosition = {x:0, y:0, z:0};

        @:shouldExpire ::{
            return ray.Vector3Distance(v1:this.position, v2:origin) > 20 || speed_ < 0.1;
        };

        this.interface = {
            setup ::(
                position,
                direction,
                speed,
                knockback,
                friction,
                isBomb,
                intensity
            ) {
                all[this] = true;
                isBomb_ = isBomb;
                if (isBomb_) 
                    this.scale = {x:1+intensity/3, y:1+intensity/3, z:1+intensity/3};
                intensity_ = intensity;
                
                origin = {...position};
                lastPosition = {...origin};
                this.x = origin.x;
                this.y = origin.y;
                direction_ = direction;
                speed_ = speed;
                knockback_ = knockback;
                friction_ = friction;
            },
            
            explode ::{
                @exp = Explosion.new();
                if (isBomb_)
                    exp.setup(position:this.position, intensity:0.2+intensity_/2.2, isDamaging: true)
                else
                    exp.setup(position:this.position, intensity:0.3);
                room.attach(child:exp);
                this.destroy();
                all->remove(key:this);
            },
            
            knockback : {
                get ::<- knockback_
            },
            
            onStep ::{
                @:delta = ray.GetFrameTime();

                this.x += speed_ * (direction_->asRadians->cos) * delta;
                this.y += speed_ * (direction_->asRadians->sin) * delta;
                
                rotation.x += 6 * delta;
                rotation.y += 6 * delta;
                rotation.z += 6 * delta;
                this.rotation = ray.QuaternionFromEuler(
                    pitch: rotation.x,
                    yaw: rotation.y,
                    roll: rotation.z
                );
                if (!isFar) ::<= {
                    lastPosition = {...origin};
                    isFar = ray.Vector2Distance(v1:origin, v2:this.position) >= 1;
                } else ::<= {
                    @scale = if (speed_ > 8) 1 else speed_ / SPEED_FADE_THRESHOLD;

                    lastPosition.x = (direction_-180)->asRadians->cos;
                    lastPosition.y = (direction_-180)->asRadians->sin;
                    lastPosition.x *= scale;
                    lastPosition.y *= scale;
                    lastPosition.x += this.x;
                    lastPosition.y += this.y;                    
                }

                speed_ -= friction_ * delta;

                if (shouldExpire()) ::<= {
                    all->remove(key:this);
                    this.destroy();
                }
            },
            
            onDraw ::{
                ray.BeginMode3D(camera);
                    @:color = {
                        r: Number.random()*255,
                        g: Number.random()*255,
                        b: Number.random()*255,
                        a: 64 + speed_ / SPEED_FADE_THRESHOLD * 128
                    };
                    model.transform = this.globalMatrix;
                    ray.DrawModelWires(model, position:ray.Vector3Zero(), scale: 1, tint: color);    
                    ray.DrawLine3D(startPos:this.position, endPos:lastPosition, color);
                        
                ray.EndMode3D();                
            }
        }
    }
);
