// For license of this file, see <project-root-folder>/LICENSE.md.

#ifndef BASETOASTNOTIFICATION_H
#define BASETOASTNOTIFICATION_H

#include <QDialog>

#include <QTimer>

class QAbstractButton;
class QLabel;

class BaseToastNotification : public QDialog {
    Q_OBJECT

  public:
    explicit BaseToastNotification(QWidget* parent = nullptr);
    virtual ~BaseToastNotification();

  public slots:
    virtual void reject();

  protected:
    virtual bool eventFilter(QObject* watched, QEvent* event);
    virtual void timerEvent(QTimerEvent* event);
    virtual void closeEvent(QCloseEvent* event);

    void setupHeading(QLabel* lbl);
    void setupTimedClosing();
    void setupCloseButton(QAbstractButton* btn);
    void stopTimedClosing();

  signals:
    void closeRequested(BaseToastNotification* notif);

  private:
    QTimer m_timerClosingClick;
    int m_timerId;
};

#endif // BASETOASTNOTIFICATION_H
