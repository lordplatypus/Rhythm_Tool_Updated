#include "BPMScene.h"
#include <math.h>
#include "../Base/ID.h"
#include "../Base/Math.h"
//Objects
#include "Background.h"
#include "SaveText.h"

BPMScene::BPMScene(Game* game) : game_{game}
{}

BPMScene::~BPMScene()
{}

void BPMScene::Init()
{
    //Objects
    AddGameObject(new Background(*this, sf::Vector2f(0.0f, 0.0f))); //background
    player_ = new Player(GetLP(), GetMP(), sf::Vector2f(805, 439)); //Player
    AddGameObject(player_);
    heart_ = new Heart(GetLP(), GetMP(), sf::Vector2f(641, 471)); //Heart
    AddGameObject(heart_);

    //Main menu setup
    menuText_.push_back(game_->GetLP().SetText(main_font, "Choose Music", sf::Vector2f(0.0f, 0.0f), 16));
    menuText_.push_back(game_->GetLP().SetText(main_font, "Start BPM Setup", sf::Vector2f(0.0f, 0.0f), 16));
    menuText_.push_back(game_->GetLP().SetText(main_font, "Start Playback", sf::Vector2f(0.0f, 0.0f), 16));
    menuText_.push_back(game_->GetLP().SetText(main_font, "Save Changes", sf::Vector2f(0.0f, 0.0f), 16));
    for (int i = 0; i < menuText_.size(); i++) game_->GetLP().SetTextOriginCenter(menuText_[i]);

    //Music menu setup
    std::vector<std::string> songNames = FM_.GetAllMusic(); //store all availble music in music directory
    for (int i = 0; i < songNames.size(); i++)
    {//put music title into the music menu and load BPM for song (if availible)
        musicTitles_.push_back(game_->GetLP().SetText(main_font, songNames[i], sf::Vector2f(0.0f, 0.0f), 16));
        game_->GetLP().SetTextOriginCenter(musicTitles_[i]);

        float BPM = FM_.GetBPM(songNames[i]);
        secPerBeatMap_[songNames[i]] = sf::seconds(1.0f / (BPM * (1.0f / 60.0f)));
    }
    if (musicTitles_.size() <= 0)
    {
        musicTitles_.push_back(game_->GetLP().SetText(main_font, "Whoops, no music was found!", sf::Vector2f(0.0f, 0.0f), 16));
        musicTitles_.push_back(game_->GetLP().SetText(main_font, "Place music into the", sf::Vector2f(0.0f, 0.0f), 16));
        musicTitles_.push_back(game_->GetLP().SetText(main_font, "music directory and restart OR", sf::Vector2f(0.0f, 0.0f), 16));
        musicTitles_.push_back(game_->GetLP().SetText(main_font, "Change the music directory", sf::Vector2f(0.0f, 0.0f), 16));
        musicTitles_.push_back(game_->GetLP().SetText(main_font, "in the config file", sf::Vector2f(0.0f, 0.0f), 16));
        for (int i = 0; i < musicTitles_.size(); i++) game_->GetLP().SetTextOriginCenter(musicTitles_[i]);
    }

    //Verticle menu setup
    menu_ = new VerticalMenu(sf::Vector2f(275, 183), menuText_.size(), menuText_, 3, 1, 32);
    musicMenu_ = new VerticalMenu(sf::Vector2f(803, 183), musicTitles_.size(), musicTitles_, 3, 1, 32);
    musicMenu_->SetDisplay(false);

    //Get stats of the first music title
    secPerBeat = secPerBeatMap_[musicTitles_[0].getString()].asSeconds(); //get sec per beat
    beatsPerMin = (int)round(60 / secPerBeat); //get BPM

    //Set up the rest of the text used
    instructions = game_->GetLP().SetText(main_font, "Use 'Up' and 'Down' to\n\ncycle through options\n\n'Z' to select an option\n\n\nChoose Music:\n\nSelect a music title", sf::Vector2f(584+32, 88), 16);
    displayMusicTitle = game_->GetLP().SetText(main_font, musicTitles_[0].getString(), sf::Vector2f(96, 448), 16);
    displayBeatsPerMin = game_->GetLP().SetText(main_font, "Beats Per Min: " + std::to_string(beatsPerMin), sf::Vector2f(96, 480), 16);
    displaySecPerBeat = game_->GetLP().SetText(main_font, "Sec Per Beat: " + std::to_string(secPerBeat), sf::Vector2f(96, 512), 16);
    displayBeatTimer = game_->GetLP().SetText(main_font, "Beat Time: 0", sf::Vector2f(96, 544), 16);
    displayBeatCount = game_->GetLP().SetText(main_font, "Beat Count: 0", sf::Vector2f(96, 576), 16);
    displayMusicDirectory = game_->GetLP().SetText(main_font, "Music Directory: " + FM_.GetMusicDirectory(), sf::Vector2f(96, 664), 16);
    displayBPMSaveDirectory = game_->GetLP().SetText(main_font, "BPM Save File: " + FM_.GetBPMDirectory(), sf::Vector2f(96, 688), 16);

    //Import available music
    ImportSongs();
}

