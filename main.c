/********************************************************************************
* main.c: Demonstration av inbyggt system innefattande 7-segmentsdisplayer.
*         Timerkrets Timer 1 används för att räkna upp befintligt tal på
*         7-segmentsdisplayerna en gång per sekund.
********************************************************************************/
#include "setup.h"

struct button b1, b2, b3;
struct timer timer0;

/********************************************************************************
* setup: Initierar systemet enligt följande:
*
*        1. Knappar med interrupts initieras.
*
*        2. Initierar 7-segmentsdisplayerna med startvärde 0 och aktiverar
*           uppräkning en gång per sekund.
*   	 
*        3. Initierar Watchdog-timern med en timeout på 1024 ms. System reset
*           aktiveras så att systemåterställning sker ifall Watchdog-timern
*           löper ut.
********************************************************************************/
static inline void setup(void)
{
	
	button_init(&b1, 11);
	button_init(&b2, 12);
	button_init(&b3, 13);
	
	button_enable_interrupt(&b1);
	button_enable_interrupt(&b2);
	button_enable_interrupt(&b3);
	
	wdt_init(WDT_TIMEOUT_1024_MS);
	wdt_enable_system_reset();
	
	timer_init(&timer0, TIMER_SEL_0, 300);

	display_init();
	return;
}

/********************************************************************************
* main: Initierar systemet vid start. Uppräkning sker sedan kontinuerligt
*       av talet på 7-segmentsdisplayerna en gång per sekund.
********************************************************************************/
int main(void)
{
	setup();
	
	while (1)
	{
		wdt_reset();
	}

	return 0;
}