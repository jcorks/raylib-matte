@:game   = import(module:"game.mt");
@:ray    = import(module:"raylib.mt");
@:class  = import(module:"Matte.Core.Class");
@:Shooter = import(module:"shooter.mt"); 
@:res    = import(module:"resources.mt");
@:Stats  = import(module:"stats.mt");


// WHere the table should begin, vertically
@:DISPLAY_Y = 70;

// Size of the main upgrade title
@:TITLE_FONT_SIZE = 50;

// Width of a row in pixels
@:ROW_WIDTH = 430;

// Height of a row in pixels
@:ROW_HEIGHT = 70;

// Padding between items in a row.
@:ROW_ITEM_PADDING = 4;

// Main display font size for a row item.
@:ROW_FONT_SIZE = 24;

// Size of the block icon
@:ROW_ICON_SIZE = 40;

// Width of the display portion of the row.
@:ROW_NAME_WIDTH = 200;





// Space between each rank notch
@:RANK_GAP = 2;

// Size of the rank notch
@:RANK_WIDTH = 10;
@:RANK_HEIGHT = 30;

// Max number of notches before defaulting to text display.
@:MAX_RANK = 10;

// Number of upgrades choosable
@:UPGRADE_COUNT = 4;



// Shows a number key to press for the option
@:UpgradeNumberIcon = class(
    name : "UpgradeNumberIcon",
    inherits : [game.Layout.Item],
    define::(this) {
        @index_;
        this.constructor = ::{
            this.setup(
                pixelSizeRequest: ROW_ICON_SIZE
            );
        }
    
        this.interface = {
            setNumber ::(index) {
                index_ = index; 
                return this;
            },
            onDraw::{
                @:content = this.contentSpace;

                @numberIconSize = ROW_ICON_SIZE;
                ray.DrawRectangleLines(
                    posX: content.x,
                    posY: content.y,
                    width : content.width,
                    height : content.height,
                    color : ray.WHITE
                );
                    
                // icon number
                ray.DrawText(
                    text:'' + (index_),
                    posX: content.x + ROW_ITEM_PADDING,
                    posY: content.y + ROW_ITEM_PADDING,
                    fontSize : 12,
                    color: ray.WHITE
                );
            }    
        }
    }
);

@:UpgradeRowLabel = class(
    name : "UpgradeRowLabel",
    inherits : [game.Layout.Item],
    define::(this) {
        @display_;
        @textSize;
        
        this.constructor = ::{
            this.setup(
                margin: 10
            )
        };
        
        this.interface = { 
            setText ::(display) {
                display_ = display;
                
                textSize = ray.MeasureTextEx(
                    font: ray.GetFontDefault(),
                    text: display_,
                    fontSize : ROW_FONT_SIZE,
                    spacing: 0
                );
                                
                return this;
            },
            onDraw ::{
                @:content = this.contentSpace;


                
                ray.DrawText(
                    text: display_,
                    posX: content.x,
                    posY: content.y + content.height/2 - textSize.y/2,
                    fontSize: ROW_FONT_SIZE,
                    color: ray.WHITE
                );                
            }
        }    
    }
);


@UpgradeRowRank = class(
    name : "UpgradeRowRank",
    inherits : [game.Layout.Item],
    define ::(this) {
        @rank;
        this.interface = {
            setRank::(value) {
                rank = value
                return this;
            },
            onDraw ::{
                @content = {...this.contentSpace};
                if (rank < MAX_RANK) ::<= {
                    // pen is middled, so move it to top left
                    for(0, rank) ::(i) {
                        ray.DrawLineEx(
                            startPos:content,
                            endPos: {
                                x: content.x,
                                y: content.y + content.height
                            },
                            thick: RANK_WIDTH,
                            color: ray.GREEN
                        );        
                        content.x += RANK_WIDTH + RANK_GAP;
                    }
                    
                    // mark empty ranks
                    for(rank, 10) ::(i) {
                        ray.DrawLineEx(
                            startPos:content,
                            endPos: {
                                x: content.x,
                                y: content.y + content.height
                            },
                            thick: RANK_WIDTH,
                            color: ray.BLACK
                        );        
                        content.x += RANK_WIDTH + RANK_GAP;
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
                        text: rankDisplay,
                        posX: content.x,
                        posY: content.y + content.height/2 - textSize.y / 2,
                        fontSize: ROW_FONT_SIZE,
                        color: ray.GREEN
                    )
                }                    
            }        
        }
    }
);


