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
@:game   = import(module:"game.mt");
@:ray    = import(module:"raylib.mt");
@:class  = import(module:"Matte.Core.Class");


@:bullet = import(module:"bullet.mt"); 
@:camera = import(module:"camera.mt");
@:room   = import(module:"room.mt");



@:AXIS = {x:0, y:0, z:1};
@:damagingExplosions = {};
return class(
    name: "Explosion",
    inherits : [game.Entity],
    statics : {
        isInDamagingExplosion::(entity) {
            return {:::} {
                foreach(damagingExplosions)::(exp, v) {
                    if (ray.Vector2Distance(v1:exp.position, v2:entity.position) < (entity.collideRadius + exp.size/2))
                        send(message:true);
                }
                return false;
            }
        }
    },
    define::(this) {
        @life;
        @size;
        @initialLife;
        this.interface = {
            size : {
                get ::<- size * (1 - life / initialLife)**0.5
            },
        
            setup ::(position, intensity, isDamaging) {
                if (isDamaging)
                    damagingExplosions[this] = true;

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
            
            onDestroy ::{
                damagingExplosions->remove(key:this);
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
                        radius : this.size,
                        rotationAxis : AXIS,
                        rotationAngle: 0,
                        color
                    );
                ray.EndMode3D();
            }
        }    
    }
);

