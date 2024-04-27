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
                ).setText(:"How to play (mouse)"),
                
                
                // mouse button row
                game.Layout.Horizontal.new().setup(
                    sizeRequest:0.3
                ).layout(items: [
                    Label.new().setup(sizeRequest:0.3).setText(:"Shoot -"),
                    Rectangle.new(),
                    Rectangle.new(),
                    Label.new().setup(sizeRequest:0.3).setText(:"- Charge"),
                ]),
                
                // mouse base
                game.Layout.Horizontal.new().layout(items: [
                    createSpacer().setup(sizeRequest:0.3), 
                    Rectangle.new(),
                    createSpacer().setup(sizeRequest:0.3)
                ]),
                
                // continue text
                Label.new().setup(sizeRequest: 0.1).setText(:"Left-click to continue")
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
