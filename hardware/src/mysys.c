#include "mysys.h"

/**
 * @brief   系统时钟设置为240MHZ运行
 * 
 */
void SysCLK_Init(void) {
		stc_clock_xtal_init_t stcXtalInit;
    stc_clock_pll_init_t stcPLLHInit;
		LL_PERIPH_WE(LL_PERIPH_ALL);    //解锁所有外设寄存器写入功能
		EFM_FWMC_Cmd(ENABLE);

    /* PCLK0, HCLK  Max 240MHz */
    CLK_SetClockDiv(CLK_BUS_CLK_ALL, (CLK_PCLK0_DIV1 | CLK_PCLK1_DIV2 | CLK_PCLK2_DIV4 |
                                      CLK_PCLK3_DIV4 | CLK_PCLK4_DIV2 | CLK_EXCLK_DIV2 | CLK_HCLK_DIV1));
    (void)CLK_XtalStructInit(&stcXtalInit);
    /* Config Xtal and enable Xtal */
    stcXtalInit.u8Mode   = CLK_XTAL_MD_OSC;
    stcXtalInit.u8Drv    = CLK_XTAL_DRV_ULOW;
    stcXtalInit.u8State  = CLK_XTAL_ON;
    stcXtalInit.u8StableTime = CLK_XTAL_STB_2MS;

    GPIO_AnalogCmd(BSP_XTAL_PORT, BSP_XTAL_IN_PIN | BSP_XTAL_OUT_PIN, ENABLE);
    (void)CLK_XtalInit(&stcXtalInit);

    (void)CLK_PLLStructInit(&stcPLLHInit);
    /* VCO = (8/1)*120 = 960MHz*/
    stcPLLHInit.u8PLLState = CLK_PLL_ON;
    stcPLLHInit.PLLCFGR = 0UL;
    stcPLLHInit.PLLCFGR_f.PLLM = 1UL - 1UL;
    stcPLLHInit.PLLCFGR_f.PLLN = 120UL - 1UL;
    stcPLLHInit.PLLCFGR_f.PLLP = 4UL - 1UL;
    stcPLLHInit.PLLCFGR_f.PLLQ = 4UL - 1UL;
    stcPLLHInit.PLLCFGR_f.PLLR = 4UL - 1UL;
    stcPLLHInit.PLLCFGR_f.PLLSRC = CLK_PLL_SRC_XTAL;
    (void)CLK_PLLInit(&stcPLLHInit);

    /* Highspeed SRAM set to 1 Read/Write wait cycle */
    SRAM_SetWaitCycle(SRAM_SRAMH, SRAM_WAIT_CYCLE1, SRAM_WAIT_CYCLE1);
    /* SRAM1_2_3_4_backup set to 2 Read/Write wait cycle */
    SRAM_SetWaitCycle((SRAM_SRAM123 | SRAM_SRAM4 | SRAM_SRAMB), SRAM_WAIT_CYCLE2, SRAM_WAIT_CYCLE2);
    /* 0-wait @ 40MHz */
    EFM_SetWaitCycle(EFM_WAIT_CYCLE5);
    /* 4 cycles for 200 ~ 250MHz */
    GPIO_SetReadWaitCycle(GPIO_RD_WAIT4);
    CLK_SetSysClockSrc(CLK_SYSCLK_SRC_PLL);
		
		
		//PORT_DebugPortSetting(TDO_SWO,Disable);	//关闭DEBUG端口功能
	//PORT_DebugPortSetting(TDI,Disable);     //关闭DEBUG端口功能
	//PORT_DebugPortSetting(TRST,Disable);    //关闭DEBUG端口功能
    
		GPIO_SetDebugPort(GPIO_PIN_SWO,DISABLE);
    GPIO_SetDebugPort(GPIO_PIN_TDI,DISABLE);
    GPIO_SetDebugPort(GPIO_PIN_TRST,DISABLE);
}

/**
 * @brief  IAP clock De-Initialize.
 * @param  None
 * @retval None
 */
void IAP_CLK_DeInit(void)
{
    CLK_SetSysClockSrc(CLK_SYSCLK_SRC_MRC);
    CLK_SetClockDiv(CLK_BUS_CLK_ALL, (CLK_PCLK0_DIV1 | CLK_PCLK1_DIV1 | CLK_PCLK2_DIV1 |
                                      CLK_PCLK3_DIV1 | CLK_PCLK4_DIV1 | CLK_EXCLK_DIV1 | CLK_HCLK_DIV1));
    CLK_PLLCmd(DISABLE);
    CLK_XtalCmd(DISABLE);
    /* Highspeed SRAM set to 0 Read/Write wait cycle */
    SRAM_SetWaitCycle(SRAM_SRAMH, SRAM_WAIT_CYCLE0, SRAM_WAIT_CYCLE0);
    /* SRAM1_2_3_4_backup set to 0 Read/Write wait cycle */
    SRAM_SetWaitCycle((SRAM_SRAM123 | SRAM_SRAM4 | SRAM_SRAMB), SRAM_WAIT_CYCLE0, SRAM_WAIT_CYCLE0);
    /* 0-wait @ 40MHz */
    EFM_SetWaitCycle(EFM_WAIT_CYCLE0);
    /* 0 cycles for 50MHz */
    GPIO_SetReadWaitCycle(GPIO_RD_WAIT0);
}
