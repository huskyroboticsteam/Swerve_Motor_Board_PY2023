# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\mewin\OneDrive\Documents\PSoC Creator\Swerve Motor Board 2023\Swerve_Motor_Board_PY2023\SwerveMotorFirmware.cydsn\SwerveMotorFirmware.cyprj
# Date: Fri, 13 Jan 2023 02:20:10 GMT
#set_units -time ns
create_clock -name {ADC_SAR_Seq_1_intClock(FFB)} -period 375 -waveform {0 187.5} [list [get_pins {ClockBlock/ff_div_10}]]
create_clock -name {UART_SCBCLK(FFB)} -period 8687.5 -waveform {0 4343.75} [list [get_pins {ClockBlock/ff_div_3}]]
create_clock -name {Clock_PWM2(FFB)} -period 83.333333333333329 -waveform {0 41.6666666666667} [list [get_pins {ClockBlock/ff_div_15}]]
create_clock -name {Clock_PWM1(FFB)} -period 83.333333333333329 -waveform {0 41.6666666666667} [list [get_pins {ClockBlock/ff_div_16}]]
create_clock -name {CyRouted1} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/dsi_in_0}]]
create_clock -name {CyILO} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyLFClk} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyIMO} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyHFClk} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/hfclk}]]
create_clock -name {CySysClk} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/sysclk}]]
create_generated_clock -name {Clock_1} -source [get_pins {ClockBlock/hfclk}] -edges {1 3 5} [list [get_pins {ClockBlock/udb_div_1}]]
create_generated_clock -name {ADC_SAR_Seq_1_intClock} -source [get_pins {ClockBlock/hfclk}] -edges {1 19 37} [list]
create_generated_clock -name {Clock_2} -source [get_pins {ClockBlock/hfclk}] -edges {1 480001 960001} [list [get_pins {ClockBlock/udb_div_2}]]
create_generated_clock -name {UART_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 417 835} [list]
create_generated_clock -name {Clock_PWM2} -source [get_pins {ClockBlock/hfclk}] -edges {1 5 9} [list]
create_generated_clock -name {Clock_PWM1} -source [get_pins {ClockBlock/hfclk}] -edges {1 5 9} [list]
create_generated_clock -name {timer_clock} -source [get_pins {ClockBlock/hfclk}] -edges {1 3 5} [list [get_pins {ClockBlock/udb_div_3}]]


# Component constraints for C:\Users\mewin\OneDrive\Documents\PSoC Creator\Swerve Motor Board 2023\Swerve_Motor_Board_PY2023\SwerveMotorFirmware.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\mewin\OneDrive\Documents\PSoC Creator\Swerve Motor Board 2023\Swerve_Motor_Board_PY2023\SwerveMotorFirmware.cydsn\SwerveMotorFirmware.cyprj
# Date: Fri, 13 Jan 2023 02:19:59 GMT
