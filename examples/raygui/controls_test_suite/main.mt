/*******************************************************************************************
*
*   raygui - controls test suite
*
*   TEST CONTROLS:
*       - GuiDropdownBox()
*       - GuiCheckBox()
*       - GuiSpinner()
*       - GuiValueBox()
*       - GuiTextBox()
*       - GuiButton()
*       - GuiComboBox()
*       - GuiListView()
*       - GuiToggleGroup()
*       - GuiColorPicker()
*       - GuiSlider()
*       - GuiSliderBar()
*       - GuiProgressBar()
*       - GuiColorBarAlpha()
*       - GuiScrollPanel()
*
*
*   DEPENDENCIES:
*       raylib 4.5          - Windowing/input management and drawing
*       raygui 3.5          - Immediate-mode GUI controls with custom styling and icons
*
*   COMPILATION (Windows - MinGW):
*       gcc -o $(NAME_PART).exe $(FILE_NAME) -I../../src -lraylib -lopengl32 -lgdi32 -std=c99
*
*   LICENSE: zlib/libpng
*
*   Copyright (c) 2016-2023 Ramon Santamaria (@raysan5)
*
**********************************************************************************************/

// Adapted for Matte.

@:ray = import(module:'raylib.mt');
@:gui = import(module:'raygui.mt');


// Initialization
//---------------------------------------------------------------------------------------
@:screenWidth = 960;
@:screenHeight = 560;

ray.InitWindow(
    width:screenWidth, 
    height:screenHeight, 
    title:"raygui - controls test suite"
);
ray.SetExitKey(key:0);

// GUI controls initialization
//----------------------------------------------------------------------------------
@dropdownBox000Active = 0;
@dropDown000EditMode = false;

@dropdownBox001Active = 0;
@dropDown001EditMode = false;

@spinner001Value = 0;
@spinnerEditMode = false;

@valueBox002Value = 0;
@valueBoxEditMode = false;

@textBoxText = "Text box";
@textBoxEditMode = false;

@textBoxMultiText = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.\n\nDuis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
@textBoxMultiEditMode = false;

@listViewScrollIndex = 0;
@listViewActive = -1;

@listViewExScrollIndex = 0;
@listViewExActive = 2;
@listViewExFocus = -1;
@listViewExList = [ "This", "is", "a", "list view", "with", "disable", "elements", "amazing!" ];

@multiTextBoxText = "Multi text box";
@multiTextBoxEditMode = false;
@colorPickerValue = {...ray.RED};

@sliderValue = 50.0;
@sliderBarValue = 60;
@progressValue = 0.1;

@forceSquaredChecked = false;

@alphaValue = 0.5f;

    //int comboBoxActive = 1;
@visualStyleActive = 0;
@prevVisualStyleActive = 0;

@toggleGroupActive = 0;
@toggleSliderActive = 0;

@viewScroll = { x:0, y:0 };
//----------------------------------------------------------------------------------

// Custom GUI font loading
//Font font = LoadFontEx("fonts/rainyhearts16.ttf", 12, 0, 0);
//GuiSetFont(font);

@exitWindow = false;
@showMessageBox = false;

@textInput = "";
@textInputFileName = "";
@showTextInputBox = false;

@alpha = 1.0;

// DEBUG: Testing how those two properties affect all controls!
//GuiSetStyle(DEFAULT, TEXT_PADDING, 0);
//GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);

