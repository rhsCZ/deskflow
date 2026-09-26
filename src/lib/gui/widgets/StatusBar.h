/*
 * Deskflow -- mouse and keyboard sharing utility
 * SPDX-FileCopyrightText: (C) 2025 - 2026 Deskflow Developers
 * SPDX-FileCopyrightText: (C) 2026 Synergy App Ltd
 * SPDX-License-Identifier: GPL-2.0-only WITH LicenseRef-OpenSSL-Exception
 */

#pragma once

#include <QStatusBar>

#include "common/Enums.h"

class QPushButton;
class QLabel;

using ProcessState = deskflow::core::ProcessState;
using ConnectionState = deskflow::core::ConnectionState;

class StatusBar : public QStatusBar
{
  Q_OBJECT
public:
  explicit StatusBar(QWidget *parent = nullptr);
  void setStatus(ConnectionState connectionState, ProcessState processState, bool isServer);
  void setServerClients(const QStringList &clients);
  void setSecurityIconVisible(bool visible);
  void setConnectionInterval(int newInterval);
  bool securityIconVisible() const;
  void updateSecurityInfo(bool encrypted);
  void setSecurityIcon(bool encrypted);
  void setSecurityLevel(const QString &securityLevel);
  void setBtnFingerprintVisible(bool visible);
  void updateFound(const QString &version);
  void showClipboardSending(qint64 bytes, const QString &peer);
  void showClipboardSent(const QString &peer);
  void showClipboardOverLimit(qint64 bytes, qint64 limit);

Q_SIGNALS:
  void requestShowMyFingerprints();
  void requestUpdateVersion();

protected:
  void changeEvent(QEvent *e) override;

private:
  void updateText();
  void updateTimerLabel();
  static QString clipboardPeerName(const QString &peer);

  static constexpr int kClipboardSentTimeoutMs = 5000;
  static constexpr int kClipboardNoticeTimeoutMs = 30000;

  QPushButton *m_btnFingerprint = nullptr;
  QLabel *m_lblSecurityIcon = nullptr;
  QLabel *m_lblStatus = nullptr;
  QLabel *m_lblClipboard = nullptr;
  QPushButton *m_btnUpdate = nullptr;
  bool m_encrypted = false;
  QString m_securityLevel;
  int m_connectionInterval = -1;
  QTimer *m_retryTimer = nullptr;
  QTimer *m_clipboardTimer = nullptr;
};
