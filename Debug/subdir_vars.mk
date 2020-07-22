################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../CC3220SF_LAUNCHXL_FREERTOS.cmd 

SYSCFG_SRCS += \
../empty.syscfg 

C_SRCS += \
../debug_if.c \
./syscfg/ti_drivers_config.c \
../main_freertos.c \
../sensors_main.c \
../sensors_queues.c \
../task_rgb.c \
../task_ultrasonic.c \
../timerRGB.c \
../timerUS.c \
../uart_term.c 

GEN_FILES += \
./syscfg/ti_drivers_config.c 

GEN_MISC_DIRS += \
./syscfg/ 

C_DEPS += \
./debug_if.d \
./syscfg/ti_drivers_config.d \
./main_freertos.d \
./sensors_main.d \
./sensors_queues.d \
./task_rgb.d \
./task_ultrasonic.d \
./timerRGB.d \
./timerUS.d \
./uart_term.d 

OBJS += \
./debug_if.obj \
./syscfg/ti_drivers_config.obj \
./main_freertos.obj \
./sensors_main.obj \
./sensors_queues.obj \
./task_rgb.obj \
./task_ultrasonic.obj \
./timerRGB.obj \
./timerUS.obj \
./uart_term.obj 

GEN_MISC_FILES += \
./syscfg/ti_drivers_config.h \
./syscfg/syscfg_c.rov.xs 

GEN_MISC_DIRS__QUOTED += \
"syscfg\" 

OBJS__QUOTED += \
"debug_if.obj" \
"syscfg\ti_drivers_config.obj" \
"main_freertos.obj" \
"sensors_main.obj" \
"sensors_queues.obj" \
"task_rgb.obj" \
"task_ultrasonic.obj" \
"timerRGB.obj" \
"timerUS.obj" \
"uart_term.obj" 

GEN_MISC_FILES__QUOTED += \
"syscfg\ti_drivers_config.h" \
"syscfg\syscfg_c.rov.xs" 

C_DEPS__QUOTED += \
"debug_if.d" \
"syscfg\ti_drivers_config.d" \
"main_freertos.d" \
"sensors_main.d" \
"sensors_queues.d" \
"task_rgb.d" \
"task_ultrasonic.d" \
"timerRGB.d" \
"timerUS.d" \
"uart_term.d" 

GEN_FILES__QUOTED += \
"syscfg\ti_drivers_config.c" 

C_SRCS__QUOTED += \
"../debug_if.c" \
"./syscfg/ti_drivers_config.c" \
"../main_freertos.c" \
"../sensors_main.c" \
"../sensors_queues.c" \
"../task_rgb.c" \
"../task_ultrasonic.c" \
"../timerRGB.c" \
"../timerUS.c" \
"../uart_term.c" 

SYSCFG_SRCS__QUOTED += \
"../empty.syscfg" 


