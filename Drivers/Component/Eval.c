/**
  ******************************************************************************
  * @file    stm32h743i_eval.c
  * @author  MCD Application Team
  * @brief   This file provides a set of firmware functions to manage LEDs,
  *          push-buttons and COM ports available on STM32H743I-EVAL
  *          evaluation board(MB1246) from STMicroelectronics.
  *
  @verbatim
            This driver requires the stm32h743i_eval_io.c/.h files to manage the
            IO module resources mapped on the MFX IO expander.
            These resources are mainly LEDs, Joystick push buttons, SD detect pin,
            USB OTG power switch/over current drive pins, Audio
            INT pin
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
#include "Eval.h"
#if defined(USE_IOEXPANDER)
//#include "stm32h743i_eval_io.h"
#endif /* USE_IOEXPANDER */

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32H743I_EVAL
  * @{
  */

/** @addtogroup STM32H743I_EVAL_LOW_LEVEL
  * @{
  */

/** @defgroup STM32H743I_EVAL_LOW_LEVEL_Private_TypesDefinitions STM32H743I-EVAL LOW LEVEL Private Types Definitions
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32H743I_EVAL_LOW_LEVEL_Private_Defines STM32H743I-EVAL LOW LEVEL Private Defines
  * @{
  */
/**
 * @brief STM32H743I EVAL BSP Driver version number V1.3.0
   */
#define __STM32H743I_EVAL_BSP_VERSION_MAIN   (0x01) /*!< [31:24] main version */
#define __STM32H743I_EVAL_BSP_VERSION_SUB1   (0x03) /*!< [23:16] sub1 version */
#define __STM32H743I_EVAL_BSP_VERSION_SUB2   (0x00) /*!< [15:8]  sub2 version */
#define __STM32H743I_EVAL_BSP_VERSION_RC     (0x00) /*!< [7:0]  release candidate */
#define __STM32H743I_EVAL_BSP_VERSION         ((__STM32H743I_EVAL_BSP_VERSION_MAIN << 24)\
                                             |(__STM32H743I_EVAL_BSP_VERSION_SUB1 << 16)\
                                             |(__STM32H743I_EVAL_BSP_VERSION_SUB2 << 8 )\
                                             |(__STM32H743I_EVAL_BSP_VERSION_RC))
/**
  * @}
  */

/** @defgroup STM32H743I_EVAL_LOW_LEVEL_Private_Macros STM32H743I-EVAL LOW LEVEL Private Macros
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32H743I_EVAL_LOW_LEVEL_Private_Variables STM32H743I-EVAL LOW LEVEL Private Variables
  * @{
  */




USART_TypeDef* COM_USART[COMn] = {EVAL_COM1};

GPIO_TypeDef* COM_TX_PORT[COMn] = {EVAL_COM1_TX_GPIO_PORT};

GPIO_TypeDef* COM_RX_PORT[COMn] = {EVAL_COM1_RX_GPIO_PORT};

const uint16_t COM_TX_PIN[COMn] = {EVAL_COM1_TX_PIN};

const uint16_t COM_RX_PIN[COMn] = {EVAL_COM1_RX_PIN};

const uint16_t COM_TX_AF[COMn] = {EVAL_COM1_TX_AF};

const uint16_t COM_RX_AF[COMn] = {EVAL_COM1_RX_AF};

static I2C_HandleTypeDef heval_I2c;
//static ADC_HandleTypeDef heval_ADC;

#if defined(BSP_USE_CMSIS_OS)
static osSemaphoreId BspI2cSemaphore = 0;
#endif

/**
  * @}
  */

/** @defgroup STM32H743I_EVAL_LOW_LEVEL_Private_FunctionPrototypes  STM32H743I_EVAL LOW LEVEL Private Function Prototypes
  * @{
  */
