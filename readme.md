# 迷你战棋

一个极简的 C++ 文本游戏，基于小型战斗规则。两方（SM 与 CSM）各自装备两把武器，交替进行射击。骰子为 1–6，全部在控制台显示，英文/中文均可。
<del>马斯特上计算机课时无聊打发时间所作</del>
## 功能
- 两个单位：SM 与 CSM  
- 每个单位两个武器槽：a、b  
- 武器属性：伤害（damage）、射弹数量（shots）、命中阈值（hit threshold，例如 4 表示 4+ 命中）  
- 每次射击逐发掷骰并显示每次掷骰结果；命中数 × 单发伤害 为总伤害  
- 可从外部武器目录文件 `weapons.txt` 载入武器列表

## 文件说明
- `base.cpp` — 单文件简易游戏实现（可交互）  
- `weapons.txt` — 可选武器目录（每行一把武器）  
- `readme.md` — 本说明（当前为中文版本）

## weapons.txt 格式
每行非注释行格式：  
`Name damage shots hit_threshold`  
## 构建与运行（Windows）

前提：安装 C++ 编译器（g++ / MSVC），支持 C++11；可选安装 CMake。

1. 使用 g++（快速）
在项目根目录打开 PowerShell 或 Git Bash：
```powershell
g++ base.cpp -o base.exe
```

##  游戏玩法（简要）
启动后若存在 weapons.txt，程序会显示武器目录；玩家通过输入编号（1、2、3…）为每个单位选择两把武器。
回合中玩家选择武器槽 a 或 b 发射。
程序打印每次掷骰（例如 2 2 3 4），统计命中（掷 >= 阈值），并显示总伤害（命中数 × 单发伤害）。
当任一单位生命值 ≤ 0 或玩家选择退出时，游戏结束。
##  注意事项
请将源文件保存为 UTF-8，避免 MSVC 出现 C4819 编码警告（在 VS Code 中选择 “Save with Encoding → UTF-8”）。
若将此代码集成到更大的项目中，注意设置 include 路径或使用相对包含。
运行可执行时，请将 weapons.txt 放在工作目录（可执行文件同目录）以便加载武器目录。
建议在 .gitignore 中忽略 build/ 目录及可执行文件。

许可证
可自由用于学习或原型开发，按需修改。

注意：目录 mini-wargame-cpp 为一个尝试性的实现（存在问题），建议以 base.cpp 为简化示例使用，若需完善请参考源码并修复。

# Mini Wargame (Simple Text Demo)

A minimal C++ text game inspired by tabletop skirmish rules. Two sides (SM and CSM) equip two weapons each and take turns shooting. Dice are simulated (1–6). All in-console, English text.

## Features
- Two units: SM and CSM
- Each unit equips two weapons (slots `a` and `b`)
- Weapon properties: damage, shots, hit threshold (e.g. 4 means 4+ hits)
- Shooting resolves per-shot rolls; output shows each roll and damage calculation
- Weapon catalog can be loaded from `weapons.txt`

## Files
- `base.cpp` — single-file minimal game implementation (interactive)
- `weapons.txt` — optional weapon catalog (one weapon per line)
- `readme.md` — this file

## weapons.txt format
Each non-comment line:  
`Name damage shots hit_threshold`  
Example:
```
# name damage shots hit_threshold
Boltgun 2 1 4
StormBolter 1 4 4
PlasmaGun 3 2 5
```
Lines starting with `#` are treated as comments.

## Build & Run (Windows)

Prerequisites:
- A C++ compiler (g++ / MSVC) supporting C++11
- (Optional) CMake

1. Using g++ (quick):
Open PowerShell or Git Bash in project root and run:
```powershell
g++ -std=c++11 -O2 base.cpp -o mini_wargame.exe
.\mini_wargame.exe
```

2. Using CMake (if you have a CMakeLists):
```powershell
mkdir build
cd build
cmake ..
cmake --build . --config Release
# then run the produced executable (path may vary)
.\Release\mini_wargame.exe
```

If `cmake` is not installed, install it via `winget install Kitware.CMake -e` or use the g++ method.

## How to play (summary)
- On start, if `weapons.txt` is present the game will show a catalog; choose weapon indices (1,2,3...) for slots `a` and `b`.
- On each turn, choose weapon `a` or `b` to fire.
- The program prints each die roll, counts hits (roll >= threshold) and applies damage = hits * weapon.damage.
- Game ends when one unit's HP ≤ 0 or player quits.

## Notes & Troubleshooting
- Save source files as UTF-8 to avoid MSVC C4819 warnings. In VS Code: "Save with Encoding → UTF-8".
- If include paths or header errors occur when integrating into a larger project, ensure `src` is added to include paths or use relative includes.
- Keep `weapons.txt` in the same working directory when running the executable.

## License
Use and modify as you like for learning or prototyping.

The folder mini-wargame-cpp is a fail try please don't use it.