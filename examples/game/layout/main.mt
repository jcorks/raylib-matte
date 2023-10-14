/*
    raymatte: Layout Example

    Layouts are intended for dynamic use of UIs, similar
    to establish UI engines. The functionality provided here 
    is considered the "bare essentials" to make UI layouts 
    sensitive to input sizing without requiring explicit 
    placement or anchors.
    
    In addition to the game module's Layouts, this example
    uses Layouts in conjunction with the raygui module.

*/


@:game  = import(module:"game.mt");
@:ray   = import(module:"raylib.mt");
@:gui   = import(module:"raygui.mt");
@:class = import(module:"Matte.Core.Class");


// Panel using the raygui module and Layouts.
@:Panel = class(
    inherits : [game.Layout.Item],
    define::(this) {
        @text_;
        
        this.constructor = ::{
            // Set an inherent default margin.
            // This is useful because a later setup() 
            // call can override this default.
            this.setup(
                margin : 10
            );
        }
        
        this.interface = {
            // convenience function that sets the text and 
            // returns "this" for constructor chaining.
            setText::(text) {
                text_ = text;
                return this;
            },
        
            onDraw ::{
                // simply draw the GUI with the content space 
                // allocated to the widget.
                gui.GuiPanel(bounds:this.contentSpace, text:text_);
            }
        }
    }
);  


// Button using raygui and Layouts.
@:Button = class(
    inherits : [game.Layout.Item],
    define::(this) {
        @pressed = 0;
        @text_;
        
        this.constructor = ::{
            // Set an inherent default margin.
            // This is useful because a later setup() 
            // call can override this default.
            this.setup(
                margin : 10
            );
        }
        
        this.interface = {
            // convenience function that sets the text and 
            // returns "this" for constructor chaining.
            setText::(text) {
                text_ = text;
                return this;
            },
        
            // Add a press detection routine
            onStep ::{
                if (pressed)
                    print(message:"Hello! from: " + text_);
            },
            
            
            // simply draw using raygui
            onDraw ::{
                pressed = gui.GuiButton(bounds:this.contentSpace, text:text_);
            }
        }
    }
);  


ray.InitWindow(width: 800, height: 480, title: 'Layout Test');



// Layouts allow for complete construction with 
// one call, letting users visually see how 
// its constructed and provide overrides as 
// needed.
//
// NOTE: if size requests arent set, all siblings 
// equally split the parent's allotted space after 
// other sibling's size requests.
@:box = game.Layout.Horizontal.new().layout(
    items : [
        game.Layout.Vertical.new().setup(
            margin: 20
        ).layout(items : [
        
            Panel.new().setText(text: "Im a panel!"),
            game.Layout.Vertical.new().setup(
                margin: 10
            ).layout(items : [
                Button.new().setText(text: "Button0"),
                Button.new().setup(
                    // pixel size requests override regular sizeRequests.
                    pixelSizeRequest : 50 
                ).setText(text: "Button1"),
                Button.new().setText(text: "Button2")
            ]),
        ]),
        Button.new().setup(
            sizeRequest: 0.5 // uses half of the parent space available.
        ).setText(text: "Im large!")
    ]
)

box.move(
    x: 0,
    y: 0
);
// lets have the top level box take up the entire screen.
// HINT: try experimenting with this to see the flexibility of 
// dynamic UI layouts!
box.resize(
    width:ray.GetRenderWidth(),
    height:ray.GetRenderHeight()
);

// Attach root and start loop
game.GetRoot().attach(child:box);
game.StartLoop(allowExit:true);
