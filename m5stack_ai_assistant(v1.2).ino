#include <M5Cardputer.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Preferences.h>

Preferences prefs;
M5Canvas canvas(&M5Cardputer.Display); 

// 持久化变量
String ssid = "";
String password = ""; 
String qwenApiKey = "";
String dsApiKey = "";
String userInput = "";
String aiResponse = "Select a model to start";
String lastUserQuery = "";

// 运行时变量
int scrollY = 0;
int cursorLine = 0;
int lastDisplayedBat = -1;
int selectedModelIdx = 0; // 0: Qwen-Turbo, 1: DeepSeek-Chat
const char* modelList[] = {"Qwen-Turbo", "DeepSeek-Chat"};

// --- 启动动画 ---
void playStartupAnimation() {
    canvas.fillSprite(BLACK);
    canvas.setFont(&fonts::efontCN_12);
    uint16_t cyberColor = canvas.color565(255, 0, 60); 
    for (int i = 0; i < 50; i++) {
        canvas.fillSprite(BLACK);
        for (int j = 0; j < 10; j++) { 
            int ry = random(0, 135);
            canvas.fillRect(0, ry, 240, random(1, 3), cyberColor);
        }
        canvas.setTextSize(1.0);
        canvas.setTextColor(DARKGREY);
        canvas.drawString("Anakin v1.2", 160, 118);
        if (i > 10 && i < 40) {
            canvas.setTextColor(WHITE);
            if (i % 2 == 0) canvas.drawCenterString("SYSTEM STARTING...", 120, 55);
        }
        canvas.pushSprite(0, 0);
        delay(80); 
    }
}

// --- 电量显示  ---
void drawBattery() {
    int currentBat = M5Cardputer.Power.getBatteryLevel();
    if (currentBat > 100) currentBat = 100;
    if (lastDisplayedBat == -1 || abs(currentBat - lastDisplayedBat) >= 2) lastDisplayedBat = currentBat;
    canvas.setTextColor(lastDisplayedBat < 20 ? RED : GREEN);
    canvas.setCursor(200, 2);
    canvas.printf("%d%%", lastDisplayedBat);
}

// --- 主 UI 绘制  ---
void updateDisplay(int inputPos) {
    canvas.fillSprite(BLACK);
    canvas.setFont(&fonts::efontCN_12);
    canvas.fillRoundRect(0, 0, 240, 18, 3, selectedModelIdx == 1 ? BLUE : DARKCYAN);
    canvas.setTextColor(WHITE);
    canvas.setCursor(5, 2);
    canvas.print(modelList[selectedModelIdx]);
    drawBattery();

    if (scrollY > 0) scrollY = 0; 
    canvas.setCursor(5, 25 + scrollY);
    canvas.setTextWrap(true);
    if (lastUserQuery.length() > 0) {
        canvas.setTextColor(DARKGREY);
        canvas.print("Me: "); canvas.println(lastUserQuery);
    }
    canvas.setTextColor(WHITE);
    canvas.print("AI: "); canvas.println(aiResponse);

    canvas.fillRect(0, 105, 240, 30, BLACK);
    canvas.drawFastHLine(0, 105, 240, DARKGREY);
    canvas.setCursor(5, 112);
    canvas.setTextColor(GREEN);
    canvas.print("> ");
    canvas.setTextColor(WHITE);
    canvas.print(userInput.substring(0, inputPos));
    canvas.setTextColor(ORANGE); canvas.print("|");
    canvas.setTextColor(WHITE); canvas.print(userInput.substring(inputPos));
    canvas.pushSprite(0, 0);
}

// --- 键盘输入逻辑 ---
String getKbdInput(String title, String initialValue = "") {
    String input = initialValue;
    int pos = input.length();
    while (true) {
        M5Cardputer.update();
        canvas.fillSprite(BLACK);
        canvas.setFont(&fonts::efontCN_12);
        canvas.fillRoundRect(0, 0, 240, 20, 4, BLUE);
        canvas.setTextColor(WHITE);
        canvas.setCursor(5, 2);
        canvas.print(title);
        canvas.drawRoundRect(5, 30, 230, 80, 5, DARKGREY);
        canvas.setCursor(10, 45);
        canvas.print(input.substring(0, pos));
        canvas.setTextColor(CYAN); canvas.print("|");
        canvas.setTextColor(WHITE); canvas.print(input.substring(pos));
        canvas.pushSprite(0, 0);

        if (M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed()) {
            auto s = M5Cardputer.Keyboard.keysState();
            if (s.enter) return input;
            else if (s.del && pos > 0) { input.remove(pos - 1, 1); pos--; }
            else if (s.fn) {
                if (M5Cardputer.Keyboard.isKeyPressed(',')) pos = max(0, pos - 1);
                if (M5Cardputer.Keyboard.isKeyPressed('/')) pos = min((int)input.length(), pos + 1);
            } else {
                for (auto c : s.word) {
                    input = input.substring(0, pos) + c + input.substring(pos);
                    pos++;
                }
            }
        }
        delay(30);
    }
}