static void     I2Cx_MspInit(void);
static void     I2Cx_Init(void);
static void     I2Cx_Write(uint8_t Addr, uint8_t Reg, uint8_t Value);
static uint8_t  I2Cx_Read(uint8_t Addr, uint8_t Reg);
static HAL_StatusTypeDef I2Cx_ReadMultiple(uint8_t Addr, uint16_t Reg, uint16_t MemAddSize, uint8_t *Buffer, uint16_t Length);
static HAL_StatusTypeDef I2Cx_WriteMultiple(uint8_t Addr, uint16_t Reg, uint16_t MemAddSize, uint8_t *Buffer, uint16_t Length);
static HAL_StatusTypeDef I2Cx_IsDeviceReady(uint16_t DevAddress, uint32_t Trials);
static void     I2Cx_Error(uint8_t Addr);

#if defined(USE_IOEXPANDER)
/* IOExpander IO functions */
void            IOE_Init(void);
void            IOE_ITConfig(void);
void            IOE_Delay(uint32_t Delay);
void            IOE_Write(uint8_t Addr, uint8_t Reg, uint8_t Value);
uint8_t         IOE_Read(uint8_t Addr, uint8_t Reg);
uint16_t        IOE_ReadMultiple(uint8_t Addr, uint8_t Reg, uint8_t *Buffer, uint16_t Length);
void            IOE_WriteMultiple(uint8_t Addr, uint8_t Reg, uint8_t *Buffer, uint16_t Length);

/* MFX IO functions */
void            MFX_IO_Init(void);
void            MFX_IO_DeInit(void);
void            MFX_IO_ITConfig(void);
void            MFX_IO_Delay(uint32_t Delay);
void            MFX_IO_Write(uint16_t Addr, uint8_t Reg, uint8_t Value);
uint8_t         MFX_IO_Read(uint16_t Addr, uint8_t Reg);
uint16_t        MFX_IO_ReadMultiple(uint16_t Addr, uint8_t Reg, uint8_t *Buffer, uint16_t Length);
void            MFX_IO_Wakeup(void);
void            MFX_IO_EnableWakeupPin(void);
#endif /* USE_IOEXPANDER */

/* AUDIO IO functions */
void            AUDIO_IO_Init(void);
void            AUDIO_IO_DeInit(void);
void            AUDIO_IO_Write(uint8_t Addr, uint16_t Reg, uint16_t Value);
uint16_t        AUDIO_IO_Read(uint8_t Addr, uint16_t Reg);
void            AUDIO_IO_Delay(uint32_t Delay);

/* I2C EEPROM IO function */
void                EEPROM_IO_Init(void);
HAL_StatusTypeDef   EEPROM_IO_WriteData(uint16_t DevAddress, uint16_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize);
HAL_StatusTypeDef   EEPROM_IO_ReadData(uint16_t DevAddress, uint16_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize);
HAL_StatusTypeDef   EEPROM_IO_IsDeviceReady(uint16_t DevAddress, uint32_t Trials);



void OTM8009A_IO_Delay(uint32_t Delay);
/**
  * @}
  */

/**
  * @brief  BSP Error Notification
  * @note   Defined as a weak function to be overwritten by the application.
  * @retval None
  */
__weak void BSP_ErrorNotify(void)
{
}

/**
  * @brief  Configures COM port.
  * @param  COM: COM port to be configured.
  *          This parameter can be one of the following values:
  *            @arg  COM1
  *            @arg  COM2
  * @param  huart: Pointer to a UART_HandleTypeDef structure that contains the
  *                configuration information for the specified USART peripheral.
  * @retval None
  */
//void BSP_COM_Init(COM_TypeDef COM, UART_HandleTypeDef *huart)
//{
//  GPIO_InitTypeDef gpio_init_structure;

//  /* Enable GPIO clock */
//  EVAL_COMx_TX_GPIO_CLK_ENABLE(COM);
//  EVAL_COMx_RX_GPIO_CLK_ENABLE(COM);

//  /* Enable USART clock */
//  EVAL_COMx_CLK_ENABLE(COM);

//  /* Configure USART Tx as alternate function */
//  gpio_init_structure.Pin = COM_TX_PIN[COM];
//  gpio_init_structure.Mode = GPIO_MODE_AF_PP;
//  gpio_init_structure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//  gpio_init_structure.Pull = GPIO_PULLUP;
//  gpio_init_structure.Alternate = COM_TX_AF[COM];
//  HAL_GPIO_Init(COM_TX_PORT[COM], &gpio_init_structure);

