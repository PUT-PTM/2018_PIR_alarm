#include "defines.h"
#include "stm32f4xx.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_hd44780.h"

void LED_init()
{
	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

volatile unsigned int counter;

void TIM5_init()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period =49999;
	TIM_TimeBaseStructure.TIM_Prescaler = 8399;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode =  TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
	TIM_Cmd(TIM5, ENABLE);
	counter = TIM5->CNT;

}

void TIM4_init(){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure2;

	TIM_TimeBaseStructure2.TIM_Period =49999;
	TIM_TimeBaseStructure2.TIM_Prescaler = 8399;
	TIM_TimeBaseStructure2.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure2.TIM_CounterMode =  TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure2);
	//TIM_Cmd(TIM4, ENABLE);
}

void TIM4_NVIC_Config()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);

	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
}

void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
	{
		// Uruchom buzzer
		GPIO_SetBits(GPIOE, GPIO_Pin_14);
		//Zmien diode RGB na czerwona

		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
}

void Guzik_init()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
//inicjalizacjia GPIO do przyciskow
	GPIO_InitTypeDef GPIO_InitStructure2;
	GPIO_InitStructure2.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure2.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure2.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure2.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOE, &GPIO_InitStructure2);
}

int waitKey()
{
	TIM_Cmd(TIM2, ENABLE);

	int kodWybranegoPrzycisku = -1;

	GPIO_ResetBits(GPIOE, GPIO_Pin_12);
	GPIO_ResetBits(GPIOE, GPIO_Pin_15);
	GPIO_SetBits(GPIOE, GPIO_Pin_11);

	while(kodWybranegoPrzycisku == -1)
	{
		for (int i = 0; i < 1000000; i++);

		//ROW 1
		if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_7) && GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_11)) //czytaj z wejscia E7
		{
			kodWybranegoPrzycisku = 1;
		}
		//ROW 2
		else if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_8) && GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_11)) //czytaj z wejscia E7
		{
			kodWybranegoPrzycisku = 4;
		}
		//ROW 3
		else if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_9) && GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_11)) //czytaj z wejscia E7
		{
			kodWybranegoPrzycisku = 7;
		}
		//ROW 4
		else if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_10) && GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_11)) //czytaj z wejscia E7
		{
			kodWybranegoPrzycisku = 10;
		}

		//ROW 1
		else if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_7) && GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_12)) //czytaj z wejscia E7
		{
			kodWybranegoPrzycisku = 2;
		}
		//ROW 2
		else if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_8) && GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_12)) //czytaj z wejscia E7
		{
			kodWybranegoPrzycisku = 5;
		}
		//ROW 3
		else if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_9) && GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_12)) //czytaj z wejscia E7
		{
			kodWybranegoPrzycisku = 8;
		}
		//ROW 4
		else if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_10) && GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_12)) //czytaj z wejscia E7
		{
			kodWybranegoPrzycisku = 0;
		}
		//ROW 1
		else if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_7) && GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_15)) //czytaj z wejscia E7
		{
			kodWybranegoPrzycisku = 3;
		}
		//ROW 2
		else if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_8) && GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_15)) //czytaj z wejscia E7
		{
			kodWybranegoPrzycisku = 6;
		}
		//ROW 3
		else if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_9) && GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_15)) //czytaj z wejscia E7
		{
			kodWybranegoPrzycisku = 9;
		}
		//ROW 4
		else if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_10) && GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_15)) //czytaj z wejscia E7
		{
			kodWybranegoPrzycisku = 11;
		}
	}

	TIM_Cmd(TIM2, DISABLE);
	return kodWybranegoPrzycisku;
}

