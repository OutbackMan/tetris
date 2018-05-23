#ifndef __core_game_players_h__
#define __core_game_players_h__

typedef struct {
	size_t num;
	G_GamePlayer* players;
} G_GamePlayers;

typedef struct {
	bool has_control;
	bool is_computer_controlled;		
	bool is_energising;
	float energy_level;
} G_GamePlayer;

#endif
