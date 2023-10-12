/////////////////////////
/*
The raylib-matte Game Extension Library (game.mt)

The game extension library is split into classes.
Any relevent documentation will be commented with 
slash-star comments

NOTE;
Functions that are not meant to be called by user code 
and do not have a stable interface are suffixed with _


*/
/////////////////////////

@:ray = import(module:"raylib.mt");
@:class = import(module:"Matte.Core.Class");
@:EventSystem = import(module:"Matte.Core.EventSystem");

@toDestroy = empty;
/*
    Class: Node
   
    A generic node.
    Like in game engines, nodes are the basic building 
    blocks of a scene. On its own, a Node is just 
    organizational, but the useful tools inherit from 
    this class.

    Nodes also can generate their own events to which 
    user code can respond.

*/
@:Node = class(
    name: "Game.Node",
    inherits : [EventSystem],
    define::(this) {
        @:children = [];
        @parent;
        @destroyed = false;
        this.interface = {
            /*
                Adds a node as a child of this node. If the child 
                already has a parent, that parent is detached.
            */
            attach ::(child) {
                when(child.parent == this) empty;
                child.detach();
                children->push(value:child);
                child.bindParent_(newParent:this);
            },

            /*
                Adds a node as a child of this node. If the child 
                already has a parent, that parent is detached.
            */
            attachFirst ::(child) {
                when(child.parent == this) empty;
                child.detach();
                children->insert(at:0, value:child);
                child.bindParent_(newParent:this);
            },

            
            
            /*
                Detaches a node from its current parent.
                Has no effect if the node has no parents.
            */
            detach :: {
                when(parent == empty) empty;
                parent.unbindParent_(child:this);
                parent = empty;
            },
            
            /*
                Getter for the current parent node of this node.
                If no such node exists, empty is returned.
            */
            parent : {
                get ::<- parent
            },
            
            /*
                Virtual function that is called on every update frame.
                Inherited classes from Node implement these with 
                logic for what the Node should do as it updates.
                onStep for this Node is called before children nodes.
            */
            onStep ::{},

            
            /*
                Virtual function that is called on every update frame.
                Inherited classes from Node implement these with 
                drawing commands. onDraw() is guaranteed to happen after 
                a BeginDrawing() and before an EndDrawing().
                onDraw for this Node is called before children nodes.
            */
            onDraw ::{},
            
            /*
                Virtual function that is called on every update frame.
                Inherited classes from Node implement these with 
                things to do after a node and its children have run onDraw().
            */
            onLeaveDraw ::{},
            
            /*
                Virtual function that is called when destroy() is called.
            */
            onDestroy ::{},
            
            /*  
                Performs a step for this node and its children.
                This is called for you once StartLoop() is called.
            */
            step ::{
                if (destroyed) error(detail:"Tried to update Node that was already destroyed!");
                this.onStep();
                foreach(children) ::(i, child) {
                    child.step();
                }
            },
            
            
            /*
                Performs a draw for this node and its children.
                This is called for you once StartLoop() is called.
            */
            draw ::{
                if (destroyed) error(detail:"Tried to draw Node that was already destroyed!");
                this.onDraw();
                foreach(children) ::(i, child) {
                    child.draw();
                }
                this.onLeaveDraw();
            },
            
            /*
                Marks that this Node is not to be used any further.
                When called, onDestroy() is called for this Node.
            */
            destroy ::{
                if (toDestroy == empty) toDestroy = {};
                toDestroy[this] = true;
            },
            

            /*
                A getter that returns the array of current children
                of this node. The array will contain no members if 
                there are no children.
            */
            children : {
                get ::<- children
            },
            
           
            updateTransform_ ::{
                foreach(children) ::(i, child) {
                    child.updateTransform_();
                }
            },
            bindParent_ ::(newParent) <- parent = newParent,
            unbindParent_::(child) {
                children->remove(key:children->findIndex(value:child));            
            },
            finalize_ ::{
                if (destroyed) error(detail:"Tried to destroy a Node that was already destroyed.");
                this.detach();
                this.onDestroy();
                destroyed = true;
            
            }
        }   
    }    
);






