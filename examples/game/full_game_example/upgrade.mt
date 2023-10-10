@:game   = import(module:"game.mt");
@:ray    = import(module:"raylib.mt");
@:class  = import(module:"Matte.Core.Class");
@:Shooter = import(module:"shooter.mt"); 
@:res    = import(module:"resources.mt");


// WHere the table should begin, vertically
@:DISPLAY_Y = 70;

// Size of the main upgrade title
@:TITLE_FONT_SIZE = 50;

// Width of a row in pixels
@:ROW_WIDTH = 400;

// Height of a row in pixels
@:ROW_HEIGHT = 55;

// Padding between items in a row.
@:ROW_ITEM_PADDING = 4;

// Main display font size for a row item.
@:ROW_FONT_SIZE = 24;

// Size of the block icon
@:ROW_ICON_SIZE = 40;

// Width of the display portion of the row.
@:ROW_NAME_WIDTH = 200;

// space between rows
@:ROW_SPACING = 5;




// Space between each rank notch
@:RANK_GAP = 2;

// Size of the rank notch
@:RANK_WIDTH = 10;
@:RANK_HEIGHT = 30;

// Max number of notches before defaulting to text display.
@:MAX_RANK = 10;

@:UpgradeWindowRow = class(
    name : "UpgradeWindowRow",
    inherits : [game.Entity],
    define::(this) {
    
        // draws the ranks. If 10 or below, it is drawn as notches
        @:drawRank ::(pen, rank) {
            if (rank < MAX_RANK) ::<= {
                // pen is middled, so move it to top left
                pen.y -= RANK_HEIGHT / 2;
                for(0, rank) ::(i) {
                    ray.DrawLineEx(
                        startPos:pen,
                        endPos: {
                            x: pen.x,
                            y: pen.y + RANK_HEIGHT
                        },
                        thick: RANK_WIDTH,
                        color: ray.GREEN
                    );        
                    pen.x += RANK_WIDTH + RANK_GAP;
                }
                
                // mark empty ranks
                for(rank, 10) ::(i) {
                    ray.DrawLineEx(
                        startPos:pen,
                        endPos: {
                            x: pen.x,
                            y: pen.y + RANK_HEIGHT
                        },
                        thick: RANK_WIDTH,
                        color: ray.BLACK
                    );        
                    pen.x += RANK_WIDTH + RANK_GAP;
                }    
            // Whoa! you ranked highly. That's crazy...
            } else ::<= {
                @:rankDisplay = " x" + rank + " ";
                @textSize = ray.MeasureTextEx(
                    font: ray.GetFontDefault(),
                    text: rankDisplay,
                    fontSize : ROW_FONT_SIZE,
                    spacing: 0
                );

                ray.DrawText(
                    posX: pen.x,
                    posY: pen.y - textSize.y / 2,
                    fontSize: ROW_FONT_SIZE,
                    color: ray.GREEN
                )
            }        
        }
    
        @index_;
        @display_;
        @onSelect_;
        @rank_;
        @hovered = false;
        @color = {r:128, g:128, b:128, a:64};
        @targetAlpha = 64;
        @selfRec = {
            width: ROW_WIDTH,
            height: ROW_HEIGHT,
            x: 0,
            y: 0
        }
        this.interface = {
            setup ::(
                y,
                index,
                display,
                onSelect,
                rank
            ) {
                selfRec.x = (ray.GetRenderWidth() - ROW_WIDTH) / 2;
                selfRec.y = y;
                index_ = index;
                display_ = display;
                onSelect_ = onSelect;
                rank_ = rank;
                return this;
            },
            
            onStep ::{
                hovered = (ray.CheckCollisionPointRec(
                    point:ray.GetMousePosition(),
                    rec: selfRec
                ));
                
                if (hovered) ::<= {
                    if (ray.IsMouseButtonPressed(button:ray.MOUSE_BUTTON_LEFT))
                        onSelect_();
                }
                
                
                // from 1 to 9
                if (ray.IsKeyPressed(key:(ray.KEY_ONE) + (index_-1)))
                    onSelect_();
                
                
                targetAlpha = if (hovered) 128 else 64;
            },
            
            onDraw ::{
                @delta = ray.GetFrameTime();
                color.a = ray.Lerp(start:color.a, end:targetAlpha, amount:7 * delta);
                ray.DrawRectangleRec(
                    rec: selfRec,
                    color: color
                );

                // pen to track where we are drawing the 
                // UI in the row
                @pen = {x: selfRec.x, y: selfRec.y}
                
                
                // draw number button icon
                pen.x += ROW_ITEM_PADDING;
                pen.y += (ROW_HEIGHT - ROW_ICON_SIZE)/2
                @numberIconSize = ROW_ICON_SIZE;
                ray.DrawRectangleLines(
                    posX: pen.x,
                    posY: pen.y,
                    width : ROW_ICON_SIZE,
                    height : ROW_ICON_SIZE,
                    color : ray.WHITE
                );
                
                // icon number
                pen.x += ROW_ITEM_PADDING;
                ray.DrawText(
                    text:'' + (index_),
                    posX: pen.x + ROW_ITEM_PADDING,
                    posY: pen.y + ROW_ITEM_PADDING,
                    fontSize : 12,
                    color: ray.WHITE
                );
                
                
                
                
                
                // then draw the description
                pen.x += ROW_ICON_SIZE + ROW_ITEM_PADDING;
                @textSize = ray.MeasureTextEx(
                    font: ray.GetFontDefault(),
                    text: display_,
                    fontSize : ROW_FONT_SIZE,
                    spacing: 0
                );
                
                pen.y = selfRec.y + (ROW_HEIGHT - textSize.y) / 2;
                ray.DrawText(
                    text: display_,
                    posX: pen.x,
                    posY: pen.y,
                    fontSize: ROW_FONT_SIZE,
                    color: ray.WHITE
                );




                // finally draw the rank
                pen.x += ROW_NAME_WIDTH;
                pen.y = selfRec.y + ROW_HEIGHT/2;
                drawRank(pen, rank:rank_);
            }
        }
    }
);



