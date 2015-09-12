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
#define BORDER_SELECTED "selected"
#define BORDER_UNSELECTED "unselected"
#define BACK_BUTTON "buttonBack"
#define CREATE_BUTTON "buttonCreate"

#define CHARACTOR_ICON_BIG_PATH "charactors/%s/icon_big.png"

#define BACKGROUND_PLIST        "backgrounds/backgrounds.plist"
#define BACKGROUND_ICON_PATH    "backgrounds/%s/icon.png"

#define CHARACTOR_SPRITE_PATH       "charactors/%s/sprite.plist"
#define CHARACTOR_ANIMATION_PATH    "charactors/%s/animation.plist"

#define BACKGROUND_SPRITE_PATH      "backgrounds/%s/sprite.plist"
#define BACKGROUND_ANIMATION_PATH   "backgrounds/%s/animation.plist"

#define NUM_BACKGROUNDS 4
#define NUM_BESTOF 3

// Splash Scence
#define DISPLAY_TIME_SPLASH_SCENE       0.5
#define TRANSITION_TIME                 0.5


// Choose Charactor Scene
#define CHOOSE_CHARACTOR_SCENE                      "ChooseCharactorScene"
#define CHOOSE_CHARACTOR_SCENE_FILE                 "ChooseCharactor.csb"
#define CHOOSE_CHARACTOR_SCENE_CHARACTOR_WIDTH      310.0
#define CHOOSE_CHARACTOR_SCENE_CHARACTOR_HEIGHT     430.0
#define CHOOSE_CHARACTOR_SCENE_CHARACTOR_PLIST      "charactors.plist"
#define CHOOSE_CHARACTOR_SCENE_CHARACTOR_PREFIX     "charactor"
#define CHOOSE_CHARACTOR_SCENE_PLAYER_ICON_HOLDER   "player"
#define CHOOSE_CHARACTOR_SCENE_OPPONENT_ICON_HOLDER "opponent"
#define CHOOSE_CHARACTOR_SCENE_COUNT_DOWN_LABEL     "labelCountDown"
#define CHOOSE_CHARACTOR_SCENE_ROOMID               "roomID"
#define CHOOSE_CHARACTOR_SCENE_READY_L              "buttonReadyL"
#define CHOOSE_CHARACTOR_SCENE_READY_R              "buttonReadyR"
#define CHOOSE_CHARACTOR_SCENE_GO_L                 "buttonGoL"
#define CHOOSE_CHARACTOR_SCENE_GO_R                 "buttonGoR"
#define CHOOSE_CHARACTOR_SCENE_WAITING              "waiting"


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


// MULTIPLAYER
#define MAX_USERS 2
#define ROOM_NAME "MEMEDA"

// ROOM PROPERTIES
#define ROOM_PROPERTY_BACKGROUND "background"
#define ROOM_PROPERTY_BESTOF      "bestof"

// Multiplayer protocol
#define MP_CHOOSE_CHARACTOR_SCENE           1

#define OP_CCS_CHARACTOR_CHANGED            1
#define OP_CCS_READY                        2
#define OP_CCS_START_COUNTDOWN              3
#define OP_CCS_NOTREADY                     4
#define OP_CCS_START_GAME                   5

#define MP_GAME_PLAY_SCNE                   2


// Fighter

#define ACTION_1_STAND                        100
#define ACTION_1_MOVE_FORWARD                 101
#define ACTION_1_MOVE_BACK                    102
#define ACTION_1_CALL_FUNC                    199

#define ACTION_JUMP                         201
#define ACTION_PUNCH1                       202
#define ACTION_PUNCH2                       203
#define ACTION_KICK1                        204
#define ACTION_KICK2                        205

#define ACTION_MOVE_SPEED                   200
#define ACTION_1_MOVE_DURATION                .7f


// Camera
#define CAMERA_MOVE_THRESHOLD                150
#define CAMERA_FIGHTER_OFFSET                30

#endif
