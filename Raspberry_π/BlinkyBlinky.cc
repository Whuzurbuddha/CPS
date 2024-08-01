#include <bcm2835.h>
#include <iostream>
#include <cstdint>
#include <array>

constexpr std::uint8_t led_1 = RPI_V2_GPIO_P1_21;   // GPIO 9               
constexpr std::uint8_t led_2 = RPI_V2_GPIO_P1_19;   // GPIO 10                
constexpr std::uint8_t led_3 = RPI_V2_GPIO_P1_15;   // GPIO 22                
constexpr std::uint8_t led_4 = RPI_V2_GPIO_P1_13;   // GPIO 27                
constexpr std::uint8_t led_5 = RPI_V2_GPIO_P1_11;   // GPIO 17 
constexpr std::uint8_t button = RPI_V2_GPIO_P1_37;   // GPIO 4 
constexpr std::array<std::uint8_t, 5> leds = {led_1, led_2, led_3, led_4, led_5};
int switch_state; 

void run_led()
{
    for(int i = 0; i < 20; ++i)
    {
        if(i % 2 == 0)
        {
            switch_state = HIGH;
        }else 
        {
            switch_state = LOW;
        }
        for(int j = 0; j < leds.size(); ++j)
        {
            bcm2835_gpio_write(leds[j], switch_state);
            bcm2835_delay(80);
        }
    }
}

void setup()
{
    bcm2835_gpio_fsel(led_1, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(led_2, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(led_3, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(led_4, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(led_5, BCM2835_GPIO_FSEL_OUTP);

    bcm2835_gpio_fsel(button, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(button, BCM2835_GPIO_PUD_UP);
}


int main() {
    
    if(!bcm2835_init())
    {
        std::cerr << "BCM2835 init failed. Are you running as root?\n";
        return 1;
    }else
    {
        setup();
    }

    std::uint8_t counter = 0;
    do
    {
        if(bcm2835_gpio_lev(button) == LOW)
        {
            ++counter;
            run_led();
        }
    }while(counter < 3);
    bcm2835_close();
    return 0;
}

