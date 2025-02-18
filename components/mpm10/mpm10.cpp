#include "esphome/core/hal.h"
#include "esphome/core/log.h"

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/i2c/i2c.h"

#include "mpm10.h"

namespace esphome {
namespace mpm10 {
  static const uint8_t MPM10_CMD_MEASURE_PM1_0_HIGH   = 0x20;
  static const uint8_t MPM10_CMD_MEASURE_PM1_0_LOW    = 0x21;
  static const uint8_t MPM10_CMD_MEASURE_PM2_5_HIGH   = 0x22;
  static const uint8_t MPM10_CMD_MEASURE_PM2_5_LOW    = 0x23;
  static const uint8_t MPM10_CMD_MEASURE_PM10_0_HIGH  = 0x24;
  static const uint8_t MPM10_CMD_MEASURE_PM10_0_LOW   = 0x25;
  
  static const uint8_t MPM10_CMD_MEASURE_PM1_0_ATM_HIGH     = 0x26;
  static const uint8_t MPM10_CMD_MEASURE_PM1_0_ATM_LOW      = 0x27;
  static const uint8_t MPM10_CMD_MEASURE_PM2_5_ATM_HIGH     = 0x28;
  static const uint8_t MPM10_CMD_MEASURE_PM2_5_ATM_LOW      = 0x29;
  static const uint8_t MPM10_CMD_MEASURE_PM10_0_ATM_HIGH    = 0x2A;
  static const uint8_t MPM10_CMD_MEASURE_PM10_0_ATM_LOW     = 0x2B;
  
  static const uint8_t MPM10_CMD_MEASURE_0_1_IN_0_3L_HIGH   = 0x2C;
  static const uint8_t MPM10_CMD_MEASURE_0_1_IN_0_3L_LOW    = 0x2D;
  static const uint8_t MPM10_CMD_MEASURE_0_1_IN_0_5L_HIGH   = 0x2E;
  static const uint8_t MPM10_CMD_MEASURE_0_1_IN_0_5L_LOW    = 0x2F;
  static const uint8_t MPM10_CMD_MEASURE_0_1_IN_1_0L_HIGH   = 0x30;
  static const uint8_t MPM10_CMD_MEASURE_0_1_IN_1_0L_LOW    = 0x31;
  static const uint8_t MPM10_CMD_MEASURE_0_1_IN_2_5L_HIGH   = 0x32;
  static const uint8_t MPM10_CMD_MEASURE_0_1_IN_2_5L_LOW    = 0x33;
  static const uint8_t MPM10_CMD_MEASURE_0_1_IN_5_0L_HIGH   = 0x34;
  static const uint8_t MPM10_CMD_MEASURE_0_1_IN_5_0L_LOW    = 0x35;
  static const uint8_t MPM10_CMD_MEASURE_0_1_IN_10_0L_HIGH  = 0x36;
  static const uint8_t MPM10_CMD_MEASURE_0_1_IN_10_0L_LOW   = 0x37;   



  // Method called during setup
  void MPM10Component::setup() {
    ESP_LOGD(TAG, "mpm10 Sensor Initialized");
  }

