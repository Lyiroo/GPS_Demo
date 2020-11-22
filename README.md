# 最近的修改
* 2020/11/22 </br>
STM32F1/GPS_demo
改用原开发板上的STM32F101RB芯片，外接GSM/GPRS/GNSS模块.
GNSS中包括北斗、GPS和准天顶系统三者联合定位，相比于原NEO-6M模块解决了定位时间长的问题.
GNSS通过有源天线获取位置信息，传输给STM32F1，插有SIM卡的F1将位置信息通过HTTP协议发送到[中国移动OneNet物联网开发平台](https://open.iot.10086.cn/).</br>
OneNet通过F1的device_id和APIKey获取API，将位置信息其以数据流的方式显示在网页，支持历史回放显示运动轨迹.</br>
* 2020/11/11 </br>
STM32F4/GPS_demo_final
简单在TFTLCD上显示运动轨迹.
* 2020/10/31 </br>
STM32F4/GPS_demo_1031演示程序.
静态显示.
* 2020/10/20 </br>
实现定位.
# STM32F1使用说明
## 一 OneNet配置
###  Step1
注册并登录[中国移动OneNet物联网开发平台](https://open.iot.10086.cn/)账号，点击右上角“控制台”，登录开发者中心.
###  Step2
页面左上角六边形图标，全部产品->基础服务->多协议接入->http
### Step3
添加产品->创建产品,产品名称/行业/类别/简介随便写,但技术参数如下配置：
 ![技术参数](https://github.com/freepoet/GPS_demo/blob/main/Images/OneNet/%E6%8A%80%E6%9C%AF%E5%8F%82%E6%95%B0.png#pic_center)</br>
### Step4
点击确定后，在弹出的窗口点击立即添加设备，在新的页面点击右上角添加设备。详情如下：
 ![添加设备](https://github.com/freepoet/GPS_demo/blob/main/Images/OneNet/%E6%B7%BB%E5%8A%A0%E8%AE%BE%E5%A4%87.png#pic_center)</br>
### Step5
点击产品概况，查看并复制master-key.</br>
点击设备列表->详情->添加APIKey，输入master-key.详情如下：</br>
 ![设备详情](https://github.com/freepoet/GPS_demo/blob/main/Images/OneNet/%E8%AE%BE%E5%A4%87%E8%AF%A6%E6%83%85.png#pic_center)</br>
### Step6
记录设备ID和APIKey，修改main.c文件里的device_id[]和API_KEY[]，然后编译下载程序.</br>
 ![代码](https://github.com/freepoet/GPS_demo/blob/main/Images/OneNet/%E4%BB%A3%E7%A0%81.png#pic_center)
### Step7
程序正常运行后，即可在设备列表-》数据流详情里查看运动轨迹，如图所示：</br>
 ![运动轨迹](https://github.com/freepoet/GPS_demo/blob/main/Images/OneNet/%E8%BF%90%E5%8A%A8%E8%BD%A8%E8%BF%B9.png#pic_center)</br>

## 二 引脚连接

## 三 使用

--------------------
# STM32F4使用说明
**STM32F407+NEO-6M的使用说明**
## 一 引脚的连接
       GPS模块<-------------->STM32开发板
        VCC                    电源模块5V
        GND                    电源模块GND
        TXD                     PB11
        RXD                     PB10
        PPS(悬空)
--------------------
## 二 使用
### 1、开发板接上电源和仿真器，烧录程序.
### 2、按一下按键模块的"复位"按键，程序开始运行，按"K_DOWN"进行功能切换，
#### 功能1：显示时间、经纬度、海拔等信息；
在空旷位置，首次定位时间较长，可能需要几分钟的时间。<br>
fix mode:3D 代表定位成功。 定位成功以后才能切换到功能2.
#### 功能2：轨迹绘制；
### 三 程序流程图：




  
