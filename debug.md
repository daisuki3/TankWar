1. 链接错误 
![link](https://github.com/daisuki3/TankWar/blob/master/de/link.png)

原因：没有在 main.cpp 初始化全局机构体 struct info 导致报错

2. painter 画不出效果 
![paint](https://github.com/daisuki3/TankWar/blob/master/de/paint.png)
![paint_GUI](https://github.com/daisuki3/TankWar/blob/master/de/paintGUI.png)

原因：错误的图片地址，导致解析出错，图片加载不出

3. 异常地图
![map_init](https://github.com/daisuki3/TankWar/blob/master/de/map_init.png)
![cell_init](https://github.com/daisuki3/TankWar/blob/master/de/cell_init.png)

原因：地图初始化出错

4. 程序异常结束 
![exit](https://github.com/daisuki3/TankWar/blob/master/de/exit.png)

原因：运行会直接崩溃，找不到结果。尝试用debugger，但debugger无法正常启动，配置好debugger后找到了原因：segmentation fault

5. segmentation fault 初步猜测是数组越界
![array](https://github.com/daisuki3/TankWar/blob/master/de/array.png)

原因：函数调用时，错误的参数传递，错误的参数最后导致数组越界
![get_cell](https://github.com/daisuki3/TankWar/blob/master/de/get_cell.png)

6. 攻击BOSS BOSS不死亡
![fire_boss](https://github.com/daisuki3/TankWar/blob/master/de/fire_boss.png)

原因：地图元素中的BOSS元素和全局结构体info中的BOSS对象是分离的，无法正确执行BOSS的死亡逻辑
解决办法是在地图元素类中加入BOSS元素的死亡判断 

7. 玩家坦克卡住
![tank_stuck](https://github.com/daisuki3/TankWar/blob/master/de/tank_stuck.png)


原因：movejudge函数中，方向计算逻辑有误
![movejudge_wrong](https://github.com/daisuki3/TankWar/blob/master/de/movejudge_wrong.png)

8. unknown signal
![signal_error](https://github.com/daisuki3/TankWar/blob/master/de/signal_error.png)

原因：初步猜测数组越界 检查后发现是missile类的构造函数中变量未正确初始化

9. 敌方坦克子弹无法显示

原因：missile类的构造函数中，导弹坐标未给到正确的初始化参数