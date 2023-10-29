#ifndef MYSYS_H
#define MYSYS_H

#include "hc32_ll.h"


/**
 * @defgroup BSP_XTAL_CONFIG BSP XTAL Configure definition
 * @{
 */
#define BSP_XTAL_PORT                   (GPIO_PORT_H)
#define BSP_XTAL_IN_PIN                 (GPIO_PIN_01)
#define BSP_XTAL_OUT_PIN                (GPIO_PIN_00)
/**
 * @}
 */

/**
 * @defgroup BSP_XTAL32_CONFIG BSP XTAL32 Configure definition
 * @{
 */
#define BSP_XTAL32_PORT                 (GPIO_PORT_C)
#define BSP_XTAL32_IN_PIN               (GPIO_PIN_15)
#define BSP_XTAL32_OUT_PIN              (GPIO_PIN_14)

/**
 * @brief   系统时钟设置为240MHZ运行
 * 
 */
extern void SysCLK_Init(void);


/**
 * @brief  IAP clock De-Initialize.
 * @param  None
 * @retval None
 */
extern void IAP_CLK_DeInit(void);

#endif
