@:game   = import(module:"game.mt");
@:ray    = import(module:"raylib.mt");
@:class  = import(module:"Matte.Core.Class");


@:bullet = import(module:"bullet.mt"); 
@:camera = import(module:"camera.mt");
@:room   = import(module:"room.mt");



@:AXIS = {x:0, y:0, z:1};

return class(
    name: "Explosion",
    inherits : [game.Entity],
    define::(this) {
        @life;
        @size;
        @initialLife;
        this.interface = {
            setup ::(position, intensity) {
                life = intensity;
                size = intensity * 4;
                initialLife = life;
                this.position = position;
                camera.shake(amount:intensity, length:life);
            },
            
            onStep ::{
                when(life == empty) empty;
                life -= ray.GetFrameTime();
                when(life <= 0)
                    this.destroy();
            },
            
            onDraw ::{
                when(life == empty) empty;
                ray.BeginMode3D(camera);
                    @:color = {
                        r: Number.random()*255,
                        g: Number.random()*255,
                        b: Number.random()*255,
                        a: 255 * (life / initialLife)
                    };
                    ray.DrawCircle3D(
                        center : this.position,
                        radius : size * (1 - life / initialLife)**0.5,
                        rotationAxis : AXIS,
                        rotationAngle: 0,
                        color
                    );
                ray.EndMode3D();
            }
        }    
    }
);

