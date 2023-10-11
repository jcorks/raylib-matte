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
    SPREAD : 6,
    ACCURACY : 7,
    CHARGED_INTENSITY : 8,
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
    formula ::(rank) <- 0.05 * (1.4 ** rank) - 0.03
);

Stats.list[Stats.CHARGE_RATE] = Stat.new().setup(
    name: "Charge rate",
    formula ::(rank) <- 4 * (0.9 ** rank)
);


Stats.list[Stats.SPREAD] = Stat.new().setup(
    name: "Bullet Spread",
    formula ::(rank) <- rank
);

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


