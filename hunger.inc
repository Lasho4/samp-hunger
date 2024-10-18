/*
    SA:MP Hunger System | Lasho4 (Jax Teller)
    (C) 2024

    * Use '#define DONT_USE_HUNGER_SYSTEM' or '#define DONT_USE_THIRSTY_SYSTEM'
    * Use '#define DONT_USE_PROPERTIE_TEXTDRAW'
*/

#if defined _hungerinc_included
	#endinput
#endif
#define _hungerinc_included

#if !defined HUNGER_LEVEL_PER_DECREASE
    #define HUNGER_LEVEL_PER_DECREASE 1
#endif

#if !defined THIRSTY_LEVEL_PER_DECREASE
    #define THIRSTY_LEVEL_PER_DECREASE 1
#endif

// 5 minute by default
#if !defined PLAYER_PROPERTIES_DECREARE_TIME
    #define PLAYER_PROPERTIES_DECREARE_TIME 5*60000
#endif

#if !defined PLAYER_HUGRY_LESS_THAN
    #define PLAYER_HUGRY_LESS_THAN 50
#endif

#if !defined PLAYER_THIRSTY_LESS_THAN
    #define PLAYER_THIRSTY_LESS_THAN 50
#endif

#define MAX_HUNGER_LEVEL    100
#define MAX_THIRSTY_LEVEL   100

forward OnPlayerHungerLevelUpdate(playerid, oldhungerlevel, newhungerlevel);
forward OnPlayerThirstyLevelUpdate(playerid, oldthirstylevel, newthirstylevel);

enum (+=1)
{
    propertie_id_hunger,
    propertie_id_thirsty
}

enum e_PlayerHungerProperties
{
    bool:h_Active,
    h_PlayerHunger,
    h_PlayerThirsty
}
static _PlayerProperties[MAX_PLAYERS][e_PlayerHungerProperties];

static PlayerText:hunger_PTD[MAX_PLAYERS][4],
    PlayerText:thirsty_PTD[MAX_PLAYERS][4];

public OnGameModeInit()
{
    #if !defined DONT_USE_HUNGER_SYSTEM && !defined DONT_USE_THIRSTY_SYSTEM
        SetTimer("PlayerPropertiesTime", PLAYER_PROPERTIES_DECREARE_TIME, true);
    #endif
	#if defined hungerinc_OnGameModeInit
		return hungerinc_OnGameModeInit();
	#else
		return 1;
	#endif
}
#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit hungerinc_OnGameModeInit
#if defined hungerinc_OnGameModeInit
	forward hungerinc_OnGameModeInit();
#endif

