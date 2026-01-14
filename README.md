# 俄罗斯方块（Tetris）  

**游戏展示**
<img alt="Pasted image 20260103133227" src="https://github.com/user-attachments/assets/c9eef9eb-8ed7-404e-90fc-473fb130a0d5" >


**温馨提示**
 - 代码中使用的 ACLLib 图形库具有静态库依赖，作者已在项目中完成正确连接。若需重新编译，请确保你的 Dev-C++ 项目已按 acllib.h 或 acllib.c 中的说明正确配置所需的静态库文件
 - 本项目结构清晰，游戏参数（如地图尺寸、初始下落速度、消除规则等）均在 main.c 文件开头以宏定义或变量形式集中设置，便于自行调整和实验
 - 代码以学习演示为目的，部分实现可能并非最优方案，欢迎交流改进思路

**许可证说明**  
本项目采用GNU通用公共许可证v3.0，主要用于：  
- **学习交流**：供其他学习C语言的同学参考  
- **代码展示**：作为个人编程能力的证明  
- **开源贡献**：为学生项目贡献开源社区  

**重要提示**：本项目包含浙江大学ACLLib图形库，该库同样遵循GPL v3协议。详见LICENSE文件。

**项目结构**  
```
Tetris/
├── acllib.c
├── acllib.h
├── main.c               # 主游戏程序
├── main.h               # 主头文件
├── draw.c               # 图形绘制模块
├── draw.h               # 图形绘制头文件
├── map.c                # 游戏地图与方块管理
├── map.h                # 地图管理头文件
├── recore.c             # 分数记录模块
├── recore.h             # 分数记录头文件
├── Tetris.dev
├── best_record.txt
└── recore.txt
```

**项目配置步骤**  
1. 下载安装Dev-C++  
2. 双击打开Tetris.dev项目文件  
3. 点击编译运行（F11）启动游戏  
4. 修改代码后重新编译即可立即查看效果 

**算法特色**  
采用线性变换处理方块旋转：  
```c
// 旋转变换矩阵计算
void line_change(int* x, int* y, int line[2][3]) {
    int a = *x;
    int b = *y;
    *x = line[0][0]*a + line[0][1]*b + line[0][2];
    *y = line[1][0]*a + line[1][1]*b + line[1][2];
}

// 方块旋转函数
void rotate_block(Blockstate* state) {
    // 计算旋转矩阵
    int rotation_matrix[2][3] = {
        {0, -1, state->x + state->y},
        {1,  0, state->y - state->x}
    };
    
    // 应用于每个方块单元
    for (每个方块单元) {
        line_change(&单元x坐标, &单元y坐标, rotation_matrix);
    }
}
```

**核心游戏功能**  
1. **分数与等级系统**  
   ```c
   // 计分公式
   单行消除：+200分
   双行消除：+800分（200×2²）
   三行消除：+1800分（200×3²）
   四行消除：+3200分（200×4²）
   软降奖励：每格+10分
   ```

2. **速度调节机制**  
   - 基础速度：1000ms/格（可调节）  
   - 速度控制：S键加速×2，Q键减速÷2  
   - 软降功能：按住↓键临时加速  

3. **特殊功能**  
   - 清屏机会：每局游戏一次清屏机会（C键）  
   - 暂停功能：随时暂停游戏（P键）  
   - 一键重启：重置游戏（R键）  

**致谢**  
- 感谢ACLLib团队：提供优秀的C语言图形库，降低学习门槛  
- 感谢师长同学：学习过程中的帮助与鼓励  
- 感谢坚持的自己：完成第一个完整编程项目  

欢迎大家提交Issue和改进建议。  

本项目仅用于学习交流目的。  

作者：浙大学生 - 绿意不息  
版本：1.0.1  
核心代码完成日期：2025年8月14日  
开源发布日期：2026年1月3日  

**附录：游戏界面展示**  
<img alt="Pasted image 20260103133309" src="https://github.com/user-attachments/assets/cff3d35c-d87e-428f-bc94-ee96093c2d4f" />
*游戏引导界面*  

<img alt="Pasted image 20260103133227" src="https://github.com/user-attachments/assets/c9eef9eb-8ed7-404e-90fc-473fb130a0d5" />
*常规游戏界面*  

<img alt="Pasted image 20260103133403" src="https://github.com/user-attachments/assets/54ec583c-07bb-475a-ba3d-4c796c9dcbda" />
*单行消除界面*  
