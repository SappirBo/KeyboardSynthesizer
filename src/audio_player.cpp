#include "audio_player.hpp"

AudioPlayer::PortAudioPlayer::PortAudioPlayer()
    : m_callback(nullptr), m_userData(nullptr) {}

AudioPlayer::PortAudioPlayer::PortAudioPlayer(PaStreamCallback *callback,
                                              void *userData)
    : m_callback(callback), m_userData(userData) {}

AudioPlayer::PortAudioPlayer::~PortAudioPlayer() {}

void AudioPlayer::PortAudioPlayer::Initialize() {
  PaError err = Pa_Initialize();
  if (err != paNoError) {
    std::cout << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
    exit(0);
  }
};

void AudioPlayer::PortAudioPlayer::set_audio_callback(
    PaStreamCallback *callback, void *userData) {
  m_callback = callback;
  m_userData = userData;
}

void AudioPlayer::PortAudioPlayer::set_output_params(uint32_t channels) {
  m_outputParameters.device =
      Pa_GetDefaultOutputDevice(); /* default output device */
  if (m_outputParameters.device == paNoDevice) {
    fprintf(stderr, "Error: No default output device.\n");
    exit(0);
  }
  m_outputParameters.channelCount = 2; /* stereo output */
  m_outputParameters.sampleFormat =
      paFloat32; /* 32 bit floating point output */
  m_outputParameters.suggestedLatency =
      Pa_GetDeviceInfo(m_outputParameters.device)->defaultLowOutputLatency;
  m_outputParameters.hostApiSpecificStreamInfo = NULL;
}

void AudioPlayer::PortAudioPlayer::open_stream() {
  PaError err = Pa_OpenStream(&m_stream, NULL, /* no input */
                              &m_outputParameters, AudioSettings::SAMPLE_RATE,
                              AudioSettings::FRAME_BUFFER_SIZE, paClipOff,
                              m_callback, m_userData);
  if (err != paNoError) {
    std::cout << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
    exit(0);
  }
}

void AudioPlayer::PortAudioPlayer::set_stream_finish() {
  PaError err = Pa_SetStreamFinishedCallback(m_stream, &StreamFinished);
  if (err != paNoError) {
    std::cout << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
    exit(0);
  }
}

bool AudioPlayer::PortAudioPlayer::is_stream_active() {
  return Pa_IsStreamActive(m_stream);
}

void AudioPlayer::PortAudioPlayer::stop_stream() {
  PaError err = Pa_StopStream(m_stream);
  if (err != paNoError) {
    std::cout << "PortAudio StopStream error: " << Pa_GetErrorText(err)
              << std::endl;
    exit(0);
  }
}

void AudioPlayer::PortAudioPlayer::start_stream() {
  PaError err = Pa_StartStream(m_stream);
  if (err != paNoError) {
    std::cout << "PortAudio StartStream error: " << Pa_GetErrorText(err)
              << std::endl;
    exit(0);
  }
}

void AudioPlayer::PortAudioPlayer::close_stream() {
  PaError err = Pa_CloseStream(m_stream);
  if (err != paNoError) {
    std::cout << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
    exit(0);
  }
}

void AudioPlayer::PortAudioPlayer::terminate_stream() {
  PaError err = Pa_Terminate();
  if (err != paNoError) {
    std::cout << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
    exit(0);
  }
}