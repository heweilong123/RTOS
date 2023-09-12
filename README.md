# RTOS

## demo1

**笔记**
**1**  
osThreadDef(name, thread, priority, instances, stacksz)

=  

const osThreadDef_t os_thread_def_##name = { #name, (thread), (priority), (instances), (stacksz), NULL, NULL }  

=  

const osThreadDef_t os_thread_def_name = { "name", (thread), (priority), (instances), (stacksz) , NULL, NULL }  

**笔记2**
portDISABLE_INTERRUPTS() 和 portENABLE_INTERRUPTS() 必须在任务中一次运行完不然无效

## demo2

使用task3 和 TIM1 控制task2的挂起和恢复  
