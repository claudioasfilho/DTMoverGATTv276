################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../app/bluetooth/common/util/infrastructure.c 

OBJS += \
./app/bluetooth/common/util/infrastructure.o 

C_DEPS += \
./app/bluetooth/common/util/infrastructure.d 


# Each subdirectory must supply rules for building sources it contributes
app/bluetooth/common/util/infrastructure.o: ../app/bluetooth/common/util/infrastructure.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DNVM3_DEFAULT_NVM_SIZE=24576' '-D__HEAP_SIZE=0xD00' '-DHAL_CONFIG=1' '-D__StackLimit=0x20000000' '-D__STACK_SIZE=0x800' '-DEFR32MG21A010F1024IM32=1' -I"/Users/clfilho/SimplicityStudio/AoA/DTMoverGattxG21v2136/platform/Device/SiliconLabs/EFR32MG21/Include" -I"/Users/clfilho/SimplicityStudio/AoA/DTMoverGattxG21v2136/hardware/kit/common/drivers" -I"/Users/clfilho/SimplicityStudio/AoA/DTMoverGattxG21v2136/protocol/bluetooth/ble_stack/inc/common" -I"/Users/clfilho/SimplicityStudio/AoA/DTMoverGattxG21v2136/protocol/bluetooth/ble_stack/inc/soc" -I"/Users/clfilho/SimplicityStudio/AoA/DTMoverGattxG21v2136/platform/CMSIS/Include" -I"/Users/clfilho/SimplicityStudio/AoA/DTMoverGattxG21v2136/platform/emlib/src" -I"/Users/clfilho/SimplicityStudio/AoA/DTMoverGattxG21v2136/hardware/kit/common/halconfig" -I"/Users/clfilho/SimplicityStudio/AoA/DTMoverGattxG21v2136/platform/emdrv/nvm3/inc" -I"/Users/clfilho/SimplicityStudio/AoA/DTMoverGattxG21v2136/platform/emlib/inc" -I"/Users/clfilho/SimplicityStudio/AoA/DTMoverGattxG21v2136/platform/radio/rail_lib/common" -I"/Users/clfilho/SimplicityStudio/AoA/DTMoverGattxG21v2136/platform/Device/SiliconLabs/EFR32MG21/Source" -I"/Users/clfilho/SimplicityStudio/AoA/DTMoverGattxG21v2136/hardware/kit/EFR32MG21_BRD4181B/config" -I"/Users/clfilho/SimplicityStudio/AoA/DTMoverGattxG21v2136/hardware/kit/common/bsp" -I"/Users/clfilho/SimplicityStudio/AoA/DTMoverGattxG21v2136/platform/service/sleeptimer/inc" -I"/Users/clfilho/SimplicityStudio/AoA/DTMoverGattxG21v2136/platform/service/sleeptimer/config" -I"/Users/clfilho/SimplicityStudio/AoA/DTMoverGattxG21v2136/platform/emdrv/nvm3/src" -I"/Users/clfilho/SimplicityStudio/AoA/DTMoverGattxG21v2136/platform/halconfig/inc/hal-config" -I"/Users/clfilho/SimplicityStudio/AoA/DTMoverGattxG21v2136/platform/radio/rail_lib/chip/efr32/efr32xg2x" -I"/Users/clfilho/SimplicityStudio/AoA/DTMoverGattxG21v2136/platform/bootloader/api" -I"/Users/clfilho/SimplicityStudio/AoA/DTMoverGattxG21v2136/platform/service/sleeptimer/src" -I"/Users/clfilho/SimplicityStudio/AoA/DTMoverGattxG21v2136/platform/emdrv/sleep/inc" -I"/Users/clfilho/SimplicityStudio/AoA/DTMoverGattxG21v2136/app/bluetooth/common/util" -I"/Users/clfilho/SimplicityStudio/AoA/DTMoverGattxG21v2136/platform/common/inc" -I"/Users/clfilho/SimplicityStudio/AoA/DTMoverGattxG21v2136/platform/radio/rail_lib/protocol/ieee802154" -I"/Users/clfilho/SimplicityStudio/AoA/DTMoverGattxG21v2136/platform/emdrv/gpiointerrupt/inc" -I"/Users/clfilho/SimplicityStudio/AoA/DTMoverGattxG21v2136/platform/emdrv/common/inc" -I"/Users/clfilho/SimplicityStudio/AoA/DTMoverGattxG21v2136/platform/Device/SiliconLabs/EFR32MG21/Source/GCC" -I"/Users/clfilho/SimplicityStudio/AoA/DTMoverGattxG21v2136/platform/emdrv/uartdrv/inc" -I"/Users/clfilho/SimplicityStudio/AoA/DTMoverGattxG21v2136/platform/emdrv/sleep/src" -I"/Users/clfilho/SimplicityStudio/AoA/DTMoverGattxG21v2136/platform/radio/rail_lib/protocol/ble" -I"/Users/clfilho/SimplicityStudio/AoA/DTMoverGattxG21v2136" -I"/Users/clfilho/SimplicityStudio/AoA/DTMoverGattxG21v2136/platform/bootloader" -O2 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=hard -MMD -MP -MF"app/bluetooth/common/util/infrastructure.d" -MT"app/bluetooth/common/util/infrastructure.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