// --- 模型选择界面 (仿 WiFi 逻辑新增) ---
void selectModelUI() {
    while (true) {
        M5Cardputer.update();
        canvas.fillSprite(BLACK);
        canvas.setFont(&fonts::efontCN_12);
        canvas.fillRoundRect(0, 0, 240, 20, 4, DARKGREY);
        canvas.setCursor(5, 2);
        canvas.print("Select AI Engine");

        for (int i = 0; i < 2; i++) {
            int y = 40 + (i * 25);
            if (i == selectedModelIdx) canvas.fillRoundRect(5, y - 2, 230, 20, 3, DARKGREEN);
            canvas.setCursor(15, y + 2);
            canvas.setTextColor(WHITE);
            canvas.print(modelList[i]);
        }
        canvas.pushSprite(0, 0);

        if (M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed()) {
            if (M5Cardputer.Keyboard.isKeyPressed(';')) { // 上
                if (selectedModelIdx > 0) selectedModelIdx--;
            } else if (M5Cardputer.Keyboard.isKeyPressed('.')) { // 下
                if (selectedModelIdx < 1) selectedModelIdx++;
            } else if (M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER)) {
                // 检查选定模型的 Key
                prefs.begin("ai-keys", false);
                if (selectedModelIdx == 0) {
                    qwenApiKey = prefs.getString("qwen_key", "");
                    if (qwenApiKey == "") {
                        qwenApiKey = getKbdInput("Enter Qwen API Key");
                        prefs.putString("qwen_key", qwenApiKey);
                    }
                } else {
                    dsApiKey = prefs.getString("ds_key", "");
                    if (dsApiKey == "") {
                        dsApiKey = getKbdInput("Enter DeepSeek API Key");
                        prefs.putString("ds_key", dsApiKey);
                    }
                }
                prefs.end();
                return;
            }
        }
        delay(10);
    }
}

// --- WiFi 扫描与连接 ---
bool scanAndConnect() {
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    int n = WiFi.scanNetworks();
    int selected = 0, offset = 0;
    const int pageSize = 5;

    while (true) {
        M5Cardputer.update();
        canvas.fillSprite(BLACK);
        canvas.setFont(&fonts::efontCN_12);
        canvas.fillRoundRect(0, 0, 240, 20, 4, PURPLE);
        canvas.setCursor(5, 2);
        canvas.printf("Select WiFi (%d/%d)", selected + 1, n);
        for (int i = 0; i < pageSize; i++) {
            int cur = offset + i;
            if (cur >= n) break;
            int y = 30 + (i * 20);
            if (cur == selected) canvas.fillRoundRect(5, y - 2, 230, 18, 3, DARKGREEN);
            canvas.setCursor(10, y + 2);
            canvas.setTextColor(WHITE);
            canvas.print(WiFi.SSID(cur));
        }
        canvas.pushSprite(0, 0);
        if (M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed()) {
            if (M5Cardputer.Keyboard.isKeyPressed(';')) { 
                if (selected > 0) { selected--; if (selected < offset) offset = selected; }
            } else if (M5Cardputer.Keyboard.isKeyPressed('.')) { 
                if (selected < n - 1) { selected++; if (selected >= offset + pageSize) offset = selected - pageSize + 1; }
            } else if (M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER)) {
                ssid = WiFi.SSID(selected);
                password = getKbdInput("Password for: " + ssid);
                canvas.fillSprite(BLACK);
                canvas.drawCenterString("Connecting to " + ssid + "...", 120, 60);
                canvas.pushSprite(0, 0);
                WiFi.begin(ssid.c_str(), password.c_str());
                int ms = 0;
                while (WiFi.status() != WL_CONNECTED && ms < 10000) { delay(500); ms += 500; }
                if (WiFi.status() == WL_CONNECTED) return true;
                else WiFi.disconnect();
            }
        }
        delay(10);
    }
}

