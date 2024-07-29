#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"

// Our assembled program generated header
#include "ledcounter.pio.h"


#define FIRST_PIN   2

struct taskparams
{
    PIO Pio;
    uint Sm;
};

void fifo_task(void* param)
{   
    uint32_t count = 0;

    struct taskparams params = *((struct taskparams*)param);
    
    while (true)
    {

        printf("Sending %d\n", count);

        // Put data into FIFO
        pio_sm_put_blocking(params.Pio, params.Sm, count++);

        // reset counter 
        if (count == 32) count = 0;

        // 1s delay
        vTaskDelay(250);
    }
}

int main()
{

    struct taskparams params;

    stdio_init_all();

    // Choose which PIO instance to use (there are two instances)
    PIO pio = pio0;

    // Our assembled program needs to be loaded into this PIO's instruction
    // memory. This SDK function will find a location (offset) in the
    // instruction memory where there is enough space for our program. We need
    // to remember this location!
    uint offset = pio_add_program(pio, &pioledcounter_program);

    // Find a free state machine on our chosen PIO (erroring if there are
    // none). Configure it to run our program, and start it, using the
    // helper function we included in our .pio file.
    uint sm = pio_claim_unused_sm(pio, true);

    // store params for task
    params.Pio = pio;
    params.Sm = sm;

    // calculate divider for 10MHz pio clock (system runs at 125MHz)
    float div = (float)clock_get_hz(clk_sys) / 10000000.0;
    div = 1.0f;
    pioledcounter_program_init(pio, sm, offset, FIRST_PIN, div);

    xTaskCreate(fifo_task, "FIFO_Task", 256, &params, 1, NULL);
    vTaskStartScheduler();

    while(1){};
}