void BPMScene::Update(float delta_time)
{
    if (state == Menu)
    {//Main menu
        MainMenu();
    }
    else if (state == MusicSelect)
    {//Music select
        MusicSelectMenu();
    }
    else if (state == SetUp)
    {//Setup the BPM for selected song
        BPMSetUp();
    }
    else if (state == PlayBack)
    {//Play back the selected song
        MusicPlayBack();
    }
    else if (state == Save)
    {//save new BPM
        SaveBPMForSelectedSong();
    }

    //Game Object Updates
    gom_.Update(delta_time); //update all gameobjects
    gom_.Remove(); //remove "dead" gameobjects

    //Menu update
    menu_->Update(delta_time);
    musicMenu_->Update(delta_time);

    //input update
    IP_.Update();
}

void BPMScene::Draw(Camera& camera) const
{
    //Game Object Draw
    gom_.Draw(camera); //Regular draw - Draw GameObjects in order based on position in the list
    gom_.DelayedDraw(camera); //draw things after Regular draw is finished, helpful for UI or things that should always be drawn last

    //Draw UI
    menu_->Draw(camera);
    musicMenu_->Draw(camera);
    if (state != MusicSelect) camera.Draw(instructions, layer_UI);
    camera.Draw(displayMusicTitle, layer_UI);
    camera.Draw(displayBeatsPerMin, layer_UI);
    camera.Draw(displaySecPerBeat, layer_UI);
    camera.Draw(displayBeatTimer, layer_UI);
    camera.Draw(displayBeatCount, layer_UI);
    camera.Draw(displayMusicDirectory, layer_UI);
    camera.Draw(displayBPMSaveDirectory, layer_UI);
}

void BPMScene::AddGameObject(GameObject* gameObject)
{
    gom_.Add(gameObject); //add gameobject to the list of gameobjects
}

GameObject* BPMScene::FindGameObject(const std::string& string, const bool byName, const bool byTag, const bool byID)
{//if byTag and byID are both left to default (false), search by name
    return gom_.Find(string, byName, byTag, byID); //returns a GameObject, returns a nullptr if the GameObject is not found
}

void BPMScene::ChangeScene(const std::string& sceneName)
{
    game_->ChangeScene(sceneName);
}

void BPMScene::End()
{
    gom_.Clear();
}



void BPMScene::ImportSongs()
{
    for (int i = 0; i < musicTitles_.size(); i++)
    {//load music
        game_->GetMP().SetMusic(i, FM_.GetMusicDirectory() + musicTitles_[i].getString());
    }
}

