//
//  Definitions.h
//  KOF
//
//  Created by Dongtao Yu on 12/08/2015.
//
//

#ifndef KOF_Definitions_h
#define KOF_Definitions_h

#define APPWARP_APP_KEY                 "10672fd365d93fc814eb81b83f281d13d867485180e0e68cc255ac3e5e4b0162"
#define APPWARP_SECRET_KEY              "1a05138df28bca585f7405481055f9e51b9f65d8d92469b4377812455cdb92a8"
#define GAME_NAME                       "KOFUnimelb"

// GOBAL
#define BORDER_SELECTED                 "selected"
#define BORDER_UNSELECTED               "unselected"
#define BACK_BUTTON                     "buttonBack"
#define CREATE_BUTTON                   "buttonCreate"

#define CHARACTER_ICON_BIG_PATH         "characters/%s/icon_big.png"

#define BACKGROUND_PLIST                "backgrounds/backgrounds.plist"
#define BACKGROUND_ICON_PATH            "backgrounds/%s/icon.png"

#define CHARACTER_SPRITE_PATH           "characters/%s/sprite.plist"
#define CHARACTER_ANIMATION_PATH        "characters/%s/animation.plist"

#define BACKGROUND_SPRITE_PATH          "backgrounds/%s/sprite.plist"
#define BACKGROUND_ANIMATION_PATH       "backgrounds/%s/animation.plist"

#define COUNTDOWN_SPRITE_PATH           "countdown/sprite.plist"
#define COUNTDOWN_ANIMATION_PATH        "countdown/animation.plist"

#define CHARACTER_SPRITE_PATH           "characters/%s/sprite.plist"
#define CHARACTER_ANIMATION_PATH        "characters/%s/animation.plist"

#define CHARACTER_SQUAT                 "%s/squat"
#define CHARACTER_SQUAT_DOWN            "%s/squat_down"
#define CHARACTER_SQUAT_HIT             "%s/squat_hit"
#define CHARACTER_SQUAT_KICK1           "%s/squat_kick1"
#define CHARACTER_SQUAT_KICK2           "%s/squat_kick2"
#define CHARACTER_SQUAT_MOVEBACK        "%s/squat_moveback"
#define CHARACTER_SQUAT_MOVEFORWARD     "%s/squat_moveforward"
#define CHARACTER_SQUAT_PUNCH1          "%s/squat_punch1"
#define CHARACTER_SQUAT_PUNCH2          "%s/squat_punch2"
#define CHARACTER_SQUAT_UP              "%s/squat_up"

#define CHARACTER_INITIAL_FRAME         "characters/%s/stand/00.png"

#define CHARACTER_STAND                 "%s/stand"
#define CHARACTER_STAND_HIT             "%s/stand_hit"
#define CHARACTER_STAND_JUMP            "%s/stand_jump"
#define CHARACTER_STAND_KICK1           "%s/stand_kick1"
#define CHARACTER_STAND_KICK2           "%s/stand_kick2"
#define CHARACTER_STAND_MOVEBACK        "%s/stand_moveback"
#define CHARACTER_STAND_MOVEFORWARD     "%s/stand_moveforward"
#define CHARACTER_STAND_PUNCH1          "%s/stand_punch1"
#define CHARACTER_STAND_PUNCH2          "%s/stand_punch2"


#define CHARACTER_START                 "%s/start"
#define CHARACTER_WIN                   "%s/win"
#define CHARACTER_DIE                   "%s/die"


#define NUM_BACKGROUNDS 4
#define NUM_BESTOF 3

// Splash Scence
#define DISPLAY_TIME_SPLASH_SCENE       0.5
#define TRANSITION_TIME                 0.5


// Choose Character Scene
#define CHOOSE_CHARACTER_SCENE                      "ChooseCharacterScene"
#define CHOOSE_CHARACTER_SCENE_FILE                 "ChooseCharacter.csb"
#define CHOOSE_CHARACTER_SCENE_CHARACTER_WIDTH      310.0
#define CHOOSE_CHARACTER_SCENE_CHARACTER_HEIGHT     430.0
#define CHOOSE_CHARACTER_SCENE_CHARACTER_PREFIX     "character"
#define CHOOSE_CHARACTER_SCENE_PLAYER_ICON_HOLDER   "player"
#define CHOOSE_CHARACTER_SCENE_OPPONENT_ICON_HOLDER "opponent"
#define CHOOSE_CHARACTER_SCENE_COUNT_DOWN_LABEL     "labelCountDown"
#define CHOOSE_CHARACTER_SCENE_ROOMID               "roomID"
#define CHOOSE_CHARACTER_SCENE_READY_L              "buttonReadyL"
#define CHOOSE_CHARACTER_SCENE_READY_R              "buttonReadyR"
#define CHOOSE_CHARACTER_SCENE_GO_L                 "buttonGoL"
#define CHOOSE_CHARACTER_SCENE_GO_R                 "buttonGoR"
#define CHOOSE_CHARACTER_SCENE_WAITING              "waiting"


// Create Room Scene
#define CREATE_ROOM_SCENE                       "CreateRoomScene"
#define CREATE_ROOM_SCENE_FILE                  "CreateRoom.csb"
#define CREATE_ROOM_SCENE_BACKGROUND_PREFIX     "background"
#define CREATE_ROOM_SCENE_CHECKBOX_PREFIX       "checkbox"
#define CREATE_ROOM_SCENE_BESTOF_LABEL          "label"


