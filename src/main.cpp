#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include "pico/stdlib.h"

#include "MathClass.h"

MathClass *pMath;

void led_task(void*)
{   
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    TickType_t delay;
    bool fast = false, last = false;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    pMath = new MathClass(0);

    // first 8 flashes slow, second 8 fast, repeat

    while (true)
    {

        fast = pMath->value() > 4;

        if (fast != last)
        {
            const char* msg = fast ? "Fast mode" : "Slow mode";
            printf("%s\n", msg);
            last = fast;
        }

        delay = fast ? 20 : 50;
        gpio_put(LED_PIN, 1);
        printf("LED On\n");
        vTaskDelay(delay);
        gpio_put(LED_PIN, 0);
        printf("LED Off\n");
        vTaskDelay(delay);

        pMath->inc();
    
        if (pMath->value() == 10)
        {
            pMath->setValue(0);
            vTaskDelay(100);
            printf("Waiting...\n");
        } 
    }
}

int main()
{
    stdio_init_all();

    xTaskCreate(led_task, "LED_Task", 256, NULL, 1, NULL);
    vTaskStartScheduler();

    while(1){};
}