void keypadAndBuzzerOut_init()
{
	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11| GPIO_Pin_12| GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

volatile int tabPinKeys[4];

int insertPin(int i)
{
	int tabInsertedKeys[] = { 0, 0, 0, 0 };
	TM_HD44780_BlinkOn();
	Delayms(300);

	GPIO_SetBits(GPIOD, GPIO_Pin_12);
	tabInsertedKeys[0] = waitKey();
	TM_HD44780_Puts(5, 1, "*");
	Delayms(300);

	GPIO_ResetBits(GPIOD, GPIO_Pin_12);
	tabInsertedKeys[1] = waitKey();
	TM_HD44780_Puts(6, 1, "*");
	Delayms(300);

	GPIO_SetBits(GPIOD, GPIO_Pin_12);
	tabInsertedKeys[2] = waitKey();
	TM_HD44780_Puts(7, 1, "*");
	Delayms(300);

	GPIO_ResetBits(GPIOD, GPIO_Pin_12);
	tabInsertedKeys[3] = waitKey();
	TM_HD44780_Puts(8, 1, "*");
	Delayms(300);

	GPIO_SetBits(GPIOD, GPIO_Pin_12);
	if(tabInsertedKeys[0] == tabPinKeys[0] && tabInsertedKeys[1] == tabPinKeys[1] && tabInsertedKeys[2] == tabPinKeys[2] && tabInsertedKeys[3] == tabPinKeys[3])
	{
		// Jesli PIN jest poprawny
		GPIO_SetBits(GPIOD, GPIO_Pin_14);
		TM_HD44780_Clear();
		TM_HD44780_BlinkOff();
		TM_HD44780_CursorOff();
		return 1;
	}
	else if(i>1)
	{
		// Jesli PIN jest niepoprawny
		GPIO_SetBits(GPIOD, GPIO_Pin_13);
		TM_HD44780_Clear();
		TM_HD44780_Puts(0, 0, "Blad! Podaj PIN");
		TM_HD44780_Puts(0, 1, "PIN: ");
		TM_HD44780_CursorOn();
		return 0;
	}
	else if(i=4)
	{
	GPIO_SetBits(GPIOD, GPIO_Pin_14);
		TM_HD44780_Clear();
		TM_HD44780_BlinkOff();
		TM_HD44780_CursorOff();
		return 0;
	}else
	{
	GPIO_SetBits(GPIOD, GPIO_Pin_13);
		TM_HD44780_Clear();
		TM_HD44780_Puts(0, 0, "Wykorzystano limit prob!!!!");
		Delayms(1000);
		TM_HD44780_CursorOff();
		return 0;
	}


}

int zmianaPinu()
{
	TM_HD44780_Clear();
	TM_HD44780_Puts(0, 0, "Wpisz stary PIN");
	TM_HD44780_Puts(0, 1, "PIN: ");
	// wpisanie starego pinu
	if(insertPin(4) != 1) {
		TM_HD44780_Clear();
		TM_HD44780_BlinkOff();
		TM_HD44780_CursorOff();
		return 0;
	}

	int tabInsertedKeys[] = { 0, 0, 0, 0 };

	// wpisanie nowego pinu
	TM_HD44780_Puts(0, 0, "Wpisz nowy PIN");
	TM_HD44780_Puts(0, 1, "PIN: ");
	TM_HD44780_CursorOn();
	TM_HD44780_BlinkOn();
	Delayms(1000);
	GPIO_SetBits(GPIOD, GPIO_Pin_12);
	tabInsertedKeys[0] = waitKey();
	TM_HD44780_Puts(5, 1, "*");
	Delayms(1000);

	GPIO_ResetBits(GPIOD, GPIO_Pin_12);
	tabInsertedKeys[1] = waitKey();
	TM_HD44780_Puts(6, 1, "*");
	Delayms(1000);

	GPIO_SetBits(GPIOD, GPIO_Pin_12);
	tabInsertedKeys[2] = waitKey();
	TM_HD44780_Puts(7, 1, "*");
	Delayms(1000);

	GPIO_ResetBits(GPIOD, GPIO_Pin_12);
	tabInsertedKeys[3] = waitKey();
	TM_HD44780_Puts(8, 1, "*");
	Delayms(1000);

	// zatwierdzenie nowego pinu znakiem # (kod 11)
	GPIO_SetBits(GPIOD, GPIO_Pin_12);
	if(waitKey() != 11) return 0;
	Delayms(1000);

	// przepisanie nowego pinu do globalnej tablicy z pinem
	tabPinKeys[0] = tabInsertedKeys[0];
	tabPinKeys[1] = tabInsertedKeys[1];
	tabPinKeys[2] = tabInsertedKeys[2];
	tabPinKeys[3] = tabInsertedKeys[3];

	// po zmianie pinu zamrugaj dioda zielona
	for (int i = 0; i < 1000000; i++);
	GPIO_ResetBits(GPIOD, GPIO_Pin_12);
	for (int i = 0; i < 1000000; i++);

	for (int i = 0; i < 1000000; i++);
	GPIO_SetBits(GPIOD, GPIO_Pin_12);
	for (int i = 0; i < 1000000; i++);

	for (int i = 0; i < 1000000; i++);
	GPIO_ResetBits(GPIOD, GPIO_Pin_12);
	for (int i = 0; i < 1000000; i++);

	for (int i = 0; i < 1000000; i++);
	GPIO_SetBits(GPIOD, GPIO_Pin_12);
	for (int i = 0; i < 1000000; i++);
	TM_HD44780_CursorOff();
	TM_HD44780_Clear();
	TM_HD44780_BlinkOff();
	TM_HD44780_Puts(0, 0, "zmieniono pin");
	Delayms(4000);

	TM_HD44780_Clear();
	return 1;

}

void testPrzerwyTimer2()
{
	for (int i = 0; i < 1000000; i++);
	GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
	for (int i = 0; i < 1000000; i++);
	GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
	for (int i = 0; i < 1000000; i++);
	GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
	for (int i = 0; i < 1000000; i++);
	GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
	for (int i = 0; i < 1000000; i++);
	GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
	for (int i = 0; i < 1000000; i++);
	GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
	for (int i = 0; i < 1000000; i++);
	GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
	for (int i = 0; i < 1000000; i++);
	GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
	for (int i = 0; i < 1000000; i++);
	GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
	for (int i = 0; i < 1000000; i++);
	GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
	for (int i = 0; i < 1000000; i++);
	GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
	for (int i = 0; i < 1000000; i++);
	GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
	for (int i = 0; i < 1000000; i++);
	GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
	for (int i = 0; i < 1000000; i++);
	GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
	for (int i = 0; i < 1000000; i++);
	GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
	for (int i = 0; i < 1000000; i++);
	GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
	for (int i = 0; i < 1000000; i++);
	GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
	for (int i = 0; i < 1000000; i++);
	GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
	for (int i = 0; i < 1000000; i++);
	GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
	for (int i = 0; i < 1000000; i++);
	GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
	for (int i = 0; i < 1000000; i++);
	GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
	for (int i = 0; i < 1000000; i++);
	GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
	for (int i = 0; i < 1000000; i++);
	GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
	for (int i = 0; i < 1000000; i++);
	GPIO_ToggleBits(GPIOD, GPIO_Pin_13);

	GPIO_ResetBits(GPIOD, GPIO_Pin_13);

	TIM2_init();
	TIM2_NVIC_Config();
	TIM2_IRQHandler();
}

void TIM2_init(){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure2;

	TIM_TimeBaseStructure2.TIM_Period = 499;
	TIM_TimeBaseStructure2.TIM_Prescaler = 4399;
	TIM_TimeBaseStructure2.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure2.TIM_CounterMode =  TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure2);
}

