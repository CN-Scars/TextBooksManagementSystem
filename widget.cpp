#include "widget.h"
#include "ui_widget.h"
#include <ActiveQt/QAxObject>
#include <QFileDialog>
#include <QProgressBar>
#include <QMessageBox>
#include <QDesktopServices>
#include <QInputDialog>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //设置表格列数
    ui->TextBooksTable->setColumnCount(9);
    //头部标签
    QStringList horizontalList;
    horizontalList << "教材编号";
    horizontalList << "教材名称";
    horizontalList << "数量";
    horizontalList << "价格";
    horizontalList << "所属专业";
    horizontalList << "作者";
    horizontalList << "出版社";
    horizontalList << "备注信息";
    horizontalList << "保存时间";
    //添加标签至表格头部
    ui->TextBooksTable->setHorizontalHeaderLabels(horizontalList);
    //自动获取头部宽度并将其设置为列的宽度以填充头部（列数多时不建议使用，否则单元格内容会被强制压缩，是否使用视情况而定）
    //ui->TextBooksTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //添加初始化数据
    appendOneRow("教材编号1", "名称A", "Null", "0元", "专业1", "作者A", "出版社A", "备注信息1", "修改时间1");
    appendOneRow("教材编号2", "名称B", "Null", "0元", "专业2", "作者B", "出版社B", "备注信息2", "修改时间2");
    appendOneRow("教材编号3", "名称C", "Null", "0元", "专业3", "作者C", "出版社C", "备注信息3", "修改时间3");
    //设置行表头是否显示
    if(ui->TextBooksTable->horizontalHeader()->isHidden())
    {
        ui->ShowRowHeader->setChecked(false);
    }
    else
    {
        ui->ShowRowHeader->setChecked(true);
    }
    connect(ui->ShowRowHeader, &QCheckBox::stateChanged, this, [=](int state){
       if(state == Qt::Checked)
       {
           ui->TextBooksTable->horizontalHeader()->show();
       }
       else
       {
           ui->TextBooksTable->horizontalHeader()->hide();
       }
    });
    //设置列表头是否显示
    if(!ui->TextBooksTable->verticalHeader()->isHidden())
    {
        ui->ShowListHeader->setChecked(false);
    }
    else
    {
        ui->ShowListHeader->setChecked(true);
    }
    connect(ui->ShowListHeader, &QCheckBox::stateChanged, this, [=](int state){
       if(state == Qt::Checked)
       {
           ui->TextBooksTable->verticalHeader()->show();
       }
       else
       {
           ui->TextBooksTable->verticalHeader()->hide();
       }
    });

    //设置默认交替显示行背景色
    ui->TextBooksTable->setAlternatingRowColors(true);
    //设置是否交替显示行背景色
    if(ui->TextBooksTable->alternatingRowColors())   //判断是否有默认背景色
    {
        ui->AlternatingDisplay->setChecked(true);
    }
    else
    {
        ui->AlternatingDisplay->setChecked(false);
    }
    connect(ui->AlternatingDisplay, &QCheckBox::stateChanged, this, [=](int state){
        if(state == Qt::Checked)
        {
            ui->TextBooksTable->setAlternatingRowColors(true);
        }
        else
        {
            ui->TextBooksTable->setAlternatingRowColors(false);
        }
    });

    //默认设置单元格不可编辑
    ui->TextBooksTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //int trigger = ui->TextBooksTable->editTriggers();

    //设置显示框中修改时间的数据不可修改
    ui->TimeShower->setReadOnly(true);

    //点击单元格时，将内容显示到文本框内
    connect(ui->TextBooksTable, &QTableWidget::itemClicked, this, &Widget::onItemClicked);

    //设置进度条初始值为0
    ui->progressBar->setValue(0);

    //取消行号
    ui->TextBooksTable->verticalHeader()->hide();

    //设置文本框的占位字符串
    ui->KeyWords->setPlaceholderText("请输入关键词：");
    ui->ISBNEditor->setPlaceholderText("请输入教材编号（ISBN）：");
    ui->NameEditor->setPlaceholderText("请输入教材名称：");
    ui->CountEditor->setPlaceholderText("请输入教材数量：");
    ui->PriceEditor->setPlaceholderText("请输入教材价格：");
    ui->SubjectEditor->setPlaceholderText("请输入教材所属专业：");
    ui->AuthorEditor->setPlaceholderText("请输入作者：");
    ui->PublisherEditor->setPlaceholderText("请输入出版社：");
    ui->RemarksEditor->setPlaceholderText("请输入备注信息：");

    ui->TextBooksTable->setSortingEnabled(true);
    ui->TextBooksTable->sortItems(1);
    ui->TextBooksTable->sortItems(6);
    ui->TextBooksTable->sortItems(8);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::appendOneRow(QString ISBN, QString BookName, QString Count, QString Price, QString Subject, QString Author, QString PublishingHouse, QString Remarks, QString Time)
{
    int count = ui->TextBooksTable->rowCount(); //获取行数
    ui->TextBooksTable->setRowCount(count + 1);

    //创建Item类指针
    QTableWidgetItem* ISBNItem = new QTableWidgetItem(ISBN);
    QTableWidgetItem* BookNameItem = new QTableWidgetItem(BookName);
    QTableWidgetItem* CountItem = new QTableWidgetItem(Count);
    QTableWidgetItem* PriceItem = new QTableWidgetItem(Price);
    QTableWidgetItem* SubjectItem = new QTableWidgetItem(Subject);
    QTableWidgetItem* AuthorItem = new QTableWidgetItem(Author);
    QTableWidgetItem* PublishingHouseItem = new QTableWidgetItem(PublishingHouse);
    QTableWidgetItem* RemarksItem = new QTableWidgetItem(Remarks);
    QTableWidgetItem* TimeItem = new QTableWidgetItem(Time);

    //居中显示
    ISBNItem->setTextAlignment(Qt::AlignCenter);
    BookNameItem->setTextAlignment(Qt::AlignCenter);
    CountItem->setTextAlignment(Qt::AlignCenter);
    PriceItem->setTextAlignment(Qt::AlignCenter);
    SubjectItem->setTextAlignment(Qt::AlignCenter);
    AuthorItem->setTextAlignment(Qt::AlignCenter);
    PublishingHouseItem->setTextAlignment(Qt::AlignCenter);
    RemarksItem->setTextAlignment(Qt::AlignCenter);
    TimeItem->setTextAlignment(Qt::AlignCenter);

    //设置初始数据
    ui->TextBooksTable->setItem(count, 0, ISBNItem);
    ui->TextBooksTable->setItem(count, 1, BookNameItem);
    ui->TextBooksTable->setItem(count, 2, CountItem);
    ui->TextBooksTable->setItem(count, 3, PriceItem);
    ui->TextBooksTable->setItem(count, 4, SubjectItem);
    ui->TextBooksTable->setItem(count, 5, AuthorItem);
    ui->TextBooksTable->setItem(count, 6, PublishingHouseItem);
    ui->TextBooksTable->setItem(count, 7, RemarksItem);
    ui->TextBooksTable->setItem(count, 8, TimeItem);
}

