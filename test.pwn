#include <a_samp>
main(){}

#define PLAYER_PROPERTIES_DECREARE_TIME 	1000
#define PLAYER_THIRSTY_LESS_THAN 			45
#define THIRSTY_LEVEL_PER_DECREASE 			2
#include <hunger.inc>

public OnPlayerConnect(playerid)
{
	SetPlayerHungerLevel(playerid, 100);
	SetPlayerThirstyLevel(playerid, 100);
	return 1;
}

public OnPlayerHungerLevelUpdate(playerid, oldhungerlevel, newhungerlevel)
{
	if(IsPlayerHungry(playerid))
	{
	    // force the player to eat
		new Float:health;
		GetPlayerHealth(playerid, health);
		SetPlayerHealth(playerid, health-3);

		// message
		SendClientMessage(playerid, -1, "You are hungry! Eat some food");
	}
	return 1;
}
public OnPlayerThirstyLevelUpdate(playerid, oldthirstylevel, newthirstylevel)
{
	if(IsPlayerThirsty(playerid))
	{
	    // force the player to drink
		new Float:health;
		GetPlayerHealth(playerid, health);
		SetPlayerHealth(playerid, health-3);

		// message
		SendClientMessage(playerid, -1, "You are thirsty! Drink some soda");
	}
	return 1;
}
