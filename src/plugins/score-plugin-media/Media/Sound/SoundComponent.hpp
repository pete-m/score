#pragma once
#include <Media/Sound/SoundModel.hpp>
#include <Process/Dataflow/Port.hpp>
#include <Process/Execution/ProcessComponent.hpp>
#include <Process/Process.hpp>

#include <score/model/Component.hpp>

#include <ossia/dataflow/node_process.hpp>
#include <ossia/network/value/value.hpp>

namespace Execution
{

class SoundComponent final
    : public ::Execution::
          ProcessComponent_T<Media::Sound::ProcessModel, ossia::node_process>
{
  COMPONENT_METADATA("a25d0de0-74e2-4011-aeb6-4188673015f2")
public:
  SoundComponent(
      Media::Sound::ProcessModel& element,
      const ::Execution::Context& ctx,
      const Id<score::Component>& id,
      QObject* parent);

  void recompute();

  ~SoundComponent() override;

private:
};

using SoundComponentFactory
    = ::Execution::ProcessComponentFactory_T<SoundComponent>;

SCORE_CONCRETE_COMPONENT_FACTORY(
    Execution::ProcessComponentFactory,
    Execution::SoundComponentFactory)
}
