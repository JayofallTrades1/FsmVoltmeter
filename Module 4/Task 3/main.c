#include "fsm.c"

void main(void)
{
	const key key_sequence[] = {icw, iccw, ocw, occw, icw, iccw};
	key keypressed;
	present_state = aut;
	
	for(int i = 0; i < 4; i++)
	{
		keypressed = key_sequence[i];
		fsm(present_state, keypressed);
	}
	while(1){}
}