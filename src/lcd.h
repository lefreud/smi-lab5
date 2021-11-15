#ifndef LCD_H_
#define LCD_H_

//Numbers of the Keypad
#define NUMBER1				"00110001"
#define NUMBER2				"00110010"
#define NUMBER3				"00110011"
#define NUMBER4				"00110100"
#define NUMBER5				"00110101"
#define NUMBER6				"00110110"
#define NUMBER7				"00110111"
#define NUMBER8				"00111000"
#define NUMBER9				"00111001"

// Functions
void lcd_init();
void lcd_write_first_row();
void lcd_write_characters(char* characters);
void LCD_pre_Send_Command();
void LCD_post_Send();
void LCD_pre_Write_Command();
void LCD_write_Instruction(char* instruction);
void lcd_write_time(int currentTime);
void goToFirstLine();
void goToSecondLine();
void lcd_write_blank_space();
char* charToBinary(char c, char* binaryForm);

#endif /* LCD_H_ */
