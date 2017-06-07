#include "MGMAudioManager.h"
#include"MGMForm.h"
MGMAudioManager* MGMAudioManager::_Instance = 0;
MGMAudioManager::MGMAudioManager(){
	Init_DirectSound(MGMForm::getInstance()->getHandleWindow());
	sounds = new GSound*[AUDIO_COUNT];
	sounds[AUDIO_GAME_START] = LoadSound("Data\\Audio\\01 - GameStart.wav");
	sounds[AUDIO_PAUSE_MENU] = LoadSound("Data\\Audio\\02 - PauseMenu.wav");
	sounds[AUDIO_ENEMY_SHOOT] = LoadSound("Data\\Audio\\10 - EnemyShoot.wav");
	sounds[AUDIO_MEGA_BUSTER] = LoadSound("Data\\Audio\\05 - MegaBuster.wav");
	sounds[AUDIO_MEGAMAN_DAMAGE] = LoadSound("Data\\Audio\\07 - MegamanDamage.wav");
	sounds[AUDIO_ENEMY_DAMAGE] = LoadSound("Data\\Audio\\09 - EnemyDamage.wav");
	sounds[AUDIO_BONUS_BALL] = LoadSound("Data\\Audio\\26 - BonusBall.wav");
	sounds[AUDIO_1UP] = LoadSound("Data\\Audio\\25 - 1up.wav");
	sounds[AUDIO_CUTMAN] = LoadSound("Data\\Audio\\Music_CutMan.wav");
	sounds[AUDIO_GUTMAN] = LoadSound("Data\\Audio\\Music_GutMan.wav");
	sounds[AUDIO_MEGAMAN_LAND] = LoadSound("Data\\Audio\\06 - MegamanLand.wav");
	sounds[AUDIO_MEGAMAN_DEFEATE] = LoadSound("Data\\Audio\\08 - MegamanDefeat.wav");
	sounds[AUDIO_ENEMY_DAMAGE] = LoadSound("Data\\Audio\\09 - EnemyDamage.wav");
	sounds[AUDIO_DINK] = LoadSound("Data\\Audio\\11 - Dink.wav");
	sounds[AUDIO_BIG_EYE] = LoadSound("Data\\Audio\\12 - BigEye.wav");
	sounds[AUDIO_BOSS_GATE] = LoadSound("Data\\Audio\\30 - BossGate.wav");
	sounds[AUDIO_CONVEY_OR_LIFT] = LoadSound("Data\\Audio\\29 - ConveyorLift.wav");
	sounds[AUDIO_GUTSQUAKE] = LoadSound("Data\\Audio\\15 - GutsQuake.wav");
	sounds[AUDIO_SELECT_STAGE] = LoadSound("Data\\Audio\\Stage Select.wav");
	sounds[AUDIO_MENU_SELECT] = LoadSound("Data\\Audio\\03 - MenuSelect.wav");
	sounds[AUDIO_ENERGY_FILL] = LoadSound("Data\\Audio\\24 - EnergyFill.wav");
	sounds[AUDIO_BOSS_BATTLE] = LoadSound("Data\\Audio\\Boss Battle.wav");
	sounds[AUDIO_GAME_OVER] = LoadSound("Data\\Audio\\Game Over.wav");
}
MGMAudioManager* MGMAudioManager::getInstance(){
	if (_Instance == NULL){
		_Instance = new MGMAudioManager();
	}
	return _Instance;
}
int MGMAudioManager::Init_DirectSound(HWND hwnd)
{
    HRESULT result;

    //create DirectSound manager object
    dsound = new GSoundManager();

    //initialize DirectSound
    result = dsound->Initialize(hwnd, DSSCL_PRIORITY);
    if (result != DS_OK)
    {
		
		MessageBox(hwnd, "[FAILED] Can not init directx sound", "Loi", MB_ICONERROR);
		return 0;
	}

    //set the primary buffer format
    result = dsound->SetPrimaryBufferFormat(2, 22050, 16);
    if (result != DS_OK)
    {
		
		MessageBox(hwnd, "[FAILED] Can not set the primary buffer", "Loi", MB_ICONERROR);
		 return 0;
	}
    //return success
	//GLTrace("Directx Sound has been success init");
	//MessageBox(hwnd, "Directx Sound has been success init", "Loi", MB_ICONERROR);
    return 1;
}

GSound* MGMAudioManager::LoadSound(char *filename)
{
    HRESULT result;

    //create local reference to wave data
    GSound *wave;

    //attempt to load the wave file
    result = dsound->Create(&wave, filename);
    if (result != DS_OK)
    {
		MessageBox(MGMForm::getInstance()->getHandleWindow(), "[FAILED] Can not set the primary buffer", "Loi", MB_ICONERROR);
		 return NULL;
	}
	//GLTrace("Sound file has been loaded");
	//MessageBox(hwnd, "[FAILED] Can not set the primary buffer", "Loi", MB_ICONERROR);
    //return the wave
    return wave;
}

void MGMAudioManager::Play(LIST_AUDIO item){
	sounds[item]->Play();
}


void MGMAudioManager::LoopSound(LIST_AUDIO item)
{
	sounds[item]->Play(0, DSBPLAY_LOOPING);
}

void MGMAudioManager::StopSound(LIST_AUDIO item)
{
	sounds[item]->Stop();

}
MGMAudioManager::~MGMAudioManager(){
	if (sounds != NULL){
		for (int i = 0; i < AUDIO_COUNT; i++){
			delete sounds[i];
		}
		delete []sounds;
	}
}
