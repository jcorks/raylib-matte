@:ray    = import(module:"raylib.mt");
@:class  = import(module:"Matte.Core.Class");


@:Resources = class(
    name: "Resources",
    define::(this) {
        // Sounds that can be aliased with ray.LoadSoundAlias
        @:sounds = {
            shoot:          ray.LoadSound(fileName: "resources/shoot.wav"),
            loaded:         ray.LoadSound(fileName: "resources/loaded.wav"),
            upgraded:       ray.LoadSound(fileName: "resources/upgraded.wav"),
            enemyHit:       ray.LoadSound(fileName: "resources/impact.wav"),
            enemyDeath:     ray.LoadSound(fileName: "resources/enemyDeath.wav")
        };

        @:music = {
            main:          ray.LoadMusicStream(fileName: "resources/bgm.mp3")
        };

        this.interface = {
            sounds: {get ::<- sounds},
            music: {get ::<- music},

            // This should be called when the game ends
            unloadAll :: {
                foreach(sounds) :: (name, sound) {
                    ray.UnloadSound(sound: sound);
                }

                foreach(music) :: (name, music) {
                    ray.UnloadMusicStream(music: music);
                }
            }
        };
    }
);


return Resources.new();
