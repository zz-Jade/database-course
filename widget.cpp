#include "widget.h"
#include "ui_widget.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariantList>
#include <QSqlTableModel>
#include <QSqlRecord>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
   QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
   db.setHostName("localhost");
   db.setUserName("root");
   db.setPassword("asd88323");
   db.setDatabaseName("portm");

   if(!db.open())
   {
       QMessageBox::warning(this,"wrong",db.lastError().text());
       return;
   }

   QSqlQuery query;
   //批量插入,windows风格
   query.perpare("insert into (name,)values(：name,:age,?");
   QVariantList namelist;
   namelist<<""<<"";
   QVariantList agelist;
   agelist<<""<<"";
    query.bindValue(":name",namelist);
    //.....
    query.execBatch();



  //query.exec("select ")
    //设置模型
    model = new QSqlTableModel(this);
    model ->setTable("");//指定使用那个表

    //把model放在view中
    ui->tableView->setModel(model);

    //显示model里的数据
    model->select();
    //设置model编辑模式，手动提交修改
    model->setEditStrategy(2);
    //对视图不允许修改
    ui->tableView->setEditTriggers(0);



}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    QSqlRecord record = model->record();//获取空记录
    //获取行号
    int row = model->rowCount();
    model->insertRecord(row,record);
}

void Widget::on_pushButton_2_clicked()
{
    model->submitAll();//提交动作
}

void Widget::on_pushButton_3_clicked()
{
    model->revertAll();//取消所有动作
    model->submitAll();//提交动作
}

void Widget::on_pushButton_4_clicked()
{
    //获取选中的模型
   QItemSelectionModel *sModel = ui->tableView->selectionMode();
   //取出模型中的索引
   QModelIndexList list= sModel->selectedRows();
   for(int i = 0;i < list.size();i++)
   {
       model->removeRow(list.at(i).row());
   }

}

void Widget::on_pushButton_5_clicked()
{
    QString name = ui->lineEdit->text();
    QString str = QString("wid = '%1'").arg(wid);//
    model->setFilter(str);
    model->select();
}
