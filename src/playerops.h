
#ifndef PLAYEROPS_H
#define PLAYEROPS_H

#include <dirent.h>
#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include "player.h"
#include "songloader.h"
#include "settings.h"
#include "soundcommon.h"

#ifndef CLOCK_MONOTONIC
#define CLOCK_MONOTONIC 1
#endif

#ifndef MAXPATHLEN
#define MAXPATHLEN 4096
#endif

typedef struct
{
        char filePath[MAXPATHLEN];
        SongData *songdataA;
        SongData *songdataB;
        bool loadA;
        bool loadingFirstDecoder;
        pthread_mutex_t mutex;
} LoadingThreadData;

extern GDBusConnection *connection;
extern LoadingThreadData loadingdata;
extern double elapsedSeconds;
extern double pauseSeconds;
extern double totalPauseSeconds;
extern struct timespec pause_time;
extern volatile bool loadedNextSong;
extern bool playlistNeedsUpdate;
extern bool nextSongNeedsRebuilding;
extern bool enqueuedNeedsUpdate;
extern bool waitingForPlaylist;
extern bool waitingForNext;
extern bool usingSongDataA;
extern Node *nextSong;
extern Node *songToStartFrom;
extern int lastPlayedId;
extern bool playingMainPlaylist;
extern bool songHasErrors;
extern bool doQuit;
extern bool loadingFailed;
extern volatile bool clearingErrors;
extern volatile bool songLoading;
extern struct timespec start_time;
extern bool skipping;
extern bool skipOutOfOrder;
extern Node *tryNextSong;
extern struct timespec lastInputTime;
extern struct timespec lastPlaylistChangeTime;
extern bool skipFromStopped;
extern bool doNotifyMPRISSwitched;

extern UserData userData;

SongData *getCurrentSongData(void);

void rebuildAndUpdatePlaylist();

Node *getNextSong();

void handleRemove();

void enqueueSongs(FileSystemEntry *entry);

void updateLastSongSwitchTime(void);

void updateLastInputTime(void);

void playbackPause(struct timespec *pause_time);

void playbackPlay(double *totalPauseSeconds, double *pauseSeconds);

void togglePause(double *totalPauseSeconds, double *pauseSeconds, struct timespec *pause_time);

void stop();

void toggleRepeat(void);

void toggleShuffle(void);

void addToSpecialPlaylist(void);

void toggleBlocks(AppSettings *settings);

void toggleColors(AppSettings *settings);

void toggleVisualizer(AppSettings *settings);

void quit(void);

void calcElapsedTime(void);

Node *getSongByNumber(PlayList *playlist, int songNumber);

void skipToNextSong(void);

void skipToPrevSong(void);

void skipToSong(int id, bool startPlaying);

void seekForward(void);

void seekBack(void);

void skipToNumberedSong(int songNumber);

void skipToLastSong(void);

void loadSong(Node *song, LoadingThreadData *loadingdata);

void loadNext(LoadingThreadData *loadingdata);

int loadFirst(Node *song);

void flushSeek(void);

Node *findSelectedEntryById(PlayList *playlist, int id);

void emitSeekedSignal(double newPositionSeconds);

void rebuildNextSong(Node *song);

void updateLibrary(char *path);

void askIfCacheLibrary();

void unloadSongA();

void unloadSongB();

void unloadPreviousSong();

void createLibrary(AppSettings *settings);

void loadNextSong();

void setCurrentSongToNext();

void finishLoading();

void resetTimeCount();

bool setPosition(gint64 newPosition);

bool seekPosition(gint64 offset);

void silentSwitchToNext(bool loadSong);

void reshufflePlaylist();

bool determineCurrentSongData(SongData **currentSongData);

void updateLibraryIfChangedDetected();

#endif
