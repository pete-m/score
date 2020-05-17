#include "AudioPreviewExecutor.hpp"

#include <score/tools/Debug.hpp>

#include <ossia/audio/audio_protocol.hpp>
namespace Audio
{

AudioPreviewExecutor& AudioPreviewExecutor::instance()
{
  SCORE_ASSERT(m_instance);
  return *m_instance;
}

AudioPreviewExecutor::AudioPreviewExecutor() : audio{}
{
  m_instance = this;
}

void AudioPreviewExecutor::endTick(unsigned long frameCount, double seconds)
{
  bool received = false;
  while (queue.try_dequeue(current_sound))
  {
    received = true;
    continue;
  }

  if (received)
  {
    if (current_sound.handle)
    {
      currentPos = 0;
      playing = true;
    }
    else
    {
      playing = false;
    }
  }

  if (!audio)
    return;

  auto& outs = this->audio->audio_outs;
  if (playing && current_sound.handle && outs.size() >= 2)
  {
    auto out_l = outs[0]->audio[0];
    auto out_r = outs[1]->audio[0];

    switch (current_sound.handle->data.size())
    {
      case 0:
      {
        return;
      }
      case 1:
      {
        int64_t max_n = current_sound.handle->data.front().size();
        float* in_mono = current_sound.handle->data.front().data();

        int64_t& i = currentPos;
        unsigned long out_i = 0;
        for (; i < max_n && out_i < frameCount; i++, out_i++)
        {
          out_l[out_i] += 0.6f * in_mono[i];
          out_r[out_i] += 0.6f * in_mono[i];
        }

        if (i == max_n)
        {
          playing = false;
          currentPos = 0;
        }

        break;
      }
      case 2:
      {
        int64_t max_n = current_sound.handle->data.front().size();
        float* in_l = current_sound.handle->data[0].data();
        float* in_r = current_sound.handle->data[1].data();

        int64_t& i = currentPos;
        unsigned long out_i = 0;
        for (; i < max_n && out_i < frameCount; i++, out_i++)
        {
          out_l[out_i] += 0.6f * in_l[i];
          out_r[out_i] += 0.6f * in_r[i];
        }

        if (i == max_n)
        {
          playing = false;
          currentPos = 0;
        }

        break;
      }
    }
  }
}

}
