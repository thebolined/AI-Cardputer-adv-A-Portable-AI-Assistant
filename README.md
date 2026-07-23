# AI-Cardputer-adv-A-Portable-AI-Assistant (Kimi Fork)

> **This fork adds 🌙 Kimi (Moonshot AI) support (v1.3) and 💾 SD-card credential import (v1.4) — see below.**
> Original project by thebolined / Anakin. All credit for v1.0–v1.2 goes upstream.

---

## 🌙 v1.3 — Kimi (Moonshot AI) Support (this fork)

`m5stack_ai_assistant(v1.4).ino` adds **Kimi** as a third AI engine alongside Qwen-Turbo and DeepSeek-Chat.

### What changed
* **Kimi engine added**: model selector now lists `Qwen-Turbo` / `DeepSeek-Chat` / `Kimi-Code` (scroll with `;` / `.`, `Fn + M` to switch mid-chat).
* **OpenAI-compatible call**: Kimi uses the standard `/chat/completions` format, same code path as DeepSeek.
* **Magenta status bar**: the UI theme turns magenta while Kimi is active (Qwen: teal, DeepSeek: blue).
* **Separate key storage**: your Kimi key is stored independently in NVS (`kimi_key`); long-press G0 for 2s to wipe everything.

---

### 🔑 Getting your Kimi key (membership / subscription)

You do **not** need a separate pay-per-token developer account. Any Kimi membership tier (**Andante / Moderato / Allegretto / Allegro**) can mint API keys for third-party tools:

1. Go to the **Kimi Code Console**: https://www.kimi.com/code/console and sign in with your Kimi account.
2. Click **"Create API Key"**, give it a name (e.g. `cardputer`), and confirm.
3. **Copy the key immediately** — it is shown only once. It starts with `sk-kimi-`. (You can hold up to 5 keys.)
4. Get the key onto the device — either via SD card (v1.4, recommended, see below) or by typing it when the **Kimi-Code** engine prompts on first use.

Notes:
* Usage draws from your **membership quota**, not a metered bill.
* Kimi Code keys and Kimi Open Platform keys are **not interchangeable** — a key from one returns `401` on the other.
* With **Moderato or above** you can also change `KIMI_MODEL` in the sketch to `k3` (Kimi K3); `kimi-for-coding` (K2.7 Code) works on every tier.

### Which endpoint / key to use

Two Moonshot key types work — pick the one matching your key (top of the sketch):

| Key type | `KIMI_API_URL` | `KIMI_MODEL` |
| --- | --- | --- |
| **Kimi Code / membership key** (`sk-kimi-...`) | `https://api.kimi.com/coding/v1/chat/completions` *(default)* | `kimi-for-coding` *(default)* |
| **Open Platform key** (pay-per-token, platform.kimi.com) | `https://api.moonshot.ai/v1/chat/completions` | `kimi-k3` or `kimi-k2.7-code` |

If you get `Error: 401`, you're using the wrong endpoint for your key type — flip the `#define`s at the top of the sketch.

---

## 💾 v1.4 — Import keys & WiFi from SD card (this fork)

Typing a 70-character API key (or a long WiFi password) on the Cardputer keyboard is painful and error-prone. v1.4 lets you stage credentials as plain text files on the SD card root instead.

### File formats (place on SD root)

| File | Contents | Imported into |
| --- | --- | --- |
| `/kimi_key.txt` | one line: your `sk-kimi-...` key | NVS `kimi_key` |
| `/qwen_key.txt` | one line: your DashScope key | NVS `qwen_key` |
| `/ds_key.txt` | one line: your DeepSeek key | NVS `ds_key` |
| `/wifi.txt` | line 1: SSID, line 2: password | NVS WiFi config |

### How it works
1. Create the file(s) on your computer, copy to the **root of a FAT32 microSD card**, insert the card.
2. Boot the app. WiFi is imported at startup; API keys are imported the first time you select that engine.
3. **After a successful import the file is automatically deleted from the SD card** — no plaintext key lingers on the card. The credential lives in NVS from then on (until a G0 factory reset).
4. Lookup order per engine: **NVS → SD txt file → manual keyboard input**. If no SD card / no file is found, the old manual prompt appears as before.

