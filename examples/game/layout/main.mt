/*
Copyright (c) 2023 Johnathan Corkery

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


@:game  = import(:"game.mt");
@:ray   = import(:"raylib.mt");
@:gui   = import(:"raygui.mt");
@:class = import(:"Matte.Core.Class");


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
                    print(:"Hello! from: " + text_);
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
        
            Panel.new().setText(: "Im a panel!"),
            game.Layout.Vertical.new().setup(
                margin: 10
            ).layout(items : [
                Button.new().setText(: "Button0"),
                Button.new().setup(
                    // pixel size requests override regular sizeRequests.
                    pixelSizeRequest : 50 
                ).setText(: "Button1"),
                Button.new().setText(: "Button2")
            ]),
        ]),
        Button.new().setup(
            sizeRequest: 0.5 // uses half of the parent space available.
        ).setText(: "Im large!")
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
game.GetRoot().attach(:box);
game.StartLoop(allowExit:true);