void BPMScene::MainMenu()
{
    if (IP_.GetButtonDown(sf::Keyboard::Up))
    {//scroll up
        selectedOption--;
        if (selectedOption < 0) selectedOption = menuText_.size() - 1;
        menu_->ScrollUp();
        switch(selectedOption)
        {//update instructions based on what menu option is selected
            case 0:
            instructions.setString("Use 'Up' and 'Down' to\n\ncycle through options\n\n'Z' to select an option\n\n\nChoose Music:\n\nSelect a music title");
            break;

            case 1:
            instructions.setString("Use 'Up' and 'Down' to\n\ncycle through options\n\n'Z' to select an option\n\n\nStart BPM Setup:\n\nSetup BPM for selected song");
            break;

            case 2:
            instructions.setString("Use 'Up' and 'Down' to\n\ncycle through options\n\n'Z' to select an option\n\n\nStart Playback:\n\nPlay slected song");
            break;

            case 3:
            instructions.setString("Use 'Up' and 'Down' to\n\ncycle through options\n\n'Z' to select an option\n\n\nSave Changes:\n\nSave BPM for selected song");
            break;
        }
    }
    if (IP_.GetButtonDown(sf::Keyboard::Down))
    {//scroll down
        selectedOption++;
        if (selectedOption > menuText_.size() - 1) selectedOption = 0;
        menu_->ScrollDown();
        switch(selectedOption)
        {//update instructions based on what menu option is selected
            case 0:
            instructions.setString("Use 'Up' and 'Down' to\n\ncycle through options\n\n'Z' to select an option\n\n\nChoose Music:\n\nSelect a music title");
            break;

            case 1:
            instructions.setString("Use 'Up' and 'Down' to\n\ncycle through options\n\n'Z' to select an option\n\n\nStart BPM Setup:\n\nSetup BPM for selected song");
            break;

            case 2:
            instructions.setString("Use 'Up' and 'Down' to\n\ncycle through options\n\n'Z' to select an option\n\n\nStart Playback:\n\nPlay slected song");
            break;

            case 3:
            instructions.setString("Use 'Up' and 'Down' to\n\ncycle through options\n\n'Z' to select an option\n\n\nSave Changes:\n\nSave BPM for selected song");
            break;
        }
    }
    if (IP_.GetButtonDown(sf::Keyboard::Z))
    {//select current option
        if (selectedOption == 0) 
        {
            state = MusicSelect;
            musicMenu_->SetDisplay(true);
        }
        if (selectedOption == 1) 
        {
            state = SetUp;
            instructions.setString("'Z' to start music\n\n'Down' to time beats,\n\n'X' to return");
        }
        if (selectedOption == 2) 
        {
            state = PlayBack;
            instructions.setString("Use 'Up' and 'Down'\n\nto tweak the BPM,\n\n'X' to return");
        }
        if (selectedOption == 3) state = Save;
    }
}

void BPMScene::MusicSelectMenu()
{
    if (IP_.GetButtonDown(sf::Keyboard::Up))
    {//scroll up
        musicID--;
        if (musicID < 0) musicID = musicTitles_.size() - 1;
        musicMenu_->ScrollUp();
    }
    if (IP_.GetButtonDown(sf::Keyboard::Down))
    {//scroll down
        musicID++;
        if (musicID > musicTitles_.size() - 1) musicID = 0;
        musicMenu_->ScrollDown();
    }
    if (IP_.GetButtonDown(sf::Keyboard::Z))
    {//select music
        selectedMusicID = musicID;
        secPerBeat = secPerBeatMap_[musicTitles_[selectedMusicID].getString()].asSeconds(); //get sec per beat for selected song
        beatsPerMin = (int)round(60 / secPerBeat); //get BPM for selected song

        //update displayed text
        displayMusicTitle.setString(musicTitles_[selectedMusicID].getString());
        displayBeatsPerMin.setString("Beats Per Min: " + std::to_string(beatsPerMin));
        displaySecPerBeat.setString("Sec Per Beat: " + std::to_string(secPerBeat));
        displayBeatTimer.setString("Beat Time: 0");
        displayBeatCount.setString("Beat Count: 0");
        instructions.setString("Use 'Up' and 'Down' to\n\ncycle through options\n\n'Z' to select an option\n\n\nChoose Music:\n\nSelect a music title");

        state = Menu; //return to the main menu
        musicMenu_->SetDisplay(false);
    }
    if (IP_.GetButtonDown(sf::Keyboard::X))
    {
        musicID = selectedMusicID; //don't select a song, reverts back to perviously selected song
        instructions.setString("Use 'Up' and 'Down' to\n\ncycle through options\n\n'Z' to select an option\n\n\nChoose Music:\n\nSelect a music title");
        state = Menu; //return to the main menu
        musicMenu_->SetDisplay(false);
    }
}