void Widget::insertOneRow(int CurrentRow,QString ISBN, QString BookName, QString Count, QString Price, QString Subject, QString Author, QString PublishingHouse, QString Remarks, QString Time)
{
    ui->TextBooksTable->insertRow(CurrentRow);  //插入一个空行
    //创建Item类指针
    QTableWidgetItem* ISBNItem = new QTableWidgetItem(ISBN);
    QTableWidgetItem* BookNameItem = new QTableWidgetItem(BookName);
    QTableWidgetItem* CountItem = new QTableWidgetItem(Count);
    QTableWidgetItem* PriceItem = new QTableWidgetItem(Price);
    QTableWidgetItem* SubjectItem = new QTableWidgetItem(Subject);
    QTableWidgetItem* AuthorItem = new QTableWidgetItem(Author);
    QTableWidgetItem* PublishingHouseItem = new QTableWidgetItem(PublishingHouse);
    QTableWidgetItem* RemarksItem = new QTableWidgetItem(Remarks);
    QTableWidgetItem* TimeItem = new QTableWidgetItem(Time);

    //居中显示
    ISBNItem->setTextAlignment(Qt::AlignCenter);
    BookNameItem->setTextAlignment(Qt::AlignCenter);
    CountItem->setTextAlignment(Qt::AlignCenter);
    PriceItem->setTextAlignment(Qt::AlignCenter);
    SubjectItem->setTextAlignment(Qt::AlignCenter);
    AuthorItem->setTextAlignment(Qt::AlignCenter);
    PublishingHouseItem->setTextAlignment(Qt::AlignCenter);
    RemarksItem->setTextAlignment(Qt::AlignCenter);
    TimeItem->setTextAlignment(Qt::AlignCenter);

    //设置初始数据
    ui->TextBooksTable->setItem(CurrentRow, 0, ISBNItem);
    ui->TextBooksTable->setItem(CurrentRow, 1, BookNameItem);
    ui->TextBooksTable->setItem(CurrentRow, 2, CountItem);
    ui->TextBooksTable->setItem(CurrentRow, 3, PriceItem);
    ui->TextBooksTable->setItem(CurrentRow, 4, SubjectItem);
    ui->TextBooksTable->setItem(CurrentRow, 5, AuthorItem);
    ui->TextBooksTable->setItem(CurrentRow, 6, PublishingHouseItem);
    ui->TextBooksTable->setItem(CurrentRow, 7, RemarksItem);
    ui->TextBooksTable->setItem(CurrentRow, 8, TimeItem);
}

