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
* [ ] Integration of more AI APIs (DeepSeek, GPT-4o, Claude).
* [ ] Voice-to-Text capabilities using the onboard microphone.
* [ ] UI themes and customization options.

**Maintained by: Anakin** *Stay tuned for more updates! 本项目将持续维护，敬请期待更多功能！*