/*
    Class: Entity
   
    A node that responds to a 2D or 3D environment. allowing
    its transform to be inherited by children.
    
    Every entity has a position, rotation, and scale, all of which 
    pull from its parent, if any.
    

*/
@:Entity = ::<= {
    @:compose_ ::(
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
            
                /*
                    Getter for the raylib Matrix that represents the 
                    global, rather than local, transform of this entity.
                    
                */
                globalMatrix : {
                    get ::<- matrix
                },

                
                /*
                    Setter / Getter for the local X position.
                */
                x : {
                    get ::<- position.x,
                    set ::(value) {
                        isDirty = true;
                        position.x = value;
                        return value;
                    }
                },

                /*
                    Setter / Getter for the local Y position.
                */
                y : {
                    get ::<- position.y,
                    set ::(value) {
                        isDirty = true;
                        position.y = value;;
                        return value;
                    }
                },

                /*
                    Setter / Getter for the local Z position.
                */
                z : {
                    get ::<- position.z,
                    set ::(value) {
                        isDirty = true;
                        position.z = value;
                        return value;
                    }
                },
                
                /*
                    Setter / Getter for the position vector reference.
                */
                position : {
                    get ::<- position,
                    set ::(value) {
                        position = value;
                        isDirty = true;
                        return value;
                    }
                },
                
                /* 
                    Getter for a global position of the Entity.
                */
                globalPosition : {
                    get :: {
                        return ray.Vector3Transform(v:ray.Vector3Zero(), mat:matrix);
                    }
                },
                
                
                
                /*
                    Setter / Getter for the rotational vector reference.
                */
                rotation : {
                    get ::<- rotation,
                    set ::(value) {
                        rotation = value;
                        isDirty = true;
                        return rotation;
                    }
                },
                
                
                /*
                    Setter / Getter for the scale vector reference.
                */
                scale : {
                    get ::<- scale,
                    set ::(value) {
                        scale = value;
                        isDirty = true;
                        return scale;
                    }
                },
                
                
                
            
                isDirty_ : {
                    get ::<- isDirty,
                    set ::(value) <- isDirty = value
                },
                                
                updateTransform_:: {
                    @:parent = this.parent;
                    @:parentValid = parent != empty && parent->isa(type:Entity.type);
                    
                    if (isDirty || (parentValid && parent.isDirty_)) ::<= {
                        matrix = compose_(
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
                            if (child->isa(type:Entity.type))
                                child.isDirty_ = true;
                        }
                        
                    };
                    foreach(this.children) ::(i, child) {
                        child.updateTransform_();
                    }
                }
            }
        }
    )
}

