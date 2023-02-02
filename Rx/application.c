 /* 
 * File:   application.c
 * Author: Mohamed_Nagy
 * https://www.linkedin.com/in/mohamednagyofficial/
 * Created on January 27, 2022, 8:41 PM
 */

#include "application.h"
Std_ReturnType ret = E_NOT_OK;
void usart_rx_int_handeler();

led_t led_1 = 
{
    .port_name = PORTD_INDEX,
    .pin = GPIO_PIN0,
    .led_status = LED_OFF
};


usart_t usart_1 = 
{
    .baudrate = 9600,
    .baudrate_gen_gonfig = BAUDRATE_ASYN_8BIT_lOW_SPEED,
            
    .usart_tx_cfg.usart_tx_enable = EUSART_ASYNCHRONOUS_TX_ENABLE,
    .usart_tx_cfg.usart_tx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE,
    .usart_tx_cfg.usart_tx_9bit_enable = EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE,
    
    .usart_rx_cfg.usart_rx_enable = EUSART_ASYNCHRONOUS_RX_ENABLE,
    .usart_rx_cfg.usart_rx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE,
    .usart_rx_cfg.usart_rx_9bit_enable = EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE,    

    .EUSART_RxDefaultInterruptHandler = usart_rx_int_handeler,
    .EUSART_FramingErrorHandler = NULL,
    .EUSART_OverrunErrorHandler = NULL,
    .EUSART_TxDefaultInterruptHandler = NULL
};


volatile uint8 rx_data;

int main() 
{ 
    application_intialize();
    while(1)
    {    
        
    }   
    return (EXIT_SUCCESS);
}

void application_intialize(void)
{
    ecu_layer_intialize();
    ret = led_initialize(&led_1);
    ret = EUSART_ASYNC_Init(&usart_1);
}


// Reciever

void usart_rx_int_handeler()
{
    EUSART_ASYNC_ReadByteBlocking(&rx_data);
    if(rx_data == 'a')
    {
        ret = led_turn_on(&led_1);
        ret = EUSART_ASYNC_WriteByteBlocking('c');
    }
    else if(rx_data == 'b')
    {
        ret = led_turn_off(&led_1);
        ret = EUSART_ASYNC_WriteByteBlocking('d');
    }
}

