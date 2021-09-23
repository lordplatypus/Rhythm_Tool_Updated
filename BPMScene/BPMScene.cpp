#include "BPMScene.h"
#include <math.h>
#include "../Base/ID.h"
#include "../Base/Math.h"

BPMScene::BPMScene(Game* game) : game_{game}
{}

BPMScene::~BPMScene()
{}

void BPMScene::Init()
{
    //AddGameObject(new Object(position, &pm_, this)); Example
    menuText_.push_back(game_->GetLP().SetText(main_font, "Choose Music"));
    menuText_.push_back(game_->GetLP().SetText(main_font, "Start BPM Setup"));
    menuText_.push_back(game_->GetLP().SetText(main_font, "Start Playback"));
    menuText_.push_back(game_->GetLP().SetText(main_font, "Save Changes"));
    //menuText_.push_back(game_->GetLP().SetText(main_font, "Quit"));
    for (int i = 0; i < menuText_.size(); i++) game_->GetLP().SetTextOriginCenter(menuText_[i]);

    std::vector<std::string> songNames = FM_.SearchDirectory("./", ".ogg");
    for (int i = 0; i < songNames.size(); i++)
    {
        musicTitles_.push_back(game_->GetLP().SetText(main_font, songNames[i]));
        game_->GetLP().SetTextOriginCenter(musicTitles_[i]);

        float BPM = FM_.GetBPM("./BPM.txt", songNames[i]);
        secPerBeatMap_[songNames[i]] = sf::seconds(1.0f / (BPM * (1.0f / 60.0f)));
    }

    //Verticle menu setup ()
    menu_ = new VerticalMenu(sf::Vector2f(275, 183), menuText_.size(), menuText_, 3, 1, 32);
    musicMenu_ = new VerticalMenu(sf::Vector2f(803, 183), musicTitles_.size(), musicTitles_, 3, 1, 32);
    musicMenu_->SetDisplay(false);

    //Set up the rest of the text used
    instructions = game_->GetLP().SetText(main_font, "Use Up and Down to\n\ncycle through options\n\nZ to select an option,\n\nX to return to lobby", sf::Vector2f(584+32, 88), 16);
    displayMusicTitle = game_->GetLP().SetText(main_font, "Music Title: NA", sf::Vector2f(96, 448), 16);
    displayBeatsPerMin = game_->GetLP().SetText(main_font, "Beats Per Min: NA", sf::Vector2f(96, 480), 16);
    //secPerBeat = MP::GetBPMForSelectedMusic(musicID);
    displaySecPerBeat = game_->GetLP().SetText(main_font, "Beats Per Sec: NA", sf::Vector2f(96, 512), 16);
    displayBeatTimer = game_->GetLP().SetText(main_font, "0", sf::Vector2f(96, 544), 16);
    displayBeatCount = game_->GetLP().SetText(main_font, "0", sf::Vector2f(96, 576), 16);

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

    //UI update
    menu_->Update(delta_time);
    musicMenu_->Update(delta_time);

    //input update
    IP_.Update();
}

void BPMScene::Draw(Camera& camera) const
{
    if (state == Menu)
    {
        camera.Draw(instructions, layer_UI);
        camera.Draw(displayMusicTitle, layer_UI);
        camera.Draw(displayBeatsPerMin, layer_UI);
        camera.Draw(displaySecPerBeat, layer_UI);
        camera.Draw(displayBeatTimer, layer_UI);
        camera.Draw(displayBeatCount, layer_UI);
    }

    else if (state == MusicSelect)
    {
        camera.Draw(displayMusicTitle, layer_UI);
        camera.Draw(displayBeatsPerMin, layer_UI);
        camera.Draw(displaySecPerBeat, layer_UI);
        camera.Draw(displayBeatTimer, layer_UI);
        camera.Draw(displayBeatCount, layer_UI);
    }

    else if (state == SetUp)
    {
        camera.Draw(instructions, layer_UI);
        camera.Draw(displayMusicTitle, layer_UI);
        camera.Draw(displayBeatsPerMin, layer_UI);
        camera.Draw(displaySecPerBeat, layer_UI);
        camera.Draw(displayBeatTimer, layer_UI);
        camera.Draw(displayBeatCount, layer_UI);
    }

    else if (state == PlayBack)
    {
        camera.Draw(instructions, layer_UI);
        camera.Draw(displayMusicTitle, layer_UI);
        camera.Draw(displayBeatsPerMin, layer_UI);
        camera.Draw(displaySecPerBeat, layer_UI);
        camera.Draw(displayBeatTimer, layer_UI);
        camera.Draw(displayBeatCount, layer_UI);
    }

    //Game Object Draw
    gom_.Draw(camera); //Regular draw - Draw GameObjects in order based on position in the list
    gom_.DelayedDraw(camera); //draw things after Regular draw is finished, helpful for UI or things that should always be drawn last

    //Draw UI
    menu_->Draw(camera);
    musicMenu_->Draw(camera);
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
    {
        game_->GetMP().SetMusic(i, "./" + musicTitles_[i].getString());
    }
}