void TIM2_NVIC_Config()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
}


void TIM2_IRQHandler()
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		if ( GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_11) && !GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_12) && !GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_15) )
		{
			GPIO_ResetBits(GPIOE, GPIO_Pin_11);
			GPIO_SetBits(GPIOE, GPIO_Pin_12);
		}
		else if  ( !GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_11) && GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_12) && !GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_15) )
		{
			GPIO_ResetBits(GPIOE, GPIO_Pin_12);
			GPIO_SetBits(GPIOE, GPIO_Pin_15);
		}
		else if  ( !GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_11) && !GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_12) && GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_15) )
		{
			GPIO_ResetBits(GPIOE, GPIO_Pin_15);
			GPIO_SetBits(GPIOE, GPIO_Pin_11);
		}
		else
		{
			GPIO_ResetBits(GPIOE, GPIO_Pin_15);
			GPIO_ResetBits(GPIOE, GPIO_Pin_15);
			GPIO_SetBits(GPIOE, GPIO_Pin_11);
		}

		//GPIO_ToggleBits(GPIOE, GPIO_Pin_12);
		//GPIO_ToggleBits(GPIOE, GPIO_Pin_15);
		//GPIO_ToggleBits(GPIOE, GPIO_Pin_11);

		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

void TIM3_init() 
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	//Licznik odpowiedzialny za wypelnienie
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period = 999;
	TIM_TimeBaseStructure.TIM_Prescaler = 83;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	// ustawic odpowiednie wartosci Periodu i Prescalera
}

