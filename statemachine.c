int state_machine(int setstate, int value)
{
	static int current;

	if (setstate==1)
		current=value;
	
	return current;
}


int getstate()
{
	return state_machine(0,0);
}


void setstate(int value)
{
	state_machine(1,value);
}
