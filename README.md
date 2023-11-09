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

## demo6

串口接受到数据后调用信号量 通知任务打印串口数据  

## demo7

串口接收数据 任务2发送数据的同时释放计数信号量
任务3 获取计数信号量 获取到就打印  

## demo8

三个任务 低优先级任务占用二值信号后休眠，导致高优先级任务无法获取信号一直等待，中优先级任务不断的运行。


## demo9

与demo8相比 是用互斥信号后 低任务的优先级提升后高于中优先级任务 所以在等待的过程中 中优先级任务不会运行


## demo10

使用事件标志组实 任务和中断中发送 信号给另一个任务

## demo11

使用任务通知 代替二值信号量