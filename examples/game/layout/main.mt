@:game  = import(module:"game.mt");
@:ray   = import(module:"raylib.mt");
@:gui   = import(module:"raygui.mt");
@:class = import(module:"Matte.Core.Class");



@:Panel = class(
    inherits : [game.Layout.Item],
    define::(this) {
        @text_;
        
        this.constructor = ::{
            this.setup(
                margin : 10
            );
        }
        
        this.interface = {
            setText::(text) {
                text_ = text;
                return this;
            },
        
            
        
            onDraw ::{
                gui.GuiPanel(bounds:this.contentSpace, text:text_);
            }
        }
    }
);  

@:Button = class(
    inherits : [game.Layout.Item],
    define::(this) {
        @pressed = 0;
        @text_;
        
        this.constructor = ::{
            this.setup(
                margin : 10
            );
        }
        
        this.interface = {
            setText::(text) {
                text_ = text;
                return this;
            },
        
            onStep ::{
                if (pressed)
                    print(message:"Hello! from: " + text_);
            },
            
        
            onDraw ::{
                pressed = gui.GuiButton(bounds:this.contentSpace, text:text_);
            }
        }
    }
);  


ray.InitWindow(width: 800, height: 480, title: 'Layout Test');




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
                    pixelSizeRequest : 50 // override default
                ).setText(text: "Button1"),
                Button.new().setText(text: "Button2")
            ]),
        ]),
        Button.new().setup(
            sizeRequest: 0.5
        ).setText(text: "Im large!")
    ]
)
box.move(
    x: 0,
    y: 0
);
box.resize(
    width:ray.GetRenderWidth(),
    height:ray.GetRenderHeight()
);

game.roots->push(value:box);
game.StartLoop();
