#include "audioplayer.h"

AudioPlayer::AudioPlayer(QObject *parent) : QObject(parent), soundStopEvent()
{
    qDebug() << "AudioPlayer Constructer invoked";

    m_curr_sound = Q_NULLPTR;
    m_engine = irrklang::createIrrKlangDevice();

    if (!m_engine)
    {
        printf("Could not startup engine\n");
    }

    playlistIndex = 0;
    // TODO: Remove this
    //m_curr_sound = m_engine->play2D("C:/libs/media/ophelia.mp3", true, true);
}

AudioPlayer::~AudioPlayer()
{
    m_curr_sound->drop();
    m_engine->drop();
}

void AudioPlayer::setPlaylist(QStringList playlist)
{
    this->playlist.clear();
    this->playlist = playlist;
    playlistIndex = 0;

    setupMusic();
}

void AudioPlayer::setupMusic()
{
    if(m_curr_sound)
    {
        m_engine->removeAllSoundSources();
        m_curr_sound->drop();
    }

    if(playlist.size() == 0)
    {
        m_curr_sound = Q_NULLPTR;
        return;
    }

    if(playlistIndex >= playlist.size() || playlistIndex < 0)
    {
        qDebug() << "Error playlist size = " << playlist.size() << " and playlistIndex = " << playlistIndex;
        m_curr_sound = Q_NULLPTR;
        return;
    }

    m_curr_sound = m_engine->play2D(playlist.at(playlistIndex).toUtf8(), false, true);
    m_curr_sound->setSoundStopEventReceiver((irrklang::ISoundStopEventReceiver*) &soundStopEvent);

    // TODO: Remove this and use something more efficient
    //m_engine->removeAllSoundSources();
    /*
    for(int i = 1; i < playlist.size(); i++)
    {
        qDebug() << "Adding " + playlist.at(i) + " as a source";
        //QString::toUtf8()
        m_engine->addSoundSourceFromFile(playlist.at(i).toUtf8());
    }
    */

    m_curr_sound->setIsPaused(false);
}

void AudioPlayer::setPlayPosition(double pos)
{
    unsigned long currPos = m_curr_sound->getPlayPosition();
    currPos = (double)currPos * pos;
    m_curr_sound->setPlayPosition(currPos);

    qDebug() << "Audio position changed";
}

double AudioPlayer::getPlayPosition()
{
    unsigned long fullLength = m_curr_sound->getPlayLength();
    unsigned long currPos = m_curr_sound->getPlayPosition();

    return (double)currPos / (double)fullLength;
}

void AudioPlayer::nextSong()
{
    qDebug() << "nextSong invoked";
}

void AudioPlayer::prevSong()
{
    qDebug() << "prevSong invoked";
}

void AudioPlayer::togglePause()
{
    if(m_engine->getSoundSourceCount() == 0)
        return;

    static int x = 1;
    if(x % 2 == 0)
        m_curr_sound->setIsPaused(true);
    else
        m_curr_sound->setIsPaused(false);
    x++;
    qDebug() << "togglePause invoked";
}

bool AudioPlayer::getIsPlaying()
{
    if(!m_curr_sound)
        return false;
    return m_curr_sound->getIsPaused();
}

void AudioPlayer::setIsPlaying(bool isPlaying)
{
    if(!m_curr_sound)
        return;
    m_curr_sound->setIsPaused(isPlaying);
}

void AudioPlayer::stopAudio()
{
    qDebug() << "stopAudio invoked";
}
