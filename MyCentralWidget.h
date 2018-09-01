#ifndef MYCENTRALWIDGET_H
#define MYCENTRALWIDGET_H

#include <QWidget>

class MyCentralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyCentralWidget(QWidget *parent = nullptr);

signals:

public slots:

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *);
};

#endif // MYCENTRALWIDGET_H