void BPMScene::MainMenu()
{
    if (IP_.GetButtonDown(sf::Keyboard::Up))
    {
        selectedOption--;
        if (selectedOption < 0) selectedOption = menuText_.size() - 1;
        menu_->ScrollUp();
    }
    if (IP_.GetButtonDown(sf::Keyboard::Down))
    {
        selectedOption++;
        if (selectedOption > menuText_.size() - 1) selectedOption = 0;
        menu_->ScrollDown();
    }
    if (IP_.GetButtonDown(sf::Keyboard::Z))
    {
        if (selectedOption == 0) 
        {
            state = MusicSelect;
            musicMenu_->SetDisplay(true);
        }
        if (selectedOption == 1) 
        {
            state = SetUp;
            //instructions.setString("Z to start,\n\nDown to time beats,\n\nX to return");
        }
        if (selectedOption == 2) 
        {
            state = PlayBack;
            //instructions.setString("Use Up and Down\n\nto tweak the BPM,\n\nX to return");
        }
        if (selectedOption == 3) state = Save;
    }
}

void BPMScene::MusicSelectMenu()
{
    if (IP_.GetButtonDown(sf::Keyboard::Up))
    {
        musicID--;
        if (musicID < 0) musicID = musicTitles_.size() - 1;
        musicMenu_->ScrollUp();
    }
    if (IP_.GetButtonDown(sf::Keyboard::Down))
    {
        musicID++;
        if (musicID > musicTitles_.size() - 1) musicID = 0;
        musicMenu_->ScrollDown();
    }
    if (IP_.GetButtonDown(sf::Keyboard::Z))
    {
        selectedMusicID = musicID;

        //game_->GetLP().SetTextString(displayMusicTitle, MP::GetMusicTitle(selectedMusicID));
        displayMusicTitle.setString(musicTitles_[selectedMusicID].getString());
        displayBeatsPerMin.setString("Beats Per Min: " + std::to_string((int)round(60 / secPerBeatMap_[musicTitles_[selectedMusicID].getString()].asSeconds())));
        displaySecPerBeat.setString("Beats Per Sec: " + std::to_string(secPerBeatMap_[musicTitles_[selectedMusicID].getString()].asSeconds()));
        displayBeatTimer.setString("Beat Time: 0");
        displayBeatCount.setString("Beat Count: 0");

        instructions.setString("Use Up and Down\n\nto cycle through options,\n\nZ to select an option,\n\nX to return to lobby");

        state = Menu;
        musicMenu_->SetDisplay(false);
    }
    if (IP_.GetButtonDown(sf::Keyboard::X))
    {
        musicID = selectedMusicID;
        //instructions.setString("Use Up and Down\n\nto cycle through options,\n\nZ to select an option,\n\nX to return to lobby");
        state = Menu;
        musicMenu_->SetDisplay(false);
    }
}

