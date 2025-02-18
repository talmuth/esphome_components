import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c, sensor, sensirion_common
from esphome import automation
from esphome.automation import maybe_simple_id
from esphome.const import (
    CONF_ID,

    ICON_COUNTER,
    UNIT_COUNTS_PER_CUBIC_CENTIMETER,
    
    CONF_PM_1_0,
    CONF_PM_2_5,
    CONF_PM_10_0,

    DEVICE_CLASS_PM1,
    DEVICE_CLASS_PM10,
    DEVICE_CLASS_PM25,
    STATE_CLASS_MEASUREMENT,
    UNIT_MICROGRAMS_PER_CUBIC_METER,
    ICON_CHEMICAL_WEAPON,
)

CODEOWNERS = ["@talmuth"]
DEPENDENCIES = ["i2c"]

mpm10_ns = cg.esphome_ns.namespace("mpm10")
MPM10Component = mpm10_ns.class_(
    "MPM10Component", cg.PollingComponent
)

CONF_PM_1_0_ATM     = "pm_1_0_atm"
CONF_PM_2_5_ATM     = "pm_2_5_atm"
CONF_PM_10_0_ATM    = "pm_10_0_atm"

CONF_PM_0_1_0_3     = "pm_0_1_0_3"
CONF_PM_0_1_0_5     = "pm_0_1_0_5"
CONF_PM_0_1_1_0     = "pm_0_1_1_0"
CONF_PM_0_1_2_5     = "pm_0_1_2_5"
CONF_PM_0_1_5_0     = "pm_0_1_5_0"
CONF_PM_0_1_10_0    = "pm_0_1_10_0"

# Actions
StartFanAction = mpm10_ns.class_("StartFanAction", automation.Action)

