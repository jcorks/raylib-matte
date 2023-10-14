@:game   = import(module:"game.mt");
@:ray    = import(module:"raylib.mt");
@:class  = import(module:"Matte.Core.Class");
@:Shooter = import(module:"shooter.mt"); 
@:res    = import(module:"resources.mt");
@:Stats  = import(module:"stats.mt");


@: HOW_TO_PLAY_WIDTH  = 500;
@: HOW_TO_PLAY_HEIGHT = 350;

@:Rectangle = class(
    name: "HowToPlay.Rectangle",
    inherits : [game.Layout.Item],
    define::(this) {
        this.constructor = ::{
            this.setup(
                margin: 5
            );
        }
        
        this.interface = {
            onDraw ::{
                @:content = this.contentSpace;
                ray.DrawRectangleLinesEx(
                    rec:content,
                    lineThick: 2,
                    color:ray.WHITE
                );
            }            
        }
    }
);

@:Label = class(
    name: "HowToPlay.Label",
    inherits : [game.Layout.Item],
    define::(this) {
        @:FONT_SIZE = 30;
        @text = '';
        @textSize = {};
        
        
        this.interface = {
            setText::(display) {
                text = display;
                textSize = ray.MeasureTextEx(
                    font: ray.GetFontDefault(),
                    text,
                    fontSize: FONT_SIZE,
                    spacing: 3
                );
                return this;
            },
            
            
            onDraw ::{
                @:content = this.contentSpace;
                ray.DrawText(
                    text,
                    posX: content.x + content.width/2  - textSize.x/2,
                    posY: content.y + content.height/2 - textSize.y/2,
                    fontSize: FONT_SIZE,
                    color: ray.WHITE
                );
            }
        }
    }
);


@:createSpacer :: <- game.Layout.Item.new();

return class(
    name: "HowToPlay",
    inherits : [game.Layout.Vertical],
    define::(this) {
        this.constructor = ::{
            this.layout(items:[
                // title
                Label.new().setup(
                    sizeRequest: 0.2
                ).setText(display:"How to play (mouse)"),
                
                
                // mouse button row
                game.Layout.Horizontal.new().setup(
                    sizeRequest:0.3
                ).layout(items: [
                    Label.new().setup(sizeRequest:0.3).setText(display:"Shoot -"),
                    Rectangle.new(),
                    Rectangle.new(),
                    Label.new().setup(sizeRequest:0.3).setText(display:"- Charge"),
                ]),
                
                // mouse base
                game.Layout.Horizontal.new().layout(items: [
                    createSpacer().setup(sizeRequest:0.3), 
                    Rectangle.new(),
                    createSpacer().setup(sizeRequest:0.3)
                ]),
                
                // continue text
                Label.new().setup(sizeRequest: 0.1).setText(display:"Left-click to continue")
            ]);
            
            // center it and set the size
            this.move(
                x: ray.GetRenderWidth()  / 2 - HOW_TO_PLAY_WIDTH/2,
                y: ray.GetRenderHeight() / 2 - HOW_TO_PLAY_HEIGHT/2
            );
            
            this.resize(
                width: HOW_TO_PLAY_WIDTH,
                height: HOW_TO_PLAY_HEIGHT
            );
        }  
        

        
        this.interface = {
            onDraw ::{
                @:content = this.contentSpace;
                @bg = {...ray.BLACK};
                bg.a = 128;
                ray.DrawRectangleRec(
                    rec:content,
                    color: bg
                );
            }            
        }        
        
    }
);
