#pragma once
#include "DxLib.h"
#include <windows.h> // POINT 構造体用

// 仮想画面の描画と座標変換を管理するユーティリティクラス
// このクラスは、仮想画面のサイズを設定し、実際の画面にスケーリングして描画する機能
// インスタンス化を禁止するのは、ユーティリティクラスとしての性質を保つためです。
// ユーティリティクラスは通常、静的メソッドのみを提供し、インスタンス化する必要がないため。
// ユーティリティクラスとは、特定の機能を提供するために設計されており、状態を持たないことが一般的。
class VirtualScreenManager
{
private:
    VirtualScreenManager() = delete; // インスタンス化禁止

	static int s_virtualWidth;          // 仮想画面の幅
	static int s_virtualHeight;         // 仮想画面の高さ
	static int s_virtualScreenHandle;   // 仮想画面のハンドル

public:
    // 仮想画面の初期化
    static void Init(int virtualW, int virtualH);

    // 仮想画面に描画開始（クリア含む）
    static void BeginDraw();

    // 仮想画面を実画面にスケーリング描画
    static void EndDraw();

    // 仮想画面の幅・高さを取得
    static int GetVirtualWidth();
    static int GetVirtualHeight();

    // マウス座標を仮想画面座標に変換
    static POINT ConvertMousePositionToVirtual();
};