void Widget::onItemClicked(QTableWidgetItem *Item)
{
    int row = Item->row();
    QString ISBN = ui->TextBooksTable->item(row, 0)->text();
    QString BookName = ui->TextBooksTable->item(row, 1)->text();
    QString Count = ui->TextBooksTable->item(row, 2)->text();
    QString Price = ui->TextBooksTable->item(row, 3)->text();
    QString Subject = ui->TextBooksTable->item(row, 4)->text();
    QString Author = ui->TextBooksTable->item(row, 5)->text();
    QString PublishingHouse = ui->TextBooksTable->item(row, 6)->text();
    QString Remarks = ui->TextBooksTable->item(row, 7)->text();
    QString Time = ui->TextBooksTable->item(row, 8)->text();

    //显示文本
    ui->ISBNEditor->setText(ISBN);
    ui->NameEditor->setText(BookName);
    ui->CountEditor->setText(Count);
    ui->PriceEditor->setText(Price);
    ui->SubjectEditor->setText(Subject);
    ui->AuthorEditor->setText(Author);
    ui->PublisherEditor->setText(PublishingHouse);
    ui->RemarksEditor->setText(Remarks);
    ui->TimeShower->setText(Time);
}

void Widget::on_Append_clicked()
{
    //获取数据
    QString ISBN = ui->ISBNEditor->text();
    QString BookName = ui->NameEditor->text();
    QString Count = ui->CountEditor->text();
    QString Price = ui->PriceEditor->text();
    QString Subject = ui->SubjectEditor->text();
    QString Author = ui->AuthorEditor->text();
    QString PublishingHouse = ui->PublisherEditor->text();
    QString Remarks = ui->RemarksEditor->text();
    QDateTime time = QDateTime::currentDateTime();  //获取系统现在的时间
    QString Time = time.toString("yyyy-MM-dd hh:mm:ss");
    //添加一行
    appendOneRow(ISBN, BookName, Count, Price, Subject, Author, PublishingHouse, Remarks, Time);
}

void Widget::on_Insert_clicked()
{
    //获取数据
    QString ISBN = ui->ISBNEditor->text();
    QString BookName = ui->NameEditor->text();
    QString Count = ui->CountEditor->text();
    QString Price = ui->PriceEditor->text();
    QString Subject = ui->SubjectEditor->text();
    QString Author = ui->AuthorEditor->text();
    QString PublishingHouse = ui->PublisherEditor->text();
    QString Remarks = ui->RemarksEditor->text();
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString Time = time.toString("yyyy-MM-dd hh:mm:ss");
    //获取当前行
    int CurrentRow = ui->TextBooksTable->currentRow();
    //插入一行
    insertOneRow(CurrentRow, ISBN, BookName, Count, Price, Subject, Author, PublishingHouse, Remarks, Time);
}

