/*
	mythburnwizard.h

    header for the mythburn interface screen
*/

#ifndef MYTHBURNWIZARD_H_
#define MYTHBURNWIZARD_H_

#include <mythtv/uitypes.h>
#include <mythtv/uilistbtntype.h>
#include <mythtv/dialogbox.h>
#include <mythtv/libmythtv/programinfo.h>

#include "mytharchivewizard.h"

enum ArchiveItemType
{
    AT_RECORDING = 1,
    AT_VIDEO,
    AT_FILE
};

typedef struct
{
    QString name;
    QString description;
    float bitrate;
} EncoderProfile;

typedef struct
{
    int     id;
    QString type;
    QString title;
    QString subtitle;
    QString description;
    QString startDate;
    QString startTime;
    QString filename;
    long long size;
    long long newsize;
    int duration;
    EncoderProfile *encoderProfile;
    QString fileCodec;
    QString videoCodec;
    int videoWidth, videoHeight;
    bool hasCutlist;
    bool useCutlist;
    bool editedDetails;
} ArchiveItem;


class MythburnWizard : public MythThemedDialog
{

  Q_OBJECT

  public:
    MythburnWizard(ArchiveDestination destination,
                   MythMainWindow *parent, QString window_name,
                   QString theme_filename, const char *name = 0);

    ~MythburnWizard(void);

    void keyPressEvent(QKeyEvent *e);
    void createConfigFile(const QString &filename);

    void setSaveFilename(QString filename) {saveFilename = filename;}

  public slots:
    void handleNextPage(void);
    void handlePrevPage(void);
    void handleCancel(void);

    void setTheme(int);
    void setCategory(int);
    void setProfile(int);
    void titleChanged(UIListBtnTypeItem *item);
    void selectedChanged(UIListBtnTypeItem *item);
    void toggleUseCutlist(bool state);
    void showMenu(void);
    void closePopupMenu(void);
    void editDetails(void);
    void useSLDVD(void);
    void useDLDVD(void);
    void removeItem(void);

  private:
    ArchiveDestination archiveDestination;
    QString themeDir; 
    int freeSpace;
    int usedSpace;

    void getThemeList(void);
    void updateArchiveList(void);
    void toggleSelectedState(void);
    void getArchiveList(void);
    void wireUpTheme(void);
    void updateSizeBar(bool show);
    void loadConfiguration(void);
    void saveConfiguration(void);
    void updateSelectedArchiveList(void);
    void showEditMetadataDialog();
    QString loadFile(const QString &filename);
    vector<ArchiveItem *>  *getArchiveListFromDB(void);
    bool doRemoveArchiveItem(QString &filename);
    bool isArchiveItemValid(QString &type, QString &filename);
    bool hasCutList(QString &type, QString &filename);
    bool extractDetailsFromFilename(const QString &inFile,
                                    QString &chanID, QString &startTime);
    void loadEncoderProfiles(void);
    EncoderProfile *getDefaultProfile(ArchiveItem *item);
    long long recalcSize(EncoderProfile *profile, ArchiveItem *a);
    bool getFileDetails(ArchiveItem *a);
    void setProfile(EncoderProfile *profile, ArchiveItem *item);

    vector<ArchiveItem *>  *archiveList;
    QPtrList<ArchiveItem> selectedList;

    vector<EncoderProfile *> *profileList;

    UISelectorType *theme_selector;
    UIImageType    *theme_image;
    int             theme_no;
    QStringList     theme_list;

    UIImageType    *intro_image;
    UIImageType    *mainmenu_image;
    UIImageType    *chapter_image;
    UIImageType    *details_image;
    UITextType     *themedesc_text;

    UIListBtnType  *archive_list;
    UIListBtnType  *selected_list;

    bool            bCreateISO;
    bool            bDoBurn;
    bool            bEraseDvdRw;

    QString         saveFilename;

    UITextButtonType *next_button;
    UITextButtonType *prev_button;
    UITextButtonType *cancel_button;

    UISelectorType   *category_selector;
    UITextType       *title_text;
    UITextType       *datetime_text;
    UITextType       *description_text;
    UITextType       *usecutlist_text;
    UICheckBoxType   *usecutlist_check;
    UITextType       *nocutlist_text;
    UITextType       *filesize_text;

    // size bar
    UIStatusBarType  *size_bar;
    UITextType       *maxsize_text;
    UITextType       *minsize_text;
    UITextType       *currentsize_error_text;
    UITextType       *currentsize_text;

    // profile
    UISelectorType   *profile_selector;
    UITextType       *profile_text;
    UITextType       *oldsize_text;
    UITextType       *newsize_text;

    MythPopupBox     *popupMenu;
};

#endif


