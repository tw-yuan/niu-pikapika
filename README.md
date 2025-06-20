# niu-pika 皮卡丘排球

這是一個簡單的雙人對戰排球遊戲，由 C++ 和 [Easy2D](https://easy2d.cn/) 遊戲引擎製成。

## 遊戲玩法

兩位玩家分別控制一隻皮卡丘，目標是將精靈球擊至對方的場地使其落地得分。

### 操作方式

- **左方玩家 (皮卡丘)**
    - `A` 鍵: 向左移動
    - `D` 鍵: 向右移動
    - `W` 鍵: 跳躍

- **右方玩家 (皮卡丘)**
    - `←` (左箭頭): 向左移動
    - `→` (右箭頭): 向右移動
    - `↑` (上箭頭): 跳躍

## 遊戲截圖

![遊戲截圖](https://raw.githubusercontent.com/tw-yuan/niu-pikapika/refs/heads/main/resource/demo.gif) 

## 技術框架

- **語言**: C++
- **遊戲引擎**: Easy2D

## 如何編譯與執行
本專案使用 Visual Studio 進行開發。

1.  請先安裝 Visual Studio 以及 C++ 遊戲開發相關的工作負載。
2.  請確保您的環境中已正確設定 Easy2D 函式庫。
3.  使用 Visual Studio 開啟 `niu-pika.vcxproj` 專案檔案。
4.  編譯專案並執行。

## 專案結構

- `main.cpp`: 遊戲主要邏輯。
- `resource/`: 存放遊戲所需的圖片等資源檔案。
- `*.vcxproj`: Visual Studio 專案設定檔。 