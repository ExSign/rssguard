// For license of this file, see <project-root-folder>/LICENSE.md.

#include "gui/notifications/singlenotificationeditor.h"

#include "miscellaneous/application.h"
#include "miscellaneous/iconfactory.h"

#include <QFileDialog>

SingleNotificationEditor::SingleNotificationEditor(const Notification& notification, QWidget* parent)
  : QGroupBox(parent), m_notificationEvent(Notification::Event::NoEvent) {
  m_ui.setupUi(this);

  m_ui.m_btnBrowseSound->setIcon(qApp->icons()->fromTheme(QSL("document-open")));
  m_ui.m_btnClearSound->setIcon(qApp->icons()->fromTheme(QSL("edit-clear")));
  m_ui.m_btnPlaySound->setIcon(qApp->icons()->fromTheme(QSL("media-playback-start")));

  loadNotification(notification);

  connect(m_ui.m_btnPlaySound, &QPushButton::clicked, this, &SingleNotificationEditor::playSound);
  connect(m_ui.m_btnBrowseSound, &QPushButton::clicked, this, &SingleNotificationEditor::selectSoundFile);
  connect(m_ui.m_btnClearSound, &QPushButton::clicked, m_ui.m_txtSound, &QLineEdit::clear);
  connect(m_ui.m_txtSound, &QLineEdit::textChanged, this, &SingleNotificationEditor::notificationChanged);
  connect(m_ui.m_cbBalloon, &QCheckBox::toggled, this, &SingleNotificationEditor::notificationChanged);

  setFixedHeight(sizeHint().height());
}

Notification SingleNotificationEditor::notification() const {
  return Notification(m_notificationEvent, m_ui.m_cbBalloon->isChecked(), m_ui.m_txtSound->text());
}

void SingleNotificationEditor::selectSoundFile() {
  auto fil = QFileDialog::getOpenFileName(window(), tr("Select sound file"),
                                          qApp->homeFolder(),
                                          tr("WAV files (*.wav)"));

  if (!fil.isEmpty()) {
    m_ui.m_txtSound->setText(fil);
  }
}

void SingleNotificationEditor::playSound() {
  Notification({}, {}, m_ui.m_txtSound->text()).playSound(qApp);
}

void SingleNotificationEditor::loadNotification(const Notification& notification) {
  m_ui.m_txtSound->setText(notification.soundPath());
  m_ui.m_cbBalloon->setChecked(notification.balloonEnabled());
  setTitle(Notification::nameForEvent(notification.event()));

  m_notificationEvent = notification.event();
}