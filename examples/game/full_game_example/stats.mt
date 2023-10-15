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
@:class  = import(module:"Matte.Core.Class");



@:Stat = class(
    name : "Stat",
    define::(this) {
        @name_;
        @formula_;
        @value;
        @rank = 0;
        this.interface = {
            setup::(
                name => String,
                formula => Function
            ) {
                formula_ = formula;
                value = formula(rank);
                name_ = name;
                return this;
            },
            
            rankUp ::{
                rank += 1;
                value = formula_(rank);
            },
            
            value : {
                get ::<- value
            },
            
            rank : {
                get ::<- rank
            },
            
            name : {
                get ::<- name_
            }   
        }
    }
);


@Stats = {
    MAX_SHOTS : 0,
    COOLDOWN : 1,
    FIRERATE : 2,
    KNOCKBACK : 3,
    SPEED : 4,
    CHARGE_RATE : 5,
    ACCURACY : 6,
    CHARGED_INTENSITY : 7,
    //SPREAD : 8,
    list : []
}


Stats.list[Stats.MAX_SHOTS] = Stat.new().setup(
    name: "Bullet Count",
    formula ::(rank) <- 4 + rank * 3
);


Stats.list[Stats.COOLDOWN] = Stat.new().setup(
    name: "Cooldown",
    formula ::(rank) <- 1.5 * (0.7 ** rank)
);

Stats.list[Stats.FIRERATE] = Stat.new().setup(
    name: "Firerate",
    formula ::(rank) <- 0.1 * (0.7 ** rank)
);

Stats.list[Stats.KNOCKBACK] = Stat.new().setup(
    name: "Knockback",
    formula ::(rank) <- 0.05 * (1.4 ** rank) - 0.01
);

Stats.list[Stats.CHARGE_RATE] = Stat.new().setup(
    name: "Charge rate",
    formula ::(rank) <- 2 * (1.23 ** rank)
);

// The most OP stat has been removed... Sorry gamers....
/*
Stats.list[Stats.SPREAD] = Stat.new().setup(
    name: "Bullet Spread",
    formula ::(rank) <- rank
);
*/

Stats.list[Stats.SPEED] = Stat.new().setup(
    name: "Bullet Speed",
    formula ::(rank) <- 7 + (1.3 ** rank)
);

Stats.list[Stats.ACCURACY] = Stat.new().setup(
    name: "Bullet Accuracy",
    formula ::(rank) <- 30 * (0.7 ** rank)
);

Stats.list[Stats.CHARGED_INTENSITY] = Stat.new().setup(
    name: "Charged AoE",
    formula ::(rank) <- (1.2 ** rank)
);

return Stats;