// Choose Room Scene
#define CHOOSE_ROOM_SCENE                       "ChooseRoomScene"
#define CHOOSE_ROOM_SCENE_FILE                  "ChooseRoom.csb"
#define CHOOSE_ROOM_SCENE_ROOM_LIST             "listRoom"
#define CHOOSE_ROOM_SCENE_ROOM_LIST_ITEM_ID     "text"
#define CHOOSE_ROOM_SCENE_ROOM_LIST_ITEM_BESTOF "bestof"
#define CHOOSE_ROOM_SCENE_ROOM_LIST_ITEM_STATUS "status"
#define CHOOSE_ROOM_SCENE_ROOM_LIST_ITEM_BACKGROUND "map"


// GAME PLAY
#define GAME_PLAY_SCENE                         "GamePlayScene"
#define GAME_PLAY_SCENE_FILE                    "GamePlay.csb"
#define GAME_PLAY_SCENE_FIGHTER_LEFT            "left"
#define GAME_PLAY_SCENE_FIGHTER_RIGHT           "right"
#define GAME_PLAY_SCENE_JOYSTICK_BASE           "Resources/joystick.png"
#define GAME_PLAY_SCENE_JOYSTICK                "Resources/joystick_button.png"
#define GAME_PLAY_SCENE_BUTTON_A_NORMAL "Resources/a.png"
#define GAME_PLAY_SCENE_BUTTON_A_PRESSED "Resources/a_c.png"
#define GAME_PLAY_SCENE_BUTTON_A_X      0.7f
#define GAME_PLAY_SCENE_BUTTON_A_Y      0.3f
#define GAME_PLAY_SCENE_BUTTON_B_NORMAL "Resources/b.png"
#define GAME_PLAY_SCENE_BUTTON_B_PRESSED "Resources/b_c.png"
#define GAME_PLAY_SCENE_BUTTON_B_X      0.85f
#define GAME_PLAY_SCENE_BUTTON_B_Y      0.3f
#define GAME_PLAY_SCENE_BUTTON_C_NORMAL "Resources/c.png"
#define GAME_PLAY_SCENE_BUTTON_C_PRESSED "Resources/c_c.png"
#define GAME_PLAY_SCENE_BUTTON_C_X      0.75f
#define GAME_PLAY_SCENE_BUTTON_C_Y      0.1f
#define GAME_PLAY_SCENE_BUTTON_D_NORMAL "Resources/d.png"
#define GAME_PLAY_SCENE_BUTTON_D_PRESSED "Resources/d_d.png"
#define GAME_PLAY_SCENE_BUTTON_D_X      0.9f
#define GAME_PLAY_SCENE_BUTTON_D_Y      0.1f



// MULTIPLAYER
#define MAX_USERS 2
#define ROOM_NAME "MEMEDA"

// ROOM PROPERTIES
#define ROOM_PROPERTY_BACKGROUND "background"
#define ROOM_PROPERTY_BESTOF      "bestof"

// Multiplayer protocol
#define MP_GLOBLE                           100

#define OP_GB_USER_JOINED                   500
#define OP_GB_USER_LEFT                     501

#define MP_CHOOSE_CHARACTER_SCENE           1

#define OP_CCS_CHARACTER_CHANGED            1
#define OP_CCS_READY                        2
#define OP_CCS_START_COUNTDOWN              3
#define OP_CCS_NOTREADY                     4
#define OP_CCS_START_GAME                   5

#define MP_GAME_PLAY_SCNE                   2

#define OP_GPS_BUTTON_A                     1
#define OP_GPS_BUTTON_B                     2
#define OP_GPS_BUTTON_C                     3
#define OP_GPS_BUTTON_D                     4

#define OP_GPS_STAND_MOVEFORWARD                 5
#define OP_GPS_STAND_MOVEBACK                    6
#define OP_GPS_STAND                        7
//#define OP_GPS_SQUAT_DOWN                        7
//#define OP_GPS_SQU


// Fighter

#define ACTION_1_STAND                      100
#define ACTION_1_STAND_MOVEFORWARD          101
#define ACTION_1_STAND_MOVEBACK             102

#define ACTION_1_SQUAT                      150
#define ACTION_1_SQUAT_DOWN                 151
#define ACTION_1_SQUAT_MOVEBACK             152
#define ACTION_1_SQUAT_MOVEFORWARD          153

#define ACTION_2_STAND_JUMP                 201
#define ACTION_2_STAND_PUNCH1               202
#define ACTION_2_STAND_PUNCH2               203
#define ACTION_2_STAND_KICK1                204
#define ACTION_2_STAND_KICK2                205

#define ACTION_2_SQUAT_PUNCH1               250
#define ACTION_2_SQUAT_PUNCH2               251
#define ACTION_2_SQUAT_KICK1                252
#define ACTION_2_SQUAT_KICK2                253




#define ACTION_MOVE_SPEED                   200
#define ACTION_1_MOVE_DURATION              .7f


// Camera
#define CAMERA_MOVE_THRESHOLD               150
#define CAMERA_FIGHTER_OFFSET               10


// LOCKSTEP
#define LOCK_STEP_DELAY                     100
#define GAME_FRAME_DELAY                    20
#define GAME_FRAMES_PER_LOCK_STEP           4
//#define LOCK_S

struct command_t
{
    std::string sender;
    int scene;
    int operation;
    std::string properties;
    int lockstepId;
};

#endif
