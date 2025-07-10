#pragma once

// ゲーム内で使用するサウンドを管理するクラス
class SoundManager
{
public:
    // サウンドファイルを識別するための変数
    // int = bgm      : BGM
    // int = shot     : 発射音
    // int = hit      : 当たり音
    // int = gameOver : ゲームオーバー音
	// int = button   : ボタン音（将来的に追加予定）
	// int = titleBGM : タイトル画面のBGM（将来的に追加予定）
	// int = gameOberBGM : ゲームオーバー時のBGM（将来的に追加予定）
	int m_bgm, m_shot, m_hit, m_gameOver, m_button, m_titleBGM, m_gameOverBGM;

    // サウンドの読み込み処理を行う
    void Load();

    // BGMを再生する
    void PlayBGM();

    // BGMを再生する
    void TitleBGM();

    // BGMの再生を停止する
    void StopBGM();

    // BGMの再生を停止する
    void StopTitleBGM();

    // 発射音を再生する
    void PlayShot();

    // 当たり音を再生する
    void PlayHit();

    // ゲームオーバー音を再生する
    void PlayGameOver();

    // 将来的な改善案として、音の再生を一本化する方法について記述
    // 現在は個別に関数を用意しているが、引数で音を識別して再生する方法を検討中
    // 例えば、引数に int を渡し、switch文や関数ポインタ、std::function、std::map などを使用して管理する方法

    // +α
	// シングルトンパターンを使用して、SoundManagerのインスタンスを一つだけにすることも検討中
	// ファサードパターンを使用して、サウンドの再生処理を簡潔にすることも検討中
};