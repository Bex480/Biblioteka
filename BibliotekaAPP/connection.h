#ifndef CONNECTION_H
#define CONNECTION_H

#endif // CONNECTION_H

#include <QSqlDatabase>

static void Connection(){

    QSqlDatabase mydb = QSqlDatabase::addDatabase("QMYSQL");
    mydb.setDatabaseName("biblioteka");


        mydb.setHostName("127.0.0.1");
        mydb.setPort(3306);
        mydb.setUserName("root");
        mydb.setPassword("");

}