void TIM3_NVIC_Config() 
{
	//Przerwanie do zmieniania wypelnienia (Tim3)
	NVIC_InitTypeDef NVIC_InitStructure;
	// numer przerwania
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	// priorytet g³ówny
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	// subpriorytet
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	// uruchom dany kana³
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// zapisz wype³nion¹ strukturê do rejestrów
	NVIC_Init(&NVIC_InitStructure);

	// wyczyszczenie przerwania od timera 3 (wyst¹pi³o przy konfiguracji 	timera)
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	// zezwolenie na przerwania od przepe³nienia dla timera 3
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

}


void RGB_init()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	//inicjalizacjia GPIO do kolorow diody RGB (6-R 8-G 6-9)
	GPIO_InitTypeDef GPIO_InitStructure;

	TIM_OCInitTypeDef TIM_OCInitStructure;
	/* PWM1 Mode configuration: */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 100;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM4);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	TIM_OC3Init(TIM3, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_TIM4);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	TIM_OC4Init(TIM3, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_TIM4);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	TIM3->CCR1 = 1000;
	TIM3->CCR3 = 1000;
	TIM3->CCR4 = 0;

	TIM_Cmd(TIM3, ENABLE);

	GPIO_SetBits(GPIOC, GPIO_Pin_6 | GPIO_Pin_8 | GPIO_Pin_9);

}

void setRGBColours(int valueOfRed, int valueOfGreen, int valueOfBlue) //nowa funkcja
{
	// ustawienie koloru diody wg podanych wartosci
	TIM3->CCR1 = valueOfRed;
	TIM3->CCR3 = valueOfGreen;
	TIM3->CCR4 = valueOfBlue;
}

