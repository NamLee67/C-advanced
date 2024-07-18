#include "max30102_driver.h"
#include <stdio.h>

void max30102_init(max30102_t *obj, I2C_HandleTypeDef *hi2c){
    obj->_ui2c = hi2c;
    obj->_interrupt_flag = 0;
    memset(obj->_ir_samples, 0, MAX30102_SAMPLE_LEN_MAX*sizeof(max30102_t));
    memset(obj->_red_samples, 0, MAX30102_SAMPLE_LEN_MAX*sizeof(max30102_t));
}   

void max30102_write(max30102_t *obj,uint8_t reg, uint8_t *buf, uint16_t buflen){
    uint8_t *tmp = (uint8_t *)malloc((buflen+1)*sizeof(uint8_t));  // lưu đủ (buflen byte data) + (1 byte chứa địa chỉ cảm biến)
    *tmp = reg; // ghi dia chi cua thanh ghi vao dau mang
    // uint8_t tx_buf[buflen+1];
    // tx_buf[0] = reg;
    if(buf!=NULL)   memcpy(tmp + 1, buf, buflen); // copy (buflen data) từ *buf vào tmp từ index 1 ( index 0 đã lưu trữ địa chỉ cảm biến)
    HAL_I2C_Master_Transmit(obj->_ui2c, (MAX30102_I2C_ADDR << 1), tmp, buflen+1, 1000);   // truyền ( địa chỉ và data) từ master đến slave
    free(tmp);
}

void max30102_read(max30102_t *obj,uint8_t reg, uint8_t *buf, uint16_t buflen) {
    HAL_I2C_Master_Transmit(obj->_ui2c, (MAX30102_I2C_ADDR << 1), &reg, 1, 1000);
    HAL_I2C_Master_Receive(obj->_ui2c, (MAX30102_I2C_ADDR << 1), buf, buflen, 1000);
}   

void max30102_reset(max30102_t *obj){
    uint8_t reset = 0x40;   // bit reset là bit 6 0x0100 0000
    max30102_write(obj, MAX30102_MODE_CONFIG, &reset, 1);
}

void max30102_sutdown(max30102_t *obj, uint8_t sutdown){
    uint8_t shdn_config;
    max30102_read(obj, MAX30102_MODE_CONFIG, &shdn_config, 1);
    shdn_config |= (shdn_config & 0x7f) | (sutdown << MAX30102_MODE_SHDN);
    max30102_write(obj, MAX30102_MODE_CONFIG, &shdn_config, 1);
}
void max30102_mode_config(max30102_t *obj, max30102_mode_t mode){
    uint8_t mode_config;
    max30102_read(obj, MAX30102_MODE_CONFIG, &mode_config, 1);
    mode_config |= (mode_config & 0xF8) | (mode);
    max30102_write(obj, MAX30102_MODE_CONFIG, &mode_config, 1);
    max30102_clear_fifo(obj);
}

void max30102_set_fifo_config(max30102_t *obj, max30102_smp_ave_t smp_ave, uint8_t roll_over_en, uint8_t fifo_a_full) {
    uint8_t fifo_config;   // ghi các thông số vào thanh ghi fifo config
    max30102_read(obj, MAX30102_FIFO_CONFIG, &fifo_config, 1);   
    fifo_config = (fifo_config & 0x1F) | (smp_ave << MAX30102_FIFO_SMP_AVE);
    fifo_config = (fifo_config & 0xEF) | (roll_over_en << MAX30102_FIFO_ROLLOVER_EN);
    fifo_config = (fifo_config & 0xF0) | (fifo_a_full);
    max30102_write(obj, MAX30102_FIFO_CONFIG, &fifo_config, 1);                 // roll_over_en: lên 1 thì fifo sẽ về địa chỉ 0 và bắt đầu ghi lại dữ liệu mới
}

void max30102_clear_fifo(max30102_t *obj){
    uint8_t clear_fifo = 0x00;
    max30102_write(obj, MAX30102_FIFO_RD_PTR, &clear_fifo, 1);
    max30102_write(obj, MAX30102_FIFO_WR_PTR, &clear_fifo, 1);
    max30102_write(obj, MAX30102_OVF_COUNTER, &clear_fifo, 1);
}

