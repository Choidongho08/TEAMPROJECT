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
    //LPCWSTR path;     // ���� ���
    std::wstring path; // ���� ���
    int     volume;  // ���� (0~1000)  
    UINT    deviceId; // MCI ��ġ ID (�ʱⰪ 0)
};
// �ʱ�ȭ
bool InitAllSounds();
// ���
void PlaySoundID(SOUNDID _id, bool _repeat = false);
// ������ 
void ReleaseAllSounds();