  // Method called every polling interval
  void MPM10Component::update()  {
    ESP_LOGD(TAG, "mpm10 Sensor Update");

    std::vector<SensorData> sensors = {
      {pm_1_0_sensor, MPM10_CMD_MEASURE_PM1_0_HIGH, MPM10_CMD_MEASURE_PM1_0_LOW, 1, "Standard PM1.0: %d µg/m³"},
      {pm_2_5_sensor, MPM10_CMD_MEASURE_PM2_5_HIGH, MPM10_CMD_MEASURE_PM2_5_LOW, 1, "Standard PM2.5: %d µg/m³"},
      {pm_10_0_sensor, MPM10_CMD_MEASURE_PM10_0_HIGH, MPM10_CMD_MEASURE_PM10_0_LOW, 1, "Standard PM10.0: %d µg/m³"},
      {pm_1_0_atm_sensor, MPM10_CMD_MEASURE_PM1_0_ATM_HIGH, MPM10_CMD_MEASURE_PM1_0_ATM_LOW, 1, "Environmental PM1.0: %d µg/m³"},
      {pm_2_5_atm_sensor, MPM10_CMD_MEASURE_PM2_5_ATM_HIGH, MPM10_CMD_MEASURE_PM2_5_ATM_LOW, 1, "Environmental PM2.5: %d µg/m³"},
      {pm_10_0_atm_sensor, MPM10_CMD_MEASURE_PM10_0_ATM_HIGH, MPM10_CMD_MEASURE_PM10_0_ATM_LOW, 1, "Environmental PM10.0: %d µg/m³"},
      {pm_0_1_0_3_sensor, MPM10_CMD_MEASURE_0_1_IN_0_3L_HIGH, MPM10_CMD_MEASURE_0_1_IN_0_3L_LOW, 300, "Counts in 0.3L (adjusted for #/cm³): %d"},
      {pm_0_1_0_5_sensor, MPM10_CMD_MEASURE_0_1_IN_0_5L_HIGH, MPM10_CMD_MEASURE_0_1_IN_0_5L_LOW, 500, "Counts in 0.5L (adjusted for #/cm³): %d"},
      {pm_0_1_1_0_sensor, MPM10_CMD_MEASURE_0_1_IN_1_0L_HIGH, MPM10_CMD_MEASURE_0_1_IN_1_0L_LOW, 1000, "Counts in 1.0L (adjusted for #/cm³): %d"},
      {pm_0_1_2_5_sensor, MPM10_CMD_MEASURE_0_1_IN_2_5L_HIGH, MPM10_CMD_MEASURE_0_1_IN_2_5L_LOW, 2500, "Counts in 2.5L (adjusted for #/cm³): %d"},
      {pm_0_1_5_0_sensor, MPM10_CMD_MEASURE_0_1_IN_5_0L_HIGH, MPM10_CMD_MEASURE_0_1_IN_5_0L_LOW, 5000, "Counts in 5.0L (adjusted for #/cm³): %d"},
      {pm_0_1_10_0_sensor, MPM10_CMD_MEASURE_0_1_IN_10_0L_HIGH, MPM10_CMD_MEASURE_0_1_IN_10_0L_LOW, 10000, "Counts in 10.0L (adjusted for #/cm³): %d"}
    };

    for (const auto &sensor_data : sensors) {
      if (sensor_data.sensor != nullptr) {
        uint16_t measurement = read_pm_value(sensor_data.high_cmd, sensor_data.low_cmd);

        if (1 !=  sensor_data.divisor) {
          ESP_LOGVV(TAG, "Adjusting reading %d/%d", measurement, sensor_data.divisor);
          measurement /= sensor_data.divisor;
        }
  
        ESP_LOGD(TAG, sensor_data.description, measurement);
        sensor_data.sensor->publish_state(measurement);
      }
    }
  }

  void MPM10Component::dump_config()  {
    ESP_LOGCONFIG(TAG, "mpm10 Sensor:");
    ESP_LOGCONFIG(TAG, "  I2C Address: 0x%02X", address_);

    LOG_I2C_DEVICE(this);
    LOG_UPDATE_INTERVAL(this);

    LOG_SENSOR("  ", "PM1.0 Concentration", this->pm_1_0_sensor);
    LOG_SENSOR("  ", "PM2.5 Concentration", this->pm_2_5_sensor);
    LOG_SENSOR("  ", "PM10  Concentration", this->pm_10_0_sensor);

    LOG_SENSOR("  ", "PM1.0 Atmospheric Concentration", this->pm_1_0_atm_sensor);
    LOG_SENSOR("  ", "PM2.5 Atmospheric Concentration", this->pm_2_5_atm_sensor);
    LOG_SENSOR("  ", "PM10  Atmospheric Concentration", this->pm_10_0_atm_sensor);

    LOG_SENSOR("  ", "PM0.1 in 0.3L", this->pm_0_1_0_3_sensor);
    LOG_SENSOR("  ", "PM0.1 in 0.5L", this->pm_0_1_0_5_sensor);
    LOG_SENSOR("  ", "PM0.1 in 1.0L", this->pm_0_1_1_0_sensor);
    LOG_SENSOR("  ", "PM0.1 in 2.5L", this->pm_0_1_2_5_sensor);
    LOG_SENSOR("  ", "PM0.1 in 5.0L", this->pm_0_1_5_0_sensor);
    LOG_SENSOR("  ", "PM0.1 in 10.0L", this->pm_0_1_10_0_sensor);
  }

}  // namespace mpm10
}  // namespace esphome