// --- API接口调用 (打通 DeepSeek 与 Qwen) ---
void callAPI() {
    if (userInput.length() == 0) return;
    lastUserQuery = userInput;
    String savedQuery = userInput;
    userInput = ""; cursorLine = 0;
    aiResponse = "Thinking...";
    updateDisplay(0);

    HTTPClient http;
    String url, currentKey;
    if (selectedModelIdx == 0) { // Qwen
        url = "https://dashscope.aliyuncs.com/api/v1/services/aigc/text-generation/generation";
        currentKey = qwenApiKey;
    } else { // DeepSeek
        url = "https://api.deepseek.com/chat/completions";
        currentKey = dsApiKey;
    }

    http.begin(url);
    http.setTimeout(30000); 
    http.addHeader("Authorization", "Bearer " + currentKey);
    http.addHeader("Content-Type", "application/json");
    
    JsonDocument doc;
    if (selectedModelIdx == 0) { // Qwen 格式
        doc["model"] = "qwen-turbo";
        doc["input"]["messages"][0]["role"] = "user";
        doc["input"]["messages"][0]["content"] = savedQuery;
        doc["parameters"]["result_format"] = "message";
    } else { // DeepSeek/OpenAI 格式
        doc["model"] = "deepseek-chat";
        JsonArray msgs = doc["messages"].to<JsonArray>();
        JsonObject m = msgs.add<JsonObject>();
        m["role"] = "user";
        m["content"] = savedQuery;
    }
    
    String body;
    serializeJson(doc, body);
    int code = http.POST(body);
    
    if (code == 200) {
        JsonDocument resDoc;
        deserializeJson(resDoc, http.getString());
        if (selectedModelIdx == 0)
            aiResponse = resDoc["output"]["choices"][0]["message"]["content"].as<String>();
        else
            aiResponse = resDoc["choices"][0]["message"]["content"].as<String>();
    } else {
        aiResponse = "Error: " + String(code);
    }
    http.end();
    updateDisplay(0);
}

// --- 主函数 ---
void setup() {
    auto cfg = M5.config();
    M5Cardputer.begin(cfg, true);
    canvas.createSprite(240, 135);
    playStartupAnimation(); 

    prefs.begin("qwen-config", false);
    ssid = prefs.getString("ssid", "");
    password = prefs.getString("password", "");
    prefs.end();

    if (ssid == "") {
        while(!scanAndConnect()); 
        prefs.begin("qwen-config", false);
        prefs.putString("ssid", ssid);
        prefs.putString("password", password);
        prefs.end();
    } else {
        WiFi.begin(ssid.c_str(), password.c_str());
    }

    // WiFi连上后，弹出模型选择界面
    selectModelUI();
    updateDisplay(0);
}

void loop() {
    M5Cardputer.update();
    
    // G0 重置逻辑 
    if (digitalRead(0) == LOW) {
        unsigned long startTime = millis();
        while (digitalRead(0) == LOW) {
            if (millis() - startTime > 2000) {
                canvas.fillSprite(BLACK);
                canvas.drawCenterString("RESETTING...", 120, 60);
                canvas.pushSprite(0, 0);
                prefs.begin("qwen-config", false); prefs.clear(); prefs.end();
                prefs.begin("ai-keys", false); prefs.clear(); prefs.end();
                delay(1000);
                ESP.restart();
            }
        }
    }

    // 键盘逻辑
    if (M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed()) {
        auto s = M5Cardputer.Keyboard.keysState();
        if (s.fn) {
            if (M5Cardputer.Keyboard.isKeyPressed(';')) { scrollY += 20; if (scrollY > 0) scrollY = 0; }
            if (M5Cardputer.Keyboard.isKeyPressed('.')) scrollY -= 20;
            if (M5Cardputer.Keyboard.isKeyPressed(',')) cursorLine = max(0, cursorLine - 1);
            if (M5Cardputer.Keyboard.isKeyPressed('/')) cursorLine = min((int)userInput.length(), cursorLine + 1);
            // 新增快捷键：Fn + M 重新选择模型
            if (M5Cardputer.Keyboard.isKeyPressed('m')) { selectModelUI(); aiResponse = "Switched Model"; }
        } 
        else if (s.enter) { 
            callAPI();
        } 
        else if (s.del) {
            if (cursorLine > 0) { userInput.remove(cursorLine - 1, 1); cursorLine--; }
        } 
        else {
            for (auto c : s.word) {
                userInput = userInput.substring(0, cursorLine) + c + userInput.substring(cursorLine);
                cursorLine++;
            }
        }
        updateDisplay(cursorLine);
    }
    delay(10);
}
