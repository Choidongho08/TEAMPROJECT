#pragma once
#include <Windows.h>
#include <string>

// open
bool OpenMciDevice(LPCWSTR deviceType, LPCWSTR name, UINT& deviceId);

// close
void CloseMciDevice(UINT& deviceId);

// play
void PlayMciDevice(UINT deviceId, bool repeat = false);
enum class SOUNDID
{
    BGM, EXPLOSION, END
};

struct SoundEntry
{
    //LPCWSTR path;     // 파일 경로
    std::wstring path; // 파일 경로
    int     volume;  // 볼륨 (0~1000)  
    UINT    deviceId; // MCI 장치 ID (초기값 0)
};
// 초기화
bool InitAllSounds();
// 재생
void PlaySoundID(SOUNDID _id, bool _repeat = false);
// 릴리즈 
void ReleaseAllSounds();