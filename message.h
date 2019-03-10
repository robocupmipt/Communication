#ifndef MESSAGE_H
#define MESSAGE_H

struct RoboCupGameControlData
{
  char header[4];               // header to identify the structure
  uint16_t version;             // version of the data structure
  uint8_t packetNumber;         // number incremented with each packet sent (with wraparound)
  uint8_t playersPerTeam;       // the number of players on a team
  uint8_t competitionPhase;     // phase of the competition (COMPETITION_PHASE_ROUNDROBIN, COMPETITION_PHASE_PLAYOFF)
  uint8_t competitionType;      // type of the competition (COMPETITION_TYPE_NORMAL, COMPETITION_TYPE_MIXEDTEAM, COMPETITION_TYPE_GENERAL_PENALTY_KICK)
  uint8_t gamePhase;            // phase of the game (GAME_PHASE_NORMAL, GAME_PHASE_PENALTYSHOOT, etc)
  uint8_t state;                // state of the game (STATE_READY, STATE_PLAYING, etc)
  uint8_t setPlay;              // active set play (SET_PLAY_NONE, SET_PLAY_GOAL_FREE_KICK, etc)
  uint8_t firstHalf;            // 1 = game in first half, 0 otherwise
  uint8_t kickingTeam;          // the team number of the next team to kick off, free kick, DROPBALL etc.
  uint8_t dropInTeam;           // number of team that caused last drop in
  uint16_t dropInTime;          // number of seconds passed since the last drop in. -1 (0xffff) before first dropin
  uint16_t secsRemaining;       // estimate of number of seconds remaining in the half
};

#endif /* MESSAGE_H */