@:UpgradeWindowRow = class(
    name : "UpgradeWindowRow",
    inherits : [game.Layout.Horizontal],
    define::(this) {
        @index_;
        @display_;
        @onSelect_;
        @rank_;
        @hovered = false;
        @color = {r:128, g:128, b:128, a:64};
        @targetAlpha = 64;


        this.interface = {
            setData::(index, upgrade, onSelect) {
                index_ = index;
                onSelect_ = onSelect;
                this.setup(
                    pixelSizeRequest : ROW_HEIGHT,
                    margin : 5,
                    padding : 10
                );
                this.layout(
                    items : [
                        UpgradeNumberIcon.new().setNumber(index),
                        UpgradeRowLabel.new().setup(sizeRequest: 0.7).setText(display:upgrade.name),
                        UpgradeRowRank.new().setup(sizeRequest: 0.3).setRank(value:upgrade.rank)
                    ]
                )
                return this;
            },
            
            onStep ::{
                hovered = (ray.CheckCollisionPointRec(
                    point:ray.GetMousePosition(),
                    rec: this.contentSpace
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
                @content = this.contentSpace;
                @delta = ray.GetFrameTime();
                color.a = ray.Lerp(start:color.a, end:targetAlpha, amount:7 * delta);
                ray.DrawRectangleRec(
                    rec: content,
                    color: color
                );
            }
        }
    }
);


@:UpgradeTitleLabel = class(
    name: "UpgradeTitleLabel",
    inherits : [game.Layout.Item],
    define::(this) {
        
        @:titleDisplay = "Choose an Upgrade";
        @:titleSize = ray.MeasureTextEx(
            font: ray.GetFontDefault(),
            fontSize: TITLE_FONT_SIZE,
            spacing: 4,
            text:titleDisplay
        );    
    
        this.constructor = ::{
            this.setup(
                pixelSizeRequest : TITLE_FONT_SIZE + 10,
                margin: 10
            );
        }
    
        this.interface = {
            onDraw ::{
                @content = this.contentSpace;
                ray.DrawText(
                    posX: content.x + content.width / 2 - titleSize.x / 2,
                    posY: content.y + content.height / 2 - titleSize.y / 2,
                    color: ray.GRAY,
                    text: titleDisplay,
                    fontSize: TITLE_FONT_SIZE
                );                
            }
        }    
    }
);


return class(
    name : "Upgrade",
    inherits : [game.Layout.Vertical],
    define::(this) {
    
        @picked = false;

        // Resource prep
        @:soundUpgraded = res.sounds["upgraded"];

        @:newRow::(upgrade, index) {
            return UpgradeWindowRow.new().setData(
                upgrade,
                index,
                onSelect ::{
                    upgrade.rankUp();
                    ray.PlaySound(sound: soundUpgraded);
                    picked = true;
                    breakpoint();                    
                }
            )
        }
        this.constructor = ::{
            this.move(
                x:ray.GetRenderWidth()/2 - ROW_WIDTH/2, 
                y:50
            );
            this.resize(
                width: ROW_WIDTH,
                height: ray.GetRenderHeight()
            );            
            

            @upgrades = {...Stats.list};
            @:pickOneUpgrade :: {
                @index = (Number.random() * (upgrades->size))->floor
                @upgrade = upgrades[index];
                upgrades->remove(key:index);
                return upgrade;
            }

            this.layout(
                items : [
                    UpgradeTitleLabel.new(),
                    newRow(upgrade:pickOneUpgrade(), index:1),
                    newRow(upgrade:pickOneUpgrade(), index:2),
                    newRow(upgrade:pickOneUpgrade(), index:3),
                    newRow(upgrade:pickOneUpgrade(), index:4)
                ]
            );
            
        }

        this.interface = {
            shouldContinue : {
                get ::<- picked
            },
        }   
    }
);
