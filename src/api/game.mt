@:ray = import(module:"raylib.mt");
@:class = import(module:"Matte.Core.Class");
@:EventSystem = import(module:"Matte.Core.EventSystem");

// A generic node.
// Like in game engines, node are the basic building 
// blocks of a scene. On its own, a Node is just 
// organizational, but the useful tools inherit from 
// this class.
@:Node = class(
    name: "Game.Node",
    inherits : [EventSystem],
    define::(this) {
        @:children = [];
        @parent;
        this.interface = {
            attach ::(child) {
                when(child.parent == this) empty;
                child.detach();
                children->push(value:child);
                child.bindParent(newParent:this);
            },
            
            bindParent ::(newParent) {
               parent = newParent;            
            },
            
            detach :: {
                children->remove(key:children->findIndex(value:this));
                parent = empty;
            },
            
            parent : {
                get ::<- parent
            },
            
            onDraw ::{},
            onStep ::{},
            leaveDraw ::{},
            
            step ::{
                this.onStep();
                foreach(children) ::(i, child) {
                    child.step();
                }
            },
            draw ::{
                
                this.onDraw();
                foreach(children) ::(i, child) {
                    child.draw();
                }
                this.leaveDraw();
            },
            
            children : {
                get ::<- children
            },
            
            // used for 3D and 2D implementations
            updateTransform ::{
                foreach(children) ::(i, child) {
                    child.updateTransform();
                }
            }
        }   
    }    
);







@:Entity = ::<= {
    @:compose ::(
        base,
        position,
        rotation,
        scale 
    ) {
        @:scaleIn = ray.MatrixScale(x:scale.x, y:scale.y, z:scale.z);
        @:rotationIn = ray.QuaternionToMatrix(q:rotation);
        @:positionIn = ray.MatrixTranslate(x:position.x, y:position.y, z:position.z);



        base = ray.MatrixMultiply(left:positionIn, right:base);
        base = ray.MatrixMultiply(left:rotationIn, right:base);
        base = ray.MatrixMultiply(left:scaleIn, right:base);
        return base;
    }

    return class(
        name: "Game.Entity",
        inherits : [Node],
        define::(this) {
            @matrix = ray.MatrixIdentity();
            @isDirty = true; 
            
            @position = ray.Vector3Zero();
            @rotation = ray.QuaternionIdentity();
            @scale = ray.Vector3One();
            
            this.interface = {
                globalMatrix : {
                    get ::<- matrix
                },
            
                isDirty : {
                    get ::<- isDirty,
                    set ::(value) <- isDirty = value
                },
                
                
            
                x : {
                    get ::<- position.x,
                    set ::(value) {
                        isDirty = true;
                        position.x = value;
                        return value;
                    }
                },

                y : {
                    get ::<- position.y,
                    set ::(value) {
                        isDirty = true;
                        position.y = value;;
                        return value;
                    }
                },

                z : {
                    get ::<- position.z,
                    set ::(value) {
                        isDirty = true;
                        position.z = value;
                        return value;
                    }
                },
                
                
                position : {
                    get ::<- position,
                    set ::(value) {
                        position = value;
                        isDirty = true;
                        return value;
                    }
                },
                
                globalPosition : {
                    get :: {
                        return ray.Vector3Transform(v:ray.Vector3Zero(), mat:matrix);
                    }
                },
                
                
                
                rotation : {
                    get ::<- rotation,
                    set ::(value) {
                        rotation = value;
                        isDirty = true;
                        return rotation;
                    }
                },
                
                
                scale : {
                    get ::<- scale,
                    set ::(value) {
                        scale = value;
                        isDirty = true;
                        return scale;
                    }
                },
                
                updateTransform:: {
                    @:parent = this.parent;
                    @:parentValid = parent != empty && parent->isa(type:Entity.type);
                    
                    if (isDirty || (parentValid && parent.isDirty)) ::<= {
                        matrix = compose(
                            base: if (parentValid)
                                        parent.globalMatrix
                                    else 
                                        ray.MatrixIdentity()
                                  ,
                            position,
                            rotation,
                            scale
                        );
                        isDirty = false;
                        foreach(this.children) ::(i, child) {
                            // this should propogate to children
                            child.isDirty = true;
                        }
                        
                    };
                    foreach(this.children) ::(i, child) {
                        child.updateTransform();
                    }
                }
            }
        }
    )
}

