#ifndef OCLIPBOARDEDITER_H
#define OCLIPBOARDEDITER_H

#include <QDialog>
#include <map>
#include <QString>
#include <QByteArray>

struct IClipboard;

namespace Ui {
class OClipboardEditer;
}

class OClipboardEditer : public QDialog
{
    Q_OBJECT

public:
    explicit OClipboardEditer(QWidget *parent = 0);
    ~OClipboardEditer();

    void initWith(IClipboard* clipboard);
    void refreshFormatList();

    void accept() override;

protected:
	void addBtnClick();
    void removeBtnClick();
    void showEvent(QShowEvent* e) override;

private:
    Ui::OClipboardEditer *ui;
    std::map<QString, QByteArray> m_datas;
    IClipboard* m_clipboard;
};

#endif // OCLIPBOARDEDITER_H
