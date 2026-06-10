# LineTrace-AGV-Pico
Line trace AGV using Raspberry Pi Pico 2W + FreeRTOS


Raspberry Pi Pico 2W + FreeRTOS を用いたライントレースAGVの開発プロジェクト。

## 概要

- **マイコン**: Raspberry Pi Pico 2W（RP2350）
- **OS**: FreeRTOS
- **センサー**: TCRT5000 × 3（左・中央・右）
- **モーター制御**: DRV8833 デュアルモータードライバ
- **制御方式**: ON/OFF制御 → PID制御（段階的に高度化）

## システム構成

## FreeRTOSタスク構成

| タスク | 優先度 | 役割 |
|---|---|---|
| sensor_task | 高 | ラインセンサー読み取り・キューへ送信 |
| control_task | 高 | PID演算・PWM出力 |
| state_task | 中 | 走行状態管理（直進・右折・左折・停止） |
| debug_task | 低 | UARTでセンサー値・速度をPC出力 |

## 開発環境

- VS Code + Raspberry Pi Pico 拡張機能
- Pico SDK v2.x
- ARM GCC
- FreeRTOS

## ビルド方法

```bash
# リポジトリをクローン
git clone https://github.com/koruku315/LineTrace-AGV-Pico.git
cd LineTrace-AGV-Pico

# ビルド
# VS Code の「Compile Project」を実行

