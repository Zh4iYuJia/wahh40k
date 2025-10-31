# 迷你战棋(Scroll down for English version)

一个极简的 C++ 文本游戏，模拟两方（SM 与 CSM）各自装备两把武器进行回合射击的流程。每次射击逐发掷骰并显示结果，命中后按（命中数 × 单发伤害）计算总伤害。
<del>马斯特上课摸鱼时的倾心之作，太无聊+太像打锤导致的</del>
---

## 功能
- 两个单位：SM 与 CSM  
- 每单位两个武器槽：a、b  
- 武器属性：伤害、射弹数、命中阈值（例如 4 表示 4+ 命中）  
- 支持从 weapons.txt 载入武器目录，并可用 units.txt 定义单位模板（可选）  
- 控制台显示每次掷骰、命中数和造成的总伤害

---

## 文件说明
- `base.cpp` — 核心单文件实现（可交互）  
- `weapons.txt` — 武器目录（可选）  
- `units.txt` — 单位模板（可选，指定单位名、HP、允许武器索引）  
- `readme.md` — 本说明

### 关于原项目文件夹
- 项目路径：`c:\Users\mst\Desktop\Dev\Wahh40k\mini-wargame-cpp`  
- 说明：该文件夹包含原始的多文件 C++ 项目（更完整的实现尝试，例如冲锋阶段、射击阶段），但由于存在多处编译/接口/逻辑错误，维护者最终放弃，转而使用当前的单文件简化实现（`base.cpp`）。如果你具备 C++、CMake 与 MSVC 调试经验，欢迎进入该文件夹尝试修复：先运行 `cmake` 配置并查看 `build` 目录的错误，然后逐步修复头文件包含、类接口不匹配、编码问题等。修复后可提交 PR 或与作者沟通合并。

---

## weapons.txt 格式
每行（非注释）格式：  
`Name damage shots hit_threshold`  
注释行以 `#` 开头。若在 `units.txt` 中引用武器索引，使用 1-based（第一行为 1）。

示例：
```
# name damage shots hit_threshold
Boltgun 2 1 4
StormBolter 1 4 4
PlasmaGun 3 2 5
```

## units.txt 格式（可选）
每行：`Name HP idx1 idx2 ...`，idx 为 `weapons.txt` 中的编号（1-based）。例如：  
`Scout 12 1 2` 表示 Scout，HP=12，可选武器为 weapons.txt 的第1和第2项。

---

## 构建与运行（Windows）
要求：C++11 编译器（g++ 或 MSVC）

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

## 游戏玩法
1. 启动程序：若存在 `weapons.txt`，程序会显示武器目录。  
2. 为每个单位选择两把武器（输入武器编号）。  
3. 回合制交替进行：每回合选择 a 或 b 发射，程序打印每次掷骰（例如 `2 2 3 4`），判断命中（掷 ≥ 阈值），计算并显示总伤害与目标剩余生命。  
4. 当任一单位 HP ≤ 0 或玩家选择退出时，游戏结束。

---

## 注意事项
- 请将源文件保存为 UTF-8 以避免 MSVC 的编码警告（C4819）。  
- 若将代码合并到更大项目，请确保正确的 include/构建设置。  
- 推荐在 `.gitignore` 中忽略 `build/` 目录与可执行文件。

---

## 许可证
本项目可用于学习与原型开发，按需修改。

---

# Mini Wargame

A minimal single-file C++ text game where two sides (SM and CSM) each equip two weapons and take turns shooting. Each shot rolls dice per projectile, displays rolls, and applies damage = hits × weapon damage.

---

## Features
- Two sides: SM and CSM  
- Two weapon slots per unit: a and b  
- Weapon properties: damage, shots, hit threshold (e.g. 4 means 4+)  
- Supports loading weapons from `weapons.txt` and optional unit templates from `units.txt`  
- Console prints each die roll, hit count and total damage

---

## Files
- `base.cpp` — Main single-file implementation (interactive)  
- `weapons.txt` — Weapon catalog (optional)  
- `units.txt` — Unit templates (optional: name HP weaponIndex...)  
- `readme.md` — This README

### About the original project folder
- Path: `c:\Users\mst\Desktop\Dev\Wahh40k\mini-wargame-cpp`  
- Note: That folder contains the original multi-file C++ project (more complete implementation attempts, e.g., advance and shooting phases). It was abandoned due to numerous compile/interface/logic issues; the simplified single-file approach (`base.cpp`) is used instead. If you have experience with C++, CMake and MSVC, you can try to repair it: run `cmake` to configure, inspect the build errors in `build`, and fix include paths, class/interface mismatches, encoding and other issues. Contributions or PRs are welcome.

---

## weapons.txt format
Each non-comment line:  
`Name damage shots hit_threshold`  
Comment lines start with `#`. If you reference weapons from `units.txt`, use 1-based indices.

Example:
```
# name damage shots hit_threshold
Boltgun 2 1 4
StormBolter 1 4 4
PlasmaGun 3 2 5
```

## units.txt format (optional)
Each line: `Name HP idx1 idx2 ...` where idx are 1-based indices into `weapons.txt`.  
Example: `Scout 12 1 2` means Scout with HP=12 can select weapons 1 and 2 from `weapons.txt`.

---

## Build & Run (Windows)
Requirements: C++11 compiler (g++ or MSVC)

Quick compile (g++):
```powershell
g++ -std=c++11 -O2 base.cpp -o mini_wargame.exe
.\mini_wargame.exe
```

Using CMake (if CMakeLists exists):
```powershell
mkdir build
cd build
cmake ..
cmake --build . --config Release
# run the produced executable (path depends on configuration)
```

---

## How to play
1. Launch: if `weapons.txt` exists the game shows the catalog.  
2. Pick two weapons for each unit by entering indices.  
3. Take turns: each turn choose slot a or b to fire; the program prints rolls, counts hits (roll ≥ threshold), and applies damage.  
4. Game ends when a unit HP ≤ 0 or player quits.

---

## Notes
- Save source files as UTF-8 to avoid MSVC C4819 warnings.  
- If integrating into a larger project ensure correct include/build settings.  
- Recommend adding `build/` and binaries to `.gitignore`.

---

## License
Use and modify freely for learning or prototyping.