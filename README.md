# AI-Cardputer-adv-A-Portable-AI-Assistant
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
* [x] Integration of more AI APIs (DeepSeek, Kimi).
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

* **v1.2**:
* Added DeepSeek API support.
* Implemented interactive model selection menu.
* Optimized Preferences storage logic.
* **v1.2**：增加 DeepSeek 支持；实现交互式模型菜单；优化存储逻辑。


* **v1.1**:
* Initial Qwen-Turbo implementation.
* Startup animations and WiFi persistence.
* **v1.1**：实现基础 Qwen 调用、启动动画及 WiFi 持久化。


v1.3 update
# 🌙 Anakin AI Assistant (v1.3) — Kimi K3

**Anakin v1.3** adds **Kimi K3 (Moonshot AI)** as a third AI engine, alongside **Qwen-Turbo** and **DeepSeek-Chat**.

**Anakin v1.3** 新增第三引擎 **Kimi K3（月之暗面 Moonshot AI）**，与 **通义千问**、**DeepSeek** 并列。

---

### ✨ v1.3 New Features | 新特性

* **🌙 Kimi K3 Engine | Kimi K3 引擎**
* Native support for Moonshot AI's Kimi via an OpenAI-compatible endpoint (model `k3`), using the same request path as DeepSeek. Selectable in the model menu; the status bar turns **magenta** while active.
* 原生支持月之暗面 Kimi（OpenAI 兼容接口，模型 `k3`），与 DeepSeek 共用请求路径。模型菜单可选，启用时状态栏为**品红色**。


* **🗝️ Key Management | Key 管理**
* Press `Del` in the model menu to clear the highlighted engine's saved API key — no full factory reset needed. Keys can also be edited from a browser via bmorcelli Launcher's WebUI NVS editor (namespace `ai-keys`).
* 在模型菜单按 `Del` 可清除当前引擎已保存的 API Key，无需整机复位。也可通过 bmorcelli Launcher 的 WebUI NVS 编辑器在浏览器中修改（命名空间 `ai-keys`）。


* **🩺 Error Details | 错误详情**
* API errors now show the server's message (e.g. `401` invalid key) instead of just a status code.
* API 错误现在显示服务器返回信息（如 `401` Key 无效），不再只显示状态码。


* **📶 WiFi Fallback | WiFi 回退**
* Saved WiFi credentials that fail now fall back to the scan UI instead of retrying silently.
* 已存 WiFi 凭据失效时自动回退到扫描界面，不再静默重试。

---

### 🔑 Getting a Kimi API Key | 获取 Kimi 密钥

Any Kimi membership tier (Andante / Moderato / Allegretto / Allegro) can create API keys — no separate pay-per-token account needed:
任何 Kimi 会员档位（Andante / Moderato / Allegretto / Allegro）均可创建 API Key，无需单独开通按量付费账户：

1. Visit the **Kimi Code Console**: https://www.kimi.com/code/console and sign in. (访问 Kimi Code 控制台并登录)
2. Click **"Create API Key"** and copy it immediately — it is shown only once and starts with `sk-kimi-`. (点击“创建 API Key”并立即复制，仅显示一次，以 `sk-kimi-` 开头)
3. Enter it on the device on first use of the **Kimi K3** engine. (首次使用 Kimi K3 引擎时在设备上输入)

| Key type 密钥类型 | `KIMI_API_URL` | `KIMI_MODEL` |
| --- | --- | --- |
| **Kimi membership key** (`sk-kimi-...`) | `https://api.kimi.com/coding/v1/chat/completions` *(default)* | `k3` *(default)* |
| **Open Platform key** (pay-per-token) | `https://api.moonshot.ai/v1/chat/completions` | `kimi-k3` / `kimi-k2.7-code` |

Notes 注意:
* Model `k3` requires **Moderato or above**; on other tiers set `KIMI_MODEL` to `kimi-for-coding`. (模型 `k3` 需 Moderato 及以上会员，其他档位可将 `KIMI_MODEL` 改为 `kimi-for-coding`)
* Kimi Code keys and Open Platform keys are **not interchangeable** — a mismatch returns `401`. (Kimi Code 密钥与开放平台密钥不通用，混用会返回 `401`)

---

### 📜 Changelog | 更新日志

* **v1.3 (Current)**:
* Added Kimi K3 (Moonshot AI) engine via OpenAI-compatible endpoint.
* Model selector now lists three engines; magenta status bar for Kimi.
* `Del` in model menu clears the highlighted engine's saved API key.
* API errors show the server's message; saved WiFi credentials fall back to scan UI on failure.
* **v1.3 (当前版本)**：新增 Kimi K3（月之暗面）引擎（OpenAI 兼容接口）；模型选择器支持三引擎，Kimi 状态栏为品红色；模型菜单按 Del 可清除已存 Key；API 错误显示服务器详情；WiFi 凭据失效自动回退扫描界面。


**Maintained by: Anakin** *Stay tuned for more updates! 本项目将持续维护，敬请期待更多功能！*