/*
    Class: StateMachine
   
    Provides a mechanism by which states can be controlled
    and updated of a particular object.
    
    States are managed with response functions that are called
    when a state is updated. As such, a state machine can supplant 
    the usual onStep / onDraw functions that are called for an Entity.
    
*/
@StateMachine = class(
    name : 'Game.StateMachine',
    inherits : [Node],
    define::(this) {
        @states = {};
        @currentState = empty;
        @currentStateName = empty;
        this.interface = {
            /* 
                Setter for the entire possible set of 
                states that the state machine can handle.
                Each member of the input object should be 
                keyed with a string, and each value shall be an object.
                Each object shall have named, if desired, a member 
                for "onEnter", "onStep", "onDraw", and "onLeave", each
                corresponding to inputs to addState(). See that function 
                for more details.
            */
            states : {
                set ::(value) {
                    states = {};
                    foreach(value) ::(name => String, set => Object) {
                        states[name] = set;
                    }
                }
            },
            
            /*
                Adds a new state to the state machine.
            */
            addState ::(
                name => String,
                onEnter,
                onStep,
                onDraw,
                onLeave
            ) {
                states[name] = {
                    onEnter : if (onEnter) onEnter else ::{},
                    onStep : if (onStep) onStep else ::{},
                    onDraw : if (onDraw) onDraw else ::{},
                    onLeave : if (onLeave) onLeave else ::{}
                };
            },
            
            /*
                Setter / getter for the current state name.
                To set no state, set with empty.
            */
            state : {
                get ::<- currentStateName,
                set ::(value) {
                    if (currentState)
                        if (currentState.onLeave)
                            currentState.onLeave();

                    currentState = states[value];
                    if (value != empty && currentState == empty)
                        error(detail:"No such state exists.");

                                    
                    currentStateName = value;
                    
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
            
            active : {
                get ::<- active
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



@:lerp_repeat ::(t, m) {
    return ray.Clamp(value:t - ((t / m)->floor) * m, min:0, max:m);
}





@:Layout = ::<= {
    @Item = class(
        name: "game.Layout.Item",
        inherits : [Node],
        define::(this) {
            @bounds_ = {x:0, y:0, width:0, height:0};
            
            @marginOffset_ = {x:0, y:0, width:0, height:0};
            @paddingOffset_ = {x:0, y:0, width:0, height:0};
            @sizeRequest_;
            @pixelSizeRequest_;
            @dirty = true;
            @innerSpace = {x:0, y:0, width:0, height:0};
            @outerSpace = {x:0, y:0, width:0, height:0};
            this.interface = {
                /*
                    If no sizeRequest or pixelSizeRequest is present, 
                    the remaining available space is divided equally among
                    children.
                */
                setup ::(
                    margin, // total margin as one number
                    padding, // total padding as one number
                    marginOffset, // margin as a Rectangle set of offsets.
                    paddingOffset, // padding as a Rectangle set of offsets
                    sizeRequest, // fraction of remainingSpace
                    pixelSizeRequest // pixels of total space used. calculated first. Takes priority if both are present                
                ) {
                    if (margin != empty) ::<= {
                        marginOffset_.x = margin;
                        marginOffset_.y = margin;
                        marginOffset_.width = -margin*2;
                        marginOffset_.height = -margin*2;
                    }
                    
                    if (padding != empty) ::<= {
                        paddingOffset_.x = padding;
                        paddingOffset_.y = padding;
                        paddingOffset_.width = -padding*2;
                        paddingOffset_.height = -padding*2;
                    }
                
                    if (marginOffset != empty) ::<= {
                        marginOffset_ = {...marginOffset};
                    }

                    if (paddingOffset != empty) ::<= {
                        paddingOffset_ = {...paddingOffset};
                    }
                    
                    sizeRequest_ = sizeRequest;
                    pixelSizeRequest_ = pixelSizeRequest;
                
                    dirty = true;
                    return this;
                },
                resize::(width, height) {
                    bounds_.width = width;
                    bounds_.height = height;
                    dirty = true;
                },
                
                move::(x, y) {
                    bounds_.x = x;
                    bounds_.y = y;
                    dirty = true;
                },
                
                recalculate::{
                    
                    outerSpace.x = bounds_.x + marginOffset_.x;
                    outerSpace.y = bounds_.y + marginOffset_.y;
                    outerSpace.width = bounds_.width + marginOffset_.width;
                    outerSpace.height = bounds_.height + marginOffset_.height;
                    
                    innerSpace.x = outerSpace.x + paddingOffset_.x;
                    innerSpace.y = outerSpace.y + paddingOffset_.y;
                    innerSpace.width = outerSpace.width + paddingOffset_.width;
                    innerSpace.height = outerSpace.height + paddingOffset_.height;
                    
                    
                    
                    foreach(this.children) ::(i, child) {
                        when(child => Item.type)
                            child.needsRecalculation();
                    }                    
                    
                    this.onRecalculate();
                    dirty = false;                
                },
                
                pixelSizeRequest : {
                    set ::(value) {
                        pixelSizeRequest_ = value;
                        dirty = true;
                    },
                    get ::<- pixelSizeRequest_
                },
                
                sizeRequest : {
                    set ::(value) {
                        sizeRequest_ = value;
                        dirty = true;
                    },
                    get ::<- sizeRequest_
                },
                
                marginOffset : {
                    set ::(value => Object) {
                        marginOffset_ = {...value};
                        dirty = true;
                    },
                    get ::<- marginOffset_
                },
                
                paddingOffset : {
                    set ::(value => Object) {
                        paddingOffset_ = {...value};
                        dirty = true;
                    },
                    get ::<- paddingOffset_
                },
                
                // OVERRIDES node step, so do it right!
                step ::{                
                    if (dirty) ::<= {
                        this.recalculate();
                    }
                    
                    this.onStep();
                    foreach(this.children) ::(i, child) {
                        child.step();
                    }                    
                },
                
                childSpace : {
                    get ::<- innerSpace
                },
                
                contentSpace : {
                    get ::<- outerSpace
                },
                
                needsRecalculation :: {
                    dirty = true
                },  
                
                
                onRecalculate ::(){}
            }
        }
    );


    @Vertical = class(
        name: "game.Layout.Vertical",
        inherits : [Item],
        define::(this) {
            this.interface = {
                layout ::(items) {
                    foreach(items) ::(index, item) {
                        this.attach(child:item);
                    }
                    return this;
                },
                onRecalculate :: {
                    @totalVerticalAvailable = this.childSpace.height;
                    @empties = [];
                    @emptyCount = 0;
                    @freeSpaceFraction = 1;

                    
                    // first iterate through and find pixelSizeRequests
                    foreach(this.children) ::(index, child) {
                        @p = child.pixelSizeRequest;
                        if (p != empty) 
                            totalVerticalAvailable -= p->floor;
                        
                        if (child.sizeRequest != empty)
                            freeSpaceFraction -= child.sizeRequest;
                        
                        if (p == empty && child.sizeRequest == empty) ::<= {
                            empties[index] = true;
                            emptyCount += 1;
                        }
                    }                

                    @:childBox = {...this.childSpace};

                    foreach(this.children) ::(index, child) {
                        @p = child.pixelSizeRequest;
                        if (p != empty) ::<= {
                            childBox.height = p->floor;
                        } else ::<= {
                            if (empties[index] != empty) 
                                childBox.height = ((1/emptyCount) * freeSpaceFraction * totalVerticalAvailable)->floor
                            else
                                childBox.height = (child.sizeRequest * totalVerticalAvailable)->floor
                        }
                        
                        child.move(x: childBox.x, y: childBox.y);
                        child.resize(width:childBox.width, height:childBox.height);
                        
                        childBox.y += childBox.height
                    }
                }
            }
        }
    );
    
    @Horizontal = class(
        name: "game.Layout.Horizontal",
        inherits : [Item],
        define::(this) {
            this.interface = {
                layout ::(items) {
                    foreach(items) ::(index, item) {
                        this.attach(child:item);
                    }
                    return this;
                },
                onRecalculate :: {
                    @totalHorizontalAvailable = this.childSpace.width;
                    @empties = [];
                    @emptyCount = 0;
                    @freeSpaceFraction = 1;

                    
                    // first iterate through and find pixelSizeRequests
                    foreach(this.children) ::(index, child) {
                        @p = child.pixelSizeRequest;
                        if (p != empty) 
                            totalHorizontalAvailable -= p->floor;

                        if (child.sizeRequest != empty)
                            freeSpaceFraction -= child.sizeRequest;
                        
                        if (p == empty && child.sizeRequest == empty) ::<= {
                            empties[index] = true;
                            emptyCount += 1;
                        }
                        
                    }                

                    @:childBox = {...this.childSpace};

                    foreach(this.children) ::(index, child) {
                        @p = child.pixelSizeRequest;
                        if (p != empty) ::<= {
                            childBox.width = p->floor;
                        } else ::<= {
                            if (empties[index] != empty) 
                                childBox.width = ((1/emptyCount) * freeSpaceFraction * totalHorizontalAvailable)->floor
                            else
                                childBox.width = (child.sizeRequest * totalHorizontalAvailable)->floor
                        }
                        
                        child.move(x: childBox.x, y: childBox.y);
                        child.resize(width:childBox.width, height:childBox.height);
                        
                        childBox.x += childBox.width
                    }
                }
            }
        }
    );    
    return {
        Item : Item,
        Vertical : Vertical,
        Horizontal : Horizontal
    }
}



return ::<= {
    @:roots = [];
    return {
        LerpAngle ::(start, end, amount) {
            @:dt = lerp_repeat(t:end - start, m:360);
            return ray.Lerp(start, end:start + (if(dt > 180) dt - 360 else dt), amount);
        },    
        Log : Log,
        Node : Node,
        Entity : Entity,
        Timer : Timer,
        StateMachine : StateMachine,
        Layout : Layout,
        StartLoop ::{
            forever ::{
                foreach(roots) ::(i, root) {
                    root.updateTransform_();
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
                
                if (toDestroy) ::<= {
                    foreach(toDestroy) ::(node, v) {
                        node.finalize_();
                    }
                    toDestroy = empty;
                }
            }
        },
        roots : roots,
    }
}