void Widget::on_Delete_clicked()
{
    //获取当前行
    int CurrentRow = ui->TextBooksTable->currentRow();
    ui->TextBooksTable->removeRow(CurrentRow);
}

void Widget::on_Edit_clicked()
{
    //获取数据
    QString ISBN = ui->ISBNEditor->text();
    QString BookName = ui->NameEditor->text();
    QString Count = ui->CountEditor->text();
    QString Price = ui->PriceEditor->text();
    QString Subject = ui->SubjectEditor->text();
    QString Author = ui->AuthorEditor->text();
    QString PublishingHouse = ui->PublisherEditor->text();
    QString Remarks = ui->RemarksEditor->text();
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString Time = time.toString("yyyy-MM-dd hh:mm:ss");
    //获取当前行
    int CurrentRow = ui->TextBooksTable->currentRow();
    //创建Item类指针
    QTableWidgetItem* ISBNItem = new QTableWidgetItem(ISBN);
    QTableWidgetItem* BookNameItem = new QTableWidgetItem(BookName);
    QTableWidgetItem* CountItem = new QTableWidgetItem(Count);
    QTableWidgetItem* PriceItem = new QTableWidgetItem(Price);
    QTableWidgetItem* SubjectItem = new QTableWidgetItem(Subject);
    QTableWidgetItem* AuthorItem = new QTableWidgetItem(Author);
    QTableWidgetItem* PublishingHouseItem = new QTableWidgetItem(PublishingHouse);
    QTableWidgetItem* RemarksItem = new QTableWidgetItem(Remarks);
    QTableWidgetItem* TimeItem = new QTableWidgetItem(Time);

    //居中显示
    ISBNItem->setTextAlignment(Qt::AlignCenter);
    BookNameItem->setTextAlignment(Qt::AlignCenter);
    CountItem->setTextAlignment(Qt::AlignCenter);
    PriceItem->setTextAlignment(Qt::AlignCenter);
    SubjectItem->setTextAlignment(Qt::AlignCenter);
    AuthorItem->setTextAlignment(Qt::AlignCenter);
    PublishingHouseItem->setTextAlignment(Qt::AlignCenter);
    RemarksItem->setTextAlignment(Qt::AlignCenter);
    TimeItem->setTextAlignment(Qt::AlignCenter);

    //设置初始数据
    ui->TextBooksTable->setItem(CurrentRow, 0, ISBNItem);
    ui->TextBooksTable->setItem(CurrentRow, 1, BookNameItem);
    ui->TextBooksTable->setItem(CurrentRow, 2, CountItem);
    ui->TextBooksTable->setItem(CurrentRow, 3, PriceItem);
    ui->TextBooksTable->setItem(CurrentRow, 4, SubjectItem);
    ui->TextBooksTable->setItem(CurrentRow, 5, AuthorItem);
    ui->TextBooksTable->setItem(CurrentRow, 6, PublishingHouseItem);
    ui->TextBooksTable->setItem(CurrentRow, 7, RemarksItem);
    ui->TextBooksTable->setItem(CurrentRow, 8, TimeItem);
}

