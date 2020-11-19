#pragma once

class GlobalSetting
{
private:
	bool gMuteSFX = false;
	bool gMuteBGM = false;
private:
	GlobalSetting() = default;
public:
	static GlobalSetting& GetInstance()
	{
		static GlobalSetting mgr;
		return mgr;
	}

	void MuteSFX() { gMuteSFX = true; }
	void MuteBGM() { gMuteBGM = true; }
	void UnMuteSFX() { gMuteSFX = false; }
	void UnMuteBGM() { gMuteBGM = false; }

	bool IsSFXMute() { return gMuteSFX; }
	bool IsBGMMute() { return gMuteBGM; }
};