# Learning_Assistant
星火杯二等奖作品记录。这是一个基于Arduino UNO板的有一些有趣功能的学习小助手。

## About

这是大一参加星火杯的作品。由于年代较久，且当时并没有上传、记录的意识，导致留下的痕迹较为残缺，实物也已经无法启动。所幸我仍在U盘中找到了 **疑似是** 最终成品的源代码，实物外表也完好无损，因此依然存在着开源的可能。

这是我最早期的作品，回看感慨万千。

## 实物图

![实物图](https://i0.hdslb.com/bfs/article/49820e907aee3c5392dade84b7527870481184837.jpg)

实物图。图中涂抹部分为姓名学号。整体体积不大，6.2/*7.1/*1.6cm，约等于小型游戏机。

## 原理图与PCB效果图

![原理图](https://i0.hdslb.com/bfs/article/da45f4ad5c26241fd90376b4a5d5cc2e481184837.png)

原理图。

![PCB效果图](https://i0.hdslb.com/bfs/article/77e67e7fdb0721e945fce6bb5881ffca481184837.jpg)

PCB效果图。使用立创EDA绘制的。

## 功能列表

1. 基于RTC DS3231模块的实时时钟、计时器、闹钟功能。
2. 储存在数组中，利用tone播放《欢乐颂》曲调的音乐功能。
3. 自由演奏音乐功能。
4. 一个简单的接小球小游戏。

## 开源注意

1. 在About章节中已经说明，我找到的代码只是 **疑似为** 当时最终成品的源代码。但是可信度还是很高的。
2. 本项目全部开源，即ArduinoIDE中的代码与PCB工程文件开源。
3. 元件列表（均为插件）
   1. DS3231模块  1个
   2. 1.3寸OLED模块  1个  （四排线：GND、VCC\SCL\SDA左到右依序，若不是四排线则需修改源代码和PCB文件，若是四排线但不按照此顺序则需修改源代码）
   3. 5.8自锁按键开关  10个  （PS-5836DVA-6PL）
   4. 发光led  3个
   5. 1KΩ电阻  2个
   6. 蜂鸣器  1个  （脚距7.6）
   7. Arduino UNO板  1个
   8. 排针  若干
5. 一点说明：按照我开源的PCB文件复制成品的话，各元件插在PCB板正面，Arduino UNO板通过排针，插在PCB板的背面。如图所示。
   ![](https://i0.hdslb.com/bfs/article/3f7768640c78c61772be6aefec451307481184837.jpg)