CONF_AUTO_CLEANING_INTERVAL = "auto_cleaning_interval"

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(MPM10Component),
            cv.Optional(CONF_PM_1_0): sensor.sensor_schema(
                unit_of_measurement=UNIT_MICROGRAMS_PER_CUBIC_METER,
                icon=ICON_CHEMICAL_WEAPON,
                accuracy_decimals=2,
                device_class=DEVICE_CLASS_PM1,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_PM_2_5): sensor.sensor_schema(
                unit_of_measurement=UNIT_MICROGRAMS_PER_CUBIC_METER,
                icon=ICON_CHEMICAL_WEAPON,
                accuracy_decimals=2,
                device_class=DEVICE_CLASS_PM25,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_PM_10_0): sensor.sensor_schema(
                unit_of_measurement=UNIT_MICROGRAMS_PER_CUBIC_METER,
                icon=ICON_CHEMICAL_WEAPON,
                accuracy_decimals=2,
                device_class=DEVICE_CLASS_PM10,
                state_class=STATE_CLASS_MEASUREMENT,
            ),

            cv.Optional(CONF_PM_1_0_ATM): sensor.sensor_schema(
                unit_of_measurement=UNIT_MICROGRAMS_PER_CUBIC_METER,
                icon=ICON_CHEMICAL_WEAPON,
                accuracy_decimals=2,
                device_class=DEVICE_CLASS_PM1,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_PM_2_5_ATM): sensor.sensor_schema(
                unit_of_measurement=UNIT_MICROGRAMS_PER_CUBIC_METER,
                icon=ICON_CHEMICAL_WEAPON,
                accuracy_decimals=2,
                device_class=DEVICE_CLASS_PM25,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_PM_10_0_ATM): sensor.sensor_schema(
                unit_of_measurement=UNIT_MICROGRAMS_PER_CUBIC_METER,
                icon=ICON_CHEMICAL_WEAPON,
                accuracy_decimals=2,
                device_class=DEVICE_CLASS_PM10,
                state_class=STATE_CLASS_MEASUREMENT,
            ),


            cv.Optional(CONF_PM_0_1_0_3): sensor.sensor_schema(
                unit_of_measurement=UNIT_COUNTS_PER_CUBIC_CENTIMETER,
                icon=ICON_COUNTER,
                accuracy_decimals=2,
                device_class=DEVICE_CLASS_PM1,
                state_class=STATE_CLASS_MEASUREMENT,
            ),

            cv.Optional(CONF_PM_0_1_0_5): sensor.sensor_schema(
                unit_of_measurement=UNIT_COUNTS_PER_CUBIC_CENTIMETER,
                icon=ICON_COUNTER,
                accuracy_decimals=2,
                device_class=DEVICE_CLASS_PM1,
                state_class=STATE_CLASS_MEASUREMENT,
            ),

            cv.Optional(CONF_PM_0_1_1_0): sensor.sensor_schema(
                unit_of_measurement=UNIT_COUNTS_PER_CUBIC_CENTIMETER,
                icon=ICON_COUNTER,
                accuracy_decimals=2,
                device_class=DEVICE_CLASS_PM1,
                state_class=STATE_CLASS_MEASUREMENT,
            ),

            cv.Optional(CONF_PM_0_1_2_5): sensor.sensor_schema(
                unit_of_measurement=UNIT_COUNTS_PER_CUBIC_CENTIMETER,
                icon=ICON_COUNTER,
                accuracy_decimals=2,
                device_class=DEVICE_CLASS_PM1,
                state_class=STATE_CLASS_MEASUREMENT,
            ),

            cv.Optional(CONF_PM_0_1_5_0): sensor.sensor_schema(
                unit_of_measurement=UNIT_COUNTS_PER_CUBIC_CENTIMETER,
                icon=ICON_COUNTER,
                accuracy_decimals=2,
                device_class=DEVICE_CLASS_PM1,
                state_class=STATE_CLASS_MEASUREMENT,
            ),

            cv.Optional(CONF_PM_0_1_10_0): sensor.sensor_schema(
                unit_of_measurement=UNIT_COUNTS_PER_CUBIC_CENTIMETER,
                icon=ICON_COUNTER,
                accuracy_decimals=2,
                device_class=DEVICE_CLASS_PM1,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
        }
    )
    .extend(cv.polling_component_schema("60s"))
    .extend(i2c.i2c_device_schema(0x4d))
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)

    if CONF_PM_1_0 in config:
        sens = await sensor.new_sensor(config[CONF_PM_1_0])
        cg.add(var.set_pm_1_0_sensor(sens))

    if CONF_PM_2_5 in config:
        sens = await sensor.new_sensor(config[CONF_PM_2_5])
        cg.add(var.set_pm_2_5_sensor(sens))

    if CONF_PM_10_0 in config:
        sens = await sensor.new_sensor(config[CONF_PM_10_0])
        cg.add(var.set_pm_10_0_sensor(sens))

    if CONF_PM_1_0_ATM in config:
        sens = await sensor.new_sensor(config[CONF_PM_1_0_ATM])
        cg.add(var.set_pm_1_0_atm_sensor(sens))

    if CONF_PM_2_5_ATM in config:
        sens = await sensor.new_sensor(config[CONF_PM_2_5_ATM])
        cg.add(var.set_pm_2_5_atm_sensor(sens))

    if CONF_PM_10_0_ATM in config:
        sens = await sensor.new_sensor(config[CONF_PM_10_0_ATM])
        cg.add(var.set_pm_10_0_atm_sensor(sens))

    if CONF_AUTO_CLEANING_INTERVAL in config:
        cg.add(var.set_auto_cleaning_interval(config[CONF_AUTO_CLEANING_INTERVAL]))

    if CONF_PM_0_1_0_3 in config:
        sens = await sensor.new_sensor(config[CONF_PM_0_1_0_3])
        cg.add(var.set_pm_0_1_0_3_sensor(sens))

    if CONF_PM_0_1_0_5 in config:
        sens = await sensor.new_sensor(config[CONF_PM_0_1_0_5])
        cg.add(var.set_pm_0_1_0_5_sensor(sens))

    if CONF_PM_0_1_1_0 in config:
        sens = await sensor.new_sensor(config[CONF_PM_0_1_1_0])
        cg.add(var.set_pm_0_1_1_0_sensor(sens))

    if CONF_PM_0_1_2_5 in config:
        sens = await sensor.new_sensor(config[CONF_PM_0_1_2_5])
        cg.add(var.set_pm_0_1_2_5_sensor(sens))

    if CONF_PM_0_1_5_0 in config:
        sens = await sensor.new_sensor(config[CONF_PM_0_1_5_0])
        cg.add(var.set_pm_0_1_5_0_sensor(sens))

    if CONF_PM_0_1_10_0 in config:
        sens = await sensor.new_sensor(config[CONF_PM_0_1_10_0])
        cg.add(var.set_pm_0_1_10_0_sensor(sens))


MPM10_ACTION_SCHEMA = maybe_simple_id(
    {
        cv.Required(CONF_ID): cv.use_id(MPM10Component),
    }
)
