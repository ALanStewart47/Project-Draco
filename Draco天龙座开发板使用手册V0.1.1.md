1. **硬件资源介绍**

Draco天龙座AI教育开发板，由AI模块和外设底板构成。开发板集成了摄像头、LCD屏幕、麦克风和WIFI模块等丰富外设，且板载拓展口与树莓派兼容。利用Type-C接口搭配USB-UART电路使得用户可以直接连接电脑进行开发。

![image-20211012150736262](C:\Users\843530433\AppData\Roaming\Typora\typora-user-images\image-20211012150736262.png)



### 1.1. **AI模块**

AI模块内置双核64位处理器，频率高达400MHz，拥有8M的内存（SRAM）和128M的FLASH，内置多种硬件加速器（KPU、FPU、APU等），具有机器视觉与听觉能力，总算力达1TOPS。

![image-20211012150800632](C:\Users\843530433\AppData\Roaming\Typora\typora-user-images\image-20211012150800632.png)



### 1.2. **外设底板**

外设底板上集成多种外设，满足AI学习的多种需求，I/O拓展口与树莓派拓展口兼容，便于用户与树莓派进行通讯或连接其他传感器。LCD屏采用分辨率为320x240的IPS屏幕，而摄像头采用GC0308感光芯片，像素为640x480。

![image-20211012151750632](C:\Users\843530433\AppData\Roaming\Typora\typora-user-images\image-20211012151750632.png)

\1. LCD屏幕

\2. RGB灯

\3. LED灯

\4. WIFI控制按键

\5. WIFI模块

\6. 摄像头

\7. 喇叭接口

\8. 串口选择拨动开关

\9. K1、K2按键

\10. BOOT按键

\11. 重启按键

\12. 麦克风

\13. 陀螺仪





### 2. **使用说明**

Draco天龙座开发板供电电压为5V，故可以直接通过Type-C数据线与电脑连接进行供电，并可以通过板子上集成的ISP下载电路进行固件烧录，具体的说明请看一下说明。

### 2.1. **下载说明**

**1)** ***\*使用带有数据传输功能的Type-C数据线连接板子和电脑\****（市面上有部分Type-C数据线仅能供电，无法传输数据，需要特别注意），当板子与电脑连接后，板子USB接口旁边的LED灯会点亮，表示电源供电正常。

 

图2.1.1

 

**2)** ***\*安装CH340驱动。\****板上使用CH340C这颗USB转串口芯片，故需要安装对应的驱动来实现电脑与板子之间的通讯，可以在提供的资料里面找到名为CH341SER.EXE的安装包，或者网上搜索CH340驱动也能找到对应驱动安装包，双击安装包进行安装。

![image-20211012151838838](C:\Users\843530433\AppData\Roaming\Typora\typora-user-images\image-20211012151838838.png)

​		出现安装界面后，点击安装然后等待数秒即可，安装完成后会有“驱动安装成功！”的提示

![image-20211012151849429](C:\Users\843530433\AppData\Roaming\Typora\typora-user-images\image-20211012151849429.png)

​		此时打开我们的设备管理器，你会发现在端口下拉栏中会出现USB-SERIAL CH340的设备（SERIAL就是串行的意思）。

![image-20211012151926485](C:\Users\843530433\AppData\Roaming\Typora\typora-user-images\image-20211012151926485.png)

​		此需要注意一下COM后的数字，找到板子对应的串口，用于下一步的固件下载。



**3)** ***\*获取下载软件\*******\*。\**** Draco天龙座开发板可以使用Kendryte IDE或者K-Flash软件进行固件烧录，这里首先介绍K-Flash固件烧录软件的使用方法：

- 下载K-Flash，进入以下地址进行下载：（https://github.com/kendryte/kendryte-flash-windows/releases）

如下图所示，单击K-Flash.zip就会开始下载了，十分简单。

![image-20211012151956213](C:\Users\843530433\AppData\Roaming\Typora\typora-user-images\image-20211012151956213.png)

※提供的资料中已经提供了对应的K-Flash.zip压缩包了，可以不用下载，如果没有请按照以上步骤下载。

- 解压K-Flash压缩包，解压后得到名为K-Flash.exe的软件，双击打开该软件，会出现以下界面：

![image-20211012152142597](C:\Users\843530433\AppData\Roaming\Typora\typora-user-images\image-20211012152142597.png)

**4)** ***\*固件烧录\****

-  ***\*把板子的拨动开关拨到ISP的一端\****，因为只有把开关拨到ISP一端，AI模块的默认下载串口才能与电脑端相连接进行固件烧录（***\*务必要完成这一步\****再进行接下来的步骤）：

![image-20211012152227191](C:\Users\843530433\AppData\Roaming\Typora\typora-user-images\image-20211012152227191.png)



- 点击Device（设备）的下拉菜单，找到刚刚在设备管理器的串口设备，并选择它；

  ![image-20211012152507634](C:\Users\843530433\AppData\Roaming\Typora\typora-user-images\image-20211012152507634.png)

- ***\*点击Firmware（固件）\****输入框旁边的按键，如下图：

![image-20211012152523562](C:\Users\843530433\AppData\Roaming\Typora\typora-user-images\image-20211012152523562.png)

- 选择固件（即后缀为 .bin 的文件），然后点击底下的Flash按键即会进行下载。

![image-20211012152544005](C:\Users\843530433\AppData\Roaming\Typora\typora-user-images\image-20211012152544005.png)

下载完成后会弹出窗口显示串口的打印信息，不同固件有不同的打印信息，下图是摄像头显示的固件下载后的串口打印信息，同时你也可以根据固件内容观察板子的实验现象。

​											![image-20211012152604115](C:\Users\843530433\AppData\Roaming\Typora\typora-user-images\image-20211012152604115.png)![image-20211012152606736](C:\Users\843530433\AppData\Roaming\Typora\typora-user-images\image-20211012152606736.png)



### 2.2. **下载失败处理**

​	请确保板上唯一的拨动开关***\*拨到了ISP端\****，否则无法进行固件下载。

​	***\*个别电脑在下载的时候会出现无法进入ISP模式的情况\****，可能跟K-FLASH软件的兼容性有关；

![image-20211012152657907](C:\Users\843530433\AppData\Roaming\Typora\typora-user-images\image-20211012152657907.png)

有这种情况出现的电脑请根据以下步骤，手动让板子进入ISP模式

- 在K-Flash软件中选择完串口后，我们需要长按板子上的BOOT按键，然后再点击K-Flash上的Flash按键进行下载，当出现进入ISP下载模式（英文）或者下载进度的动画时候，既可以放开按键。

![image-20211012152718213](C:\Users\843530433\AppData\Roaming\Typora\typora-user-images\image-20211012152718213.png)