@:Node2D = ::<= {
    @zup = {
        x:0,
        y:0,
        z:1
    };
    @:compose ::(
        base,
        position,
        rotation,
        scale 
    ) {
        @:scale = ray.MatrixScale(x:scale.x, y:scale.y, z:1);
        @:rotation = ray.MatrixRotate(axis:zup, angle:rotation->asRadians);
        @:position = ray.MatrixTranslate(x:position.x, y:position.y, z:0);



        base = ray.MatrixMultiply(left:position, right:base);
        base = ray.MatrixMultiply(left:rotation, right:base);
        base = ray.MatrixMultiply(left:scale, right:base);
        return base;
    }

    return class(
        name: "Game.Node2D",
        inherits : [Node],
        define::(this) {
            @matrix = ray.MatrixIdentity();
            @isDirty = true; 
            
            @position = ray.Vector2Zero();
            @rotation = 0;
            @scale = ray.Vector2One();
            
            this.interface = {
                globalMatrix : {
                    get ::<- matrix
                },
            
                isDirty : {
                    get ::<- isDirty,
                    set ::(value) <- isDirty = value
                },
                
                
            
                x : {
                    get ::<- position.x,
                    set ::(value) {
                        isDirty = true;
                        position.x = value;
                        return value;
                    }
                },

                y : {
                    get ::<- position.y,
                    set ::(value) {
                        isDirty = true;
                        position.y = value;;
                        return value;
                    }
                },

                
                position : {
                    get ::<- position,
                    set ::(value) {
                        position = value;
                        isDirty = true;
                        return value;
                    }
                },
                
                globalPosition : {
                    get :: {
                        @:result = ray.Vector3Transform(v:ray.Vector3Zero(), mat:matrix);
                        return {
                            x:result.x,
                            y:result.y
                        };
                    }
                },
                
                
                
                rotation : {
                    get ::<- rotation,
                    set ::(value) {
                        rotation = value;
                        isDirty = true;
                        return rotation;
                    }
                },
                
                
                scale : {
                    get ::<- scale,
                    set ::(value) {
                        scale = value;
                        isDirty = true;
                        return scale;
                    }
                },
                
                updateTransform:: {
                    @:parent = this.parent;
                    @:parentValid = parent != empty && parent->isa(type:Node2D.type);
                    
                    if (isDirty || (parentValid && parent.isDirty)) ::<= {
                        matrix = compose(
                            base: if (parentValid)
                                        parent.globalMatrix
                                    else 
                                        ray.MatrixIdentity()
                                  ,
                            position,
                            rotation,
                            scale
                        );
                        isDirty = false;
                        foreach(this.children) ::(i, child) {
                            // this should propogate to children
                            child.isDirty = true;
                        }
                        
                    };
                    foreach(this.children) ::(i, child) {
                        child.updateTransform();
                    }
                }
            }
        }
    )
}

@StateMachine = class(
    name : 'Game.StateMachine',
    inherits : [Node],
    define::(this) {
        @:states = {};
        @currentState = empty;
        this.interface = {
            states : {
                set ::(value) {
                    foreach(value) ::(name, set) {
                        states[name] = set;
                    }
                }
            },
            addState ::(
                name,
                onEnter,
                onStep,
                onDraw,
                onLeave
            ) {
                states[name] = {
                    onEnter : onEnter,
                    onStep : onStep,
                    onDraw : onDraw,
                    onLeave : onLeave
                };
            },
            

            state : {
                get ::<- currentState,
                set ::(value) {
                    if (currentState)
                        if (currentState.onLeave)
                            currentState.onLeave();

                    currentState = states[value];
                    if (value != empty && currentState == empty)
                        error(detail:"No such state exists.");
                    
                    if (currentState)
                        if (currentState.onEnter)
                            currentState.onEnter();
                }
            },
            
            onStep :: {
                when(currentState == empty) empty;
                if (currentState.onStep)
                    currentState.onStep();
            },

            onDraw :: {
                when(currentState == empty) empty;
                if (currentState.onDraw)
                    currentState.onDraw();
            }

        }
    }
);


