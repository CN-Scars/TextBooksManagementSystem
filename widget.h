#ifndef WIDGET_H
#define WIDGET_H

#include <QTableWidgetItem>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    QString strData;
    QString Password = "homo11451419190810";    //系统密码

    void appendOneRow(QString ISBN, QString BookName, QString Count, QString Price, QString Subject, QString Author, QString PublishingHouse, QString Remarks, QString Time); //添加一行
    void insertOneRow(int CurrentRow,QString ISBN, QString BookName, QString Count, QString Price, QString Subject, QString Author, QString PublishingHouse, QString Remarks, QString Time);   //插入一行

public slots:
    void onItemClicked(QTableWidgetItem* Item); //显示单元格数据槽函数

private slots:
    void on_Append_clicked();

    void on_Insert_clicked();

    void on_Delete_clicked();

    void on_Edit_clicked();

    void on_Import_clicked();

    void on_Export_clicked();

    void on_Search_clicked();

    void on_Clear_clicked();

    void on_TextBooksTable_clicked(const QModelIndex &index);

    void on_TextBooksTable_cellClicked(int row, int column);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
