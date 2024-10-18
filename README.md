# samp-hunger
This is hunger/thirsty system for a San Andreas Multiplayer

##Callbacks
```pawn
OnPlayerHungerLevelUpdate(playerid, oldhungerlevel, newhungerlevel)
OnPlayerThirstyLevelUpdate(playerid, oldthirstylevel, newthirstylevel)
```

```Examples
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