void BPMScene::BPMSetUp()
{
    if (IP_.GetButtonDown(sf::Keyboard::Z))
    {//reset variables - start song
        game_->GetMP().PlayMusic(musicID); //start song
        //update objects that require musicID and music BPM
        player_->SetMusicID(musicID);
        player_->SetBPM(secPerBeatMap_[musicTitles_[musicID].getString()]);
        heart_->SetMusicID(musicID);
        heart_->SetBPM(secPerBeatMap_[musicTitles_[musicID].getString()]);
        //reset variables
        secPerBeat = 0;
        beatsPerMin = 0;
        beatTimer = 0;
        zeroOutTime = 0;
        count = 0;
        listOfBeats.clear();
    }

    if (IP_.GetButtonDown(sf::Keyboard::Down))
    {//If Down is pressed, the beat is recorded
        if (firstTime == true)
        {//start recording once the fist "down" is pressed - the user doesn't have to start timing right when the song starts
            zeroOutTime = game_->GetMP().GetMusic(musicID).getPlayingOffset().asMicroseconds();
            firstTime = false;
        }
        else
        { 
            beatTimer = game_->GetMP().GetMusic(musicID).getPlayingOffset().asMicroseconds() - zeroOutTime; //take the time from the last button press
            zeroOutTime = game_->GetMP().GetMusic(musicID).getPlayingOffset().asMicroseconds(); //take the time of the current button press

            listOfBeats.push_back(beatTimer); //record time inbetween button presses in seconds
            int averageMicrosec = 0;
            for (auto i : listOfBeats) averageMicrosec += i; //add all beat times
            averageMicrosec /= listOfBeats.size(); //average time inbetween beats
            secPerBeat = (float)averageMicrosec / 1000000.0f;
            if (secPerBeat != 0) beatsPerMin = (int)round(60 / secPerBeat); //calculate BPM as long as the time is above 0
        }
        count++; //for beat count
        //play animations
        player_->PlayAnimation();
        heart_->PlayAnimation();
    }

    //update the display text
    displayBeatsPerMin.setString("Beats Per Min: " + std::to_string((int)beatsPerMin));
    displaySecPerBeat.setString("Sec Per Beat: " + std::to_string(secPerBeat));
    displayBeatTimer.setString("Beat Time: " + std::to_string(beatTimer));
    displayBeatCount.setString("Beat Count: " + std::to_string(count));

    if (IP_.GetButtonDown(sf::Keyboard::X))
    {//finish and return to the menu
        firstTime = true; //reset flag
        state = Menu; //return to the main menu
        instructions.setString("Use 'Up' and 'Down' to\n\ncycle through options\n\n'Z' to select an option\n\n\nStart BPM Setup:\n\nSetup BPM for selected song");
        secPerBeatMap_[musicTitles_[musicID].getString()] = sf::seconds(secPerBeat); //save the new sec per beat in the map
        game_->GetMP().StopMusic(musicID); //stop music
    }
}

