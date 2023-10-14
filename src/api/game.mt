/////////////////////////
/*
The raylib-matte Game Extension Library (game.mt)

The game extension library is split into classes.
Any relevent documentation will be commented with 
slash-star comments

NOTE;
Functions that are not meant to be called by user code 
and do not have a stable interface are suffixed with _
or have no slash-star comments.


*/
/////////////////////////

@:ray = import(module:"raylib.mt");
@:class = import(module:"Matte.Core.Class");
@:EventSystem = import(module:"Matte.Core.EventSystem");

@toDestroy = empty;
/*
    Class: Game.Node
   
    A generic node.
    Like in game engines, nodes are the basic building 
    blocks of a scene. On its own, a Node is just 
    organizational, but the useful tools inherit from 
    this class.

    Nodes also can generate their own events to which 
    user code can respond, as they inherit from 
    Matte.Core.EventSystem (https://github.com/jcorks/matte/blob/main/src/rom/core/eventsystem.mt)

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
                The child is added at the end, meaning it will 
                be the last child of this Node to be stepped and 
                drawn.
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
                The child is added at the start, meaning it will 
                be the first child of this Node to be stepped and 
                drawn.
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
    Class: Game.Entity
   
    A Game.Node that responds to a 2D or 3D environment. allowing
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
            @globalPosition;
            
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
                        when(globalPosition != empty) globalPosition;
                        globalPosition = ray.Vector3Transform(v:ray.Vector3Zero(), mat:matrix);
                        return globalPosition;
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
                        globalPosition = empty;
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
    Class: Game.StateMachine
   
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


/*
    Class: Game.Timer 
    
    Provides a convenient way to work with times and timeouts.
    Timer utilizes the base class EventSystem to emit the "onTimeout"
    event when a timer expires.
*/
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
            /*
                Setter / Getter for if this timer automatically 
                resets itself from the start after expiring.
            */
            endless : {
                get ::<- endless,
                set ::(value) <- endless = value
            },
        
            /*
                Starts the timer instance, emitting an "onTimeout"
                event once the "seconds" seconds has elapsed.
            */
            start ::(seconds) {
                duration = seconds;
                start = ray.GetTime();
                active = true;
            },

            /*
                Getter for the amount of seconds that remain until 
                the timer expires.
            */            
            remaining : {
                get ::{
                    when(freezeRemaining) freezeRemaining;
                    @:diff = ray.GetTime() - start;
                    when (diff > duration) 0;
                    return duration - diff;
                }   
            },
            
            
            /*
                Getter for whether the timer is actively recording 
                any time.
            */
            active : {
                get ::<- active
            },
            
            
            /*
                Pauses the timer.
            */
            pause ::{
                when(freezeRemaining != empty) empty;
                freezeRemaining = this.remaining;
            },
            
            /*
                Resumes the timer from the paused state.
            */
            resume ::{
                when(freezeRemaining == empty) empty;
                start = ray.GetTime() - (duration - freezeRemaining);
                freezeRemaining = empty;
            },
            
            /*
                Stops the timer and makes it inactive.
            */
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


/*
    Singleton: Game.Log
    Log is not a class, but an instance to be used 
    immediately without instantiation.
    
    It allows for quick-and-dirty display of strings 
    on-screen above the rest of existing content 
    (its always drawn last).

*/