void BPMScene::BPMSetUp()
{
    if (IP_.GetButtonDown(sf::Keyboard::Z))
    {//reset variables
        game_->GetMP().PlayMusic(musicID);
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
            zeroOutTime = game_->GetMP().GetMusic(musicID).getPlayingOffset().asSeconds();
            firstTime = false;
        }
        else
        { 
            beatTimer = game_->GetMP().GetMusic(musicID).getPlayingOffset().asSeconds() - zeroOutTime; //take the time from the last button press
            zeroOutTime = game_->GetMP().GetMusic(musicID).getPlayingOffset().asSeconds(); //take the time of the current button press

            listOfBeats.push_back(beatTimer); //record time inbetween button presses
            secPerBeat = 0; //reset variable
            //musicSPBMap[musicID] = 0;
            for (auto i : listOfBeats) secPerBeat += i; //add all beat times
            //for (auto i : listOfBeats) musicSPBMap[musicID] += i;
            secPerBeat /= listOfBeats.size(); //average time inbetween beats
            //musicSPBMap[musicID] /= listOfBeats.size();
            if (secPerBeat != 0) beatsPerMin = (int)round(60 / secPerBeat); //calculate BPM as long as the time is above 0
            // if (musicSPBMap[musicID] != 0) 
            // {
            //     beatsPerMin = round(60 / musicSPBMap[musicID]);
            //     secPerBeat = musicSPBMap[musicID];
            //     displayBeatsPerMin.setString("Beats Per Min: " + std::to_string((int)beatsPerMin));
            //     displaySecPerBeat.setString("Beats Per Sec: " + std::to_string(secPerBeat));
            // }
        }
        count++; //for beat count
    }

    //update the displays
    displayBeatsPerMin.setString("Beats Per Min: " + std::to_string((int)beatsPerMin));
    displaySecPerBeat.setString("Beats Per Sec: " + std::to_string(secPerBeat));
    displayBeatTimer.setString("Beat Time: " + std::to_string(beatTimer));
    displayBeatCount.setString("Beat Count: " + std::to_string(count));

    if (IP_.GetButtonDown(sf::Keyboard::X))
    {//finish and return to the menu
        firstTime = true;
        state = Menu;
        instructions.setString("Use Up and Down\n\nto cycle through options,\n\nZ to select an option,\n\nX to return to lobby");
        secPerBeatMap_[musicTitles_[musicID].getString()] = sf::seconds(secPerBeat); //save the new sec per beat in the map
    }
}

void BPMScene::MusicPlayBack()
{
    if (IP_.GetButtonDown(sf::Keyboard::Up))
    {//actively change the BPM by +1
        secPerBeat = secPerBeatMap_[musicTitles_[musicID].getString()].asSeconds(); //get sec per beat for the song
        beatsPerMin = (int)round(60 / secPerBeat + 1); //convert to BPM, then add one
        displayBeatsPerMin.setString("Beats Per Min: " + std::to_string(beatsPerMin));
        displaySecPerBeat.setString("Beats Per Sec: " + std::to_string(secPerBeat));
    }
    if (IP_.GetButtonDown(sf::Keyboard::Down))
    {//actively change the BPM by -1
        secPerBeat = secPerBeatMap_[musicTitles_[musicID].getString()].asSeconds(); //get sec per beat for the song
        beatsPerMin = (int)round(60 / secPerBeat + -1); //convert to BPM, then subtract one
        displayBeatsPerMin.setString("Beats Per Min: " + std::to_string(beatsPerMin));
        displaySecPerBeat.setString("Beats Per Sec: " + std::to_string(secPerBeat));
    }

    if (firstTime)
    {//reset variables
        game_->GetMP().PlayMusic(musicID);
        secPerBeat = secPerBeatMap_[musicTitles_[musicID].getString()].asSeconds();
        beatsPerMin = (int)round(60 / secPerBeat);
        count = 0;
        displayBeatsPerMin.setString("Beats Per Min: " + std::to_string(beatsPerMin));
        displaySecPerBeat.setString("Beats Per Sec: " + std::to_string(secPerBeat));
        firstTime = false;
    }

    //beatTimer = fmod(MP::GetPlayingMusicOffSetInSec(), musicSPBMap[musicID]);
    beatTimer = game_->GetMP().GetMusic(musicID).getPlayingOffset().asMicroseconds() % secPerBeatMap_[musicTitles_[musicID].getString()].asMicroseconds();

    displayBeatTimer.setString("Beat Time: " + std::to_string(beatTimer));
    displayBeatCount.setString("Beat Count: " + std::to_string(count));

    if (IP_.GetButtonDown(sf::Keyboard::X))
    {
        count = 0;
        displayBeatTimer.setString("Beat Time: 0");
        displayBeatCount.setString("Beat Count: 0");
        firstTime = true;
        state = Menu;
        instructions.setString("Use Up and Down\n\nto cycle through options,\n\nZ to select an option,\n\nX to return to lobby");
    }
}

void BPMScene::SaveBPMForSelectedSong()
{
    // if (secPerBeatMap_[musicTitles_[musicID].getString()] != 0)
    // {
    //     MP::SetBPM(musicID, musicSPBMap[musicID]);
    //     alpha = 255;
    // }
    FM_.SetBPM("./BPM.txt", musicTitles_[musicID].getString(), (int)round(60 / secPerBeatMap_[musicTitles_[musicID].getString()].asSeconds()));
    state = Menu;
}