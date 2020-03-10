+++
date = "2018-01-22T11:28:50-06:00"
title = "Enabling PWM on the TM4C123 microcontroller"
image = "projects/tm4c-pwm/LinkImage_SquareWave.svg"
draft = false
showonlyimage = false

+++
A brief example showing the step missing from the datasheet.
<!--more-->

This example shows how to enable PWM output on pin PB6 for the Cortex M4 core TM4C123GH6PM microcontroller. The steps outlined in the [datasheet](http://www.ti.com/lit/ds/symlink/tm4c123gh6pm.pdf) in section 20.4 are as follows:

1. Enable PWM clock (RCGC0)
2. Enable GPIO port clock (RCGC2)
3. Enable alternate function on pins to be used for PWM (GPIOAFSEL)
4. Assign PWM signals to the appropriate pins (GPIOPCTL)
5. Select PWM clock source and potentially set clock divider (RCC)
6. Configure counting mode and generator A and B behavior (PWMxCTL, PWMxGENA, PWMxGENB)
7. Set the reload counter value (PWMxLOAD)
8. Set comparator A trigger value (PWMxCMPA)
9. Set comparator B trigger value (PWMxCMPB)
10. Start the PWM timers (PWMxCTL)
11. Enable PWM outputs (PWMENABLE)

The problem with these instructions is that they are incomplete. Looking at table 10-3 (in the GPIO configuration and initialization section) on the row "Digital Output (PWM)" shows that the appropriate bit needs set in both the alternative function select register (AFSEL) AND in the digital enable (DEN) register. The PWM initialization instructions mention the former but not the later, and at no point mention table 10-3. 

The code below includes a line for setting bit 6 in the PORTB DEN register to enable pin PB6.



``` c
void PWM_Init(void){
 int volatile delay;
 
 SYSCTL_RCC_R  &= ~(SYSCTL_RCC_USEPWMDIV); //Use undivided system clock as PWM clock
 
 SYSCTL_RCGC0_R     |= (1<<20);     //activate PWM module 0 clock
 SYSCTL_RCGC2_R     |= (1<<1);      //activate port B clock
 delay = SYSCTL_RCGC2_R;            //Allow time for clock to stabalize
 GPIO_PORTB_DR4R_R  |= (1<<6);
 GPIO_PORTB_DEN_R   |= (1<<6);      //Enable digital output on PB6
 GPIO_PORTB_AFSEL_R |= (1<<6);      //Activate  Alternate function on PB6
 GPIO_PORTB_PCTL_R  |= (0x04000000);//Set alternate peripheral to PWM
 
 PWM0_0_CTL_R   &= ~(1<<0);         //Disable pwm block until ready to use
 PWM0_0_CTL_R   &= ~(1<<1);         //Set count-down mode
 PWM0_0_GENA_R  |=  (0xC2);         //Drive pwm low on CmpA and high on zero
 PWM0_0_LOAD_R   =  (1000-1)        //80e6/80e3=1000 (80khz pwm)
 PWM0_0_CMPA_R   =  (500-1);        //Set couter value at which CmpA triggers
 PWM0_0_CTL_R   |=  (0x01);         //Enable pwm block
 PWM0_ENABLE_R  |=  (PWM_ENABLE_PWM0EN);//Enable pwm output to M0PWM0
}
```