@:Log = class(
    name : 'Game.Log',
    define::(this) {
        @display = [];
        @:fontSize = 24;
        @baseHeight = 0;
        @:bgColor = {r:32, g:32, b:32, a:255 * 0.8};
        this.interface = {
            /*
                Setter / Getter for the display array.
                "display" is an array of strings, each drawn 
                serially from the top left of the screen.
                The array may be modified in-place or replaced 
                entirely.
            */
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




/*
    Namespace: Game.Layout
    
    Layout contains the building blocks for a basic 
    layout engine, which controls the spacings of 2D
    elements in a reactive, hierarchical way.
    
    The namespace consists of 3 classes.

*/
@:Layout = ::<= {

    /*
        Class: Game.Layout.Item
    
        Layout Items are the building blocks of the layout engine.
        Each Item is organized in 2D space by being given a 
        space (rectangle) to exist and place child content,
        all while taking into account margins and padding.
        Items can also make requests to parent Horizontal or 
        Vertical layouts to better position them in space.
    */
    @Item = class(
        name: "Game.Layout.Item",
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
                    Sets a new set of spacing rules for this Item.
                    The inputs have the following meanings:
                    
                    - margin: the distance from the donated space that this item 
                              may have its content reside. This is a single-number input 
                              that uniformly establishes boundaries on each side

                    - padding: the distance from the content space that this item 
                               may have its child(ren) reside. This is a single-number input 
                               that uniformly establishes boundaries on each side

                    - marginOffset: a more advanced alternative to "margin" that establishes 
                                    top, left, right, and bottom offsets to the margin as a Rectangle, allowing for 
                                    more dynamic and specific setups. These are offsets from the parent space.
                                    This is prioritized over "margin" if both are specified.

                    - paddingOffset: a more advanced alternative to "padding" that establishes 
                                     top, left, right, and bottom offsets to the padding as a Rectangle, allowing for 
                                     more dynamic and specific setups. These are offsets from the parent space.
                                     This is prioritized over "padding" if both are specified.
                                     
                    - sizeRequest: When children of Horizontal or Vertical layouts, this specifies 
                                   how much space this Item should be donated of available size remaining 
                                   in the parent. This is a number expressed as a fraction [0, 1] of how 
                                   much space it should take in the direction of the layout. When calculated,
                                   this fraction refers to the space available AFTER pixelSizeRequests are 
                                   calculated among siblings.
                                   
                    - pixelSizeRequest: When children of Horizontal or Vertical layouts, this specifies
                                        exactly how much pixel space to take up of the parent layout. This is 
                                        expressed as a single number.
                                        
                    

                    NOTE:
                    If no sizeRequest or pixelSizeRequest is present, 
                    the remaining available space is divided equally among
                    children.
                    
                    For convenience, this is returned, allowing for chaining 
                    on creation.
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
                
                /*
                    Establishes a new width and height for the Item,
                    which will modify the space available for use.
                    
                    This is only needed for toplevel items that do not 
                    have a parent item.
                */
                resize::(width, height) {
                    bounds_.width = width;
                    bounds_.height = height;
                    dirty = true;
                },
                
                /*
                    Establishes a new topleft for the Item,
                    which will modify the space available for use.
                    
                    This is only needed for toplevel items that do not 
                    have a parent item.
                */
                move::(x, y) {
                    bounds_.x = x;
                    bounds_.y = y;
                    dirty = true;
                },
                
                
                /*
                    Immediately recalculates the space available for this 
                    Item and requests children be recalculated.
                    
                    Under normal circumstances, this is called for you, but 
                    if changes arent immediate enough, this can be called 
                    by hand.
                */
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
                
                /*
                    Setter/Getter for the current pixelSizeRequest for the Item.
                    See setup() for more information.
                */
                pixelSizeRequest : {
                    set ::(value) {
                        pixelSizeRequest_ = value;
                        dirty = true;
                    },
                    get ::<- pixelSizeRequest_
                },
                
                /*
                    Setter/Getter for the current sizeRequest for the Item.
                    See setup() for more information.
                */
                sizeRequest : {
                    set ::(value) {
                        sizeRequest_ = value;
                        dirty = true;
                    },
                    get ::<- sizeRequest_
                },
                
                /*
                    Setter/Getter for the current marginOffset Rectangle for the Item.
                    See setup() for more information.
                */
                marginOffset : {
                    set ::(value => Object) {
                        marginOffset_ = {...value};
                        dirty = true;
                    },
                    get ::<- marginOffset_
                },
                
                /*
                    Setter/Getter for the current paddingOffset Rectangle for the Item.
                    See setup() for more information.
                */
                paddingOffset : {
                    set ::(value => Object) {
                        paddingOffset_ = {...value};
                        dirty = true;
                    },
                    get ::<- paddingOffset_
                },
                

                /*
                    Gets a space that is allotted for a children 
                    that may be used as a Rectangle.
                */
                childSpace : {
                    get ::<- innerSpace
                },
                
                /*
                    Gets a space that is allotted for this Item's content 
                    that may be used as a Rectangle.
                */
                contentSpace : {
                    get ::<- outerSpace
                },
                
                /*
                    Puts in a soft request that this Item needs to be recalculated
                    next frame.
                */
                needsRecalculation :: {
                    dirty = true
                },  
                
                /*
                    Virtual function to react to any time an Item has been given 
                    a new allotted spatial Rectangle for itself and children.
                */
                onRecalculate ::(){},
                
                
                
                
                // OVERRIDES node step, so do it right!
                step ::{                
                    if (dirty) ::<= {
                        this.recalculate();
                    }
                    
                    this.onStep();
                    foreach(this.children) ::(i, child) {
                        child.step();
                    }                    
                }
            }
        }
    );

    /*
        Class: Game.Layout.Vertical
        
        A type of Game.Layout.Item that holds children Items
        in a vertical layout. Vertical takes into account Item's
        size requests to distribute space among children properly.
    */
    @Vertical = class(
        name: "Game.Layout.Vertical",
        inherits : [Item],
        define::(this) {
            this.interface = {
                /*
                    Specifies the children for the Vertical layout and 
                    requests space recalculation. This is preferred over 
                    attaching children by hand because of the inherent 
                    recalculation request.
                */
                layout ::(items) {
                    foreach(items) ::(index, item) {
                        this.attach(child:item);
                    }
                    this.needsRecalculation();
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
    
    /*
        Class: Game.Layout.Horizontal
        
        A type of Game.Layout.Item that holds children Items
        in a horizontal layout. Horizontal takes into account Item's
        size requests to distribute space among children properly.
    */
    @Horizontal = class(
        name: "Game.Layout.Horizontal",
        inherits : [Item],
        define::(this) {
            this.interface = {
                /*
                    Specifies the children for the Horizontal layout and 
                    requests space recalculation. This is preferred over 
                    attaching children by hand because of the inherent 
                    recalculation request.
                */
                layout ::(items) {
                    foreach(items) ::(index, item) {
                        this.attach(child:item);
                    }
                    this.needsRecalculation();
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


/*
    Namespace: Game
    
    This is the main module thats returned.
    Along with acting as a namespace for all these 
    utilities, this section contains some standalone
    functions that may prove to be useful but dont 
    necessarily fit as part of their own classes

*/
@:Game = ::<= {
    @:root = Node.new();
    return {
        /*
            Correctly linearly interpolates between angles 
            without wrap-around.
        */
        LerpAngle ::(start, end, amount) {
            @:dt = lerp_repeat(t:end - start, m:360);
            return ray.Lerp(start, end:start + (if(dt > 180) dt - 360 else dt), amount);
        }, 
        /*
            Function that allows drawing of textures in 2D space 
            according to transforms, which is convenient for working 
            in 2D with Entities.
        */
        DrawSprite ::<= {
            @mat;
            @mesh;
            @model;
            @SPRITE_CAMERA = {
                position: {x:0, y:0, z:-1},
                target: {x:0, y:0, z:0},
                up : {x:0, y:-1, z:0},
                fovy : 400,
                projection : ray.CAMERA_ORTHOGRAPHIC
            }            
            return ::(transform, texture, tint) {
                if (mat == empty) ::<= {
                    mat = ray.LoadMaterialDefault();
                    mesh = ray.GenMeshPlane(width:1, length:1, resX: 1, resZ: 1);
                    model = ray.LoadModelFromMesh(mesh);
                };
                @m = ray.MatrixScale(
                    x: texture.width,
                    y: texture.height,
                    z:1
                );

                @ma = ray.MatrixRotate(
                    axis: {x:1, y:0, z:0},
                    angle: -90->asRadians
                );
                
                
                m = ray.MatrixMultiply(
                    right:m,
                    left:ma
                );
                
                SPRITE_CAMERA.fovy = ray.GetRenderHeight();
                SPRITE_CAMERA.target.x =  ray.GetRenderWidth()/2;
                SPRITE_CAMERA.target.y =  ray.GetRenderHeight()/2;
                

                SPRITE_CAMERA.position.x =  ray.GetRenderWidth()/2;
                SPRITE_CAMERA.position.y =  ray.GetRenderHeight()/2;
                
                ray.SetMaterialTexture(material:mat, mapType:ray.MATERIAL_MAP_ALBEDO, texture);
                if (tint != empty) 
                    ray.SetMaterialMapColor(material:mat, mapType:ray.MATERIAL_MAP_ALBEDO, color: tint)
                else
                    ray.SetMaterialMapColor(material:mat, mapType:ray.MATERIAL_MAP_ALBEDO, color: ray.WHITE);

                ray.BeginMode3D(camera:SPRITE_CAMERA);
                    ray.DrawMesh(
                        mesh,
                        material:mat,
                        transform: ray.MatrixMultiply(
                            right:transform,
                            left: m
                        )
                    );
                ray.EndMode3D();        
            }   
        },

        
        /* 
            Starts the main loop, which 
            updates roots regularly.
        */
            
        StartLoop ::(allowExit => Boolean) {
            {:::} {
                forever ::{
                    root.updateTransform_();
                    root.step();
                    ray.BeginDrawing();
                        ray.ClearBackground(color:ray.BLACK);
                        root.draw();
                        Log.draw();
                    ray.EndDrawing();
                    
                    if (toDestroy) ::<= {
                        foreach(toDestroy) ::(node, v) {
                            node.finalize_();
                        }
                        toDestroy = empty;
                    }
                    
                    if (allowExit && ray.WindowShouldClose())
                        send();
                }
            }
        },

        /*
            Gets the main root of Game module.
            Any child of the root will get stepped and 
            drawn.
        */
        GetRoot ::<- root,


        Log : Log,
        Node : Node,
        Entity : Entity,
        Timer : Timer,
        StateMachine : StateMachine,
        Layout : Layout,
    }
}
return Game;