//  /* Configure USART Rx as alternate function */
//  gpio_init_structure.Pin = COM_RX_PIN[COM];
//  gpio_init_structure.Mode = GPIO_MODE_AF_PP;
//  gpio_init_structure.Alternate = COM_RX_AF[COM];
//  HAL_GPIO_Init(COM_RX_PORT[COM], &gpio_init_structure);

//  /* USART configuration */
//  huart->Instance = COM_USART[COM];
//  HAL_UART_Init(huart);
//}


/*******************************************************************************
                            BUS OPERATIONS
*******************************************************************************/

/******************************* I2C Routines *********************************/
/**
  * @brief  Initializes I2C MSP.
  * @retval None
  */
static void I2Cx_MspInit(void)
{
  GPIO_InitTypeDef  gpio_init_structure;
  RCC_PeriphCLKInitTypeDef  RCC_PeriphClkInit;

  /* Configure the I2C clock source */
  RCC_PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C123;
  RCC_PeriphClkInit.I2c123ClockSelection = RCC_I2C123CLKSOURCE_D2PCLK1;
  HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphClkInit);

  /* set STOPWUCK in RCC_CFGR */
  __HAL_RCC_WAKEUPSTOP_CLK_CONFIG(RCC_STOP_WAKEUPCLOCK_HSI);

  /*** Configure the GPIOs ***/
  /* Enable GPIO clock */
  EVAL_I2Cx_SCL_SDA_GPIO_CLK_ENABLE();

  /* Configure I2C Tx as alternate function */
  gpio_init_structure.Pin = EVAL_I2Cx_SCL_PIN;
  gpio_init_structure.Mode = GPIO_MODE_AF_OD;
  gpio_init_structure.Pull = GPIO_NOPULL;
  gpio_init_structure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  gpio_init_structure.Alternate = EVAL_I2Cx_SCL_SDA_AF;
  HAL_GPIO_Init(EVAL_I2Cx_SCL_SDA_GPIO_PORT, &gpio_init_structure);

  /* Configure I2C Rx as alternate function */
  gpio_init_structure.Pin = EVAL_I2Cx_SDA_PIN;
  HAL_GPIO_Init(EVAL_I2Cx_SCL_SDA_GPIO_PORT, &gpio_init_structure);

  /*** Configure the I2C peripheral ***/
  /* Enable I2C clock */
  EVAL_I2Cx_CLK_ENABLE();

  /* Force the I2C peripheral clock reset */
  EVAL_I2Cx_FORCE_RESET();

  /* Release the I2C peripheral clock reset */
  EVAL_I2Cx_RELEASE_RESET();

  /* Enable and set I2Cx Interrupt to a lower priority */
  HAL_NVIC_SetPriority(EVAL_I2Cx_EV_IRQn, 0x0F, 0);
  HAL_NVIC_EnableIRQ(EVAL_I2Cx_EV_IRQn);

  /* Enable and set I2Cx Interrupt to a lower priority */
  HAL_NVIC_SetPriority(EVAL_I2Cx_ER_IRQn, 0x0F, 0);
  HAL_NVIC_EnableIRQ(EVAL_I2Cx_ER_IRQn);
}

/**
  * @brief  Initializes I2C HAL.
  * @retval None
  */
static void I2Cx_Init(void)
{
  if(HAL_I2C_GetState(&heval_I2c) == HAL_I2C_STATE_RESET)
  {
#if defined(BSP_USE_CMSIS_OS)
    if(BspI2cSemaphore == NULL)
    {
      /* Create semaphore to prevent multiple I2C access */
      osSemaphoreDef(BSP_I2C_SEM);
      BspI2cSemaphore = osSemaphoreCreate(osSemaphore(BSP_I2C_SEM), 1);
    }
#endif

    heval_I2c.Instance              = EVAL_I2Cx;
    heval_I2c.Init.Timing           = EVAL_I2Cx_TIMING;
    heval_I2c.Init.OwnAddress1      = 0x72;
    heval_I2c.Init.AddressingMode   = I2C_ADDRESSINGMODE_7BIT;
    heval_I2c.Init.DualAddressMode  = I2C_DUALADDRESS_ENABLE;
    heval_I2c.Init.OwnAddress2      = 0;
    heval_I2c.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
    heval_I2c.Init.GeneralCallMode  = I2C_GENERALCALL_ENABLE;
    heval_I2c.Init.NoStretchMode    = I2C_NOSTRETCH_DISABLE;

    /* Init the I2C */
    I2Cx_MspInit();
    HAL_I2C_Init(&heval_I2c);
  }
}

