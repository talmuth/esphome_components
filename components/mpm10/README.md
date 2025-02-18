MPM10
===============================

The ``mpm10`` sensor platform allows you to use
 [MemsFrontier MPM10 SERIES Laser Particle Sensor](https://pdf.directindustry.com/pdf/shenzhen-memsfrontier-electronics-co-ltd/memsfrontier-mpm10-series-laser-particle-sensor/238643-975540-_5.html) sensors with ESPHome.

The [I²C Bus]([https://esphome.io/components/i2c#i2c]) is required to be set up in your configuration for this sensor to work.
This sensor supports both UART and I²C communication. However, at the moment only I²C communication is implemented. The implementation of this component was caused by a desire to put Esphome into [RoomSense IQ](https://www.roomsenselabs.com/), which using this sensor connected using I²C for its  [Climatesense](https://www.roomsenselabs.com/climatesense) extenstion.

Example:

```yaml
  - platform: mpm10
    pm_1_0:
      name: "PM <1µm concentration value (standard particulate matter)"
    pm_2_5:
      name: "PM <2.5µm concentration value (standard particulate matter)"
    pm_10_0:
      name: "PM <10µm concentration value (standard particulate matter)"
```

Configuration variables
------------------------

- **pm_1_0** (*Optional*): PM1.0 concentration value (standard particulate matter), µg/m³.

  - All options from [Sensor](https://esphome.io/components/sensor/#config-sensor).

- **pm_2_5** (*Optional*): PM2.5 concentration value (standard particulate matter), µg/m³.

  - All options from [Sensor](https://esphome.io/components/sensor/#config-sensor).

- **pm_10_0** (*Optional*): Pm10 concentration value (standard particulate matter), µg/m³.

  - All options from [Sensor](https://esphome.io/components/sensor/#config-sensor).

- **pm_1_0_atm** (*Optional*): PM1.0 concentration value (atmospheric environment), µg/m³.

  - All options from [Sensor](https://esphome.io/components/sensor/#config-sensor).

- **pm_2_5_atm** (*Optional*): PM2.5 concentration value (atmospheric environment), µg/m³.

  - All options from [Sensor](https://esphome.io/components/sensor/#config-sensor).

- **pm_10_0_atm** (*Optional*): Pm10 concentration value (atmospheric environment), µg/m³.

  - All options from [Sensor](https://esphome.io/components/sensor/#config-sensor).

- **pm_0_1_0_3** (*Optional*): The number of particulate matters with diameter of over 0.1µm in 0.3L air (*adjusted to #/cm³*)

  - All options from [Sensor](https://esphome.io/components/sensor/#config-sensor).

- **pm_0_1_0_5** (*Optional*): The number of particulate matters with diameter of over 0.1µm in 0.5L air (*adjusted to #/cm³*)

  - All options from [Sensor](https://esphome.io/components/sensor/#config-sensor).

- **pm_0_1_1_0** (*Optional*): The number of particulate matters with diameter of over 0.1µm in 1.0L air (*adjusted to #/cm³*)

  - All options from [Sensor](https://esphome.io/components/sensor/#config-sensor).

- **pm_0_1_2_5** (*Optional*): The number of particulate matters with diameter of over 0.1µm in 2.5L air (*adjusted to #/cm³*)

  - All options from [Sensor](https://esphome.io/components/sensor/#config-sensor).

- **pm_0_1_5_0** (*Optional*): The number of particulate matters with diameter of over 0.1µm in 5.0L air (*adjusted to #/cm³*)

  - All options from [Sensor](https://esphome.io/components/sensor/#config-sensor).

- **pm_0_1_10_0** (*Optional*): The number of particulate matters with diameter of over 0.1µm in 10.0L air (*adjusted to #/cm³*)

  - All options from [Sensor](https://esphome.io/components/sensor/#config-sensor).

*Note:*
The standard particulate matter value is typically adjusted for consistency across different measurement systems.
The atmospheric environment value is a raw, real-world measurement without adjustment for laboratory conditions.

You don't really need anything besides pm0_1-pm_10 (or pm0_1_0_atm-pm10_0_atm), but since it is possible to get data from sensor itself, it is availiable to read via integration.
