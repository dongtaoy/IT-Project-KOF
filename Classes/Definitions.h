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

#define CHARACTOR_RESOURCE_DIR "Charactors"
#define CHARACTOR_ICON_BIG "icon_big.png"

#define BACKGROUND_PLIST        "backgrounds.plist"
#define BACKGROUND_RESOURCE_DIR "Backgrounds"
#define BACKGROUND_ICON "icon.png"

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
#define CHOOSE_CHARACTOR_SCENE_OPPONENT_ICON_HOLDER "oponent"
#define CHOOSE_CHARACTOR_SCENE_COUNT_DOWN_LABEL     "labelCountDown"

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
#endif
