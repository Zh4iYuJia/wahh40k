# 迷你战棋 / Mini Wargame

一个极简的 C++ 文本游戏，模拟两方（SM 与 CSM）各自装备两把武器进行回合射击的流程。每次射击逐发掷骰并显示结果，命中后按（命中数 × 单发伤害）计算总伤害。  
<del>马斯特上课时的无心之作,因为课太无聊+太想打锤<del>
A minimal single-file C++ text game where two sides (SM and CSM) each equip two weapons and take turns shooting. Each shot rolls dice per projectile, displays rolls, and applies damage = hits × weapon damage.

---

## 功能 / Features
- 两个单位：SM 与 CSM。Each side: SM and CSM.  
- 每单位两个武器槽：a、b。Two weapon slots per unit: a and b.  
- 武器属性：伤害、射弹数、命中阈值（例如 4 表示 4+ 命中）。Weapon properties: damage, shots, hit threshold (e.g. 4 means 4+).  
- 支持从 weapons.txt 载入武器目录，并可用 units.txt 定义单位模板（可选）。Supports loading weapons from weapons.txt and optional unit templates from units.txt.  
- 控制台显示每次掷骰、命中数和造成的总伤害。Console prints each die roll, hit count and total damage.

---

## 文件说明 / Files
- `base.cpp` — 核心单文件实现（可交互）。Main single-file implementation (interactive).  
- `weapons.txt` — 武器目录（可选）。Weapon catalog (optional).  
- `units.txt` — 单位模板（可选，指定单位名、HP、允许武器索引）。Unit templates (optional: name HP weaponIndex...).  
- `readme.md` — 本说明。This README.

---

## weapons.txt 格式 / weapons.txt format
每行（非注释）格式：  
`Name damage shots hit_threshold`  
注释行以 `#` 开头。Indices used in units.txt are 1-based (第一行为 1)。  
Each non-comment line: `Name damage shots hit_threshold`. Comment lines start with `#`. If you reference weapons from `units.txt`, use 1-based indices (first weapon is 1).

示例 / Example:
```
# name damage shots hit_threshold
Boltgun 2 1 4
StormBolter 1 4 4
PlasmaGun 3 2 5
```

## units.txt 格式（可选） / units.txt format (optional)
每行：`Name HP idx1 idx2 ...`，idx 为 weapons.txt 中的编号（1-based）。例如：  
`Scout 12 1 2` 表示 Scout，HP=12，可选武器为 weapons.txt 的第1和第2项。  
Each line: `Name HP idx1 idx2 ...` where idx are 1-based indices into weapons.txt.

---

## 构建与运行 / Build & Run (Windows)
要求：C++11 编译器（g++ 或 MSVC）。  
Requirements: C++11 compiler (g++ or MSVC).

快速编译（g++）：
```powershell
g++ -std=c++11 -O2 base.cpp -o mini_wargame.exe
.\mini_wargame.exe
```

使用 CMake（如有 CMakeLists）：
```powershell
mkdir build
cd build
cmake ..
cmake --build . --config Release
# 运行生成的可执行文件（路径视配置而定）
```

---

## 游戏玩法 / How to play
1. 启动程序：若存在 `weapons.txt`，程序会显示武器目录。If `weapons.txt` exists the game shows the catalog.  
2. 为每个单位选择两把武器（输入武器编号）。Pick two weapons for each unit by entering indices.  
3. 回合制交替进行：每回合选择 a 或 b 发射，程序打印每次掷骰（例如 `2 2 3 4`），判断命中（掷 ≥ 阈值），计算并显示总伤害与目标剩余生命。On each turn choose slot a or b to fire; the program prints rolls, counts hits (roll ≥ threshold), and applies damage.  
4. 当任一单位 HP ≤ 0 或玩家选择退出时，游戏结束。Game ends when a unit HP ≤ 0 or player quits.

---

## 注意事项 / Notes
- 请将源文件保存为 UTF-8 以避免 MSVC 的编码警告（C4819）。Save source files as UTF-8 to avoid MSVC C4819 warnings.  
- 若将代码合并到更大项目，请确保正确的 include/构建设置。If integrating into a larger project, ensure correct include/build settings.  
- 推荐在 `.gitignore` 中忽略 build/ 目录与可执行文件。Recommend adding build/ and binaries to .gitignore.

---

## 许可证 / License
本项目可用于学习与原型开发，按需修改。Use and modify freely for learning or prototyping.

---