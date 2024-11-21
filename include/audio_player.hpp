#include "audio_settings.hpp"
#include "pa_data.hpp"
#include <cmath>
#include <iostream>
#include <portaudio.h>

namespace AudioPlayer {

static void StreamFinished(void *userData) {
  // paData *data = (paData *) userData;
  // printf( "Stream Completed: %s\n", data->message );
}

class PortAudioPlayer {
private:
  PaStreamCallback *m_callback;
  PaStreamParameters m_outputParameters;
  PaStream *m_stream;
  void *m_userData;

public:
  PortAudioPlayer();
  PortAudioPlayer(PaStreamCallback *callback, void *userData);
  ~PortAudioPlayer();

  void set_audio_callback(PaStreamCallback *callback, void *userData);

  void Initialize();
  void set_output_params(uint32_t channels);
  void open_stream();
  void set_stream_finish();
  bool is_stream_active();
  void stop_stream();
  void start_stream();
  void close_stream();
  void terminate_stream();
};

} // namespace AudioPlayer