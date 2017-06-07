
#ifndef _DXAUDIO_H
#define _DXAUDIO_H

#include "dsutil.h"
enum LIST_AUDIO{
	AUDIO_GAME_START,
	AUDIO_PAUSE_MENU,
	AUDIO_MENU_SELECT,
	AUDIO_MEGAMAN_WARP,
	AUDIO_MEGA_BUSTER,
	AUDIO_MEGAMAN_LAND,
	AUDIO_MEGAMAN_DAMAGE,
	AUDIO_MEGAMAN_DEFEATE,
	AUDIO_ENEMY_DAMAGE,
	AUDIO_ENEMY_SHOOT,
	AUDIO_DINK,
	AUDIO_BIG_EYE,
	AUDIO_EXPLOSION,
	AUDIO_GUTSQUAKE,
	AUDIO_THUNDER_BEAM,
	AUDIO_BEAM,
	AUDIO_ROLLING_CUTTER,
	AUDIO_CUTMAN_SNIP,
	AUDIO_ENERGY_FILL,
	AUDIO_1UP,
	AUDIO_BONUS_BALL,
	AUDIO_POINT_TALLY,
	AUDIO_CONVEY_OR_LIFT,
	AUDIO_BOSS_GATE,
	AUDIO_CUTMAN,
	AUDIO_GUTMAN,
	AUDIO_SELECT_STAGE,
	AUDIO_BOSS_BATTLE,
	AUDIO_GAME_OVER,
	AUDIO_COUNT,
};
class MGMAudioManager
{
private:
	static MGMAudioManager* _Instance;
	MGMAudioManager();
	int Init_DirectSound(HWND);

	GSoundManager *dsound;
	GSound** sounds;
public:
	GSound *LoadSound(char *);
	void Play(LIST_AUDIO);
	void LoopSound(LIST_AUDIO);
	void StopSound(LIST_AUDIO);
	static MGMAudioManager* getInstance();
	~MGMAudioManager();

};
#endif

