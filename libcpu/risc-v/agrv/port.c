#include "rtthread.h"
#include "alta.h"

static uint32_t rt_mtime_per_tick;
void rt_hw_interrupt_init(void)
{
  INT_DisableIntGlobal(); // Disable all interrupts. Let the OS handle them.
  INT_SetMtimeHi(0);
  INT_SetMtimeLo(0);
  rt_mtime_per_tick = SYS_GetSysClkFreq() / RT_TICK_PER_SECOND;
  INT_SetMtimeCmp(rt_mtime_per_tick);
  INT_EnableIntTimer();
}

void MTIMER_isr(void)
{
  INT_SetMtimeCmp(INT_GetMtimeCmp() + rt_mtime_per_tick);
  rt_tick_increase();
}
