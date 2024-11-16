#include <portaudio.h>
#include <iostream>
#include <cmath>
#include "pa_data.hpp"
#include "audio_settings.hpp"

namespace AudioPlayer{
    static int paCallback( const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer,
                            const PaStreamCallbackTimeInfo* timeInfo,PaStreamCallbackFlags statusFlags, void *userData)
    {
        paData *data = (paData*)userData;
        float *out = (float*)outputBuffer;
        unsigned long i;

        (void) timeInfo; /* Prevent unused variable warnings. */
        (void) statusFlags;
        (void) inputBuffer;

        for( i=0; i<framesPerBuffer; i++ )
        {
            size_t left_phase_index{static_cast<size_t>(data->left_phase)};
            size_t right_phase_index{static_cast<size_t>(data->right_phase)};

            *out++ = data->wave_table[left_phase_index];  /* left */
            *out++ = data->wave_table[right_phase_index];  /* right */
            data->left_phase += data->phaseIncrement;
            if( data->left_phase >= AudioSettings::TABLE_SIZE ) data->left_phase -= AudioSettings::TABLE_SIZE;
            data->right_phase += data->phaseIncrement; /* higher pitch so we can distinguish left and right. */
            if( data->right_phase >= AudioSettings::TABLE_SIZE ) data->right_phase -= AudioSettings::TABLE_SIZE;
        }

        return paContinue;
    }

    static void StreamFinished( void* userData )
    {
        // paData *data = (paData *) userData;
        // printf( "Stream Completed: %s\n", data->message );
    }   

    class PortAudioPlayer
    {
    private:
        PaStreamParameters m_outputParameters;
        PaStream *m_stream;

    public:
        PortAudioPlayer();
        ~PortAudioPlayer();

        void Initialize();
        void set_output_params(uint32_t channels);
        void open_stream(paData &data);
        void set_stream_finish();
        bool is_stream_active();
        void stop_stream();
        void start_stream();
        void close_stream();
        void terminate_stream();
    };

}