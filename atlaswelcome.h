#ifndef ATLASWELCOME_H
#define ATLASWELCOME_H

#include <QMainWindow>
#include <QMessageBox>
#include "profile.h"
#include "weeklycalendar.h"

namespace Ui {
class AtlasWelcome;
}

class AtlasWelcome : public QMainWindow
{
    Q_OBJECT

public:
    explicit AtlasWelcome(QWidget *parent = 0);
    Profile User;
    ~AtlasWelcome();
    Ui::AtlasWelcome *ui;

private slots:
    void on_SignIn_clicked();

    void on_loginCheckButton_clicked();

    void on_nextProfile_clicked();

    void on_finishCharacter_clicked();

    void on_LogoutButton_clicked();

    void on_SettingsButton_clicked();

    void on_addTaskButton_clicked();

    void on_removeTaskButton_clicked();

    void on_settingsButton_clicked();

    void on_logoutButton_clicked();

    void on_saveCatButton_clicked();

    void on_cancelAddTask_clicked();

    void on_deleteTaskButton_clicked();

    void on_cancelDeleteButton_clicked();

    void on_cancelSettingsButton_clicked();

    void on_applySettingsButton_clicked();

    void on_myProfileButton_clicked();

    void on_registrationButton_clicked();

    void on_settingsButton_2_clicked();

    void on_logoutButton_2_clicked();

    void on_registrationButton_2_clicked();

    void on_backProfileButton_clicked();

    void on_nameProfileIn_textChanged(const QString &arg1);

    void on_maleSelect_clicked(bool checked);

    void on_femaleSelect_clicked();

    void on_otherSelect_clicked();

    void on_DoBSelect_editingFinished();

    void on_FavSubjectProfileIn_textChanged(const QString &arg1);

    void on_userProfileIn_textChanged(const QString &arg1);

    void on_emailProfileIn_textChanged(const QString &arg1);

    void on_PswdProfileIn_textChanged(const QString &arg1);

    void on_characterSelect1_clicked();

    void on_characterSelect2_clicked();

    void on_characterSelect3_clicked();

    void on_characterSelect4_clicked();

    void on_characterSelect5_clicked();

    void on_characterSelect1_2_clicked();

    void on_characterSelect2_2_clicked();

    void on_characterSelect3_2_clicked();

    void on_characterSelect4_2_clicked();

    void on_characterSelect5_2_clicked();

    void setCategorySelect();

	void on_toTreasureChest_clicked();

    void on_backCharacterButton_clicked();

    void on_calculator_clicked(bool checked);

    void on_owl_clicked(bool checked);

    void on_star_clicked(bool checked);

    void on_trophy_clicked(bool checked);

    void on_locked1_clicked();

    void on_locked2_clicked();

    void on_locked3_clicked();

    void on_locked4_clicked();

    void on_pencil_clicked(bool checked);

    void on_notebook_clicked(bool checked);

    void on_skinColourCombo_currentIndexChanged(int index);

    void on_hairstyleCombo_currentIndexChanged(int index);

    void on_outfitCombo_currentIndexChanged(int index);

};

#endif // ATLASWELCOME_H