ray.SetTargetFPS(fps:60);
    //--------------------------------------------------------------------------------------
{:::} {
    forever ::{
    // Main game loop
        if (exitWindow) send();    // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        exitWindow = ray.WindowShouldClose();

        if (ray.IsKeyPressed(key:ray.KEY_ESCAPE)) showMessageBox = !showMessageBox;

        if (ray.IsKeyDown(key:ray.KEY_LEFT_CONTROL) && ray.IsKeyPressed(key:ray.KEY_S)) showTextInputBox = true;

        if (ray.IsFileDropped())
        ::<= {
            @droppedFiles = ray.LoadDroppedFiles();

            if ((droppedFiles.paths->size > 0) && ray.IsFileExtension(fileName:droppedFiles.paths[0], ext:".rgs")) gui.GuiLoadStyle(fileName:droppedFiles.paths[0]);

        }

        //alpha -= 0.002f;
        if (alpha < 0) alpha = 0;
        if (ray.IsKeyPressed(key:ray.KEY_SPACE)) alpha = 1;

        gui.GuiSetAlpha(alpha);

        //progressValue += 0.002f;
        if (ray.IsKeyPressed(key:ray.KEY_LEFT)) progressValue -= 0.1;
        if (ray.IsKeyPressed(key:ray.KEY_RIGHT)) progressValue += 0.1;
        if (progressValue > 1.0) progressValue = 1.0;
        if (progressValue < 0.0) progressValue = 0.0;

        /*
        if (visualStyleActive != prevVisualStyleActive)
        ::<= {
            ray.GuiLoadStyleDefault();

            match (visualStyleActive)
            {
                (0): empty,      // Default style
                (1): GuiLoadStyleJungle(); break;
                case 2: GuiLoadStyleLavanda(); break;
                case 3: GuiLoadStyleDark(); break;
                case 4: GuiLoadStyleBluish(); break;
                case 5: GuiLoadStyleCyber(); break;
                case 6: GuiLoadStyleTerminal(); break;
                default: break;
            }

            GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);

            prevVisualStyleActive = visualStyleActive;
        }
        */
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        ray.BeginDrawing();

            ray.ClearBackground(
                color:ray.GetColor(
                    hexValue:gui.GuiGetStyle(
                        control:gui.DEFAULT, 
                        property:gui.BACKGROUND_COLOR
                    )
                )
            );

            // raygui: controls drawing
            //----------------------------------------------------------------------------------
            // Check all possible events that require GuiLock
            if (dropDown000EditMode || dropDown001EditMode) gui.GuiLock();

            // First GUI column
            //GuiSetStyle(CHECKBOX, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
            @:inOut = {};
            
            inOut.checked = forceSquaredChecked;
            gui.GuiCheckBox(bounds:{ x:25, y:108, width:15, height:15 }, text:"FORCE CHECK!", inOut);
            forceSquaredChecked = inOut.checked;

            gui.GuiSetStyle(
                control:gui.TEXTBOX, 
                property:gui.TEXT_ALIGNMENT, 
                value:gui.TEXT_ALIGN_CENTER
            );

            //GuiSetStyle(VALUEBOX, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
            inOut.value = spinner001Value;
            if (gui.GuiSpinner(bounds:{ x:25, y:135, width:125, height:30 }, text:"", inOut, minValue:0, maxValue:100, editMode:spinnerEditMode)) spinnerEditMode = !spinnerEditMode;
            spinner001Value = inOut.value;

            inOut.value = valueBox002Value;
            if (gui.GuiValueBox(bounds:{ x:25, y:175, width:125, height:30 }, text:"", inOut, minValue:0, maxValue:100, editMode:valueBoxEditMode)) valueBoxEditMode = !valueBoxEditMode;
            valueBox002Value = inOut.value;

            gui.GuiSetStyle(
                control:gui.TEXTBOX, 
                property:gui.TEXT_ALIGNMENT, 
                value:gui.TEXT_ALIGN_LEFT
            );

            
            inOut.text = textBoxText;
            if (gui.GuiTextBox(bounds:{ x:25, y:215, width:125, height:30 }, inOut, editMode:textBoxEditMode)) textBoxEditMode = !textBoxEditMode;
            textBoxText = inOut.text;

            
            gui.GuiSetStyle(
                control:gui.BUTTON, 
                property:gui.TEXT_ALIGNMENT,
                value:gui.TEXT_ALIGN_CENTER
            );

            if (gui.GuiButton(bounds:{ x:25, y:255, width:125, height:30 }, text:gui.GuiIconText(iconId:gui.ICON_FILE_SAVE, text:"Save File"))) showTextInputBox = true;

            gui.GuiGroupBox(bounds:{ x:25, y:310, width:125, height:150 }, text:"STATES");
            //GuiLock();
            gui.GuiSetState(state:gui.STATE_NORMAL); if (gui.GuiButton(bounds:{ x:30, y:320, width:115, height:30 }, text:"NORMAL")) empty
            gui.GuiSetState(state:gui.STATE_FOCUSED); if (gui.GuiButton(bounds:{ x:30, y:355, width:115, height:30 }, text:"FOCUSED")) empty
            gui.GuiSetState(state:gui.STATE_PRESSED); if (gui.GuiButton(bounds:{ x:30, y:390, width:115, height:30 }, text:"#15#PRESSED")) empty
            gui.GuiSetState(state:gui.STATE_DISABLED); if (gui.GuiButton(bounds:{ x:30, y:425, width:115, height:30 }, text:"DISABLED")) empty
            gui.GuiSetState(state:gui.STATE_NORMAL);
            //GuiUnlock();

            //inOut.active = visualStyleActive;
            //GuiComboBox(bounds:{ x:25, y:480, width:125, height:30 }, text:"default;Jungle;Lavanda;Dark;Bluish;Cyber;Terminal", inOut);
            //visualStyleActive = inOut.active;

            // NOTE: GuiDropdownBox must draw after any other control that can be covered on unfolding
            gui.GuiUnlock();
            gui.GuiSetStyle(control:gui.DROPDOWNBOX, property:gui.TEXT_PADDING, value:4);
            gui.GuiSetStyle(control:gui.DROPDOWNBOX, property:gui.TEXT_ALIGNMENT, value:gui.TEXT_ALIGN_LEFT);

            inOut.active = dropdownBox001Active;
            if (gui.GuiDropdownBox(bounds:{ x:25, y:65, width:125, height:30 }, text:"#01#ONE;#02#TWO;#03#THREE;#04#FOUR", inOut, editMode:dropDown001EditMode)) dropDown001EditMode = !dropDown001EditMode;
            dropdownBox001Active = inOut.active;

            gui.GuiSetStyle(control:gui.DROPDOWNBOX, property:gui.TEXT_ALIGNMENT, value:gui.TEXT_ALIGN_CENTER);
            gui.GuiSetStyle(control:gui.DROPDOWNBOX, property:gui.TEXT_PADDING, value:0);

            inOut.active = dropdownBox000Active;
            if (gui.GuiDropdownBox(bounds:{ x:25, y:25, width:125, height:30 }, text:"ONE;TWO;THREE", inOut, editMode:dropDown000EditMode)) dropDown000EditMode = !dropDown000EditMode;
            dropdownBox000Active = inOut.active;

            // Second GUI column
            inOut.scrollIndex = listViewScrollIndex;
            inOut.active = listViewActive;
            gui.GuiListView(bounds:{ x:165, y:25, width:140, height:124 }, text:"Charmander;Bulbasaur;#18#Squirtel;Pikachu;Eevee;Pidgey", inOut);
            listViewScrollIndex = inOut.scrollIndex;
            listViewActive = inOut.active;


            inOut.scrollIndex = listViewExScrollIndex;
            inOut.active = listViewExActive;
            inOut.focus = listViewExFocus;
            gui.GuiListViewEx(bounds:{ x:165, y:162, width:140, height:184 }, text:listViewExList, inOut);
            listViewExScrollIndex = inOut.scrollIndex;
            listViewExActive = inOut.active;
            listViewExFocus = inOut.focus;

            //GuiToggle((Rectangle){ 165, 400, 140, 25 }, "#1#ONE", &toggleGroupActive);
            inOut.active = toggleGroupActive;
            gui.GuiToggleGroup(bounds:{ x:165, y:360, width:140, height:24 }, text:"#1#ONE\n#3#TWO\n#8#THREE\n#23#", inOut);
            toggleGroupActive = inOut.active;

            //GuiDisable();
            gui.GuiSetStyle(
                control:gui.SLIDER, 
                property:gui.SLIDER_PADDING, 
                value:2
            );
            inOut.active = toggleSliderActive;
            gui.GuiToggleSlider(bounds:{ x:165, y:480, width:140, height:30 }, text:"ON;OFF", inOut);
            toggleSliderActive = inOut.active;

            gui.GuiSetStyle(
                control:gui.SLIDER, 
                property:gui.SLIDER_PADDING, 
                value:0
            );

            // Third GUI column
            gui.GuiPanel(bounds:{ x:320, y:25, width:225, height:140 }, text:"Panel Info");
            gui.GuiColorPicker(bounds:{ x:320, y:185, width:196, height:192 }, text:"", color:colorPickerValue);

            //GuiDisable();
            inOut.value = sliderValue;
            gui.GuiSlider(bounds:{ x:355, y:400, width:165, height:20 }, textLeft:"TEST", textRight:String(from:(sliderValue*100)->floor/100), inOut, minValue:-50, maxValue:100);
            sliderValue = inOut.value;
            
            
            inOut.value = sliderBarValue;
            gui.GuiSliderBar(bounds:{ x:320, y:430, width:200, height:20 }, textLeft:"", textRight:String(from:sliderBarValue->floor), inOut, minValue:0, maxValue:100);
            sliderBarValue = inOut.value;

            
            inOut.value = progressValue;
            gui.GuiProgressBar(bounds:{ x:320, y:460, width:200, height:20 }, textLeft:"", textRight:""+((progressValue*100)->floor)+"%", inOut, minValue:0.0, maxValue:1.0);
            progressValue = inOut.value;
            gui.GuiEnable();

            // NOTE: View rectangle could be used to perform some scissor test
            @view = { x:0, y:0, width:0, height: 0};
            gui.GuiScrollPanel(bounds:{ x:560, y:25, width:102, height:354 }, text:"", content:{ x:560, y:25, width:300, height:1200 }, scroll:viewScroll, view);

            @mouseCell = { x:0, y:0 };
            gui.GuiGrid(bounds:{ x:560, y:25 + 180 + 195, width:100, height:120 }, text:"", spacing:20, subdivs:3, mouseCell);

            inOut.alpha = alphaValue;
            gui.GuiColorBarAlpha(bounds:{ x:320, y:490, width:200, height:30 }, text:"", inOut);
            alphaValue = inOut.alpha;

            gui.GuiSetStyle(
                control:gui.DEFAULT, 
                property:gui.TEXT_ALIGNMENT_VERTICAL, 
                value:gui.TEXT_ALIGN_TOP
            );   // WARNING: Word-wrap does not work as expected in case of no-top alignment
            
            
            gui.GuiSetStyle(
                control:gui.DEFAULT, 
                property:gui.TEXT_WRAP_MODE, 
                value:gui.TEXT_WRAP_WORD
            );            // WARNING: If wrap mode enabled, text editing is not supported
            
            inOut.text = textBoxMultiText
            if (gui.GuiTextBox(bounds:{ x:678, y:25, width:258, height:492 }, inOut, editMode:textBoxMultiEditMode)) textBoxMultiEditMode = !textBoxMultiEditMode;
            textBoxMultiText = inOut.text;
            
            gui.GuiSetStyle(
                control:gui.DEFAULT, 
                property:gui.TEXT_WRAP_MODE, 
                value:gui.TEXT_WRAP_NONE
            );
            gui.GuiSetStyle(
                control:gui.DEFAULT, 
                property:gui.TEXT_ALIGNMENT_VERTICAL, 
                value:gui.TEXT_ALIGN_MIDDLE
            );

            gui.GuiSetStyle(
                control:gui.DEFAULT, 
                property:gui.TEXT_ALIGNMENT, 
                value:gui.TEXT_ALIGN_LEFT
            );
            gui.GuiStatusBar(bounds:{ x:0, y:ray.GetScreenHeight() - 20, width:ray.GetScreenWidth(), height:20 }, text:"This is a status bar");
            gui.GuiSetStyle(
                control:gui.DEFAULT, 
                property:gui.TEXT_ALIGNMENT, 
                value:gui.TEXT_ALIGN_CENTER
            );
            //GuiSetStyle(STATUSBAR, TEXT_INDENTATION, 20);

            if (showMessageBox)
            ::<= {
                ray.DrawRectangle(posX:0, posY:0, width:ray.GetScreenWidth(), height:ray.GetScreenHeight(), color:ray.Fade(color:ray.RAYWHITE, alpha:0.8));
                @result = gui.GuiMessageBox(bounds:{ x:ray.GetScreenWidth()/2 - 125, y:ray.GetScreenHeight()/2 - 50, width:250, height:100 }, title:gui.GuiIconText(iconId:gui.ICON_EXIT, text:"Close Window"), message:"Do you really want to exit?", buttons:"Yes;No");

                if ((result == 0) || (result == 2)) showMessageBox = false;
                if (result == 1) exitWindow = true;
            }

            if (showTextInputBox)
            ::<= {
                ray.DrawRectangle(posX:0, posY:0, width:ray.GetScreenWidth(), height:ray.GetScreenHeight(), color:ray.Fade(color:ray.RAYWHITE, alpha:0.8));
                inOut.text = textInput;
                inOut.secretViewActive = false;
                @result = gui.GuiTextInputBox(bounds:{ x:ray.GetScreenWidth()/2 - 120, y:ray.GetScreenHeight()/2 - 60, width:240, height:140 }, title:gui.GuiIconText(iconId:gui.ICON_FILE_SAVE, text:"Save file as..."), message:"Introduce output file name:", buttons:"Ok;Cancel", inOut);
                textInput = inOut.text;
                

                if (result == 1)
                ::<={
                    // TODO: Validate textInput value and save
                    textInputFileName = textInput;
                }

                if ((result == 0) || (result == 1) || (result == 2))
                ::<= {
                    showTextInputBox = false;
                    textInput = "";
                }
            }
            //----------------------------------------------------------------------------------

        ray.EndDrawing();
        //----------------------------------------------------------------------------------
    }
}


// De-Initialization
//--------------------------------------------------------------------------------------
ray.CloseWindow();        // Close window and OpenGL context
//--------------------------------------------------------------------------------------

