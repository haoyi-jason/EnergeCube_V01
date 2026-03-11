# EnergeCube_V01

**Energycube Display and Control Project**

## Hardware
- MCU: STM32H750XB (Cortex-M7, 480 MHz)
- Display: 480×272 RGB888 TFT (HMA480272T016-ZHC)
- Interface: LTDC + DMA2D
- Storage: SDMMC1 (eMMC), SDMMC2 (SD Card), FATFS
- Comms: FDCAN2 (CAN-FD)
- RTOS: FreeRTOS via CMSIS-OS2

## GUI Framework
TouchGFX 4.20.0 — MVP (Model-View-Presenter) pattern

## Screens
| Screen    | Purpose                          |
|-----------|----------------------------------|
| Screen1   | Dashboard — live energy metrics  |
| Screen2   | Details — fault status, history  |
| Screen3   | Settings — charge control, info  |

## Data Model
The `Model` class holds real-time energy data:
- Voltage (V), Current (A), Power (W)
- State of Charge (%)
- Temperature (°C)
- Fault flags (bitmask)
- Charge enable state

## Architecture

```
FreeRTOS AppTask (100 ms) ──► model_tick_from_c()
                                      │
                              FrontendApplication::handleTickEvent()
                                      │
                               Model::tick() — simulation/HW read
                                      │
                          ModelListener::energyDataUpdated()
                                      │
                           Screen1/2/3 Presenter → View
                                      │
                          LTDC 480×272 RGB888 framebuffer
```

## Build
Open in STM32CubeIDE, select Debug or Release configuration, and build.
TouchGFX assets are generated via: `make -f simulator/gcc/Makefile assets -j8`

