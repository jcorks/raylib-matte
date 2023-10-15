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