int main()
{
	SystemInit();

    TM_HD44780_Init(16, 2);

	int z=0;
	LED_init();
	TIM5_init();
	Guzik_init();
	TIM4_init();
	TIM4_NVIC_Config();
	keypadAndBuzzerOut_init();

	TIM3_init();
	TIM3_NVIC_Config();
	RGB_init();
	int alarm=0;

	tabPinKeys[0] = 1;
	tabPinKeys[1] = 2;
	tabPinKeys[2] = 3;
	tabPinKeys[3] = 4;

	GPIO_SetBits(GPIOD, GPIO_Pin_13);

	testPrzerwyTimer2();

	// Ustawienie diody RGB na zielono
	setRGBColours(0, 1000, 0);

while(1)
{
	if(alarm==0)
	{
		//wyczysczenie wyswietlacza
		TM_HD44780_Clear();
		GPIO_SetBits(GPIOD, GPIO_Pin_12);
		do{
			TM_HD44780_Puts(0, 0, "Wlacz alarm: *");
			TM_HD44780_Puts(0, 1, "Zmien PIN #");

			// Zmiana diod informujacych
			GPIO_SetBits(GPIOD, GPIO_Pin_12);

			// Ustawienie diody RGB na zielono
			setRGBColours(0, 1000, 0);

			int wcisnietyPrzycisk = waitKey();
			// Jezeli wcisnieto gwiazdke (przycisk 10), to aktywuj alarm
			if(wcisnietyPrzycisk == 10) alarm = 1;
			// Jezeli wcisnieto krzyzyk (przycisk 11), to przejdz do trybu zmiany pinu
			else if(wcisnietyPrzycisk == 11)
			{
				// Zmiana diod informujacych
				GPIO_ResetBits(GPIOD, GPIO_Pin_12);
				GPIO_ResetBits(GPIOD, GPIO_Pin_13);
				GPIO_ResetBits(GPIOD, GPIO_Pin_14);
				GPIO_SetBits(GPIOD, GPIO_Pin_15);

				// Ustawienie diody RGB na niebieski
				setRGBColours(0, 0, 1000);

				// Wywolanie funkcji zmieniajacej pin
				zmianaPinu();
				GPIO_ResetBits(GPIOD, GPIO_Pin_15);

				// Ustawienie diody RGB na zielony
				setRGBColours(0, 1000, 0);
			}
		}while(alarm==0); // Dopoki alarm jest w stanie nieaktywnym
	}

	// Jezeli alarm zostal zalaczony
	if(alarm == 1 )
	{
		//Zmien kolor diody RGB na zolty
		setRGBColours(1000, 900, 0);

		TM_HD44780_Clear();
		TM_HD44780_Puts(0, 0, "Wlaczanie alarmu!");
		TM_HD44780_Puts(0, 1, "Opusc pokoj!");

		// Zmiana diod informujacych
		GPIO_ResetBits(GPIOD, GPIO_Pin_12);
		GPIO_SetBits(GPIOD, GPIO_Pin_13);

		// Odczekanie (czas na odsuniecie sie od czujnika)
		do{
			if(TIM_GetFlagStatus(TIM5, TIM_FLAG_Update))
			{
				TIM_ClearFlag(TIM5, TIM_FLAG_Update);
			}
			TIM_Cmd(TIM5, DISABLE);
			TIM_Cmd(TIM5, ENABLE);
			counter=TIM5->CNT;
			if(counter==49999)
			{
				// Zmiana alarmu na uzbrojony po uplynieciu czasu (zadzwoni gdy wykryje ruch)
				alarm=2;
			}
		}while(alarm==1);


	}

	if(alarm ==2)// Jezeli alarm jest uzbrojony
	{
		// Zmiana koloru diody RGB na pomaranczowy
		setRGBColours(1000, 500, 0);

		TM_HD44780_Clear();
		TM_HD44780_Puts(0, 0, "Alarm uzbrojony");
		// Zmiana diod informujacych
		GPIO_ResetBits(GPIOD, GPIO_Pin_13);
		GPIO_ResetBits(GPIOD, GPIO_Pin_12);
		GPIO_SetBits(GPIOD, GPIO_Pin_14);
		do
		{
			// Jezeli wykryto ruch (aktywacja pinu E11 - wyjscie czujnika ruchu)
			if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_6))
			{
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				GPIO_ResetBits(GPIOD, GPIO_Pin_13);
				alarm = 3;
			}
		}while(alarm==2); // Dopoki czujnik nie poda stanu wysokiego na pin 11E


	}

	if(alarm==3)//alarm sie uaktywnia - wykryto ruch
	{
		// Zmien kolor diody RGB na czerowny
		setRGBColours(1000, 0, 0);

		TM_HD44780_Clear();
		TM_HD44780_Puts(0, 0, "Wpisz kod PIN");
		TM_HD44780_Puts(0, 1, "PIN: ");
		TM_HD44780_CursorOn();

		int pozostalaLiczbaProb = 3;

		// Zmiana diod informujacych
		GPIO_ResetBits(GPIOD, GPIO_Pin_14);
		GPIO_SetBits(GPIOD, GPIO_Pin_13);

		TIM_Cmd(TIM4, DISABLE);
		TIM_Cmd(TIM4, ENABLE);

		//wpisywanie pinu - jezeli poprawny zmienia alarm na 0
		while(alarm == 3)
		{
			if(pozostalaLiczbaProb == 0)
			{
				GPIO_ResetBits(GPIOD, GPIO_Pin_12);
				GPIO_ResetBits(GPIOD, GPIO_Pin_13);
				GPIO_ResetBits(GPIOD, GPIO_Pin_14);
				GPIO_ResetBits(GPIOD, GPIO_Pin_15);
				pozostalaLiczbaProb -= 1;

			}
			else if(insertPin(pozostalaLiczbaProb) == 1)
			{
				alarm = 0;
				TIM_Cmd(TIM4, DISABLE);
				GPIO_ResetBits(GPIOD, GPIO_Pin_12);
				GPIO_ResetBits(GPIOD, GPIO_Pin_13);
				GPIO_ResetBits(GPIOD, GPIO_Pin_14);
				GPIO_ResetBits(GPIOD, GPIO_Pin_15);

				GPIO_ResetBits(GPIOE, GPIO_Pin_14);
			}
		}
	}
}
}
