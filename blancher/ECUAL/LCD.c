#include "LCD.h"
#include "../MCAL/DIO.h"

//Configuration global struct
static modbus_config g_LCD_modbus_config;



/* _____callback functions_____________________________________________________ */
void LCD_pre_transmission(void) {
	/*Mode_bus_1_change_state*/
	Modbus_change_state(LCD,HIGH);
}

void LCD_post_transmission(void) {
	Modbus_change_state(LCD,LOW);
}


/* _____initialization Global_____________________________________________________ */
void Lcd_init(UART_Modules uart_n,uint32_t baudrate,uint8_t slaveID){
//make sure that DIO_init called first	
	g_LCD_modbus_config.slave_address = slaveID;
	g_LCD_modbus_config.uart_num = uart_n;
	g_LCD_modbus_config.baud_rate= baudrate;
	g_LCD_modbus_config.pre_transmission = LCD_pre_transmission;
	g_LCD_modbus_config.post_transmission = LCD_post_transmission;
	Modbus_init(LCD , &(g_LCD_modbus_config));

}//end Lcd_init


/***********************************************************************************************************
 *
 *                    LCD General Functions 
 * 
************************************************************************************************************/
//
uint16_t Lcd_Read(uint16_t address,uint16_t *pData){
    int err_4 = Modbus_Read_holding_registers(LCD,address, 1);
    if(!err_4){
        *pData=Modbus_Get_response_buffer(LCD,0);
		UART0_puts("RECEEEEEEVIVING \n ");
		
    }
     return LCD_READ_ERROR;
}

//
void Lcd_Write(uint16_t address, uint16_t value){
	Modbus_Set_transmit_buffer(LCD,0, value);
    Modbus_Write_multiple_registers(LCD,address, 0x01);
}


/***********************************************************************************************************
 *
 *                    LCD Multiple Data functions 
 * 
************************************************************************************************************/

uint16_t Lcd_Read_multiple_data(uint16_t address ,uint16_t *pData,uint8_t QTY){
	int err = Modbus_Read_holding_registers(LCD,address,QTY);
	if(err == 0){
		for(uint8_t i=0; i<QTY;i++){
			(*(pData+i)) = Modbus_Get_response_buffer(LCD,i);
		}
		return LCD_OK;	
	}
	else {
		return LCD_READ_ERROR;
	}

}

void Lcd_Write_multiple_data(uint16_t address ,uint16_t *pData,uint8_t QTY){
	for(uint8_t i=0;i<QTY;i++){
		Modbus_Set_transmit_buffer(LCD,i, (*(pData+i)));
	}
	Modbus_Write_multiple_registers(LCD,address,QTY);
	
}

/***********************************************************************************************************
 *
 *                   LCD Special Functions
 * 
************************************************************************************************************/

// jump to spacific image
void lcd_Jump_to(uint16_t pic_id){ // v
	
		Modbus_Set_transmit_buffer(LCD,0,pic_id);
		Modbus_Our_write_multiple_coils(LCD,LCD_CURRENT_PIC_REG, 1);
		
}

// to open buzzer to 2 second pass 200 to this function
void lcd_Open_buzzer(uint16_t value){ //v

		Modbus_Set_transmit_buffer(LCD,0,value);
		Modbus_Write_multiple_coils(LCD,LCD_BUZZER_REG, 1);

}





