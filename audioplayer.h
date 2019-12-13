#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QObject>
#include <QDebug>
#include <QLinkedList>
#include <QTimer>

// TODO: Part of a hack, remove
#include <QFile>
#include <QFileInfo>
#include <QDir>

#include <fileref.h>
#include <tag.h>
#include <mpeg/id3v2/id3v2tag.h>
#include <mpeg/id3v2/id3v2header.h>
#include <mpeg/id3v2/id3v2frame.h>
#include <mpeg/mpegfile.h>
#include <mpeg/id3v2/frames/attachedpictureframe.h>

// irrKlangIncludes
#include "./inc/irrKlang.h"

#include "soundstopevent.h"
#include "audiofile.h"
#include "textparser.h"

class AudioPlayer : public QObject
{
    Q_OBJECT

    Q_PROPERTY(double playPosition READ getPlayPosition WRITE setPlayPosition NOTIFY playPositionChanged)
    Q_PROPERTY(bool isPlaying READ getIsPlaying WRITE setIsPlaying NOTIFY isPlayingChanged)
    Q_PROPERTY(AudioFile * currentAudio READ getCurrentAudio NOTIFY songChanged)
    Q_PROPERTY(int currentSongIndex READ getCurrentSongIndex NOTIFY currentSongIndexChanged)
public:
    explicit AudioPlayer(QObject *parent = nullptr);
    ~AudioPlayer();
    Q_INVOKABLE void nextSong(void);
    Q_INVOKABLE void prevSong(void);
    Q_INVOKABLE bool getIsPlaying(void);
    Q_INVOKABLE void setIsPlaying(bool pIsPlaying);
    Q_INVOKABLE void setPlayPosition(double pPos);
    Q_INVOKABLE double getPlayPosition(void);
    Q_INVOKABLE void togglePause(void);
    Q_INVOKABLE void stopAudio(void);
    void playMusic(void);
    void updateAudioPosition();
    void setCurrentAudio(QString path);
    AudioFile* getCurrentAudio();

    int getCurrentSongIndex();
signals:
    void playPositionChanged(double);
    void isPlayingChanged(bool);
    void songChanged();
    void currentSongIndexChanged(int);
public slots:
    void setPlaylist(QStringList playlist);
private:
    static QString getAudioTitle(QFile audioFile);
    static QString getAudioArtist(QFile audioFile);
    static QString getAudioAlbum(QFile audioFile);
    static void getAudioArt(QFile audioFile);
    static QString loadAlbumArtToFileIfExists(QString filePath, QString successPath, QString failurePath);

    irrklang::ISoundEngine* mEngine;
    irrklang::ISound* mCurrentSound;
    QStringList mPlaylist;
    int mPlaylistIndex;
    SoundStopEvent mSoundStopEvent;
    QTimer* mPositionTimer;
    AudioFile mCurrentAudio;
};

#endif // AUDIOPLAYER_H
