/**
 * @file songloader.h
 * @brief Song loading and preparation routines.
 *
 * Responsible for loading song data from file
 */

#include <stdbool.h>
#include "common/appstate.h"

#ifndef MAXPATHLEN
#define MAXPATHLEN 4096
#endif

#ifndef KEYVALUEPAIR_STRUCT
#define KEYVALUEPAIR_STRUCT

typedef struct
{
        char *key;
        char *value;
} KeyValuePair;

#endif

#ifndef TAGSETTINGS_STRUCT
#define TAGSETTINGS_STRUCT

#define METADATA_MAX_LENGTH 256

        typedef struct
        {
                char title[METADATA_MAX_LENGTH];
                char artist[METADATA_MAX_LENGTH];
                char album_artist[METADATA_MAX_LENGTH];
                char album[METADATA_MAX_LENGTH];
                char date[METADATA_MAX_LENGTH];
                double replaygainTrack;
                double replaygainAlbum;
        } TagSettings;

#endif

#ifndef SONGDATA_STRUCT
#define SONGDATA_STRUCT

typedef struct
{
        gchar *trackId;
        char filePath[MAXPATHLEN];
        char coverArtPath[MAXPATHLEN];
        unsigned char red;
        unsigned char green;
        unsigned char blue;
        TagSettings *metadata;
        unsigned char *cover;
        int avgBitRate;
        int coverWidth;
        int coverHeight;
        double duration;
        bool hasErrors;
} SongData;

#endif

SongData *loadSongData(char *filePath);

void unloadSongData(SongData **songdata);
