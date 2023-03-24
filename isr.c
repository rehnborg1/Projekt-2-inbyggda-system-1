/********************************************************************************
* isr.c: Inneh�ller avbrottsrutiner.
********************************************************************************/
#include "setup.h"

/********************************************************************************
* ISR (PCINT0_vect): Avbrottsrutin f�r PCI-avbrott p� I/O-port B som anropas vid 
				     nedtryckning av tryckknapprna anslutna till pin 11 - 13 
					 (PORTB3 - PORTB5).
********************************************************************************/
ISR (PCINT0_vect)
{
	disable_pin_change_interrupt(IO_PORTB);
	timer_enable_interrupt(&timer0);
	
	if (button_is_pressed(&b1))
	{
		display_toggle_count();
	}
	
	else if (button_is_pressed(&b2))
	{
		display_toggle_count_direction();
	}
	
	else if (button_is_pressed(&b3))
	{
		display_toggle_output();
	}
}

/********************************************************************************
* ISR (TIME0_OVF_vect): Avbrottsrutin som �ger rum vid uppr�kning till 256 av
*                        Timer 2 i Normal Mode, vilket sker var 0.128:e
*                        millisekund n�r timern �r aktiverad. En g�ng per sekund
*                        inkrementeras talet utskrivet p� 7-segmentsdisplayerna.
********************************************************************************/
ISR (TIMER0_OVF_vect)
{
	timer_count(&timer0);
	
	if (timer_elapsed(&timer0))
	{
		timer_disable_interrupt(&timer0);
		enable_pin_change_interrupt(IO_PORTB);
	}
}

/********************************************************************************
* ISR (TIMER1_COMPA_vect): Avbrottsrutin som �ger rum vid uppr�kning till 256 av
*                          Timer 1 i CTC Mode, vilket sker var 0.128:e
*                          millisekund n�r timern �r aktiverad. En g�ng per
*                          millisekund togglas talet utskrivet p�
*                          7-segmentsdisplayerna mellan tiotal och ental.
********************************************************************************/
ISR (TIMER1_COMPA_vect)
{
	display_toggle_digit();
	return;
}

/********************************************************************************
* ISR (TIMER2_OVF_vect): Avbrottsrutin som �ger rum vid uppr�kning till 256 av
*                        Timer 2 i Normal Mode, vilket sker var 0.128:e
*                        millisekund n�r timern �r aktiverad. En g�ng per sekund
*                        inkrementeras talet utskrivet p� 7-segmentsdisplayerna.
********************************************************************************/
ISR (TIMER2_OVF_vect)
{
	display_count();
	return;
}