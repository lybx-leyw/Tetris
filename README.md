# Tetris

这是我为了**巩固 C 语言编程基础**而创建的俄罗斯方块游戏项目。一个基于 ACLLib 图形库实现的简单俄罗斯方块游戏，采用纯 C 语言开发。

##  许可证说明

本项目采用 **GNU General Public License v3.0** 许可证，主要用于：
1. **学习交流**：分享给其他学习 C 语言的同学参考
2. **代码展示**：作为个人编程能力的证明
3. **开源贡献**：为开源社区贡献一份学生项目

**重要提示**：本项目包含浙江大学 ACLLib 图形库，同样遵循 GPL v3 许可证。

##  项目结构

```
Tetris/
├── acllib.c              
├── acllib.h             
├── main.c                # 游戏主程序
├── main.h                # 主头文件
├── draw.c                # 图形绘制模块
├── draw.h                # 图形绘制头文件
├── map.c                 # 游戏地图和方块管理
├── map.h                 # 地图管理头文件
├── recore.c              # 分数记录模块
├── recore.h              # 分数记录头文件
├── Tetris.dev          
├── best_record.txt       
└── recore.txt
```

## 项目设置步骤
1. 下载并安装 Dev-C++
2. 双击打开 `Tetris.dev` 项目文件
3. 点击 **编译运行** (F11) 即可开始游戏
4. 修改代码后重新编译，立即看到效果

## 算法特点
线性变换处理方块旋转
```c
// 旋转矩阵计算
void line_change(int* x, int* y, int line[2][3]) {
    int a = *x;
    int b = *y;
    *x = line[0][0]*a + line[0][1]*b + line[0][2];
    *y = line[1][0]*a + line[1][1]*b + line[1][2];
}

// 旋转方块
void rotate_block(Blockstate* state) {
    // 计算旋转矩阵
    int rotation_matrix[2][3] = {
        {0, -1, state->x + state->y},
        {1,  0, state->y - state->x}
    };
    
    // 应用到每个方块单元
    for (每个方块单元) {
        line_change(&unit_x, &unit_y, rotation_matrix);
    }
}
```

##  核心游戏特性

### 1. 分数与等级系统
```c
// 分数计算公式
单行消除：+200 分
双行消除：+800 分（200×2²）
三行消除：+1800 分（200×3²）
四行消除：+3200 分（200×4²）
软降落加分：每格 +10 分
```

### 2. 速度调节机制
- **基础速度**：1000ms/格（可调）
- **加速功能**：S键×2加速，Q键÷2减速
- **软加速**：按住↓键临时加速

### 3. 特殊功能
- **清空机会**：每局游戏提供一次清空机会（C键）
- **暂停功能**：随时暂停游戏（P键）
- **重新开始**：一键重置游戏（R键）

##  致谢

- **感谢 ACLLib 团队**：提供了优秀的 C 语言图形库，降低了学习门槛
- **感谢老师和同学**：在学习过程中给予的帮助和鼓励
- **感谢坚持的自己**：完成了第一个完整的编程项目

---

欢迎大家提交问题和改进建议。  
本项目仅供学习交流使用。

---
**作者**：浙江大学学生-绿意不息  
**版本**：1.0  
**核心代码完成时间**：2025年8月14日  
**开源发布时间**：2026年1月3日  

---
## 附录：游戏界面展示

<img alt="Pasted image 20260103133309" src="https://github.com/user-attachments/assets/9cd58e30-08f3-4f3b-aa77-afffa6417550" />
*游戏Guide界面*

<img alt="Pasted image 20260103133227" src="https://github.com/user-attachments/assets/c9eef9eb-8ed7-404e-90fc-473fb130a0d5" />
*正常游戏界面*

<img alt="Pasted image 20260103133403" src="https://github.com/user-attachments/assets/54ec583c-07bb-475a-ba3d-4c796c9dcbda" />
*消除单行界面*




