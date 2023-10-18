#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"

void printf_studentID(void *pvParameter) {
  while(1) {
    printf("Quach Vu Giang Nam - 1914251\n");
    printf("Luu Vinh Loi - 2010044\n");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void read_button(void *param) {
  gpio_pad_select_gpio(GPIO_NUM_18);
  gpio_pad_select_gpio(GPIO_NUM_2);
  gpio_set_direction(GPIO_NUM_18, GPIO_MODE_INPUT);
  gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
  gpio_set_pull_mode(GPIO_NUM_18, GPIO_PULLUP_ONLY);
  bool currentStatus = 1, previousStatus = 1;
  int count = 0;
  while(1) {
    currentStatus = gpio_get_level(GPIO_NUM_18);
    if (currentStatus == previousStatus && currentStatus == 0) {
      if (count == 0) {
        printf("ESP32\n");
        gpio_set_level(GPIO_NUM_2, 1);
      }
      count++;
    }
    else {
      previousStatus = currentStatus;
      count = 0;
    }
    vTaskDelay(20 / portTICK_PERIOD_MS);
  }
}

void app_main(void)
{
    xTaskCreate(printf_studentID, "Printf student ID", 2048, NULL, 5, NULL);
    xTaskCreate(read_button, "Reading from button", 2048, NULL, 6, NULL);
}
