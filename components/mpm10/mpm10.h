#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace mpm10 {

static const char *const TAG = "mpm10";


class MPM10Component : public PollingComponent, public i2c::I2CDevice {
 public:
  void set_pm_1_0_sensor(sensor::Sensor *sensor)  { pm_1_0_sensor = sensor;  }
  void set_pm_2_5_sensor(sensor::Sensor *sensor)  { pm_2_5_sensor = sensor;  }
  void set_pm_10_0_sensor(sensor::Sensor *sensor) { pm_10_0_sensor = sensor; }

  void set_pm_1_0_atm_sensor(sensor::Sensor *sensor)      { pm_1_0_atm_sensor = sensor;  }
  void set_pm_2_5_atm_sensor(sensor::Sensor *sensor)      { pm_2_5_atm_sensor = sensor;  }
  void set_pm_10_0_atm_sensor(sensor::Sensor *sensor)     { pm_10_0_atm_sensor = sensor; }

  void set_pm_0_1_0_3_sensor(sensor::Sensor *sensor)   { pm_0_1_0_3_sensor = sensor;  }
  void set_pm_0_1_0_5_sensor(sensor::Sensor *sensor)   { pm_0_1_0_5_sensor = sensor;  }
  void set_pm_0_1_1_0_sensor(sensor::Sensor *sensor)   { pm_0_1_1_0_sensor = sensor;  }
  void set_pm_0_1_2_5_sensor(sensor::Sensor *sensor)   { pm_0_1_2_5_sensor = sensor;  }
  void set_pm_0_1_5_0_sensor(sensor::Sensor *sensor)   { pm_0_1_5_0_sensor = sensor;  }
  void set_pm_0_1_10_0_sensor(sensor::Sensor *sensor)  { pm_0_1_10_0_sensor = sensor; }

  void setup() override;
  void update() override;
  void dump_config() override;

 protected:
  sensor::Sensor *pm_1_0_sensor{nullptr};
  sensor::Sensor *pm_2_5_sensor{nullptr};
  sensor::Sensor *pm_10_0_sensor{nullptr};

  sensor::Sensor *pm_1_0_atm_sensor{nullptr};
  sensor::Sensor *pm_2_5_atm_sensor{nullptr};
  sensor::Sensor *pm_10_0_atm_sensor{nullptr};

  sensor::Sensor *pm_0_1_0_3_sensor{nullptr};
  sensor::Sensor *pm_0_1_0_5_sensor{nullptr};
  sensor::Sensor *pm_0_1_1_0_sensor{nullptr};
  sensor::Sensor *pm_0_1_2_5_sensor{nullptr};
  sensor::Sensor *pm_0_1_5_0_sensor{nullptr};
  sensor::Sensor *pm_0_1_10_0_sensor{nullptr};


  struct SensorData {
    sensor::Sensor *sensor;
    uint8_t high_cmd;
    uint8_t low_cmd;
    uint16_t divisor;
    const char *description;
  };
  


  // Helper function to read PM values or particle counts
  uint16_t read_pm_value(uint8_t reg_high, uint8_t reg_low) {
    uint8_t high_byte, low_byte;
    
    if (!read_byte(reg_high, &high_byte)) {
      ESP_LOGW(TAG, "Failed to read high byte for register: 0x%02X", reg_high);
      return 0;
    }
    if (!read_byte(reg_low, &low_byte)) {
      ESP_LOGW(TAG, "Failed to read low byte for register: 0x%02X", reg_low);
      return 0;
    }
    return (high_byte << 8) | low_byte;
  }

  // Helper function to read a single byte from a register
  bool read_byte(uint8_t reg, uint8_t *value) {
    i2c::ErrorCode code = write(&reg, 1);
    if (i2c::ERROR_OK != code) {
      mark_failed();

      ESP_LOGW(TAG, "Failed to write to register: 0x%02X (%d)", reg, code);
      return false;
    }

    code = read(value, 1);
    if (i2c::ERROR_OK != code) {
      mark_failed();

      ESP_LOGW(TAG, "Failed to read value from register: 0x%02X (%d)", reg, code);
      return false;
    }

    return true;
  }
};

}  // namespace mpm10
}  // namespace esphome
