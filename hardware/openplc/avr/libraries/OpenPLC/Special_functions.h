//LADDER SPECIAL FUNCTIONS

//allways on
boolean SF_01()
{
	return(1);
}

//allways off
boolean SF_02()
{
	return(0);
}

//first cicle on
boolean SF_03()
{
	return first_cycle;
}

//30s off - 30s on
boolean SF_04()
{
	return toggle_30s;
}

//500ms off - 500ms on
boolean SF_05()
{
	return toggle_500ms;
}

//cycle off - cycle on
boolean SF_06()
{
	return toggle_50ms;
}

void countTimers()
{
	system_timer++; //increment system timer each cycle
	
	//SPECIAL FUNCTION VARIABLES
	first_cycle = false; //after the first cycle this boolean remains off
	toggle_50ms = !toggle_50ms; //toggle each cycle
	if (!(system_timer % 10)) 
	{
		toggle_500ms = !toggle_500ms; //toggle each 500ms
	}
	if (system_timer == 600)
	{
		system_timer=0; //reset timer
		toggle_30s = !toggle_30s; //toggle each 30s
	}
}