@:Timer = class(
    inherits : [Node],
    name : 'Game.Timer',
    define::(this) {
        @start = 0;
        @duration = 0;
        @endless = false;
        @freezeRemaining;
        @active = false;
        
        this.constructor = ::{
            this.events = {
                'onTimeout' ::(detail) {}
            }
        }
        
        this.interface = {
            endless : {
                get ::<- endless,
                set ::(value) <- endless = value
            },
        
            start ::(seconds) {
                duration = seconds;
                start = ray.GetTime();
                active = true;
            },
            
            remaining : {
                get ::{
                    when(freezeRemaining) freezeRemaining;
                    @:diff = ray.GetTime() - start;
                    when (diff > duration) 0;
                    return duration - diff;
                }   
            },
            
            pause ::{
                when(freezeRemaining != empty) empty;
                freezeRemaining = this.remaining;
            },
            
            resume ::{
                when(freezeRemaining == empty) empty;
                start = ray.GetTime() - (duration - freezeRemaining);
                freezeRemaining = empty;
            },
            
            stop :: {
                start = 0;
                duration = 0;
                endless = false;     
                active = false;           
            },
            
            onStep ::{
                when(!active) empty;
                if (this.remaining == 0) ::<= {
                    this.emit(event:'onTimeout');
                    if (endless) 
                        this.start(seconds:duration)
                    else
                        active = false;
                }
            }
        }
    }
);



@:FONT_SIZE = 12;
@:Log = class(
    name : 'Game.Log',
    define::(this) {
        @display = [];
        @:fontSize = 24;
        @baseHeight = 0;
        @:bgColor = {r:32, g:32, b:32, a:255 * 0.8};
        this.interface = {
            display : {
                set ::(value) {
                    display = value;
                },
                
                get ::<- display
            },
            
            
            draw ::{
                when (display == empty || display->size == 0) empty;
                
                if (baseHeight == 0) ::<= {
                    baseHeight = ray.MeasureTextEx(
                        font: ray.GetFontDefault(),
                        text:'|',
                        fontSize,
                        spacing: 0
                    ).y;                
                
                } 
                
                @width = 0;
                foreach(display) ::(i, line) {
                    when(line == empty) empty;
                    @cW = ray.MeasureTextEx(
                        font: ray.GetFontDefault(),
                        text:line,
                        fontSize,
                        spacing: 3
                    ).x;
                    
                    if (cW > width)
                        width = cW;
                        
                    //width += 2; // padding
                }


                ray.DrawRectangle(
                    posX: 0,
                    posY: 0,
                    width,
                    height : display->size * baseHeight + display->size,
                    color : bgColor
                );
            
            
                foreach(display) ::(i, line) {
                    when(line == empty) empty;
                    ray.DrawText(
                        text: line,
                        posX: 1,
                        posY: i + i*baseHeight,
                        fontSize,
                        color: ray.WHITE
                    );
                }
            }
        }
    }
).new();





return ::<= {
    @:roots = [];
    return {
        Log : Log,
        Node : Node,
        Entity : Entity,
        Timer : Timer,
        StateMachine : StateMachine,
        StartLoop ::{
            forever ::{
                foreach(roots) ::(i, root) {
                    root.updateTransform();
                }
                foreach(roots) ::(i, root) {
                    root.step();
                }
                ray.BeginDrawing();
                    ray.ClearBackground(color:ray.BLACK);
                    foreach(roots) ::(i, root) {
                        root.draw();
                    }                            
                Log.draw();
                ray.EndDrawing();
            }
        },
        roots : roots,
    }
}
