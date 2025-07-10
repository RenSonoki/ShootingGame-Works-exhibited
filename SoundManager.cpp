#include "SoundManager.h"
#include "DxLib.h"

// サウンドファイルを読み込む
void SoundManager::Load()
{
    m_bgm = LoadSoundMem(_T("Assets/SE/play_bgm.mp3"));
    m_shot = LoadSoundMem(_T("fire.wav"));
    m_hit = LoadSoundMem(_T("hit.wav"));
    m_gameOver = LoadSoundMem(_T("gameover.wav"));
	m_button = LoadSoundMem(_T("button.wav"));
	m_titleBGM = LoadSoundMem(_T("Assets/SE/title_bgm.mp3"));
	m_gameOverBGM = LoadSoundMem(_T("gameover_bgm.mp3"));
}

// PlaySoundMemはDXライブラリの関数で、サウンドを再生するために使用されます。

void SoundManager::PlayBGM()
{
    PlaySoundMem(m_bgm, DX_PLAYTYPE_LOOP);
}

void SoundManager::TitleBGM()
{
    PlaySoundMem(m_titleBGM, DX_PLAYTYPE_LOOP);
}

void SoundManager::StopBGM()
{
    StopSoundMem(m_bgm);
}

void SoundManager::StopTitleBGM()
{
    StopSoundMem(m_titleBGM);
}

void SoundManager::PlayShot()
{
    PlaySoundMem(m_shot, DX_PLAYTYPE_BACK);
}

void SoundManager::PlayHit()
{
    PlaySoundMem(m_hit, DX_PLAYTYPE_BACK);
}

void SoundManager::PlayGameOver()
{
    PlaySoundMem(m_gameOver, DX_PLAYTYPE_BACK);
}