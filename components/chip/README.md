# Chip组件信息：外设CSI驱动。依赖于SDK组件。

# Release Notes
======================================================
Version: V1.3.5
Release Date: 2023.10.18

Release Notes
======================================================

======================================================
Version: V1.3.4
Release Date: 2023.10.10

Release Notes
1、添加ADC OFFSET校准静态库及校准函数adc0_offset_trim
2、csi_ifc_wr_useroption()中增加ifc clock使能操作
3、hwdiv增加接口,支持主动使用软件库做除法
4、ept增加csi驱动接口：
csi_ept_set_channel_polarity_mode
csi_ept_set_hlcrv_mode
csi_ept_set_cxosf
csi_ept_set_cxcsf
======================================================

======================================================
Version: V1.3.3
Release Date: 2023.8.8

Release Notes
1、规范syc clk相关定义，添加clk clo输出csi枚举定义
2、添加csi_pin_input_filter接口函数
3、更新csi_sramcheck_int配置，解决RAM_ERR中断未使能BUG
4、更新csi_gpio_port_irq_mode函数
5、添加PA011_INTVREF引脚功能
======================================================

======================================================
Version: V1.2.3
Release Date: 2023.5.12

Release Notes
1、中断函数移到demo文件中
2、规范驱动文件中的变量类型定义，添加枚举变量强制类型转换
3、区分csi层与csp层枚举
4、更新系统时钟配置函数csi_sysclk_config
5、添加csi_calc_clk_freq接口
6、添加功耗策略调节的接口csi_pm_power_control
======================================================

======================================================
Version: V1.1.3
Release Date: 2023.1.31

Release Notes
1、增加一个同时将所有中断优先级都设为同一个值的接口函数csi_irq_set_all_prio
2、BT/GPTA/EPT添加直接设置PRDR和CMP寄存器的api接口函数，修改CAMPA/B/C/D为COMPA/B/C/D
3、iwdt溢出时间=5h的值修改为2944，修正csp_syscon.h中iwdt报警时间枚举变量的定义
======================================================

======================================================
Version: V1.1.2
Release Date: 2022.12.27

Release Notes
1、添加CMP csi触发接口函数，升级触发源中断模式函数
2、根据最新SPEC,添加CMP触发接口函数及触发源定义
======================================================

======================================================
Version: V1.1.1
Release Date: 2022.12.20

Release Notes
版本 V1.1.1
======================================================

======================================================
Version: V1.0.1
Release Date: 2022.12.13

Release Notes
1、csp_adc_get_isr 替换为csp_adc_get_imr
2、USART添加超时处理使能参数，接收中断需用户自己选择
3、UART更新UART初始化接口函数，接收超时中断需用户选择，不在默认配置
4、ADC/BT/PIN添加触发输出单独使能/禁止接口
5、修改csp_ept.h一些枚举定义及内联函数，与手册保持统一
6、修改apt32f171_v1.0.svc文件，删掉chipconfig页
7、解决wSclk偏小，delay延迟异常的问题
8、更新GPTA事件触发驱动，去掉枚举中PE事件触发
======================================================

======================================================
Version: V1.0.0
Release Date: 2022.11.15

Release Notes
1、GPTA：添加基本定时接口功能、同步触发窗口功能、添加phsr相位控制接口函数
2、优化hwdiv
3、去掉long long 类型的除法运算，将相关运算优化到32位模式
4、规范寄存器定义，与文档一致
5、修复：并行模式下，DROM page erase会fail
6、uart增加接收超时配置
7、SYSCON 系统时钟初始化增加入口参数
8、USART 增加接收超时配置
======================================================

======================================================
Version: V0.0.0
Release Date: 2022.9.5

Release Notes
初始版本。
======================================================