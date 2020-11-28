#ifndef DBCTRL_H
#define DBCTRL_H

#include <QSqlDatabase>

class DBCtrl : public QSqlDatabase {
public:
    DBCtrl();

private:
    QSqlDatabase *m_db;
};

#endif // DBCTRL_H