Security notes:
* The `.gitignore` in this repo blocks `*_key.txt` and `wifi.txt` — never commit these files.
* Anyone with the SD card can read the files before import. Import once, and the card is clean again.
* Bonus fix in v1.4: saved WiFi credentials that fail now fall back to the scan UI instead of silently retrying.

---

### 🚀 Install Path A — via bmorcelli Launcher (recommended)

Run this app **alongside Bruce and other firmware**, switchable from a boot menu. Source: [Launcher wiki — Obtaining binaries to launch](https://github.com/bmorcelli/Launcher/wiki/Obtaining-binaries-to-launch).

1. **Install Launcher** on the Cardputer: web flasher at https://bmorcelli.github.io/Launcher/ (or via M5Burner).
2. **Export the binary**: Arduino IDE → open `m5stack_ai_assistant(v1.4).ino` → `Sketch > Export Compiled Binary` → find the app binary in the generated `build` folder.
3. **Rename it** to something simple, e.g. `kimi-cardputer.bin` — parentheses and spaces in filenames can trip the installer.
4. **Copy it to a FAT32 microSD card**, insert the card, open `SD` in Launcher → select the file → **Install**. Launcher 2.7+ checks the image and creates a suitable app partition automatically — you do **not** need the "Huge APP" partition scheme for this path.
   * No SD card? Open `WUI` in Launcher, browse to the shown IP from your computer, and upload the `.bin` there (default login `admin` / `launcher`).
5. **Launch** the app from Launcher's main menu. `CFG > Boot to Launcher` controls whether the device boots to the menu or straight into the last-used app.

Notes:
* Your WiFi credentials and Kimi key live in NVS (`Preferences`) and **persist across Launcher app switches** — enter them once.
* The G0 factory reset only clears this app's own NVS namespaces (`qwen-config`, `ai-keys`); Launcher's settings are untouched.
* If an SD install fails, retry through the WebUI installer.

### 🚀 Install Path B — direct flash (standalone)

Arduino IDE → install `M5Cardputer` + `ArduinoJson` (7.x) libraries → partition scheme **Huge APP (3MB No OTA)** → upload. On first boot, select **Kimi-Code** in the model menu and paste your API key (or pre-stage it via SD as above).

---

# 🚀 Qwen-Cardputer: A Portable AI Assistant

**Qwen-Cardputer** is an open-source, portable AI terminal built for the **M5Cardputer**. It integrates the powerful AliCloud Qwen (Tongyi Qianwen) LLM into a handheld form factor, allowing you to interact with advanced artificial intelligence anytime, anywhere via Wi-Fi.

This project features a customized **Cyberpunk-inspired** startup sequence and a streamlined UI designed for the Cardputer's mechanical keyboard and 1.14-inch display.

---

## ✨ Key Features / 核心功能
* **Real-time AI Interaction**: Low-latency communication with the Qwen-Turbo model. (与 Qwen-Turbo 模型进行低延迟实时对话)
* **Custom Cyber-Glitch Startup**: A unique, developer-branded (**Anakin v1.0**) boot animation. (独特的赛博故障风开机动画及开发者署名)
* **Persistent Configuration**: Saves your Wi-Fi credentials and API keys securely using onboard NVS. (持久化存储 Wi-Fi 及 API Key 配置)
* **Quick Reset**: Hardware-level reset via a 2-second long press of the **G0 button**. (长按侧边 G0 按键 2 秒即可硬件级重置系统)
* **Enhanced UI**: Optimized rendering, scrollable history, and battery monitoring. (优化的 UI 渲染、滚动历史记录及电量监控)

---

## 🔑 API Configuration / API 配置指南

To use the AI features, you need an API Key from AliCloud DashScope.
若要使用 AI 功能，您需要从阿里云百炼平台获取 API Key：

1.  **Console Access**: Visit the [AliCloud DashScope (Model Studio)](https://dashscope.console.aliyun.com/). (访问 [阿里云百炼控制台](https://dashscope.console.aliyun.com/))
2.  **Activate Service**: Search for "DashScope" and activate the service. (开通“模型服务 DashScope”，新用户通常有免费额度)
3.  **Create Key**: Go to **API-KEY Management** and click "Create New API-KEY". (在 API-KEY 管理页创建新的密钥)
4.  **Security**: Copy your key and enter it into your Cardputer on the first boot. (复制密钥并在设备首次开机时输入)

---

## 🛠️ Hardware & Learning / 硬件与学习资源

### Where to Buy Hardware / 硬件购买:
* **M5Cardputer**: Available at the [M5Stack Official Store](https://shop.m5stack.com/products/m5stack-cardputer-kit-w-m5stamps3) or Taobao/AliExpress. (可通过 M5Stack 官方商城或天猫旗舰店购买)

### M5Stack Community / 社区支持:
* **Official Forum**: [M5Stack Community](https://community.m5stack.com/) - Troubleshooting and discussions.
* **Documentation**: [M5Stack Docs](https://docs.m5stack.com/) - Detailed pinouts and references.

---

## 🚀 Getting Started / 快速开始

1.  **Libraries**: Install `M5Cardputer`, `ArduinoJson`, and `HTTPClient` in Arduino IDE.
2.  **Flash**: Select **"Huge APP (3MB No OTA)"** in the Partition Scheme. (烧录时分区方案请选择 Huge APP)
3.  **Setup**: Follow the on-screen boot animation. On first launch, the device will scan for Wi-Fi and prompt for your API Key.

---

## 📅 Roadmap / 开发计划
This project is under active development. Future updates will include:
* [x] Integration of more AI APIs (DeepSeek, ~~GPT-4o, Claude~~ → **Kimi** added in this fork).
* [x] SD-card credential import (no more typing long keys).
* [ ] Voice-to-Text capabilities using the onboard microphone.
* [ ] UI themes and customization options.

![374bfb8fb4fe78b3726e1925f033de36](https://github.com/user-attachments/assets/6d037e4d-ec0e-49aa-8b0a-3ac8fa4673e9)

![fb10f4880a4f0b3530359e9b14a5dbd4](https://github.com/user-attachments/assets/ca86e5f4-92af-4ddb-b3ea-706843ccf33e)

![483d3d0c1ea007f0871b400b44062727](https://github.com/user-attachments/assets/234eff61-8040-407e-aca5-2bb679f90a34)


v1.1 update
🚀 Added | 新增
Cyberpunk Startup: Added a high-speed glitch animation during system boot.

赛博启动: 系统启动时新增高刷故障风动画。

WiFi Scan & Select: A robust WiFi management UI with automatic reconnection on boot.

WiFi 扫描与选择: 强大的 WiFi 管理界面，支持开机自动重连。

Qwen-Turbo Core: Initial implementation of Alibaba's LLM via HTTPS POST.

Qwen 核心: 首次实现通过 HTTPS POST 调用阿里云大模型。

Battery Indicator: Real-time battery percentage with color-coded alerts.

电量指示: 实时百分比显示，低电量时自动变红预警。

🛠️ Fixed & Improved | 修复与改进
Cursor Movement: Added Fn + , and Fn + / for precise text editing.

光标移动: 增加 Fn + , 与 Fn + / 实现精准文本编辑。

Manual Scrolling: Implemented Fn + ; and Fn + . for reading long AI replies.

手动滚动: 支持 Fn + ; 与 Fn + . 查阅 AI 长回复。

Factory Reset: Long press G0 button for 2s to clear all NVS data (WiFi & Keys).

工厂复位: 长按 G0 键 2 秒可清除所有已存数据。


v1.2 update
# 🤖 Anakin AI Assistant (v1.2)

**Anakin** is a powerful, portable AI assistant designed specifically for the **M5Cardputer**. It bridges the gap between your pocket and the world's leading LLMs, featuring native integration for both **Qwen (Aliyun)** and **DeepSeek**.

**Anakin** 是一款专为 **M5Cardputer** 打造的强大便携式 AI 助手。它将大语言模型（LLM）装进你的口袋，原生支持 **通义千问 (Qwen)** 与 **DeepSeek** 双引擎。

---

### ✨ v1.2 New Features | 新特性

* **🔄 Model Selector UI | 模型滚动选择器**
* Navigate through AI models (**Qwen-Turbo** / **DeepSeek-V3**) using a WiFi-style scrolling menu with `;` and `.` keys.
* 使用类 WiFi 扫描界面的交互逻辑，通过 `;` 和 `.` 键在 **Qwen-Turbo** 与 **DeepSeek-V3** 间无缝切换。


* **⚡ DeepSeek Native Support | DeepSeek 原生支持**
* Fully compatible with DeepSeek's OpenAI-style API. High-speed inference directly on your ESP32-S3.
* 完美适配 DeepSeek API 格式，在 ESP32-S3 上实现极速对话响应。


* **💾 Smart Key Persistence | 智能 Key 持久化**
* Independent storage for different API keys using NVS (`Preferences`). Input once, access anytime.
* 为不同平台独立存储 API Key，一次输入，永久记忆。


* **🎨 Reactive Status Bar | 感应式状态栏**
* UI theme colors change dynamically based on the active model (Qwen: **Teal** | DeepSeek: **Blue**).
* 状态栏颜色随模型动态改变（Qwen: **深青色** | DeepSeek: **蓝色**），电量实时监控。


* **🛠️ On-the-fly Switching | 实时切换**
* Press `Fn + M` to bring up the model menu instantly without rebooting.
* 无需重启，按下 `Fn + M` 即可在对话中途随时重选模型。

---

### ⌨️ Key Map | 操作指南

| Key (按键) | Function (EN) | 功能 (CN) |
| --- | --- | --- |
| **`;` / `.`** | **Scroll**: Navigate lists (Up/Down) | **滚动**：列表向上 / 向下 |
| **Enter** | **Confirm**: Send / Select / Enter | **确认**：发送消息 / 确认选择 |
| **Del** | **Delete**: Backspace character | **删除**：回退输入字符 |
| **Fn + `,` / `/**` | **Cursor**: Move left / right | **光标**：左右移动输入光标 |
| **Fn + `;` / `.`** | **Screen Scroll**: View history | **屏幕滚动**：查阅长回复历史 |
| **Fn + M** | **Switch**: Change AI Model | **切换**：实时弹出模型菜单 |
| **G0 Button** | **Hard Reset**: Long press 2s to wipe | **重置**：侧边按键长按 2s 清除所有配置 |

---

### 🚀 Quick Start | 快速开始

1. **Flash**: Upload the code using Arduino IDE (ensure `M5Cardputer` and `ArduinoJson` libraries are installed).
* **烧录**：使用 Arduino IDE 上传代码（确保已安装相关库）。


2. **Network**: Select your WiFi and enter the password.
* **联网**：在启动菜单中连接 WiFi。


3. **Model Select**: Choose your engine. If it's your first time, the system will prompt for the **API Key**.
* **模型选择**：选择引擎。首次使用时，系统会提示输入 **API Key**。


4. **Chat**: Type your message and hit Enter!
* **对话**：输入文字并按回车发送！

---

### 📂 Technical Stack | 技术栈

* **Microcontroller**: ESP32-S3
* **Display Library**: M5Canvas (for flicker-free rendering)
* **Data Handling**: ArduinoJson 7.x
* **Protocol**: HTTPS (Secure API Calls)

---

### 📜 Changelog | 更新日志

* **v1.4 (this fork)**:
* Import API keys (`kimi_key.txt` / `qwen_key.txt` / `ds_key.txt`) and WiFi (`wifi.txt`) from SD card root.
* Imported files are auto-deleted from SD; credentials persist in NVS.
* Fallback to WiFi scan UI when saved credentials fail.
* **v1.4（本 Fork）**：支持从 SD 卡导入 Key 与 WiFi 凭据；导入后自动删除明文文件；凭据失效自动回退到扫描界面。


* **v1.3 (this fork)**:
* Added Kimi (Moonshot AI) engine via OpenAI-compatible endpoint.
* Kimi Code subscription key support (`kimi-for-coding`).
* Magenta status bar theme for Kimi.
* bmorcelli Launcher install path documented.
* **v1.3（本 Fork）**：新增 Kimi 引擎；支持 Kimi Code 订阅 Key；Kimi 主题状态栏；补充 Launcher 安装路径。


* **v1.2**:
* Added DeepSeek API support.
* Implemented interactive model selection menu.
* Optimized Preferences storage logic.
* **v1.2**：增加 DeepSeek 支持；实现交互式模型菜单；优化存储逻辑。


* **v1.1**:
* Initial Qwen-Turbo implementation.
* Startup animations and WiFi persistence.
* **v1.1**：实现基础 Qwen 调用、启动动画及 WiFi 持久化。


**Original: Anakin | Kimi fork: PerrySm** *Stay tuned for more updates! 本项目将持续维护，敬请期待更多功能！*
