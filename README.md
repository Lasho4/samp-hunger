# samp-hunger
This is hunger/thirsty system for a San Andreas Multiplayer

![hunger](https://github.com/user-attachments/assets/5e49b80c-fd4e-4363-9b85-45a171f560de)

## Usage
```pawn
#include <hunger.inc>
```

## Callbacks
```pawn
public OnPlayerHungerLevelUpdate(playerid, oldhungerlevel, newhungerlevel);
public OnPlayerThirstyLevelUpdate(playerid, oldthirstylevel, newthirstylevel);
```

## Examples
```pawn
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
```