public OnPlayerConnect(playerid)
{
    _PlayerProperties[playerid][h_Active] = false;
    #if !defined DONT_USE_HUNGER_SYSTEM && !defined DONT_USE_PROPERTIE_TEXTDRAW
        hunger_PTD[playerid][0] = CreatePlayerTextDraw(playerid, 509.6001, 107.4155, "LD_SPAC:white"); // ïóñòî
        PlayerTextDrawTextSize(playerid, hunger_PTD[playerid][0], 45.0000, 11.5299);
        PlayerTextDrawAlignment(playerid, hunger_PTD[playerid][0], 1);
        PlayerTextDrawColor(playerid, hunger_PTD[playerid][0], 387984127);
        PlayerTextDrawBackgroundColor(playerid, hunger_PTD[playerid][0], 255);
        PlayerTextDrawFont(playerid, hunger_PTD[playerid][0], 4);
        PlayerTextDrawSetProportional(playerid, hunger_PTD[playerid][0], 0);
        PlayerTextDrawSetShadow(playerid, hunger_PTD[playerid][0], 0);

        hunger_PTD[playerid][1] = CreatePlayerTextDraw(playerid, 511.6001, 109.9022, "LD_SPAC:white"); // ïóñòî
        PlayerTextDrawTextSize(playerid, hunger_PTD[playerid][1], 41.0000, 6.5299);
        PlayerTextDrawAlignment(playerid, hunger_PTD[playerid][1], 1);
        PlayerTextDrawColor(playerid, hunger_PTD[playerid][1], 241587711);
        PlayerTextDrawBackgroundColor(playerid, hunger_PTD[playerid][1], 255);
        PlayerTextDrawFont(playerid, hunger_PTD[playerid][1], 4);
        PlayerTextDrawSetProportional(playerid, hunger_PTD[playerid][1], 0);
        PlayerTextDrawSetShadow(playerid, hunger_PTD[playerid][1], 0);

        hunger_PTD[playerid][2] = CreatePlayerTextDraw(playerid, 511.6001, 109.9022, "LD_SPAC:white"); // ïóñòî
        PlayerTextDrawTextSize(playerid, hunger_PTD[playerid][2], 41.0000, 6.5299);
        PlayerTextDrawAlignment(playerid, hunger_PTD[playerid][2], 1);
        PlayerTextDrawColor(playerid, hunger_PTD[playerid][2], 665739519);
        PlayerTextDrawBackgroundColor(playerid, hunger_PTD[playerid][2], 255);
        PlayerTextDrawFont(playerid, hunger_PTD[playerid][2], 4);
        PlayerTextDrawSetProportional(playerid, hunger_PTD[playerid][2], 0);
        PlayerTextDrawSetShadow(playerid, hunger_PTD[playerid][2], 0);

        hunger_PTD[playerid][3] = CreatePlayerTextDraw(playerid, 500.9001, 106.9199, "hud:radar_dateFood"); // ïóñòî
        PlayerTextDrawTextSize(playerid, hunger_PTD[playerid][3], 11.4500, 13.3300);
        PlayerTextDrawAlignment(playerid, hunger_PTD[playerid][3], 1);
        PlayerTextDrawColor(playerid, hunger_PTD[playerid][3], -1);
        PlayerTextDrawBackgroundColor(playerid, hunger_PTD[playerid][3], 255);
        PlayerTextDrawFont(playerid, hunger_PTD[playerid][3], 4);
        PlayerTextDrawSetProportional(playerid, hunger_PTD[playerid][3], 0);
        PlayerTextDrawSetShadow(playerid, hunger_PTD[playerid][3], 0);
    #endif

    #if !defined DONT_USE_THIRSTY_SYSTEM && !defined DONT_USE_PROPERTIE_TEXTDRAW
        thirsty_PTD[playerid][0] = CreatePlayerTextDraw(playerid, 560.8983, 107.3155, "LD_SPAC:white"); // ïóñòî
        PlayerTextDrawTextSize(playerid, thirsty_PTD[playerid][0], 45.0000, 11.5299);
        PlayerTextDrawAlignment(playerid, thirsty_PTD[playerid][0], 1);
        PlayerTextDrawColor(playerid, thirsty_PTD[playerid][0], 387984127);
        PlayerTextDrawBackgroundColor(playerid, thirsty_PTD[playerid][0], 255);
        PlayerTextDrawFont(playerid, thirsty_PTD[playerid][0], 4);
        PlayerTextDrawSetProportional(playerid, thirsty_PTD[playerid][0], 0);
        PlayerTextDrawSetShadow(playerid, thirsty_PTD[playerid][0], 0);

        thirsty_PTD[playerid][1] = CreatePlayerTextDraw(playerid, 563.1878, 109.9022, "LD_SPAC:white"); // ïóñòî
        PlayerTextDrawTextSize(playerid, thirsty_PTD[playerid][1], 41.0000, 6.5299);
        PlayerTextDrawAlignment(playerid, thirsty_PTD[playerid][1], 1);
        PlayerTextDrawColor(playerid, thirsty_PTD[playerid][1], 441612031);
        PlayerTextDrawBackgroundColor(playerid, thirsty_PTD[playerid][1], 255);
        PlayerTextDrawFont(playerid, thirsty_PTD[playerid][1], 4);
        PlayerTextDrawSetProportional(playerid, thirsty_PTD[playerid][1], 0);
        PlayerTextDrawSetShadow(playerid, thirsty_PTD[playerid][1], 0);

        thirsty_PTD[playerid][2] = CreatePlayerTextDraw(playerid, 563.1878, 109.9022, "LD_SPAC:white"); // ïóñòî
        PlayerTextDrawTextSize(playerid, thirsty_PTD[playerid][2], 41.0000, 6.5299);
        PlayerTextDrawAlignment(playerid, thirsty_PTD[playerid][2], 1);
        PlayerTextDrawColor(playerid, thirsty_PTD[playerid][2], 696302079);
        PlayerTextDrawBackgroundColor(playerid, thirsty_PTD[playerid][2], 255);
        PlayerTextDrawFont(playerid, thirsty_PTD[playerid][2], 4);
        PlayerTextDrawSetProportional(playerid, thirsty_PTD[playerid][2], 0);
        PlayerTextDrawSetShadow(playerid, thirsty_PTD[playerid][2], 0);

        thirsty_PTD[playerid][3] = CreatePlayerTextDraw(playerid, 555.5996, 106.8244, "hud:radar_dateDrink"); // ïóñòî
        PlayerTextDrawTextSize(playerid, thirsty_PTD[playerid][3], 11.0000, 13.0000);
        PlayerTextDrawAlignment(playerid, thirsty_PTD[playerid][3], 1);
        PlayerTextDrawColor(playerid, thirsty_PTD[playerid][3], -1);
        PlayerTextDrawBackgroundColor(playerid, thirsty_PTD[playerid][3], 255);
        PlayerTextDrawFont(playerid, thirsty_PTD[playerid][3], 4);
        PlayerTextDrawSetProportional(playerid, thirsty_PTD[playerid][3], 0);
        PlayerTextDrawSetShadow(playerid, thirsty_PTD[playerid][3], 0);
    #endif

	#if defined hungerinc_OnPlayerConnect
		return hungerinc_OnPlayerConnect(playerid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect hungerinc_OnPlayerConnect
#if defined hungerinc_OnPlayerConnect
	forward hungerinc_OnPlayerConnect(playerid);
#endif

public OnPlayerSpawn(playerid)
{
    #if !defined DONT_USE_PROPERTIE_TEXTDRAW
        ShowPlayerHungerTextDraw(playerid);
        ShowPlayerThirstyTextDraw(playerid);
    #endif
	#if defined lac_OnPlayerSpawn
		return lac_OnPlayerSpawn(playerid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerSpawn
	#undef OnPlayerSpawn
#else
	#define _ALS_OnPlayerSpawn
#endif
#define OnPlayerSpawn hungerinc_OnPlayerSpawn
#if defined hungerinc_OnPlayerSpawn
	forward hungerinc_OnPlayerSpawn(playerid);
#endif

forward PlayerPropertiesTime();
public PlayerPropertiesTime()
{
    #if defined foreach
        foreach(new i:Player)
        {
    #else
        for(new i = 0, j = GetPlayerPoolSize(); i <= j; i ++)
        {
            if(!IsPlayerConnected(i)) continue;
    #endif
            if(!_PlayerProperties[i][h_Active]) continue;
            #if !defined DONT_USE_HUNGER_SYSTEM
                SetPlayerHungerLevel(i, GetPlayerHungerLevel(i)-HUNGER_LEVEL_PER_DECREASE);
            #endif
            #if !defined DONT_USE_THIRSTY_SYSTEM
                SetPlayerThirstyLevel(i, GetPlayerThirstyLevel(i)-THIRSTY_LEVEL_PER_DECREASE);
            #endif
        }

}

#if !defined DONT_USE_HUNGER_SYSTEM
    stock GetPlayerHungerLevel(playerid)
    {
        if(!(0 <= playerid < MAX_PLAYERS))
            return false;
        return _PlayerProperties[playerid][h_PlayerHunger];
    }
    stock SetPlayerHungerLevel(playerid, amount)
    {
        if(!(0 <= playerid < MAX_PLAYERS))
            return false;
        if(!(0 <= amount <= MAX_HUNGER_LEVEL))
            return false;
        OnPlayerHungerLevelUpdate(playerid, GetPlayerHungerLevel(playerid), amount);
        #if !defined DONT_USE_PROPERTIE_TEXTDRAW
            UpdatePlayerPropertiesTextDraw(playerid);
        #endif
        return _PlayerProperties[playerid][h_PlayerHunger] = amount;
    }
    stock IsPlayerHungry(playerid)
    {
        if(!(0 <= playerid < MAX_PLAYERS))
            return false;
        return (GetPlayerHungerLevel(playerid) < PLAYER_HUGRY_LESS_THAN);
    }
#endif

#if !defined DONT_USE_THIRSTY_SYSTEM
    stock GetPlayerThirstyLevel(playerid)
    {
        if(!(0 <= playerid < MAX_PLAYERS))
            return false;
        return _PlayerProperties[playerid][h_PlayerThirsty];
    }
    stock SetPlayerThirstyLevel(playerid, amount)
    {
        if(!(0 <= playerid < MAX_PLAYERS))
            return false;
        if(!(0 <= amount <= MAX_THIRSTY_LEVEL))
            return false;
        OnPlayerThirstyLevelUpdate(playerid, GetPlayerThirstyLevel(playerid), amount);
        #if !defined DONT_USE_PROPERTIE_TEXTDRAW
            UpdatePlayerPropertiesTextDraw(playerid);
        #endif
        return _PlayerProperties[playerid][h_PlayerThirsty] = amount;
    }
    stock IsPlayerThirsty(playerid)
    {
        if(!(0 <= playerid < MAX_PLAYERS))
            return false;
        return (GetPlayerThirstyLevel(playerid) < PLAYER_THIRSTY_LESS_THAN);
    }
#endif

#if !defined DONT_USE_PROPERTIE_TEXTDRAW
    stock ShowPlayerHungerTextDraw(playerid)
    {
        if(!(0 <= playerid < MAX_PLAYERS))
            return false;
        for(new i = 0; i < sizeof hunger_PTD[]; i ++)
        {
            PlayerTextDrawShow(playerid, hunger_PTD[playerid][i]);
        }
        _PlayerProperties[playerid][h_Active] = true;
        return UpdatePlayerPropertiesTextDraw(playerid);
    }
    stock ShowPlayerThirstyTextDraw(playerid)
    {
        if(!(0 <= playerid < MAX_PLAYERS))
            return false;
        for(new i = 0; i < sizeof thirsty_PTD[]; i ++)
        {
            PlayerTextDrawShow(playerid, thirsty_PTD[playerid][i]);
        }
        return UpdatePlayerPropertiesTextDraw(playerid);
    }
    stock UpdatePlayerPropertiesTextDraw(playerid)
    {
        static Float:_textdraw_Size = 41.0;
        _textdraw_Size = (GetPlayerHungerLevel(playerid) * 41.0) / MAX_HUNGER_LEVEL;
        if(_textdraw_Size > 41.0) _textdraw_Size = 41.0;
        PlayerTextDrawTextSize(playerid, hunger_PTD[playerid][2], _textdraw_Size, 6.5299);
        
        if(_PlayerProperties[playerid][h_Active])
        {
            PlayerTextDrawHide(playerid, hunger_PTD[playerid][2]);
            PlayerTextDrawShow(playerid, hunger_PTD[playerid][2]);
        }

        _textdraw_Size = 41.0;
        _textdraw_Size = (GetPlayerThirstyLevel(playerid) * 41.0) / MAX_THIRSTY_LEVEL;
        if(_textdraw_Size > 41.0) _textdraw_Size = 41.0;
        PlayerTextDrawTextSize(playerid, thirsty_PTD[playerid][2], _textdraw_Size, 6.5299);

        if(_PlayerProperties[playerid][h_Active])
        {
            PlayerTextDrawHide(playerid, thirsty_PTD[playerid][2]);
            PlayerTextDrawShow(playerid, thirsty_PTD[playerid][2]);
        }
        return true;
    }
#endif