/**
  * @brief  Writes a single data.
  * @param  Addr: I2C address
  * @param  Reg: Register address
  * @param  Value: Data to be written
  * @retval None
  */
static void I2Cx_Write(uint8_t Addr, uint8_t Reg, uint8_t Value)
{
  HAL_StatusTypeDef status = HAL_OK;

#if defined(BSP_USE_CMSIS_OS)
  /* Get semaphore to prevent multiple I2C access */
  osSemaphoreWait(BspI2cSemaphore, osWaitForever);
#endif

  status = HAL_I2C_Mem_Write(&heval_I2c, Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, &Value, 1, 100);

#if defined(BSP_USE_CMSIS_OS)
  /* Release semaphore to prevent multiple I2C access */
  osSemaphoreRelease(BspI2cSemaphore);
#endif

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Execute user timeout callback */
    I2Cx_Error(Addr);
  }
}

/**
  * @brief  Reads a single data.
  * @param  Addr: I2C address
  * @param  Reg: Register address
  * @retval Read data
  */
static uint8_t I2Cx_Read(uint8_t Addr, uint8_t Reg)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint8_t Value = 0;

#if defined(BSP_USE_CMSIS_OS)
  /* Get semaphore to prevent multiple I2C access */
  osSemaphoreWait(BspI2cSemaphore, osWaitForever);
#endif

  status = HAL_I2C_Mem_Read(&heval_I2c, Addr, Reg, I2C_MEMADD_SIZE_8BIT, &Value, 1, 1000);

#if defined(BSP_USE_CMSIS_OS)
  /* Release semaphore to prevent multiple I2C access */
  osSemaphoreRelease(BspI2cSemaphore);
#endif

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Execute user timeout callback */
    I2Cx_Error(Addr);
  }
  return Value;
}

/**
  * @brief  Reads multiple data.
  * @param  Addr: I2C address
  * @param  Reg: Reg address
  * @param  MemAddress: memory address to be read 
  * @param  Buffer: Pointer to data buffer
  * @param  Length: Length of the data
  * @retval Number of read data
  */
static HAL_StatusTypeDef I2Cx_ReadMultiple(uint8_t Addr, uint16_t Reg, uint16_t MemAddress, uint8_t *Buffer, uint16_t Length)
{
  HAL_StatusTypeDef status = HAL_OK;

#if defined(BSP_USE_CMSIS_OS)
  /* Get semaphore to prevent multiple I2C access */
  osSemaphoreWait(BspI2cSemaphore, osWaitForever);
#endif

    status = HAL_I2C_Mem_Read(&heval_I2c, Addr, (uint16_t)Reg, MemAddress, Buffer, Length, 1000);

#if defined(BSP_USE_CMSIS_OS)
  /* Release semaphore to prevent multiple I2C access */
  osSemaphoreRelease(BspI2cSemaphore);
#endif

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* I2C error occurred */
    I2Cx_Error(Addr);
  }
  return status;
}

/**
  * @brief  Writes a value in a register of the device through BUS in using DMA mode.
  * @param  Addr: Device address on BUS Bus.
  * @param  Reg: The target register address to write
  * @param  MemAddress: memory address to be written   
  * @param  Buffer: The target register value to be written
  * @param  Length: buffer size to be written
  * @retval HAL status
  */
