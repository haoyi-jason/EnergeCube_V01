/**
  ******************************************************************************
  * @file    stm32h743i_eval.h
  * @author  MCD Application Team
  * @brief   This file contains definitions for STM32H743I_EVAL LEDs,
  *          push-buttons and COM ports hardware resources.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32H743I_EVAL_H
#define __STM32H743I_EVAL_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"
#if defined(BSP_USE_CMSIS_OS)
#include "cmsis_os.h"
#endif

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32H743I_EVAL
  * @{
  */

/** @defgroup STM32H743I_EVAL_LOW_LEVEL LOW LEVEL
  * @{
  */

/** @defgroup STM32H743I_EVAL_LOW_LEVEL_Exported_Types LOW LEVEL Exported Types
  * @{
  */
typedef enum
{
#if defined(USE_IOEXPANDER)
LED1 = 0,
LED_GREEN = LED1,
LED2 = 1,
LED_ORANGE = LED2,
LED3 = 2,
LED_RED = LED3,
LED4 = 3,
LED_BLUE = LED4
#else
LED1 = 0,
LED_GREEN = LED1,
LED3 = 1,
LED_RED = LED3,
#endif /* USE_IOEXPANDER */
}Led_TypeDef;

typedef enum
{
  BUTTON_WAKEUP = 0,
  BUTTON_TAMPER = 1,
  BUTTON_KEY = 2
}Button_TypeDef;

typedef enum
{
  BUTTON_MODE_GPIO = 0,
  BUTTON_MODE_EXTI = 1
}ButtonMode_TypeDef;

#if defined(USE_IOEXPANDER)
typedef enum
{
  JOY_MODE_GPIO = 0,
  JOY_MODE_EXTI = 1
}JOYMode_TypeDef;

typedef enum
{
  JOY_NONE  = 0,
  JOY_SEL   = 1,
  JOY_DOWN  = 2,
  JOY_LEFT  = 3,
  JOY_RIGHT = 4,
  JOY_UP    = 5
}JOYState_TypeDef;
#endif /* USE_IOEXPANDER */

typedef enum
{
  COM1 = 0,
  COM2 = 1
}COM_TypeDef;
/**
  * @}
  */

/** @defgroup STM32H743I_EVAL_LOW_LEVEL_Exported_Constants LOW LEVEL Exported Constants
  * @{
  */

/**
  * @brief  Define for STM32H743I_EVAL board
  */
#if !defined (USE_STM32H743I_EVAL)
 #define USE_STM32H743I_EVAL
#endif



/**
  * @brief MFX_IRQOUt pin
  */
#define MFX_IRQOUT_PIN                    GPIO_PIN_8
#define MFX_IRQOUT_GPIO_PORT              GPIOI
#define MFX_IRQOUT_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOI_CLK_ENABLE()
#define MFX_IRQOUT_GPIO_CLK_DISABLE()     __HAL_RCC_GPIOI_CLK_DISABLE()
#define MFX_IRQOUT_EXTI_IRQn              EXTI9_5_IRQn

#define FOCAL_TSINT_PIN                    GPIO_PIN_7
#define FOCAL_TSINT_GPIO_PORT              GPIOH
#define FOCAL_TSINT_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOH_CLK_ENABLE()
#define FOCAL_TSINT_GPIO_CLK_DISABLE()     __HAL_RCC_GPIOH_CLK_DISABLE()
#define FOCAL_TSINT_EXTI_IRQn              EXTI9_5_IRQn

#define TS_INT_PIN                        ((uint32_t)GPIO_PIN_2)
#define TS_INT_GPIO_PORT                  ((GPIO_TypeDef*)GPIOG)
#define TS_INT_GPIO_CLK_ENABLE()          __HAL_RCC_GPIOH_CLK_ENABLE()
#define TS_INT_GPIO_CLK_DISABLE()         __HAL_RCC_GPIOH_CLK_DISABLE()
#define TS_INT_EXTI_IRQn                  EXTI2_IRQn

/**
  * @brief TouchScreen FT5336 Slave I2C address
  */
#define TS_I2C_ADDRESS                   ((uint16_t)0x70)

/** @addtogroup STM32H743I_EVAL_LOW_LEVEL_BUTTON
  * @{
  */
/* Joystick pins are connected to IO Expander (accessible through I2C1 interface) */
#define BUTTONn                             ((uint8_t)3)

/**
  * @brief Wakeup push-button
  */
#define WAKEUP_BUTTON_PIN                   GPIO_PIN_0
#define WAKEUP_BUTTON_GPIO_PORT             GPIOA
#define WAKEUP_BUTTON_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOA_CLK_ENABLE()
#define WAKEUP_BUTTON_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOA_CLK_DISABLE()
#define WAKEUP_BUTTON_EXTI_IRQn             EXTI0_IRQn



