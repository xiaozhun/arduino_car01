# arduino_car01
实现使用红外遥控小车前进和转向，使用模块 arduino+2个减速电机+红外模块+L298N模块+2节10850电池+小车底盘
## 材料清单
1. arduino uno 模块一个。
2. L298N 驱动电机控制模块。
3. 小车底盘带2个33GB-520个减速电机。
4. 红外接收模块和发射模块。
## 接线注意事项
+ 因为arduino 1针脚 2针脚无法进行高低点评控制，arduino和L298N的连线对应关系:  

| arduino | L298N | 备注 |
| ------ | ------ | ------ |
| 8 | IN1 | 因为arduino 1 2针脚莫名的电平不太容易控制，所以选择其它针脚 |
| 9 | IN2 | 无 |
| 3 | IN3 | 无 |
| 4 | IN4 | 无 |
| GND | GND | 无 |
| 5V | 5V | 采用电池直接供电给L298N,然后由L298N的5V输出给arduino供电 |
| 5 | 使能端A | 需要接到arduino上带波浪线的针脚上 |
| 6 | 使能端B | 同上 |

## 连线图

![线路图](https://github.com/xiaozhun/arduino_car01/blob/master/car.jpg)