static HAL_StatusTypeDef I2Cx_WriteMultiple(uint8_t Addr, uint16_t Reg, uint16_t MemAddress, uint8_t *Buffer, uint16_t Length)
{
  HAL_StatusTypeDef status = HAL_OK;

#if defined(BSP_USE_CMSIS_OS)
  /* Get semaphore to prevent multiple I2C access */
  osSemaphoreWait(BspI2cSemaphore, osWaitForever);
#endif

  status = HAL_I2C_Mem_Write(&heval_I2c, Addr, (uint16_t)Reg, MemAddress, Buffer, Length, 1000);

#if defined(BSP_USE_CMSIS_OS)
  /* Release semaphore to prevent multiple I2C access */
  osSemaphoreRelease(BspI2cSemaphore);
#endif

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Re-Initiaize the I2C Bus */
    I2Cx_Error(Addr);
  }
  return status;
}

/**
  * @brief  Checks if target device is ready for communication.
  * @note   This function is used with Memory devices
  * @param  DevAddress: Target device address
  * @param  Trials: Number of trials
  * @retval HAL status
  */
static HAL_StatusTypeDef I2Cx_IsDeviceReady(uint16_t DevAddress, uint32_t Trials)
{
  HAL_StatusTypeDef status = HAL_OK;

#if defined(BSP_USE_CMSIS_OS)
  /* Get semaphore to prevent multiple I2C access */
  osSemaphoreWait(BspI2cSemaphore, osWaitForever);
#endif

  status = HAL_I2C_IsDeviceReady(&heval_I2c, DevAddress, Trials, 1000);

#if defined(BSP_USE_CMSIS_OS)
  /* Release semaphore to prevent multiple I2C access */
  osSemaphoreRelease(BspI2cSemaphore);
#endif

  return status;
}

/**
  * @brief  Manages error callback by re-initializing I2C.
  * @param  Addr: I2C Address
  * @retval None
  */
static void I2Cx_Error(uint8_t Addr)
{
  BSP_ErrorNotify();

  /* De-initialize the I2C communication bus */
  HAL_I2C_DeInit(&heval_I2c);

  /* Re-Initialize the I2C communication bus */
  I2Cx_Init();

#if defined(BSP_USE_CMSIS_OS)
  /* Release semaphore to prevent multiple I2C access */
  osSemaphoreRelease(BspI2cSemaphore);
#endif
}



/********************************* LINK AUDIO *********************************/

/**
  * @brief  Initializes Audio low level.
  * @retval None
  */
void AUDIO_IO_Init(void)
{
  I2Cx_Init();
}

/**
  * @brief  Deinitializes Audio low level.
  * @retval None
  */
void AUDIO_IO_DeInit(void)
{
}

/**
  * @brief  Writes a single data.
  * @param  Addr: I2C address
  * @param  Reg: Reg address
  * @param  Value: Data to be written
  * @retval None
  */
void AUDIO_IO_Write(uint8_t Addr, uint16_t Reg, uint16_t Value)
{
  uint16_t tmp = Value;

  Value = ((uint16_t)(tmp >> 8) & 0x00FF);

  Value |= ((uint16_t)(tmp << 8)& 0xFF00);

  I2Cx_WriteMultiple(Addr, Reg, I2C_MEMADD_SIZE_16BIT,(uint8_t*)&Value, 2);
}

/**
  * @brief  Reads a single data.
  * @param  Addr: I2C address
  * @param  Reg: Reg address
  * @retval Data to be read
  */
uint16_t AUDIO_IO_Read(uint8_t Addr, uint16_t Reg)
{
  uint16_t read_value = 0, tmp = 0;

  I2Cx_ReadMultiple(Addr, Reg, I2C_MEMADD_SIZE_16BIT, (uint8_t*)&read_value, 2);

  tmp = ((uint16_t)(read_value >> 8) & 0x00FF);

  tmp |= ((uint16_t)(read_value << 8)& 0xFF00);

  read_value = tmp;

  return read_value;
}

/**
  * @brief  AUDIO Codec delay
  * @param  Delay: Delay in ms
  * @retval None
  */
void AUDIO_IO_Delay(uint32_t Delay)
{
  HAL_Delay(Delay);
}

/******************************** LINK I2C EEPROM *****************************/

/**
  * @brief  Initializes peripherals used by the I2C EEPROM driver.
  * @retval None
  */