void Widget::on_Import_clicked()
{
    //导入表格
    ui->progressBar->setValue(0);   //设置进度条的值为0
    QString path = QFileDialog::getOpenFileName(this,"打开","../","Excel Files(*.xls)");
    //指定父对象（this），“open”具体操作，打开，“../”默认，之后可以添加要打开文件的格式
    if(path.isEmpty() == false)
    {
        //文件对象
        QFile file(path);
        //打开文件,默认为utf8变量，
        bool flag = file.open(QIODevice::ReadOnly);
        if(flag == true)    //打开成功
        {
            ui->progressBar->show();
            ui->progressBar->setValue(10);
            QAxObject *excel = new QAxObject(this); //建立excel操作对象
            excel->setControl("Excel.Application"); //连接Excel控件
            excel->setProperty("Visible", false);   //不显示窗体看效果
            excel->setProperty("DisplayAlerts", false); //不显示警告看效果
            /*********获取COM文件的一种方式************/
            QAxObject *workbooks = excel->querySubObject("WorkBooks");
            //获取工作簿(excel文件)集合
            workbooks->dynamicCall("Open(const QString&)", path);   //path至关重要，获取excel文件的路径
            //打开一个excel文件
            QAxObject *workbook = excel->querySubObject("ActiveWorkBook");
            QAxObject *worksheet = workbook->querySubObject("WorkSheets(int)",1);   //访问excel中的工作表中第一个单元格
            QAxObject *usedRange = worksheet->querySubObject("UsedRange");  //sheet的范围
            /*********获取COM文件的一种方式************/
            //获取打开excel的起始行数和列数和总共的行数和列数
            int intRowStart = usedRange->property("Row").toInt();   //起始行数
            int intColStart = usedRange->property("Column").toInt();    //起始列数
            QAxObject *rows, *columns;
            rows = usedRange->querySubObject("Rows");   //行
            columns = usedRange->querySubObject("Columns"); //列
            int intRow = rows->property("Count").toInt();   //行数
            int intCol = columns->property("Count").toInt();    //列数
            //起始行列号
            int a, b;
            a = intRow-intRowStart + 1,b = intCol-intColStart + 1;
            QByteArray text[a][b];
            QString exceldata[a][b];
            int coerow = 0,coecol = 0;
            for (int i = intRowStart; i < intRowStart + intRow; i++,coerow++)
            {
                coecol = 0;   //恢复初始值
                for (int j = intColStart; j < intColStart + intCol; j++,coecol++)
                {
                    auto cell = excel->querySubObject("Cells(Int, Int)", i, j );
                    QVariant cellValue = cell->dynamicCall("value");
                    text[coerow][coecol] = cellValue.toByteArray(); //QVariant转换为QByteArray
                    exceldata[coerow][coecol] = QString(text[coerow][coecol]);  //QByteArray转换为QString
                    if(ui->progressBar->value()<=60)
                    {
                        ui->progressBar->setValue(10+i*5);
                    }
                    //qDebug()<<exceldata[coerow][coecol]<<coerow<<" "<<coecol;
                }
            }
            ui->TextBooksTable->setRowCount(a-1);
            for(int i = 1; i < a; ++i)
            {
                for(int j = 0; j < b; ++j)
                {
                    ui->TextBooksTable->setItem(i-1, j, new QTableWidgetItem(exceldata[i][j]));
                    if(ui->progressBar->value()<=80)
                    {
                        ui->progressBar->setValue(60+i*5);
                    }
                }
            }
            //将表格内所有元素全部居中显示
            for (int i = 0; i < ui->TextBooksTable->rowCount(); i++)    //行数
            {
                for (int j = 0; j < ui->TextBooksTable->columnCount(); j++) //列数
                {
                    ui->TextBooksTable->item(i,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                }
            }
            workbook->dynamicCall( "Close(Boolean)", false );
            excel->dynamicCall( "Quit(void)" );
            delete excel;
            ui->progressBar->setValue(100);
            QMessageBox::information(this,tr("导入情况"),tr("导入完成！"),QMessageBox::Ok);
            ui->progressBar->setValue(0);
        }
        file.close();   //关闭文件
    }
}

void Widget::on_Export_clicked()
{
    //导出
    ui->progressBar->show();    //进度条需要在ui文件中加个progressBar控件
    ui->progressBar->setValue(0);   //设置进度条的值为0
    QString fileName = QFileDialog::getSaveFileName(this,tr("另存为"),QString("./Excel.xls"),tr("Excel Files(*.xls)"));    //设置保存的文件名
    qDebug() << fileName;
    if(fileName != "")
    {
        ui->progressBar->setValue(10);
        QAxObject *excel = new QAxObject;
        if(excel->setControl("Excel.Application"))
        {
            excel->dynamicCall("SetVisible (bool Visible)",false);
            excel->setProperty("DisplayAlerts",false);
            QAxObject *workbooks = excel->querySubObject("WorkBooks");  //获取工作簿集合
            workbooks->dynamicCall("Add");  //新建一个工作簿
            QAxObject *workbook = excel->querySubObject("ActiveWorkBook");  //获取当前工作簿
            QAxObject *worksheet = workbook->querySubObject("Worksheets(int)", 1);
            QAxObject *cell;

            /*添加Excel表头数据*/
            for(int i = 1; i <= ui->TextBooksTable->columnCount(); i++)
            {
                cell=worksheet->querySubObject("Cells(int,int)", 1, i);
                cell->setProperty("RowHeight", 40);
                cell->dynamicCall("SetValue(const QString&)", ui->TextBooksTable->horizontalHeaderItem(i-1)->data(0).toString());
                if(ui->progressBar->value()<=50)
                {
                    ui->progressBar->setValue(10+i*5);
                }
            }

            /*将form列表中的数据依此保存到Excel文件中*/
            for(int j = 2; j <= ui->TextBooksTable->rowCount() + 1; j++)
            {
                for(int k = 1; k <= ui->TextBooksTable->columnCount(); k++)
                {
                    cell=worksheet->querySubObject("Cells(int,int)", j, k);
                    cell->dynamicCall("SetValue(const QString&)",ui->TextBooksTable->item(j-2,k-1)->text()+ "\t");
                }
                if(ui->progressBar->value()<80)
                {
                    ui->progressBar->setValue(50+j*5);
                }
            }

            /*将生成的Excel文件保存到指定目录下*/
            workbook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(fileName)); //保存至fileName
            workbook->dynamicCall("Close()");   //关闭工作簿
            excel->dynamicCall("Quit()");   //关闭excel
            delete excel;
            excel=NULL;

            ui->progressBar->setValue(100);
            if (QMessageBox::question(NULL,QString::fromUtf8("完成"),QString::fromUtf8("文件已经导出，是否现在打开？"),QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
            {
                QDesktopServices::openUrl(QUrl("file:///" + QDir::toNativeSeparators(fileName)));
            }
            ui->progressBar->setValue(0);
        }
    }
}

void Widget::on_Search_clicked()
{
    for(int i = 0; i < ui->TextBooksTable->rowCount(); i++)
    {
        ui->TextBooksTable->setRowHidden(i,false);
    }
    QString text = ui->KeyWords->text();
    if(!text.isEmpty())
    {
        QList<QTableWidgetItem*> findItem = ui->TextBooksTable->findItems(text,Qt::MatchContains);
        int nRow = ui->TextBooksTable->rowCount();
        bool bRowHidden = true;
        for(int i = 0; i < nRow; i++)
        {
            bRowHidden = true;
            foreach(QTableWidgetItem* item, findItem)
            {
                 if(NULL == item)
                 {
                    continue;
                 }
                 if(ui->TextBooksTable->row(item) == i)
                 {
                    bRowHidden = false;
                    break;
                 }
             }
             ui->TextBooksTable->setRowHidden(i,bRowHidden);
        }
    }
}

void Widget::on_Clear_clicked()
{
    ui->progressBar->setValue(0);
    bool ok;
    QString text = QInputDialog::getText(this, tr("操作验证"),tr("请输入密码以继续操作"), QLineEdit::Password,0, &ok);
    if(text == Password)
    {
        ok = true;
    }
    else
    {
        ok = false;
    }
    ui->progressBar->setValue(20);
    if (ok && !text.isEmpty())  //密码正确
    {
        //清空QTableWidget控件数据
        int Count = ui->TextBooksTable->rowCount();
        int Value = 20;
        while(ui->TextBooksTable->rowCount())
        {
            ui->TextBooksTable->removeRow(0);
            ui->progressBar->setValue(Value + 80 / Count);
            Value += 80 / Count;
        }
        ui->progressBar->setValue(100);
        QMessageBox::information(this,tr("成功！"),tr("已清空所有数据！"),QMessageBox::Ok);
    }
    else if(!ok && !text.isEmpty()) //密码错误
    {
        ui->progressBar->setValue(0);
        QMessageBox::warning(this,tr("错误！"),tr("密码错误！请重新输入，若忘记密码请联系管理员！"),QMessageBox::Ok);    
    }
    ui->progressBar->setValue(0);
}

void Widget::on_TextBooksTable_cellClicked(int row, int column)
{
    ui->TablePosition->setText("当前位置：第" + QString::number(row + 1) + "行" + QString::number(column + 1) + "列");
}

void Widget::on_TextBooksTable_clicked(const QModelIndex &index)
{
    //此函数不存在实际作用，仅为保证void Widget::on_TextBooksTable_cellClicked()函数能成功运行
    qDebug() << index;
}
