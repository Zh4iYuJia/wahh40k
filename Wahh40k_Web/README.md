# Mini Wargame Web

A web-based turn-based wargame inspired by Warhammer 40k, ported from a C++ console application. Players select units with weapons, engage in dice-based combat, and battle until one side's HP reaches zero.

## Features

- Unit selection from database
- Dice-rolling combat mechanics
- Real-time HP updates and battle logs
- SQLite database for units and weapons
- Simple web interface

## Installation

1. Ensure Node.js is installed (download from https://nodejs.org).
2. Clone or download the project.
3. Navigate to the `web-game` directory.
4. Run `npm install` to install dependencies.
5. Run `npm start` to start the server.
6. Open `http://localhost:3000` in your browser.

## Usage

1. Select two units (one for SM, one for CSM).
2. Click attack buttons to roll dice and deal damage.
3. View battle logs and HP changes.
4. Game ends when one unit's HP is 0.

## File Structure

- `server.js`: Express server and API endpoints
- `database.js`: SQLite database operations
- `schema.sql`: Database schema and initial data
- `public/index.html`: Main HTML page
- `public/styles.css`: CSS styles
- `public/game.js`: Client-side game logic
- `package.json`: Node.js dependencies

## API Endpoints

- `GET /api/units`: Get all units with weapon details
- `GET /api/weapons`: Get all weapons
- `POST /api/units`: Add a new unit

## License

MIT License

---

# Mini Wargame Web

一个基于网页的回合制战棋游戏，灵感来源于Warhammer 40k，从C++控制台应用程序移植而来。玩家从数据库中选择单位和武器，进行基于骰子的战斗，直到一方HP为零。

## 功能

- 从数据库中选择单位
- 骰子战斗机制
- 实时HP更新和战斗日志
- SQLite数据库存储单位和武器
- 简单的网页界面

## 安装

1. 确保安装了Node.js（从https://nodejs.org下载）。
2. 克隆或下载项目。
3. 导航到`web-game`目录。
4. 运行`npm install`安装依赖。
5. 运行`npm start`启动服务器。
6. 在浏览器中打开`http://localhost:3000`。

## 使用方法

1. 选择两个单位（一个给SM，一个给CSM）。
2. 点击攻击按钮掷骰子和造成伤害。
3. 查看战斗日志和HP变化。
4. 当一个单位的HP为0时游戏结束。

## 文件结构

- `server.js`：Express服务器和API端点
- `database.js`：SQLite数据库操作
- `schema.sql`：数据库schema和初始数据
- `public/index.html`：主HTML页面
- `public/styles.css`：CSS样式
- `public/game.js`：客户端游戏逻辑
- `package.json`：Node.js依赖

## API端点

- `GET /api/units`：获取所有单位及其武器详情
- `GET /api/weapons`：获取所有武器
- `POST /api/units`：添加新单位

## 许可证

MIT许可证