void BPMScene::MusicPlayBack()
{
    if (IP_.GetButtonDown(sf::Keyboard::Up))
    {//actively change the BPM by +1
        beatsPerMin++; //add one to BPM
        secPerBeatMap_[musicTitles_[musicID].getString()] = sf::seconds(1.0f / (beatsPerMin * (1.0f/60.0f))); //update SPBMap
        player_->SetBPM(secPerBeatMap_[musicTitles_[musicID].getString()]); //update the BPM for the player
        heart_->SetBPM(secPerBeatMap_[musicTitles_[musicID].getString()]); //update the BPM for the heart
        displayBeatsPerMin.setString("Beats Per Min: " + std::to_string(beatsPerMin));
        displaySecPerBeat.setString("Sec Per Beat: " + std::to_string(secPerBeatMap_[musicTitles_[musicID].getString()].asSeconds()));
    }
    if (IP_.GetButtonDown(sf::Keyboard::Down))
    {//actively change the BPM by -1
        beatsPerMin--; //subtract one from BPM
        secPerBeatMap_[musicTitles_[musicID].getString()] = sf::seconds(1.0f / (beatsPerMin * (1.0f/60.0f))); //update SPBMap
        player_->SetBPM(secPerBeatMap_[musicTitles_[musicID].getString()]); //update the BPM for the player
        heart_->SetBPM(secPerBeatMap_[musicTitles_[musicID].getString()]); //update the BPM for the heart
        displayBeatsPerMin.setString("Beats Per Min: " + std::to_string(beatsPerMin));
        displaySecPerBeat.setString("Sec Per Beat: " + std::to_string(secPerBeatMap_[musicTitles_[musicID].getString()].asSeconds()));
    }

    if (firstTime)
    {//reset variables
        game_->GetMP().PlayMusic(musicID); //play music
        //reset variables
        secPerBeat = secPerBeatMap_[musicTitles_[musicID].getString()].asSeconds();
        beatsPerMin = (int)round(60 / secPerBeat);
        count = 0;
        //update objects
        player_->SetAutoAnimation(true);
        player_->SetMusicID(musicID);
        player_->SetBPM(secPerBeatMap_[musicTitles_[musicID].getString()]);
        heart_->SetAutoAnimation(true);
        heart_->SetMusicID(musicID);
        heart_->SetBPM(secPerBeatMap_[musicTitles_[musicID].getString()]);
        //update display text
        displayBeatsPerMin.setString("Beats Per Min: " + std::to_string(beatsPerMin));
        displaySecPerBeat.setString("Sec Per Beat: " + std::to_string(secPerBeat));
        firstTime = false;
    }

    //keep track of the num of beats
    beatTimer = game_->GetMP().GetMusic(musicID).getPlayingOffset().asMicroseconds() % secPerBeatMap_[musicTitles_[musicID].getString()].asMicroseconds();
    if (beatTimer < secPerBeatMap_[musicTitles_[musicID].getString()].asMicroseconds() / 2) 
    {
        if (!startOfBeat)
        {
            startOfBeat = true;
            count++;
        }
    }
    else startOfBeat = false;

    //update display text
    displayBeatTimer.setString("Beat Time: " + std::to_string(beatTimer));
    displayBeatCount.setString("Beat Count: " + std::to_string(count));

    if (IP_.GetButtonDown(sf::Keyboard::X))
    {//return to the main menu
        //reset variables
        count = 0;
        displayBeatTimer.setString("Beat Time: 0");
        displayBeatCount.setString("Beat Count: 0");
        firstTime = true;
        state = Menu;
        instructions.setString("Use 'Up' and 'Down' to\n\ncycle through options\n\n'Z' to select an option\n\n\nStart Playback:\n\nPlay slected song");
        game_->GetMP().StopMusic(musicID); //stop music
        //turn off auto animation
        player_->SetAutoAnimation(false);
        heart_->SetAutoAnimation(false);
    }
}

void BPMScene::SaveBPMForSelectedSong()
{
    FM_.SetBPM(musicTitles_[musicID].getString(), (int)round(60 / secPerBeatMap_[musicTitles_[musicID].getString()].asSeconds())); //save BPM to the save file
    AddGameObject(new SaveText(*this, sf::Vector2f(1080/2, 720/2), FM_.GetBPMDirectory())); //add fade out save text to the list of objects
    state = Menu; //return to the main menu
}



LP& BPMScene::GetLP()
{
    return game_->GetLP();
}

MP& BPMScene::GetMP()
{
    return game_->GetMP();
}