/** @addtogroup STM32H743I_EVAL_LOW_LEVEL_COM
  * @{
  */
#define COMn                             ((uint8_t)1)

/**
 * @brief Definition for COM port1, connected to USART1
 */
#define EVAL_COM1                          USART1
#define EVAL_COM1_CLK_ENABLE()             __HAL_RCC_USART1_CLK_ENABLE()
#define EVAL_COM1_CLK_DISABLE()            __HAL_RCC_USART1_CLK_DISABLE()

#define EVAL_COM1_TX_PIN                   GPIO_PIN_14
#define EVAL_COM1_TX_GPIO_PORT             GPIOB
#define EVAL_COM1_TX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()
#define EVAL_COM1_TX_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOB_CLK_DISABLE()
#define EVAL_COM1_TX_AF                    GPIO_AF4_USART1

#define EVAL_COM1_RX_PIN                   GPIO_PIN_15
#define EVAL_COM1_RX_GPIO_PORT             GPIOB
#define EVAL_COM1_RX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()
#define EVAL_COM1_RX_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOB_CLK_DISABLE()
#define EVAL_COM1_RX_AF                    GPIO_AF4_USART1

#define EVAL_COM1_IRQn                     USART1_IRQn

#define EVAL_COMx_CLK_ENABLE(__INDEX__)            do { if((__INDEX__) == COM1) EVAL_COM1_CLK_ENABLE(); } while(0)
#define EVAL_COMx_CLK_DISABLE(__INDEX__)           (((__INDEX__) == 0) ? EVAL_COM1_CLK_DISABLE() : 0)

#define EVAL_COMx_TX_GPIO_CLK_ENABLE(__INDEX__)    do { if((__INDEX__) == COM1) EVAL_COM1_TX_GPIO_CLK_ENABLE(); } while(0)
#define EVAL_COMx_TX_GPIO_CLK_DISABLE(__INDEX__)   (((__INDEX__) == 0) ? EVAL_COM1_TX_GPIO_CLK_DISABLE() : 0)

#define EVAL_COMx_RX_GPIO_CLK_ENABLE(__INDEX__)    do { if((__INDEX__) == COM1) EVAL_COM1_RX_GPIO_CLK_ENABLE(); } while(0)
#define EVAL_COMx_RX_GPIO_CLK_DISABLE(__INDEX__)   (((__INDEX__) == 0) ? EVAL_COM1_RX_GPIO_CLK_DISABLE() : 0)



/* Exported constant IO ------------------------------------------------------*/

/*  The MFX_I2C_ADDR input pin selects the MFX I2C device address
        MFX_I2C_ADDR input pin     MFX I2C device address
            0                           b: 1000 010x    (0x84)
            1                           b: 1000 011x    (0x86)
   This input is sampled during the MFX firmware startup.  */
#define IO_I2C_ADDRESS                   ((uint16_t)0x84)  /*mfx MFX_I2C_ADDR 0*/
#define IO_I2C_ADDRESS_2                 ((uint16_t)0x86)  /*mfx MFX_I2C_ADDR 1*/
//#define TS_I2C_ADDRESS                   ((uint16_t)0x82)  /*stmpe811 used on MB1046 board */
#define TS3510_I2C_ADDRESS               ((uint16_t)0x80)
#define EXC7200_I2C_ADDRESS              ((uint16_t)0x08)
#define AUDIO_I2C_ADDRESS                ((uint16_t)0x34)
#define EEPROM_I2C_ADDRESS_A01           ((uint16_t)0xA0)
#define EEPROM_I2C_ADDRESS_A02           ((uint16_t)0xA6)

#define FOCAL_I2C_ADDRESS                   ((uint8_t)0x70)

/* I2C clock speed configuration (in Hz)
   WARNING:
   Make sure that this define is not already declared in other files (ie.
   stm32h743i_eval.h file). It can be used in parallel by other modules. */
#ifndef I2C_SPEED
 #define I2C_SPEED                        ((uint32_t)100000)
#endif /* I2C_SPEED */

/* User can use this section to tailor I2Cx/I2Cx instance used and associated
   resources */
/* Definition for I2Cx clock resources */
#define EVAL_I2Cx                           I2C2//   I2C1
#define EVAL_I2Cx_CLK_ENABLE()              __HAL_RCC_I2C2_CLK_ENABLE()//  __HAL_RCC_I2C1_CLK_ENABLE()
#define EVAL_DMAx_CLK_ENABLE()                __HAL_RCC_DMA1_CLK_ENABLE()
#define EVAL_I2Cx_SCL_SDA_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOB_CLK_ENABLE()

