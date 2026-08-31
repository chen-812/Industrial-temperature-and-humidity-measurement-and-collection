#include <delay.h>

// 微秒级延时（基于HAL_Delay拆分，精度更高）
void delay_us(uint32_t us)
{
    uint32_t clk = SystemCoreClock / 1000000U;
    uint32_t ticks = us * clk;
    uint32_t start = SysTick->VAL;

    // 处理SysTick溢出
    if(ticks > SysTick->LOAD + 1U)
    {
        ticks = SysTick->LOAD + 1U;
    }

    while((start - SysTick->VAL) < ticks);
}

// 毫秒级延时（直接调用HAL_Delay，精准稳定）
void delay_ms(uint32_t ms)
{
    HAL_Delay(ms);
}