void max30102_spo2_config(max30102_t *obj,max30102_adc_t spo2_adc, max30102_sr_t spo2_sr, max30102_led_pw_t led_pw){
    uint8_t spo2_config = (spo2_adc << MAX30102_SPO2_ADC_RGE) | (spo2_sr << MAX30102_SPO2_SR) | (led_pw);
    max30102_read(obj, MAX30102_SPO2_CONFIG, &spo2_config, 1);
    spo2_config = (spo2_config & 0x1F) | (spo2_adc << MAX30102_SPO2_ADC_RGE);
    spo2_config = (spo2_config & 0x63) | (spo2_sr << MAX30102_SPO2_SR);
    spo2_config = (spo2_config & 0x7C) | (led_pw);
    max30102_write(obj,MAX30102_SPO2_CONFIG, &spo2_config, 1);
}

void max30102_set_led_current_1(max30102_t *obj, float ma)
{
    uint8_t pa = ma / 0.2;
    max30102_write(obj, MAX30102_LED_IR_PA1, &pa, 1);
}

void max30102_set_led_current_2(max30102_t *obj, float ma)
{
    uint8_t pa = ma / 0.2;
    max30102_write(obj, MAX30102_LED_RED_PA2, &pa, 1);
}

void max30102_multi_led_1_2(max30102_t *obj, max30102_multi_led_ctrl_t led_slot1, max30102_multi_led_ctrl_t led_slot2){
    uint8_t led_ctrl= 0;
    led_ctrl |= (led_slot1 << MAX30102_MULTI_LED_CTRL_SLOT1) | (led_slot2 << MAX30102_MULTI_LED_CTRL_SLOT2);
    max30102_write(obj, MAX30102_MULTI_LED_CTRL_1, &led_ctrl, 1);
}

void max30102_multi_led_3_4(max30102_t *obj, max30102_multi_led_ctrl_t led_slot3, max30102_multi_led_ctrl_t led_slot4){
    uint8_t led_ctrl = 0;
    led_ctrl |= (led_slot3 << MAX30102_MULTI_LED_CTRL_SLOT3) | (led_slot4 << MAX30102_MULTI_LED_CTRL_SLOT4);
    max30102_write(obj, MAX30102_MULTI_LED_CTRL_2, &led_ctrl, 1);
}

void max30102_read_temp(max30102_t *obj, uint8_t enable, int8_t *temp_int, uint8_t *temp_frac){
    uint8_t temp_enable = (enable & 0x01) << MAX30102_DIE_TEMP_EN ;
    max30102_write(obj, MAX30102_DIE_TEMP_CONFIG, &temp_enable, 1);
    if(enable == 1){
        max30102_read(obj, MAX30102_DIE_TINT, temp_int, 1);
        max30102_read(obj, MAX30102_DIE_TFRAC, temp_frac, 1);
    }
}

void max30102_read_fifo(max30102_t *obj){
    // đọc số sample có trong fifo data
    uint8_t rd_ptr = 0;
    uint8_t wr_ptr = 0;
    max30102_read(obj, MAX30102_FIFO_RD_PTR, &rd_ptr, 1);
    max30102_read(obj, MAX30102_FIFO_WR_PTR, &wr_ptr, 1);

    int8_t num_samples = wr_ptr - rd_ptr;
    if(num_samples < 0){
        num_samples += 32;
    }
    // read data 
    for(int i=0; i < num_samples; i++){
        uint8_t sample[6];
        uint32_t ir_sample = ((uint32_t)(sample[0] << 16) | (uint32_t)(sample[1] << 8) | (uint32_t)(sample[2])) &(0x3FFFF);
        uint32_t red_sample = ((uint32_t)(sample[3] << 16) | (uint32_t)(sample[4] << 8) | (uint32_t)(sample[5])) &(0x3FFFF);
        obj->_ir_samples[i] = ir_sample;
        obj->_red_samples[i] = red_sample;
    }
}

void max30102_is_interrupt(max30102_t *obj){
    return obj->_interrupt_flag;
}
