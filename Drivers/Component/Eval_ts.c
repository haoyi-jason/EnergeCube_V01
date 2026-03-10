/**
  ******************************************************************************
  * @file    stm32h743i_eval_ts.c
  * @author  MCD Application Team
  * @brief   This file provides a set of functions needed to manage the Touch
  *          Screen on STM32H743I-EVAL evaluation boards.
  @verbatim
  How To use this driver:
  -----------------------
   - This driver is used to drive the touch screen module of the STM32H743I-EVAL
     evaluation board on the AMPIRE 640x480 LCD mounted on MB1063 or AMPIRE
     480x272 LCD mounted on MB1046 daughter board.
   - If the AMPIRE 640x480 LCD is used, the TS3510 or EXC7200 component driver
     must be included according to the touch screen driver present on this board.
   - If the AMPIRE 480x272 LCD is used, the STMPE811 IO expander device component
     driver must be included in order to run the TS module commanded by the IO
     expander device, the MFXSTM32L152 IO expander device component driver must be
     also included in case of interrupt mode use of the TS.

  Driver description:
  ------------------
  + Initialization steps:
     o Initialize the TS module using the BSP_TS_Init() function. This
       function includes the MSP layer hardware resources initialization and the
       communication layer configuration to start the TS use. The LCD size properties
       (x and y) are passed as parameters.
     o If TS interrupt mode is desired, you must configure the TS interrupt mode
       by calling the function BSP_TS_ITConfig(). The TS interrupt mode is generated
       as an external interrupt whenever a touch is detected.
       The interrupt mode internally uses the IO functionalities driver driven by
       the IO expander, to configure the IT line.

  + Touch screen use
     o The touch screen state is captured whenever the function BSP_TS_GetState() is
       used. This function returns information about the last LCD touch occurred
       in the TS_StateTypeDef structure.
     o If TS interrupt mode is used, the function BSP_TS_ITGetStatus() is needed to get
       the interrupt status. To clear the IT pending bits, you should call the
       function BSP_TS_ITClear().
     o The IT is handled using the corresponding external interrupt IRQ handler,
       the user IT callback treatment is implemented on the same external interrupt
       callback.
  @endverbatim
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

/* Includes ------------------------------------------------------------------*/
#include "Eval_ts.h"
//#include "stm32h743i_eval_io.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32H743I_EVAL
  * @{
  */

/** @addtogroup STM32H743I_EVAL_TS
  * @{
  */

/** @defgroup STM32H743I_EVAL_TS_Private_Types_Definitions TS Private Types Definitions
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32H743I_EVAL_TS_Private_Defines TS Private Defines
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32H743I_EVAL_TS_Private_Macros TS Private Macros
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32H743I_EVAL_TS_Private_Variables TS Private Variables
  * @{
  */
static TS_DrvTypeDef *tsDriver;
static uint16_t tsXBoundary, tsYBoundary;
static uint8_t  tsOrientation;
static uint8_t  I2cAddress;
/**
  * @}
  */

/** @defgroup STM32H743I_EVAL_TS_Private_Function_Prototypes TS Private Function Prototypes
  * @{
  */
/**
  * @}
  */

/** addtogroup STM32H743I_EVAL_TS_Exported_Functions
  * @{
  */

/**
  * @brief  Initializes and configures the touch screen functionalities and
  *         configures all necessary hardware resources (GPIOs, clocks..).
  * @param  xSize: Maximum X size of the TS area on LCD
  * @param  ySize: Maximum Y size of the TS area on LCD
  * @retval TS_OK if all initializations are OK. Other value if error.
  */
uint8_t BSP_TS_Init(uint16_t xSize, uint16_t ySize)
{
  uint8_t status = TS_OK;
  tsXBoundary = xSize;
  tsYBoundary = ySize;

  
  /* Initialize the TS driver structure */
  tsDriver = &ft5336_ts_drv;
  I2cAddress = FOCAL_I2C_ADDRESS;
    
  tsOrientation = TS_SWAP_NONE;
  

  /* Initialize the TS driver */
  tsDriver->Init(I2cAddress);
  tsDriver->Start(I2cAddress);

  return status;
}

/**
  * @brief  DeInitializes the TouchScreen.
  * @retval TS state
  */
uint8_t BSP_TS_DeInit(void)
{
  /* Actually ts_driver does not provide a DeInit function */
  return TS_OK;
}

/**
  * @brief  Configures and enables the touch screen interrupts.
  * @retval TS_OK if all initializations are OK. Other value if error.
  */
uint8_t BSP_TS_ITConfig(void)
{
  GPIO_InitTypeDef gpio_init_structure;

  /* Configure Interrupt mode for SD detection pin */
  gpio_init_structure.Pin = TS_INT_PIN;
  gpio_init_structure.Pull = GPIO_NOPULL;
  gpio_init_structure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  gpio_init_structure.Mode = GPIO_MODE_IT_RISING;
  HAL_GPIO_Init(TS_INT_GPIO_PORT, &gpio_init_structure);

  /* Enable and set Touch screen EXTI Interrupt to the lowest priority */
  HAL_NVIC_SetPriority((IRQn_Type)(TS_INT_EXTI_IRQn), 0x0F, 0x00);
  HAL_NVIC_EnableIRQ((IRQn_Type)(TS_INT_EXTI_IRQn));

  /* Enable the TS ITs */
  tsDriver->EnableIT(I2cAddress);

  return TS_OK;  
}

/**
  * @brief  Gets the touch screen interrupt status.
  * @retval TS_OK if all initializations are OK. Other value if error.
  */
uint8_t BSP_TS_ITGetStatus(void)
{
  /* Return the TS IT status */
  return (tsDriver->GetITStatus(I2cAddress));
}

/**
  * @brief  Returns status and positions of the touch screen.
  * @param  TS_State: Pointer to touch screen current state structure
  * @retval TS_OK if all initializations are OK. Other value if error.
  */
uint8_t BSP_TS_GetState(TS_StateTypeDef *TS_State)
{
   static uint32_t _x[TS_MAX_NB_TOUCH] = {0, 0};
  static uint32_t _y[TS_MAX_NB_TOUCH] = {0, 0};
  uint8_t ts_status = TS_OK;
  uint16_t x[TS_MAX_NB_TOUCH];
  uint16_t y[TS_MAX_NB_TOUCH];
  uint16_t brute_x[TS_MAX_NB_TOUCH];
  uint16_t brute_y[TS_MAX_NB_TOUCH];
  uint16_t x_diff;
  uint16_t y_diff;
  uint32_t index;
#if (TS_MULTI_TOUCH_SUPPORTED == 1)
  uint32_t weight = 0;
  uint32_t area = 0;
  uint32_t event = 0;
#endif /* TS_MULTI_TOUCH_SUPPORTED == 1 */

  /* Check and update the number of touches active detected */
  TS_State->touchDetected = tsDriver->DetectTouch(I2cAddress);
  
  if(TS_State->touchDetected)
  {
    for(index=0; index < TS_State->touchDetected; index++)
    {
      /* Get each touch coordinates */
      tsDriver->GetXY(I2cAddress, &(brute_x[index]), &(brute_y[index]));

      if(tsOrientation == TS_SWAP_NONE)
      {
        x[index] = brute_x[index];
        y[index] = brute_y[index];
      }

      if(tsOrientation & TS_SWAP_X)
      {
        x[index] = 4096 - brute_x[index];
      }

      if(tsOrientation & TS_SWAP_Y)
      {
        y[index] = 4096 - brute_y[index];
      }

      if(tsOrientation & TS_SWAP_XY)
      {
        y[index] = brute_x[index];
        x[index] = brute_y[index];
      }

      x_diff = x[index] > _x[index]? (x[index] - _x[index]): (_x[index] - x[index]);
      y_diff = y[index] > _y[index]? (y[index] - _y[index]): (_y[index] - y[index]);

      if ((x_diff + y_diff) > 5)
      {
        _x[index] = x[index];
        _y[index] = y[index];
      }

      if(I2cAddress == FT5336_I2C_SLAVE_ADDRESS)
      {
        TS_State->touchX[index] = x[index];
        TS_State->touchY[index] = y[index];
      }
      else
      {
        /* 2^12 = 4096 : indexes are expressed on a dynamic of 4096 */
        TS_State->touchX[index] = (tsXBoundary * _x[index]) >> 12;
        TS_State->touchY[index] = (tsYBoundary * _y[index]) >> 12;
      }

#if (TS_MULTI_TOUCH_SUPPORTED == 1)

      /* Get touch info related to the current touch */
      ft5336_TS_GetTouchInfo(I2cAddress, index, &weight, &area, &event);

      /* Update TS_State structure */
      TS_State->touchWeight[index] = weight;
      TS_State->touchArea[index]   = area;

      /* Remap touch event */
      switch(event)
      {
        case FT5336_TOUCH_EVT_FLAG_PRESS_DOWN	:
          TS_State->touchEventId[index] = TOUCH_EVENT_PRESS_DOWN;
          break;
        case FT5336_TOUCH_EVT_FLAG_LIFT_UP :
          TS_State->touchEventId[index] = TOUCH_EVENT_LIFT_UP;
          break;
        case FT5336_TOUCH_EVT_FLAG_CONTACT :
          TS_State->touchEventId[index] = TOUCH_EVENT_CONTACT;
          break;
        case FT5336_TOUCH_EVT_FLAG_NO_EVENT :
          TS_State->touchEventId[index] = TOUCH_EVENT_NO_EVT;
          break;
        default :
          ts_status = TS_ERROR;
          break;
      } /* of switch(event) */

#endif /* TS_MULTI_TOUCH_SUPPORTED == 1 */

    } /* of for(index=0; index < TS_State->touchDetected; index++) */

#if (TS_MULTI_TOUCH_SUPPORTED == 1)
    /* Get gesture Id */
    ts_status = BSP_TS_Get_GestureId(TS_State);
#endif /* TS_MULTI_TOUCH_SUPPORTED == 1 */

  } /* end of if(TS_State->touchDetected != 0) */

  return (ts_status);
}

/**
  * @brief  Clears all touch screen interrupts.
  * @retval None
  */
void BSP_TS_ITClear(void)
{
  /* Clear all IO IT pin */
 // BSP_IO_ITClear();

  /* Clear TS IT pending bits */
  tsDriver->ClearIT(I2cAddress);
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