return class(
    name : "Upgrade",
    inherits : [game.Node],
    define::(this) {
    
        @originY = DISPLAY_Y;
        @picked = false;

        // Resource prep
        @:soundUpgraded = res.sounds["upgraded"];

        @:addRow::(
            display => String,
            onSelect => Function,
            rank => Number
        ) {
            this.attach(
                child:UpgradeWindowRow.new().setup(
                    y: originY + this.children->size * (ROW_HEIGHT + ROW_SPACING),
                    index : this.children->size+1,
                    display,
                    onSelect,
                    rank
                )
            );
        }
        this.constructor = ::{
            addRow(
                display: "Cooldown",
                onSelect ::{ 
                    Shooter.getMain().rankCooldown += 1;
                    ray.PlaySound(sound: soundUpgraded);
                    picked = true;
                },
                rank : Shooter.getMain().rankCooldown
            );


            addRow(
                display: "Bullet Count",
                onSelect ::{ 
                    Shooter.getMain().rankCount += 1;
                    ray.PlaySound(sound: soundUpgraded);
                    picked = true;
                },
                rank : Shooter.getMain().rankCount
            );

            addRow(
                display: "Bullet Spread",
                onSelect ::{ 
                    Shooter.getMain().rankSpread += 1;
                    ray.PlaySound(sound: soundUpgraded);
                    picked = true;
                },
                rank :  Shooter.getMain().rankSpread
            );

            addRow(
                display: "Fire rate",
                onSelect ::{ 
                    Shooter.getMain().rankFirerate += 1;
                    ray.PlaySound(sound: soundUpgraded);
                    picked = true;
                },
                rank : Shooter.getMain().rankFirerate
            );


            addRow(
                display: "Knockback",
                onSelect ::{ 
                    Shooter.getMain().rankKnockback += 1;
                    ray.PlaySound(sound: soundUpgraded);
                    picked = true;
                },
                rank : Shooter.getMain().rankKnockback
            );

            addRow(
                display: "Range",
                onSelect ::{ 
                    Shooter.getMain().rankRange += 1;
                    ray.PlaySound(sound: soundUpgraded);
                    picked = true;
                },
                rank : Shooter.getMain().rankRange
            );



        }
        
        @:titleDisplay = "Choose an Upgrade";
        @:titleSize = ray.MeasureTextEx(
            font: ray.GetFontDefault(),
            fontSize: TITLE_FONT_SIZE,
            spacing: 4,
            text:titleDisplay
        );
        this.interface = {
            shouldContinue : {
                get ::<- picked
            },
            
            onDraw ::{
                ray.DrawText(
                    posX: (ray.GetRenderWidth() - titleSize.x) / 2,
                    posY: DISPLAY_Y - titleSize.y,
                    color: ray.GRAY,
                    text: titleDisplay,
                    fontSize: TITLE_FONT_SIZE
                );
            }
        }   
    }
);
