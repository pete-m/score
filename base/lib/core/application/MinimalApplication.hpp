#pragma once

#include <QLocale>
#include <clocale>
#include <QApplication>

#include <core/settings/Settings.hpp>
#include <core/presenter/Presenter.hpp>
#include <core/application/ApplicationInterface.hpp>
#include <core/application/ApplicationSettings.hpp>

#if defined(SCORE_STATIC_PLUGINS)
#include <score_static_plugins.hpp>
#endif

namespace score
{
class MinimalApplication final
    : public QObject
    , public score::GUIApplicationInterface
{
public:
  MinimalApplication(int& argc, char** argv)
    : QObject{nullptr}
    , m_app{new QApplication{argc, argv}}
  {
    #if defined(SCORE_STATIC_PLUGINS)
    score_init_static_plugins();
    #endif

    m_instance = this;
    this->setParent(m_app);

    m_presenter = new score::Presenter{m_applicationSettings, m_settings, m_pset, nullptr, this};

    GUIApplicationInterface::loadPluginData(m_settings, *m_presenter);
  }

  ~MinimalApplication() override
  {
    this->setParent(nullptr);
    delete m_presenter;

    QApplication::processEvents();
    delete m_app;
  }

  const score::GUIApplicationContext& context() const override
  {
    return m_presenter->applicationContext();
  }

  const score::ApplicationComponents& components() const override
  {
    return context().components;
  }

  int exec() { return m_app->exec(); }

  QApplication* m_app;
  score::Settings m_settings;
  score::ProjectSettings m_pset;
  score::Presenter* m_presenter{};
  score::ApplicationSettings m_applicationSettings;
};
}
