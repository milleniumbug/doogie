#ifndef DOOGIE_PROFILE_SETTINGS_DIALOG_H_
#define DOOGIE_PROFILE_SETTINGS_DIALOG_H_

#include <QtWidgets>

#include "blocker_list.h"
#include "bubble.h"
#include "profile.h"

namespace doogie {

class ProfileSettingsDialog : public QDialog {
  Q_OBJECT

 public:
  explicit ProfileSettingsDialog(const Cef& cef,
                                 Profile* profile,
                                 QSet<QString> in_use_bubble_names,
                                 QWidget* parent = nullptr);
  bool NeedsRestart() const { return needs_restart_; }
  void done(int r) override;

 protected:
  void closeEvent(QCloseEvent* event) override;
  void keyPressEvent(QKeyEvent* event) override;

 private:
  QWidget* CreateSettingsTab();
  QWidget* CreateShortcutsTab();
  QWidget* CreateBubblesTab();
  QWidget* CreateBlockerTab(const Cef& cef);
  void AddBlockerListUrl(const Cef& cef,
                         const QString& default_url,
                         std::function<void(BlockerList, bool)> callback);
  bool BlockerChanged();

  Profile* orig_profile_;
  QSet<QString> in_use_bubble_names_;
  Profile profile_;
  bool needs_restart_ = false;
  QList<Bubble> temp_bubbles_;

  QList<BlockerList> orig_blocker_lists_;
  // Keyed by url or local path
  QHash<QString, BlockerList> temp_blocker_lists_;
  // Value is url or local path
  QSet<QString> enabled_blocker_lists_;
  QList<qlonglong> blocker_list_ids_pending_refresh_;

 signals:
  void Changed();
};

}  // namespace doogie

#endif  // DOOGIE_PROFILE_SETTINGS_DIALOG_H_
