@:ray    = import(module:"raylib.mt");
@:class  = import(module:"Matte.Core.Class");
@:game = import(module:"game.mt");


@:Camera = class(
    name: "Camera",
    inherits : [game.Node],
    define::(this) {
        @:position = {x:0, y:0, z:-10};
        @:idealPosition = {x:0, y:0};
        @:target = {x:0, y:0, z:1};
        @:up = {x:0, y:1, z:0};
        
        @variance = 0;
        @duration = 0;
        this.interface = {
            position : {get ::<- position},
            target : {get ::<- target},
            up : {get::<- up},
            
            fovy : {get::<- 45},
            projection : {get::<- ray.CAMERA_PERSPECTIVE},
            
            shake ::(amount, length) {
                variance = amount;
                duration = length;
            },
            
            onStep ::{
                if (duration > 0) ::<={
                    position.x = idealPosition.x + (Number.random() * variance - variance/2);
                    position.y = idealPosition.y + (Number.random() * variance - variance/2);
                    duration -= ray.GetFrameTime();
                }
            }
        }    
    }
);


return Camera.new();
