#ifndef ID_H_
#define ID_H_

//Commonly used "keys" that need to have the same value across the whole program
//Ex: texture keys, music keys, render layer keys
//Textures
enum
{
    background_texture,
    player_texture,
    heart_texture,
    small_heart_texture
};

//Font
enum
{
    main_font,
};

//Music && Sound
enum
{
    audio_music,
};

//Layer group - order in which objects will be rendered (0 = back, 0 < front)
enum
{
    layer_tilemap,
    layer_main,
    layer_particle,
    layer_UI
};

//Views
enum
{
    view_main,
    view_UI
};

#endif