#define EVAL_I2Cx_FORCE_RESET()              __HAL_RCC_I2C2_FORCE_RESET()// __HAL_RCC_I2C1_FORCE_RESET()
#define EVAL_I2Cx_RELEASE_RESET()             __HAL_RCC_I2C2_RELEASE_RESET() // __HAL_RCC_I2C1_RELEASE_RESET()

/* Definition for I2Cx Pins */
#define EVAL_I2Cx_SCL_PIN                     GPIO_PIN_10
#define EVAL_I2Cx_SCL_SDA_GPIO_PORT           GPIOB
#define EVAL_I2Cx_SCL_SDA_AF                  GPIO_AF4_I2C2 //GPIO_AF4_I2C1
#define EVAL_I2Cx_SDA_PIN                  GPIO_PIN_11//   GPIO_PIN_7

/* I2C interrupt requests */
#define EVAL_I2Cx_EV_IRQn                    I2C2_EV_IRQn// I2C1_EV_IRQn
#define EVAL_I2Cx_ER_IRQn                    I2C2_ER_IRQn// I2C1_ER_IRQn

/* I2C TIMING Register define when I2C clock source is SYSCLK */
/* I2C TIMING is calculated from APB1 source clock = 50 MHz */
/* 0x40912732 takes in account the big rising and aims a clock of 100khz */
#ifndef EVAL_I2Cx_TIMING
#define EVAL_I2Cx_TIMING                      ((uint32_t)0x40912732)
#endif /* EVAL_I2Cx_TIMING */



/**
  * @}
  */


/** @addtogroup STM32H743I_EVAL_LCD_TIM
  * @{
  */
/**
 * @brief Definition for LCD Timer used to control the Brightnes
 */
#define LCD_TIMx                           TIM3
#define LCD_TIMx_CLK_ENABLE()              __HAL_RCC_TIM3_CLK_ENABLE()
#define LCD_TIMx_CLK_DISABLE()             __HAL_RCC_TIM3_CLK_DISABLE()
#define LCD_TIMx_CHANNEL                   TIM_CHANNEL_1
#define LCD_TIMx_CHANNEL_AF                GPIO_AF2_TIM3
#define LCD_TIMX_PERIOD_VALUE              ((uint32_t)50000) /* Period Value    */
#define LCD_TIMX_PRESCALER_VALUE           ((uint32_t)4)     /* Prescaler Value */

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup STM32H743I_EVAL_LOW_LEVEL_Exported_Macros LOW LEVEL Exported Macros
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32H743I_EVAL_LOW_LEVEL_Exported_Functions LOW LEVEL Exported Functions
  * @{
  */
uint32_t         BSP_GetVersion(void);
void             BSP_LED_Init(Led_TypeDef Led);
void             BSP_LED_DeInit(Led_TypeDef Led);
void             BSP_LED_On(Led_TypeDef Led);
void             BSP_LED_Off(Led_TypeDef Led);
void             BSP_LED_Toggle(Led_TypeDef Led);
void             BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef ButtonMode);
void             BSP_PB_DeInit(Button_TypeDef Button);
uint32_t         BSP_PB_GetState(Button_TypeDef Button);
//void             BSP_COM_Init(COM_TypeDef COM, UART_HandleTypeDef *husart);
//void             BSP_COM_DeInit(COM_TypeDef COM, UART_HandleTypeDef *huart);
void             BSP_POTENTIOMETER_Init(void);
uint32_t         BSP_POTENTIOMETER_GetLevel(void);
#if defined(USE_IOEXPANDER)
uint8_t          BSP_JOY_Init(JOYMode_TypeDef JoyMode);
void             BSP_JOY_DeInit(void);
JOYState_TypeDef BSP_JOY_GetState(void);
uint8_t          BSP_TS3510_IsDetected(void);
#endif /* USE_IOEXPANDER */
void             BSP_ErrorNotify(void);

/**
  * @}
  */
/* TouchScreen (TS) IO functions */
void         TS_IO_Init(void);
void         TS_IO_Write(uint8_t Addr, uint8_t Reg, uint8_t Value);
uint8_t      TS_IO_Read(uint8_t Addr, uint8_t Reg);
uint16_t     TS_IO_ReadMultiple(uint8_t Addr, uint8_t Reg, uint8_t *Buffer, uint16_t Length);
void         TS_IO_WriteMultiple(uint8_t Addr, uint8_t Reg, uint8_t *Buffer, uint16_t Length);
void         TS_IO_Delay(uint32_t Delay);
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32H743I_EVAL_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