void EEPROM_IO_Init(void)
{
  I2Cx_Init();
}

/**
  * @brief  Write data to I2C EEPROM driver in using DMA channel.
  * @param  DevAddress: Target device address
  * @param  MemAddress: Internal memory address
  * @param  pBuffer: Pointer to data buffer
  * @param  BufferSize: Amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef EEPROM_IO_WriteData(uint16_t DevAddress, uint16_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize)
{
  return (I2Cx_WriteMultiple(DevAddress, MemAddress, I2C_MEMADD_SIZE_16BIT, pBuffer, BufferSize));
}

/**
  * @brief  Read data from I2C EEPROM driver in using DMA channel.
  * @param  DevAddress: Target device address
  * @param  MemAddress: Internal memory address
  * @param  pBuffer: Pointer to data buffer
  * @param  BufferSize: Amount of data to be read
  * @retval HAL status
  */
HAL_StatusTypeDef EEPROM_IO_ReadData(uint16_t DevAddress, uint16_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize)
{
  return (I2Cx_ReadMultiple(DevAddress, MemAddress, I2C_MEMADD_SIZE_16BIT, pBuffer, BufferSize));
}

/**
  * @brief  Checks if target device is ready for communication.
  * @note   This function is used with Memory devices
  * @param  DevAddress: Target device address
  * @param  Trials: Number of trials
  * @retval HAL status
  */
HAL_StatusTypeDef EEPROM_IO_IsDeviceReady(uint16_t DevAddress, uint32_t Trials)
{
  return (I2Cx_IsDeviceReady(DevAddress, Trials));
}

/******************************** LINK TS (TouchScreen) *****************************/

/**
  * @brief  Initialize I2C communication
  *         channel from MCU to TouchScreen (TS).
  */
void TS_IO_Init(void)
{
  I2Cx_Init();
}

/**
  * @brief  Writes single data with I2C communication
  *         channel from MCU to TouchScreen.
  * @param  Addr: I2C address
  * @param  Reg: Register address
  * @param  Value: Data to be written
  */
void TS_IO_Write(uint8_t Addr, uint8_t Reg, uint8_t Value)
{
  I2Cx_Write(Addr, Reg, Value);
}

/**
  * @brief  Reads single data with I2C communication
  *         channel from TouchScreen.
  * @param  Addr: I2C address
  * @param  Reg: Register address
  * @retval Read data
  */
uint8_t TS_IO_Read(uint8_t Addr, uint8_t Reg)
{
  return I2Cx_Read(Addr, Reg);
}

/**
  * @brief  Reads multiple data with I2C communication
  *         channel from TouchScreen.
  * @param  Addr: I2C address
  * @param  Reg: Register address
  * @param  Buffer: Pointer to data buffer
  * @param  Length: Length of the data
  * @retval Number of read data
  */
uint16_t TS_IO_ReadMultiple(uint8_t Addr, uint8_t Reg, uint8_t *Buffer, uint16_t Length)
{
 return I2Cx_ReadMultiple(Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, Buffer, Length);
}

/**
  * @brief  Writes multiple data with I2C communication
  *         channel from MCU to TouchScreen.
  * @param  Addr: I2C address
  * @param  Reg: Register address
  * @param  Buffer: Pointer to data buffer
  * @param  Length: Length of the data
  * @retval None
  */
void TS_IO_WriteMultiple(uint8_t Addr, uint8_t Reg, uint8_t *Buffer, uint16_t Length)
{
  I2Cx_WriteMultiple(Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, Buffer, Length);
}

/**
  * @brief  Delay function used in TouchScreen low level driver.
  * @param  Delay: Delay in ms
  * @retval None
  */
void TS_IO_Delay(uint32_t Delay)
{
  __IO uint32_t index = 0; 
  for(index = (100000 * Delay); index != 0; index--)
  {
  }
}

/**************************** LINK OTM8009A (Display driver) ******************/
/**
  * @brief  OTM8009A delay
  * @param  Delay: Delay in ms
  */
void OTM8009A_IO_Delay(uint32_t Delay)
{
  HAL_Delay(Delay);
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
