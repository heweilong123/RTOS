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

## demo3

初始化列表、列表项，添加删除列表项

## demo4

设置时间片 频率为20HZ 每个任务有50ms运行时间  
运行效果 就是每个任务连续打印4到5次

## demo5

使用队列传输数据  
中断使用队列传输 中断优先级必须小于5  
中断互传好像有问题